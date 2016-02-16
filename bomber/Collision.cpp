#include "stdafx.h"
#include <cmath>

//该文件中包含碰撞检测函数

extern int GridSize;
int tolerance=3;          //设置碰撞检测的容忍度为3像素

bool Collision::Isoverlap(Position blockpos,Position actorpos)
{  if(abs(blockpos.x-actorpos.x)<GridSize-tolerance && abs(blockpos.y-actorpos.y)<GridSize-tolerance)//用物体的中心坐标做比较
        return true;
   return false;
}