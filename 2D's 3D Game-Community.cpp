#include <bits/stdc++.h>
#include <random>
#include <conio.h>
#include <windows.h>
#include "hashPD.h"
#include "randomPD.h"
#define ptf printf
#define ent printf("\n");
#define i_input _color(14);printf(">");_color();
using namespace std;
int m,n,f,s,x,y,cc,oo,bir,fin,birx,biry,birx1,biry1,finx,finy,tp,ttp,_d,steps,map_style,deepseek=2,max_wide=1;
int a[1000][1000];//地图,上下左右四周都有-1环绕(便于判定越界行为),左上角为1,1,右下角为m,n
int amap[1000][1000];//地图副本
bool b[1000][1000],bb[1000][1000],bd[3][3];//查询地图可走位置
bool visited[1000][1000];
bool imm[1000][1000],immd[3][3];
int cl[]={0,160,224,240,159,176,207};//当前位置颜色
short cll[10][10];//多彩模式,前一个代表地图最高点的颜色样式,后一个是对应高度的颜色
int savx[10],savy[10],savstep[10],ma=-9,maa=-9,mi=9;//存档和地图最高点、小于10的最高点
char z;//读入的键
char W='w',A='a',S='s',D='d',Q='q',E='e',Z='z',C='c';//键位
bool __E,__C,__A,__I,__T,__D,__X,_X,_GUI,_anyway,_hid,fr;//_X显示坐标
string userIDPath,mapPath,playerswords,mapswords,originalMapOHash,raceDataPath,raceDataHash;
bool mapPassed=false,disWMIC=false;
string mapPasswd,mapPasswdHash;
int beststep;
char _x1[100000]=".\\map\\",_x2[100000];
char _xx1[100000]=".\\user\\",_xx2[100000];
long long unixunix0,unixunix1;
double msms,msms0;
ifstream finnn;
ifstream playerswordsin(".\\+set\\playerswords.txt");
streambuf* originalCinBuffer=cin.rdbuf();
string tptp;
string ttemp;
string winRoadA="",winRoad="";//有效winRoadA, 原始winRoad
string nameee="2D's 3D Game Plus",verrr="4.3(Community)";

