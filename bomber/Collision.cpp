#include "stdafx.h"
#include <cmath>

//���ļ��а�����ײ��⺯��

extern int GridSize;
int tolerance=3;          //������ײ�������̶�Ϊ3����

bool Collision::Isoverlap(Position blockpos,Position actorpos)
{  if(abs(blockpos.x-actorpos.x)<GridSize-tolerance && abs(blockpos.y-actorpos.y)<GridSize-tolerance)//������������������Ƚ�
        return true;
   return false;
}