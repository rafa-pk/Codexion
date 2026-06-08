/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 11:00:21 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 12:44:09 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

bool	sim_init(t_sim *sim, t_args *args)
{
	int	i;

	i = -1;
	sim->active = true;
	sim->ticket_booth = 0;
	sim->start_t = now_ms();
	sim->args = args;
	pthread_mutex_init(&sim->mutex, NULL);
	sim->dongles = malloc(sizeof(t_dongle) * args->number_of_coders);
	sim->coders = malloc(sizeof(t_coder) * args->number_of_coders);
	if (!sim->dongles || !sim->coders)
		return (free(sim->dongles), false);
	while (++i < args->number_of_coders)
	{
		if (!init_dongle(&sim->dongles[i], i))
			return (safe_exit_dong(sim, sim->dongles, i), false);
	}
	i = -1;
	while (++i < args->number_of_coders)
	{
		if (!init_coder(sim, &sim->coders[i], i, args->number_of_coders))
			return (safe_exit_coder(sim, sim->coders, i), false);
	}
	return (true);
}

bool	create_coders(t_sim *sim, int nb_coders)
{
	int	i;

	i = 0;
	while (i < nb_coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		sim->coders[i].compile_start = now_ms();
		pthread_mutex_unlock(&sim->coders[i].mutex);
		if (pthread_create(&sim->coders[i].thread_id, NULL, routine,
				&sim->coders[i]))
			return (false);
		i++;
	}
	return (true);
}

void	wait_for_coders(t_sim *sim, int nb_coders)
{
	int	i;

	i = 0;
	while (i < nb_coders)
	{
		pthread_join(sim->coders[i].thread_id, NULL);
		i++;
	}
	pthread_join(sim->monitor, NULL);
}

void	cleanup(t_sim *sim)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&sim->mutex);
	while (i < sim->args->number_of_coders)
	{
		free(sim->dongles[i].heap.list);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
		pthread_mutex_destroy(&sim->coders[i].mutex);
		i++;
	}
	free(sim->dongles);
	free(sim->coders);
}

bool	simulation(t_args *args)
{
	t_sim	sim;

	if (!sim_init(&sim, args))
		return (false);
	if (pthread_create(&sim.monitor, NULL, monitoring, &sim))
		return (monitor_failure_exit(&sim), false);
	if (!create_coders(&sim, args->number_of_coders))
		return (false);
	wait_for_coders(&sim, args->number_of_coders);
	cleanup(&sim);
	return (true);
}
