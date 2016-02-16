#include "stdafx.h"

//��cpp�ļ�����Player�ࡢPrize�ࡢBombsc��Ĺ�ͬ����  Element��

extern int GridSize;
int rim=10;                   //rim����������ͼ���ϱ߿������������

Element::Element(){}
Element::Element(int x1,int y1):pos(x1,y1)
{  moveSpeed=2;                      //��ʼ���ƶ��ٶ�
   direction=Direction::DOWN;        //��ʼ������ķ���
   cpos.x=pos.x+GridSize/2;          //cpos���ڴ洢���ǽ�ڡ�ը���Լ��������������꣬�Ա������ײ���
   cpos.y=pos.y+GridSize/2+rim;
}
void Element::draw(Graphics^g,ImageList^){}    //���麯��,ʵ�ֻ�ͼ
void Element::move()                //ʵ�������ƶ�
{ switch(direction)
	{  case Direction::UP : { pos.y-=moveSpeed; cpos.y-=moveSpeed;  break; }   //�����ƶ�
	   case Direction::DOWN : { pos.y+=moveSpeed; cpos.y+=moveSpeed;  break; }   //�����ƶ�
	   case Direction::LEFT : { pos.x-=moveSpeed; cpos.x-=moveSpeed;  break; }   //�����ƶ�
	   case Direction::RIGHT : { pos.x+=moveSpeed; cpos.x+=moveSpeed;  break; }   //�����ƶ�
	}
}