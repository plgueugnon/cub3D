/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 09:03:12 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/06 10:14:01 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void		ft_buffer_img(t_data *data)
{
	void	*ptr;

	ptr = NULL;
	ptr = data->i.img_2;
	data->i.img_2 = data->i.img;
	data->i.img = ptr;
	ptr = data->i.addr_2;
	data->i.addr_2 = data->i.addr;
	data->i.addr = ptr;
}

int			ft_loop(t_data *data)
{
	data->x = 0;
	while (data->x < data->w)
	{
		ft_init_ray_starting_point(data);
		ft_sidedist_compute(data);
		ft_dda_compute(data);
		ft_draw_col(data);
		data->s.zbuffer[data->x] = data->perpwalldist;
		data->x++;
	}
	ft_draw_sprite(data);
	if (data->save)
		ft_save(data);
	mlx_put_image_to_window(data->i.mlx, data->i.mlx_win, data->i.img, 0, 0);
	ft_forward_or_backward(data);
	ft_strafe_left_or_right(data);
	ft_rotate_right(data);
	ft_rotate_left(data);
	ft_buffer_img(data);
	return (1);
}

static void	ft_resize_window(t_data *data)
{
	int screenx;
	int screeny;

	mlx_get_screen_size(data->i.mlx, &screenx, &screeny);
	if (data->w > screenx)
		data->w = screenx;
	if (data->h > screeny)
		data->h = screeny;
}

void		ft_start_raycasting(t_data *data)
{
	ft_floodfill(data, 55, 48);
	ft_init_raycast_values(data);
	data->i.mlx = mlx_init();
	if (!data->save)
	{
		ft_resize_window(data);
		data->i.mlx_win = mlx_new_window(data->i.mlx, data->w, data->h,
		"cub3D");
		mlx_hook(data->i.mlx_win, 2, 1L << 0, ft_key_press, data);
		mlx_hook(data->i.mlx_win, 3, 1L << 1, ft_key_release, data);
		mlx_hook(data->i.mlx_win, CROSSEXIT, 1L << 17, ft_mouse_exit, data);
	}
	ft_init_textures(data);
	ft_init_sprites(data);
	data->i.img = mlx_new_image(data->i.mlx, data->w, data->h);
	data->i.addr = mlx_get_data_addr(data->i.img, &data->i.bpp,
			&data->i.line_size, &data->i.endian);
	data->i.img_2 = mlx_new_image(data->i.mlx, data->w, data->h);
	data->i.addr_2 = mlx_get_data_addr(data->i.img_2, &data->i.bpp,
			&data->i.line_size, &data->i.endian);
	if (data->save)
		ft_loop(data);
	mlx_loop_hook(data->i.mlx, ft_loop, data);
	mlx_loop(data->i.mlx);
}
