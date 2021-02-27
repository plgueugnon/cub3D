/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:13:40 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/26 15:53:39 by pgueugno         ###   ########.fr       */
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
	ft_clear_still_reachable(data);
	ft_init_parsing_values(data);
	close(fd);
	printf("%s\n", err);
	exit(0);
}

void	ft_free_map(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i])
	{
//		printf("B%s\n", data->map[i]);
		free(data->map[i]);
		data->map[i] = NULL;
//		printf("A%s\n", data->map[i]);
//		if (data->map[i + 1] == 0)
//		{
//			printf("%d\n", i + 1);
//			free(data->map[i + 1]);
//			data->map[i + 1] = NULL;
//		}
		i++;
	}
//	printf("last%s\n", data->map[i]);
//	printf("count%d\n", i);
//	printf("L1%s\n", data->map[0]);
//	free(data->map[0]);
//	printf("L2%s\n", data->map[0]);
	free(data->map);
	data->map = NULL;
}

void	ft_map_error(char *err, t_data *data)
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
	{
		ft_lstclear(data->p.lstptr, &ft_del);
		*data->p.lstptr = NULL;
		data->p.lstptr = NULL;
	}
	ft_clear_still_reachable(data);
	if (data->map)
		ft_free_map(data);
	printf("%s\n", err);
	exit(0);
}
