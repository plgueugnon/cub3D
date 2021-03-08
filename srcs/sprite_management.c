/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:55:41 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/04 12:02:17 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void	ft_get_sprites_pos(t_data *data)
{
	int	i;
	int	j;
	int	r;

	i = 0;
	r = 0;
	data->spos = malloc(sizeof(t_sprite_pos) * data->s.nb);
	if (!data->spos)
		ft_exit("Error\nMalloc of sprite position tab failed", data);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 50)
			{
				data->spos[r].y = i + 0.5;
				data->spos[r].x = j + 0.5;
				r++;
				data->map[i][j] = 48;
			}
			j++;
		}
		i++;
	}
}

void	ft_init_sprites(t_data *data)
{
	data->s.zbuffer = malloc(sizeof(double) * data->w);
	if (!data->s.zbuffer)
		ft_exit("Error\nMalloc of zbuffer tab failed", data);
	data->s.order = malloc(sizeof(int) * data->s.nb);
	if (!data->s.order)
		ft_exit("Error\nMalloc of sprite order tab failed", data);
	data->s.dist = malloc(sizeof(double) * data->s.nb);
	if (!data->s.dist)
		ft_exit("Error\nMalloc of sprite dist tab failed", data);
}

void	ft_sort_sprites(t_data *data)
{
	int			i;
	int			j;
	double		swap;

	i = 0;
	while (i < data->s.nb)
	{
		j = 0;
		while (j < data->s.nb)
		{
			if (data->s.dist[i] > data->s.dist[j])
			{
				swap = data->s.dist[i];
				data->s.dist[i] = data->s.dist[j];
				data->s.dist[j] = swap;
				swap = data->s.order[i];
				data->s.order[i] = data->s.order[j];
				data->s.order[j] = (int)swap;
			}
			j++;
		}
		i++;
	}
}
