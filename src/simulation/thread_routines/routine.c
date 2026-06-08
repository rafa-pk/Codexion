/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:26:22 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 14:06:11 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

bool	compile(t_sim *sim, t_coder *coder)
{
	if (!take_dongles(coder))
		return (false);
	has_taken_dongles(coder);
	if (!atomic_load(&sim->active))
		return (release_dongles(coder), false);
	pthread_mutex_lock(&coder->mutex);
	coder->compile_start = now_ms();
	coder->compile_count++;
	pthread_mutex_unlock(&coder->mutex);
	printx(sim, coder, "is compiling\n");
	precise_sleep(sim, sim->args->time_to_compile_ms);
	release_dongles(coder);
	if (!atomic_load(&sim->active))
		return (false);
	return (true);
}

bool	debug(t_sim *sim, t_coder *coder)
{
	printx(sim, coder, "is debugging\n");
	precise_sleep(sim, sim->args->time_to_debug_ms);
	if (!atomic_load(&sim->active))
		return (false);
	return (true);
}

bool	refactor(t_sim *sim, t_coder *coder)
{
	printx(sim, coder, "is refactoring\n");
	precise_sleep(sim, sim->args->time_to_refactor_ms);
	if (!atomic_load(&sim->active))
		return (false);
	return (true);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	t_sim	*sim;

	coder = (t_coder *)arg;
	sim = coder->sim;
	pthread_mutex_lock(&coder->mutex);
	coder->compile_start = now_ms();
	pthread_mutex_unlock(&coder->mutex);
	while (atomic_load(&sim->active))
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
