/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.42belgium.be>. +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:14:30 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/04 18:59:21 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*duplicate;

	if (!str)
		return (NULL);
	i = 0;
	duplicate = malloc(sizeof(char) * (strlen(str) + 1));
	if (!duplicate)
		return (NULL);
	while (str[i])
	{
		duplicate[i] = str[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
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
	if (strcmp(av[i], FIFO) && strcmp(av[i], EDF))
		return (fprintf(stderr, INV_SCHEDULER), false);
	return (true);
}

t_args	init_data(char *av[])
{
	t_args	args;

	args.number_of_coders = atoi(av[1]);
	args.time_to_burnout_ms = atoi(av[2]);
	args.time_to_compile_ms = atoi(av[3]);
	args.time_to_debug_ms = atoi(av[4]);
	args.time_to_refactor_ms = atoi(av[5]);
	args.number_of_compiles_required = atoi(av[6]);
	args.dongle_cooldown_ms = atoi(av[7]);
	args.scheduler = ft_strdup(av[8]);
	if (!args.scheduler)
		return (fprintf(stderr, SCHEDULER_ALLOC), (t_args){0});
	return (args);
}
