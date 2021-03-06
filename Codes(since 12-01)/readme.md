除了 Codeforces 套题，日常做的题就放在这里。

#### notice:

- 2019.01.08：学完 min_25 筛之后突然反应过来杜教筛甚至连哈希表都不用。因为所有可能出现的前缀位置一定满足形如 $\left\lfloor\frac{n}{i}\right\rfloor(i \leq n)$，即只会有最多 $O(\sqrt n)$ 个不同的前缀位置需要筛，所以开一个长为 $2\sqrt n$ 的数组就可以存下了（具体参见 min_25 筛题目中的自定义结构体 `my_array`）。在这之前的杜教筛代码使用的哈希表，之后将会修改。~~我以前sb了。虽然看到过这种做法但没怎么管......~~
- 2019.03.14：修改 link-cut-tree 的写法（`splay`   函数）。
- 2019.04.26：在这之前的部分代码中，匿名函数（`function` 或 `auto` 类函数）与其他的代码间会包含单独的空行，之后将会取消。
- 2019.06.10：早期 AtCoder 的题目代码命名会使用题目的四位数编号，如 `AtCoder1999`（编号可在 luogu 或 vjudge 上找到），后期的题目代码命名会直接使用“比赛编号+字母编号”的格式，如 `AGC034E`。
- 通常情况下，代码命名的格式为“OJ 名称+题目编号”，若某些题目未在公开 OJ 中收录/找到，则在命名中以题目来源代替 OJ 名称，如 `[SCOI2019]超矩形`、`[NOI模拟赛]与运算`。
- GitHub 上放置有代码的题目，代码请以 Github 上为准（即个人文件夹内可能有误）。
