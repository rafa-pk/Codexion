/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:04:49 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/17 15:03:06 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

bool	init_heap(t_heap *heap)
{
	heap->list = malloc(sizeof(t_coder) * 2);
	if (!heap->list)
		return (false);
	heap->size = 0;
	heap->capacity = 2;
	return (true);
}

bool	init_dongle(t_dongle *dongle, int id)
{
	dongle->id = id;
	dongle->taken = false;
	dongle->released_at = 0;
	if (!init_heap(&dongle->heap))
		return (false);
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (false);
	return (true);
}

bool	init_coder(t_sim *sim, t_coder *coder, int id, int nb_coders)
{
	coder->id = id;
	coder->compile_count = 0;
	coder->start = sim->start;
	coder->dongle_request = 0;
	coder->thread_id = 0;
	if (pthread_mutex_init(&coder->mutex, NULL))
		return (false);
	coder->left = &sim->dongles[id];
	coder->right = &sim->dongles[(id + 1) % nb_coders];
	coder->sim = sim;
	return (true);
}
