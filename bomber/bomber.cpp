// bomber.cpp: ����Ŀ�ļ���

#include "stdafx.h"
#include "Form1.h"
#include "Greeting.h"

using namespace bomber;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// �ڴ����κοؼ�֮ǰ���� Windows XP ���ӻ�Ч��
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// ���������ڲ�������
	Application::Run(gcnew Greeting());
	return 0;
}
