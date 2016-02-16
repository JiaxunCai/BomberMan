// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
#pragma once

// TODO: 在此处引用程序需要的其他头文件

//using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Windows::Forms;

struct wall
{ int row,coloum;
  wall*next,*neighbor;
};

enum PrizeType
{ Power,
  Life,
  Speed,
  Bombers
};
enum Walltype
{ Wall_1,
  Wall_2,
  Wall_3,
  fixedWall_1,
  fixedWall_2,
};

enum class GridState
{ Wall,
  fixedWall,
  Bomb, 
  Blank
};
enum class GameState
{ LevelUp,
  GameOver,
  GamePuase,
  GameNormal,
  ToBoss,
  WithBoss,
  Win
};
enum class Direction
{ Safe,
  UP,
  LEFT,
  RIGHT,
  DOWN
};
enum class FiresType
{ FiresEnd,
  FiresCenter,
  FiresMiddle
};

ref struct Position
{  Position();
   Position(int,int);
   Position(Position%);
   int x,y;
   virtual bool Equals(Object^obj) override;
};
ref struct NewKeys
{  NewKeys(Keys^);
   Keys^keys;
   virtual bool Equals(Object^obj) override;
};
ref struct Maps
{	Maps();
	void Generate(int,int);
	void Initial();
	void Push(int,int,int);
	void Check();
	void Newmaps();
	array<GridState,2>^grid;
	array<int,2>^maze;
};
ref struct wallType
{ wallType();
  wallType(int,int,Walltype);
  void draw(Graphics^g,ImageList^); 
  int r,c;
  Walltype isfix;
};
ref struct KeyBoard
{ KeyBoard();
  bool KeyIsDown(Keys^key);
  void KeyRelease(Keys^key);
  void KeyDown(Keys^key);
  static List<NewKeys^>^downkeys=gcnew List<NewKeys^>();
};
ref struct Collision
{ static bool Isoverlap(Position,Position);
};
ref struct Element abstract
{ Element();
  Element(int,int);
  virtual void draw(Graphics^,ImageList^);
  void move();
  Position pos,cpos;  
  int moveSpeed;
  Direction direction;
};
ref struct Player:Element
{  Player();
   Player(int,int);
   virtual void draw(Graphics^g,ImageList^)override;
   void initial();
   int cnt;
   int bombLimit;
   int fireRange;
   int age;
   bool isDead,mark;
};
ref struct Prize:Element
{ Prize(int,int,PrizeType);
  PrizeType type;
  virtual void draw(Graphics^g,ImageList^)override;
};
ref struct Door:Element
{ Door(int,int);
  virtual void draw(Graphics^,ImageList^)override;
};
ref struct Bombsc:Element
{ Bombsc(int,int);
  virtual void draw(Graphics^,ImageList^)override;
  int bcount;
  int elapse;
  bool Isleave;
};
ref struct Fires:Element
{ Fires(int,int,FiresType,Direction);
  virtual void draw(Graphics^,ImageList^)override;
  int cnt,Elapsed;
  FiresType firestype;
};
ref struct Enemy:Element
{ Enemy(int,int);
  virtual void draw(Graphics^,ImageList^)override;
  int cnt;
  bool isDead,mark;
};
ref struct AI
{ static void Getposition(Element^,int%,int%);
  static void Gets(Maps^);
  static void UpdateAttack(Element^);
  static void UpdateEscape(List<Bombsc^>^,Player^);
  static bool IsDanger(Element^);
  static void Updatepath(int,int);
  static void ChangeDir(Element^,int);
  static bool IsAttack(Element^);
  static Maps^tmap;
  static Queue<Position^>^paths=gcnew Queue<Position^>;
  static int lastX=0;
  static int lastY=0;
  static int tlevel;
  static array<int,2>^Attack=gcnew array<int,2>(15,21);
  static array<Direction,2>^EscapeDir=gcnew array<Direction,2>(15,21);
  static array<Direction,2>^AttackDir=gcnew array<Direction,2>(15,21);
};

ref struct Boss:Element
{ Boss(int,int);
  virtual void draw(Graphics^,ImageList^)override;
  int cnt;
  bool isDead;
  int energy;
  int bulletlimit;
};
ref struct Bullet:Element
{ Bullet(int,int,Direction);
  virtual void draw(Graphics^,ImageList^)override;
};

ref struct Games 
{  Games(Timer^,ImageList^,ImageList^,ImageList^);
   void initialwall(); 
   void Initial_FristState();
   void Initial_BossStage();
   void playerDied();
   void draw(Graphics^);
   void PauseOrResume(bool);
   bool Canmove(Element^);
   void Update();
   void AdjustX(Element^);
   void AdjustY(Element^);
   void Adjust(Element^);
   void CreateBomb();
   void CreateBullet();
   void CreateFires(Bombsc^);
   bool CanCreateBomb(Position);
   void ExplodeBomb(Bombsc^);
   void ChangeDirection(Element^);
   void Playerleave(Bombsc^);
   Maps m;
   KeyBoard keyboard;
   Timer^timer;
   ImageList^imageList_1,^imageList_2,^imageList_3;
   GameState gamestate;
   static List<wallType^>^walls=gcnew List<wallType^>();
   static List<Bombsc^>^bombs=gcnew List<Bombsc^>();
   static List<Fires^>^fires=gcnew List<Fires^>();
   static List<Enemy^>^enemies=gcnew List<Enemy^>();
   static List<Prize^>^prizes=gcnew List<Prize^>();
   static List<Position^>^pos=gcnew List<Position^>();
   static List<Bullet^>^bullets=gcnew List<Bullet^>();
   int level,countofenemy;
   int countofPlayer;
   int countofprize;
   Player^player;
   Door^door;
   Boss^boss;
};

void Add(wall*);
wall*getwall(int);
void remove(int);
void gotoxy(int x, int y,char a);