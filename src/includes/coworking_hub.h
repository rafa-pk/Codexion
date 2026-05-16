/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coworking_hub.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 18:31:51 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/16 18:07:21 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COWORKING_HUB_H
# define COWORKING_HUB_H

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
	int		size;
	int		capacity;
}	t_heap;

typedef struct s_dongle
{
	int				id;
	bool			taken;
	long			released_at;
	t_heap			heap;
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			start;
	long			dongle_request;
	pthread_t		thread_id;
	pthread_mutex_t	mutex;
	t_dongle		*left;
	t_dongle		*right;
	struct s_sim	*sim;
}	t_coder;

typedef struct s_sim
{
	bool			active;
	long			start;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_t		monitor;
	t_args			*args;
	t_dongle		*dongles;
	t_coder			*coders;
}	t_sim;

#endif
