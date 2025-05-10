#include <bits/stdc++.h>
#include <random>
#include <conio.h>
#include <windows.h>
#include "hashPD.h"
#include "randomPD.h"
#define i_input _color(14);cout<<'>';_color();
using namespace std;
int m,n,f,s,x,y,cc,oo,bir,fin,birx,biry,birx1,biry1,finx,finy,tp,ttp,_d,steps,map_style,deepseek=1,max_wide=1;
int a[1000][1000];//地图,上下左右四周都有-1环绕（便于判定越界行为）,左上角为1,1,右下角为m,n
int amap[1000][1000];//地图副本
bool b[1000][1000],bb[1000][1000],bd[3][3];//查询地图可走位置
bool visited[1000][1000];
bool imm[1000][1000],immd[3][3];
int cl[]={0,160,224,240,159,176,207};//当前位置颜色
int cll[10][10];//多彩模式,前一个代表地图最高点的颜色样式,后一个是对应高度的颜色
int savx[10],savy[10],savstep[10],ma=-9,maa=-9,mi=9;//存档和地图最高点、小于10的最高点
char z;//读入的键
char W='w',A='a',S='s',D='d',Q='q',E='e',Z='z',C='c';//键位
bool __E,__C,__A,__I,__T,__D,__X,_X,_GUI,_anyway,_hid,fr;//_X显示坐标
string tx;
char c_tx[7];
int i_tx;
string userIDPath,mapPath;
char _x1[100000]=".\\map\\",_x2[100000];
char _xx1[100000]=".\\user\\",_xx2[100000];
ifstream finnn;
streambuf* originalCinBuffer=cin.rdbuf();
string mapswords,tptp;
string ttemp;
string winRoadP="",winRoad="";
string nameee="2D's 3D Game Plus",verrr="4.0(Community)";

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
void err()
{
	printf("十分错误的输入。\n");
	return;
}
void _rre()
{
	_color(207);
	printf("OUT OF MAP!!!已经超出边界!!!\n");
	_color();
	system("pause");
	return;
}
void rre()
{
	_color(207);
	printf("YOU CANNOT DO THIS!!!禁止通行!!!\n");
	_color();
	system("pause");
	return;
}
string comNameShow()//返回计算机名称
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
string guiguigui()//桂哥文本
{
	int random_num=PD_random(1,1000)%5;
	if(random_num==1)return "666烟斗不带烟";
	if(random_num==2)return "666盐豆不带盐";
	if(random_num==3)return "666有嘿壳";
	if(random_num==4)return "666开没开自己心里清楚";
	return "666这个入是桂";
}
void sset()//设置出生点
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
bool _cantgoORnot(char _ch,int _x,int _y)//判断边界,用于强制移动
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
bool cantgoORnot(char _ch,int _x,int _y)//十分强悍的移动判断
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
	if(!cantgoORnot('w',x,y))
	{
		tttt++;
	}
	if(!cantgoORnot('s',x,y))
	{
		tttt++;
	}
	if(!cantgoORnot('a',x,y))
	{
		tttt++;
	}
	if(!cantgoORnot('d',x,y))
	{
		tttt++;
	}
	if(!cantgoORnot('q',x,y))
	{
		tttt++;
	}
	if(!cantgoORnot('e',x,y))
	{
		tttt++;
	}
	if(!cantgoORnot('z',x,y))
	{
		tttt++;
	}
	if(!cantgoORnot('c',x,y))
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
	// 新增访问标记数组（与地图尺寸一致）
	static bool visited[1001][1001] = {false}; // 索引从1开始
	
	// 初始化队列和记录结构
	queue<pair<int, int>> q;
	unordered_map<int, pair<int, int>> prev;
	unordered_map<int, char> moveDir;
	
	// 重置访问标记（每次调用时）
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
			
			// 边界检查（确保在1..m和1..n范围内）
			if (nextX < 1 || nextX > m || nextY < 1 || nextY > n)
				continue;
			
			// 检查是否可移动且未访问过
			if (!visited[nextX][nextY] && !cantgoORnot(dirChar[i], x, y)) {
				visited[nextX][nextY] = true;
				int key = nextX * n + nextY;
				prev[key] = {x, y};
				moveDir[key] = dirChar[i];
				q.push({nextX, nextY});
			}
		}
	}
	return "ERROR"; // 无解返回空字符串
}
string _findOptimalPath(int startX, int startY, int endX, int endY)
{
	string _x=findOptimalPath(startX, startY, endX, endY);
	if(_x=="ERROR")return "ERROR";
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
void searchMAX()//重新寻找地图最高点
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
void print(int p_num)//对齐补空格
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
				printf(" ");
			}
		}
		else
		{
			___d=max_wide-____b(p_num);
			for(Ff=0;Ff<___d;Ff++)
			{
				printf(" ");
			}
		}
	}
	return;
}
void otpt()//otpt=output,打印地图
{
	system("cls");
	searchMAX();
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
		if(!cantgoORnot('w',x,y))//标记能走的
		{
			b[x-1][y]=true;
		}
		if(!cantgoORnot('s',x,y))
		{
			b[x+1][y]=true;
		}
		if(!cantgoORnot('a',x,y))
		{
			b[x][y-1]=true;
		}
		if(!cantgoORnot('d',x,y))
		{
			b[x][y+1]=true;
		}
		if(!cantgoORnot('q',x,y))
		{
			b[x-1][y-1]=true;
		}
		if(!cantgoORnot('e',x,y))
		{
			b[x-1][y+1]=true;
		}
		if(!cantgoORnot('z',x,y))
		{
			b[x+1][y-1]=true;
		}
		if(!cantgoORnot('c',x,y))
		{
			b[x+1][y+1]=true;
		}
	}
	string pathh=_findOptimalPath(x,y,_finx(),_finy());
	if(_GUI and pathh!="ERROR")
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
				if(cantgoORnot('w',f+1,s) and cantgoORnot('s',f-1,s) and cantgoORnot('a',f,s+1) and cantgoORnot('d',f,s-1) and cantgoORnot('q',f+1,s+1) and cantgoORnot('e',f+1,s-1) and cantgoORnot('z',f-1,s+1) and cantgoORnot('c',f-1,s-1))
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
						printf("%d",a[f][s]);
						_color();
						print(a[f][s]);
						printf(" ");
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
						printf("%d",a[f][s]);
						_color();
						print(a[f][s]);
						printf(" ");
					}
					else//普通模式
					{
						if(_GUI and bb[f][s])
						{
							_color(14);
							printf("%d",a[f][s]);
							_color();
							print(a[f][s]);
							printf(" ");
							continue;
						}
						if(__A and b[f][s])//可走位置
						{
							_color(10);
							printf("%d",a[f][s]);
							_color();
							print(a[f][s]);
							printf(" ");
							continue;
						}
						if(__I and imm[f][s])
						{
							_color(13);
							printf("%d",a[f][s]);
							_color();
							print(a[f][s]);
							printf(" ");
							continue;
						}
						_color();
						printf("%d",a[f][s]);
						print(a[f][s]);
						printf(" ");
					}
				}
				else
				{
					_color();
					printf(" ",a[f][s]);
					print(1);
					printf(" ");
				}
				
			}
			printf("\n");
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
					printf("%d",a[f][s]);
					_color();
					print(a[f][s]);
					printf(" ");
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
					printf("%d",a[f][s]);
					_color();
					print(a[f][s]);
					printf(" ");
				}
				else//普通模式
				{
					if(_GUI and bb[f][s])
					{
						_color(14);
						printf("%d",a[f][s]);
						_color();
						print(a[f][s]);
						printf(" ");
						continue;
					}
					if(__A and b[f][s])//可走位置
					{
						_color(10);
						printf("%d",a[f][s]);
						_color();
						print(a[f][s]);
						printf(" ");
						continue;
					}
					if(__I and imm[f][s])
					{
						_color(13);
						printf("%d",a[f][s]);
						_color();
						print(a[f][s]);
						printf(" ");
						continue;
					}
					_color();
					printf("%d",a[f][s]);
					print(a[f][s]);
					printf(" ");
				}
			}
			printf("\n");
		}
	}
	
	return;
}
bool winORnot()
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

