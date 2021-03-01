/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 22:31:35 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/01 12:24:09 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void			ft_cleanup_queue(t_queue *q)
{
	while (!ft_queue_is_empty(q))
		ft_remove_from_queue(q);
	if (q)
		free(q);
	q = NULL;
}

static t_queue	*ft_malloc_queue(t_data *data, t_queue *q)
{
	q = malloc(sizeof(t_queue));
	if (!q)
	{
		ft_cleanup_queue(q);
		ft_map_error("Error\nMalloc of queue list failed", data);
	}
	return (q);
}

static void		ft_check_if_map_is_closed(t_data *data, t_queue *q,
				int y, int x)
{
	if (data->map[y - 1][x] == ' ' || data->map[y - 1][x] == '#'
		|| data->map[y + 1][x] == ' ' || data->map[y + 1][x] == '#'
		|| data->map[y - 1][x] == ' ' || data->map[y - 1][x] == '#'
		|| data->map[y][x - 1] == ' ' || data->map[y][x - 1] == '#'
		|| data->map[y][x + 1] == ' ' || data->map[y][x + 1] == '#')
	{
		ft_cleanup_queue(q);
		ft_map_error("Error\nMap is not properly closed", data);
	}
}

static void		ft_check_next_case(t_data *data, t_queue *q, int y, int x)
{
	if (data->map[y - 1][x] == data->p.iszero[0])
	{
		data->map[y - 1][x] = data->p.iszero[1];
		ft_add_to_queue(q, y - 1, x, data);
	}
	if (data->map[y + 1][x] == data->p.iszero[0])
	{
		data->map[y + 1][x] = data->p.iszero[1];
		ft_add_to_queue(q, y + 1, x, data);
	}
	if (data->map[y][x - 1] == data->p.iszero[0])
	{
		data->map[y][x - 1] = data->p.iszero[1];
		ft_add_to_queue(q, y, x - 1, data);
	}
	if (data->map[y][x + 1] == data->p.iszero[0])
	{
		data->map[y][x + 1] = data->p.iszero[1];
		ft_add_to_queue(q, y, x + 1, data);
	}
}

void			ft_floodfill(t_data *data, int oval, int rval)
{
	t_queue	*q;
	int		x;
	int		y;

	q = NULL;
	x = data->mapx + 1;
	y = data->mapy;
	data->p.iszero[0] = oval;
	data->p.iszero[1] = rval;
	q = ft_malloc_queue(data, q);
	ft_initialise_queue(q);
	ft_add_to_queue(q, y, x, data);
	data->map[y][x] = rval;
	while (!ft_queue_is_empty(q))
	{
		x = q->front->x;
		y = q->front->y;
		ft_check_if_map_is_closed(data, q, y, x);
		ft_check_next_case(data, q, y, x);
		ft_remove_from_queue(q);
	}
	ft_cleanup_queue(q);
}