//0 RACE
//1 RACE-DARK
//2 NORMAL
//3 NORMAL-DARK
//4 EASY
//5 EASY-DARK
//6 FUN
//7 X
struct STR
{
	string str;
};
void _color(int __c=7)//着色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),__c);
}
bool windAsk(const char* title,const char* mess)//弹出对话框
{
	int xx=MessageBox(NULL, mess, title, MB_YESNO | MB_ICONQUESTION);
	return xx==IDYES;
}
void windTitle(string t1)//修改标题为t1
{
	SetConsoleTitle(t1.c_str());
	return;
}
int hex_to_10(char a)
{
	if(a>='0' and a<='9')return a-'0';
	a=tolower(a);
	return a-'a'+10;
}
string getCurrentTimeString(bool _ms=true) 
{
	time_t now = time(nullptr);
	tm* localTime = localtime(&now);
	
	ostringstream oss;
	oss << put_time(localTime,"%Y-%m-%d %H:%M:%S");
	if(_ms)
	{
		auto now = chrono::system_clock::now();
		auto ms = chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())%1000;
		oss<<"."<<setw(3)<<setfill('0')<<ms.count();
		return oss.str();
	}
	return oss.str();
}
string getCurrentTimeString4Report() 
{
	time_t now = time(nullptr);
	tm* localTime = localtime(&now);
	
	ostringstream oss;
	oss << put_time(localTime, "%Y-%m-%d_%H-%M-%S");
	return oss.str();
}
bool isNonASCII(const string& filePath)
{
	// 以二进制模式打开文件，确保正确读取所有字节
	ifstream file(filePath, ios::binary);
	if (!file.is_open())
	{
		// 文件打开失败，这里选择返回false，你也可以根据需要修改为其他处理方式
		return false;
	}
	
	char c;
	while (file.get(c))
	{
		unsigned char uc = static_cast<unsigned char>(c);
		// 检查字符是否不在ASCII可见字符范围内(32-126)
		if (uc < 32 || uc > 126)
		{
			return true; // 发现非ASCII可见字符
		}
	}
	
	return false; // 所有字符都是ASCII可见字符
}
void err_wrong_input()
{
	ptf("十分错误的输入。\n");
	return;
}
void err_out_of_map()
{
	_color(207);
	ptf("OUT OF MAP!!!已经超出边界!!!\n");
	_color();
	system("pause");
	return;
}
void err_cant_go()
{
	_color(207);
	ptf("YOU CANNOT DO THIS!!!禁止通行!!!\n");
	_color();
	system("pause");
	return;
}
string getEXEPath()//返回本程序路径,带本程序名
{
	char buffer[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return string(buffer);
}
string getEXEPathO()//返回本程序路径,不带本程序名
{
	string fullPath = getEXEPath();
	size_t lastSlashPos = fullPath.find_last_of("\\/");
	if (lastSlashPos != string::npos)
	{
		return fullPath.substr(0, lastSlashPos);
	}
	return "";// 如果没有找到路径分隔符
}
string getComName()//返回计算机名称
{
	char comName[256];
	DWORD size=sizeof(comName);
	string comNameShoww="2ds3dgame";
	if(GetComputerNameA(comName,&size))
	{
		comNameShoww=(string)comName;
	}
	return comNameShoww;
}
string tx_text(int t)//返回特性文本
{
	if(t==0)return "RACE";
	if(t==1)return "RACE-DARK";
	if(t==2)return "NORMAL";
	if(t==3)return "NORMAL-DARK";
	if(t==4)return "EASY";
	if(t==5)return "EASY-DARK";
	if(t==6)return "FUN";
	if(t==7)return "X";
}
string gui_text()//桂哥文本
{
	int random_num=PD_random(1,1000)%5;
	if(random_num==1)return "666烟斗不带烟";
	if(random_num==2)return "666盐豆不带盐";
	if(random_num==3)return "666有嘿壳";
	if(random_num==4)return "666开没开自己心里清楚";
	return "666这个入是桂";
}
void set_birth()//设置出生点
{
	if(oo==0)
	{
		if(bir==1)x=1,y=1;
		if(bir==2)x=1,y=n;
		if(bir==3)x=m,y=1;
		if(bir==4)x=m,y=n;
	}
	if(oo==1)
	{
		x=birx,y=biry;
	}
	for(f=0;f<10;f++)
	{
		savx[f]=x,savy[f]=y;
	}
	birx1=x,biry1=y;
	return;
}
int _finx()//返回结束坐标
{
	if(oo==0)
	{
		if(fin==1 or fin==2)return 1;
		if(fin==3 or fin==4)return m;
	}
	if(oo==1)return finx;
}
int _finy()//返回结束坐标
{
	if(oo==0)
	{
		if(fin==1 or fin==3)return 1;
		if(fin==2 or fin==4)return n;
	}
	if(oo==1)return finy;
}
bool _cant_go(char _ch,int _x,int _y)//判断边界,用于强制移动
{
	if(_ch=='w')
		_x--;
	if(_ch=='s')
		_x++;
	if(_ch=='a')
		_y--;
	if(_ch=='d')
		_y++;
	if(_ch=='q')
		_x--,_y--;
	if(_ch=='e')
		_x--,_y++;
	if(_ch=='z')
		_x++,_y--;
	if(_ch=='c')
		_x++,_y++;
	if(_x<1 or _x>m or _y<1 or _y>n)
	{
		return true;
	}
	return false;
}
bool cant_go(char _ch,int _x,int _y)//十分强悍的移动判断
{
	if(_x<1 or _x>m or _y<1 or _y>n)
		return true;
	if(_ch=='w')
		if(a[_x-1][_y]==-1 or a[_x-1][_y]-a[_x][_y]>1 or a[_x-1][_y]-a[_x][_y]<-2)
			return true;
	else
		return false;
	if(_ch=='s')
		if(a[_x+1][_y]==-1 or a[_x+1][_y]-a[_x][_y]>1 or a[_x+1][_y]-a[_x][_y]<-2)
			return true;
	else
		return false;
	if(_ch=='a')
		if(a[_x][_y-1]==-1 or a[_x][_y-1]-a[_x][_y]>1 or a[_x][_y-1]-a[_x][_y]<-2)
			return true;
	else
		return false;
	if(_ch=='d')
		if(a[_x][_y+1]==-1 or a[_x][_y+1]-a[_x][_y]>1 or a[_x][_y+1]-a[_x][_y]<-2)
			return true;
	else
		return false;
	if(_ch=='q')
		if(a[_x-1][_y-1]==-1 or a[_x-1][_y-1]-a[_x][_y]>0 or a[_x-1][_y-1]-a[_x][_y]<-2 or (a[_x-1][_y]>a[_x][_y] and a[_x][_y-1]>a[_x][_y]))
			return true;
	else
		return false;
	if(_ch=='e')
		if(a[_x-1][_y+1]==-1 or a[_x-1][_y+1]-a[_x][_y]>0 or a[_x-1][_y+1]-a[_x][_y]<-2 or (a[_x-1][_y]>a[_x][_y] and a[_x][_y+1]>a[_x][_y]))
			return true;
	else
		return false;
	if(_ch=='z')
		if(a[_x+1][_y-1]==-1 or a[_x+1][_y-1]-a[_x][_y]>0 or a[_x+1][_y-1]-a[_x][_y]<-2 or (a[_x+1][_y]>a[_x][_y] and a[_x][_y-1]>a[_x][_y]))
			return true;
	else
		return false;
	if(_ch=='c')
		if(a[_x+1][_y+1]==-1 or a[_x+1][_y+1]-a[_x][_y]>0 or a[_x+1][_y+1]-a[_x][_y]<-2 or (a[_x+1][_y]>a[_x][_y] and a[_x][_y+1]>a[_x][_y]))
			return true;
	else
		return false;
}
bool DIE()//你die了没?
{
	int tttt=0;
	if(!cant_go('w',x,y))
	{
		tttt++;
	}
	if(!cant_go('s',x,y))
	{
		tttt++;
	}
	if(!cant_go('a',x,y))
	{
		tttt++;
	}
	if(!cant_go('d',x,y))
	{
		tttt++;
	}
	if(!cant_go('q',x,y))
	{
		tttt++;
	}
	if(!cant_go('e',x,y))
	{
		tttt++;
	}
	if(!cant_go('z',x,y))
	{
		tttt++;
	}
	if(!cant_go('c',x,y))
	{
		tttt++;
	}
	return tttt==0;
}
int ____b(int ____n)//读入____n一个数(>=0),返回____d表示____n的数字位数
{
	if(____n==0)return 1;
	int ____d=0,____p;
	while(____n>0)
	{
		____p=____n%10;
		____n/=10;
		____d++;
	}
	return ____d;
}
//DeepSeek写的
int dirX[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dirY[8] = {0, 0, -1, 1, -1, 1, -1, 1};
char dirChar[8] = {'w', 's', 'a', 'd', 'q', 'e', 'z', 'c'};
// 寻找最短路径
string findOptimalPath(int startX, int startY, int endX, int endY) {
	// 新增访问标记数组(与地图尺寸一致)
	static bool visited[1001][1001] = {false}; // 索引从1开始
	
	// 初始化队列和记录结构
	queue<pair<int, int>> q;
	unordered_map<int, pair<int, int>> prev;
	unordered_map<int, char> moveDir;
	
	// 重置访问标记(每次调用时)
	memset(visited, 0, sizeof(visited));
	
	q.push({startX, startY});
	visited[startX][startY] = true;
	prev[startX * n + startY] = {-1, -1};
	moveDir[startX * n + startY] = ' ';
	
	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();
		
		// 到达终点时回溯路径
		if (x == endX && y == endY) {
			string path;
			while (prev[x * n + y] != make_pair(-1, -1)) {
				path = moveDir[x * n + y] + path;
				auto [px, py] = prev[x * n + y];
				x = px;
				y = py;
			}
			return path;
		}
		
		// 遍历8个方向
		for (int i = 0; i < 8; i++) {
			int nextX = x + dirX[i];
			int nextY = y + dirY[i];
			
			// 边界检查(确保在1..m和1..n范围内)
			if (nextX < 1 || nextX > m || nextY < 1 || nextY > n)
				continue;
			
			// 检查是否可移动且未访问过
			if (!visited[nextX][nextY] && !cant_go(dirChar[i], x, y)) {
				visited[nextX][nextY] = true;
				int key = nextX * n + nextY;
				prev[key] = {x, y};
				moveDir[key] = dirChar[i];
				q.push({nextX, nextY});
			}
		}
	}
	return "ERROR123ABC"; // 无解返回空字符串
}
string _findOptimalPath(int startX, int startY, int endX, int endY)
{
	string _x=findOptimalPath(startX, startY, endX, endY);
	if(_x=="ERROR123ABC")return "ERROR123ABC";
	unordered_map<char, char> _mp=
	{
		{'w',W},{'s',S},{'a',A},{'d',D},{'q',Q},{'e',E},{'z',Z}, {'c',C}
	};
	string _rst;
	transform(_x.begin(),_x.end(),back_inserter(_rst),[&_mp](char c)
															 {
		return _mp[c];
	});
	return _rst;
}
void searchMapMax()//重新寻找地图最高点
{
	int _f,_s;
	ma=-9,maa=-9,mi=9;
	for(_f=1;_f<=m;_f++)
		for(_s=1;_s<=n;_s++)
		{
			ma=max(a[_f][_s],ma);
			mi=min(a[_f][_s],mi);
			if(a[_f][_s]<10)
				maa=max(a[_f][_s],maa);
		}
	if(ma>9 or mi<0)
	{
		map_style=1;
		max_wide=max(____b(abs(mi))+1,____b(ma));
	}
	else
	{
		map_style=0;
		max_wide=1;
	}
	return;
}
void printSpace(int p_num)//对齐补空格
{
	if(map_style==0)
	{
		return;
	}
	else
	{
		int l_num,Ff,___d;
		if(p_num<0)
		{
			p_num=abs(p_num);
			___d=max_wide-____b(p_num)-1;
			for(Ff=0;Ff<___d;Ff++)
			{
				ptf(" ");
			}
		}
		else
		{
			___d=max_wide-____b(p_num);
			for(Ff=0;Ff<___d;Ff++)
			{
				ptf(" ");
			}
		}
	}
	return;
}
void otpt(bool _cls=true)//otpt=output,打印地图
{
	if(_cls)system("cls");
	searchMapMax();
	int f,s,f1,s1;
	if(__A)//显示可走位置
	{
		for(f=1;f<=m;f++)//初始化标记数组
		{
			for(s=1;s<=n;s++)
			{
				b[f][s]=false;
			}
		}
		if(!cant_go('w',x,y))//标记能走的
		{
			b[x-1][y]=true;
		}
		if(!cant_go('s',x,y))
		{
			b[x+1][y]=true;
		}
		if(!cant_go('a',x,y))
		{
			b[x][y-1]=true;
		}
		if(!cant_go('d',x,y))
		{
			b[x][y+1]=true;
		}
		if(!cant_go('q',x,y))
		{
			b[x-1][y-1]=true;
		}
		if(!cant_go('e',x,y))
		{
			b[x-1][y+1]=true;
		}
		if(!cant_go('z',x,y))
		{
			b[x+1][y-1]=true;
		}
		if(!cant_go('c',x,y))
		{
			b[x+1][y+1]=true;
		}
	}
	string pathh=_findOptimalPath(x,y,_finx(),_finy());
	if(_GUI and pathh!="ERROR123ABC")
	{
		for(f=1;f<=m;f++)
			for(s=1;s<=n;s++)
				bb[f][s]=false;
		int x_1=x,y_1=y;
		for(f=0;f<pathh.size();f++)
		{
			if(pathh[f]==W)
			{
				x_1--;
			}
			if(pathh[f]==S)
			{
				x_1++;
			}
			if(pathh[f]==A)
			{
				y_1--;
			}
			if(pathh[f]==D)
			{
				y_1++;
			}
			if(pathh[f]==Q)
			{
				x_1--,y_1--;
			}
			if(pathh[f]==E)
			{
				x_1--,y_1++;
			}
			if(pathh[f]==Z)
			{
				x_1++,y_1--;
			}
			if(pathh[f]==C)
			{
				x_1++,y_1++;
			}
			bb[x_1][y_1]=true;
		}
	}
	if(__I)
	{
		for(f=1;f<=m;f++)
			for(s=1;s<=n;s++)
				imm[f][s]=false;
		for(f=1;f<=m;f++)
			for(s=1;s<=n;s++)
				if(cant_go('w',f+1,s) and cant_go('s',f-1,s) and cant_go('a',f,s+1) and cant_go('d',f,s-1) and cant_go('q',f+1,s+1) and cant_go('e',f+1,s-1) and cant_go('z',f-1,s+1) and cant_go('c',f-1,s-1))
					imm[f][s]=true;
	}
	
	if(__D)//瞎子
	{
		for(f=1;f<=m;f++)//输出地图
		{
			for(s=1;s<=n;s++)
			{
				if(abs(x-f)<=deepseek and abs(y-s)<=deepseek)
				{
					if(x==f and y==s)//当前位置
					{
						_color(cl[cc]);
						ptf("%d",a[f][s]);
						_color();
						printSpace(a[f][s]);
						ptf(" ");
						continue;
					}
					if(__C)//多彩模式
					{
						if(_GUI and bb[f][s])
						{
							_color(14);
							goto __add;
						}
						if(__A and b[f][s])//可走位置
						{
							_color(10);
							goto __add;
						}
						if(__I and imm[f][s])
						{
							_color(13);
							goto __add;
						}//直接输出对应的颜色
						if(ma>9)
						{
							if(a[f][s]>9)
							{
								_color(13);
							}
							else
							{
								_color(cll[maa][a[f][s]]);
							}
						}
						else if(a[f][s]<0)
						{
							_color(8);
						}
						else
						{
							_color(cll[ma][a[f][s]]);
						}__add:
						ptf("%d",a[f][s]);
						_color();
						printSpace(a[f][s]);
						ptf(" ");
					}
					else//普通模式
					{
						if(_GUI and bb[f][s])
						{
							_color(14);
							ptf("%d",a[f][s]);
							_color();
							printSpace(a[f][s]);
							ptf(" ");
							continue;
						}
						if(__A and b[f][s])//可走位置
						{
							_color(10);
							ptf("%d",a[f][s]);
							_color();
							printSpace(a[f][s]);
							ptf(" ");
							continue;
						}
						if(__I and imm[f][s])
						{
							_color(13);
							ptf("%d",a[f][s]);
							_color();
							printSpace(a[f][s]);
							ptf(" ");
							continue;
						}
						_color();
						ptf("%d",a[f][s]);
						printSpace(a[f][s]);
						ptf(" ");
					}
				}
				else
				{
					_color();
					ptf(" ",a[f][s]);
					printSpace(1);
					ptf(" ");
				}
				
			}
			ptf("\n");
		}
	}
	else//不瞎
	{
		for(f=1;f<=m;f++)//输出地图
		{
			for(s=1;s<=n;s++)
			{
				if(x==f and y==s)//当前位置
				{
					_color(cl[cc]);
					ptf("%d",a[f][s]);
					_color();
					printSpace(a[f][s]);
					ptf(" ");
					continue;
				}
				if(__C)//多彩模式
				{
					if(_GUI and bb[f][s])
					{
						_color(14);
						goto __a;
					}
					if(__A and b[f][s])//可走位置
					{
						_color(10);
						goto __a;
					}
					if(__I and imm[f][s])
					{
						_color(13);
						goto __a;
					}//直接输出对应的颜色
					if(ma>9)
					{
						if(a[f][s]>9)
						{
							_color(13);
						}
						else
						{
							_color(cll[maa][a[f][s]]);
						}
					}
					else if(a[f][s]<0)
					{
						_color(8);
					}
					else
					{
						_color(cll[ma][a[f][s]]);
					}__a:
					ptf("%d",a[f][s]);
					_color();
					printSpace(a[f][s]);
					ptf(" ");
				}
				else//普通模式
				{
					if(_GUI and bb[f][s])
					{
						_color(14);
						ptf("%d",a[f][s]);
						_color();
						printSpace(a[f][s]);
						ptf(" ");
						continue;
					}
					if(__A and b[f][s])//可走位置
					{
						_color(10);
						ptf("%d",a[f][s]);
						_color();
						printSpace(a[f][s]);
						ptf(" ");
						continue;
					}
					if(__I and imm[f][s])
					{
						_color(13);
						ptf("%d",a[f][s]);
						_color();
						printSpace(a[f][s]);
						ptf(" ");
						continue;
					}
					_color();
					ptf("%d",a[f][s]);
					printSpace(a[f][s]);
					ptf(" ");
				}
			}
			ptf("\n");
		}
	}
	
	return;
}
bool isWin()
{
	if(oo==0)//四个角落模式
	{
		if(fin==1)return x==1&&y==1;
		if(fin==2)return x==1&&y==n;
		if(fin==3)return x==m&&y==1;
		if(fin==4)return x==m&&y==n;
	}
	if(oo==1)//自定义坐标模式
	{
		return x==finx&&y==finy;
	}
}

bool isKeyword(string _a)//按键保留键
{
	int l=_a.size(),f;
	for(f=0;f<l;f++)
	{
		if(W==_a[f] or A==_a[f] or S==_a[f] or D==_a[f] or Q==_a[f] or E==_a[f] or Z==_a[f] or C==_a[f])
		{
			return true;
		}
	}
	return false;
}

void zuse()//阻塞
{
	ptf("按回车继续"); i_input getchar();
	system("pause"); i_input
	return;
}
void chooseMap()
{
	int as;
	ptf("\n输入你想选择的地图编号(1~2)。");ent
	i_input
	cin>>as;
	if(as==1)
	{
		_color(112);
		ptf(R"(16 16 0
0122323512312210
1242452443251521
1542154352154333
2353451243512331
5123413132421554
3215354251243542
4512425453143132
1441242134545123
2352324123242435
1543155352351542
2351234151415143
2344343323425421
1545155411313543
2352332122542132
1231442155345541
0145153212341510)");ent
		_color();
	}
	else if(as==2)
	{
		ptf("地道战地图");ent
		_color(112);
		ptf(R"(10 18 0
077879236601687930
080117659009798212
102021032178667216
401668122186768218
631742107221012320
740412789167687668
511008897223688778
306017771134211027
108610112773387116
077802898686769600)");ent
		_color();
	}
	else
	{
		err_wrong_input();
		ent
		return;
	}
	ptf("复制并粘贴以上内容,并按回车。");ent ent
	return;
}
bool KFC(char __a,char __b)//经典函数
{
	return __a>__b;
}
bool KFC2(char __a,char __b)//经典函数
{
	return __a>__b;
}

int i_tx()
{
	if(__X)return 7;
	if(__T)return 6;
	if(__D)
	{
		if(__A)return 5;
		if(__C or __I)return 3;
		return 1;
	}
	else
	{
		if(__A)return 4;
		if(__C or __I)return 2;
		return 0;
	}
}

string tx_get(int t=0)//返回当前特性
{
	if(t==0)
	{
		string txx=__E?"E":"";
		txx+=__C?"C":"";
		txx+=__A?"A":"";
		txx+=__I?"I":"";
		txx+=__T?"T":"";
		txx+=__D?"D":"";
		txx+=__X?"X":"";
		txx+=_GUI?"G":"";
		txx+=_anyway?"!":"";
		return txx;
	}
	if(t==1)
	{
		string txx=__E?"E1 ":"E0 ";
		txx+=__C?"C1 ":"C0 ";
		txx+=__A?"A1 ":"A0 ";
		txx+=__I?"I1 ":"I0 ";
		txx+=__T?"T1 ":"T0 ";
		txx+=__D?"D1 ":"D0 ";
		txx+=__X?"X1 ":"X0 ";
		txx+=_GUI?"G1 ":"G0 ";
		txx+=_anyway?"!1":"!0";
		return txx;
	}
}
void tx_set()//设置特性向导
{
	while(1)
	{
		string txstr;
		ptf(R"(下面是所有的竞速模式, 当选择特性超出模式允许的范围, 会自动切换到更加宽松的模式。
0 RACE		E
1 RACE-DARK	ED
2 NORMAL	ECI
3 NORMAL-DARK	ECID
4 EASY		ECAI
5 EASY-DARK	ECAID
6 FUN		ECAITD
7 X		ECAITDX

下面是所有特性：
E回车以下一步
C多彩模式
A显示可到达地点
I显示不可能到达地点
T下一步提示
D瞎子模式
X允许作弊)");ent ent
		zuse();
		ptf("输入你想要的特性, 想要的特性输入英文字母(不区分大小写, 不区分顺序), 不想要的特性不输入。");ent ent
		i_input getline(cin,txstr);
		__E=__C=__A=__I=__T=__D=__X=_GUI=false;
		int f;
		for(f=0;f<txstr.size();f++)
		{
			if(toupper(txstr.at(f))=='E')__E=true;
			if(toupper(txstr.at(f))=='C')__C=true;
			if(toupper(txstr.at(f))=='A')__A=true;
			if(toupper(txstr.at(f))=='I')__I=true;
			if(toupper(txstr.at(f))=='T')__T=true;
			if(toupper(txstr.at(f))=='D')__D=true;
			if(toupper(txstr.at(f))=='X')__X=true;
		}
		char x;
		ent ptf((to_string(i_tx())+" "+tx_text(i_tx())+" "+tx_get()+", 满意了吗?").c_str());ent
		i_input ptf("1=满意");ent
		i_input ptf("2=重设");ent ent
		i_input cin>>x;
		if(x=='1')return;
	}
}

string getOMap()
{
	string t1="";
	//地图头
	t1=t1+to_string(m)+" "+to_string(n)+" 1\n";
	for(f=1;f<=m;f++)
	{
		for(s=1;s<n;s++)
		{
			t1=t1+to_string(a[f][s])+" ";
		}t1=t1+to_string(a[f][n]);
		if(f<m)t1=t1+"\n";
	}
	return t1;
}
string subhash(string has,int aa,int ss,int ee)
{
	//aa=0 前后 aa=1 前 aa=2 后
	if(aa==0)
		return (has.substr(0,ss)+"-"+has.substr(has.size()-ee,ee));
	if(aa==1)
		return (has.substr(0,ss));
	if(aa==2)
		return (has.substr(has.size()-ee,ee));
}
string userHash(int t=0)
{
	//t=0 原 t=1 subhash
	string a=PD_hash(userIDPath,true);
	if(t==0)return a;
	string b=subhash(a,1,8,0);
	if(t==1)return b;
}
string mapOHash(int t=0)
{
	//t=0 文件校验 t=1 内存校验
	if(t==0)
	{
		return PD_hash(mapPath,true);
	}
	if(t==1 or t==2)
	{
		return PD_hash(getOMap(),false);
	}
}
string winReport()
{
	//本程序路径、hash
	string EXEpath=getEXEPath();
	string exehash=PD_hash(EXEpath,true);
	//7z路径、hash
	string EXEpathO=getEXEPathO();
	string sevenZadll=PD_hash(EXEpathO+"\\"+"7za.dll",true);
	string sevenZaexe=PD_hash(EXEpathO+"\\"+"7za.exe",true);
	string sevenZxadll=PD_hash(EXEpathO+"\\"+"7zxa.dll",true);
	
	string t0="";
	t0=nameee+" "+verrr+"通关报告\n"
	+getCurrentTimeString()+"\n"
	+(disWMIC?"本报告文件不含WMIC信息。\n":"")
	+"地图原文件SHA-256:"+mapOHash()+"\n地图纯码:"+mapOHash(1)
	+"\n--游戏按键--\n↑ "+W+"  ↓ "+S+"  ← "+A+"  → "+D+"\n↖ "+Q+"  ↗ "+E+"  ↙ "+Z+"  ↘ "+C+"\n最终步数:"+to_string(steps)
	+(steps==beststep?"(步数为最优解)":"")
	+"	作弊次数:"+to_string(_d)+"\n游戏时全部输入:"+winRoad+"\n游戏时有效输入:"+winRoadA
	+"\n开始Unix时间:"+to_string(unixunix0)+"\n结束Unix时间:"+to_string(unixunix1)+"\n用时:"+to_string(msms0)+"s\nID hash SHA-256:"+userHash()+"\n计算机名:"+getComName()
	+"\n出生位置:"+to_string(birx1)+"行 "+to_string(biry1)+"列"+"\n结束位置:"+to_string(_finx())+"行 "+to_string(_finy())+"列"
	+"\n特性变量:"+tx_get(1)+"\n特性:"+to_string(i_tx())+" "+tx_text(i_tx())+" "+tx_get()+"\n"
	+"地图的话:\n========\n"+mapswords+"\n========\n\n玩家的话:\n********\n"+playerswords+"\n********\n"
	+"\n本程序路径:"+EXEpath
	+"\n本程序hash SHA-256:"+exehash
	+"\n7za.dll hash SHA-256:"+sevenZadll
	+"\n7za.exe hash SHA-256:"+sevenZaexe
	+"\n7zxa.dll hash SHA-256:"+sevenZxadll;
	return t0;
}
// tempPath 应为 "\\abc"
int outFile4packData(string result,string fileName,string tempPath="",bool printt=true)
{
	string filePath="."+tempPath+"\\"+fileName;
	ofstream _f(filePath);
	if (!_f) 
	{
		cerr<<"无法保存"<<filePath<<endl;
	}
	_f<<result;
//	_f.close();
	//不关闭防止修改信息
	if(printt)
	{
		_color(48);
		cout<<filePath;
		_color(176);
		ptf("已成功保存");
		_color();
		ent
	}
	
	return 0;
}

// 执行CMD命令并捕获输出到string
string execCmd(const string& cmd)
{
	char buffer[128];
	string result = "";
	// 执行命令并读取输出
	FILE* pipe = _popen(cmd.c_str(), "r");
	if (!pipe)
	{
		return cmd+"执行失败";
	}
	while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
	{
		result += buffer;
	}
	_pclose(pipe);
	
	// 去除开头的多个空行
	size_t start = result.find_first_not_of("\r\n");
	if (start != string::npos)
	{
		result = result.substr(start);
	}
	else
	{
		// 如果全是空行，返回空字符串
		result = "";
	}
	
	return result;
}

string packRaceData()
{
	//cmd调用路径: "."+randomPath+"\\"+fileName
	int randomNum=PD_random(100000,999999);
	string randomPath="\\$temp\\"+to_string(randomNum);
	
	_color(11);
	cout<<"\n	\\info\\tasklist.txt保存中...\n";
	string tasklistOutput = execCmd("tasklist");
	cout<<"\n	\\info\\tasklistM.txt保存中...\n";
	string tasklistMOutput = execCmd("tasklist /M");
	string treeOutput = execCmd("tree .\\ /f");
	string EXEpath=getEXEPath();
	string exehash=PD_hash(EXEpath,true);
	string EXEpathO=getEXEPathO();
	string sevenZadll=PD_hash(EXEpathO+"\\"+"7za.dll",true);
	string sevenZaexe=PD_hash(EXEpathO+"\\"+"7za.exe",true);
	string sevenZxadll=PD_hash(EXEpathO+"\\"+"7zxa.dll",true);
	cout<<"\n	\\info\\systeminfo.txt保存中...\n";
	string systeminfoOutput = execCmd("systeminfo");
	string ipconfigOutput = execCmd("ipconfig /all");
	_color();
	
	string wmicCPUOutput,wmicMEMOutput,wmicDISKOutput,wmicGPUOutput,wmicMBOutput,wmicOSOutput,wmicBIOSOutput;
	if(!disWMIC)
	{
		_color(11);
		cout<<"\n	\\info\\wmicCPU.txt保存中...\n";
		wmicCPUOutput = execCmd("wmic cpu get *");
		cout<<"\n	\\info\\wmicMEM.txt保存中...\n";
		wmicMEMOutput = execCmd("wmic memorychip get *");
		cout<<"\n	\\info\\wmicDISK.txt保存中...\n";
		wmicDISKOutput = execCmd("wmic diskdrive get *");
		cout<<"\n	\\info\\wmicGPU.txt保存中...\n";
		wmicGPUOutput = execCmd("wmic gpu get *");
		cout<<"\n	\\info\\wmicMB.txt保存中...\n";
		wmicMBOutput = execCmd("wmic baseboard get *");
		cout<<"\n	\\info\\wmicOS.txt保存中...\n";
		wmicOSOutput = execCmd("wmic os get *");
		cout<<"\n	\\info\\wmicBIOS.txt保存中...\n";
		wmicBIOSOutput = execCmd("wmic bios get *");
		_color();
	}
	
	system(("mkdir \"."+randomPath+"\\readme\"").c_str());
	system(("mkdir \"."+randomPath+"\\player\"").c_str());
	system(("mkdir \"."+randomPath+"\\result\"").c_str());
	
	system(("mkdir \"."+randomPath+"\\map\"").c_str());
	system(("mkdir \"."+randomPath+"\\keyboard\"").c_str());
	system(("mkdir \"."+randomPath+"\\info\"").c_str());
	
	//readme
	{
		_color(11);
		cout<<"\n\\readme\\保存中...\n";
		_color();
		//本程序简介
		string readmee=nameee+" "+verrr+"\nby IQ Online Studio, github.com/iqonli/2ds3dgame\n这是一份2D's 3D Game的游戏通关报告，详细信息请前往我们的项目网站。";
		outFile4packData(readmee,"readme\\README.txt",randomPath);
		//玩家的话
		outFile4packData(playerswords,"readme\\playerswords.txt",randomPath);
	}
	//player OK
	{
		_color(11);
		cout<<"\n\\player\\保存中...\n";
		_color();
		//useridhash
		outFile4packData(userHash(),"player\\useridhash.txt",randomPath);
		//计算机名称 computerName
		outFile4packData(getComName(),"player\\computerName.txt",randomPath);
	}
	//result
	{
		_color(11);
		cout<<"\n\\result\\保存中...\n";
		_color();
		outFile4packData(winReport(),"result\\result.txt",randomPath);
	}
	//map OK
	{
		_color(11);
		cout<<"\n\\map\\保存中...\n";
		_color();
		//地图文件hash mapFileHash
		outFile4packData(mapOHash(),"map\\mapFileHash.txt",randomPath);
		//地图内存纯码hash mapRAMOHash
		outFile4packData(mapOHash(1),"map\\mapRAMOHash.txt",randomPath);
		//copy源文件
		system(("copy \""+mapPath+"\" ."+randomPath+"\\"+"map\\mapOriginalFile.txt").c_str());
		//原始地图路径
		outFile4packData(mapPath,"map\\mapOriginalFilePath.txt",randomPath);
		//RAM备份 mapRAMOriginal
		string t1="";
		t1=t1+to_string(m)+" "+to_string(n)+" 1\n";
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				t1=t1+to_string(amap[f][s])+" ";
			}t1=t1+to_string(amap[f][n]);
			if(f<m)t1=t1+"\n";
		}
		t1=t1+mapswords;
		outFile4packData(t1,"map\\mapRAMOriginal.txt",randomPath);
		//RAM现在 mapRAMNow
		string t2="";
		t2=t2+to_string(m)+" "+to_string(n)+" 1\n";
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				t2=t2+to_string(a[f][s])+" ";
			}t2=t2+to_string(a[f][n]);
			if(f<m)t2=t2+"\n";
		}
		t2=t2+mapswords;
		outFile4packData(t2,"map\\mapRAMNow.txt",randomPath);
		//地图的话 mapswords
		outFile4packData(mapswords,"map\\mapswords.txt",randomPath);
	}
	//keyboard
	{
		_color(11);
		cout<<"\n\\keyboard\\保存中...\n";
		_color();
		//游戏内有效输入 winRoadA
		outFile4packData(winRoadA,"keyboard\\winRoadA.txt",randomPath);
		//游戏内全部输入 winRoad
		outFile4packData(winRoad,"keyboard\\winRoad.txt",randomPath);
		//live带时间
		114514;
	}
	//info
	{
		_color(11);
		cout<<"\n\\info\\保存中...\n";
		_color();
		//tasklist non/M - 先捕获输出再写入
		outFile4packData(tasklistOutput, "info\\tasklist.txt", randomPath);
		outFile4packData(tasklistMOutput, "info\\tasklistM.txt", randomPath);
		
		//游戏目录文件 gameFolderFileList
		outFile4packData(treeOutput, "info\\gameFolderFileList.txt", randomPath);
		
		//剪贴板
		114514;
		
		//本程序路径、hash
		outFile4packData(EXEpath,"info\\gamepath.txt",randomPath);
		outFile4packData(exehash,"info\\gamehash.txt",randomPath);
		
		//7z路径、hash
		outFile4packData(sevenZadll,"info\\7za.dll-hash.txt",randomPath);
		outFile4packData(sevenZaexe,"info\\7za.exe-hash.txt",randomPath);
		outFile4packData(sevenZxadll,"info\\7zxa.dll-hash.txt",randomPath);
		
		//screen size hz
		114514;
		
		//系统配置 - 先捕获输出再写入
		outFile4packData(systeminfoOutput, "info\\systeminfo.txt", randomPath);
		
		if(!disWMIC)
		{
			outFile4packData(wmicCPUOutput, "info\\wmicCPU.txt", randomPath);
			outFile4packData(wmicMEMOutput, "info\\wmicMEM.txt", randomPath);
			outFile4packData(wmicDISKOutput, "info\\wmicDISK.txt", randomPath);
			outFile4packData(wmicGPUOutput, "info\\wmicGPU.txt", randomPath);
			outFile4packData(wmicMBOutput, "info\\wmicMB.txt", randomPath);
			outFile4packData(wmicOSOutput, "info\\wmicOS.txt", randomPath);
			outFile4packData(wmicBIOSOutput, "info\\wmicBIOS.txt", randomPath);
		}
		
		//ipconfig信息 - 先捕获输出再写入
		outFile4packData(ipconfigOutput, "info\\ipconfig.txt", randomPath);
	}
	string reportZipName="2ds3dgame-"+subhash(mapOHash(1),1,8,0)+"-"+getCurrentTimeString4Report()+"-"+to_string(randomNum);//没有.zip
	if(disWMIC)
	{
		reportZipName=reportZipName+"-NonWMIC";
	}
	string sevenZcommand="7za.exe a -tzip -mx=9 \".\\report\\"+reportZipName+".zip\" \"."+randomPath+"\\*\"";
	_color(11);
	cout<<"\n即 7-zip压缩中...\n";
	cout<<"将 7-zip压缩中...\n";
	cout<<"成 7-zip压缩中...\n";
	cout<<"功 7-zip压缩中...\n";
	_color(6);
	system(sevenZcommand.c_str());
	_color(11);
	cout<<"\n临时文件删除中...\n";
	_color();
	system(("rd \"."+randomPath+"\\\" /s /q").c_str());
	return ".\\report\\"+reportZipName+".zip";
}

