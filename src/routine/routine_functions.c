/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:44:20 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/05 15:44:21 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	compile(t_coder *coder)
{
	printf("coder %d is compiling\n", coder->id);
}

void	debug(t_coder *coder)
{
	printf("coder %d is debugging\n", coder->id);
}

void	refactor(t_coder *coder)
{
	printf("coder %d is refactoring\n", coder->id);
}
