/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 21:37:45 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 14:04:27 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

bool	single_coder_take(t_coder *coder)
{
	long	now;
	long	cooldown;

	cooldown = coder->sim->args->dongle_cooldown_ms;
	pthread_mutex_lock(&coder->left->mutex);
	while (atomic_load(&coder->sim->active)
		&& !((now_ms() - coder->left->released_at) > cooldown))
		pthread_cond_wait(&coder->left->cond, &coder->left->mutex);
	if (!atomic_load(&coder->sim->active))
		return (pthread_mutex_unlock(&coder->left->mutex), true);
	coder->left->taken = true;
	pthread_mutex_unlock(&coder->left->mutex);
	return (true);
}

bool	try_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	heap_push(&dongle->heap, coder);
	while (atomic_load(&coder->sim->active) && !available(coder, dongle))
		pthread_wait(coder->sim, dongle);
	if (!atomic_load(&coder->sim->active))
		return (pthread_mutex_unlock(&dongle->mutex), false);
	dongle->taken = true;
	heap_pop(&dongle->heap);
	pthread_mutex_unlock(&dongle->mutex);
	return (true);
}

void	put_dongle_back(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->taken = false;
	dongle->released_at = now_ms();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

bool	take_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->sim->args->number_of_coders == 1)
		return (single_coder_take(coder));
	coder->dongle_ticket = atomic_fetch_add(&coder->sim->ticket_booth, 1);
	first = coder->left;
	second = coder->right;
	if (coder->right->id < coder->left->id)
	{
		first = coder->right;
		second = coder->left;
	}
	if (!try_dongle(coder, first))
		return (false);
	if (!try_dongle(coder, second))
		return (put_dongle_back(first), false);
	return (true);
}

void	release_dongles(t_coder *coder)
{
	put_dongle_back(coder->left);
	put_dongle_back(coder->right);
}
