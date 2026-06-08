/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 11:42:01 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 14:06:22 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + (tv.tv_usec / 1000L));
}

void	broadcast_all(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->args->number_of_coders)
	{
		pthread_mutex_lock(&sim->dongles[i].mutex);
		pthread_cond_broadcast(&sim->dongles[i].cond);
		pthread_mutex_unlock(&sim->dongles[i].mutex);
		i++;
	}
}

void	printx(t_sim *sim, t_coder *coder, char *message)
{
	long	now;

	pthread_mutex_lock(&sim->mutex);
	now = now_ms() - sim->start_t;
	if (atomic_load(&sim->active))
		printf("%ld %d %s", now, coder->id, message);
	pthread_mutex_unlock(&sim->mutex);
}

void	has_taken_dongles(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	printx(sim, coder, "has taken a dongle\n");
	printx(sim, coder, "has taken a dongle\n");
}

void	precise_sleep(t_sim *sim, int sleep_ms)
{
	long	starting_time;

	starting_time = now_ms();
	while (now_ms() - starting_time < sleep_ms)
	{
		if (!atomic_load(&sim->active))
			return ;
		usleep(100);
	}
}
