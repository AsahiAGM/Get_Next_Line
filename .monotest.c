#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int fd = open(".src/.srcA.txt", O_RDONLY);
    if (fd == -1)
    {
        perror(".src/.srcA.txt");
        return (0);
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        write(1, line, ft_strlen(line));
        free(line);
    }
    close(fd);
    return (0);
}