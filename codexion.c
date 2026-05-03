/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 22:03:38 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/04/26 22:03:40 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int    main(int ac, char *av[])
{
    t_args  args;

    if (ac > 9)
        return (fprintf(stderr, "Error: Too many arguments passed (8 required)\n"), 1);
    else if (ac < 9)
        return (fprintf(stderr, "Error: Not enough arguments passed (8 required)\n"), 1);
    if (!args_valid(ac, av))
        return (1);
    args = init_data(av);
    if (!args.scheduler)
        return (1);
    start_simulation(&args)
    //simulation_cleanup(&args)
    return (0);
}
