#include "get_next_line.h"

char	*read_and_store(int fd, char *remainder)
{
    char    *buf;
    char    ch;
    int     i;

    buf = malloc(sizeof(char) * BUFFER_SIZE);
    if (!buf)
        return (NULL);
    i = 0;
    while (i < BUFFER_SIZE)
    {
        ch = read(fd, buf[i], 1);
        if (ch == '\n')
            return (buf);
        i++;
    }
    if (!remainder)
    {
        remainder= malloc(sizeof(char) * REMAINDER_SIZE + 1);
        if (!remainder)
            return (NULL);
    }
    ft_strlcat(remainder, buf, REMAINDER_SIZE);
    return (buf);
}

size_t	ft_strlcat(char *dst, char const *src, size_t size)
{
	size_t	str_len;
	int		i;

	str_len = 0;
	while (src[str_len])
		str_len++;
	if (REMAINDER_SIZE >= size)
		return (size + str_len);
	i = 0;
	while (src[i] && REMAINDER_SIZE + i + 1 < size)
	{
		dst[REMAINDER_SIZE + i] = src[i];
		i++;
	}
	dst[REMAINDER_SIZE + i] = '\0';
	return (REMAINDER_SIZE + str_len);
}