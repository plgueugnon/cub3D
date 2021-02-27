/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:00:16 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/25 22:54:25 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

static void	ft_tabstrcpy(t_data *data, int i, char *content)
{
	int j;

	j = 0;
	while (content[j])
	{
		data->map[i][j + 1] = content[j];
		j++;
	}
//	while (content[i])
//	{
//		*map[i + 1] = content[i];
//		i++;
//	}
//	return (j);
}

static void	ft_add_border_to_map(t_list *ptr, int j, int i, t_data *data)
{
	int r;

	r = ft_strlen(ptr->content);
	data->map[i][0] = '#';
	if (i == 0 || i > data->p.maph)
		data->map[i][j] = '#';
	else if (j > r)
		data->map[i][j] = '#';
	else if (i >= 1 && i <= data->p.maph && j >= 1 && j <= r)
		ft_tabstrcpy(data, i, ptr->content);
}

static void	ft_malloc_rows(t_data *data)
{
//	printf("h=%d\n", data->p.maph + 2);
	data->map = malloc(sizeof(char *) * (data->p.maph + 2));
	if (data->map == NULL)
		ft_map_error("Error\nMalloc of **map failed", data);
}

static void ft_malloc_col(t_data *data, int i)
{
//	printf("w=%d\n", data->p.mapw + 2);
	data->map[i] = malloc(sizeof(char) * (data->p.mapw + 2));
	if (data->map[i] == NULL)
			ft_map_error("Error\nMalloc of *map failed", data);
}

void	ft_transform_to_tab(t_list *list, t_data *data)
{
	int i;
	int j;
	t_list *ptr;

	i = 0;
	j = 0;
	ptr = list;
	ft_malloc_rows(data);
	while (i < (data->p.maph + 2))
	{
		ft_malloc_col(data, i);
		j = 0;
		while (j < data->p.mapw + 2)
		{
			ft_add_border_to_map(ptr, j, i, data);
			j++;
		}
//		data->map[i][j] = 0;
		if (ptr->next != NULL && i > 0)
			ptr = ptr->next;
		i++;
	}
	free(data->map[i]); // WTF?
	data->map[i] = NULL;
//	data->map[i - 1] = 0;
	ft_lstclear(data->p.lstptr, &ft_del);
	data->p.lstptr = NULL;
}
