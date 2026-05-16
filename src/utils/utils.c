/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 13:41:28 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/16 16:13:02 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + (tv.tv_usec / 1000L));
}

bool	sim_active(t_sim *sim)
{
	bool	active;

	pthread_mutex_lock(&sim->mutex);
	active = sim->active;
	pthread_mutex_unlock(&sim->mutex);
	return (active);
}

bool	compiles_done(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args->number_of_coders)
	{
		pthread_mutex_lock(&sim->coders[i].mutex);
		if (sim->coders[i].compile_count < sim->args->number_of_compiles_required)
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
		last_compile = sim->coders[i].start;
		pthread_mutex_unlock(&sim->coders[i].mutex);
		delta = now_ms() - last_compile;
		if (delta > sim->args->time_to_burnout_ms)
			return (i);
		i++;
	}
	return (-1);
}

void	printx(t_sim *sim, t_coder *coder, char *message)
{
	long	now;
	
	pthread_mutex_lock(&coder->mutex);
	now = now_ms() - sim->start;
	if (sim->active)
		printf("%ld %d %s", now, coder->id, message);
	pthread_mutex_unlock(&coder->mutex);
}
