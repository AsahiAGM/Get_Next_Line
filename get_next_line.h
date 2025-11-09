#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

char	*get_next_line(int fd);
char	*read_and_store(int fd, char *remainder);
char	*extract_line(char *remainder);
char	*update_remainder(char *remainder);

#endif