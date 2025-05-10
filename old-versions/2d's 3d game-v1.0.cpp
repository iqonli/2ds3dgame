#include <bits/stdc++.h>
#include <windows.h> 
using namespace std;
int m,n,f,s,bir,fin,x,y,cc;
int a[1000][1000];
int cl[]={0,160,224,240,159,176,207};
char z;
void choose()
{
	int a;
	cout<<"ok. input a num (1-1).\n";
	cin>>a;
	if(a==1)
	{
		cout<<"16*16"<<endl;
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
	}
	cout<<"copy and paste the map.\n";
	return ;
}
void sset()
{
	if(bir==1)x=1,y=1;
	if(bir==2)x=1,y=n;
	if(bir==3)x=m,y=1;
	if(bir==4)x=m,y=n;
	return ;
}
void otpt()
{
	system("cls");
	int f,s;
	for(f=1;f<=m;f++)
	{
		for(s=1;s<=n;s++)
		{
			if(x==f and y==s)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cl[cc]);
				printf("%d",a[f][s]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				printf(" ");
				continue;
			}
			printf("%d ",a[f][s]);
		}
		printf("\n");
	}
	return ;
}
bool winORnot()
{
	if(fin==1)return x==1&&y==1;
	if(fin==2)return x==1&&y==n;
	if(fin==3)return x==m&&y==1;
	if(fin==4)return x==m&&y==n;
}
int main()
{
	ch:
	cout<<"hello! welcome to the 2D's 3D PaoKu. input your size m & n. or, input -1 and -1 to choose map, input -2 and -2 to see the rules.\n";
	cin>>m>>n;
	if(m==-1 and n==-1)
	{
		choose();
		goto ch;
	}
	if(m==-2 and n==-2)
	{
		puts("by Alone, IQ Online Studio. QQ:34067513 See the website: https://melonchats.github.io/melon/a.html");
		puts("this is a game that use 2d number to play 3d PaoKu. like Minecraft, the nums in map is the heights of the blocks.");
		puts("for example, the num 2 just 2 blocks in MC.");
		puts("To go up, you can only go up 1 height. like 1 to 2, 2 to 3 and so on. and you can only move in four directions: front ^, back v, left <, right >.");
		puts("To go down, you can go down 1 height or 2 height, if above this num, you'll fall and lose some health. isn't it? and you can move in eight directions.");
		puts("To go down or go front, you should notice: if your direction is left-front, right-front, left-back, right-back, you can move when the other two num beside below or equal your now num and expect num.");
		puts("like this:\n1 2\n2 1\nwhen you are in 1, you can't use right-back or left-front to the other 1, but you can use right-front and left-back from 2 to 2.\n");
		goto ch;
	}
	cout<<"now, input your map (warning: do not input number <=0 or >=10)\nyou can input space or enter or not input between two values.\n";
	for(f=1;f<=m;f++)
		for(s=1;s<=n;s++)
			scanf("%1d",&a[f][s]);
	for(f=0;f<=m+1;f++)
		for(s=0;s<=n+1;s++)
			if(f==0 or f==m+1 or s==0 or s==n+1)
				a[f][s]=-1;
	
	while(1)
	{
		ch1:
		cout<<"choose a birth point and a finish point.\n<^1  ^>2  <v3  v>4\ninput bir & fin.\n";
		cin>>bir>>fin;
		if(bir==fin)
		{
			cout<<"do not input the same number!\n";goto ch1;
		}
		if(bir<1 or bir>4 or fin<1 or fin>4)
		{
			cout<<"wrong num.\n";goto ch1;
		}
		chC:
		cout<<"choose a NOW color:\ngreen 1, yellow 2, white 3, blue 4, light-blue 5, red 6.\n";
		cin>>cc;
		if(cc<1 or cc>6)
		{
			cout<<"wrong num.\n";goto chC;
		}
		chR:
		sset();
		while(!winORnot())
		{
			ch2:
			otpt();
			printf("input and then press enter:\nup w  down s  left a  right d\n<^ q  ^> e  <v z  v> c\npress R (big) to replay, C to reColor.\n");
			cin>>z;
			if(z=='w')
			{
				if(a[x-1][y]==-1 or a[x-1][y]-a[x][y]>1 or a[x-1][y]-a[x][y]<-2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
					cout<<"YOU CANNOT DO THIS!!!\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					system("pause");
					goto ch2;
				}
				x--;
			}
			if(z=='s')
			{
				if(a[x+1][y]==-1 or a[x+1][y]-a[x][y]>1 or a[x+1][y]-a[x][y]<-2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
					cout<<"YOU CANNOT DO THIS!!!\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					system("pause");
					goto ch2;
				}
				x++;
			}
			if(z=='a')
			{
				if(a[x][y]-1==-1 or a[x][y-1]-a[x][y]>1 or a[x][y-1]-a[x][y]<-2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
					cout<<"YOU CANNOT DO THIS!!!\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					system("pause");
					goto ch2;
				}
				y--;
			}
			if(z=='d')
			{
				if(a[x][y+1]==-1 or a[x][y+1]-a[x][y]>1 or a[x][y+1]-a[x][y]<-2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
					cout<<"YOU CANNOT DO THIS!!!\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					system("pause");
					goto ch2;
				}
				y++;
			}
			
			if(z=='q')
			{
				if(a[x-1][y-1]==-1 or a[x-1][y-1]-a[x][y]>0 or a[x-1][y-1]-a[x][y]<-2 or a[x-1][y]>a[x][y] or a[x][y-1]>a[x][y])
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
					cout<<"YOU CANNOT DO THIS!!!\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					system("pause");
					goto ch2;
				}
				x--,y--;
			}
			if(z=='e')
			{
				if(a[x-1][y+1]==-1 or a[x-1][y+1]-a[x][y]>0 or a[x-1][y+1]-a[x][y]<-2 or a[x-1][y]>a[x][y] or a[x][y+1]>a[x][y])
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
					cout<<"YOU CANNOT DO THIS!!!\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					system("pause");
					goto ch2;
				}
				x--,y++;
			}
			if(z=='z')
			{
				if(a[x+1][y-1]==-1 or a[x+1][y-1]-a[x][y]>0 or a[x+1][y-1]-a[x][y]<-2 or a[x+1][y]>a[x][y] or a[x][y-1]>a[x][y])
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
					cout<<"YOU CANNOT DO THIS!!!\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					system("pause");
					goto ch2;
				}
				x++,y--;
			}
			if(z=='c')
			{
				if(a[x+1][y+1]==-1 or a[x+1][y+1]-a[x][y]>0 or a[x+1][y+1]-a[x][y]<-2 or a[x+1][y]>a[x][y] or a[x][y+1]>a[x][y])
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
					cout<<"YOU CANNOT DO THIS!!!\n";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
					system("pause");
					goto ch2;
				}
				x++,y++;
			}
			if(z=='R')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
				cout<<"ARE YOU SURE???";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
				cout<<"\n1 yes, 0 no.\n";
				cin>>f;
				if(f==1)
				{
					goto chR;
				}
			}
			if(z=='C')
			{
				chC1:
				cout<<"choose a NOW color:\ngreen 1, yellow 2, white 3, blue 4, light-blue 5, red 6.\n";
				cin>>cc;
				if(cc<1 or cc>6)
				{
					cout<<"wrong num.\n";goto chC1;
				}
			}
		}
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),207);
		cout<<"YOU WIN!!!\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
		cout<<"input 1 to replay, 0 to say goodbye.\n";
		cin>>f;
		if(f==0)break;
		else goto chR;
	}
	cout<<"do you want to copy the map?\n1 yes, 0 no.\n";
	cin>>f;
	if(f==1)
	{
		cout<<m<<'*'<<n<<endl;
		for(f=1;f<=m;f++)
		{
			for(s=1;s<=n;s++)
			{
				printf("%d",a[f][s]);
			}
			printf("\n");
		}
		cout<<"\ncopy it!\n";
		system("pause");
	}
	return 0;
}
