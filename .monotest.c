#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FILE_COUNT 3

typedef struct s_file_state
{
    int fd;
    int eof;
    const char *path;
} t_file_state;

char *read_line_from_file(int file_index, t_file_state *files, int file_count)
{
    if (file_index < 0 || file_index >= file_count)
        return NULL;
    if (files[file_index].eof)
        return NULL;    
    char *line = get_next_line(files[file_index].fd);
    if (!line)
        files[file_index].eof = 1;
    return line;
}

int main(void)
{
    t_file_state files[FILE_COUNT] = {
        {.fd = -1, .eof = 0, .path = ".src/.srcA.txt"},
        {.fd = -1, .eof = 0, .path = ".src/.srcB.txt"},
        {.fd = -1, .eof = 0, .path = ".src/.srcC.txt"}
    };

    // ファイルを開く
    for (int i = 0; i < FILE_COUNT; i++)
    {
        files[i].fd = open(files[i].path, O_RDONLY);
        if (files[i].fd == -1)
        {
            perror(files[i].path);
            files[i].eof = 1; // 開けなければ常に NULL を返す
        }
    }

    // 標準入力からファイル番号を受け取り 1 行ずつ出力
    int file_index;
    while (scanf("%d", &file_index) == 1)
    {
        char *line = read_line_from_file(file_index, files, FILE_COUNT);
        if (line)
        {
            write(1, line, strlen(line));
            free(line);
        }
        else
        {
            write(1, "(NULL)\n", 7);
        }
    }

    // 終了時に全て閉じる
    for (int i = 0; i < FILE_COUNT; i++)
        if (files[i].fd != -1)
            close(files[i].fd);

    return 0;
}
