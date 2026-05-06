/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 10:16:29 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/04 19:30:09 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

bool	init_dongle(t_dongle *dongle, int id)
{
	dongle->id = id;
	dongle->used = false;
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (false);
	return (true);
}

void	init_coder(t_sim *sim, t_coder *coder, int id, int nb_coders)
{
	coder->id = id;
	coder->compile_count = 0;
	coder->thread_id = 0;
	coder->sim = sim;
	coder->left = &sim->dongles[id];
	coder->right = &sim->dongles[(id + 1) % nb_coders];
}

bool	sim_init(t_sim *sim, t_args args)
{
	int	i;

	i = 0;
	sim->args = args;
	sim->monitor = 0;
	sim->coders = malloc(sizeof(t_coder) * args.number_of_coders);
	sim->dongles = malloc(sizeof(t_dongle) * args.number_of_coders);
	if (!sim->coders || !sim->dongles)
		return (false);
	while (i < args.number_of_coders)
	{
		if (!init_dongle(&sim->dongles[i], i))
			return (safe_exit_mutexes(sim, i),
				free(args.scheduler), false);
		i++;
	}
	i = 0;
	while (i < args.number_of_coders)
	{
		init_coder(sim, &sim->coders[i], i, args.number_of_coders);
		i++;
	}
	return (true);
}
