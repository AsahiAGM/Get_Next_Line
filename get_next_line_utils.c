/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                             :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamaguc <ahamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:30:20 by ahamaguc          #+#    #+#             */
/*   Updated: 2025/10/24 17:04:11 by ahamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
* Read from file until a newline or EOF is found,
* and append the read content to the given pointer.
* @param fd         file id
* @param *remainder buffer of reading char
* @return new remainder
*/
char	*read_and_store(int fd, char *remainder)
{
	char	buf[BUFFER_SIZE + 1];
	int		bytes;
	size_t	j;

	if (!remainder)
	{
		remainder = malloc(1);
		if (!remainder)
			return (NULL);
		remainder[0] = '\0';
	}
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(remainder), NULL);
		buf[bytes] = '\0';
		remainder = ft_strjoin(remainder, buf);
		j = 0;
		while (j < ft_strlen(buf))
			if (buf[j++] == '\n')
				return (remainder);
	}
	return (remainder);
}

/*
* Read from the buffer until a newline or EOF is found,
* then dump as much as you read.
* @param *remainder buffer of reading char
* @return new line
*/
char	*extract_line(char *remainder)
{
	size_t	i;
	size_t	ri;
	char	*line;

	i = 0;
	ri = 0;
	if (!remainder || !remainder[0])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	while (ri < i)
	{
		line[ri] = remainder[ri];
		ri++;
	}
	if (remainder[i] == '\n')
		line[ri++] = '\n';
	line[ri] = '\0';
	return (line);
}

/*
* Among the remainder, dump the characters from the newline
* to the null character and update remainder.
* @param *remainder current remainder
* @return new remainder
*/
char	*update_remainder(char *remainder)
{
	size_t	len;
	size_t	src;
	size_t	dst;
	char	*buf;

	len = ft_strlen(remainder);
	src = 0;
	while (remainder[src] && remainder[src] != '\n')
		src++;
	if (!remainder[src])
	{
		free(remainder);
		return (NULL);
	}
	if (remainder[src] == '\n')
		src++;
	buf = (char *)malloc(sizeof(char) * (len - src + 1));
	if (!buf)
		return (NULL);
	dst = 0;
	while (remainder[src])
		buf[dst++] = remainder[src++];
	buf[dst] = '\0';
	free(remainder);
	return (buf);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*newstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc(
			sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	free((void *)s1);
	return (newstr);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}
