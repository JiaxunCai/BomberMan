#include "stdafx.h"

Door::Door(int x1,int y1):Element(x1,y1){}
void Door::draw(Graphics^g,ImageList^imagelist3)
{ Image^image=imagelist3->Images[15];
  g->DrawImage(image,pos.x,pos.y);
}