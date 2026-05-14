/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 18:09:36 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/14 12:36:50 by rvaz-da-         ###   ########.fr       */
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
		return (1);
	return (0);
}
