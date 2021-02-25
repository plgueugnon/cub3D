/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:44:27 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/24 20:54:23 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void ft_init_parsing_values(t_data *data)
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
}
