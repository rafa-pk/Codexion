/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:58:24 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 14:05:50 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

bool	available(t_coder *coder, t_dongle *dongle)
{
	long	now;
	int		cooldown;

	now = now_ms();
	cooldown = coder->sim->args->dongle_cooldown_ms;
	return (!dongle->taken && (now - dongle->released_at) > cooldown
		&& heap_peek(&dongle->heap) == coder->id);
}

void	next_wakeup(t_dongle *dongle, long cooldown_ms,
				struct timespec *deadline)
{
	long	now;
	long	wakeup;

	now = now_ms();
	wakeup = dongle->released_at + cooldown_ms;
	if (wakeup <= now)
		wakeup = now + 2;
	deadline->tv_sec = wakeup / 1000;
	deadline->tv_nsec = (wakeup % 1000) * 1000000L;
}

void	pthread_wait(t_sim *sim, t_dongle *dongle)
{
	struct timespec	deadline;

	next_wakeup(dongle, sim->args->dongle_cooldown_ms, &deadline);
	pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &deadline);
}
