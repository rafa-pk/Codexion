/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:38:47 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/17 17:27:29 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	announce_burnout(t_sim *sim, int coder)
{
	long	now;

	pthread_mutex_lock(&sim->mutex);
	now = now_ms() - sim->start;
	sim->active = false;
	printf("%ld %d burned out\n", now, sim->coders[coder].id);
	pthread_cond_broadcast(&sim->cond);
	pthread_mutex_unlock(&sim->mutex);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	t_sim	*sim;

	coder = (t_coder *)arg;
	sim = coder->sim;
	pthread_mutex_unlock(&sim->init_mutex);
	printf("In coder routine\n");
	while (sim_active(sim))
	{
		if (!compile(sim, coder))
			break ;
		if (!debug(sim, coder))
			break ;
		if (!refactor(sim, coder))
			break ;
	}
	return (NULL);
}

void	*monitoring(void *arg)
{
	t_sim	*sim;
	int		i;
	int		dead;

	sim = (t_sim *)arg;
	printf("In monitoring thread\n");
	while (!compiles_done(sim))
	{
		dead = burnout(sim);
		if (dead != -1)
			return (announce_burnout(sim, dead), NULL);
		i++;
		usleep(500);
	}
	pthread_mutex_lock(&sim->mutex);
	sim->active = false;
	pthread_cond_broadcast(&sim->cond);
	pthread_mutex_unlock(&sim->mutex);
	return (NULL);
}
