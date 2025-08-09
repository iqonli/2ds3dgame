#include <bits/stdc++.h>
#include <windows.h>
#include "hashPD.h"
#include "randomPD.h"
#define i_input _color(14);cout<<'>';_color();
#define ptf printf
#define ent ptf("\n");
using namespace std;
void _color(int __c=7)//着色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),__c);
}
void createID()
{
	long long n,f;
	string chara="!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	string result="",fn;
	
	ent
	_color(10);
	ptf("指定长度");
	_color();
	ent
	do{i_input cin>>n;}while(n<=0);
	
	for(f=0;f<n;f++)
	{
		result+=chara.at(PD_random(0,chara.size()-1));
	}
	
	ent
	_color(10);
	ptf("密钥生成成功, 输入文件名以保存");
	_color();
	ent
	system("pause");
	do{i_input cin>>fn;}while(regex_match(fn,regex("^\\s+$")));
	
	string fn1=fn+".txt";
	ofstream outFile1(fn1);
	
	if (!outFile1) 
	{
		cerr<<"无法保存文件"<<endl;
		return;
	}
	
	outFile1<<result;
	outFile1.close();
	
	_color(48);
	cout<<fn1;
	_color(176);
	ptf("已成功保存");
	_color();
	ent
	return;
}
int main()
{
	while(1)
	{
		char x;
		ptf("欢迎使用 初始设置 for 2D's 3D Game");ent
		i_input ptf("1=快速创建ID文件");ent
		i_input ptf("2=设置玩家的话");ent ent
		i_input cin>>x;
		if(x=='1')
		{
			createID();
		}
		if(x=='2')
		{
			ptf("作者很懒, 真的很懒, 这部分不支持打开现有的玩家的话。如果要用文本编辑器编辑玩家的话, 请去notepad。");ent
			ptf("开创这部分功能是因为C++ fstream只有在打开本地编码(ANSI)的txt时不会乱码, 而大部分人使用notepad保存时没选ANSI。");ent
			ptf("所以, 为了避免编码问题, 写好玩家的话后, 粘贴到下面, 本部分功能会自动以ANSI编码保存到玩家的话文件。");ent ent
			system("pause");
			ptf("输入两个连续的空行以结束"); i_input
			
			string playerswords="",line;
			int ln=0;
			
			while(getline(cin,line))
			{
				if (line.empty())
				{
					ln++;
					if(ln>=2)
					{
						break;
					}
					playerswords+="\n";
				}
				else
				{
					ln=0;
					playerswords += line+"\n";
				}
			}
			if(!playerswords.empty()&&playerswords.back()=='\n')
			{
				playerswords.pop_back();
			}
			playerswords+='\n';
			
			ofstream outFile1(".\\+set\\playerswords.txt");
			
			if (!outFile1) 
			{
				cerr<<"无法保存文件"<<endl;
				continue;
			}
			
			outFile1<<playerswords;
			outFile1.close();
		}
	}
	return 0;
}
