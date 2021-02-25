/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:02:55 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/25 13:07:57 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

int ft_check_charset(char src, char *charset)
{
	while (*charset)
	{
		if (src == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	ft_check_spaces_in_map(char *line)
{
	if (*line == '\0')
		return (0);
	while (*line)
	{
		if (ft_check_charset(*line, "012NSWE") == 1)
			return (1);
		line++;
	}
	return (0);
}

void	ft_parse_map(t_data *data, char *line, int fd)
{
	int i;

	i = 0;
	++(data->p.maph);
	while (line[i])
	{
		if (!ft_check_charset(line[i], "012 NSWE"))
			ft_parsing_error("Error\nWrong input in map lines", data, fd);
		if ((line[i] == 'N' || line[i] == 'W' || line[i] == 'S' ||
			line[i] == 'E') && (data->mapx == -1 && data->mapy == -1))
		{
			data->mapx = i;
			data->mapy = data->p.maph;
		}
		else if ((line[i] == 'N' || line[i] == 'W' || line[i] == 'S' ||
			line[i] == 'E') && (data->mapx != -1 && data->mapy != -1))
			ft_parsing_error("Error\nPlayer position already given", data, fd);
		i++;
	}
	if ((size_t)data->p.mapw < ft_strlen(line))
		data->p.mapw = ft_strlen(line);
}

void	ft_free_line_before_next(t_data *data)
{
	if (!data->p.lptr)
		return ;
	else
	{
		free(*data->p.lptr);
		*data->p.lptr = NULL;
		data->p.lptr = NULL;
	}
}

void	ft_link_line(t_list **list, void *content, t_data *data, int fd)
{
	t_list *new;
	t_list *end;

	new = malloc(sizeof(t_list));
	if (!new)
		ft_parsing_error("Error\nFailed malloc of linked list", data, fd);
	if (new)
	{
		new->content = ft_strdup(content);
		new->next = NULL;
	}
	end = *list;

	if (!*list)
	{
		*list = new;
		return ;
	}
	else
	{
		while (end->next)
			end = end->next;
	}
	end->next = new;
}
