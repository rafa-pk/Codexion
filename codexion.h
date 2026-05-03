/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:03:30 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/04/26 23:00:04 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define FIFO "fifo"
# define EDF "edf"

typedef struct s_args
{
    int     number_of_coders;
    int     time_to_burnout_ms;
    int     time_to_compile_ms;
    int     time_to_debug_ms;
    int     time_to_refactor_ms;
    int     number_of_compiles_required;
    int     dongle_cooldown_ms;
    char    *scheduler;
}   t_args;

bool      args_valid(int ac, char **av);
t_args    init_data(char *av[]);
//void    start_simulation(t_args *args)
//void    simulation_cleanup(t_args *args)
bool      ft_isdigit(int c);

# endif
