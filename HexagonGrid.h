#ifndef HEXAGONGRID_H
#define HEXAGONGRID_H

template<class T>
class HexagonGrid{
public:

    T Data;
    int Weight;
    int X;
    int Y;
    int TotalWeight;

public:
    HexagonGrid(){
        Weight=1;
        X=0;
        Y=0;
        TotalWeight=0;
    }
};


#endif // HEXAGONGRID_H
