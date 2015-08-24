#ifndef HEXAGONMAP_H
#define HEXAGONMAP_H
#include "HexagonGrid.h"
#include <vector>

/*简单封装了STL的queue*/
template<class T>
class Queue{
private:
    std::vector<T> __List;
public:
    Queue(){}
    ~Queue(){__List.clear();}
    void EnQueue( T x);
    T DeQueue();

    bool IsEmpty();
    int GetSize()const;
    T& operator[](int i);
};

template<class T>
void Queue<T>::EnQueue( T x){
    __List.push_back(x);
}

template<class T>
T Queue<T>::DeQueue(){
    T temp;
    temp=__List.at(0);
    __List.erase(__List.begin());
    return temp;
}

template<class T>
bool Queue<T>::IsEmpty(){
    return __List.empty();
}

template<class T>
int Queue<T>::GetSize() const{
    return __List.size();
}

template<class T>
T &Queue<T>::operator[](int i){
    return __List.at(i);
}
/***************************/


template<class T>
class HexagonMap{
public:
    //格子二维数组（Queue应该为Vector）篇章有限，直接用Queue
    //因为封装的queue重载了[]运算符，这直接用类似二维数组的方法访问元素
    Queue<Queue<HexagonGrid<T> > >map;

    int Width;//地图大小
    int Height;

public:
    HexagonMap(int x,int y){//新建一个地图
        Width=x-1;
        Height=y-1;

        for(int i=0;i<x;i++){
            Queue<HexagonGrid<T> > abc;
            map.EnQueue(abc);
            for(int j=0;j<y;j++){
                HexagonGrid<T> temp;
                map[i].EnQueue(temp);
                map[i][j].X=i;
                map[i][j].Y=j;
            }
        }

    }

    HexagonMap(const HexagonMap<T>& tempmap){//复制
        Width=tempmap.Width;
        Height=tempmap.Height;
        map=tempmap.map;

    }



    HexagonGrid<T> getGrid(int x,int y){//获取格子
        return map[x][y];
    }

    HexagonGrid<T> getu(int x,int y){//获取给定格子的上方格子
        HexagonGrid<T> temp;
        if(y==0)return temp;//如果到了边界，则返回一个空格子

        return map[x][y-1];
    }
    HexagonGrid<T> getd(int x,int y){//获取给定格子的下方格子
        HexagonGrid<T> temp;
        if(y==Height)return temp;//如果到了边界，则返回一个空格子
        return map[x][y+1];
    }
    HexagonGrid<T> getlu(int x,int y){//获取给定格子的左上方格子
        HexagonGrid<T> temp;
        if(x==0||(y==0&&x%2==0))return temp;//如果到了边界，则返回一个空格子

        if(x%2==1)
            return map[x-1][y];
        else
            return map[x-1][y-1];
    }
    HexagonGrid<T> getru(int x,int y){//获取给定格子的右上方格子
        HexagonGrid<T> temp;
        if(x==Width||(y==0&&x%2==0))return temp;//如果到了边界，则返回一个空格子

        if(x%2==1)
            return map[x+1][y];
        else
            return map[x+1][y-1];
    }
    HexagonGrid<T> getld(int x,int y){//获取给定格子的左下方格子
        HexagonGrid<T> temp;
        if(x==0||(y==Height&&x%2==1))return temp;//如果到了边界，则返回一个空格子

        if(x%2==1)
            return map[x-1][y+1];
        else
            return map[x-1][y];
    }
    HexagonGrid<T> getrd(int x,int y){//获取给定格子的右下方格子
        HexagonGrid<T> temp;
        if(x==Width||(y==Height&&x%2==1))return temp;//如果到了边界，则返回一个空格子

        if(x%2==1)
            return map[x+1][y+1];
        else
            return map[x+1][y];
    }

