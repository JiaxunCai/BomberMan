#include "stdafx.h"

using namespace System::Collections::Generic;

extern int R,C;

wallType::wallType(){}
wallType::wallType(int y,int x,Walltype wt):r(y),c(x),isfix(wt){}
void wallType::draw(Graphics^g,ImageList^imagelist1)
{  Image^image;
   switch(isfix)
	 { case fixedWall_1: image=imagelist1->Images[0];  break;
	   case fixedWall_2: image=imagelist1->Images[1];  break;
	   case Wall_1: image=imagelist1->Images[2];  break;
	   case Wall_2: image=imagelist1->Images[3];  break;
	   case Wall_3: image=imagelist1->Images[4];  break;
   }
   g->DrawImage(image,c,r);
 }