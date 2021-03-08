/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:44:27 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/04 12:12:34 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void		ft_init_parsing_values(t_data *data)
{
	data->p.res[0] = -1;
	data->p.res[1] = -1;
	data->p.no_tex_path = NULL;
	data->p.so_tex_path = NULL;
	data->p.we_tex_path = NULL;
	data->p.ea_tex_path = NULL;
	data->p.sp_tex_path = NULL;
	data->p.floor = -1;
	data->p.ceiling = -1;
	data->p.step = 0;
	data->p.mapw = 0;
	data->p.maph = 0;
	data->map = NULL;
	data->mapx = -1;
	data->mapy = -1;
	data->s.nb = 0;
	data->spos = NULL;
	data->s.zbuffer = NULL;
	data->s.order = NULL;
	data->s.dist = NULL;
}

static void	ft_get_camera_plan(char c, t_data *data)
{
	if (c == 'N')
	{
		data->planx = 0.66;
		data->plany = 0;
	}
	if (c == 'S')
	{
		data->planx = -0.66;
		data->plany = 0;
	}
	if (c == 'E')
	{
		data->planx = 0;
		data->plany = -0.66;
	}
	if (c == 'W')
	{
		data->planx = 0;
		data->plany = 0.66;
	}
}

void		ft_get_player_dir(char c, t_data *data)
{
	if (c == 'N')
	{
		data->dirx = 0;
		data->diry = 1;
	}
	if (c == 'S')
	{
		data->dirx = 0;
		data->diry = -1;
	}
	if (c == 'E')
	{
		data->dirx = 1;
		data->diry = 0;
	}
	if (c == 'W')
	{
		data->dirx = -1;
		data->diry = 0;
	}
	ft_get_camera_plan(c, data);
}

void		ft_init_raycast_pointers(t_data *data)
{
	data->i.img = NULL;
	data->i.img_2 = NULL;
	data->i.addr = NULL;
	data->i.addr_2 = NULL;
	data->i.mlx = NULL;
	data->i.mlx_win = NULL;
	data->texdata[0].img = NULL;
	data->texdata[0].addr = NULL;
	data->texdata[1].img = NULL;
	data->texdata[1].addr = NULL;
	data->texdata[2].img = NULL;
	data->texdata[2].addr = NULL;
	data->texdata[3].img = NULL;
	data->texdata[3].addr = NULL;
	data->texdata[4].img = NULL;
	data->texdata[4].img = NULL;
}

void		ft_init_raycast_values(t_data *data)
{
	data->posx = data->mapx + 1;
	data->posy = data->mapy;
	data->movspeed = 0.1;
	data->rotspeed = 0.1;
	data->w = data->p.res[0];
	data->h = data->p.res[1];
	data->m.forward = 0;
	data->m.backward = 0;
	data->m.straferight = 0;
	data->m.strafeleft = 0;
	data->m.rotateright = 0;
	data->m.rotateleft = 0;
	ft_init_raycast_pointers(data);
}
