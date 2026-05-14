/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:38:47 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/14 12:39:08 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	*routine(void *arg)
{
	t_coder	*coder;
	t_sim	*sim;

	coder = (t_coder *)arg;
	sim = coder->sim;
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
		if (dead!= -1)
		{
			pthread_mutex_lock(&sim->mutex);
			sim->active = false;
			printf("coder %d burned out\n", dead);
			pthread_mutex_unlock(&sim->mutex);
			return (NULL);
		}
		i++;
		usleep(500);
	}
	pthread_mutex_lock(&sim->mutex);
	sim->active = false;
	pthread_mutex_unlock(&sim->mutex);
	return (NULL);
}
