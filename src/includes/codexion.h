/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 18:24:43 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/13 18:08:56 by rvaz-da-         ###   ########.fr       */
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
# include "coworking_hub.h"

# define FIFO 1
# define EDF 0

// ERROR MESSAGES
# define NOT_ENOUGH_ARGS "Error: Too many arguments passed (8 required)\n"
# define TOO_MANY_ARGS "Error: Not enough arguments passed (8 required)\n"
# define NON_INT "Parsing Error: argument is not a valid positive integer\n"
# define INT_OVERFLOW "Parsing Error: argument exceeds INT_MAX\n"
# define INV_SCHEDULER "Parsing Error: Scheduler only accepts 'fifo' or 'edf'\n"

// Parsing
bool	ft_isdigit(int c);
bool	args_valid(int ac, char **av);
void	init_args(t_args *args, char **av);

// Simulation
bool	init_heap(t_heap *heap);
bool	init_dongle(t_dongle *dongle, int id);
bool	init_coder(t_sim *sim, t_coder *coder, int id, int nb_coders);
bool	sim_init(t_sim *sim, t_args *args);
bool	create_coders(t_sim *sim, int nb_coders);
bool	simulation(t_args *args);
void	wait_for_coders(t_sim *sim, int nb_coders);
void	cleanup(t_sim *sim);

//Routine
void	*routine(void *arg);
bool	compile(t_sim *sim, t_coder *coder);
bool	debug(t_sim *sim, t_coder *coder);
bool	refactor(t_sim *sim, t_coder *coder);

//Monitor
void	*monitoring(void *arg);

// Utils
long	now_ms(void);
bool	sim_active(t_sim *sim);
bool	compiles_done(t_sim *sim);
int		burnout(t_sim *sim);
void	precise_sleep(t_sim *sim, int sleep_ms);
void	printx(t_sim *sim, t_coder *coder, char *message);
void	safe_exit_dong(t_sim *sim, t_dongle *dongle, int ix);
void	safe_exit_code(t_sim *sim, t_coder *coder, int ix);

#endif
