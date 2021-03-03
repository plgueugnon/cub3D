/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_compute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:22:32 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/03 12:38:40 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void	ft_init_ray_starting_point(t_data *data)
{
	data->camerax = 2 * data->x / (double)(data->w) - 1;
	data->rayposx = data->posx;
	data->rayposy = data->posy;
	data->raydirx = data->dirx + data->planx * data->camerax;
	data->raydiry = data->diry + data->plany * data->camerax;
	data->mapx = (int)data->rayposx;
	data->mapy = (int)data->rayposy;
	data->deltadistx = sqrt(1 + (data->raydiry * data->raydiry)
		/ (data->raydirx * data->raydirx));
	data->deltadisty = sqrt(1 + (data->raydirx * data->raydirx)
		/ (data->raydiry * data->raydiry));
	data->hit = 0;
}

void	ft_sidedist_compute(t_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->rayposx - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->rayposx) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->rayposy - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->rayposy) * data->deltadisty;
	}
}

void	ft_DDA_compute(t_data *data)
{
	while (data->hit == 0)
	{
		if (data->sidedistx < data->sidedisty)
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			data->side = 0;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			data->side = 1;
		}
		if (data->map[data->mapy][data->mapx] != 48)
			data->hit = 1;
	}
	if (data->side == 0)
		data->perpwalldist = fabs((data->mapx - data->rayposx
			+ (1 - data->stepx) / 2) / data->raydirx);
	else
		data->perpwalldist = fabs((data->mapy - data->rayposy
			+ (1 - data->stepy) / 2) / data->raydiry);
}
