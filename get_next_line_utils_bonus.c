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
		buf[bytes] = '\0';
		remainder->buffer = ft_strjoin(remainder, buf, bytes);
		if (!remainder->buffer)
			return (free(buf), NULL);
		if (ft_strrchr(buf, '\n', bytes))
			return (free(buf), remainder->buffer);
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (bytes < 0)
		return (free(remainder->buffer), NULL);
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
		return (free(remainder), NULL);
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
char	*update_remainder(t_remainder *remainder)
{
	size_t	src;
	size_t	dst;
	char	*buf;

	if (!remainder->buffer)
		return (NULL);
	src = 0;
	while (remainder->buffer[src] && remainder->buffer[src] != '\n')
		src++;
	if (remainder->buffer[src] == '\0')
		return (free(remainder->buffer), remainder->tail = 0, NULL);
	src++;
	buf = malloc(sizeof(char) * (remainder->tail - src + 1));
	if (!buf)
		return (free(remainder->buffer), remainder->tail = 0, NULL);
	dst = 0;
	while (remainder->buffer[src])
		buf[dst++] = remainder->buffer[src++];
	buf[dst] = '\0';
	free(remainder->buffer);
	remainder->tail = dst;
	return (buf);
}

char	*ft_strjoin(t_remainder *rem, const char *src, int src_len)
{
	char	*newstr;
	int		d;
	int		s;

	if (!rem->buffer || !src)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * (rem->tail + src_len + 1));
	if (!newstr)
		return (free(rem->buffer), NULL);
	d = -1;
	while (rem->buffer[++d])
		newstr[d] = rem->buffer[d];
	s = -1;
	while (src[++s])
		newstr[d + s] = src[s];
	newstr[d + s] = '\0';
	rem->tail = rem->tail + src_len + 1;
	return (free(rem->buffer), newstr);
}

char	*ft_strrchr(const char *s, int c, int bytes)
{
	bytes -= 1;
	while (bytes >= 0)
	{
		if (s[bytes] == (unsigned char)c)
			return ((char *)(s + bytes));
		bytes--;
	}
	return (NULL);
}
