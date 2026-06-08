/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 12:23:11 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/06/08 14:04:03 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/codexion.h"

void	ft_swap(t_coder **a, t_coder **b)
{
	t_coder	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	edf_push(t_heap *heap, t_coder *coder)
{
	heap->list[heap->size] = coder;
	heap->size++;
	if (heap->size == 1)
		return ;
	if (coder->compile_start < heap->list[0]->compile_start
		|| (coder->compile_start == heap->list[0]->compile_start
			&& coder->id < heap->list[0]->id))
		ft_swap(&heap->list[0], &heap->list[heap->size - 1]);
}

void	fifo_push(t_heap *heap, t_coder *coder)
{
	heap->list[heap->size] = coder;
	heap->size++;
	if (heap->size == 1)
		return ;
	if (coder->dongle_ticket < heap->list[0]->dongle_ticket)
		ft_swap(&heap->list[0], &heap->list[heap->size - 1]);
}
