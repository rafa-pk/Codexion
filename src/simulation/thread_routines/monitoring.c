/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 12:04:52 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/07 18:08:00 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

bool	compiles_done(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args->number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		if (sim->coders[i].compile_count
			< sim->args->number_of_compiles_required)
			return (pthread_mutex_unlock(&sim->coders[i].mutex), false);
		pthread_mutex_unlock(&sim->coders[i].mutex);
		i++;
	}
	return (true);
}

int	burnout(t_sim *sim)
{
	long	last_compile;
	long	delta;
	int		i;

	i = 0;
	while (i < sim->args->number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		last_compile = sim->coders[i].compile_start;
		pthread_mutex_unlock(&sim->coders[i].mutex);
		delta = now_ms() - last_compile;
		if (delta > sim->args->time_to_burnout_ms)
			return (i);
		i++;
	}
	return (-1);
}

void	announce_burnout(t_sim *sim, int dead_coder)
{
	long	now;

	atomic_store(&sim->active, false);
	pthread_mutex_lock(&sim->mutex);
	now = now_ms() - sim->start_t;
	printf("%ld %d burned out\n", now, sim->coders[dead_coder].id);
	pthread_mutex_unlock(&sim->mutex);
	broadcast_all(sim);
}

void	*monitoring(void *arg)
{
	t_sim	*sim;
	int		dead;

	sim = (t_sim *)arg;
	sim->start_t = now_ms();
	while (!compiles_done(sim))
	{
		dead = burnout(sim);
		if (dead != -1)
			return (announce_burnout(sim, dead), NULL);
		usleep(500);
	}
	atomic_store(&sim->active, false);
	broadcast_all(sim);
	return (NULL);
}
