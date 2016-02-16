#include "stdafx.h"

Prize::Prize(int x1,int y1,PrizeType type1):Element(x1,y1)
{ type=type1;
}
void Prize::draw(Graphics^g,ImageList^imagelist1)
{ Image^image;
  switch(type)
  {  case Life: { image=imagelist1->Images[17];  break; }
     case Power: { image=imagelist1->Images[19];  break; }
	 case Bombers: { image=imagelist1->Images[18];  break; }
	 case Speed: { image=imagelist1->Images[20];  break; }
  }
  g->DrawImage(image,pos.x,pos.y);
}