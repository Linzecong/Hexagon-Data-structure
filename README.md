# Hexagon-Data-structure
This is a Simple weighted Hexagon (Cellular topology) Data structure base on double dimensional array.
这是一个非常简单的带权六边形数据结构
基于二维数组实现

# About HexagonGrid
![image](https://raw.githubusercontent.com/Linzecong/Hexagon-Data-structure/master/images-folder/grid.png)

每个六边形地图都由许多六边形格子组成，格子拥有的属性详见HexagonGrid的注释

# About HexagonMap
![image](https://raw.githubusercontent.com/Linzecong/Hexagon-Data-structure/master/images-folder/map.png)

如图这是一个5*4的地图，以中间那个格子为例，有六个方向。

如果用二维数组表示，各个格子的坐标如图，通过分析可知，只需判断列的奇偶，就可以确定六个方向的坐标。
![image](https://raw.githubusercontent.com/Linzecong/Hexagon-Data-structure/master/images-folder/map1.png)

详细函数见HexagonMap.h的注释

# About FindWay 寻路

通过各个格子的权重，计算从某个格子到某个格子的最短路径。
算法需要一个队列作为辅助，详细如下：

首先给定一个格子，该格子入队。
当队列不为空 {
第一个格子出队，将该格子标记。
按顺时针，计算从该格子到该格子的六个方向所需的最短路程（weight），记录在该格子的TotalWeight中。
按顺时针，该格子的六个方向入队。
新建一个辅助队列，将原队列里有效的格子复制到新队列。（超出边界或已标记的为无效格子）。
}

然后将上述算法以逆时针进行一遍。函数返回一个HexagonMap的指针，该地图的格子的TotalWeight即最短路程。

例：
假设所有格子权重均为1，以(4,2)为起点，则：
![image](https://raw.githubusercontent.com/Linzecong/Hexagon-Data-structure/master/images-folder/findway.png)

因为算法原因所以从(4,2)到(4,2)的路程为2。






