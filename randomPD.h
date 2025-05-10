#include <random>
using namespace std;

int PD_random(int a,int b)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(a, b);
	
	int random_num = dis(gen);
	return random_num;
}
