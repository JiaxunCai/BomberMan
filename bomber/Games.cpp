#include "stdafx.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Media;

extern int GridSize;
extern int R,C;
extern int rim;
int extime=50;         //用于控制炸弹爆炸时间
int agetime=50;        //用于控制人物初始化时的一段无敌时间
int firetime=10;

Games::Games(Timer^timer1,ImageList^imagelist1,ImageList^imagelist2,ImageList^imagelist3)
{ player=gcnew Player;
  timer=timer1;
  imageList_1=imagelist1;
  imageList_2=imagelist2;
  imageList_3=imagelist3;
  level=1;
  countofPlayer=5;
  Initial_FristState();
}
void Games::Initial_FristState()
{ initialwall();
  AI::Gets(%m);
  fires->Clear();
  bombs->Clear();
  enemies->Clear();
  prizes->Clear();
  pos->Clear();
  gamestate=GameState::LevelUp;
  countofenemy=3*level+2;
  countofprize=3*level+2;
  int x,y;
  AI::tlevel=level;
  AI::Attack=gcnew array<int,2>(R,C);
  AI::AttackDir=gcnew array<Direction,2>(R,C);
  AI::EscapeDir=gcnew array<Direction,2>(R,C);

  do                     //初始化门的位置
  { x=rand()%C;
	y=rand()%R;
	if(m.grid[y,x]==GridState::Wall)
	  { pos->Add(gcnew Position(x*GridSize, y*GridSize));
		door=gcnew Door(x*GridSize,y*GridSize);
	  }
  } while(m.grid[y,x]!=GridState::Wall);

  do                    //初始化奖励
  { x=rand()%C;
	y=rand()%R;
	Position^temp=gcnew Position(x*GridSize, y*GridSize);
	if(m.grid[y,x]==GridState::Wall&&!pos->Contains(temp))
	  { PrizeType type;
		int randKey=rand()%11;
		switch(randKey)
		  { case 0:  type=Life;    break;
		    case 1:
			case 2:  type=Power;   break;
			case 3:
			case 4:  type=Bombers; break;
			case 5:
			case 6:  type=Speed;   break;
			case 7:  type=Power;   break;
			case 8:  type=Bombers; break;
			case 9:  type=Speed;   break;
			case 10: type=Bombers; break;
		  }
	   pos->Add(temp);
	   prizes->Add(gcnew Prize(x*GridSize,y*GridSize,type));
	  }
  } while(prizes->Count<countofprize);
  int ex,ey;
  while(enemies->Count<countofenemy)
    { ex=rand()%C;
	  ey=rand()%R;
	  if(m.grid[ey,ex]==GridState::Blank&&ex>2&&ey>2)
		  enemies->Add(gcnew Enemy(ex*GridSize,ey*GridSize));
    }
}
void Games::Initial_BossStage()
{ boss=gcnew Boss((C/2)*GridSize,(C/2+3)*GridSize);
  gamestate=GameState::ToBoss;
  bullets->Clear();
  fires->Clear();
  walls->Clear();
  bombs->Clear();
  enemies->Clear();
  prizes->Clear();
  pos->Clear();
  player->age=0;
  player->pos.x=0;
  player->pos.y=0;
  player->cpos.x=GridSize/2;
  player->cpos.y=GridSize/2+rim;
}
void Games::initialwall()
{ walls->Clear();
  for(int i=0;i<R;i++)
  {  for(int j=0;j<C;j++)
      {  if(m.grid[i,j]==GridState::fixedWall)
         {  if(rand()%2==0)   walls->Add(gcnew wallType(i*GridSize,j*GridSize,fixedWall_1));
            else   walls->Add(gcnew wallType(i*GridSize,j*GridSize,fixedWall_2));
         }
       else if(m.grid[i,j]==GridState::Wall)
                { if(rand()%3==0)   walls->Add(gcnew wallType(i*GridSize,j*GridSize,Wall_1));
				  else 
				   { if(rand()%3==1)   walls->Add(gcnew wallType(i*GridSize,j*GridSize,Wall_2));
				     else  walls->Add(gcnew wallType(i*GridSize,j*GridSize,Wall_3));
				   }
                }
       }
  }
}
void Games::playerDied()
{ countofPlayer--;
  if (countofPlayer>0)
	{ player->age=0;
	  player->pos.x=0;
	  player->pos.y=0;
	  player->cpos.x=GridSize/2;
	  player->cpos.y=GridSize/2+rim;
      player->isDead = false;
	}
	else gamestate=GameState::GameOver;

}
void Games::draw(Graphics^g)
{ if (gamestate==GameState::LevelUp)
	{   SolidBrush ^ActiveBursh = gcnew SolidBrush(Color::Black);
	    SolidBrush ^WhiteBrush = gcnew SolidBrush(Color::White);
	    Font ^TitleFont = gcnew Font("Arial Black", 28);
	    Font ^LargeFont = gcnew Font("黑体", 14);
		String ^title = "  LEVEL  "+level.ToString();
		g->DrawString(title,TitleFont,ActiveBursh,float((C/2)*GridSize-120),float((R/2)*GridSize-30));
		String ^tip = "Enter to contiue..";
		g->DrawString(tip,LargeFont,WhiteBrush,400,float((R)*GridSize-30));
		return;
	}
 if (gamestate==GameState::ToBoss)
	{   SolidBrush ^ActiveBursh = gcnew SolidBrush(Color::Black);
	    SolidBrush ^WhiteBrush = gcnew SolidBrush(Color::White);
	    Font ^TitleFont = gcnew Font("Arial Black", 36);
	    Font ^LargeFont = gcnew Font("黑体", 14);
		String ^title = "  BOSS  ";
		g->DrawString(title,TitleFont,ActiveBursh,float((C/2)*GridSize-120),float((R/2)*GridSize-30));
		String ^dialog="居然能闯到这里来... \n \n颤抖吧，愚蠢的人类啊！";
		g->DrawString(dialog,LargeFont,WhiteBrush,float((C/2)*GridSize-120),float((R/2)*GridSize+50));
		String ^tip = "Enter to contiue..";
		g->DrawString(tip,LargeFont,WhiteBrush,450,float((R)*GridSize-20));
		return;
	}
  if (gamestate==GameState::GameOver)
	{   SolidBrush ^ActiveBursh = gcnew SolidBrush(Color::Black);
	    SolidBrush ^WhiteBrush = gcnew SolidBrush(Color::White);
	    Font ^TitleFont = gcnew Font("Arial Black", 28);
	    Font ^LargeFont = gcnew Font("黑体", 14);
		String ^title = "  Game Over  ";
		g->DrawString(title,TitleFont,ActiveBursh,float((C/2)*GridSize-150),float((R/2)*GridSize-30));
		String ^tip = "Enter to contiue..";
		g->DrawString(tip,LargeFont,WhiteBrush,400,float((R)*GridSize-30));
		return;
	}
    if (gamestate==GameState::Win)
	{   SolidBrush ^ActiveBursh = gcnew SolidBrush(Color::Black);
	    Font ^TitleFont = gcnew Font("Arial Black", 28);
		String ^title = "  You Win !  ";
		g->DrawString(title,TitleFont,ActiveBursh,float((C/2)*GridSize-150),float((R/2)*GridSize-30));
		return;
	}
  if(gamestate==GameState::GameNormal)
   { player->mark=true;
     for(int i=0;i<enemies->Count;i++)
	    enemies[i]->mark=true;
     for each (Prize^prize in prizes)
        prize->draw(g,imageList_1);                //画奖励
  
     door->draw(g,imageList_3);                     //画门
  
    for(int i=0;i<fires->Count;i++)
       {  if(fires[i]->Elapsed < firetime)
		      fires[i]->draw(g,imageList_2);
	      else fires->RemoveAt(i--);            //如果fires中某个元素所经历的时间超过Fire最长的生存时间删除该元素
      }

    for (int i=0;i<bombs->Count;i++)
      { int x=bombs[i]->pos.x/GridSize;
	    int y=bombs[i]->pos.y/GridSize;
	    if (m.grid[y,x]==GridState::Bomb)
		   bombs[i]->draw(g,imageList_3);
	    else bombs->RemoveAt(i--);                    //如果墙bombs某个元素所占格子不应该是bomb则删除该元素
     }
   for(int i=0;i<walls->Count;i++)
      { int x=(walls[i]->c)/GridSize;
        int y=(walls[i]->r)/GridSize;

	    if(player->pos.y>=walls[i]->r-GridSize&&player->pos.y<walls[i]->r&&!player->isDead)   
		    if(player->mark)
		       { player->draw(g,imageList_1);
	             player->mark=false; 
	           }

	    for(int j=0;j<enemies->Count;j++)
	     { if(!enemies[j]->isDead)
	         { if(enemies[j]->pos.y>=walls[i]->r-GridSize&&enemies[j]->pos.y<walls[i]->r&&enemies[j]->mark)
			      { enemies[j]->draw(g,imageList_3);
	                enemies[j]->mark=false;
	              }
	         }
		  else enemies->RemoveAt(j--);    //如果enemies中某个元素isDead的值为真删除该元素
  	    }

		if(m.grid[y,x]==GridState::fixedWall||m.grid[y,x]==GridState::Wall)
			walls[i]->draw(g,imageList_1);
		else { walls->RemoveAt(i--); continue;}

		if(walls[i]->r==(R-1)*GridSize&&player->pos.y>=(R-1)*GridSize&&!player->isDead)
			if(player->mark)
		       { player->draw(g,imageList_1);
	             player->mark=false; 
	           }

	for(int j=0;j<enemies->Count;j++)
        { if(!enemies[j]->isDead)
		    {if(enemies[j]->pos.y>=(R-1)*GridSize&&walls[i]->r==(R-1)*GridSize&&enemies[j]->mark)
			    { enemies[j]->draw(g,imageList_3);
	              enemies[j]->mark=false;
	            }
	      }
	   else  enemies->RemoveAt(j--);
	   }
    }

  for(int i=0;i<prizes->Count;i++)
    { if(Collision::Isoverlap(player->cpos,prizes[i]->cpos))
	    { if(prizes[i]->type==Speed)
			  player->moveSpeed++;
		  else if(prizes[i]->type==Bombers)
			  player->bombLimit++;
		  else if(prizes[i]->type==Power)
			  player->fireRange++;
		  else if(prizes[i]->type==Life)
			  countofPlayer++;
		  prizes->RemoveAt(i);
		  SoundPlayer^sp1=gcnew SoundPlayer;
		  sp1->SoundLocation=".\\Release\\X08_01.wav";
		  sp1->LoadAsync();
		  sp1->Play();
	    }
    }
   }
  if(gamestate==GameState::WithBoss)
  { for(int i=0;i<fires->Count;i++)
       {  if(fires[i]->Elapsed < firetime)
		      fires[i]->draw(g,imageList_2);
	      else fires->RemoveAt(i--);            //如果fires中某个元素所经历的时间超过Fire最长的生存时间删除该元素
      }

    for(int i=0;i<bombs->Count;i++)
      { int x=bombs[i]->pos.x/GridSize;
	    int y=bombs[i]->pos.y/GridSize;
	    if (m.grid[y,x]==GridState::Bomb)
		   bombs[i]->draw(g,imageList_3);
	    else bombs->RemoveAt(i--);                    //如果墙bombs某个元素所占格子不应该是bomb则删除该元素
     }
	for each(Bullet^bullet in bullets)
		bullet->draw(g,imageList_3);
	player->draw(g,imageList_1);
    boss->draw(g,imageList_3);
	
  }
}
void Games::PauseOrResume(bool enable)
{	timer->Enabled = enable;
}
void Games::AdjustX(Element ^element)
{ if (element->pos.x % GridSize > GridSize/2)
    {  int adjustment=GridSize-element->pos.x % GridSize;
        element->pos.x+=adjustment;
        element->cpos.x+=adjustment;
    }
else
   {  int adjustment=element->pos.x % GridSize;
      element->pos.x-=adjustment;
      element->cpos.x-=adjustment;
   }
}
void Games::AdjustY(Element ^element)
{ if (element->pos.y % GridSize > GridSize/2)
    {  int adjustment=GridSize-element->pos.y % GridSize;
        element->pos.y+=adjustment;
        element->cpos.y+=adjustment;
    }
else
    {  int adjustment=element->pos.y % GridSize;
       element->pos.y-=adjustment;
       element->cpos.y-=adjustment;
    }
}
void Games::Adjust(Element ^element)
{  switch (element->direction)
      { case Direction::DOWN :
                    AdjustX(element);
                    break;
	    case Direction::LEFT :
                    AdjustY(element);
                    break;
		case Direction::RIGHT :
                    AdjustY(element);
                    break;
		case Direction::UP :
                    AdjustX(element);
                    break;
      }
}
bool Games::Canmove(Element^element)
{ Position newpos(element->pos.x,element->pos.y),newcpos(element->cpos.x,element->cpos.y);
  bool canmove=true;
  switch (element->direction)
  { case Direction::UP : { newpos.y-=element->moveSpeed; newcpos.y-=element->moveSpeed;  break; }
    case Direction::DOWN : { newpos.y+=element->moveSpeed; newcpos.y+=element->moveSpeed;  break; }
	case Direction::LEFT : { newpos.x-=element->moveSpeed; newcpos.x-=element->moveSpeed;  break; }
	case Direction::RIGHT : { newpos.x+=element->moveSpeed; newcpos.x+=element->moveSpeed;  break; }
  }
  if (newcpos.x<GridSize/2||newcpos.y<GridSize/2+rim||((C-1)*GridSize+GridSize/2)<newcpos.x||
	  ((R-1)*GridSize+GridSize/2)+rim<newcpos.y)//确保移动物体在迷宫内
	  canmove=false;
  for each(wallType^awall in walls )
    { Position temp(awall->c+GridSize/2,awall->r+GridSize/2+rim);
	  if(Collision::Isoverlap(temp,newcpos))//是否与墙体发生碰撞;
		  canmove=false;
    }
  for each(Bombsc^bomb1 in bombs)
	{ if(bomb1->Isleave&&Collision::Isoverlap(bomb1->cpos,newcpos))
		  canmove=false;
  }

  Adjust(element);
  return canmove;
}
bool Games::CanCreateBomb(Position pos)
{  int x=pos.x/GridSize;
   int y=pos.y/ GridSize;
   if (m.grid[y,x]==GridState::Blank)
	  { m.grid[y,x]=GridState::Bomb;
		return true;
	  }
   return false;
}
void Games::CreateBomb()
{  int x,y;
   x=player->pos.x;
   y=player->pos.y;
   Bombsc ^newBomb=gcnew Bombsc(x,y);
   AdjustX(newBomb);
   AdjustY(newBomb);                       //修正炸弹的位置
   if(CanCreateBomb(newBomb->pos))
	  {  bombs->Add(newBomb);
		 SoundPlayer^sp2=gcnew SoundPlayer;
		 sp2->SoundLocation=".\\Release\\X09_01.wav";
		 sp2->LoadAsync();
		 sp2->Play();
	  }
}
void Games::CreateBullet()
{  int x,y;
   x=boss->pos.x;
   y=boss->pos.y;
   Bullet ^newBullet=gcnew Bullet(x,y,boss->direction);
   AdjustX(newBullet);
   AdjustY(newBullet);                       //修正炸弹的位置
   bullets->Add(newBullet);
   SoundPlayer^sp2=gcnew SoundPlayer;
   sp2->SoundLocation=".\\Release\\fly.wav";
   sp2->LoadAsync();
   sp2->Play();
}
void Games::CreateFires(Bombsc^bomb)
{ int x=bomb->pos.x/GridSize;
  int y=bomb->pos.y/GridSize;
  m.grid[y,x]=GridState::Blank;
  int i;
  FiresType type1;
  fires->Add(gcnew Fires(x*GridSize,y*GridSize,FiresType::FiresCenter,Direction::UP));    //中心位置的火花
  for(i=1;i<=player->fireRange&&y-i>=0;i++)             //向上延伸的火花
   { if(m.grid[y-i,x]==GridState::fixedWall)
         break;
	 if(y-i-1>=0&&m.grid[y-i-1,x]==GridState::fixedWall)
       { fires->Add(gcnew Fires(x*GridSize,(y-i)*GridSize,FiresType::FiresEnd,Direction::UP));
	     if(m.grid[y-i,x]==GridState::Wall)   m.grid[y-i,x]=GridState::Blank;
		 break;
       }
     else if(m.grid[y-i,x]==GridState::Wall)
            { m.grid[y-i,x]=GridState::Blank;
              fires->Add(gcnew Fires(x*GridSize,(y-i)*GridSize,FiresType::FiresEnd,Direction::UP));
              break;
            }
     if(i==player->fireRange||y-i==0)
		 type1=FiresType::FiresEnd;
	 else  type1=FiresType::FiresMiddle;
     fires->Add(gcnew Fires(x*GridSize,(y-i)*GridSize,type1,Direction::UP));          
   }

  for(i=1;i<=player->fireRange&&y+i<R;i++)             //向下延伸的火花
   { if(m.grid[y+i,x]==GridState::fixedWall)
        break;
  	 if(y+i+1<R &&m.grid[y+i+1,x]==GridState::fixedWall)
       { fires->Add(gcnew Fires(x*GridSize,(y+i)*GridSize,FiresType::FiresEnd,Direction::DOWN));
	     if(m.grid[y+i,x]==GridState::Wall)     m.grid[y+i,x]=GridState::Blank;
		 break;
       }
     else if(m.grid[y+i,x]==GridState::Wall)
            { m.grid[y+i,x]=GridState::Blank;
              fires->Add(gcnew Fires(x*GridSize,(y+i)*GridSize,FiresType::FiresEnd,Direction::DOWN));
              break;
            }
	 if(i==player->fireRange||y+i==(R-1))
		 type1=FiresType::FiresEnd;
	 else  type1=FiresType::FiresMiddle;
     fires->Add(gcnew Fires(x*GridSize,(y+i)*GridSize,type1,Direction::DOWN));    
            }

  for(i=1;i<=player->fireRange&&x-i>=0;i++)             //向左延伸的火花
   { if(m.grid[y,x-i]==GridState::fixedWall)
        break;
     if(x-i-1>=0&&m.grid[y,x-i-1]==GridState::fixedWall)
       { fires->Add(gcnew Fires((x-i)*GridSize,y*GridSize,FiresType::FiresEnd,Direction::LEFT));
	     if(m.grid[y,x-i]==GridState::Wall)   m.grid[y,x-i]=GridState::Blank;
		 break;
       }
     else if(m.grid[y,x-i]==GridState::Wall)
            { m.grid[y,x-i]=GridState::Blank;
              fires->Add(gcnew Fires((x-i)*GridSize,y*GridSize,FiresType::FiresEnd,Direction::LEFT));
              break;
            }
	 if(i==player->fireRange||x-i==0)
		 type1=FiresType::FiresEnd;
	 else  type1=FiresType::FiresMiddle;
	 fires->Add(gcnew Fires((x-i)*GridSize,y*GridSize,type1,Direction::LEFT));     
   }

   for(i=1;i<=player->fireRange&&x+i<C;i++)             //向右延伸的火花
     { if(m.grid[y,x+i]==GridState::fixedWall)
          break;
       if(x+i+1<C &&m.grid[y,x+i+1]==GridState::fixedWall)
       {  fires->Add(gcnew Fires((x+i)*GridSize,y*GridSize,FiresType::FiresEnd,Direction::RIGHT));
	      if(m.grid[y,x+i]==GridState::Wall)     m.grid[y,x+i]=GridState::Blank;
		  break;
       }
       else if(m.grid[y,x+i]==GridState::Wall)
            { m.grid[y,x+i]=GridState::Blank;
              fires->Add(gcnew Fires((x+i)*GridSize,y*GridSize,FiresType::FiresEnd,Direction::RIGHT));
              break;
            }
	  if(i==player->fireRange||x+i==(C-1))
		 type1=FiresType::FiresEnd;
	  else  type1=FiresType::FiresMiddle;
	  fires->Add(gcnew Fires((x+i)*GridSize,y*GridSize,type1,Direction::RIGHT));     
   }

}
void Games::ExplodeBomb(Bombsc^bomb)//引爆炸弹CreateFire并且进行火花与player，enemies,bombs进行碰撞检测
{ CreateFires(bomb);
  for each (Fires^fire in fires)       //player 与火花间进行碰撞检测
	{ if(Collision::Isoverlap(player->cpos,fire->cpos) && player->age>= agetime)
			playerDied();
		for each (Enemy^enemy in enemies)
			if(Collision::Isoverlap(enemy->cpos,fire->cpos))
				enemy->isDead = true;
		    if(gamestate==GameState::WithBoss)
				if(Collision::Isoverlap(boss->cpos,fire->cpos))
				   { boss->energy--;
				     if(boss->energy==0)
						 boss->isDead=true;
				   }
			for each (Bombsc^tbomb in bombs)
				if (tbomb->elapse<extime  && Collision::Isoverlap(tbomb->cpos, fire->cpos))
					tbomb->elapse=extime+1;
	   SoundPlayer^sp1=gcnew SoundPlayer;
	   sp1->SoundLocation=".\\Release\\X10_01.wav";
	   sp1->LoadAsync();
	   sp1->Play();
   }
}
void Games::ChangeDirection(Element^enemy)
{ int k=rand()%4;
  switch(k)
    { case 0: enemy->direction=Direction::UP;  break;
	  case 1: enemy->direction=Direction::DOWN;  break;
	  case 2: enemy->direction=Direction::LEFT;  break;
	  case 3: enemy->direction=Direction::RIGHT;  break;
    }
}
void Games::Playerleave(Bombsc ^bomb)
{ if(abs(player->cpos.x-bomb->cpos.x)>GridSize || abs(player->cpos.y-bomb->cpos.y)>GridSize)
     bomb->Isleave=true;
}

