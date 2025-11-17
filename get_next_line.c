/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                   :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamaguc <ahamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:30:20 by ahamaguc          #+#    #+#             */
/*   Updated: 2025/10/24 17:04:11 by ahamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_remainder	remainder;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder.buffer)
	{
		remainder.buffer = malloc(1);
		if (!remainder.buffer)
			return (NULL);
		remainder.buffer[0] = '\0';
		remainder.tail = 0;
	}
	remainder.buffer = read_and_store(fd, &remainder);
	if (!remainder.buffer)
		return (NULL);
	line = extract_line(remainder.buffer);
	if (!line)
	{
		remainder.buffer = NULL;
		return (NULL);
	}
	remainder.buffer = update_remainder(&remainder);
	return (line);
}
