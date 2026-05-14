/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz-da- <rvaz-da-@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 14:06:02 by rvaz-da-          #+#    #+#             */
/*   Updated: 2026/05/14 14:55:46 by rvaz-da-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/codexion.h"

//TODO: specify heap's underlying array type, cast to t_coder

void	edf_push(t_heap *heap, t_coder *coder)
{
	heap.list[size] = coder;
	// sift according to earliest deadline
	// deadline = last_compile_start + time_to_burnout
	// smallest = index[0]
}

void	fifo_push(t_heap *heap, t_coder *coder)
{
	heap->list[size] = coder;
	heap->size++;
}

int	heap_peek(t_heap *heap)
{
	return (heap.list[0].id);
}

void	heap_pop(t_heap *heap)
{

}
