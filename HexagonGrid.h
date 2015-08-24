#ifndef HEXAGONGRID_H
#define HEXAGONGRID_H

template<class T>
class HexagonGrid{
public:

    T Data;//存储数据
    int Weight;//权重
    int X;//坐标
    int Y;
    int TotalWeight;//到这里路程

public:
    HexagonGrid(){
        Weight=1;
        X=0;
        Y=0;
        TotalWeight=0;
    }
};


#endif // HEXAGONGRID_H
