/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:16:09 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/03 11:35:03 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

int	ft_mouse_exit(t_data *data)
{
	ft_exit("Game has ended properly using window cross button", data);
	return (0);
}

int	ft_key_press(int key, t_data *data)
{
	if (key == FORWARD)
		data->m.forward = 1;
	if (key == BACKWARD)
		data->m.backward = 1;
	if (key == RIGHT)
		data->m.straferight = 1;
	if (key == LEFT)
		data->m.strafeleft = 1;
	if (key == ROTATERIGHT)
		data->m.rotateright = 1;
	if (key == ROTATELEFT)
		data->m.rotateleft = 1;
	if (key == ESC)
		ft_exit("Game has ended properly using ESC keypad", data);
	return (1);
}

int	ft_key_release(int key, t_data *data)
{
	if (key == FORWARD)
		data->m.forward = 0;
	if (key == BACKWARD)
		data->m.backward = 0;
	if (key == RIGHT)
		data->m.straferight = 0;
	if (key == LEFT)
		data->m.strafeleft = 0;
	if (key == ROTATERIGHT)
		data->m.rotateright = 0;
	if (key == ROTATELEFT)
		data->m.rotateleft = 0;
	return (1);
}
