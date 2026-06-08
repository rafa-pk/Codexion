/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 10:22:02 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 11:13:28 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

struct	s_sim;
struct	s_coder;

typedef struct s_args
{
	int		number_of_coders;
	int		time_to_burnout_ms;
	int		time_to_compile_ms;
	int		time_to_debug_ms;
	int		time_to_refactor_ms;
	int		number_of_compiles_required;
	int		dongle_cooldown_ms;
	int		scheduler;	// 1 FIFO, 0 EDF
}	t_args;

typedef struct s_heap
{
	struct s_coder	**list;
	int				size;
	int				capacity;
}	t_heap;

typedef struct s_dongle
{
	bool			taken;
	int				id;
	long			released_at;
	t_heap			heap;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			compile_start;
	unsigned int	dongle_ticket;
	t_dongle		*left;
	t_dongle		*right;
	struct s_sim	*sim;
	pthread_t		thread_id;
	pthread_mutex_t	mutex;
}	t_coder;

typedef struct s_sim
{
	atomic_bool		active;
	atomic_int		ticket_booth;
	long			start_t;
	t_args			*args;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_t		monitor;
	pthread_mutex_t	mutex;
}	t_sim;

#endif
