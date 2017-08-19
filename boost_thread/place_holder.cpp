#include"which_to_run.h"
#ifdef PALCE_HOLDER
#include<functional>
#include<iostream>
using namespace std;
void f(int a, int b, int c)
{
	cout << a << " " << b << " " << c<<endl;
}

int main()
{
	using namespace std::placeholders;
	auto f1 = std::bind(f,1,2,_1);
	f1(200);
	getchar();
	
}
#endif