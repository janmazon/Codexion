/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamarer <jcamarer@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 15:59:04 by jcamarer          #+#    #+#             */
/*   Updated: 2026/09/10 17:20:27 by jcamarer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_insert(t_heap *heap, t_request request)
{
	int			current;
	int			parent;
	t_request	tmp;

	heap->requests[heap->size] = request;
	current = heap->size;
	heap->size += 1;
	while (current > 0)
	{
		parent = (current - 1) / 2;
		if (heap->requests[current].priority < heap->requests[parent].priority)
		{
			tmp = heap->requests[current];
			heap->requests[current] = heap->requests[parent];
			heap->requests[parent] = tmp;
			current = parent;
		}
		else
			break ;
	}
}

static int	get_smallest_son(t_heap *heap, int current)
{
	int	smallest_son;

	smallest_son = 2 * current + 1;
	if ((2 * current + 2) < heap->size)
	{
		if (heap->requests[2 * current + 2].priority
			< heap->requests[smallest_son].priority)
			smallest_son = 2 * current + 2;
	}
	return (smallest_son);
}

t_request	heap_extract(t_heap *heap)
{
	int			current;
	int			smallest_son;
	t_request	extracted;
	t_request	tmp;

	extracted = heap->requests[0];
	heap->size -= 1;
	heap->requests[0] = heap->requests[heap->size];
	current = 0;
	while ((2 * current + 1) < heap->size)
	{
		smallest_son = get_smallest_son(heap, current);
		if (heap->requests[current].priority
			> heap->requests[smallest_son].priority)
		{
			tmp = heap->requests[current];
			heap->requests[current] = heap->requests[smallest_son];
			heap->requests[smallest_son] = tmp;
			current = smallest_son;
		}
		else
			break ;
	}
	return (extracted);
}
