# Get_Next_Line
## 開発メモ
1. `static char *remainder;`
ファイルディスクリプタごとに 読み残しを保持する役割

1回の read で取得したデータが改行までに達していない場合や、改行後の残りを保持するために使われます。
staticを持ちることにより、次回 get_next_line 呼び出し時にも続きから読み出せます

注意点：
複数ファイル同時に扱う場合は fdごとに管理する必要があります。
今のコードは 単一 fd 用 です。BONUSで複数 fd に対応させたい場合は、`static char *remainders[FD_MAX]; `のように fd インデックスで配列管理するのが一般的です。

2. `read_and_store(fd, remainder)`
read を繰り返し、BUFFER_SIZE 分ずつ読み込み、remainder に追加する関数

改行に達するか EOF まで読み込む
成功すれば更新された remainder を返す
失敗やエラー時は NULL を返す

標準的なパターンでは、
```bash
malloc でバッファを確保
↓
read(fd, buf, BUFFER_SIZE) をループ
↓
改行('\n')が見つかったらそこで停止
↓
以前の remainder と結合
```
という流れになります。

```c
/*
* Read from file until a newline or EOF is found,
* and append the read content to the given pointer.
* @param fd         file id
* @param *remainder buffer of reading char
* @return new remainder
*/
char	*read_and_store(int fd, t_remainder *remainder)
{
	char	*buf;
	int		bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(remainder->buffer), NULL);
	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		remainder->buffer = ft_strjoin(remainder, buf, bytes);
		if (!remainder->buffer)
			return (free(buf), NULL);
		if (ft_strchr(buf, '\n'))
			return (free(buf), remainder->buffer);
		bytes = read(fd, buf, BUFFER_SIZE);
	}
    // read = -1,読み込みエラー と 0,EOF のときの処理
    // -1, 読み込みエラーの時はそこでGNLのプロセスを中断、static変数もリセットする
    // 0, の時は、remainderに描画候補が無いときだけ解放
	if (bytes < 0)
		return (free(remainder->buffer), NULL);
	if (!remainder->buffer || remainder->buffer[0] == '\0')
		return (free(remainder->buffer), NULL);
	return (remainder->buffer);
}
```

3. `extract_line(remainder)`
remainder から 1行分（改行まで、改行を含める場合もあり）を切り出す

malloc で新しい文字列を作り返す
これが get_next_line の戻り値になります

4. `update_remainder(remainder)`
extract_line で切り出した後の残りを 再度 remainder として保持

EOF に達して残りがなければ free して NULL にする
次回呼び出し時に read_and_store で再利用

## BONUSについて
### 複数のファイルに対応したremainderを用意する
`char *remainder[MAX_FD] (# define MAX_FD 1024)`とすることで、複数ファイル(のfd)に対応したポインタを用意し、GNLの引数に応じて参照するremainderを切り替えるようにした

- _SC_OPEN_MAX と _SC_MQ_OPEN_MAX の違い
```bash
_SC_OPEN_MAX
意味：プロセスが同時に開くことのできる ファイルディスクリプタの最大数
getrlimit(RLIMIT_NOFILE, …) と同じ制限を参照することが多い
sysconf(_SC_OPEN_MAX) で取得可能
例：標準的な Linux では 1024 や 4096 など

_SC_MQ_OPEN_MAX
意味：プロセスが同時に開くことのできる POSIX メッセージキュー (message queue) の最大数
メッセージキュー専用で、ファイルディスクリプタとは別扱い
例：Linux では 10 や 32 など小さい値になることが多い

!!
ただしfrancinetteでは _SC_OPEN_MAX を利用するとエラーになる（おそらく未定義扱いになる）ので、実行は失敗してしまう。
```