/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 11:42:43 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 12:40:46 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	safe_exit_dong(t_sim *sim, t_dongle *dongles, int id)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sim->mutex);
	while (i < id)
	{
		free(dongles[i].heap.list);
		pthread_mutex_destroy(&dongles[i].mutex);
		pthread_cond_destroy(&dongles[i].cond);
		i++;
	}
	free(sim->dongles);
	free(sim->coders);
}

void	safe_exit_coder(t_sim *sim, t_coder *coders, int id)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&sim->mutex);
	while (++i < sim->args->number_of_coders)
	{
		free(sim->dongles[i].heap.list);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
	}
	i = -1;
	while (++i < id)
		pthread_mutex_destroy(&coders[i].mutex);
	free(sim->dongles);
	free(sim->coders);
}

void	monitor_failure_exit(t_sim *sim)
{
	safe_exit_coder(sim, sim->coders, sim->args->number_of_coders);
}
