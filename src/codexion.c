/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 10:16:05 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/07 10:18:40 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"

int	main(int ac, char *av[])
{
	t_args	args;

	if (ac < 9)
		return (fprintf(stderr, NOT_ENOUGH_ARGS), 1);
	else if (ac > 9)
		return (fprintf(stderr, TOO_MANY_ARGS), 1);
	if (!args_valid(ac, av))
		return (1);
	init_args(&args, av);
	if (!simulation(&args))
		return (fprintf(stderr, SIM_FAILED), 1);
	return (0);
}
