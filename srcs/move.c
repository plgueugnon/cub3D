/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:39:15 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/04 12:20:59 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void	ft_forward_or_backward(t_data *data)
{
	if (data->m.forward)
	{
		if (data->map[(int)(data->posy + (data->diry * data->movspeed))]
			[(int)data->posx] == 48)
			data->posy += data->diry * data->movspeed;
		if (data->map[(int)(data->posy)][(int)(data->posx + data->dirx
			* data->movspeed)] == 48)
			data->posx += data->dirx * data->movspeed;
	}
	if (data->m.backward)
	{
		if (data->map[(int)(data->posy - data->diry * data->movspeed)]
			[(int)(data->posx)] == 48)
			data->posy -= data->diry * data->movspeed;
		if (data->map[(int)(data->posy)][(int)(data->posx - data->dirx
			* data->movspeed)] == 48)
			data->posx -= data->dirx * data->movspeed;
	}
}

void	ft_strafe_left_or_right(t_data *data)
{
	if (data->m.straferight)
	{
		if (data->map[(int)(data->posy + data->plany * data->movspeed)]
			[(int)(data->posx)] == 48)
			data->posy += data->plany * data->movspeed;
		if (data->map[(int)(data->posy)][(int)(data->posx + data->planx
			* data->movspeed)] == 48)
			data->posx += data->planx * data->movspeed;
	}
	if (data->m.strafeleft)
	{
		if (data->map[(int)(data->posy - data->plany * data->movspeed)]
			[(int)(data->posx)] == 48)
			data->posy -= data->plany * data->movspeed;
		if (data->map[(int)(data->posy)][(int)(data->posx - data->planx
			* data->movspeed)] == 48)
			data->posx -= data->planx * data->movspeed;
	}
}

void	ft_rotate_right(t_data *data)
{
	double	olddirx;
	double	oldplanx;

	olddirx = 0;
	oldplanx = 0;
	if (data->m.rotateright)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(-data->rotspeed) - data->diry
			* sin(-data->rotspeed);
		data->diry = olddirx * sin(-data->rotspeed) + data->diry
			* cos(-data->rotspeed);
		oldplanx = data->planx;
		data->planx = data->planx * cos(-data->rotspeed) - data->plany
			* sin(-data->rotspeed);
		data->plany = oldplanx * sin(-data->rotspeed) + data->plany
			* cos(-data->rotspeed);
	}
}

void	ft_rotate_left(t_data *data)
{
	double	olddirx;
	double	oldplanx;

	olddirx = 0;
	oldplanx = 0;
	if (data->m.rotateleft)
	{
		olddirx = data->dirx;
		data->dirx = data->dirx * cos(data->rotspeed) - data->diry
			* sin(data->rotspeed);
		data->diry = olddirx * sin(data->rotspeed) + data->diry
			* cos(data->rotspeed);
		oldplanx = data->planx;
		data->planx = data->planx * cos(data->rotspeed) - data->plany
			* sin(data->rotspeed);
		data->plany = oldplanx * sin(data->rotspeed) + data->plany
			* cos(data->rotspeed);
	}
}
