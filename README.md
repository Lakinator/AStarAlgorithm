# AStarAlgorithm
Very basic implementation of the A* algorithm in C

## About
>- -d for debug information

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

#### Example [grid.amap](https://github.com/Lakinator/AStarAlgorithm/blob/master/grid.amap)
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
![example](https://i.imgur.com/d8IfA60.png)
