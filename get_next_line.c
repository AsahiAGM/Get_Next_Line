#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_and_store(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	if (line)
		remainder = update_remainder(remainder);
	if (remainder && remainder[0] == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	return (line);
}