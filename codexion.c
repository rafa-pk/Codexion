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

    if (ac != 9)      
        return (1);
    if (!args_valid(ac, av))
        return (1);
    args = init_data(ac, av)
    start_simulation(&args)
    simulation_cleanup(&args)
    return (0);
}
