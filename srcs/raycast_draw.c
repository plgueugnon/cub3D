/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:41:40 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/04 12:10:24 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void	ft_init_texdir(t_data *data)
{
	if (data->side == 0 && data->raydirx < 0)
		data->t.texdir = 3;
	if (data->side == 0 && data->raydirx >= 0)
		data->t.texdir = 2;
	if (data->side == 1 && data->raydiry < 0)
		data->t.texdir = 1;
	if (data->side == 1 && data->raydiry >= 0)
		data->t.texdir = 0;
}

void	ft_texel_compute(t_data *data)
{
	if (data->side == 1)
		data->t.wallx = data->posx + data->perpwalldist * data->raydirx;
	else
		data->t.wallx = data->posy + data->perpwalldist * data->raydiry;
	data->t.wallx -= floor(data->t.wallx);
	data->t.texx = ft_abs((int)(data->t.wallx
			* (double)data->texdata[data->t.texdir].width));
	if (data->side == 0 && data->raydirx > 0)
		data->t.texx = data->texdata[data->t.texdir].width - data->t.texx - 1;
	if (data->side == 1 && data->raydiry < 0)
		data->t.texx = data->texdata[data->t.texdir].width - data->t.texx - 1;
}

void	ft_custom_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->i.addr + (y * data->i.line_size + x * (data->i.bpp / 8));
	*(int *)dst = color;
}

void	ft_draw_ceiling_and_floor(t_data *data)
{
	if (data->drawend < 0)
		data->drawend = data->h;
	data->y = data->drawend;
	while (data->y < data->h)
	{
		ft_custom_mlx_pixel_put(data, data->x, data->y, data->p.floor);
		ft_custom_mlx_pixel_put(data, data->x, (data->h - data->y - 1),
		data->p.ceiling);
		data->y++;
	}
}

void	ft_draw_col(t_data *data)
{
	int	color;
	int	*addr_int;

	data->lineh = (int)(data->h / data->perpwalldist);
	data->drawstart = -data->lineh / 2 + data->h / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	data->drawend = data->lineh / 2 + data->h / 2;
	if (data->drawend >= data->h)
		data->drawend = data->h - 1;
	data->y = data->drawstart;
	ft_init_texdir(data);
	ft_texel_compute(data);
	addr_int = (int *)data->texdata[data->t.texdir].addr;
	while (data->y < data->drawend)
	{
		data->t.texy = ft_abs((data->y * 2 - data->h + data->lineh)
			* (data->texdata[data->t.texdir].height / 2) / data->lineh);
		color = addr_int[data->t.texy * data->texdata[data->t.texdir].line_size
			/ (data->texdata[data->t.texdir].bpp / 8) + data->t.texx];
		ft_custom_mlx_pixel_put(data, data->x, data->y, color);
		data->y++;
	}
	ft_draw_ceiling_and_floor(data);
}
