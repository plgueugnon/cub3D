/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:56:04 by pgueugno          #+#    #+#             */
/*   Updated: 2020/11/11 20:55:37 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*c_dst;
	unsigned const char	*c_src;
	size_t				i;

	c_dst = dst;
	c_src = src;
	i = 0;
	if (c_dst == NULL && c_src == NULL)
		return (NULL);
	if (c_dst > c_src)
		while (i < len)
		{
			c_dst[len - 1] = c_src[len - 1];
			len--;
		}
	else
		while (i < len)
		{
			*c_dst = *c_src;
			c_dst++;
			c_src++;
			i++;
		}
	return (dst);
}
