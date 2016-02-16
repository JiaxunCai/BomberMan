#include "stdafx.h"

Enemy::Enemy(int x1,int y1):Element(x1,y1)
{ isDead=false;
  mark=true;
  moveSpeed=2;
  cnt=0;
  direction=Direction::DOWN;
}
void Enemy::draw(Graphics^g,ImageList^imagelist3)
{   Image^image;
    switch (direction)
       { case Direction::UP :
                 { if(cnt<4) image=imagelist3->Images[12];
				   else{ if(cnt<8)  image=imagelist3->Images[13];
				         else { if(cnt<12)   image=imagelist3->Images[12];
						         else image=imagelist3->Images[14];
				               }
				       }
					 break;
				 }
	     case Direction::DOWN :
			   { if(cnt<4) image=imagelist3->Images[3];
				   else{ if(cnt<8)  image=imagelist3->Images[4];
				         else { if(cnt<12)   image=imagelist3->Images[3];
						         else image=imagelist3->Images[5];
				               }
				       }
					 break;
				 }
		 case Direction::LEFT :
	          { if(cnt<4) image=imagelist3->Images[6];
				   else{ if(cnt<8)  image=imagelist3->Images[7];
				         else { if(cnt<12)   image=imagelist3->Images[6];
						         else image=imagelist3->Images[8];
				               }
				       }
					 break;
				 }
		 case Direction::RIGHT :
			 { if(cnt<4) image=imagelist3->Images[9];
				   else{ if(cnt<8)  image=imagelist3->Images[10];
				         else { if(cnt<12)   image=imagelist3->Images[9];
						         else image=imagelist3->Images[11];
				               }
				       }
					 break;
				 }
      } 
    g->DrawImage(image,pos.x,pos.y);
	cnt++;
	if(cnt==16)  cnt=0;
}