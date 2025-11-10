#include "get_next_line.h"

/*
* Read from file until a newline or EOF is found,
* and append the read content to the given pointer.
* @param fd         file id
* @param *remainder buffer of reading char
* @return new remainder
*/
char	*read_and_store(int fd, char *remainder)
{
    char    buf[BUFFER_SIZE + 1];
    char    ch;
    int     i;

    i = 0;
    while (i < BUFFER_SIZE)
    {
        ch = read(fd, buf[i], 1);
        if (ch == '\n')
            break;;
        i++;
    }
    if (!remainder)
    {
        remainder = malloc(1);
        if (!remainder)
            return (NULL);
        remainder[0] = '\0';
    }
    remainder = ft_strjoin(remainder, buf);
    return (remainder);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}