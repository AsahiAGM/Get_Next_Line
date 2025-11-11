#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FILE_COUNT 3

int main(void)
{
    char *files[FILE_COUNT] = {
        ".src/.srcA.txt",
        ".src/.srcB.txt",
        ".src/.srcC.txt"
    };

    int i = 0;
    while (i < FILE_COUNT)
    {
        int fd_in = open(files[i], O_RDONLY);
        if (fd_in == -1)
        {
            perror(files[i]);
            return (0);
        }

        char out_filename[256];
        snprintf(out_filename, sizeof(out_filename), "output_%d.txt", i + 1);
        int fd_out = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0)
        {
            perror(out_filename);
            close(fd_in);
            continue ;
        }

        char *line;
        while ((line = get_next_line(fd_in)) != NULL)
        {
            write(1, line, ft_strlen(line));
            free(line);
        }
        write(1, "\n", 1);
        close(fd_in);
        close(fd_out);
        i++;
    }
    return (0);
}