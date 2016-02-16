#include "stdafx.h"

Boss::Boss(int x1,int y1):Element(x1,y1)
{ isDead=false;
  moveSpeed=3;
  cnt=0;
  bulletlimit=5;
  energy=3;
  direction=Direction::DOWN;
}
void Boss::draw(Graphics^g,ImageList^imagelist3)
{   Image^image;
    switch (direction)
       { case Direction::UP :
                 { if(cnt<4) image=imagelist3->Images[25];
				   else{ if(cnt<8)  image=imagelist3->Images[26];
				         else { if(cnt<12)   image=imagelist3->Images[25];
						         else image=imagelist3->Images[27];
				               }
				       }
					 break;
				 }
	     case Direction::DOWN :
			   { if(cnt<4) image=imagelist3->Images[16];
				   else{ if(cnt<8)  image=imagelist3->Images[17];
				         else { if(cnt<12)   image=imagelist3->Images[16];
						         else image=imagelist3->Images[18];
				               }
				       }
					 break;
				 }
		 case Direction::LEFT :
	          { if(cnt<4) image=imagelist3->Images[19];
				   else{ if(cnt<8)  image=imagelist3->Images[20];
				         else { if(cnt<12)   image=imagelist3->Images[19];
						         else image=imagelist3->Images[21];
				               }
				       }
					 break;
				 }
		 case Direction::RIGHT :
			 { if(cnt<4) image=imagelist3->Images[22];
				   else{ if(cnt<8)  image=imagelist3->Images[23];
				         else { if(cnt<12)   image=imagelist3->Images[22];
						         else image=imagelist3->Images[24];
				               }
				       }
					 break;
				 }
      } 
    g->DrawImage(image,pos.x,pos.y);
	cnt++;
	if(cnt==16)  cnt=0;
}