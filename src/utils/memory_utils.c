/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:59:12 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/16 17:13:54 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	safe_exit_dong(t_sim *sim, t_dongle *dongles, int ix)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sim->mutex);
	pthread_cond_destroy(&sim->cond);
	while (i <= ix)
	{
		free(dongles[i].heap.list);
		pthread_mutex_destroy(&dongles[i].mutex);
		i++;
	}
	free(sim->dongles);
	free(sim->coders);
}

void	safe_exit_code(t_sim *sim, t_coder *coders, int ix)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sim->mutex);
	pthread_cond_destroy(&sim->cond);
	while (i < sim->args->number_of_coders)
	{
		free(sim->dongles[i].heap.list);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		i++;
	}
	i = 0;
	while (i <= ix)
	{
		pthread_mutex_destroy(&coders[i].mutex);
		i++;
	}
	free(sim->dongles);
	free(sim->coders);
}

void	monitor_failure_exit(t_sim *sim)
{
	safe_exit_code(sim, sim->coders, sim->args->number_of_coders);
}

void	coder_failure_exit(t_sim *sim, int ix)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->mutex);
	sim->active = false;
	pthread_cond_broadcast(&sim->cond);
	pthread_mutex_unlock(&sim->mutex);
	while (i < ix)
	{
		pthread_join(sim->coders[i].thread_id, NULL);
		i++;
	}
	safe_exit_code(sim, sim->coders, sim->args->number_of_coders);
}
