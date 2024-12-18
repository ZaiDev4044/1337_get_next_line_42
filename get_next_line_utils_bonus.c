/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zben-oma <zben-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:03:43 by zben-oma          #+#    #+#             */
/*   Updated: 2024/11/28 17:04:24 by zben-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	if (!dst || !src)
		return (0);
	slen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (slen);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ds;
	size_t	ss;
	size_t	dst2;

	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	ss = ft_strlen(src);
	ds = ft_strlen(dst);
	if (dstsize <= ds)
		return (dstsize + ss);
	i = 0;
	dst2 = ds;
	while (src[i] != '\0' && (dst2 + i + 1) < dstsize)
	{
		dst[dst2 + i] = src[i];
		i++;
	}
	dst[dst2 + i] = '\0';
	return (ss + ds);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!p)
		return (NULL);
	ft_strlcpy(p, (char *)s1, (s1_len + s2_len + 1));
	ft_strlcat(p, (char *)s2, (s1_len + s2_len + 1));
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while ((char)s1[i] != '\0')
	{
		s2[i] = (char)s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
