/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:47:23 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/04 12:24:45 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

static void	ft_free_sprites_values(t_data *data)
{
	if (data->s.zbuffer)
		free(data->s.zbuffer);
	if (data->s.order)
		free(data->s.order);
	if (data->s.dist)
		free(data->s.dist);
	if (data->spos)
		free(data->spos);
}

void		ft_exit(char *err, t_data *data)
{
	ft_free_tex_path(data);
	ft_free_sprites_values(data);
	if (data->texdata[0].img)
		mlx_destroy_image(data->i.mlx, data->texdata[0].img);
	if (data->texdata[1].img)
		mlx_destroy_image(data->i.mlx, data->texdata[1].img);
	if (data->texdata[2].img)
		mlx_destroy_image(data->i.mlx, data->texdata[2].img);
	if (data->texdata[3].img)
		mlx_destroy_image(data->i.mlx, data->texdata[3].img);
	if (data->texdata[4].img)
		mlx_destroy_image(data->i.mlx, data->texdata[4].img);
	if (data->i.mlx)
		mlx_destroy_window(data->i.mlx, data->i.mlx_win);
	ft_init_raycast_pointers(data);
	printf("%s\n", err);
	exit(0);
}
