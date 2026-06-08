/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:18:30 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 12:54:08 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	heap_push(t_heap *heap, t_coder *coder)
{
	if (coder->sim->args->scheduler)
		fifo_push(heap, coder);
	else
		edf_push(heap, coder);
}

int	heap_peek(t_heap *heap)
{
	if (heap->size == 0)
		return (-1);
	return (heap->list[0]->id);
}

void	heap_pop(t_heap *heap)
{
	if (heap->size == 0)
		return ;
	if (heap->size > 1)
		ft_swap(&heap->list[0], &heap->list[heap->size - 1]);
	heap->size--;
}
