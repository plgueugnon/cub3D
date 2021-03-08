/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:06:36 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/01 13:09:48 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void	ft_cleanup_queue(t_queue *q)
{
	while (!ft_queue_is_empty(q))
		ft_remove_from_queue(q);
	if (q)
		free(q);
	q = NULL;
}

void	ft_initialise_queue(t_queue *q)
{
	q->count = 0;
	q->front = NULL;
	q->rear = 0;
}

int		ft_queue_is_empty(t_queue *q)
{
	if (q->rear == NULL)
		return (1);
	return (0);
}

void	ft_add_to_queue(t_queue *q, int y, int x, t_data *data)
{
	t_node	*tmp;

	tmp = malloc(sizeof(t_node));
	if (tmp == NULL)
		ft_map_error("Error\nMalloc of node failed", data);
	if (tmp)
	{
		tmp->x = x;
		tmp->y = y;
		tmp->next = NULL;
	}
	if (!ft_queue_is_empty(q))
	{
		q->rear->next = tmp;
		q->rear = tmp;
	}
	else
	{
		q->front = q->rear;
		q->front = tmp;
		q->rear = q->front;
		q->rear = tmp;
	}
	q->count++;
}

void	ft_remove_from_queue(t_queue *q)
{
	t_node	*tmp;

	if (q->front == q->rear)
	{
		free(q->front);
		q->front = NULL;
		q->rear = NULL;
	}
	else
	{
		tmp = q->front;
		q->front = q->front->next;
		q->count--;
		free(tmp);
		tmp = NULL;
	}
}
