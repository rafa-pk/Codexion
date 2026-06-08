/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 10:18:47 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 14:03:41 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdatomic.h>
# include "macros.h"
# include "structs.h"

// Parsing
bool	ft_isdigit(int c);
bool	args_valid(int ac, char **av);
void	init_args(t_args *args, char **av);

// Simulation
bool	simulation(t_args *args);
bool	sim_init(t_sim *sim, t_args *args);
bool	init_heap(t_heap *heap);
bool	init_dongle(t_dongle *dongles, int id);
bool	init_coder(t_sim *sim, t_coder *coders, int id, int nb_coders);
bool	compiles_done(t_sim *sim);
bool	create_coders(t_sim *sim, int nb_coders);
bool	compile(t_sim *sim, t_coder *coder);
bool	debug(t_sim *sim, t_coder *coder);
bool	refactor(t_sim *sim, t_coder *coder);
int		burnout(t_sim *sim);
void	announce_burnout(t_sim *sim, int dead_coder);
void	*monitoring(void *arg);
void	*routine(void *arg);
void	wait_for_coders(t_sim *sim, int nb_coders);
void	cleanup(t_sim *sim);

// Dongles
bool	single_coder_take(t_coder *coder);
bool	try_dongle(t_coder *coder, t_dongle *dongle);
bool	take_dongles(t_coder *coder);
bool	available(t_coder *coder, t_dongle *dongle);
void	put_dongle_back(t_dongle *dongle);
void	release_dongles(t_coder *coder);
void	next_wakeup(t_dongle *dongle, long cooldown_ms,
			struct timespec *deadline);
void	pthread_wait(t_sim *sim, t_dongle *dongle);

// Heap
void	ft_swap(t_coder **a, t_coder **b);
void	edf_push(t_heap *heap, t_coder *coder);
void	fifo_push(t_heap *heap, t_coder *coder);
void	heap_push(t_heap *heap, t_coder *coder);
void	heap_pop(t_heap *heap);
int		heap_peek(t_heap *heap);

// Utils
long	now_ms(void);
void	safe_exit_dong(t_sim *sim, t_dongle *dongles, int id);
void	safe_exit_coder(t_sim *sim, t_coder *coders, int id);
void	monitor_failure_exit(t_sim *sim);
void	broadcast_all(t_sim *sim);
void	precise_sleep(t_sim *sim, int sleep_ms);
void	printx(t_sim *sim, t_coder *coder, char *message);
void	has_taken_dongles(t_coder *coder);

#endif
