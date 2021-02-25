/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:13:40 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/24 21:02:51 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void	ft_del(void *content)
{
	free(content);
}

void	ft_parsing_error(char *err, t_data *data, int fd)
{
	if (data->p.no_tex_path)
		free(data->p.no_tex_path);
	if (data->p.so_tex_path)
		free(data->p.so_tex_path);
	if (data->p.we_tex_path)
		free(data->p.we_tex_path);
	if (data->p.ea_tex_path)
		free(data->p.ea_tex_path);
	if (data->p.sp_tex_path)
		free(data->p.sp_tex_path);
	if (data->p.lstptr)
		ft_lstclear(data->p.lstptr, &ft_del);
	*data->p.lstptr = NULL;
	data->p.lstptr = NULL;
	ft_free_line_before_next(data);
	ft_init_parsing_values(data);
	close(fd);
	printf("%s\n", err);
	exit(0);
}
