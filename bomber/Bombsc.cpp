#include "stdafx.h"

extern int R,C;
extern int GridSize;
extern int rim;

Bombsc::Bombsc(int x1,int y1):Element(x1,y1)
{  bcount=0;
   elapse=0;
   Isleave=false;
}
void Bombsc::draw(Graphics^g,ImageList^imagelist3)
{  Image^image;
   if(bcount<3)  image=imagelist3->Images[0];
	 else { if(bcount<6) image=imagelist3->Images[1];
	        else { if(bcount<9)  image=imagelist3->Images[0];
			       else  image=imagelist3->Images[2];
			     }
	       }
   g->DrawImage(image,pos.x,pos.y);
   bcount++;
   if(bcount==12)   bcount=0;
}