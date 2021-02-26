/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:39:08 by pgueugno          #+#    #+#             */
/*   Updated: 2021/02/26 15:42:41 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcub.h"

char	*ft_read_it(char **tmp, int fd)
{
	int		r;
	char	*buf;
	char	*p;

	r = 1;
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	while (!(ft_strchr(*tmp, '\n')) && r > 0)
	{
		(r = read(fd, buf, BUFFER_SIZE));
		if (r)
		{
			buf[r] = '\0';
			p = *tmp;
			*tmp = ft_strjoin(*tmp, (char *)buf);
			free(p);
		}
	}
	free(buf);
	buf = NULL;
	return (*tmp);
}

char	*ft_strncpy(char *dst, char *src, int n)
{
	int i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int		ft_what_is_read(char **tmp, char **line)
{
	char	*p;
	char	*mem;

	p = NULL;
	if (ft_strchr(*tmp, '\n') == 0)
	{
		*line = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
		return (0);
	}
	else if (ft_strchr(*tmp, '\n') != 0)
	{
		mem = ft_strchr(*tmp, '\n');
		if (!(*line = malloc(sizeof(char) * (mem - *tmp + 1))))
			return (-1);
		*line = ft_strncpy(*line, *tmp, (mem - *tmp));
		p = *tmp;
		*tmp = ft_strdup(mem + 1);
		free(p);
		return (1);
	}
	return (0);
}

int		ft_gnl(int fd, char **line, t_data *data)
{
	static char *tmp = NULL;

	data->p.gnlptr = &tmp;
	if (line == NULL || fd < 0 || read(fd, tmp, 0) < 0 ||
		BUFFER_SIZE < 0)
		return (-1);
	if (!tmp)
		if (!(tmp = ft_strdup("")))
			return (-1);
	if (BUFFER_SIZE == 0)
	{
		*line = NULL;
		return (0);
	}
	tmp = ft_read_it(&tmp, fd);
	return (ft_what_is_read(&tmp, line));
}
