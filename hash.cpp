#include <bits/stdc++.h>
#include <windows.h>
#include <wincrypt.h>
using namespace std;
//Written by ChatGPT-4o


string hash_sha256(const std::string& filePath) {
	HCRYPTPROV hProv = NULL;
	HCRYPTHASH hHash = NULL;
	HANDLE hFile = NULL;
	DWORD bytesRead = 0;
	BYTE buffer[4096];
	std::string result;
	
	// 打开文件
	hFile = CreateFileA(filePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return "Error: Unable to open file.";
	}
	
	// 获取加密服务提供者 (PROV_RSA_AES)
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
		CloseHandle(hFile);
		return "Error: CryptAcquireContext failed.";
	}
	
	// 创建 SHA-256 哈希对象
	if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
		CryptReleaseContext(hProv, 0);
		CloseHandle(hFile);
		return "Error: CryptCreateHash failed.";
	}
	
	// 读取文件并计算哈希
	while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
		if (!CryptHashData(hHash, buffer, bytesRead, 0)) {
			CryptDestroyHash(hHash);
			CryptReleaseContext(hProv, 0);
			CloseHandle(hFile);
			return "Error: CryptHashData failed.";
		}
	}
	
	// 获取哈希值的长度
	DWORD hashSize = 0;
	DWORD sizeLen = sizeof(hashSize);
	if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&hashSize, &sizeLen, 0)) {
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		CloseHandle(hFile);
		return "Error: CryptGetHashParam failed.";
	}
	
	// 获取实际的哈希值
	BYTE* hashValue = new BYTE[hashSize];
	if (!CryptGetHashParam(hHash, HP_HASHVAL, hashValue, &hashSize, 0)) {
		delete[] hashValue;
		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
		CloseHandle(hFile);
		return "Error: CryptGetHashParam failed.";
	}
	
	// 将哈希值转换为十六进制字符串
	for (DWORD i = 0; i < hashSize; ++i) {
		char hex[3];
		sprintf_s(hex, sizeof(hex), "%02x", hashValue[i]);
		result.append(hex);
	}
	
	// 清理资源
	delete[] hashValue;
	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hFile);
	
	return result;
}

string hiphopsh95(string _hash) {
	// 95进制字符集
	const string BASE95 = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_abcdefghijklmnopqrstuvwxyz{|}~";
	
	// 存储大数的每一位
	vector<int> decimal;
	decimal.push_back(0);
	
	// 16进制转10进制（使用大数加法和乘法）
	for(char c : _hash) {
		// 获取当前位的值
		int digit;
		if(c >= '0' && c <= '9') digit = c - '0';
		else if(c >= 'a' && c <= 'f') digit = c - 'a' + 10;
		else if(c >= 'A' && c <= 'F') digit = c - 'A' + 10;
		else continue; // 跳过无效字符
		
		// 乘16
		for(int& d : decimal) {
			d *= 16;
		}
		
		// 处理进位
		for(int i = 0; i < decimal.size(); i++) {
			if(i == 0) decimal[i] += digit;
			if(decimal[i] >= 10000) {
				if(i + 1 == decimal.size()) 
					decimal.push_back(0);
				decimal[i + 1] += decimal[i] / 10000;
				decimal[i] %= 10000;
			}
		}
	}
	
	// 转换为95进制
	string result;
	while(!decimal.empty() && !(decimal.size() == 1 && decimal[0] == 0)) {
		int remainder = 0;
		for(int i = decimal.size() - 1; i >= 0; i--) {
			long long current = remainder * 10000LL + decimal[i];
			decimal[i] = (int)(current / 95);
			remainder = (int)(current % 95);
		}
		result = BASE95[remainder] + result;
		
		// 删除前导零
		while(!decimal.empty() && decimal.back() == 0) {
			decimal.pop_back();
		}
	}
	
	return result.empty() ? string(1, BASE95[0]) : result;
}

//----------------
const std::string HIPHOPSH_CHARS = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_abcdefghijklmnopqrstuvwxyz{|}~";

std::string hiphopsh951(std::string _hash) {
	// Convert hex string to unsigned long long
	unsigned long long decimal = 0;
	for (char hex : _hash) {
		decimal *= 16;
		if (hex >= '0' && hex <= '9') {
			decimal += hex - '0';
		} else if (hex >= 'a' && hex <= 'f') {
			decimal += hex - 'a' + 10;
		} else if (hex >= 'A' && hex <= 'F') {
			decimal += hex - 'A' + 10;
		}
	}
	
	// If decimal is 0, return the first character
	if (decimal == 0) return std::string(1, HIPHOPSH_CHARS[0]);
	
	// Convert to 95-base representation
	std::string result;
	while (decimal > 0) {
		result = HIPHOPSH_CHARS[decimal % 95] + result;
		decimal /= 95;
	}
	
	return result;
}
int main()
{
	int a;
	string b;
	cout<<"1计算文件sha256;2hash转95-hip-hopsh";
	cin>>a;
	if(a==1)
	{
		cin>>b;
		cout<<hash_sha256(b);
	}
	if(a==2)
	{
		aa:
		cin>>b;
		cout<<hiphopsh95(b);
		goto aa;
//		cout<<endl<<hiphopsh951(b);
	}
	return 0;
}
