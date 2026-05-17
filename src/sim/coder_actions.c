/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 15:49:44 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/17 14:57:34 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	precise_sleep(t_sim *sim, int sleep_ms)
{
	long	starting_time;

	starting_time = now_ms();
	while (now_ms() - starting_time < sleep_ms)
	{
		if (!sim_active(sim))
			return ;
		usleep(100);
	}
}

bool	compile(t_sim *sim, t_coder *coder)
{
	if (!take_dongles(coder))
		return (false);
	printx(sim, coder, "has taken a dongle\n");
	printx(sim, coder, "has taken a dongle\n");
	if (!sim_active(sim))
		return (release_dongles(coder), false);
	pthread_mutex_lock(&coder->mutex);
	coder->start = now_ms();
	coder->compile_count++;
	pthread_mutex_unlock(&coder->mutex);
	printx(sim, coder, "is compiling\n");
	precise_sleep(sim, sim->args->time_to_compile_ms);
	release_dongles(coder);
	if (!sim_active(sim))
		return (false);
	return (true);
}

bool	debug(t_sim *sim, t_coder *coder)
{
	printx(sim, coder, "is debugging\n");
	precise_sleep(sim, sim->args->time_to_debug_ms);
	if (!sim_active(sim))
		return (false);
	return (true);
}

bool	refactor(t_sim *sim, t_coder *coder)
{
	printx(sim, coder, "is refactoring\n");
	precise_sleep(sim, sim->args->time_to_refactor_ms);
	if (!sim_active(sim))
		return (false);
	return (true);
}
