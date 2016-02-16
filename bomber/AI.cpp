#include "stdafx.h"

using namespace System::Collections::Generic;

extern int GridSize;
extern int R,C;

void AI::Gets(Maps^m1)
{ tmap=m1;
}
void AI::Getposition(Element^enemy,int%x,int%y)
{ if(enemy->pos.x%GridSize>GridSize/2)
      x=enemy->pos.x/GridSize+1;
  else   x=enemy->pos.x/GridSize;
  if(enemy->pos.y%GridSize>GridSize/2)
	  y=enemy->pos.y/GridSize+1;
  else   y=enemy->pos.y/GridSize;
}
void AI::UpdateEscape(List<Bombsc^>^bombs1,Player^player)
{ for each(Bombsc^bomb in bombs1)
   { int x=bomb->pos.x/GridSize;
     int y=bomb->pos.y/GridSize;
	 int began = (x-player->fireRange>0) ? x-player->fireRange:0 ;
	 int ed = (x+player->fireRange<C) ? x+player->fireRange:(C-1) ;
	 while(began<ed)
	   { if(y-1>=0 && tmap->grid[y-1,began]==GridState::Blank) 
		     EscapeDir[y,began]=Direction::UP;
	     else  
			{ if(y+1<R && tmap->grid[y+1,began]==GridState::Blank)
	               EscapeDir[y,began]=Direction::DOWN;
		       else  
				   { if(began<x && began-1>=0 && tmap->grid[y,began-1]==GridState::Blank)
				         EscapeDir[y,began]=Direction::LEFT;
	                 if(began>x && began+1<C && tmap->grid[y,began+1]==GridState::Blank)
						 EscapeDir[y,began]=Direction::RIGHT;
	               }  
	        }
	 	 began++;
	   }

	 began = (y-player->fireRange>0) ? y-player->fireRange:0 ;
	 ed = (y+player->fireRange<R) ? y+player->fireRange:(R-1) ;
	 while(began<ed)
	   { if(x-1>=0 && tmap->grid[began,x-1]==GridState::Blank) 
		     EscapeDir[began,x]=Direction::LEFT;
	     else  
			{ if(x+1<C && tmap->grid[began,x+1]==GridState::Blank)
	               EscapeDir[began,x]=Direction::RIGHT;
		       else  
				   { if(began<y && began-1>=0 && tmap->grid[began-1,x]==GridState::Blank)
				         EscapeDir[began,x]=Direction::UP;
	                 if(began>y && began+1<R && tmap->grid[began+1,x]==GridState::Blank)
						 EscapeDir[began,x]=Direction::DOWN;
	               }  
	        }
	 	 began++;
	   }
   }
}
bool AI::IsDanger(Element^enemy)
{ int x=0,y=0;
  Getposition(enemy,x,y);
  if(EscapeDir[y,x]!=Direction::Safe)
	 return true;
  return false;
}
void AI::UpdateAttack(Element^player)
{ int newx=0,newy=0;
  Getposition(player,newx,newy);
  if(lastX!=newx||lastY!=newy)
   { Attack=gcnew array<int,2>(R,C);
     lastX=newx;
	 lastY=newy;
	 paths->Clear();
	 Updatepath(newx,newy);
   }
}
void AI::Updatepath(int x1,int y1)
{ int length=1;
  int m=1,n=0;
  Position ^temp;
  paths->Enqueue(gcnew Position(x1,y1));
  while(paths->Count>0)
  { temp=paths->Dequeue();
    int x=temp->x;
	int y=temp->y;
	Attack[y,x]=1;
	m--;
	if(x-1>=0 && Attack[y,x-1]!=1 && tmap->grid[y,x-1]==GridState::Blank && EscapeDir[y,x-1]==Direction::Safe)
	  { AttackDir[y,x-1]=Direction::RIGHT;
	    paths->Enqueue(gcnew Position(x-1,y));
		n++;
	  }
	if(y-1>=0 && Attack[y-1,x]!=1 && tmap->grid[y-1,x]==GridState::Blank && EscapeDir[y-1,x]==Direction::Safe)
	  { AttackDir[y-1,x]=Direction::DOWN;
		paths->Enqueue(gcnew Position(x,y-1));
		n++;
	  }
	if(y+1<R && Attack[y+1,x]!=1 && tmap->grid[y+1,x]==GridState::Blank && EscapeDir[y+1,x]==Direction::Safe)
	  { AttackDir[y+1,x]=Direction::UP;
		paths->Enqueue(gcnew Position(x,y+1));
		n++;
	  }
	if(x+1<C && Attack[y,x+1]!=1 && tmap->grid[y,x+1]==GridState::Blank && EscapeDir[y,x+1]==Direction::Safe)
	  { AttackDir[y,x+1]=Direction::LEFT;
		paths->Enqueue(gcnew Position(x+1,y));
		n++;
	  }
	if(m==0)                            //本层搜索完成进入下一层
	 { m=n;
	   n=0;
	   length++;
	   if(length>tlevel*2+4)                  //控制深度
		    return;
	 }
  }
}
void AI::ChangeDir(Element^enemy,int n)
{ int x=0,y=0;
  Getposition(enemy,x,y);
  switch (n)
    { case 1: enemy->direction=EscapeDir[y,x]; break;
	  case 2: enemy->direction=AttackDir[y,x]; break;
    }
}
bool AI::IsAttack(Element^enemy)
{ int x=0,y=0;
  Getposition(enemy,x,y);
  if(Attack[y,x]==1)
	 return true;
  return false;
}