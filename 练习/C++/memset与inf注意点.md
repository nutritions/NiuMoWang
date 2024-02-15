memset是按字节赋值的

对小于1e9的数据，并且要求无穷加无穷不溢出，使用memset应该赋值为0x3f，vector直接赋值应该是0x3f3f3f3f；如果没有相加，应该是0x7f和0x7f7f7f7f



参考：[关于memset函数和赋值0x3f，2021-5-5-CSDN博客](https://blog.csdn.net/qq_42386788/article/details/116427457)

