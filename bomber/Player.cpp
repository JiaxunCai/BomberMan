#include "stdafx.h"

extern int GridSize;
extern int rim;

Player::Player()
{ initial();
}
Player::Player(int x,int y):Element(x,y)
{ initial();
}
void Player::initial()
{ pos.x=0;
  pos.y=0;
  cpos.x=GridSize/2;
  cpos.y=rim+GridSize/2;
  moveSpeed=3;
  bombLimit=1;
  fireRange=1;
  isDead=false;
  mark=true;
  age=0;
  cnt=0;
  direction=Direction::DOWN;
}
void Player::draw(Graphics^g,ImageList^imagelist1)
{   Image^image;
    switch (direction)
       { case Direction::UP :
                 { if(cnt<4) image=imagelist1->Images[14];
				   else{ if(cnt<8)  image=imagelist1->Images[15];
				         else { if(cnt<12)   image=imagelist1->Images[14];
						         else image=imagelist1->Images[16];
				               }
				       }
					 break;
				 }
	     case Direction::DOWN :
			   { if(cnt<4) image=imagelist1->Images[5];
				   else{ if(cnt<8)  image=imagelist1->Images[6];
				         else { if(cnt<12)   image=imagelist1->Images[5];
						         else image=imagelist1->Images[7];
				               }
				       }
					 break;
				 }
		 case Direction::LEFT :
	          { if(cnt<4) image=imagelist1->Images[8];
				   else{ if(cnt<8)  image=imagelist1->Images[9];
				         else { if(cnt<12)   image=imagelist1->Images[8];
						         else image=imagelist1->Images[10];
				               }
				       }
					 break;
				 }
		 case Direction::RIGHT :
			 { if(cnt<4) image=imagelist1->Images[11];
				   else{ if(cnt<8)  image=imagelist1->Images[12];
				         else { if(cnt<12)   image=imagelist1->Images[11];
						         else image=imagelist1->Images[13];
				               }
				       }
					 break;
				 }
      } 
    g->DrawImage(image,pos.x,pos.y);
	cnt++;
	if(cnt==16)  cnt=0;
}