    void marku(int x,int y){//计算去到上方的路程
        if(y==0)return;


        if(map[x][y-1].TotalWeight==0)//如果上方还没有标记过
            map[x][y-1].TotalWeight=map[x][y].TotalWeight+map[x][y-1].Weight;
        else{
            int temp=map[x][y].TotalWeight+map[x][y-1].Weight;
            if(temp<map[x][y-1].TotalWeight||map[x][y-1].TotalWeight==0)//如果已经标记，则判断哪个路程较短，并记录
                map[x][y-1].TotalWeight=temp;

        }
    }

    void markd(int x,int y){//略同上
        if(y==Height)return;

        if(map[x][y+1].TotalWeight==0)
            map[x][y+1].TotalWeight=map[x][y].TotalWeight+map[x][y+1].Weight;
        else{
            int temp=map[x][y].TotalWeight+map[x][y+1].Weight;
            if(temp<map[x][y+1].TotalWeight||map[x][y+1].TotalWeight==0)
                map[x][y+1].TotalWeight=temp;

        }
    }
    void marklu(int x,int y){//略同
        if(x==0||(y==0&&x%2==0))return;

        if(x%2==1){//要判断奇偶
            if(map[x-1][y].TotalWeight==0)
                map[x-1][y].TotalWeight=map[x][y].TotalWeight+map[x-1][y].Weight;
            else{
                int temp=map[x][y].TotalWeight+map[x-1][y].Weight;
                if(temp<map[x-1][y].TotalWeight||map[x-1][y].TotalWeight==0)
                    map[x-1][y].TotalWeight=temp;
            }
        }
        else{
            if(map[x-1][y-1].TotalWeight==0)
                map[x-1][y-1].TotalWeight=map[x][y].TotalWeight+map[x-1][y-1].Weight;
            else{
                int temp=map[x][y].TotalWeight+map[x-1][y-1].Weight;
                if(temp<map[x-1][y-1].TotalWeight||map[x-1][y-1].TotalWeight==0)
                    map[x-1][y-1].TotalWeight=temp;
            }
        }
    }
    void markru(int x,int y){
        if(x==Width||(y==0&&x%2==0))return;

        if(x%2==1){
            if(map[x+1][y].TotalWeight==0)
                map[x+1][y].TotalWeight=map[x][y].TotalWeight+map[x+1][y].Weight;
            else{
                int temp=map[x][y].TotalWeight+map[x+1][y].Weight;
                if(temp<map[x+1][y].TotalWeight||map[x+1][y].TotalWeight==0)
                    map[x+1][y].TotalWeight=temp;
            }
        }
        else{
            if(map[x+1][y-1].TotalWeight==0)
                map[x+1][y-1].TotalWeight=map[x][y].TotalWeight+map[x+1][y-1].Weight;
            else{
                int temp=map[x][y].TotalWeight+map[x+1][y-1].Weight;
                if(temp<map[x+1][y-1].TotalWeight||map[x+1][y-1].TotalWeight==0)
                    map[x+1][y-1].TotalWeight=temp;
            }
        }
    }
    void markld(int x,int y){
        if(x==0||(y==Height&&x%2==1))return;

        if(x%2==1){
            if(map[x-1][y+1].TotalWeight==0)
                map[x-1][y+1].TotalWeight=map[x][y].TotalWeight+map[x-1][y+1].Weight;
            else{
                int temp=map[x][y].TotalWeight+map[x-1][y+1].Weight;
                if(temp<map[x-1][y+1].TotalWeight||map[x-1][y+1].TotalWeight==0)
                    map[x-1][y+1].TotalWeight=temp;
            }
        }
        else{
            if(map[x-1][y].TotalWeight==0)
                map[x-1][y].TotalWeight=map[x][y].TotalWeight+map[x-1][y].Weight;
            else{
                int temp=map[x][y].TotalWeight+map[x-1][y].Weight;
                if(temp<map[x-1][y].TotalWeight||map[x-1][y].TotalWeight==0)
                    map[x-1][y].TotalWeight=temp;
            }
        }
    }
    void markrd(int x,int y){
        if(x==Width||(y==Height&&x%2==1))return;

        if(x%2==1){
            if(map[x+1][y+1].TotalWeight==0)
                map[x+1][y+1].TotalWeight=map[x][y].TotalWeight+map[x+1][y+1].Weight;
            else{
                int temp=map[x][y].TotalWeight+map[x+1][y+1].Weight;
                if(temp<map[x+1][y+1].TotalWeight||map[x+1][y+1].TotalWeight==0)
                    map[x+1][y+1].TotalWeight=temp;
            }
        }
        else{
            if(map[x+1][y].TotalWeight==0)
                map[x+1][y].TotalWeight=map[x][y].TotalWeight+map[x+1][y].Weight;
            else{
                int temp=map[x][y].TotalWeight+map[x+1][y].Weight;
                if(temp<map[x+1][y].TotalWeight||map[x+1][y].TotalWeight==0)
                    map[x+1][y].TotalWeight=temp;
            }
        }
    }

