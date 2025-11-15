#!/bin/bash

gcc -Wall -Wextra -Werror -g get_next_line.c get_next_line_utils.c .test.c

OS=$(uname)
if [[ "$OS" == "Linux" ]]; then
    # Linux用の実行
    valgrind --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./a.out $@
else
    # macOS用の実行(Linux環境以外だと valgrind が使えないため)
    ./a.out $@
fi