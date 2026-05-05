/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:45:31 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/04 18:45:33 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	start_routine(t_coder *coder, t_args args)
{
	int	i;

	i = 0;
	while (i < args.number_of_compiles_required)
	{
		compile(coder);
		debug(coder);
		refactor(coder);
		i++;
	}
}

void	*routine(void *arg)
{
	t_coder	*coder;
	t_args	*args;

	coder = (t_coder *)arg;
	args = &coder->sim->args;
	start_routine(coder, *args);
	return (NULL);
}
