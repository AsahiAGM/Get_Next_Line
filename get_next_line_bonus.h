/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                   :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamaguc <ahamaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:30:20 by ahamaguc          #+#    #+#             */
/*   Updated: 2025/10/24 17:04:11 by ahamaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# define MAX_FD 1024

typedef struct s_remainder
{
	char	*buffer;
	size_t	tail;
}	t_remainder;

// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
char	*read_and_store(int fd, t_remainder *remainder);
char	*extract_line(char *remainder);
char	*update_remainder(t_remainder *remainder);
char	*ft_strjoin(t_remainder *s1, const char *s2, int src_len);
char	*ft_strrchr(const char *s, int c, int bytes);

#endif