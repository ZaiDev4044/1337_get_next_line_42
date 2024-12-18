/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zben-oma <zben-oma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:23:14 by zben-oma          #+#    #+#             */
/*   Updated: 2024/11/28 16:11:32 by zben-oma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	if (start >= l)
		return (ft_strdup(""));
	if (len > l - start)
		len = l - start;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*mini_crop(char *full_buf, char **prev_line)
{
	int		i;
	char	*tmp;
	char	*remaining;

	if (!full_buf || !prev_line)
		return (NULL);
	i = 0;
	while (full_buf[i])
	{
		if (full_buf[i] == '\n')
		{
			tmp = ft_substr(full_buf, 0, i + 1);
			if (!tmp)
				return (free(full_buf), NULL);
			remaining = ft_strdup(full_buf + i + 1);
			free(full_buf);
			if (!remaining)
				return (free(tmp), NULL);
			*prev_line = remaining;
			return (tmp);
		}
		i++;
	}
	*prev_line = NULL;
	return (full_buf);
}

char	*file_reader(int fd, char *buf, char *full_buf)
{
	int		bytes_read;
	char	*tmp;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		if (!full_buf)
			full_buf = ft_strdup(buf);
		else
		{
			tmp = full_buf;
			full_buf = ft_strjoin(full_buf, buf);
			free(tmp);
		}
		if (!full_buf)
			return (NULL);
		if (ft_strchr(buf, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (free(full_buf), NULL);
	return (full_buf);
}

char	*get_next_line(int fd)
{
	static char	*prev_line;
	char		*buf;
	char		*full_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	full_buf = NULL;
	if (prev_line)
	{
		full_buf = ft_strdup(prev_line);
		free(prev_line);
		prev_line = NULL;
	}
	full_buf = file_reader(fd, buf, full_buf);
	free(buf);
	if (!full_buf)
		return (NULL);
	line = mini_crop(full_buf, &prev_line);
	if (line && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
