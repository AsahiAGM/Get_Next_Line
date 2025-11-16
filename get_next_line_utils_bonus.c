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

#include "get_next_line_bonus.h"

/*
* Read from file until a newline or EOF is found,
* and append the read content to the given pointer.
* @param fd         file id
* @param *remainder buffer of reading char
* @return new remainder
*/
char	*read_and_store(int fd, t_remainder *remainder)
{
	char	*buf;
	int		bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(remainder->buffer), NULL);
	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		if (bytes < 0)
			return (free(remainder->buffer), free(buf), NULL);
		buf[bytes] = '\0';
		remainder->buffer = ft_strjoin(remainder, buf, bytes);
		if (!remainder->buffer)
			return (free(buf), NULL);
		if (ft_strchr(buf, '\n'))
			return (free(buf), remainder->buffer);
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (!remainder->buffer || remainder->buffer[0] == '\0')
		return (free(remainder->buffer), NULL);
	return (remainder->buffer);
}

/*
* Read from the buffer until a newline or EOF is found,
* then dump as much as you read.
* @param *remainder buffer of reading char
* @return new line
*/
char	*extract_line(char *remainder)
{
	size_t	end;
	size_t	ri;
	char	*line;

	end = 0;
	ri = 0;
	if (!remainder || remainder[0] == '\0')
		return (NULL);
	while (remainder[end] && remainder[end] != '\n')
		end++;
	if (remainder[end] == '\n')
		line = (char *)malloc(sizeof(char) * (end + 2));
	else
		line = (char *)malloc(sizeof(char) * (end + 1));
	if (!line)
		return (free(remainder), NULL);
	while (ri < end)
	{
		line[ri] = remainder[ri];
		ri++;
	}
	if (remainder[end] == '\n')
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

	if (!remainder)
		return (NULL);
	src = 0;
	while (remainder[src] && remainder[src] != '\n')
		src++;
	if (remainder[src] == '\0')
		return (free(remainder), NULL);
	src++;
	len = 0;
	while (remainder[len])
		len++;
	buf = (char *)malloc(sizeof(char) * (len - src + 1));
	if (!buf)
		return (free(remainder), NULL);
	dst = 0;
	while (remainder[src])
		buf[dst++] = remainder[src++];
	buf[dst] = '\0';
	free(remainder);
	return (buf);
}

char	*ft_strjoin(t_remainder *s1, const char *s2, int src_len)
{
	char	*newstr;
	int		dst;
	int		src;

	if (!s1->buffer || !s2)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * (s1->tail + src_len + 1));
	if (!newstr)
		return (free(s1->buffer), NULL);
	dst = -1;
	while (s1->buffer[++dst])
		newstr[dst] = s1->buffer[dst];
	src = -1;
	while (s2[++src])
		newstr[dst + src] = s2[src];
	newstr[dst + src] = '\0';
	s1->tail = s1->tail + src_len + 1;
	return (free(s1->buffer), newstr);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (s[i] == (unsigned char )c)
			return ((char *)(s + i));
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (NULL);
}
