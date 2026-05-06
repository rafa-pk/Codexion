/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:25:26 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/04 19:18:35 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/codexion.h"

void	safe_exit_mutexes(t_sim *sim, int ix)
{
	int	i;

	i = 0;
	while (i < ix)
	{
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		i++;
	}
	free(sim->dongles);
	free(sim->coders);
}

bool	check_compilations(t_sim *sim, t_args args)
{
	int	i;

	i = 0;
	while (i < args.number_of_coders)
	{
		if (sim->coders[i].compile_count < args.number_of_compiles_required)
			return (false);
		i++;
	}
	return (true);
}
