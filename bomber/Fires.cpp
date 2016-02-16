#include "stdafx.h"

extern int GridSize;
extern int rim;
extern int R,C;

Fires::Fires(int x1,int y1,FiresType type1,Direction dir1):Element(x1,y1)
{ Elapsed=0;
  cnt=0;
  firestype=type1;
  direction=dir1;
}
void Fires::draw(Graphics^g,ImageList^imagelist2)
{ Image^image=imagelist2->Images[0];
  if(firestype==FiresType::FiresCenter)
    { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[0];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[1];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[2];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[0];  break; }
        }
      g->DrawImage(image,pos.x,pos.y);
    }
  if(firestype==FiresType::FiresMiddle&&direction==Direction::DOWN)
    { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[3];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[4];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[5];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[3];  break; }
        }
     g->DrawImage(image,pos.x,pos.y);
    }
  if(firestype==FiresType::FiresEnd&&direction==Direction::DOWN)
    { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[6];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[7];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[8];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[9];  break; }
        }
      g->DrawImage(image,pos.x,pos.y);
    }
  if(firestype==FiresType::FiresMiddle&&direction==Direction::RIGHT)
    { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[17];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[18];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[19];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[17];  break; }
        }
      g->DrawImage(image,pos.x,pos.y);
    }
  if(firestype==FiresType::FiresEnd&&direction==Direction::RIGHT)
    { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[20];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[21];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[22];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[23];  break; }
        }
      g->DrawImage(image,pos.x,pos.y);
   }
  if(firestype==FiresType::FiresMiddle&&direction==Direction::UP)
    { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[24];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[25];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[26];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[24];  break; }
        }
      g->DrawImage(image,pos.x,pos.y);
    }
 if(firestype==FiresType::FiresEnd&&direction==Direction::UP)
   { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[27];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[28];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[29];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[30];  break; }
        }
     g->DrawImage(image,pos.x,pos.y);
   } 
 if(firestype==FiresType::FiresMiddle&&direction==Direction::LEFT)
    { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[10];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[11];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[12];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[10];  break; }
        }
      g->DrawImage(image,pos.x,pos.y);
    }
 if(firestype==FiresType::FiresEnd&&direction==Direction::LEFT)
    { switch(cnt)
        { case 0: 
          case 1: { image=imagelist2->Images[13];  break; }
	      case 3: 
	      case 4: { image=imagelist2->Images[14];  break; }
		  case 5:
		  case 6: { image=imagelist2->Images[15];  break; }
		  case 7:
		  case 8: { image=imagelist2->Images[16];  break; }
        }
      g->DrawImage(image,pos.x,pos.y);
    }
 cnt++;
 if(cnt>8)  cnt=0;
}