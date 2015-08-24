#include<iostream>
#include"Hexagon.h"
using namespace std;
int main(){

    /*测试用*/
    HexagonMap<int>* map;
    map=new HexagonMap<int>(3,4);
    map=map->findWay(2,3);
    cout<<map->map[0][0].TotalWeight<<endl;

    return 0;
}
