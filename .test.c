#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void process_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror(filename);
        return;
    }

    char *line;
    write(1, "\n<< ", 5);
    write(1, filename, strlen(filename));
    write(1, " >>\n", 5);
    while ((line = get_next_line(fd)) != NULL)
    {
        write(1, line, strlen(line));
        free(line);
    }
    write(1, "\n", 1);
    close(fd);
}

int main(int argc, char **argv)
{
    // (void)argc;
    // (void)argv;
    // printf("hello, github actions!!");
    if (argc > 1)
    {
        // argvから複数ファイルを処理
        for (int i = 1; i < argc; i++)
            process_file(argv[i]);
        return 0;
    }

    // stdin からスペース区切りでファイル名を受け取る
    char buf[4096]; // 十分大きく。バッファは4045文字までしか入らないのでこれが上限
    if (fgets(buf, sizeof(buf), stdin))
    {
        // 改行削除
        buf[strcspn(buf, "\n")] = 0;

        char *token = strtok(buf, " ");
        while (token)
        {
            process_file(token);
            token = strtok(NULL, " ");
        }
    }

    return 0;
}