bool Keyword(string _a)//按键保留键
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
void choose()
{
	int as;
	puts("\n输入你想选择的地图编号(1~2)。");
	i_input
	cin>>as;
	if(as==1)
	{
		_color(112);
		puts(R"(16 16 0
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
0145153212341510)");
		_color();
	}
	else if(as==2)
	{
		cout<<"地道战地图"<<endl;
		_color(112);
		puts(R"(10 18 0
077879236601687930
080117659009798212
102021032178667216
401668122186768218
631742107221012320
740412789167687668
511008897223688778
306017771134211027
108610112773387116
077802898686769600)");
		_color();
	}
	else
	{
		err();
		cout<<endl;
		return;
	}
	puts("复制并粘贴以上内容,并按回车。\n");
	return;
}
string tx_show(int t=0)//返回当前特性
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
void tx_sset(char txx,int ty)//设置特性,txx特性代号,ty对话框
{
	if(txx=='E')
	{
		if(ty)
		{
			__E=windAsk("选择特性E","是否需要特性E 回车以下一步?");
		}
		else
		{
			puts("是否需要特性E 回车以下一步?输入0不需要,1至9需要。");
			i_input
			cin>>tp;
			if(tp==0)__E=false;
			else __E=true;
		}
	}
	if(txx=='C')
	{
		if(ty)
		{
			__C=windAsk("选择特性C","是否需要特性C 多彩模式?");
		}
		else
		{
			puts("是否需要特性C 多彩模式?输入0不需要,1至9需要。");
			i_input
			cin>>tp;
			if(tp==0)__C=false;
			else __C=true;
		}
	}
	if(txx=='A')
	{
		if(ty)
		{
			__A=windAsk("选择特性A","是否需要特性A 显示可到达地点?");
		}
		else
		{
			puts("是否需要特性A 显示可到达地点?输入0不需要,1至9需要。");
			i_input
			cin>>tp;
			if(tp==0)__A=false;
			else __A=true;
		}
	}
	if(txx=='I')
	{
		if(ty)
		{
			__I=windAsk("选择特性I","是否需要特性I 显示不可能到达地点?");
		}
		else
		{
			puts("是否需要特性I 显示不可能到达地点?输入0不需要,1至9需要。");
			i_input
			cin>>tp;
			if(tp==0)__I=false;
			else __I=true;
		}
	}
	if(txx=='T')
	{
		if(ty)
		{
			__T=windAsk("选择特性T","是否需要特性T(按下`可以按照最优解前进一步,游戏时没有这个按键的提示) 下一步提示?");
		}
		else
		{
			puts("是否需要特性T 下一步提示(按下`可以按照最优解前进一步,游戏时没有这个按键的提示)?输入0不需要,1至9需要。");
			i_input
			cin>>tp;
			if(tp==0)__T=false;
			else __T=true;
		}
	}
	if(txx=='D')
	{
		if(ty)
		{
			__D=windAsk("选择特性D","是否需要特性D 瞎子模式?");
		}
		else
		{
			puts("是否需要特性D 瞎子模式?输入0不需要,1至9需要。");
			i_input
			cin>>tp;
			if(tp==0)__D=false;
			else __D=true;
		}
	}
}
void tx_set(int txx,int ty)//设置特性向导
{
	if(txx==0)//E
	{
		tx_sset('E',ty);
	}
	if(txx==1)//ED
	{
		__D=true;
		puts("特性D 瞎子模式 已打开");
		tx_sset('E',ty);
	}
	if(txx==2)//ECI
	{
		tx_set_2:
		tx_sset('E',ty);
		tx_sset('C',ty);
		tx_sset('I',ty);
		if(!(__C or __I))
		{
			puts("你必须具备特性CI中一个或多个，请重新设置。");
			goto tx_set_2;
		}
	}
	if(txx==3)//ECID
	{
		__D=true;
		tx_set_3:
		puts("特性D 瞎子模式 已打开");
		tx_sset('E',ty);
		tx_sset('C',ty);
		tx_sset('I',ty);
		if(!(__C or __I))
		{
			puts("你必须具备特性CI中一个或多个，请重新设置。");
			goto tx_set_3;
		}
	}
	if(txx==4)//ECAI
	{
		__A=true;
		puts("特性A 显示可到达地点 已打开");
		tx_sset('E',ty);
		tx_sset('C',ty);
		tx_sset('I',ty);
	}
	if(txx==5)//ECAID
	{
		__D=true;
		__A=true;
		puts("特性D 瞎子模式 已打开");
		puts("特性A 显示可到达地点 已打开");
		tx_sset('E',ty);
		tx_sset('C',ty);
		tx_sset('I',ty);
	}
	if(txx==6)//ECAITD
	{
		__T=true;
		puts("特性T 下一步提示(按下`可以按照最优解前进一步,游戏时没有这个按键的提示) 已打开");
		tx_sset('E',ty);
		tx_sset('C',ty);
		tx_sset('A',ty);
		tx_sset('I',ty);
		tx_sset('D',ty);
	}
	if(txx==7)//ECAITDX
	{
		__X=true;
		puts("特性X 允许作弊 已打开");
		tx_sset('E',ty);
		tx_sset('C',ty);
		tx_sset('A',ty);
		tx_sset('I',ty);
		tx_sset('T',ty);
		tx_sset('D',ty);
	}
	return;
}
bool KFC(char __a,char __b)//经典函数
{
	return __a>__b;
}