    /******详见ReadMe!!!!!******/
    HexagonMap<T>* findWay(int x,int y){

        HexagonMap<T>* map=new HexagonMap<T>(*this);
        HexagonMap<T>* mapmark=new HexagonMap<T>(*this);

        Queue<HexagonGrid<T> > a;
        HexagonGrid<T> abc=map->getGrid(x,y);
        a.EnQueue(abc);

        while(a.IsEmpty()!=true){
            HexagonGrid<T> temp=a.DeQueue();

            mapmark->map[temp.X][temp.Y].TotalWeight=-1;

            map->marku(temp.X,temp.Y);
            map->markru(temp.X,temp.Y);
            map->markrd(temp.X,temp.Y);
            map->markd(temp.X,temp.Y);
            map->markld(temp.X,temp.Y);
            map->marklu(temp.X,temp.Y);

            a.EnQueue(map->getu(temp.X,temp.Y));
            a.EnQueue(map->getru(temp.X,temp.Y));
            a.EnQueue(map->getrd(temp.X,temp.Y));
            a.EnQueue(map->getd(temp.X,temp.Y));
            a.EnQueue(map->getld(temp.X,temp.Y));
            a.EnQueue(map->getlu(temp.X,temp.Y));

            int size=a.GetSize();
            Queue<HexagonGrid<T> > b;
            for(int i=0;i<size;i++){
                HexagonGrid<T> temp1=a.DeQueue();
                if((temp1.X!=0||temp1.Y!=0)&&mapmark->map[temp1.X][temp1.Y].TotalWeight==0)
                    b.EnQueue(temp1);
            }
            a=b;
        }


        mapmark=new HexagonMap(*this);

        Queue<HexagonGrid<T> > a1;
        HexagonGrid<T> abc1=map->getGrid(x,y);
        a1.EnQueue(abc1);
        while(a1.IsEmpty()!=true){
            HexagonGrid<T> temp=a1.DeQueue();

            mapmark->map[temp.X][temp.Y].TotalWeight=-1;


            map->marklu(temp.X,temp.Y);
            map->markld(temp.X,temp.Y);
            map->markd(temp.X,temp.Y);
            map->markrd(temp.X,temp.Y);
            map->markru(temp.X,temp.Y);
            map->marku(temp.X,temp.Y);

            a1.EnQueue(map->getlu(temp.X,temp.Y));
            a1.EnQueue(map->getld(temp.X,temp.Y));
            a1.EnQueue(map->getd(temp.X,temp.Y));
            a1.EnQueue(map->getrd(temp.X,temp.Y));
            a1.EnQueue(map->getru(temp.X,temp.Y));
            a1.EnQueue(map->getu(temp.X,temp.Y));

            int size=a1.GetSize();
            Queue<HexagonGrid<T> > b1;
            for(int i=0;i<size;i++){
                HexagonGrid<T> temp1=a1.DeQueue();
                if((temp1.X!=0||temp1.Y!=0)&&mapmark->map[temp1.X][temp1.Y].TotalWeight==0)
                    b1.EnQueue(temp1);
            }
            a1=b1;

        }
        return map;
    }
    /******详见ReadMe!!!!!******/

};


#endif // HexagonMap_H
