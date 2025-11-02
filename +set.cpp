#include <bits/stdc++.h>
#include <windows.h>
#include "hashPD.h"
#include "randomPD.h"
#define i_input _color(14);cout<<'>';_color();
#define ptf printf
#define ent ptf("\n");
using namespace std;
struct STR
{
	string str;
};
struct FileData
{
	string filename;       // 文件名
	string sha256;         // 文件SHA-256哈希值
	vector<STR> results;   // 原结果数据
};
void _color(int __c=7)//着色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),__c);
}
string getCurrentTimeString4Report() 
{
	time_t now = time(nullptr);
	tm* localTime = localtime(&now);
	
	ostringstream oss;
	oss << put_time(localTime, "%Y-%m-%d_%H-%M-%S");
	return oss.str();
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
	ptf("密钥生成成功, 输入文件名以保存(无需后缀)");
	_color();
	ent
	system("pause");
	do{i_input cin>>fn;}while(regex_match(fn,regex("^\\s+$")));
	
	string fn1=".\\user\\"+fn+".id";
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
		i_input ptf("2=设置玩家的话");ent
		i_input ptf("3=生成通关报告的报表");ent ent
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
			while(!playerswords.empty()&&playerswords.back()=='\n')
			{
				playerswords.pop_back();
			}
			
			ofstream outFile1(".\\+set\\playerswords.txt");
			
			if (!outFile1) 
			{
				cerr<<"无法保存文件"<<endl;
				continue;
			}
			
			outFile1<<playerswords;
			outFile1.close();
			cout<<"保存成功\n";
		}
		if(x=='3')
		{
			ptf("仅支持4.4及以上版本的2D's 3D Game生成的通关报告,即将遍历.\\report\\中所有以2ds3dgame-开头的文件");ent
			system("pause");
			ent
			
			vector<FileData> allResults;//存储所有文件的信息（文件名+哈希+结果）
			
			//遍历.\report下所有2ds3dgame-开头的文件
			vector<string> reportFiles;
			WIN32_FIND_DATA findData;
			HANDLE hFind=FindFirstFileA(".\\report\\2ds3dgame-*",&findData);
			
			if(hFind!=INVALID_HANDLE_VALUE)
			{
				do
				{
					// 排除目录，只处理文件
					if(!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
					{
						reportFiles.push_back(findData.cFileName);
						_color(11);
						ptf("找到文件: %s",findData.cFileName);
						_color();ent
					}
				}while(FindNextFileA(hFind,&findData)!=0);
				FindClose(hFind);
			}
			else
			{
				_color(12);
				ptf("未找到任何2ds3dgame-开头的文件");
				_color();ent
				system("pause");
				continue;
			}
			
			ent
			_color(10);
			ptf("共找到[%d]个文件", reportFiles.size());
			_color();
			ent ent
			
			//处理每个压缩文件
			for(const string& fileName : reportFiles)
			{
				_color(11);
				ptf("正在处理: %s",fileName.c_str());
				_color();ent
				
				//创建临时文件夹
				int randomNum=PD_random(10000000,99999999);
				string tempPath=".\\temp\\"+to_string(randomNum);
				string createTempCmd="mkdir \""+tempPath+"\"";
				system(createTempCmd.c_str());
				
				//提取压缩包中的result/resultLite.txt
				string zipPath=".\\report\\"+fileName;
				string sevenZCommand="7za.exe e \""+zipPath+"\" -o\""+tempPath+"\" \"result\\resultLite.txt\" -y";
				ptf("正在解压文件...");ent
				_color(6);
				system(sevenZCommand.c_str());
				_color();
				
				//检查提取是否成功
				string resultLitePath=tempPath+"\\resultLite.txt";
				ifstream resultFile(resultLitePath);
				if(!resultFile.is_open())
				{
					_color(12);
					ptf("解压失败,已跳过: %s",fileName.c_str());
					_color();ent ent
					system(("rd \""+tempPath+"\" /s /q").c_str());//清理临时文件夹
					continue;
				}
				
				//读取resultLite.txt内容
				vector<STR> results;
				string line;
				int lineCount=0;
				bool foundDash=false;
				
				//先读取到减号为止
				while(getline(resultFile,line))
				{
					if(line=="-")
					{
						foundDash=true;
						break;
					}
					results.push_back({line});
					lineCount++;
				}
				
				if(!foundDash)
				{
					_color(12);
					ptf("文件格式错误,未找到分隔符,已跳过: %s",fileName.c_str());
					_color();ent ent
					resultFile.close();
					system(("rd \""+tempPath+"\" /s /q").c_str());
					continue;
				}
				
//				string fileHash=PD_hash(zipPath,true);
				allResults.push_back({fileName,"",results});
				
				_color(10);
				ptf("成功提取: %s",fileName.c_str());
				_color();ent ent
				
				//清理临时文件和文件夹
				resultFile.close();
				system(("rd \""+tempPath+"\" /s /q").c_str());
			}
			
			//单独循环计算所有文件的SHA-256
			_color(11);
			ptf("开始计算所有文件的SHA-256...");
			_color();ent
			for(auto& fileData : allResults)
			{
				_color(9);
				ptf("正在计算: %s",fileData.filename.c_str());
				_color();ent
				
				string zipPath=".\\report\\"+fileData.filename;
				string fileHash=PD_hash(zipPath,true);
				
				fileData.sha256=fileHash;
			}
			ent
			
			_color(11);
			ptf("生成通关报告报表中...");
			_color();
			ent
			//生成CSV文件
			if (allResults.empty())
			{
				_color(12);
				ptf("没有数据可生成报表");
				_color();
				ent
				system("pause");
				continue;
			}
			
			string csvFileName=".\\report\\通关报告报表_"+getCurrentTimeString4Report()+".csv";
			ofstream csvFile(csvFileName);
			
			if(!csvFile.is_open())
			{
				_color(12);
				ptf("无法创建CSV文件");
				_color();ent
				system("pause");
				continue;
			}
			
			csvFile<<"2D's 3D Game 通关报告报表,"<<getCurrentTimeString4Report()<<endl
			<<"by IQ Online Studio @ github.com/iqonli/2ds3dgame"<<endl
			<<"这是一份csv文件，请勿直接修改，如果要修改请先另存为xlsx文件"<<endl
			<<"文件名,文件SHA-256,版本,通关时间,ID hash SHA-256,地图纯码,用时,出生位置,结束位置,最终步数,特性变量,特性text,作弊次数,开始Unix时间,结束Unix时间,计算机名,游戏时全部输入,游戏时有效输入"<<endl;
			for(const auto& fileData : allResults)
			{
				csvFile<<fileData.filename<<","<<fileData.sha256;
				for(size_t i=0;i<fileData.results.size();++i)
				{
					csvFile<<","<<fileData.results[i].str;
				}
				csvFile<<endl;
			}
			csvFile.close();
			
			_color(10);
			ptf("报表生成成功: %s\n",csvFileName.c_str());
			_color();ent
			system("pause");
			ent
		}
	}
	return 0;
}
