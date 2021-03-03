/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:31:46 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/02 11:45:35 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

static void	ft_get_tex_address(t_data *data)
{
	data->texdata[0].addr = mlx_get_data_addr(data->texdata[0].img,
	&data->texdata[0].bpp, &data->texdata[0].line_size,
	&data->texdata[0].endian);
	data->texdata[1].addr = mlx_get_data_addr(data->texdata[1].img,
	&data->texdata[1].bpp, &data->texdata[1].line_size,
	&data->texdata[1].endian);
	data->texdata[2].addr = mlx_get_data_addr(data->texdata[2].img,
	&data->texdata[2].bpp, &data->texdata[2].line_size,
	&data->texdata[2].endian);
	data->texdata[3].addr = mlx_get_data_addr(data->texdata[3].img,
	&data->texdata[3].bpp, &data->texdata[3].line_size,
	&data->texdata[3].endian);
	data->texdata[4].addr = mlx_get_data_addr(data->texdata[4].img,
	&data->texdata[4].bpp, &data->texdata[4].line_size,
	&data->texdata[4].endian);
	if (!data->texdata[0].img || !data->texdata[1].img || !data->texdata[2].img
		|| !data->texdata[3].img || !data->texdata[4].img)
		ft_exit("Error\nFailure to import texture", data);
}

void	ft_init_textures(t_data *data)
{
	data->texdata[0].img = mlx_xpm_file_to_image(data->i.mlx,
	data->p.no_tex_path, &(data->texdata[0].width), &(data->texdata[0].height));
	data->texdata[1].img = mlx_xpm_file_to_image(data->i.mlx,
	data->p.so_tex_path, &(data->texdata[1].width), &(data->texdata[1].height));
	data->texdata[2].img = mlx_xpm_file_to_image(data->i.mlx,
	data->p.ea_tex_path, &(data->texdata[2].width), &(data->texdata[2].height));
	data->texdata[3].img = mlx_xpm_file_to_image(data->i.mlx,
	data->p.we_tex_path, &(data->texdata[3].width), &(data->texdata[3].height));
	data->texdata[4].img = mlx_xpm_file_to_image(data->i.mlx,
	data->p.sp_tex_path, &(data->texdata[4].width), &(data->texdata[4].height));
	ft_get_tex_address(data);
}
