#include "stdafx.h"
#include<ctime>
#include<cstdlib>

int R=15,C=21;
int width=1;
int GridSize=30;
int counter=0;
wall*head=NULL;

Maps::Maps()
{  srand(int(time(0)));
   maze=gcnew array<int,2>(R,C);
   grid=gcnew array<GridState,2>(R,C);
   Generate(0,0);
   Initial();
   Check();
}
void Maps::Newmaps()
{  srand(int(time(0)));
   maze=gcnew array<int,2>(R,C);
   grid=gcnew array<GridState,2>(R,C);
   Generate(0,0);
   Initial();
   Check();
}
void Maps::Generate(int r,int c)
{  maze[r,c]=1;
   if(r-width-1>=0&&maze[r-width,c]==0)
    	Push(r-width,c,1);
   if(r+width+1<R&&maze[r+width,c]==0)
    	Push(r+width,c,2);
   if(c-width-1>=0&&maze[r,c-width]==0)
    	Push(r,c-width,3);
   if(c+width+1<C&&maze[r,width+c]==0)
     	Push(r,c+width,4);
   srand(int(time(0)));
   int range;
   while((range=counter)>0)
    {  int key=rand()%range;
       wall*temp=getwall(key);
       int r1=temp->neighbor->row;
       int c1=temp->neighbor->coloum;
       if(maze[r1,c1]==1)
	        remove(key);
       else
          { maze[temp->row,temp->coloum]=1;
            remove(key);
            Generate(r1,c1);
          }
   }
}
void Maps::Push(int r,int c,int n)
{  wall *temp1,*temp2;
   temp1=new wall;
   temp2=new wall;
   temp1->row=r;temp1->coloum=c;
   switch(n)
   {  case 1:{ temp2->row=r-1;temp2->coloum=c; };break;
      case 2:{ temp2->row=r+1;temp2->coloum=c; };break;
      case 3:{ temp2->row=r;temp2->coloum=c-1; };break;
      case 4:{ temp2->row=r;temp2->coloum=c+1; };break;
   }
   temp1->neighbor=temp2;
   temp1->next=NULL;
   Add(temp1);
}
void Maps::Initial()
{  srand(int(time(0)));
   for(int i=0;i<R;i++)
	  for(int j=0;j<C;j++)
	   { if(maze[i,j]==0)
        	{ if(int key=rand()%3==2) grid[i,j]=GridState::fixedWall;
	          else grid[i,j]=GridState::Wall;
            }
	     else grid[i,j]=GridState::Blank;
	   }
}
void Maps::Check()                 //检测地图,保证每一行都至少有一个fixedwall,以便于实现近景和远景的遮挡
{ bool mark;
  for(int i=0;i<R;i++)
    { mark=true;
	  for(int j=0;j<C;j++)
	     if(grid[i,j]==GridState::fixedWall)
			 mark=false;
      if(mark) 
		  for(int k=0;k<C;k++)
			  if(maze[i,k]==0)
				  { grid[i,k]=GridState::fixedWall;
	                maze[i,k]=0;
	                mark=false;
					break;
                  }
	  while(mark)
		{ int c=rand()%C;
	      if(i>=1||c>=5)                             //防止fixedwall生成在玩家初始化的地方周围,以免造成玩家无法移动的尴尬
             { grid[i,c]=GridState::fixedWall;
		       maze[i,c]=0;
		       mark=false;
		     }
		}
   }
}
void Add(wall*temp)
{ if(head==NULL)
     head=temp;
  else
   { wall*s;
     s=head;
     while(s->next)
       { s=s->next;}
         s->next=temp;
   }
  counter++;
}
wall*getwall(int n)
{  wall*p=head;
   for(int i=0;i<n;i++)
	  p=p->next;
   return p;
}
void remove(int n)
{ wall*p,*q;
  p=head;
  if(n==0) 
   { q=head;
     head=head->next;
     delete q;
     q=NULL;
   }
  else
  { for(int i=0;i<n-1;i++)
    p=p->next;
    q=p->next;
    p->next=q->next;
    delete q;
    q=NULL;
  }
  counter--;
}