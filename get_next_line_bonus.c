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

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_remainder	remainder[MAX_FD];
	char				*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder[fd].buffer)
	{
		remainder[fd].buffer = malloc(1);
		if (!remainder[fd].buffer)
			return (NULL);
		remainder[fd].buffer[0] = '\0';
	}
	remainder[fd].buffer = read_and_store(fd, &remainder[fd]);
	if (!remainder[fd].buffer)
		return (NULL);
	line = extract_line(remainder[fd].buffer);
	if (!line)
	{
		remainder[fd].buffer = NULL;
		return (NULL);
	}
	remainder[fd].buffer = update_remainder(&remainder[fd]);
	return (line);
}
