#include <bits/stdc++.h>
#include <windows.h>
#include "hashPD.h"
#define i_input _color(14);cout<<'>';_color(7);
using namespace std;
int m,n,f,s,x,y,cc,oo,bir,fin,birx,biry,finx,finy,tp,ttp,_d,map_style,max_wide=1;
int a[1000][1000];//地图,上下左右四周都有-1环绕（便于判定越界行为）,左上角为1,1,右下角为m,n
int amap[1000][1000];//地图副本
bool mapPassed=false;
string mapPasswd;
void _color(int __C=7)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),__C);
}
int hex_to_10(char a)
{
	if(a>='0' and a<='9')return a-'0';
	a=tolower(a);
	return a-'a'+10;
}
int rando(int a,int b)
{
	static random_device rd;
	static mt19937 gen(rd());
	uniform_int_distribution<> dis(a, b);
	return dis(gen);
}
void err()
{
	printf("十分错误的输入。\n");
	return;
}

int main()
{ch:
	system("title 2D's 3D Game Map Creator");
	puts("2D's 3D Game Map Creator");
	puts("by IQ Online Studio, github.com/iqonli/2ds3dgame");
	puts("\n欢迎来到2D's 3D Game Map Creator。(目前版本只能格式化地图和加密)");
	system("pause");
	char _x='a';
//	puts("输入a手动输入地图,b从本地选择。");
//	i_input
//	cin>>_x;
	if(_x=='a')
	{
		puts("请输入地图大小(m行n列,空格隔开),输入\"-3 -3\"以生成加密竞速地图。");
		i_input
		cin>>m>>n;
		if(m==-3 and n==-3)
		{
			while(1)
			{
				cout<<"\n输入密码,一行,禁止空格,输入auto来自动生成一段10位密码。\n";
				i_input
				cin>>mapPasswd;
				if(mapPasswd=="auto")
				{
					mapPasswd="";
					string chara="!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
					for(int f=0;f<10;f++)
					{
						mapPasswd=mapPasswd+chara.at(rando(0,chara.size()-1));
					}
				}
				_color(48);
				cout<<mapPasswd;
				_color();
				cout<<"\n是你想要的密码吗?1 yes, 0 no.";
				char x;
				i_input
				cin>>x;
				if(x=='1')
				{
					puts("请输入地图大小(m行n列,空格隔开)。");
					i_input
					cin>>m>>n;
					break;
				}
				cout<<endl;
			}
			mapPassed=true;
		}
		
		if(m<1 or n<1)
		{
			err();
			cout<<endl;
			goto ch;
		}
		if(m>999 or n>999)
		{
			cout<<"地图大小过大,请勿超过1000。\n";goto ch;
		}
		cms:
		cout<<"\n选择你要输入地图的方式(输入数字代号):\n0 两个数之间无需间隔,则地图的数为0~9中的一个; 1 两个数之间任意数,则地图的数可以为int范围内任意数。\n";
		i_input
		cin>>map_style;
		if(map_style!=0 and map_style!=1)
		{
			err();
			goto cms;
		}
		cout<<"\n接下来,输入你的地图。";
		if(map_style==0)
		{
			cout<<"(提示: 单个方块高度不能<0且不能>10。)\n两个方块高度(即地图上的数值)之间可以输入空格,也可以不输入任何字符。\n";
			for(f=1;f<=m;f++)
				for(s=1;s<=n;s++)
				{
					scanf("%1d",&a[f][s]);//格式化输入,一个字符就识别成一个数
					amap[f][s]=a[f][s];//储存副本
				}
		}
		else
		{
			cout<<"你选择了可以输入任意数的方式,两个方块高度（即地图上的数值）必须输入空格。我们为了显示地图时更容易查看,会以最长的数字的字符为一格排版。\n";
			for(f=1;f<=m;f++)
				for(s=1;s<=n;s++)
				{
					scanf("%d",&a[f][s]);
					amap[f][s]=a[f][s];//储存副本
				}
		}
		for(f=0;f<=m+1;f++)
			for(s=0;s<=n+1;s++)
				if(f==0 or f==m+1 or s==0 or s==n+1)
					a[f][s]=-1;//四周环绕-1
	}
	cout<<"输入简介(输入:\n_end\n(单行)以结束):\n";
	i_input
	string mapswords="",tptp;
	getline(cin,tptp);
	while(tptp!="_end")
	{
		getline(cin,tptp);
		mapswords+=(tptp+"\n");
	}
	cout<<"\n地图已经录入完毕,输入你地图的名字(不可含有空格,无需后缀名),完成导出:\n";
	string _1=".\\map\\",_2,_3=mapPassed?".mapx":".map",__y11;
	cin>>_2;
	__y11=_1+_2+_3;
	ofstream file1(__y11,ios::out);
	if(!file1.is_open())return 0;
	if(mapPassed)
	{
		string mapPasswdHash=PD_hash(mapPasswd,false);
		int ddd=0;
		file1<<"-3 -3\n"<<m<<' '<<n<<" 1"<<endl;//1
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				file1<<to_string(a[f][s]^hex_to_10(mapPasswdHash.at(ddd%64)))<<" ";
				ddd++;
			}file1<<to_string(a[f][n]^hex_to_10(mapPasswdHash.at(ddd%64)));
			ddd++;
			if(f<m)file1<<"\n";
		}
		file1<<"\n";
	}
	else
	{
		file1<<m<<' '<<n<<" 1"<<endl;//1
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				file1<<a[f][s]<<" ";
			}file1<<a[f][n];
			if(f<m)file1<<"\n";
		}
		file1<<"\n";
	}
	file1<<mapswords<<endl;
	file1.close();
	
	//打印
	ifstream file(__y11);
	string content(
					   (istreambuf_iterator<char>(file)),
					   istreambuf_iterator<char>()
					   );
	cout<<content<<endl;
	cout<<"\n以上内容已输出到"<<__y11<<endl;
	
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
	cout<<"地图纯码:"<<PD_hash(t1,false);
	if(mapPassed)
	{
		cout<<"\n地图密码:";
		_color(48);
		cout<<mapPasswd;
		_color(14);
		cout<<endl<<"墙裂建议稍后手动把地图纯码附在地图的话中,防止输入错误的密码。\n";
		_color();
	}
	
	system("pause");
	return 0;
}

