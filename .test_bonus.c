#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

#define FILE_COUNT 1

int main(void)
{
    const char *files[FILE_COUNT] = {
        ".src/giant_line.txt"
        // ".src/.srcB.txt",
        // ".src/.srcC.txt"
    };
    int fds[FILE_COUNT];
    int eof[FILE_COUNT] = {0};
    int remaining = FILE_COUNT;
    char *line;
    int i;

    // ファイルを開く
    for (i = 0; i < FILE_COUNT; i++)
    {
        fds[i] = open(files[i], O_RDONLY);
        if (fds[i] < 0)
        {
            perror("open");
            return 1;
        }
    }

    srand(42);

    while (remaining > 0)
    {
        // EOF に達していない fd を選ぶ
        int idx;
        do
            idx = rand() % FILE_COUNT;
        while (eof[idx]);

        line = get_next_line(fds[idx]);
        if (line)
        {
            printf("fd=%d: %s", fds[idx], line);
            free(line);
        }
        else
        {
            printf("fd=%d: EOF\n", fds[idx]);
            eof[idx] = 1;
            remaining--;
        }
    }

    for (i = 0; i < FILE_COUNT; i++)
        close(fds[i]);

    return 0;
}
