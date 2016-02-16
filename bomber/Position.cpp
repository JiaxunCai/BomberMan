#include "stdafx.h"

Position::Position(){}
Position::Position(int x1,int y1)
{ x=x1;
  y=y1;
}
Position::Position(Position %pos1)
{  x=pos1.x;
   y=pos1.y;
}
bool Position::Equals(Object^obj)  
{ if (obj->GetType()!=this->GetType())         //进行类型比较
             return false;
  Position^other=(Position^)obj;
  return ((other->x.Equals(this->x))&&(other->y.Equals(this->y)));       //调用基类版本的Equals对Keys类型的对象进行比较
}