#include "stdafx.h"

//该cpp文件中包含相关的键盘响应事件

using namespace System::Windows::Forms;
using namespace System::Collections;;
using namespace  System::Collections::Generic;

//托管类的句柄不能指向枚举类型,为了创建List泛型类的实例,需要自定义一个新的类型,包含一个Keys枚举类的数据成员
NewKeys::NewKeys(Keys^key1)
{ keys=key1;
}

//重写Object::Equals函数,以保证List的Contain函数能调用Equals对自定义类进行正确判断
bool NewKeys::Equals(Object^obj)  
{ if (obj->GetType()!=this->GetType())         //进行类型比较
             return false;
  NewKeys^other=(NewKeys^)obj;
  return (other->keys->Equals(this->keys));       //调用基类版本的Equals对Keys类型的对象进行比较
}

KeyBoard::KeyBoard()
{ downkeys->Clear();
}
bool KeyBoard::KeyIsDown(Keys^key)       //判断键盘是否按下
{  NewKeys^key1=gcnew NewKeys(key);
   return downkeys->Contains(key1);      //判断链表中是否含有键盘接收到的Keys对象,并以判断结果作为返回值
}
void KeyBoard::KeyRelease(Keys^key)      //松开键盘的响应函数
{  NewKeys^key1=gcnew NewKeys(key);
   if(downkeys->Contains(key1))          //如果链表中包含键盘接收到的Keys对象
      downkeys->Remove(key1);            //把接收到的Keys对象从链表中删除
}
void KeyBoard::KeyDown(Keys^key)         //按下键盘的响应函数
{  NewKeys^key1=gcnew NewKeys(key);
   if(!(downkeys->Contains(key1)))       //如果链表中不包含键盘接收到的Keys对象
       downkeys->Add(key1);              //把接收到的Keys对象存入链表
}