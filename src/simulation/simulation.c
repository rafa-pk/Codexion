/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:24:28 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/05 00:31:03 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

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
}

void	simulation(t_args args)
{
	t_sim	sim;

	if (!sim_init(&sim, args))
		return ;
	if (pthread_create(&sim.monitor, NULL, monitoring, &sim))
		return ;
	if (!create_coders(&sim, args.number_of_coders))
		return ;
	wait_for_coders(&sim, args.number_of_coders);
}
