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

int     args_valid(int ac, char *av[]);
t_args  init_data(int ac, char *av[]);
void    start_simulation(t_args *args)
void    simulation_cleanup(t_args *args)

# endif
