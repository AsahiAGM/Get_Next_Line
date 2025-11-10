#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42
# define REMAINDER_SIZE 4065

// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
char	*read_and_store(int fd, char *remainder);
char	*extract_line(char *remainder);
char	*update_remainder(char *remainder);
size_t	ft_strlcat(char *dst, char const *src, size_t size);

#endif