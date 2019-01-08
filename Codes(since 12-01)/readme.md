除了 Codeforces 套题，日常做的题就放在这里。

#### notice:

- 2019.01.08：学完 min_25 筛之后突然反应过来杜教筛甚至连哈希表都不用。因为所有可能出现的前缀位置一定满足形如 <a href="https://www.codecogs.com/eqnedit.php?latex=\left\lfloor\frac{n}{i}\right\rfloor(i&space;\leq&space;n)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\left\lfloor\frac{n}{i}\right\rfloor(i&space;\leq&space;n)" title="\left\lfloor\frac{n}{i}\right\rfloor(i \leq n)" /></a>，即只会有最多 $O(\sqrt n)$ 个不同的前缀位置需要筛，所以开一个 $\sqrt n$ 的数组就可以存下了（具体参见 min_25 筛题目中的自定义结构体 `my_array`）。在这之前的杜教筛代码使用的哈希表，之后将会修改。~~我以前sb了。虽然看到过这种做法但没怎么管......~~