void Games::Update()
{ if(gamestate==GameState::LevelUp)
      if(keyboard.KeyIsDown(Keys::Enter))
      { gamestate=GameState::GameNormal;
      }
  if(gamestate==GameState::ToBoss)
	 if(keyboard.KeyIsDown(Keys::Enter))
	  { gamestate=GameState::WithBoss;
      }
  if(gamestate==GameState::GameOver)
     { if(keyboard.KeyIsDown(Keys::Enter))
          { player->initial();
  		    level=1;
            countofPlayer=5;
		    m.Newmaps();
		    Initial_FristState();
          }
      }

  if(gamestate==GameState::GameNormal)
    {  if(player->age<=agetime) player->age++;
       if(keyboard.KeyIsDown(Keys::Left))
	      {   player->direction=Direction::LEFT;
	          if(Canmove(player))
				  player->move();
          }
	   if(keyboard.KeyIsDown(Keys::Right))
	      {   player->direction=Direction::RIGHT;
	          if(Canmove(player))
				  player->move();
          }
	   if(keyboard.KeyIsDown(Keys::Up))
	      {   player->direction=Direction::UP;
	          if(Canmove(player))
				  player->move();
          }
	   if(keyboard.KeyIsDown(Keys::Down))
	      {   player->direction=Direction::DOWN;
	          if(Canmove(player))
				  player->move();
          }
	   if (keyboard.KeyIsDown(Keys::Space) && bombs->Count < player->bombLimit)
		   CreateBomb();
  
	  for each (Bombsc^bomb in bombs)
		if(bomb->Isleave==false)
		  Playerleave(bomb);

      for each (Bombsc^bomb in bombs)
        {  bomb->elapse++;
	       if(bomb->elapse > extime)
		       ExplodeBomb(bomb);
        }
  
     for  each (Fires^fire in fires)
	      fire->Elapsed++;

     AI::UpdateEscape(bombs,player);
     AI::UpdateAttack(player);
  
    for each (Enemy^enemy in enemies)
    { if (!enemy->isDead)
	  { if(AI::IsDanger(enemy))           //如果在危险的区域内先躲避炸弹
		    { AI::ChangeDir(enemy,1);
			  if (Canmove(enemy))
				  enemy->move();
		    }
		 else if(AI::IsAttack(enemy))              //如果和player的距离在一定范围内则追踪player
		       { AI::ChangeDir(enemy,2);
			     Adjust(enemy);
			     enemy->move();
		       }
		      else                      //否则自由活动
		       { if (Canmove(enemy))
			       { enemy->move();
				     int random=rand()%70;
				     if(random==5)
					 ChangeDirection(enemy);
			       }
			  else ChangeDirection(enemy);
		  }
		  if (player->age >= agetime && Collision::Isoverlap(enemy->cpos, player->cpos))//碰撞检测
			  playerDied();
	  }
    }

	if(enemies->Count==0 && Collision::Isoverlap(player->cpos,door->cpos))
	{ level++;
	  if(level <= 3)
		{ player->age=0;
		  player->pos.x=0;
		  player->pos.y=0;
		  player->cpos.x=GridSize/2;
		  player->cpos.y=GridSize/2+rim;
          gamestate=GameState::LevelUp;
		  m.Newmaps();
		  Initial_FristState();
		}
	  else
	   { Initial_BossStage();
	   }
   }
  }
  if(gamestate==GameState::WithBoss)
  { if(player->age<=agetime) player->age++;
       if(keyboard.KeyIsDown(Keys::Left))
	      {   player->direction=Direction::LEFT;
	          if(Canmove(player))
				  player->move();
          }
	   if(keyboard.KeyIsDown(Keys::Right))
	      {   player->direction=Direction::RIGHT;
	          if(Canmove(player))
				  player->move();
          }
	   if(keyboard.KeyIsDown(Keys::Up))
	      {   player->direction=Direction::UP;
	          if(Canmove(player))
				  player->move();
          }
	   if(keyboard.KeyIsDown(Keys::Down))
	      {   player->direction=Direction::DOWN;
	          if(Canmove(player))
				  player->move();
          }
	   if (keyboard.KeyIsDown(Keys::Space) && bombs->Count < player->bombLimit)
		   CreateBomb();
  
	  for each (Bombsc^bomb in bombs)
		if(bomb->Isleave==false)
		  Playerleave(bomb);

      for each (Bombsc^bomb in bombs)
        {  bomb->elapse++;
	       if(bomb->elapse > extime)
		       ExplodeBomb(bomb);
        }
  
     for  each (Fires^fire in fires)
	      fire->Elapsed++; 
	 AI::UpdateEscape(bombs,player);
     AI::UpdateAttack(player);

    if (!boss->isDead)
	  { if(AI::IsDanger(boss))           //如果在危险的区域内先躲避炸弹
		    { AI::ChangeDir(boss,1);
			  if (Canmove(boss))
				  boss->move();
		    }
		else if(AI::IsAttack(boss))              //如果和player的距离在一定范围内则追踪player
		       { AI::ChangeDir(boss,2);
			     Adjust(boss);
			     boss->move();
				 if(bullets->Count < boss->bulletlimit&&rand()%30==0)
					 CreateBullet();
		       }
		      else                      //否则自由活动
		       { if(Canmove(boss))
			       { boss->move();
				     int random=rand()%70;
				     if(random==5)
					 ChangeDirection(boss);
					 if(rand()%50==0&&bullets->Count < boss->bulletlimit)
			             CreateBullet();
		           }
			     else ChangeDirection(boss);
		       }
	  }
   else   gamestate=GameState::Win;
   for(int i=0;i<bullets->Count;i++)
	   { if(Canmove(bullets[i]))
		     bullets[i]->move();
	    else bullets->RemoveAt(i--);
       }
   for(int i=0;i<bullets->Count;i++) 
	  { if(Collision::Isoverlap(player->cpos,bullets[i]->cpos) && player->age>= agetime)
		   { playerDied();
             bullets->RemoveAt(i--);
           }
        for each (Bombsc^tbomb in bombs)
			if(tbomb->elapse<extime  && Collision::Isoverlap(tbomb->cpos, bullets[i]->cpos))
			   { tbomb->elapse=extime+1;
		         bullets->RemoveAt(i--);
		       }
	 }
  }
}
