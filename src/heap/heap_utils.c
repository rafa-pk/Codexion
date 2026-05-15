/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:21:24 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/15 16:27:19 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	ft_swap(t_coder **a, t_coder **b)
{
	t_coder	*tmp;

	tmp = *a;
	a = b;
	b = &tmp;
}

void	heap_push(t_heap *heap, t_coder *coder)
{
	if (coder->sim->args->scheduler)
		fifo_push(heap, coder);
	else
		edf_push(heap, coder);
}
