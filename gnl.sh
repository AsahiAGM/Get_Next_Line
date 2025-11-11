#!/bin/bash

gcc -Wall -Wextra -Werror -g get_next_line.c get_next_line_utils.c .runtest.c

OS=$(uname)
if [[ "$OS" == "Linux" ]]; then
    # Linux用の実行
    valgrind --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./a.out
else
    # macOS用の実行(Linux以外だと valgrind が使えないため)
    ./a.out
fi

echo
diff -u .src/.srcA.txt output_1.txt
echo
diff -u .src/.srcB.txt output_2.txt
echo
diff -u .src/.srcC.txt output_3.txt
echo

rm output_1.txt
rm output_2.txt
rm output_3.txt