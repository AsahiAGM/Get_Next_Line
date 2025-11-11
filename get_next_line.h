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
char	*ft_strjoin(char *s1, const char *s2);
size_t	ft_strlen(const char *str);

#endif