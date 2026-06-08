/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 10:56:10 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/07 18:10:59 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	args_valid(int ac, char **av)
{
	int		i;
	int		j;
	long	bound_checker;

	i = 1;
	bound_checker = 0;
	while (i < ac - 1)
	{
		j = 0;
		bound_checker = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (fprintf(stderr, NON_INT), false);
			bound_checker = bound_checker * 10 + (av[i][j] - '0');
			if (bound_checker > INT_MAX)
				return (fprintf(stderr, INT_OVERFLOW), false);
			j++;
		}
		i++;
	}
	if (strcmp(av[i], "fifo") && strcmp(av[i], "edf"))
		return (fprintf(stderr, INV_SCHEDULER), false);
	return (true);
}

void	init_args(t_args *args, char **av)
{
	args->number_of_coders = atoi(av[1]);
	args->time_to_burnout_ms = atoi(av[2]);
	args->time_to_compile_ms = atoi(av[3]);
	args->time_to_debug_ms = atoi(av[4]);
	args->time_to_refactor_ms = atoi(av[5]);
	args->number_of_compiles_required = atoi(av[6]);
	args->dongle_cooldown_ms = atoi(av[7]);
	if (!strcmp(av[8], "fifo"))
		args->scheduler = 1;
	else if (!strcmp(av[8], "edf"))
		args->scheduler = 0;
}
