/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 14:06:02 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/14 18:19:51 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

void	edf_push(t_heap *heap, t_coder *coder)
{
	heap->list[heap->size] = coder;
	heap->size++;
	if (heap->size == 1)
		return ;
	if (heap->list[0]->start > heap->list[heap->size - 1]->start)
			ft_swap(&heap->list[0], &heap->list[heap->size - 1]);
}

void	fifo_push(t_heap *heap, t_coder *coder)
{
	heap->list[heap->size] = coder;
	heap->size++;
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
