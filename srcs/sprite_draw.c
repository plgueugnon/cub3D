/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:11:18 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/04 12:09:27 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

static void	ft_compute_sprite_size_and_pos(t_data *data, int i)
{
	data->s.spritex = data->spos[data->s.order[i]].x - data->posx;
	data->s.spritey = data->spos[data->s.order[i]].y - data->posy;
	data->s.invdet = 1.0 / (data->planx * data->diry - data->dirx
			* data->plany);
	data->s.transformx = data->s.invdet * (data->diry * data->s.spritex
			- data->dirx * data->s.spritey);
	data->s.transformy = data->s.invdet * (data->planx * data->s.spritey
			- data->plany * data->s.spritex);
	data->s.screenx = (int)((data->w / 2) * (1 + data->s.transformx
				/ data->s.transformy));
	data->s.h = abs((int)(data->h / data->s.transformy));
	data->s.drawstarty = data->h / 2 - data->s.h / 2;
	if (data->s.drawstarty < 0)
		data->s.drawstarty = 0;
	data->s.drawendy = data->s.h / 2 + data->h / 2;
	if (data->s.drawendy >= data->h)
		data->s.drawendy = data->h - 1;
	data->s.w = abs((int)(data->h / data->s.transformy));
	data->s.drawstartx = data->s.screenx - data->s.w / 2;
	if (data->s.drawstartx < 0)
		data->s.drawstartx = 0;
	data->s.drawendx = data->s.w / 2 + data->s.screenx;
	if (data->s.drawendx >= data->w)
		data->s.drawendx = data->w - 1;
}

static void	ft_print_pixels(t_data *data, int texx, int x)
{
	int	*addr_int;
	int	color;
	int	y;
	int	d;
	int	texy;

	addr_int = (int *)data->texdata[4].addr;
	y = data->s.drawstarty;
	while (y < data->s.drawendy)
	{
		d = (y) * 256 - data->h * 128 + data->s.h * 128;
		texy = ((d * data->texdata[4].height) / data->s.h) / 256;
		color = addr_int[texy * data->texdata[4].line_size
			/ (data->texdata[4].bpp / 8) + texx];
		if ((color & 0x00FFFFFF) != 0)
			ft_custom_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void		ft_sprite_compute(t_data *data)
{
	int	i;
	int	x;
	int	texx;

	i = 0;
	while (i < data->s.nb)
	{
		ft_compute_sprite_size_and_pos(data, i);
		x = data->s.drawstartx;
		while (x < data->s.drawendx)
		{
			texx = (int)((256 * (x - (-data->s.w / 2 + data->s.screenx))
						* data->texdata[4].width / data->s.w)) / 256;
			if (data->s.transformy > 0 && x > 0 && x < data->w
				&& data->s.transformy < data->s.zbuffer[x])
				ft_print_pixels(data, texx, x);
			x++;
		}
		i++;
	}
}

void		ft_draw_sprite(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->s.nb)
	{
		data->s.order[i] = i;
		data->s.dist[i] = ((data->posx - data->spos[i].x) * (data->posx
					- data->spos[i].x) + (data->posy - data->spos[i].y)
				* (data->posy - data->spos[i].y));
		i++;
	}
	ft_sort_sprites(data);
	ft_sprite_compute(data);
}
