/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:39:08 by pgueugno          #+#    #+#             */
/*   Updated: 2021/03/01 12:17:43 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

void			ft_clear_still_reachable(t_data *data)
{
	if (data->p.gnlptr)
	{
		free(*data->p.gnlptr);
		*data->p.gnlptr = NULL;
		data->p.gnlptr = NULL;
	}
}

static int		ft_malloc(char **line, int n)
{
	*line = malloc(sizeof(char) * (n + 1));
	if (!(*line))
		return (0);
	return (1);
}

static int		ft_n_char_read(char **tmp, char **line, t_data *data)
{
	char	*p;
	char	*mem;

	p = NULL;
	if (ft_strchr(*tmp, '\n') == 0)
	{
		*line = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
		data->p.gnlptr = &(*line);
		return (0);
	}
	else if (ft_strchr(*tmp, '\n') != 0)
	{
		mem = ft_strchr(*tmp, '\n');
		if (!ft_malloc(&(*line), (mem - *tmp)))
			return (-1);
		*line = ft_strncpy(*line, *tmp, (mem - *tmp));
		p = *tmp;
		*tmp = ft_strdup(mem + 1);
		data->p.gnlptr = &(*tmp);
		free(p);
		return (1);
	}
	return (0);
}

int				ft_gnl(int fd, char **line, t_data *data)
{
	static char	*tmp = NULL;

	if (line == NULL || fd < 0 || read(fd, tmp, 0) < 0 || BUFFER_SIZE < 0)
		return (-1);
	if (!tmp)
		tmp = ft_strdup("");
	if (!tmp)
		return (-1);
	if (BUFFER_SIZE == 0)
	{
		*line = NULL;
		return (0);
	}
	tmp = ft_read_it(&tmp, fd);
	return (ft_n_char_read(&tmp, line, data));
}
