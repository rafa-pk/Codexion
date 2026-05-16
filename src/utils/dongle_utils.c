/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:52:27 by rvaz-da-          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	next_wakeup(t_coder *coder, long cooldown_ms, struct timespec *deadline)
{
	long	now;
	long	left;
	long	right;
	long	earliest;

	now = now_ms();
	pthread_mutex_lock(&coder->left->mutex);
	left = coder->left->released_at + cooldown_ms;
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_lock(&coder->right->mutex);
	right = coder->right->released_at + cooldown_ms;
	pthread_mutex_unlock(&coder->right->mutex);
	if (left < right)
		earliest = left;
	else if (right < left)
		earliest = right;
	if (earliest <= now)
		earliest = now + 50;
	deadline->tv_sec = earliest / 1000;
	deadline->tv_nsec = (earliest % 1000) * 1000000L;
}

void	pthread_wait(t_sim *sim, t_coder *coder)
{
	struct timespec	deadline;

	next_wakeup(coder, sim->args->dongle_cooldown_ms, &deadline);
	pthread_cond_timedwait(&sim->cond, &sim->mutex, &deadline);
}
