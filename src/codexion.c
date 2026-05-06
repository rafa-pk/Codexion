/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.42belgium.be>.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:03:38 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/04 19:19:57 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/codexion.h"

int	main(int ac, char *av[])
{
	t_args	args;

	if (ac > 9)
		return (fprintf(stderr, NOT_ENOUGH_ARGS), 1);
	else if (ac < 9)
		return (fprintf(stderr, TOO_MANY_ARGS), 1);
	if (!args_valid(ac, av))
		return (1);
	args = init_data(av);
	if (!args.scheduler)
		return (1);
	simulation(args);
	// simulation_cleanup(&args)
	return (0);
}
