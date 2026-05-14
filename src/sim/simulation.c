/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:01:23 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/14 19:19:08 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

bool	sim_init(t_sim *sim, t_args *args)
{
	int	i;

	i = 0;
	sim->active = true;
	sim->start = now_ms();
	sim->args = args;
	pthread_mutex_init(&sim->mutex, NULL);
	pthread_cond_init(&sim->cond, NULL);
	sim->dongles = malloc(sizeof(t_dongle) * args->number_of_coders);
	sim->coders = malloc(sizeof(t_coder) * args->number_of_coders);
	if (!sim->dongles && !sim->coders)
		return (false);
	while (i < args->number_of_coders)
	{
		if (!init_dongle(&sim->dongles[i], i))
			return (safe_exit_dong(sim, sim->dongles, i), false);
		i++;
	}
	i = 0;
	while (i < args->number_of_coders)
	{
		if (!init_coder(sim, &sim->coders[i], i, args->number_of_coders))
			return (safe_exit_code(sim, sim->coders, i), false);
		i++;
	}
	return (true);
}

bool	create_coders(t_sim *sim, int nb_coders)
{
	int	i;

	i = 0;
	while (i < nb_coders)
	{
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
	pthread_cond_destroy(&sim->cond);
	while (i < sim->args->number_of_coders)
	{
		free(sim->dongles[i].heap.list);
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_mutex_destroy(&sim->coders[i].mutex);
		i++;
	}
	free(sim->dongles);
	free(sim->coders);
}

void	print_args(t_args *args)
{
	printf("Number of coders: %d\n", args->number_of_coders);
	printf("Time to burnout: %d ms\n", args->time_to_burnout_ms);
	printf("Time to compile: %d ms\n", args->time_to_compile_ms);
	printf("Time to debug: %d ms\n", args->time_to_debug_ms);
	printf("Time to refactor: %d ms\n", args->time_to_refactor_ms);
	printf("Number of compiles req: %d\n", args->number_of_compiles_required);
	printf("Dongle cooldown: %d ms\n", args->dongle_cooldown_ms);
	if (args->scheduler)
		printf("Scheduler: 'fifo'\n");
	else
		printf("Scheduler: 'edf'\n");
}

bool	simulation(t_args *args)
{
	t_sim	sim;

	if (!sim_init(&sim, args))
		return (false);
	//print_args(args);
	if (pthread_create(&sim.monitor, NULL, monitoring, &sim))
		return (false);	//TODO: cleanup on failure
	printf("Monitor thread created\n");
	if (!create_coders(&sim, args->number_of_coders))
		return (false);	//TODO: idem
	wait_for_coders(&sim, args->number_of_coders);
	cleanup(&sim);
	return (true);
}
