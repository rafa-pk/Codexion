/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:59:12 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/14 12:42:38 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	safe_exit_dong(t_sim *sim, t_dongle *dongles, int ix)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sim->mutex);
	while (i <= ix)
	{
		free(dongles[i].heap.list);
		pthread_mutex_destroy(&dongles[i].mutex);
		pthread_cond_destroy(&dongles[i].cond);
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
	while (i < sim->args->number_of_coders)
	{
		free(sim->dongles[i].heap.list);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
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