//Written by ChatGPT-4o

string hachinsh(string has,int aa,int ss,int ee)
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
	//t=0 原 t=1 hachinsh
	string a=PD_hash(userIDPath,true);
	if(t==0)return a;
	string b=hachinsh(a,1,8,0);
	if(t==1)return b;
}
string mapHash(int t=0)
{
	if(t==0)
	{
		return PD_hash(mapPath,true);
	}
	if(t==1 or t==2)
	{
		string t1="";
		t1=t1+to_string(m)+" "+to_string(n)+" 1\n";
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				t1=t1+to_string(a[f][s])+" ";
			}t1=t1+to_string(a[f][n]);
			if(f<m)t1=t1+"\n";
		}
		return PD_hash(t1,false);
	}
}
void packRaceData()
{
	system("mkdir \"readme\"");
	system("mkdir \"player\"");
	system("mkdir \"result\"");
	
	system("mkdir \"map\"");
	system("mkdir \"keyboard\"");
	system("mkdir \"info\"");
	
	//readme
	{
		//本程序简介
		//玩家的话
	}
	//player
	{
		//useridhash
		//计算机名称
	}
	//result
	{
		
	}
	//map
	{
		//地图hash
		//copy源文件
		//mem备份
		//mem现在
		//地图的话
	}
	//keyboard
	{
		//通关路线
		//mem通关路线
		//live带时间
	}
	//info
	{
		//applist
		//剪贴板
		//本程序路径、hash
		//7z路径、hash
		//Windows ver
		//screen size hz
	}
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
	puts((nameee+" "+verrr).c_str());
	puts(("\n欢迎来到"+nameee+" "+verrr+"。输入i查看版本/版权，s开始游戏。本游戏输入时任何空格键皆可替换为回车。").c_str());
	char _x;
	i_input
	cin>>_x;
	if(_x=='i')
	{
		puts("提示: 游玩时可以连续输入按键再回车。");
		puts("by Alone, IQ Online Studio 智商在线工作室(非真实存在的工作室)。 QQ:34067513 See the website 查看网站: https://melonchats.github.io/melon/a.html");
		puts("玩法\n");
		puts("这是一个用二维的矩阵来玩三维的地图的游戏。三维地图由正方体格子组成,在二维地图中只有高度来表示。\n");
		puts("在二维地图中,有两种走法。");
		puts("示例地图");
		puts("(以下地图并不是格子高度,而是位置标号)");
		puts("[1] [2] [3]");
		puts("[4] [5] [6]");
		puts("[7] [8] [9]");
		puts("\n1. ↑↓←→");
		puts("如果在[5]的位置,↑↓←→即为到[2],[8],[4],[6]。");
		puts("记录原格子高度为a,目标格子高度为b,只有在");
		puts("b-a={-2, -1, 0, 1}");
		puts("时可以↑↓←→移动。");
		puts("\n2. ↖↗↙↘");
		puts("如果在[5]的位置,↖↗↙↘即为到[1],[3],[7],[9]。");
		puts("记录原格子高度为a,目标格子高度为b,只有在满足条件A时可以↑↓←→移动。");
		puts("示例地图");
		puts("(以下地图是格子高度)");
		puts("a c");
		puts("d b");
		puts("如果要在这样一个2×2的地图中进行↖↗↙↘,例如从a到b。");
		puts("条件A:b-a={-2, -1, 0},且a≥c或a≥d。\n\n");
		
		puts("2.x版说明2024.7.31");
		puts("这个介绍是老版本遗留的,新版新写了个介绍(参赛时候的要求),最好是看那个。新做了个教程程序,可以配合这个主程序使用。");
		puts("by Alone, IQ Online Studio 智商在线工作室(非真实存在的工作室)。 QQ:34067513 See the website 查看网站: https://melonchats.github.io/melon/a.html");
		puts("详细介绍(1.0原始介绍和2.0视频介绍,因为是参赛作品会晚上线)可见https://www.luogu.com.cn/blog/perryding/2ds3d-game。以下是精简版。");
		puts("这是一个用二维的矩阵来玩三维的地图的游戏,游戏中的方块像Minecraft一样, 地图中的数字代表了俯视图中每一格地面方块的高度。");
		puts("如,地图中的2代表了这一格有两个竖着垒的方块。");
		puts("你可以往上下左右平移,你也可以往上爬一格、往下走一格、往下走两格,如从1到2,2到3等。");
		puts("你也可以往左上,右上,左下,右下平移。你所在位置和目标位置组成的田字格中,如果其它两个方块的高度都小于等于所在位置和目标位置的高度,那你就能平移,否则不行。你也可以斜着下一格、下两格,但是不能往上爬。这很符合现实物理和Minecraft。");
		puts("比如说这个:\n1 2\n2 1\n当你要从1到1, 你不能往↖↘走; 但要从2到2,可以↗↙走。\n\n");
		
		puts("原版说明2023.6.29");
		puts("by Alone, IQ Online Studio. QQ:34067513 See the website: https://melonchats.github.io/melon/a.html");
		puts("this is a game that use 2d number to play 3d PaoKu. like Minecraft, the nums in map is the heights of the blocks.");
		puts("for example, the num 2 just 2 blocks in MC.");
		puts("To go up, you can only go up 1 height. like 1 to 2, 2 to 3 and so on. and you can only move in four directions: front ^, back v, left <, right >.");
		puts("To go down, you can go down 1 height or 2 height, if above this num, you'll fall and lose some health. isn't it? and you can move in eight directions.");
		puts("To go down or go front, you should notice: if your direction is left-front, right-front, left-back, right-back, you can move when the other two num beside below or equal your now num and expect num.");
		puts("like this:\n1 2\n2 1\nwhen you are in 1, you can't use right-back or left-front to the other 1, but you can use right-front and left-back from 2 to 2.\n");
		goto ch;
	}
	else if(_x=='s')
	{
		four1:
		puts("\n选择你的模式！");
		puts("fun 娱乐(必须手动输入地图)>f");
		puts("race竞速(必须选择本地地图)>r");
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
			err();
			goto four1;
		}
	}
	else
	{
		err();
		goto ch;
	}
	if(fr==false)
	{
		four2:
		puts("\n请输入地图大小（m行n列,空格隔开）,输入\"-1 -1\"以选择地图, 输入\"-2 -2\"以查看规则。");
		i_input
		cin>>m>>n;
		if(m==-1 and n==-1)
		{
			choose();
			goto four2;
		}
		if(m<1 or n<1)
		{
			err();
			puts("");
			goto four2;
		}
		if(m>999 or n>999)
		{
			puts("\n地图大小过大,请勿超过1000。");goto ch;
		}
		cms:
		puts("\n选择你要输入地图的方式(输入数字代号):\n0 两个数之间无需间隔,则地图的数为0~9中的一个; 1 两个数之间任意数,则地图的数可以为int范围内任意数。");
		i_input
		cin>>map_style;
		if(map_style!=0 and map_style!=1)
		{
			err();
			goto cms;
		}
		puts("\n接下来,输入你的地图。");
		if(map_style==0)
		{
			puts("(提示: 单个方块高度不能<0且不能>10。)\n两个方块高度(即地图上的数值)之间可以输入空格,也可以不输入任何字符。");
			for(f=1;f<=m;f++)
				for(s=1;s<=n;s++)
				{
					scanf("%1d",&a[f][s]);//格式化输入,一个字符就识别成一个数
					amap[f][s]=a[f][s];//储存副本
				}
		}
		else
		{
			puts("\n你选择了可以输入任意数的方式,两个方块高度（即地图上的数值）必须输入空格。我们为了显示地图时更容易查看,会以最长的数字的字符为一格排版。");
			for(f=1;f<=m;f++)
				for(s=1;s<=n;s++)
				{
					scanf("%d",&a[f][s]);
					amap[f][s]=a[f][s];//储存副本
				}
		}
		searchMAX();
		for(f=0;f<=m+1;f++)
			for(s=0;s<=n+1;s++)
				if(f==0 or f==m+1 or s==0 or s==n+1)
					a[f][s]=-1;//四周环绕-1
		
		ch1:
		puts("\n游玩: 输入出生位置和结束位置。\n输入0选择四个角落,输入1自定义位置。");
		i_input
		cin>>oo;
		if(oo==0)
		{
			puts("\n四个角落对应的数: ↖1  ↗2  ↙3  ↘4; 输入出生位置和结束位置对应的数,用空格隔开。");
			i_input
			cin>>bir>>fin;
			if(bir<1 or bir>4 or fin<1 or fin>4)
			{
				err();
				goto ch1;
			}
			if(bir==fin)
			{
				puts("请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。");goto ch1;
			}
			if((m==1 and ((bir==1 and fin==3) or (bir==3 and fin==1) or (bir==2 and fin==4) or (bir==4 and fin==2))) or ((n==1 and (bir==1 and fin==2) or (bir==3 and fin==4) or (bir==2 and fin==1) or (bir==4 and fin==3))))
			{
				puts("请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。");goto ch1;
			}
		}
		else if(oo==1)
		{
			puts("\n输入四个数: 出生位置的行和列,结束位置的行和列。四个数用空格隔开。↖左上角的行为1,列为1。");
			i_input
			cin>>birx>>biry>>finx>>finy;
			if(birx<1 or birx>m or biry<1 or biry>n or a[birx][biry]==-1)
			{
				puts("出生位置不存在。");oo=2;
			}
			if(finx<1 or finx>m or finy<1 or finy>n or a[finx][finy]==-1)
			{
				puts("结束位置不存在。");oo=2;
			}
			if(oo==2)
			{
				cout<<endl<<endl;
				goto ch1;
			}
			if(birx==finx and biry==finy)
			{
				puts("请勿输入相同的位置。你想直接通关吗？答案是: 不可能。呵呵。");goto ch1;
			}
		}
		else
		{
			err();
			goto ch1;
		}
		chC:
		puts("\n选择一个玩家位置显示的颜色,输入代号。\n绿色 1, 黄色 2, 白色 3, 蓝色 4, 浅蓝 5, 红色 6。");
		i_input
		cin>>cc;
		if(cc<1 or cc>6)
		{
			err();
			goto chC;
		}
		chR:
		sset();
	}
	if(fr==true)
	{
		puts("\n以下是本地的所有账号,输入文件名以导入,多级目录用反斜杠\\表示。(输入错误后果自负)如果你想在游戏窗口复制内容,请先左键拖动选择,然后按回车复制;按右键粘贴;仅限于Windows 10/11。");
		_color(48);
		system("tree .\\user /f");
		_color();
//		system("dir .\\user /s /b");
//		char _xx1[100000]=".\\user\\",_xx2[100000];
		i_input
		cin>>_xx2;
		strcat(_xx1,_xx2);
		userIDPath=_xx1;
		cout<<userHash();
		puts("\n以下是本地的所有地图,输入文件名以导入,多级目录用反斜杠\\表示。(输入错误,或地图有问题后果自负)如果你想在游戏窗口复制内容,请先左键拖动选择,然后按回车复制;按右键粘贴;仅限于Windows 10/11。");
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
		if(m<1 or n<1)
		{
			return 0;
		}
		if(m>999 or n>999)
		{
			return 0;
		}
//		cout<<"\n选择你要输入地图的方式(输入数字代号):\n0 两个数之间无需间隔,则地图的数为0~9中的一个; 1 两个数之间任意数,则地图的数可以为int范围内任意数。\n";
		cin>>map_style;
		if(map_style!=0 and map_style!=1)
		{
			return 0;
		}
//		cout<<"\n接下来,输入你的地图。";
		if(map_style==0)
		{
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
//			cout<<"你选择了可以输入任意数的方式,两个方块高度（即地图上的数值）必须输入空格。我们为了显示地图时更容易查看,会以最长的数字的字符为一格排版。\n";
			for(f=1;f<=m;f++)
				for(s=1;s<=n;s++)
				{
					cin>>a[f][s];
					amap[f][s]=a[f][s];//储存副本
				}
		}
		searchMAX();
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
		
		four_ch1:
		puts("\n游玩: 输入出生位置和结束位置。\n输入0选择四个角落,输入1自定义位置。");
		i_input
		cin>>oo;
		if(oo==0)
		{
			puts("\n四个角落对应的数: ↖1  ↗2  ↙3  ↘4; 输入出生位置和结束位置对应的数,用空格隔开。");
			i_input
			cin>>bir>>fin;
			if(bir<1 or bir>4 or fin<1 or fin>4)
			{
				err();
				goto four_ch1;
			}
			if(bir==fin)
			{
				puts("请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。");goto four_ch1;
			}
			if((m==1 and ((bir==1 and fin==3) or (bir==3 and fin==1) or (bir==2 and fin==4) or (bir==4 and fin==2))) or ((n==1 and (bir==1 and fin==2) or (bir==3 and fin==4) or (bir==2 and fin==1) or (bir==4 and fin==3))))
			{
				puts("请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。");goto four_ch1;
			}
		}
		else if(oo==1)
		{
			puts("\n输入四个数: 出生位置的行和列,结束位置的行和列。四个数用空格隔开。↖左上角的行为1,列为1。");
			i_input
			cin>>birx>>biry>>finx>>finy;
			if(birx<1 or birx>m or biry<1 or biry>n or a[birx][biry]==-1)
			{
				puts("出生位置不存在。");oo=2;
			}
			if(finx<1 or finx>m or finy<1 or finy>n or a[finx][finy]==-1)
			{
				puts("结束位置不存在。");oo=2;
			}
			if(oo==2)
			{
				cout<<endl<<endl;
				goto four_ch1;
			}
			if(birx==finx and biry==finy)
			{
				puts("请勿输入相同的位置。你想直接通关吗？答案是: 不可能。呵呵。");goto four_ch1;
			}
		}
		else
		{
			err();
			goto four_ch1;
		}
		four_chC:
		puts("\n选择一个玩家位置显示的颜色,输入代号。\n绿色 1, 黄色 2, 白色 3, 蓝色 4, 浅蓝 5, 红色 6。");
		i_input
		cin>>cc;
		if(cc<1 or cc>6)
		{
			err();
			goto four_chC;
		}
		puts(R"(竞速前,请准备你的模式。
特性：E回车以下一步 C多彩模式 A显示可到达地点 I显示不可能到达地点 T下一步提示 D瞎子模式 X允许作弊
以下是所有的竞速模式,当特性超出其允许的范围,则必须切换到更加宽松的模式。
0 RACE		E
1 RACE-DARK	ED
2 NORMAL	ECI
3 NORMAL-DARK	ECID
4 EASY		ECAI
5 EASY-DARK	ECAID
6 FUN		ECAITD
7 X		ECAITDX)");
		four_tx:
		puts("输入你想游玩的竞速模式(一个数字):");
		i_input
		cin>>i_tx;
		if(i_tx<0 or i_tx>7)
		{
			err();
			goto four_tx;
		}
		__E=__C=__A=__I=__T=__D=__X=false;
//		E      C  A  I   T    D     X
		puts("选择特性时使用对话框吗?输入0不需要,1至9需要。");
		int ttp;
		i_input
		cin>>ttp;
		if(ttp==0)ttp=0;
		else ttp=1;
		tx_set(i_tx,ttp);
		
		while(1)
		{
			puts("\n重新定义按键: 依次输入↑↓←→↖↗↙↘的按键,用空格隔开或不隔开,输入8个一样的字符以使用默认按键(请您千万别输入ASCII以外的字符,求求了)。\n默认：wsadqezc");
			i_input
			cin>>W>>S>>A>>D>>Q>>E>>Z>>C;
			if(W==S and S==A and A==D and D==Q and Q==E and E==Z and Z==C)
			{
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				puts("重置成功!");
				system("pause");
				break;
			}
			if(W==A or W==S or W==D or W==Q or W==E or W==Z or W==C or A==S or A==D or A==Q or A==E or A==Z or A==C or S==D or S==Q or S==E or S==Z or S==C or D==Q or D==E or D==Z or D==C or Q==E or Q==Z or Q==C or E==Z or E==C or Z==C)
			{
				puts("按键有重复。");
				system("pause");
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				continue;
			}
			if(Keyword("`"))
			{
				puts("禁止定义按键为`。");
				system("pause");
				continue;
			}
			break;
		}
		
		otpt();
		cout<<mapswords<<endl;
		puts("\n\nGet Ready… 请做好准备……");
		system("pause");
		sset();
		goto racegame;
	}
	
	while(!winORnot())
	{
		otpt();
		if(!_hid)
		{
			if(_GUI)
			{
				_color(224);
				cout<<guiguigui();
				_color();
			}
			printf("\n--游戏按键--\n↑ %c  ↓ %c  ← %c  → %c\n↖ %c  ↗ %c  ↙ %c  ↘ %c\n\n在操作前输入英文感叹号!可以强制移动,但禁止移动到边界外。\n输入两个英文感叹号!!锁定强制移动模式,再输入!!退出。\n输入英文问号?可以标记出所有不可能到达地点。\n输入`可以按照最优解前进一步,输入!`获得最优解。\n输入~隐藏/显示提示文字。\n0重玩（回到出生点）,1选择玩家颜色,2存档读档,3按键设置,4开关多彩模式、瞎子模式和桂哥模式,5开关显示可到达地点,6显示坐标,7直接传送,8修改方块,9还原地图。\n特性:%s	当前步数:%d	多彩模式:%s	显示可到达地点:%s	显示不可到达地点:%s	桂哥模式:%s	强制移动:%s	作弊次数:%d",W,S,A,D,Q,E,Z,C,tx_show(),steps,__C?"On":"Off",__A?"On":"Off",__I?"On":"Off",_GUI?"On":"Off",_anyway?"On":"Off",_d);
		}
		puts("");
		if(_X)
		{
			printf("当前坐标: %d行 %d列\n",x,y);
		}
		if(DIE())
		{
			puts("");
			_color(207);
			puts("你无处可退!无路可走!死!");
			_color();
			puts("接受现实并重玩");
			cout<<"按回车";
			i_input
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
				if(_cantgoORnot('w',x,y))
				{
					_rre();
					continue;
				}
				x--,_d++,steps++;
				continue;
			}
			if(z==S)
			{
				if(_cantgoORnot('s',x,y))
				{
					_rre();
					continue;
				}
				x++,_d++,steps++;
				continue;
			}
			if(z==A)
			{
				if(_cantgoORnot('a',x,y))
				{
					_rre();
					continue;
				}
				y--,_d++,steps++;
				continue;
			}
			if(z==D)
			{
				if(_cantgoORnot('d',x,y))
				{
					_rre();
					continue;
				}
				y++,_d++,steps++;
				continue;
			}
			
			if(z==Q)
			{
				if(_cantgoORnot('q',x,y))
				{
					_rre();
					continue;
				}
				x--,y--,_d++,steps++;
				continue;
			}
			if(z==E)
			{
				if(_cantgoORnot('e',x,y))
				{
					_rre();
					continue;
				}
				x--,y++,_d++,steps++;
				continue;
			}
			if(z==Z)
			{
				if(_cantgoORnot('z',x,y))
				{
					_rre();
					continue;
				}
				x++,y--,_d++,steps++;
				continue;
			}
			if(z==C)
			{
				if(_cantgoORnot('c',x,y))
				{
					_rre();
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
				if(_cantgoORnot('w',x,y))
				{
					_rre();
					continue;
				}
				x--,_d++,steps++;
				continue;
			}
			if(z==S)
			{
				if(_cantgoORnot('s',x,y))
				{
					_rre();
					continue;
				}
				x++,_d++,steps++;
				continue;
			}
			if(z==A)
			{
				if(_cantgoORnot('a',x,y))
				{
					_rre();
					continue;
				}
				y--,_d++,steps++;
				continue;
			}
			if(z==D)
			{
				if(_cantgoORnot('d',x,y))
				{
					_rre();
					continue;
				}
				y++,_d++,steps++;
				continue;
			}
			
			if(z==Q)
			{
				if(_cantgoORnot('q',x,y))
				{
					_rre();
					continue;
				}
				x--,y--,_d++,steps++;
				continue;
			}
			if(z==E)
			{
				if(_cantgoORnot('e',x,y))
				{
					_rre();
					continue;
				}
				x--,y++,_d++,steps++;
				continue;
			}
			if(z==Z)
			{
				if(_cantgoORnot('z',x,y))
				{
					_rre();
					continue;
				}
				x++,y--,_d++,steps++;
				continue;
			}
			if(z==C)
			{
				if(_cantgoORnot('c',x,y))
				{
					_rre();
					continue;
				}
				x++,y++,_d++,steps++;
				continue;
			}
		}
		if(z=='?')
		{
			puts("\n模式1 开/关显示不可到达地点为粉色(仅显示相邻地点不可到达的;连在一起不能到达的地点不能显示)\n模式2 直接修改这些地点成某个数\n输入模式代号:");
			i_input
			cin>>tp;
			if(tp==1)
			{
				__I=!__I;
			}
			else if(tp==2)
			{
				_d++;
				puts("输入你想修改成的数(建议无脑输入-1):");
				i_input
				cin>>tp;
				puts("\n若你想恢复修改前的样子,请复制下面的内容并粘贴、按回车:");
				_color(112);
				int fff,sss;
				for(fff=1;fff<=m;fff++)
					for(sss=1;sss<=n;sss++)
					{
						if(cantgoORnot('w',fff+1,sss) and cantgoORnot('s',fff-1,sss) and cantgoORnot('a',fff,sss+1) and cantgoORnot('d',fff,sss-1) and cantgoORnot('q',fff+1,sss+1) and cantgoORnot('e',fff+1,sss-1) and cantgoORnot('z',fff-1,sss+1) and cantgoORnot('c',fff-1,sss-1))
						{
							printf(" 8 %d %d %d",fff,sss,a[fff][sss]);
							a[fff][sss]=tp;
						}
					}
				_color();
				searchMAX();
				puts("");
				system("pause");
			}
			else
			{
				err();
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
			if(cantgoORnot('w',x,y))
			{
				rre();
				continue;
			}
			x--,steps++;
		}
		if(z==S)
		{
			if(cantgoORnot('s',x,y))
			{
				rre();
				continue;
			}
			x++,steps++;
		}
		if(z==A)
		{
			if(cantgoORnot('a',x,y))
			{
				rre();
				continue;
			}
			y--,steps++;
		}
		if(z==D)
		{
			if(cantgoORnot('d',x,y))
			{
				rre();
				continue;
			}
			y++,steps++;
		}
		
		if(z==Q)
		{
			if(cantgoORnot('q',x,y))
			{
				rre();
				continue;
			}
			x--,y--,steps++;
		}
		if(z==E)
		{
			if(cantgoORnot('e',x,y))
			{
				rre();
				continue;
			}
			x--,y++,steps++;
		}
		if(z==Z)
		{
			if(cantgoORnot('z',x,y))
			{
				rre();
				continue;
			}
			x++,y--,steps++;
		}
		if(z==C)
		{
			if(cantgoORnot('c',x,y))
			{
				rre();
				continue;
			}
			x++,y++,steps++;
		}
		if(z=='0')
		{
			_color(207);
			printf("ARE YOU SURE???确定重玩吗???");
			_color();
			puts("\n1 yes, 0 no.");
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
			puts("\n选择一个玩家位置显示的颜色,输入代号。\n绿色 1, 黄色 2, 白色 3, 蓝色 4, 浅蓝 5, 红色 6。");
			i_input
			cin>>cc;
			if(cc<1 or cc>6)
			{
				err();
				goto chC1;
			}
		}
		if(z=='2')
		{
			sav:
			puts("\n输入数: 0读档,1存档,-1返回上级菜单。");
			i_input
			cin>>tp;
			if(tp==-1)
			{
				continue;
			}
			else if(tp==0)
			{
				puts("");
				for(f=0;f<10;f++)
				{
					printf("存档%02d,位置%d行 %d列\n",f,savx[f],savy[f]);
				}sav1:
				printf("\n输入读取存档的编号:");
				cin>>ttp;
				if(ttp==-1)
				{
					goto sav;
				}
				if(ttp<0 or ttp>9)
				{
					puts("十分错误的数。返回上级菜单输入-1。");goto sav1;
				}
				else if(a[savx[ttp]][savy[ttp]]==-1)
				{
					printf("存档%02d是个无效的存档。返回上级菜单输入-1。\n",ttp);goto sav1;
				}
				else
				{
					x=savx[ttp],y=savy[ttp],steps=savstep[ttp];
				}
			}
			else if(tp==1)
			{
				puts("");
				for(f=0;f<10;f++)
				{
					printf("存档%02d,位置%d行 %d列\n",f,savx[f],savy[f]);
				}sav2:
				printf("\n输入存取存档的编号:");
				cin>>ttp;
				if(ttp==-1)
				{
					goto sav;
				}
				if(ttp<0 or ttp>9)
				{
					puts("十分错误的数。返回上级菜单输入-1。");goto sav2;
				}
				else
				{
					savx[ttp]=x,savy[ttp]=y,savstep[ttp]=steps;
				}
			}
			else
			{
				err();
				goto sav;
			}
		}
		if(z=='3')
		{
			puts("\n改变输入方式：输入0(直接移动) 1(回车后移动)");
			i_input
			cin>>tp;
			if(tp==0)__E=false;
			else __E=true;
			puts("\n重新定义按键: 依次输入↑↓←→↖↗↙↘的按键,用空格隔开或不隔开,输入8个一样的字符以重置按键(请您千万别输入ASCII以外的字符,求求了)。");
			i_input
			cin>>W>>S>>A>>D>>Q>>E>>Z>>C;
			if(W==S==A==D==Q==E==Z==C)
			{
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				puts("重置成功!");
				system("pause");
				continue;
			}
			if(Keyword("0123456789!?~`"))
			{
				puts("禁止定义按键为数字键或!?~`。");
				system("pause");
				continue;
			}
			if(W==A or W==S or W==D or W==Q or W==E or W==Z or W==C or A==S or A==D or A==Q or A==E or A==Z or A==C or S==D or S==Q or S==E or S==Z or S==C or D==Q or D==E or D==Z or D==C or Q==E or Q==Z or Q==C or E==Z or E==C or Z==C)
			{
				puts("按键有重复。");
				system("pause");
				W='w',S='s',A='a',D='d',Q='q',E='e',Z='z',C='c';
				continue;
			}
		}
		if(z=='4')
		{
			puts("\n输入c开关多彩模式,输入d开关瞎子模式,输入g开关桂哥模式。其实桂哥模式我本来想换成“缺德导航”的,但懒得换了。");
			char tttt;
			i_input
			cin>>tttt;
			if(tttt=='c')
			{
				__C=!__C;
			}
			if(tttt=='d')
			{
				puts("输入可见度。0:关闭瞎子模式;1:瞎子传奇;2:盲人;3:视障;还可以更大。");
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
			printf("\n输入传送位置的行和列,用空格隔开。当前坐标: %d行 %d列\n",x,y);
			i_input
			cin>>TX>>TY;
			if(TX<1 or TX>m or TY<1 or TY>n)
			{
				puts("位置不存在。");
				goto cs;
			}
			x=TX,y=TY;
			_d++;
		}
		if(z=='8')
		{
			cs1:
			int TX,TY,_f,_s;
			printf("\n输入修改位置的行和列,用空格隔开。若修改成-1则无法走到此格(可以作弊到达;代码中判定为边界,并且不会显示出来)。\n当前坐标: %d行 %d列\n",x,y);
			i_input
			cin>>TX>>TY;
			if(TX<1 or TX>m or TY<1 or TY>n)
			{
				puts("位置不存在。");
				goto cs1;
			}
			printf("\n输入修改成的数。\n");
			i_input
			cin>>tp;
			a[TX][TY]=tp;
			searchMAX();
			_d++;
		}
		if(z=='9')
		{
			int _f,_s;
			for(_f=1;_f<=m;_f++)
				for(_s=1;_s<=n;_s++)
					a[_f][_s]=amap[_f][_s];
			searchMAX();
		}
	}
	system("cls");
	_color(207);
	cout<<"YOU WIN!!!恭喜通关!!!";
	_color();
	_d=0;
	repl:
	cout<<"\n输入1重新开玩,输入2结束游戏。提示:重新开玩仍然保留存档！\n";
	i_input
	cin>>f;
	if(f==1)
	{
		steps=0;
		goto chR;
	}
	
	cout<<"\n你想复制你玩的地图吗？\n1 yes, 0 no.\n";
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
					printf("%d",a[f][s]);
				}
				if(f<m)printf("\n");
			}
		}
		
		cout<<endl<<m<<' '<<n<<" 1"<<endl;//1
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				printf("%d ",a[f][s]);
			}printf("%d",a[f][n]);
			if(f<m)printf("\n");
		}
		system("pause");
	}
	return 0;
	
	racegame:
	auto race_start=chrono::high_resolution_clock::now();
	double msms0;
	long long unixunix0=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	long long unixunix1;
	while(!winORnot())
	{
		auto race_end=chrono::high_resolution_clock::now();
		chrono::duration<double> ess = race_end-race_start;
		otpt();
		if(!_hid)
			printf("\n--游戏按键--\n↑ %c  ↓ %c  ← %c  → %c\n↖ %c  ↗ %c  ↙ %c  ↘ %c\n\n\n输入~隐藏/显示提示文字,输入0重玩\n多彩模式:%s	显示可到达地点:%s	显示不可到达地点:%s	强制移动:%s	作弊次数:%d\n",W,S,A,D,Q,E,Z,C,__C?"On":"Off",__A?"On":"Off",__I?"On":"Off",_anyway?"On":"Off",_d);
		puts("");
		if(_X)
		{
			printf("当前坐标: %d行 %d列\n",x,y);
		}
		double msms=ess.count();
		msms0=msms;
		unixunix1=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
//		long long unixunix=chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
		cout<<tx_show(1)<<endl;
		cout<<tx_show()<<" 竞速 4.0 时间: "<<msms<<' '<<comNameShow()<<endl;
		cout<<"ID SHA-256:"<<userHash()<<endl;
		cout<<"地图纯码:"<<mapHash(1)<<endl;
		stringstream ss;
		ss<<fixed<<setprecision(3)<<msms;
		windTitle(ss.str()+" | "+to_string(i_tx)+" "+tx_text(i_tx)+" "+tx_show()+" | "+userHash(1)+" | "+nameee+" "+verrr);
		if(DIE())
		{
			puts("");
			_color(207);
			puts("你无处可退!无路可走!死!");
			_color();
			puts("接受现实并重玩");
			cout<<"按回车";
			i_input
			getchar();
			getchar();
			puts("Get Ready… 请做好准备……");
			system("pause");
			sset();
			steps=0;
			goto racegame;
		}
		i_input
		if(__E)cin>>z;
		else z=_getch();
		winRoadP=winRoadP+to_string(z);
		if(z=='`' and __T)
		{
			z=_findOptimalPath(x,y,_finx(),_finy()).c_str()[0];
		}
		if(z=='~')
		{
			_hid=!_hid;
		}
		if(z=='0')
		{
			goto race_repl;
		}
		if(z==W)
		{
			if(cantgoORnot('w',x,y))
			{
				rre();
				continue;
			}
			x--,steps++;
		}
		if(z==S)
		{
			if(cantgoORnot('s',x,y))
			{
				rre();
				continue;
			}
			x++,steps++;
		}
		if(z==A)
		{
			if(cantgoORnot('a',x,y))
			{
				rre();
				continue;
			}
			y--,steps++;
		}
		if(z==D)
		{
			if(cantgoORnot('d',x,y))
			{
				rre();
				continue;
			}
			y++,steps++;
		}
		
		if(z==Q)
		{
			if(cantgoORnot('q',x,y))
			{
				rre();
				continue;
			}
			x--,y--,steps++;
		}
		if(z==E)
		{
			if(cantgoORnot('e',x,y))
			{
				rre();
				continue;
			}
			x--,y++,steps++;
		}
		if(z==Z)
		{
			if(cantgoORnot('z',x,y))
			{
				rre();
				continue;
			}
			x++,y--,steps++;
		}
		if(z==C)
		{
			if(cantgoORnot('c',x,y))
			{
				rre();
				continue;
			}
			x++,y++,steps++;
		}
	}
	system("cls");
	_color(207);
	cout<<"YOU WIN!!!恭喜通关!!!";
	_color();
	cout<<nameee+" "+verrr<<endl;
	otpt();
	cout<<m<<' '<<n<<" 0"<<endl;//0
	for(f=1;f<=m;f++)
	{
		for(s=1;s<=n;s++)
		{
			printf("%d",a[f][s]);
		}
		if(f<m)printf("\n");
	}
	cout<<mapswords<<endl;
	_color(240);
	printf("\n%s\n",nameee+" "+verrr);
	cout<<"地图原文件SHA-256:"<<mapHash()<<"\n地图纯码:"<<mapHash(1);
	printf("\n--游戏按键--\n↑ %c  ↓ %c  ← %c  → %c\n↖ %c  ↗ %c  ↙ %c  ↘ %c\n最终步数:%d	作弊次数:%d\n游戏时有效输入:%s",W,S,A,D,Q,E,Z,C,steps,_d,winRoadP);
	cout<<"开始Unix:"<<unixunix0<<"\n结束Unix:"<<unixunix1<<"\n用时:"<<msms0<<"\n账号SHA-256:"<<userHash()<<"\n计算机名:"<<comNameShow()<<"\n出生位置:"<<birx1<<"行 "<<biry1<<"列"<<"\n结束位置:"<<_finx()<<"行 "<<_finy()<<"列"<<"\n特性变量:"<<tx_show(1)<<"\n特性:"<<to_string(i_tx)+" "+tx_text(i_tx)+" "+tx_show()<<endl;
	_color();
	system("pause");
	system("pause");
	_d=0;
	race_repl:
	cout<<"\n输入0从准备时重新开玩,输入1重新设置,输入2从娱乐模式重玩,输入3结束游戏。提示:重新开玩只能使用相同地图！\n";
	i_input
	cin>>f;
	if(f==0)
	{
		puts("\nGet Ready… 请做好准备……");
		system("pause");
		sset();
		steps=0;
		winRoad="",winRoadP="";
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
	cout<<"\n你想复制你玩的地图吗？\n1 yes, 0 no.\n";
	i_input
	cin>>f;
	if(f==1)
	{
//		if(map_style==0)
//		{
//			cout<<m<<' '<<n<<" 0"<<endl;//0
//			for(f=1;f<=m;f++)
//			{
//				for(s=1;s<=n;s++)
//				{
//					printf("%d",a[f][s]);
//				}
//				if(f<m)printf("\n");
//			}
//		}
		
		cout<<endl<<m<<' '<<n<<" 1"<<endl;//1
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				printf("%d ",a[f][s]);
			}printf("%d",a[f][n]);
			if(f<m)printf("\n");
		}
		system("pause");
	}
}
