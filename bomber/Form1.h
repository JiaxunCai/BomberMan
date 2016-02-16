#pragma once

#include <ctime>
#include <stdlib.h>
#include "stdafx.h"
extern int R,C;

namespace bomber {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
			games=gcnew Games(timer1,imageList1,imageList2,imageList3);
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::ImageList^  imageList2;
	private: System::Windows::Forms::ImageList^  imageList3;

	protected: 

	protected: 
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->imageList2 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->imageList3 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 40;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"fixedwall_1.png");
			this->imageList1->Images->SetKeyName(1, L"fixedwall_2.png");
			this->imageList1->Images->SetKeyName(2, L"wall_1.png");
			this->imageList1->Images->SetKeyName(3, L"wall_2.png");
			this->imageList1->Images->SetKeyName(4, L"wall_3.png");
			this->imageList1->Images->SetKeyName(5, L"playerD_1.png");
			this->imageList1->Images->SetKeyName(6, L"playerD_2.png");
			this->imageList1->Images->SetKeyName(7, L"playerD_3.png");
			this->imageList1->Images->SetKeyName(8, L"playerL_1.png");
			this->imageList1->Images->SetKeyName(9, L"playerL_2.png");
			this->imageList1->Images->SetKeyName(10, L"playerL_3.png");
			this->imageList1->Images->SetKeyName(11, L"playerR_1.png");
			this->imageList1->Images->SetKeyName(12, L"playerR_2.png");
			this->imageList1->Images->SetKeyName(13, L"playerR_3.png");
			this->imageList1->Images->SetKeyName(14, L"playerU_1.png");
			this->imageList1->Images->SetKeyName(15, L"playerU_2.png");
			this->imageList1->Images->SetKeyName(16, L"playerU_3.png");
			this->imageList1->Images->SetKeyName(17, L"Life.png");
			this->imageList1->Images->SetKeyName(18, L"bomb.png");
			this->imageList1->Images->SetKeyName(19, L"power.png");
			this->imageList1->Images->SetKeyName(20, L"speed.png");
			// 
			// imageList2
			// 
			this->imageList2->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList2.ImageStream")));
			this->imageList2->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList2->Images->SetKeyName(0, L"explodeC_1.png");
			this->imageList2->Images->SetKeyName(1, L"explodeC_2.png");
			this->imageList2->Images->SetKeyName(2, L"explodeC_3.png");
			this->imageList2->Images->SetKeyName(3, L"explodeD_1.png");
			this->imageList2->Images->SetKeyName(4, L"explodeD_2.png");
			this->imageList2->Images->SetKeyName(5, L"explodeD_3.png");
			this->imageList2->Images->SetKeyName(6, L"explodeDE_1.png");
			this->imageList2->Images->SetKeyName(7, L"explodeDE_2.png");
			this->imageList2->Images->SetKeyName(8, L"explodeDE_3.png");
			this->imageList2->Images->SetKeyName(9, L"explodeDE_4.png");
			this->imageList2->Images->SetKeyName(10, L"explodeL_1.png");
			this->imageList2->Images->SetKeyName(11, L"explodeL_2.png");
			this->imageList2->Images->SetKeyName(12, L"explodeL_3.png");
			this->imageList2->Images->SetKeyName(13, L"explodeLE_1.png");
			this->imageList2->Images->SetKeyName(14, L"explodeLE_2.png");
			this->imageList2->Images->SetKeyName(15, L"explodeLE_3.png");
			this->imageList2->Images->SetKeyName(16, L"explodeLE_4.png");
			this->imageList2->Images->SetKeyName(17, L"explodeR_1.png");
			this->imageList2->Images->SetKeyName(18, L"explodeR_2.png");
			this->imageList2->Images->SetKeyName(19, L"explodeR_3.png");
			this->imageList2->Images->SetKeyName(20, L"explodeRE_1.png");
			this->imageList2->Images->SetKeyName(21, L"explodeRE_2.png");
			this->imageList2->Images->SetKeyName(22, L"explodeRE_3.png");
			this->imageList2->Images->SetKeyName(23, L"explodeRE_4.png");
			this->imageList2->Images->SetKeyName(24, L"explodeU_1.png");
			this->imageList2->Images->SetKeyName(25, L"explodeU_2.png");
			this->imageList2->Images->SetKeyName(26, L"explodeU_3.png");
			this->imageList2->Images->SetKeyName(27, L"explodeUE_1.png");
			this->imageList2->Images->SetKeyName(28, L"explodeUE_2.png");
			this->imageList2->Images->SetKeyName(29, L"explodeUE_3.png");
			this->imageList2->Images->SetKeyName(30, L"explodeUE_4.png");
			// 
			// imageList3
			// 
			this->imageList3->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList3.ImageStream")));
			this->imageList3->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList3->Images->SetKeyName(0, L"bomb_3.png");
			this->imageList3->Images->SetKeyName(1, L"bomb_2.png");
			this->imageList3->Images->SetKeyName(2, L"bomb_1.png");
			this->imageList3->Images->SetKeyName(3, L"enemyD_1.png");
			this->imageList3->Images->SetKeyName(4, L"enemyD_2.png");
			this->imageList3->Images->SetKeyName(5, L"enemyD_3.png");
			this->imageList3->Images->SetKeyName(6, L"enemyL_1.png");
			this->imageList3->Images->SetKeyName(7, L"enemyL_2.png");
			this->imageList3->Images->SetKeyName(8, L"enemyL_3.png");
			this->imageList3->Images->SetKeyName(9, L"enemyR_1.png");
			this->imageList3->Images->SetKeyName(10, L"enemyR_2.png");
			this->imageList3->Images->SetKeyName(11, L"enemyR_3.png");
			this->imageList3->Images->SetKeyName(12, L"enemyU_1.png");
			this->imageList3->Images->SetKeyName(13, L"enemyU_2.png");
			this->imageList3->Images->SetKeyName(14, L"enemyU_3.png");
			this->imageList3->Images->SetKeyName(15, L"door.png");
			this->imageList3->Images->SetKeyName(16, L"BossD_1.png");
			this->imageList3->Images->SetKeyName(17, L"BossD_2.png");
			this->imageList3->Images->SetKeyName(18, L"BossD_3.png");
			this->imageList3->Images->SetKeyName(19, L"BossL_1.png");
			this->imageList3->Images->SetKeyName(20, L"BossL_2.png");
			this->imageList3->Images->SetKeyName(21, L"BossL_3.png");
			this->imageList3->Images->SetKeyName(22, L"BossR_1.png");
			this->imageList3->Images->SetKeyName(23, L"BossR_2.png");
			this->imageList3->Images->SetKeyName(24, L"BossR_3.png");
			this->imageList3->Images->SetKeyName(25, L"BossU_1.png");
			this->imageList3->Images->SetKeyName(26, L"BossU_2.png");
			this->imageList3->Images->SetKeyName(27, L"BossU_3.png");
			this->imageList3->Images->SetKeyName(28, L"BulletD.png");
			this->imageList3->Images->SetKeyName(29, L"BulletL.png");
			this->imageList3->Images->SetKeyName(30, L"BulletR.png");
			this->imageList3->Images->SetKeyName(31, L"BulletU.png");
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Highlight;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(630, 461);
			this->DoubleBuffered = true;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"超级炸弹人";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 games->draw(e->Graphics);
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				games->Update();
				Refresh();
			 }
			 Games ^games;
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 games->keyboard.KeyDown(e->KeyCode);
				 if(games->keyboard.KeyIsDown(Keys::R) && games->gamestate==GameState::GamePuase)
				   { games->gamestate=GameState::GameNormal;
					 games->PauseOrResume(true);
				   }
				 if(games->keyboard.KeyIsDown(Keys::P))
				   { games->gamestate=GameState::GamePuase;
					 games->PauseOrResume(false);
				   }
			 }
	private: System::Void Form1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 games->keyboard.KeyRelease(e->KeyCode);
			 }
	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 Application::Exit();
			 }
	};
}

