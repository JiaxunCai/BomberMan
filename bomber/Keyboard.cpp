#include "stdafx.h"

//��cpp�ļ��а�����صļ�����Ӧ�¼�

using namespace System::Windows::Forms;
using namespace System::Collections;;
using namespace  System::Collections::Generic;

//�й���ľ������ָ��ö������,Ϊ�˴���List�������ʵ��,��Ҫ�Զ���һ���µ�����,����һ��Keysö��������ݳ�Ա
NewKeys::NewKeys(Keys^key1)
{ keys=key1;
}

//��дObject::Equals����,�Ա�֤List��Contain�����ܵ���Equals���Զ����������ȷ�ж�
bool NewKeys::Equals(Object^obj)  
{ if (obj->GetType()!=this->GetType())         //�������ͱȽ�
             return false;
  NewKeys^other=(NewKeys^)obj;
  return (other->keys->Equals(this->keys));       //���û���汾��Equals��Keys���͵Ķ�����бȽ�
}

KeyBoard::KeyBoard()
{ downkeys->Clear();
}
bool KeyBoard::KeyIsDown(Keys^key)       //�жϼ����Ƿ���
{  NewKeys^key1=gcnew NewKeys(key);
   return downkeys->Contains(key1);      //�ж��������Ƿ��м��̽��յ���Keys����,�����жϽ����Ϊ����ֵ
}
void KeyBoard::KeyRelease(Keys^key)      //�ɿ����̵���Ӧ����
{  NewKeys^key1=gcnew NewKeys(key);
   if(downkeys->Contains(key1))          //��������а������̽��յ���Keys����
      downkeys->Remove(key1);            //�ѽ��յ���Keys�����������ɾ��
}
void KeyBoard::KeyDown(Keys^key)         //���¼��̵���Ӧ����
{  NewKeys^key1=gcnew NewKeys(key);
   if(!(downkeys->Contains(key1)))       //��������в��������̽��յ���Keys����
       downkeys->Add(key1);              //�ѽ��յ���Keys�����������
}