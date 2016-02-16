#include "stdafx.h"

Bullet::Bullet(int x1,int y1,Direction dir):Element(x1,y1)
{ direction=dir;
  moveSpeed=5;
}
void Bullet::draw(Graphics^g,ImageList^imagelist3)
{   Image^image;
    switch (direction)
       { case Direction::UP : image=imagelist3->Images[31];  break;
	     case Direction::DOWN : image=imagelist3->Images[28];  break;
		 case Direction::LEFT : image=imagelist3->Images[29];  break;
		 case Direction::RIGHT : image=imagelist3->Images[30];  break;
	   }
    g->DrawImage(image,pos.x,pos.y);
}