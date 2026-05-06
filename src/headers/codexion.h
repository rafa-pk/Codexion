/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:03:30 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/04 19:16:52 by rvaz-da-         ###   ########.fr       */
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

// SCHEDULERS
# define FIFO "fifo"
# define EDF "edf"

// ERROR MESSAGES
# define NOT_ENOUGH_ARGS "Error: Too many arguments passed (8 required)\n"
# define TOO_MANY_ARGS "Error: Not enough arguments passed (8 required)\n"

# define NON_INT "Parsing Error: argument is not a valid positive integer\n"
# define INT_OVERFLOW "Parsing Error: argument exceeds INT_MAX\n"
# define INV_SCHEDULER "Parsing Error: Scheduler only accepts 'fifo' or 'edf'\n"
# define SCHEDULER_ALLOC "Allocation Error: scheduler type arg\n"

struct	s_sim;

typedef struct s_args
{
	int		number_of_coders;
	int		time_to_burnout_ms;
	int		time_to_compile_ms;
	int		time_to_debug_ms;
	int		time_to_refactor_ms;
	int		number_of_compiles_required;
	int		dongle_cooldown_ms;
	char	*scheduler;
}	t_args;

typedef struct s_dongle
{
	bool			used;
	int				id;
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	pthread_t		thread_id;
	struct s_sim	*sim;
	t_dongle		*right;
	t_dongle		*left;
}	t_coder;

typedef struct s_sim
{
	pthread_t	monitor;
	t_coder		*coders;
	t_dongle	*dongles;
	t_args		args;
}	t_sim;

// PARSING
bool	args_valid(int ac, char **av);
bool	ft_isdigit(int c);
char	*ft_strdup(char *str);
t_args	init_data(char *av[]);

// INIT
bool	init_dongle(t_dongle *dongle, int id);
void	init_coder(t_sim *sim, t_coder *coder, int id, int nb_coders);
bool	sim_init(t_sim *sim, t_args args);

// SIMULATION INIT
bool	create_coders(t_sim *sim, int nb_coders);
void	wait_for_coders(t_sim *sim, int nb_coders);

// ROUTINE
void	compile(t_coder *coder);
void	debug(t_coder *coder);
void	refactor(t_coder *coder);
void	start_routine(t_coder *coder, t_args args);
void	*routine(void *arg);

// MONITORING
void	*monitoring(void *arg);

void	simulation(t_args args);
//void  cleanup(t_args *args)

// UTILS
void	safe_exit_mutexes(t_sim *sim, int ix);
bool	check_compilations(t_sim *sim, t_args args);

#endif
