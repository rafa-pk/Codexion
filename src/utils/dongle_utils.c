/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:06:13 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/17 15:06:16 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

bool	take_one_dongle(t_coder *coder)
{
	long	now;
	long	cooldown;

	cooldown = coder->sim->args->dongle_cooldown_ms;
	now = now_ms();
	pthread_mutex_lock(&coder->sim->mutex);
	while (coder->sim->active && !((now - coder->left->released_at) > cooldown))
		pthread_cond_wait(&coder->sim->cond, &coder->sim->mutex);
	if (!coder->sim->active)
	{
		pthread_mutex_unlock(&coder->sim->mutex);
		return (false);
	}
	pthread_mutex_lock(&coder->mutex);
	coder->left->taken = true;
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_unlock(&coder->sim->mutex);
	return (true);
}

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
	else
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
