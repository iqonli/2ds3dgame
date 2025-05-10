#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
int m,n,f,s,x,y,cc,oo,bir,fin,birx,biry,finx,finy,tp,ttp,_d;
int a[1000][1000];//地图，上下左右四周都有-1环绕（便于判定越界行为），左上角为1,1，右下角为m,n
int amap[1000][1000];//地图副本
bool b[1000][1000];//查询地图可走位置
int cl[]={0,160,224,240,159,176,207};//当前位置颜色
int cll[10][10];//多彩模式，前一个代表地图最高点的颜色样式，后一个是对应高度的颜色
int savx[10],savy[10],ma=-9,maa=-9;//存档和地图最高点、小于10的最高点
char z;//读入的键
char W='w',A='a',S='s',D='d',Q='q',E='e',Z='z',C='c';//键位
bool _o=true,_p=false,_X=false;//_o多彩模式_p显示可走位置_X显示坐标
void err()
{
	printf("十分错误的数。\n");
	return;
}
void rre()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
	printf("YOU CANNOT DO THIS!!!禁止通行!!!\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	system("pause");
	return;
}
void choose()
{
	int as;
	cout<<"\n输入你想选择的地图编号(1~2)。\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout<<'>';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	cin>>as;
	if(as==1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),112);
		cout<<"16 16"<<endl;
		cout<<"0122323512312210"<<endl;
		cout<<"1242452443251521"<<endl;
		cout<<"1542154352154333"<<endl;
		cout<<"2353451243512331"<<endl;
		cout<<"5123413132421554"<<endl;
		cout<<"3215354251243542"<<endl;
		cout<<"4512425453143132"<<endl;
		cout<<"1441242134545123"<<endl;
		cout<<"2352324123242435"<<endl;
		cout<<"1543155352351542"<<endl;
		cout<<"2351234151415143"<<endl;
		cout<<"2344343323425421"<<endl;
		cout<<"1545155411313543"<<endl;
		cout<<"2352332122542132"<<endl;
		cout<<"1231442155345541"<<endl;
		cout<<"0145153212341510"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	}
	cout<<"复制并粘贴以上内容。\n\n";
	return;
}
void sset()
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
	return;
}
bool cantgoORnot(char _ch,int _x,int _y)
{
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
		if(a[_x][_y]-1==-1 or a[_x][_y-1]-a[_x][_y]>1 or a[_x][_y-1]-a[_x][_y]<-2)
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
void searchMAX()
{
	int _f,_s;
	ma=-9,maa=-9;
	for(_f=1;_f<=m;_f++)
		for(_s=1;_s<=n;_s++)
		{
			ma=max(a[_f][_s],ma);
			if(a[_f][_s]<10)
				maa=max(a[_f][_s],maa);
		}
			
	return;
}
void otpt()
{
	system("cls");
	int f,s,f1,s1;
	if(_p)//显示可走位置
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
	for(f=1;f<=m;f++)//输出地图
	{
		for(s=1;s<=n;s++)
		{
			if(x==f and y==s)//当前位置
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cl[cc]);
				printf("%d",a[f][s]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				printf(" ");
				continue;
			}
			if(_o)//多彩模式
			{
				if(_p and b[f][s])//可走位置
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
					goto _P;
				}//直接输出对应的颜色
				if(ma>9)
				{
					if(a[f][s]>9)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cll[maa][a[f][s]]);
					}
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cll[ma][a[f][s]]);
				}_P:
				printf("%d",a[f][s]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				printf(" ");
			}
			else//普通模式
			{
				if(_p and b[f][s])//可走位置
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
					printf("%d",a[f][s]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					printf(" ");
					continue;
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				printf("%d",a[f][s]);
				printf(" ");
			}
		}
		printf("\n");
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
bool Keyword(string _a)
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
int main()
{
	cll[2][0]=cll[3][0]=cll[4][0]=cll[5][0]=cll[6][0]=cll[7][0]=cll[8][0]=cll[9][0]=8;
	cll[3][1]=cll[4][1]=cll[5][1]=cll[5][2]=cll[6][1]=cll[6][2]=cll[7][1]=cll[7][2]=cll[8][1]=cll[8][2]=cll[9][1]=cll[9][2]=3;
	cll[0][0]=cll[1][0]=cll[2][1]=cll[3][2]=cll[4][2]=cll[5][3]=cll[6][3]=cll[6][4]=cll[7][3]=cll[7][4]=cll[8][3]=cll[8][4]=cll[9][3]=cll[9][4]=7;
	cll[1][1]=cll[2][2]=cll[3][3]=cll[4][3]=cll[5][4]=cll[6][5]=cll[7][5]=cll[7][6]=cll[8][5]=cll[8][6]=cll[9][5]=cll[9][6]=15;
	cll[4][4]=cll[5][5]=cll[6][6]=cll[7][7]=cll[8][7]=cll[8][8]=cll[9][7]=cll[9][8]=11;
	cll[9][9]=14;
	/*以上为cll数组的初始化，初始化为:
	7  0  0  0  0  0  0  0  0  0
	7  15 0  0  0  0  0  0  0  0
	8  7  15 0  0  0  0  0  0  0
	8  3  7  15 0  0  0  0  0  0
	8  3  7  15 11 0  0  0  0  0
	8  3  3  7  15 11 0  0  0  0
	8  3  3  7  7  15 11 0  0  0
	8  3  3  7  7  15 15 11 0  0
	8  3  3  7  7  15 15 11 11 0
	8  3  3  7  7  15 15 11 11 14*/
	ch:
	cout<<"欢迎来到2D's 3D Game Plus版。不要急着玩哦,先初始化。本游戏输入时任何空格键皆可替换为回车。请输入地图大小（m行n列,空格隔开）,输入\"-1 -1\"以选择地图, 输入\"-2 -2\"以查看规则。\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout<<'>';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	cin>>m>>n;
	if(m==-1 and n==-1)
	{
		choose();
		goto ch;
	}
	if(m==-2 and n==-2)
	{
		puts("提示: 游玩时可以连续输入按键再回车。");
		puts("by Alone, IQ Online Studio 智商在线工作室。 QQ:34067513 See the website 查看网站: https://melonchats.github.io/melon/a.html");
		puts("详细介绍（1.0原始介绍和2.0视频介绍,因为是参赛作品会晚上线）可见https://www.luogu.com.cn/blog/perryding/2ds3d-game。以下是精简版。");
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
	cout<<"\n接下来,输入你的地图。（提示: 单个方块高度不能<0且不能>10。）\n两个方块高度（即地图上的数值）之间可以输入空格,也可以不输入任何字符。\n";
	for(f=1;f<=m;f++)
		for(s=1;s<=n;s++)
		{
			scanf("%1d",&a[f][s]);//格式化输入，一个字符就识别成一个数
			amap[f][s]=a[f][s];
			ma=max(a[f][s],ma);//找最大高度便于多彩模式
		}
	for(f=0;f<=m+1;f++)
		for(s=0;s<=n+1;s++)
			if(f==0 or f==m+1 or s==0 or s==n+1)
				a[f][s]=-1;//四周环绕-1
	
	while(1)
	{
		ch1:
		cout<<"\n游玩: 输入出生位置和结束位置。\n输入0选择四个角落,输入1自定义位置。\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		cout<<'>';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		cin>>oo;
		if(oo==0)
		{
			cout<<"\n四个角落对应的数: ↖1  ↗2  ↙3  ↘4; 输入出生位置和结束位置对应的数,用空格隔开。\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			cout<<'>';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			cin>>bir>>fin;
			if(bir<1 or bir>4 or fin<1 or fin>4)
			{
				err();
				goto ch1;
			}
			if(bir==fin)
			{
				cout<<"请勿输入相同的数。你想直接通关吗？答案是: 不可能。呵呵。\n";goto ch1;
			}
			if((m==1 and ((bir==1 and fin==3) or (bir==3 and fin==1) or (bir==2 and fin==4) or (bir==4 and fin==2))) or ((n==1 and (bir==1 and fin==2) or (bir==3 and fin==4) or (bir==2 and fin==1) or (bir==4 and fin==3))))
			{
				cout<<"请勿输入相同的位置,你以为我看不出来吗。你想直接通关吗？答案是: 不可能。呵呵。\n";goto ch1;
			}
		}
		else if(oo==1)
		{
			cout<<"\n输入四个数: 出生位置的行和列,结束位置的行和列。四个数用空格隔开。↖左上角的行为1,列为1。\n";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			cout<<'>';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			cin>>birx>>biry>>finx>>finy;
			if(birx<1 or birx>m or biry<1 or biry>n or a[birx][biry]==-1)
			{
				cout<<"出生位置不存在。";oo=2;
			}
			if(finx<1 or finx>m or finy<1 or finy>n or a[finx][finy]==-1)
			{
				cout<<"结束位置不存在。";oo=2;
			}
			if(oo==2)
			{
				cout<<endl<<endl;
				goto ch1;
			}
			if(birx==finx and biry==finy)
			{
				cout<<"请勿输入相同的位置。你想直接通关吗？答案是: 不可能。呵呵。\n";goto ch1;
			}
		}
		else
		{
			err();
			goto ch1;
		}
		chC:
		cout<<"\n选择一个玩家位置显示的颜色,输入代号。\n绿色 1, 黄色 2, 白色 3, 蓝色 4, 浅蓝 5, 红色 6。\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		cout<<'>';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		cin>>cc;
		if(cc<1 or cc>6)
		{
			err();
			goto chC;
		}
		chR:
		sset();
		while(!winORnot())
		{
			ch2:
			otpt();
			printf("\n--游戏按键--\n↑ %c  ↓ %c  ← %c  → %c\n↖ %c  ↗ %c  ↙ %c  ↘ %c\n0重玩（回到出生点）,1选择玩家颜色,2存档读档,3自定义按键,4开关多彩模式,5开关显示可到达地点,6显示坐标,7直接传送,8修改方块,9还原地图。\n多彩模式:%s	显示可到达地点:%s	作弊次数:%d\n",W,S,A,D,Q,E,Z,C,_o?"On":"Off",_p?"On":"Off",_d);
			if(_X)
			{
				printf("当前坐标: %d行 %d列\n",x,y);
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
			cout<<'>';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			cin>>z;
			if(z==W)
			{
				if(cantgoORnot('w',x,y))
				{
					rre();
					goto ch2;
				}
				x--;
			}
			if(z==S)
			{
				if(cantgoORnot('s',x,y))
				{
					rre();
					goto ch2;
				}
				x++;
			}
			if(z==A)
			{
				if(cantgoORnot('a',x,y))
				{
					rre();
					goto ch2;
				}
				y--;
			}
			if(z==D)
			{
				if(cantgoORnot('d',x,y))
				{
					rre();
					goto ch2;
				}
				y++;
			}
			
			if(z==Q)
			{
				if(cantgoORnot('q',x,y))
				{
					rre();
					goto ch2;
				}
				x--,y--;
			}
			if(z==E)
			{
				if(cantgoORnot('e',x,y))
				{
					rre();
					goto ch2;
				}
				x--,y++;
			}
			if(z==Z)
			{
				if(cantgoORnot('z',x,y))
				{
					rre();
					goto ch2;
				}
				x++,y--;
			}
			if(z==C)
			{
				if(cantgoORnot('c',x,y))
				{
					rre();
					goto ch2;
				}
				x++,y++;
			}
			if(z=='0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
				cout<<"ARE YOU SURE???确定重玩吗???";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				cout<<"\n1 yes, 0 no.\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
				cout<<'>';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				cin>>f;
				if(f==1)
				{
					goto chR;
				}
			}
			if(z=='1')
			{
				chC1:
				cout<<"\n选择一个玩家位置显示的颜色,输入代号。\n绿色 1, 黄色 2, 白色 3, 蓝色 4, 浅蓝 5, 红色 6。\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
				cout<<'>';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
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
				cout<<"\n输入数: 0读档,1存档,-1返回上级菜单。\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
				cout<<'>';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				cin>>tp;
				if(tp==-1)
				{
					goto ch2;
				}
				else if(tp==0)
				{
					cout<<endl;
					for(f=0;f<10;f++)
					{
						printf("存档%02d,位置%d行 %d列\n",f,savx[f],savy[f]);
					}sav1:
					cout<<"\n输入读取存档的编号:";
					cin>>ttp;
					if(ttp==-1)
					{
						goto sav;
					}
					if(ttp<0 or ttp>9)
					{
						cout<<"十分错误的数。返回上级菜单输入-1。\n";goto sav1;
					}
					else if(a[savx[ttp]][savy[ttp]]==-1)
					{
						printf("存档%02d是个无效的存档。返回上级菜单输入-1。\n",ttp);goto sav1;
					}
					else
					{
						x=savx[ttp],y=savy[ttp];
					}
				}
				else if(tp==1)
				{
					cout<<endl;
					for(f=0;f<10;f++)
					{
						printf("存档%02d,位置%d行 %d列\n",f,savx[f],savy[f]);
					}sav2:
					cout<<"\n输入存取存档的编号:";
					cin>>ttp;
					if(ttp==-1)
					{
						goto sav;
					}
					if(ttp<0 or ttp>9)
					{
						cout<<"十分错误的数。返回上级菜单输入-1。\n";goto sav2;
					}
					else
					{
						savx[ttp]=x,savy[ttp]=y;
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
				cout<<"\n重新定义按键: 依次输入↑↓←→↖↗↙↘的按键,用空格隔开或不隔开。\n";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
				cout<<'>';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				cin>>W>>S>>A>>D>>Q>>E>>Z>>C;
				if(Keyword("0123456789"))
				{
					cout<<"禁止定义按键为数字键。\n";
					system("pause");
					goto ch2;
				}
				if(W==A or W==S or W==D or W==Q or W==E or W==Z or W==C or A==S or A==D or A==Q or A==E or A==Z or A==C or S==D or S==Q or S==E or S==Z or S==C or D==Q or D==E or D==Z or D==C or Q==E or Q==Z or Q==C or E==Z or E==C or Z==C)
				{
					cout<<"按键有重复。\n";
					system("pause");
					goto ch2;
				}
			}
			if(z=='4')
			{
				_o=!_o;
			}
			if(z=='5')
			{
				_p=!_p;
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
				cout<<'>';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				cin>>TX>>TY;
				if(TX<1 or TX>m or TY<1 or TY>n or a[TX][TY]==-1)
				{
					cout<<"位置不存在。\n";
					goto cs;
				}
				x=TX,y=TY;
				_d++;
			}
			if(z=='8')
			{
				cs1:
				int TX,TY,_f,_s;
				printf("\n输入修改位置的行和列,用空格隔开。若修改成-1则无法走到此格。当前坐标: %d行 %d列\n",x,y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
				cout<<'>';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				cin>>TX>>TY;
				if(TX<1 or TX>m or TY<1 or TY>n or a[TX][TY]==-1)
				{
					cout<<"位置不存在。\n";
					goto cs1;
				}
				printf("\n输入修改成的数。\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
				cout<<'>';
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
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
			}
		}
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
		cout<<"YOU WIN!!!恭喜通关!!!";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		_d=0;
		repl:
		cout<<"\n输入1重新开玩,输入2结束游戏。提示:重新开玩仍然保留存档！\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		cout<<'>';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		cin>>f;
		if(f==2)break;
		else if(f==1)goto chR;
		else
		{
			err();
			goto repl;
		}
	}
	cout<<"\n你想复制你玩的地图吗？\n1 yes, 0 no.\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
	cout<<'>';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	cin>>f;
	if(f==1)
	{
		cout<<"\n样式1:\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),112);
		cout<<m<<' '<<n<<endl;
		for(f=1;f<=m;f++)
		{
			for(s=1;s<=n;s++)
			{
				printf("%d",a[f][s]);
			}
			if(f<m)printf("\n");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		cout<<"\n\n样式2:\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),112);
		cout<<m<<' '<<n<<endl;
		for(f=1;f<=m;f++)
		{
			for(s=1;s<n;s++)
			{
				printf("%d ",a[f][s]);
			}printf("%d",a[f][n]);
			if(f<m)printf("\n");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		cout<<"\ncopy it!\n";
		system("pause");
	}
	return 0;
}