int main()
{
	cll[2][0]=cll[3][0]=cll[4][0]=cll[5][0]=cll[6][0]=cll[7][0]=cll[8][0]=cll[9][0]=8;
	cll[3][1]=cll[4][1]=cll[5][1]=cll[5][2]=cll[6][1]=cll[6][2]=cll[7][1]=cll[7][2]=cll[8][1]=cll[8][2]=cll[9][1]=cll[9][2]=3;
	cll[0][0]=cll[1][0]=cll[2][1]=cll[3][2]=cll[4][2]=cll[5][3]=cll[6][3]=cll[6][4]=cll[7][3]=cll[7][4]=cll[8][3]=cll[8][4]=cll[9][3]=cll[9][4]=7;
	cll[1][1]=cll[2][2]=cll[3][3]=cll[4][3]=cll[5][4]=cll[6][5]=cll[7][5]=cll[7][6]=cll[8][5]=cll[8][6]=cll[9][5]=cll[9][6]=15;
	cll[4][4]=cll[5][5]=cll[6][6]=cll[7][7]=cll[8][7]=cll[8][8]=cll[9][7]=cll[9][8]=11;
	cll[9][9]=9;
	/*以上为cll数组的初始化,初始化为:
	7  0  0  0  0  0  0  0  0  0
	7  15 0  0  0  0  0  0  0  0
	8  7  15 0  0  0  0  0  0  0
	8  3  7  15 0  0  0  0  0  0
	8  3  7  15 11 0  0  0  0  0
	8  3  3  7  15 11 0  0  0  0
	8  3  3  7  7  15 11 0  0  0
	8  3  3  7  7  15 15 11 0  0
	8  3  3  7  7  15 15 11 11 0
	8  3  3  7  7  15 15 11 11 9*/
	__A=__I=__T=__D=__X=_anyway=_hid=false;
	__C=_X=true;
	ch:
	ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
	windTitle(nameee+" "+verrr);
	ptf((nameee+" "+verrr+"\nby IQ Online Studio, github.com/iqonli/2ds3dgame;\n请查看README.md。\n\n输入i查看版本/版权，s开始游戏。").c_str());ent
	char _x;
	i_input
	cin>>_x;
	if(_x=='i')
	{
		ptf(R"(提示: 游玩时可以连续输入按键再回车。
by IQ Online Studio, github.com/iqonli/2ds3dgame

使用了7-Zip Extra
7-Zip Extra is package of extra modules of 7-Zip. 
7-Zip Copyright (C) 1999-2024 Igor Pavlov.
7-Zip is free software. Read License.txt for more information about license.
Source code of binaries can be found at:
http://www.7-zip.org/

玩法

这是一个用二维的矩阵来玩三维的地图的游戏。三维地图由正方体格子组成,在二维地图中只有高度来表示。

在二维地图中,有两种走法。
示例地图
(以下地图并不是格子高度,而是位置标号)
[1] [2] [3]
[4] [5] [6]
[7] [8] [9]

1. ↑↓←→
如果在[5]的位置,↑↓←→即为到[2],[8],[4],[6]。
记录原格子高度为a,目标格子高度为b,只有在
b-a={-2, -1, 0, 1}
时可以↑↓←→移动。

2. ↖↗↙↘
如果在[5]的位置,↖↗↙↘即为到[1],[3],[7],[9]。
记录原格子高度为a,目标格子高度为b,只有在满足条件A时可以↑↓←→移动。
示例地图
(以下地图是格子高度)
a c
d b
如果要在这样一个2×2的地图中进行↖↗↙↘,例如从a到b。
条件A:b-a={-2, -1, 0},且a≥c或a≥d。


2.x版说明2024.7.31
这个介绍是老版本遗留的,新版新写了个介绍(参赛时候的要求),最好是看那个。新做了个教程程序,可以配合这个主程序使用。
by Alone, IQ Online Studio 智商在线工作室(非真实存在的工作室)。 QQ:34067513 See the website 查看网站: https://melonchats.github.io/melon/a.html
详细介绍(1.0原始介绍和2.0视频介绍,因为是参赛作品会晚上线)可见https://www.luogu.com.cn/blog/perryding/2ds3d-game。以下是精简版。
这是一个用二维的矩阵来玩三维的地图的游戏,游戏中的方块像Minecraft一样, 地图中的数字代表了俯视图中每一格地面方块的高度。
如,地图中的2代表了这一格有两个竖着垒的方块。
你可以往上下左右平移,你也可以往上爬一格、往下走一格、往下走两格,如从1到2,2到3等。
你也可以往左上,右上,左下,右下平移。你所在位置和目标位置组成的田字格中,如果其它两个方块的高度都小于等于所在位置和目标位置的高度,那你就能平移,否则不行。你也可以斜着下一格、下两格,但是不能往上爬。这很符合现实物理和Minecraft。
比如说这个:
1 2
2 1
当你要从1到1, 你不能往↖↘走; 但要从2到2,可以↗↙走。


原版说明2023.6.29
by Alone, IQ Online Studio. QQ:34067513 See the website: https://melonchats.github.io/melon/a.html
this is a game that use 2d number to play 3d PaoKu. like Minecraft, the nums in map is the heights of the blocks.
for example, the num 2 just 2 blocks in MC.
To go up, you can only go up 1 height. like 1 to 2, 2 to 3 and so on. and you can only move in four directions: front ^, back v, left <, right >.
To go down, you can go down 1 height or 2 height, if above this num, you'll fall and lose some health. isn't it? and you can move in eight directions.
To go down or go front, you should notice: if your direction is left-front, right-front, left-back, right-back, you can move when the other two num beside below or equal your now num and expect num.
like this:
1 2
2 1
when you are in 1, you can't use right-back or left-front to the other 1, but you can use right-front and left-back from 2 to 2.)");ent
		goto ch;
	}
	else if(_x=='s')
	{
		four1:
		ptf("\n选择你的模式！");ent
		i_input ptf("f=fun  娱乐(必须手动输入地图);");ent
		i_input ptf("r=race 竞速(必须选择本地地图);");ent ent
		i_input
		cin>>_x;
		if(_x=='f')
		{
			fr=false;
		}
		else if(_x=='r')
		{
			fr=true;
		}
		else
		{
			err_wrong_input();
			goto four1;
		}
	}
	else
	{
		err_wrong_input();
		goto ch;
	}
	if(fr==false)
	{
		four2:
		ptf("\n请输入地图大小(m行n列,空格隔开),输入\"-1 -1\"以选择地图, 输入\"-2 -2\"以查看规则。");ent
		i_input
		cin>>m>>n;
		if(m==-1 and n==-1)
		{
			chooseMap();
			goto four2;
		}
		if(m==-1 and n==-1)
		{
			ptf("该部分已删除。\n");
			system("pause");
			goto four2;
		}
		if(m<1 or n<1)
		{
			err_wrong_input();
			ent
			goto four2;
		}
		if(m>999 or n>999)
		{
			ptf("\n地图大小过大,请勿超过1000。");ent goto ch;
		}
		cms:
		ptf("\n选择你要输入地图的方式(输入数字代号):\n0 两个数之间无需间隔,则地图的数为0~9中的一个; 1 两个数之间任意数,则地图的数可以为int范围内任意数。");ent
		i_input
		cin>>map_style;
		if(map_style!=0 and map_style!=1)
		{
			err_wrong_input();
			goto cms;
		}
		ptf("\n接下来,输入你的地图。");ent
		if(map_style==0)
		{
			ptf("(提示: 单个方块高度不能<0且不能>10。)\n两个方块高度(即地图上的数值)之间可以输入空格,也可以不输入任何字符。");ent
			for(f=1;f<=m;f++)
				for(s=1;s<=n;s++)
				{
					scanf("%1d",&a[f][s]);//格式化输入,一个字符就识别成一个数
					amap[f][s]=a[f][s];//储存副本
				}
		}
		else
		{
			ptf("\n你选择了可以输入任意数的方式,两个方块高度(即地图上的数值)必须输入空格。我们为了显示地图时更容易查看,会以最长的数字的字符为一格排版。");ent
			for(f=1;f<=m;f++)
				for(s=1;s<=n;s++)
				{
					scanf("%d",&a[f][s]);
					amap[f][s]=a[f][s];//储存副本
				}
		}
		searchMapMax();
		for(f=0;f<=m+1;f++)
			for(s=0;s<=n+1;s++)
				if(f==0 or f==m+1 or s==0 or s==n+1)
					a[f][s]=-1;//四周环绕-1
		
		ch1:
		ptf("\n游玩: 输入出生位置和结束位置。\n输入0选择四个角落,输入1自定义位置。");ent
		i_input
		cin>>oo;
		if(oo==0)
		{
			ptf("\n四个角落对应的数: ↖1  ↗2  ↙3  ↘4; 输入出生位置和结束位置对应的数,用空格隔开。");ent
			i_input
			cin>>bir>>fin;
			if(bir<1 or bir>4 or fin<1 or fin>4)
			{
				err_wrong_input();
				goto ch1;
			}
			if(bir==fin)
			{
				ptf("请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。");ent goto ch1;
			}
			if((m==1 and ((bir==1 and fin==3) or (bir==3 and fin==1) or (bir==2 and fin==4) or (bir==4 and fin==2))) or ((n==1 and (bir==1 and fin==2) or (bir==3 and fin==4) or (bir==2 and fin==1) or (bir==4 and fin==3))))
			{
				ptf("请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。");ent goto ch1;
			}
		}
		else if(oo==1)
		{
			ptf("\n输入四个数: 出生位置的行和列,结束位置的行和列。四个数用空格隔开。↖左上角的行为1,列为1。");ent
			i_input
			cin>>birx>>biry>>finx>>finy;
			if(birx<1 or birx>m or biry<1 or biry>n or a[birx][biry]==-1)
			{
				ptf("出生位置不存在。");ent
				oo=2;
			}
			if(finx<1 or finx>m or finy<1 or finy>n or a[finx][finy]==-1)
			{
				ptf("结束位置不存在。");ent
				oo=2;
			}
			if(oo==2)
			{
				ent ent
				goto ch1;
			}
			if(birx==finx and biry==finy)
			{
				ptf("请勿输入相同的位置。你想直接通关吗？答案是: 不可能。呵呵。");ent goto ch1;
			}
		}
		else
		{
			err_wrong_input();
			goto ch1;
		}
		chC:
		ptf("\n选择一个玩家位置显示的颜色, 输入代号。\n绿色 1, 黄色 2, 白色 3, 蓝色 4, 浅蓝 5, 红色 6。");ent
		i_input
		cin>>cc;
		if(cc<1 or cc>6)
		{
			err_wrong_input();
			goto chC;
		}
		chR:
		set_birth();
	}
	if(fr==true)
	{
		if(!playerswordsin.is_open())
		{
			playerswords="玩家什么话也没有留。\n";
		}
		else
		{
			playerswords="";
			string tp12;
			while(getline(playerswordsin,tp12))
			{
				playerswords += tp12+"\n";
			}
			playerswordsin.close();
		}
		ptf("\n以下是本地的所有账号,输入文件名(包括后缀)以导入,多级目录用反斜杠\\表示。(输入错误后果自负)如果你想在游戏窗口复制内容,请先左键拖动选择,然后按回车复制;按右键粘贴;仅限于Windows 10/11。");ent
		_color(48);
		system("tree .\\user /f");
		_color();
//		system("dir .\\user /s /b");
//		char _xx1[100000]=".\\user\\",_xx2[100000];
		i_input
		cin>>_xx2;
		strcat(_xx1,_xx2);
		userIDPath=_xx1;
		if(isNonASCII(userIDPath))
		{
			_color(78);
			cerr<<"错误: id文件包含非ASCII可见字符\a\n";
			_color();
			system("pause");
			return 0;
		}
		cout<<"ID加载成功!\n"<<userHash()<<"\n";
		ptf("\n以下是本地的所有地图,输入文件名(包括后缀)以导入,多级目录用反斜杠\\表示。(输入错误,或地图有问题后果自负)如果你想在游戏窗口复制内容,请先左键拖动选择,然后按回车复制;按右键粘贴;仅限于Windows 10/11。");ent
		_color(48);
		system("tree .\\map /f");
		_color();
//		system("dir .\\map /s /b");
//		char _x1[100000]=".\\map\\",_x2[100000];
		i_input
		cin>>_x2;
		strcat(_x1,_x2);
		mapPath=_x1;
		finnn.open(_x1);
		cin.rdbuf(finnn.rdbuf()); // 将标准输入重定向到文件流
		cin>>m>>n;
		if(m==-3 and n==-3)
		{
			cin>>m>>n;
			mapPassed=true;
		}
		if(m<1 or n<1)
		{
			_color(78);
			cerr<<"错误: 地图长或宽小于1, 已强制停止程序\a\n";
			_color();
			system("pause");
			return 0;
		}
		if(m>999 or n>999)
		{
			_color(78);
			cerr<<"错误: 地图长或宽大于999, 已强制停止程序\a\n";
			_color();
			system("pause");
			return 0;
		}
//		cout<<"\n选择你要输入地图的方式(输入数字代号):\n0 两个数之间无需间隔,则地图的数为0~9中的一个; 1 两个数之间任意数,则地图的数可以为int范围内任意数。\n";
		cin>>map_style;
		if(map_style!=0 and map_style!=1)
		{
			_color(78);
			cerr<<"错误: 地图样式不为1, 已强制停止程序\a\n";
			_color();
			system("pause");
			return 0;
		}
//		cout<<"\n接下来,输入你的地图。";
		if(map_style==0)
		{
			_color(78);
			cerr<<"错误: 地图样式为0, 已强制停止程序\a\n";
			_color();
			system("pause");
			return 0;
//			cout<<"(提示: 单个方块高度不能<0且不能>10。)\n两个方块高度(即地图上的数值)之间可以输入空格,也可以不输入任何字符。\n";
//			for(f=1;f<=m;f++)
//				for(s=1;s<=n;s++)
//				{
//					char xx;
//					do
//					{
//						cin>>xx;
//					}while(!(xx>='0' and xx<='9'));
//					a[f][s]=xx-'0';
//					amap[f][s]=a[f][s];//储存副本
//				}
		}
		else
		{
//			cout<<"你选择了可以输入任意数的方式,两个方块高度(即地图上的数值)必须输入空格。我们为了显示地图时更容易查看,会以最长的数字的字符为一格排版。\n";
			for(f=1;f<=m;f++)
				for(s=1;s<=n;s++)
				{
					cin>>a[f][s];
					amap[f][s]=a[f][s];//储存副本
				}
		}
		searchMapMax();
		for(f=0;f<=m+1;f++)
			for(s=0;s<=n+1;s++)
				if(f==0 or f==m+1 or s==0 or s==n+1)
					a[f][s]=-1;//四周环绕-1
		
		// 读取剩余所有行到 string
		while(getline(cin,tptp))
		{
			mapswords+=(tptp+"\n");
		}
		
		// 恢复标准输入
		finnn.close();
		cin.rdbuf(originalCinBuffer); // 恢复为控制台输入
		if(mapPassed)
		{
			while(1)
			{
				while(1)
				{
					ptf("\n地图已加密,输入密码,一行,禁止空格。\n");
					i_input
					cin>>mapPasswd;
					_color(48);
					cout<<mapPasswd;
					_color();
					cout<<"\n是你想要的密码吗?1 yes, 0 no.";
					char x;
					i_input
					cin>>x;
					if(x=='1')
					{
						break;
					}
					cout<<endl;
				}
				mapPasswdHash=PD_hash(mapPasswd,false);
				int ddd=0;
				for(f=1;f<=m;f++)
					for(s=1;s<=n;s++)
					{
						a[f][s]=a[f][s]^hex_to_10(mapPasswdHash.at(ddd%64));
						ddd++;
					}
				cout<<"\n地图的话:\n========\n"<<mapswords<<"\n========\n";
				cout<<"\n确认地图纯码:"<<mapOHash(1)<<endl;
				cout<<"\n纯码正确吗?不正确需要重新输入密码。1 yes, 0 no.";
				char x;
				i_input
				cin>>x;
				if(x=='1')
				{
					break;
				}
				cout<<endl;
				for(f=1;f<=m;f++)
					for(s=1;s<=n;s++)
					{
						a[f][s]=amap[f][s];
					}
			}
		}
		
		four_ch1:
		originalMapOHash=mapOHash(1);
		ptf("地图加载成功!\n\n游玩: 输入出生位置和结束位置。\n输入0选择四个角落,输入1自定义位置。");ent
		i_input
		cin>>oo;
		if(oo==0)
		{
			ptf("\n四个角落对应的数: ↖1  ↗2  ↙3  ↘4; 输入出生位置和结束位置对应的数,用空格隔开。");ent
			i_input
			cin>>bir>>fin;
			if(bir<1 or bir>4 or fin<1 or fin>4)
			{
				err_wrong_input();
				goto four_ch1;
			}
			if(bir==fin)
			{
				ptf("请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。");ent goto four_ch1;
			}
			if((m==1 and ((bir==1 and fin==3) or (bir==3 and fin==1) or (bir==2 and fin==4) or (bir==4 and fin==2))) or ((n==1 and (bir==1 and fin==2) or (bir==3 and fin==4) or (bir==2 and fin==1) or (bir==4 and fin==3))))
			{
				ptf("请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。");ent goto four_ch1;
			}
		}
		else if(oo==1)
		{
			ptf("\n输入四个数: 出生位置的行和列,结束位置的行和列。四个数用空格隔开。↖左上角的行为1,列为1。");ent
			i_input
			cin>>birx>>biry>>finx>>finy;
			if(birx<1 or birx>m or biry<1 or biry>n or a[birx][biry]==-1)
			{
				ptf("出生位置不存在。");ent
				oo=2;
			}
			if(finx<1 or finx>m or finy<1 or finy>n or a[finx][finy]==-1)
			{
				ptf("结束位置不存在。");ent
				oo=2;
			}
			if(oo==2)
			{
				ent ent
				goto four_ch1;
			}
			if(birx==finx and biry==finy)
			{
				ptf("请勿输入相同的位置。你想直接通关吗？答案是: 不可能。呵呵。");ent goto four_ch1;
			}
		}
		else
		{
			err_wrong_input();
			goto four_ch1;
		}
		four_chC:
		ptf("\n选择一个玩家位置显示的颜色,输入代号。\n绿色 1, 黄色 2, 白色 3, 蓝色 4, 浅蓝 5, 红色 6。");ent
		i_input
		cin>>cc;
		if(cc<1 or cc>6)
		{
			err_wrong_input();
			goto four_chC;
		}
		
		tx_set();
		
		while(1)
		{
			ptf("\n重新定义按键: 依次输入↑↓←→↖↗↙↘的按键,用空格隔开或不隔开,输入8个一样的字符以使用默认按键(请您千万别输入ASCII以外的字符,求求了)。\n默认：wsadqezc");ent
			i_input
			cin>>W>>S>>A>>D>>Q>>E>>Z>>C;
			if(W==S and S==A and A==D and D==Q and Q==E and E==Z and Z==C)
			{
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				ptf("重置成功!");ent
				system("pause");
				break;
			}
			if(W==A or W==S or W==D or W==Q or W==E or W==Z or W==C or A==S or A==D or A==Q or A==E or A==Z or A==C or S==D or S==Q or S==E or S==Z or S==C or D==Q or D==E or D==Z or D==C or Q==E or Q==Z or Q==C or E==Z or E==C or Z==C)
			{
				ptf("按键有重复。");ent
				system("pause");
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				continue;
			}
			if(isKeyword("`"))
			{
				ptf("禁止定义按键为`。");ent
				system("pause");
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				continue;
			}
			break;
		}
		cout<<"\n是否禁用通关报告中的WMIC信息输出?如果禁用,可以保护个人隐私,但是可能会失去一些报告的可信度:日常练习建议禁用,竞赛冲榜建议启用。0禁用, 1启用.";
		char x;
		i_input
		cin>>x;
		if(x=='0')
		{
			disWMIC=true;
		}
		
		otpt();
		cout<<"\n地图的话:\n========\n"<<mapswords<<"\n========\n\n玩家的话:\n********\n"<<playerswords<<"\n********\n\n";
		cout<<"确认地图纯码:"<<mapOHash(1)<<endl;
		cout<<getCurrentTimeString()<<endl;
		ptf("\nGet Ready… 请做好准备……");ent
		system("pause");
		set_birth();
		goto racegame;
	}
	
	while(!isWin())
	{
		otpt();
		if(!_hid)
		{
			if(_GUI)
			{
				_color(224);
				cout<<gui_text();
				_color();
			}
			ptf("\n--游戏按键--\n↑ %c  ↓ %c  ← %c  → %c\n↖ %c  ↗ %c  ↙ %c  ↘ %c\n\n!+想要的操作=强制移动,禁止移动到边界外。\n!!=锁定/退出强制移动。\n?=标记所有不可能到达地点。\n`=按最优解前进一步;!`=获取最优解。\n~=隐藏/显示提示文字。\n0重玩(回到出生点),1选择玩家颜色,2存档读档,3按键设置,4多彩/瞎子/桂哥,5开关显示可到达地点,6显示坐标,7直接传送,8修改方块,9还原地图。\n特性:%s	当前步数:%d	最优解步数:%d	多彩模式:%s	显示可到达地点:%s	显示不可到达地点:%s	桂哥模式:%s	强制移动:%s	作弊次数:%d",W,S,A,D,Q,E,Z,C,tx_get().c_str(),steps,_findOptimalPath(x,y,_finx(),_finy()).size(),__C?"On":"Off",__A?"On":"Off",__I?"On":"Off",_GUI?"On":"Off",_anyway?"On":"Off",_d);
		}
		ent
		if(_X)
		{
			ptf("当前坐标: %d行 %d列\n",x,y);
		}
		if(DIE())
		{
			ent
			_color(207);
			ptf("你无处可退!无路可走!死!");ent
			_color();
			ptf("接受现实并重玩");ent
			ptf("按回车");i_input
			getchar();
			getchar();
			steps=0;
			goto chR;
		}
		i_input
		if(__E)cin>>z;
		else z=_getch();
		if(_anyway)
		{
			if(z==W)
			{
				if(_cant_go('w',x,y))
				{
					err_out_of_map();
					continue;
				}
				x--,_d++,steps++;
				continue;
			}
			if(z==S)
			{
				if(_cant_go('s',x,y))
				{
					err_out_of_map();
					continue;
				}
				x++,_d++,steps++;
				continue;
			}
			if(z==A)
			{
				if(_cant_go('a',x,y))
				{
					err_out_of_map();
					continue;
				}
				y--,_d++,steps++;
				continue;
			}
			if(z==D)
			{
				if(_cant_go('d',x,y))
				{
					err_out_of_map();
					continue;
				}
				y++,_d++,steps++;
				continue;
			}
			
			if(z==Q)
			{
				if(_cant_go('q',x,y))
				{
					err_out_of_map();
					continue;
				}
				x--,y--,_d++,steps++;
				continue;
			}
			if(z==E)
			{
				if(_cant_go('e',x,y))
				{
					err_out_of_map();
					continue;
				}
				x--,y++,_d++,steps++;
				continue;
			}
			if(z==Z)
			{
				if(_cant_go('z',x,y))
				{
					err_out_of_map();
					continue;
				}
				x++,y--,_d++,steps++;
				continue;
			}
			if(z==C)
			{
				if(_cant_go('c',x,y))
				{
					err_out_of_map();
					continue;
				}
				x++,y++,_d++,steps++;
				continue;
			}
		}
		if(z=='!')
		{
			cin>>z;
			if(z=='!')
			{
				_anyway=!_anyway;
			}
			if(z=='`')
			{
				cout<<_findOptimalPath(x,y,_finx(),_finy());
				_d++;
				system("pause");
			}
			if(z==W)
			{
				if(_cant_go('w',x,y))
				{
					err_out_of_map();
					continue;
				}
				x--,_d++,steps++;
				continue;
			}
			if(z==S)
			{
				if(_cant_go('s',x,y))
				{
					err_out_of_map();
					continue;
				}
				x++,_d++,steps++;
				continue;
			}
			if(z==A)
			{
				if(_cant_go('a',x,y))
				{
					err_out_of_map();
					continue;
				}
				y--,_d++,steps++;
				continue;
			}
			if(z==D)
			{
				if(_cant_go('d',x,y))
				{
					err_out_of_map();
					continue;
				}
				y++,_d++,steps++;
				continue;
			}
			
			if(z==Q)
			{
				if(_cant_go('q',x,y))
				{
					err_out_of_map();
					continue;
				}
				x--,y--,_d++,steps++;
				continue;
			}
			if(z==E)
			{
				if(_cant_go('e',x,y))
				{
					err_out_of_map();
					continue;
				}
				x--,y++,_d++,steps++;
				continue;
			}
			if(z==Z)
			{
				if(_cant_go('z',x,y))
				{
					err_out_of_map();
					continue;
				}
				x++,y--,_d++,steps++;
				continue;
			}
			if(z==C)
			{
				if(_cant_go('c',x,y))
				{
					err_out_of_map();
					continue;
				}
				x++,y++,_d++,steps++;
				continue;
			}
		}
		if(z=='?')
		{
			ptf("\n模式1 开/关显示不可到达地点为粉色(仅显示相邻地点不可到达的;连在一起不能到达的地点不能显示)\n模式2 直接修改这些地点成某个数\n输入模式代号:");ent
			i_input
			cin>>tp;
			if(tp==1)
			{
				__I=!__I;
			}
			else if(tp==2)
			{
				_d++;
				ptf("输入你想修改成的数(建议无脑输入-1):");ent
				i_input
				cin>>tp;
				ptf("\n若你想恢复修改前的样子,请复制下面的内容并粘贴、按回车:");ent
				_color(112);
				int fff,sss;
				for(fff=1;fff<=m;fff++)
					for(sss=1;sss<=n;sss++)
					{
						if(cant_go('w',fff+1,sss) and cant_go('s',fff-1,sss) and cant_go('a',fff,sss+1) and cant_go('d',fff,sss-1) and cant_go('q',fff+1,sss+1) and cant_go('e',fff+1,sss-1) and cant_go('z',fff-1,sss+1) and cant_go('c',fff-1,sss-1))
						{
							ptf(" 8 %d %d %d",fff,sss,a[fff][sss]);
							a[fff][sss]=tp;
						}
					}
				_color();
				searchMapMax();
				ent
				system("pause");
			}
			else
			{
				err_wrong_input();
			}
		}
		if(z=='`')
		{
			z=_findOptimalPath(x,y,_finx(),_finy()).c_str()[0];
			_d++;
		}
		if(z=='~')
		{
			_hid=!_hid;
		}
		if(z==W)
		{
			if(cant_go('w',x,y))
			{
				err_cant_go();
				continue;
			}
			x--,steps++;
		}
		if(z==S)
		{
			if(cant_go('s',x,y))
			{
				err_cant_go();
				continue;
			}
			x++,steps++;
		}
		if(z==A)
		{
			if(cant_go('a',x,y))
			{
				err_cant_go();
				continue;
			}
			y--,steps++;
		}
		if(z==D)
		{
			if(cant_go('d',x,y))
			{
				err_cant_go();
				continue;
			}
			y++,steps++;
		}
		
		if(z==Q)
		{
			if(cant_go('q',x,y))
			{
				err_cant_go();
				continue;
			}
			x--,y--,steps++;
		}
		if(z==E)
		{
			if(cant_go('e',x,y))
			{
				err_cant_go();
				continue;
			}
			x--,y++,steps++;
		}
		if(z==Z)
		{
			if(cant_go('z',x,y))
			{
				err_cant_go();
				continue;
			}
			x++,y--,steps++;
		}
		if(z==C)
		{
			if(cant_go('c',x,y))
			{
				err_cant_go();
				continue;
			}
			x++,y++,steps++;
		}
		if(z=='0')
		{
			_color(207);
			ptf("ARE YOU SURE???确定重玩吗???");
			_color();
			ptf("\n1 yes, 0 no.");ent
			i_input
			cin>>f;
			if(f==1)
			{
				steps=0;
				goto chR;
			}
		}
		if(z=='1')
		{
			chC1:
			ptf("\n选择一个玩家位置显示的颜色,输入代号。\n绿色 1, 黄色 2, 白色 3, 蓝色 4, 浅蓝 5, 红色 6。");ent
			i_input
			cin>>cc;
			if(cc<1 or cc>6)
			{
				err_wrong_input();
				goto chC1;
			}
		}
		if(z=='2')
		{
			sav:
			ptf("\n输入数: 0读档,1存档,-1返回上级菜单。");ent
			i_input
			cin>>tp;
			if(tp==-1)
			{
				continue;
			}
			else if(tp==0)
			{
				ent
				for(f=0;f<10;f++)
				{
					ptf("存档%02d,位置%d行 %d列\n",f,savx[f],savy[f]);
				}sav1:
				ptf("\n输入读取存档的编号:");
				cin>>ttp;
				if(ttp==-1)
				{
					goto sav;
				}
				if(ttp<0 or ttp>9)
				{
					ptf("十分错误的数。返回上级菜单输入-1。");ent goto sav1;
				}
				else if(a[savx[ttp]][savy[ttp]]==-1)
				{
					ptf("存档%02d是个无效的存档。返回上级菜单输入-1。\n",ttp);goto sav1;
				}
				else
				{
					x=savx[ttp],y=savy[ttp],steps=savstep[ttp];
				}
			}
			else if(tp==1)
			{
				ent
				for(f=0;f<10;f++)
				{
					ptf("存档%02d,位置%d行 %d列\n",f,savx[f],savy[f]);
				}sav2:
				ptf("\n输入存取存档的编号:");
				cin>>ttp;
				if(ttp==-1)
				{
					goto sav;
				}
				if(ttp<0 or ttp>9)
				{
					ptf("十分错误的数。返回上级菜单输入-1。");ent goto sav2;
				}
				else
				{
					savx[ttp]=x,savy[ttp]=y,savstep[ttp]=steps;
				}
			}
			else
			{
				err_wrong_input();
				goto sav;
			}
		}
		if(z=='3')
		{
			ptf("\n改变输入方式：输入0(直接移动) 1(回车后移动)");ent
			i_input
			cin>>tp;
			if(tp==0)__E=false;
			else __E=true;
			ptf("\n重新定义按键: 依次输入↑↓←→↖↗↙↘的按键,用空格隔开或不隔开,输入8个一样的字符以重置按键(请您千万别输入ASCII以外的字符,求求了)。");ent
			i_input
			cin>>W>>S>>A>>D>>Q>>E>>Z>>C;
			if(W==S==A==D==Q==E==Z==C)
			{
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				ptf("重置成功!");ent
				system("pause");
				continue;
			}
			if(isKeyword("0123456789!?~`"))
			{
				ptf("禁止定义按键为数字键或!?~`。");ent
				system("pause");
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				continue;
			}
			if(W==A or W==S or W==D or W==Q or W==E or W==Z or W==C or A==S or A==D or A==Q or A==E or A==Z or A==C or S==D or S==Q or S==E or S==Z or S==C or D==Q or D==E or D==Z or D==C or Q==E or Q==Z or Q==C or E==Z or E==C or Z==C)
			{
				ptf("按键有重复。");ent
				system("pause");
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				continue;
			}
		}
		if(z=='4')
		{
			ptf("\n输入c开关多彩模式, 输入d开关瞎子模式, 输入g开关桂哥模式。其实桂哥模式我本来想换成“缺德导航”的, 但懒得换了。");ent
			char tttt;
			i_input
			cin>>tttt;
			if(tttt=='c')
			{
				__C=!__C;
			}
			if(tttt=='d')
			{
				ptf("输入可见度。0:关闭瞎子模式;1:瞎子传奇;2:盲人;3:视障;还可以更大。");ent
				int ttttt;
				i_input
				cin>>ttttt;
				if(ttttt==0)
				{
					__D=false;
				}
				if(ttttt>0)
				{
					__D=true;
					deepseek=ttttt;
				}
			}
			if(tttt=='g')
			{
				_GUI=!_GUI;
			}
		}
		if(z=='5')
		{
			__A=!__A;
		}
		if(z=='6')
		{
			_X=!_X;
		}
		if(z=='7')
		{
			cs:
			int TX,TY;
			ptf("\n输入传送位置的行和列,用空格隔开。当前坐标: %d行 %d列\n",x,y);
			i_input
			cin>>TX>>TY;
			if(TX<1 or TX>m or TY<1 or TY>n)
			{
				ptf("位置不存在。");ent
				goto cs;
			}
			x=TX,y=TY;
			_d++;
		}
		if(z=='8')
		{
			cs1:
			int TX,TY,_f,_s;
			ptf("\n输入修改位置的行和列,用空格隔开。若修改成-1则无法走到此格(可以作弊到达;代码中判定为边界,并且不会显示出来)。\n当前坐标: %d行 %d列\n",x,y);
			i_input
			cin>>TX>>TY;
			if(TX<1 or TX>m or TY<1 or TY>n)
			{
				ptf("位置不存在。");ent
				goto cs1;
			}
			ptf("\n输入修改成的数。\n");
			i_input
			cin>>tp;
			a[TX][TY]=tp;
			searchMapMax();
			_d++;
		}
		if(z=='9')
		{
			int _f,_s;
			for(_f=1;_f<=m;_f++)
				for(_s=1;_s<=n;_s++)
					a[_f][_s]=amap[_f][_s];
			searchMapMax();
		}
	}
	system("cls");
	_color(207);
	ptf("YOU WIN!!!恭喜通关!!!");
	_color();
	_d=0;
	repl:
	ptf("\n输入1重新开玩,输入2结束游戏。提示:重新开玩仍然保留存档！\n");
	i_input
	cin>>f;
	if(f==1)
	{
		steps=0;
		goto chR;
	}
	
	ptf("\n你想复制你玩的地图吗?\n1 yes, 0 no.\n");
	i_input
	cin>>f;
	if(f==1)
	{
		if(map_style==0)
		{
			cout<<m<<' '<<n<<" 0"<<endl;//0
			for(f=1;f<=m;f++)
			{
				for(s=1;s<=n;s++)
				{
					ptf("%d",a[f][s]);
				}
				if(f<m)ptf("\n");
			}
		}
		
		cout<<endl<<m<<' '<<n<<" 1"<<endl;//1
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				ptf("%d ",a[f][s]);
			}ptf("%d",a[f][n]);
			if(f<m)ptf("\n");
		}
		system("pause");
	}
	return 0;
	
	racegame:
	auto race_start=chrono::high_resolution_clock::now();
	msms0;
	unixunix0=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	beststep=strlen(_findOptimalPath(x,y,_finx(),_finy()).c_str());
	while(!isWin())
	{
		if(originalMapOHash!=mapOHash(1))
		{
			_color(78);
			cerr<<"错误: 检测到地图纯码改变, 已强制停止程序\a\n";
			_color();
			system("pause");
			return 0;
		}
		auto race_end=chrono::high_resolution_clock::now();
		chrono::duration<double> ess = race_end-race_start;
		otpt();
		if(!_hid)
			ptf("\n--游戏按键--\n↑ %c  ↓ %c  ← %c  → %c\n↖ %c  ↗ %c  ↙ %c  ↘ %c\n\n\n输入~隐藏/显示提示文字,输入0重玩\n多彩模式:%s	显示可到达地点:%s	显示不可到达地点:%s	强制移动:%s	作弊次数:%d\n",W,S,A,D,Q,E,Z,C,__C?"On":"Off",__A?"On":"Off",__I?"On":"Off",_anyway?"On":"Off",_d);
		ent
		if(_X)
		{
			ptf("当前坐标: %d行 %d列\n",x,y);
		}
		msms=ess.count();
		msms0=msms;
		unixunix1=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
//		long long unixunix=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
		cout<<tx_get(1)<<endl;
		cout<<to_string(i_tx())+" "+tx_text(i_tx())+" "+tx_get()<<" 时间: "<<msms<<"s 步数: "<<steps<<" 计算机名: "<<getComName()<<endl;
		cout<<getCurrentTimeString()<<endl;
		cout<<"ID hash:	"<<userHash()<<endl;
		cout<<"地图纯码:	"<<mapOHash(1)<<endl;
		stringstream ss;
		ss<<fixed<<setprecision(3)<<msms;
		windTitle(ss.str()+"s | "+to_string(steps)+"steps | "+to_string(i_tx())+" "+tx_text(i_tx())+" "+tx_get()+" | id="+userHash(1)+" | map="+subhash(mapOHash(1),1,8,0)+" | "+getCurrentTimeString()+" | "+nameee+" "+verrr);
		if(DIE())
		{
			ent
			_color(207);
			ptf("你无处可退!无路可走!死!");ent
			_color();
			ptf("接受现实并重玩");ent
			ptf("按回车");i_input
			getchar();
			getchar();
			ptf("Get Ready… 请做好准备……");ent
			system("pause");
			set_birth();
			steps=0;
			goto racegame;
		}
		i_input
		if(__E)cin>>z;
		else z=_getch();
		winRoad=winRoad+z;
		if(z=='`' and __T)
		{
			z=_findOptimalPath(x,y,_finx(),_finy()).c_str()[0];
			winRoadA=winRoadA+z;
		}
		if(z=='~')
		{
			_hid=!_hid;
			winRoadA=winRoadA+z;
		}
		if(z=='0')
		{
			winRoadA=winRoadA+z;
			goto race_repl;
		}
		if(z==W)
		{
			if(cant_go('w',x,y))
			{
				err_cant_go();
				continue;
			}
			x--,steps++;
			winRoadA=winRoadA+z;
		}
		if(z==S)
		{
			if(cant_go('s',x,y))
			{
				err_cant_go();
				continue;
			}
			x++,steps++;
			winRoadA=winRoadA+z;
		}
		if(z==A)
		{
			if(cant_go('a',x,y))
			{
				err_cant_go();
				continue;
			}
			y--,steps++;
			winRoadA=winRoadA+z;
		}
		if(z==D)
		{
			if(cant_go('d',x,y))
			{
				err_cant_go();
				continue;
			}
			y++,steps++;
			winRoadA=winRoadA+z;
		}
		
		if(z==Q)
		{
			if(cant_go('q',x,y))
			{
				err_cant_go();
				continue;
			}
			x--,y--,steps++;
			winRoadA=winRoadA+z;
		}
		if(z==E)
		{
			if(cant_go('e',x,y))
			{
				err_cant_go();
				continue;
			}
			x--,y++,steps++;
			winRoadA=winRoadA+z;
		}
		if(z==Z)
		{
			if(cant_go('z',x,y))
			{
				err_cant_go();
				continue;
			}
			x++,y--,steps++;
			winRoadA=winRoadA+z;
		}
		if(z==C)
		{
			if(cant_go('c',x,y))
			{
				err_cant_go();
				continue;
			}
			x++,y++,steps++;
			winRoadA=winRoadA+z;
		}
		windTitle(ss.str()+"s | "+to_string(steps)+"steps | "+to_string(i_tx())+" "+tx_text(i_tx())+" "+tx_get()+" | id="+userHash(1)+" | map="+subhash(mapOHash(1),1,8,0)+" | "+getCurrentTimeString()+" | "+nameee+" "+verrr);
	}
	system("cls");
	_color(207);
	ptf("YOU WIN!!!恭喜通关!!!");
	_color();
	if(steps==beststep)
	{
		_color(224);
		ptf("\nYOU MADE SHORTEST MOVE!!!您的步数为最优解!!!");
		_color();
	}
	cout<<"\n"<<nameee+" "+verrr<<endl;
	cout<<"\n游戏渲染地图:\n";
	otpt(false);
	cout<<"\n内存中地图内容:\n";
	cout<<m<<' '<<n<<" 0"<<endl;//0
	for(f=1;f<=m;f++)
	{
		for(s=1;s<=n;s++)
		{
			ptf("%d ",a[f][s]);
		}
		if(f<m)ptf("\n");
	}
	cout<<mapswords<<endl;
	_color(240);
	cout<<"\n"<<winReport()<<"\n";
	_color();
	raceDataPath=packRaceData();
	ptf("\n");
	_color(48);
	cout<<raceDataPath;
	_color(176);
	ptf("通关报告保存成功!");
	_color(10);
	ptf("\n");
	raceDataHash=PD_hash(raceDataPath,true);
	cout<<"\n通关报告SHA-256:";
	_color(160);
	cout<<raceDataHash<<endl;
	_color();
	system("pause");
	system("pause");
	_d=0;
	race_repl:
	ptf("\n输入0从准备时重新开玩,输入1重新设置,输入2从娱乐模式重玩,输入3结束游戏。提示:重新开玩只能使用相同地图！\n");
	i_input
	cin>>f;
	if(f==0)
	{
		otpt();
		cout<<"\n地图的话:\n========\n"<<mapswords<<"\n========\n\n玩家的话:\n********\n"<<playerswords<<"\n********\n\n";
		cout<<getCurrentTimeString()<<endl;
		ptf("\nGet Ready… 请做好准备……");ent
		system("pause");
		set_birth();
		steps=0;
		winRoad="",winRoadA="";
		goto racegame;
	}
	if(f==1)
	{
		steps=0;
		goto four_ch1;
	}
	if(f==2)
	{
		fr=false;
		steps=0;
		goto chR;
	}
	system("pause");
	return 0;
}
