#include "stdafx.h"

//该cpp文件包含Player类、Prize类、Bombsc类的共同基类  Element类

extern int GridSize;
int rim=10;                   //rim用于修正地图的上边框所带来的误差

Element::Element(){}
Element::Element(int x1,int y1):pos(x1,y1)
{  moveSpeed=2;                      //初始化移动速度
   direction=Direction::DOWN;        //初始化人物的方向
   cpos.x=pos.x+GridSize/2;          //cpos用于存储人物、墙壁、炸弹以及奖励的中心坐标，以便进行碰撞检测
   cpos.y=pos.y+GridSize/2+rim;
}
void Element::draw(Graphics^g,ImageList^){}    //纯虚函数,实现绘图
void Element::move()                //实现人物移动
{ switch(direction)
	{  case Direction::UP : { pos.y-=moveSpeed; cpos.y-=moveSpeed;  break; }   //向上移动
	   case Direction::DOWN : { pos.y+=moveSpeed; cpos.y+=moveSpeed;  break; }   //向下移动
	   case Direction::LEFT : { pos.x-=moveSpeed; cpos.x-=moveSpeed;  break; }   //向左移动
	   case Direction::RIGHT : { pos.x+=moveSpeed; cpos.x+=moveSpeed;  break; }   //向右移动
	}
}