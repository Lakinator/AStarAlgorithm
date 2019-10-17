# AStarAlgorithm
Basic implementation of the A* algorithm in C

## About

#### Command line arguments
>- filepath
>- [-d]

#### Numbers
```
tile_empty  = 0
tile_wall   = 1
tile_start  = 2
tile_end    = 3
tile_open   = 7 //only for debug
tile_closed = 9 //only for debug
```

#### Structure of .amap files
>- No spaces at the start or between numbers!
```
[width ]
[height]
[][][][][][]...
[][][][][][]...
[][][][][][]...
```

#### Example 1 [grid.amap](https://github.com/Lakinator/AStarAlgorithm/blob/master/grid.amap)
```
13
8
1111111111111
1000100000031
1000100001001
1000100000001
1020101000001
1010000000001
1000100000001
1111111111111
```
![example](https://i.imgur.com/P2pG1to.png)

#### Example 2 [grid2.amap](https://github.com/Lakinator/AStarAlgorithm/blob/master/grid2.amap)
```
32
8
11111111111111111111111111111111
10001000000010000000010100000001
10001000010010000000000100000001
10001000000010000000100000001101
10201010000000000001000000000001
10100000000010000010001111000001
10001000000010000010000000300001
11111111111111111111111111111111
```
![example](https://i.imgur.com/4ua8edm.png)