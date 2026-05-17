/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:24:08 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/17 17:34:54 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

bool	available(t_coder *coder, t_dongle *left, t_dongle *right)
{
	bool	available;
	long	now;
	long	cooldown;

	cooldown = coder->sim->args->dongle_cooldown_ms;
	now = now_ms();
	pthread_mutex_lock(&left->mutex);
	pthread_mutex_lock(&right->mutex);
	available = !left->taken && !right->taken
		&& (now - left->released_at) > cooldown
		&& (now - right->released_at) > cooldown
		&& (heap_peek(&left->heap) == coder->id
			|| heap_peek(&right->heap) == coder->id);
	pthread_mutex_unlock(&left->mutex);
	pthread_mutex_unlock(&right->mutex);
	return (available);
}

void	claim_both_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->mutex);
	pthread_mutex_lock(&coder->right->mutex);
	coder->left->taken = true;
	coder->right->taken = true;
	heap_pop(&coder->left->heap);
	heap_pop(&coder->right->heap);
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_unlock(&coder->right->mutex);
}

bool	take_dongles(t_coder *coder)
{
	if (coder->sim->args->number_of_coders == 1)
		return (take_one_dongle(coder));
	pthread_mutex_lock(&coder->left->mutex);
	heap_push(&coder->left->heap, coder);
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_lock(&coder->right->mutex);
	heap_push(&coder->right->heap, coder);
	pthread_mutex_unlock(&coder->right->mutex);
	pthread_mutex_lock(&coder->sim->mutex);
	while (coder->sim->active && !available(coder, coder->left, coder->right))
		pthread_wait(coder->sim, coder);
	if (!coder->sim->active)
	{
		pthread_mutex_unlock(&coder->sim->mutex);
		return (false);
	}
	claim_both_dongles(coder);
	pthread_mutex_unlock(&coder->sim->mutex);
	return (true);
}

void	release_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->mutex);
	pthread_mutex_lock(&coder->left->mutex);
	coder->left->taken = false;
	coder->left->released_at = now_ms();
	pthread_mutex_unlock(&coder->left->mutex);
	pthread_mutex_lock(&coder->right->mutex);
	coder->right->taken = false;
	coder->right->released_at = now_ms();
	pthread_mutex_unlock(&coder->right->mutex);
	pthread_cond_broadcast(&coder->sim->cond);
	pthread_mutex_unlock(&coder->sim->mutex);
}
