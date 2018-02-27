#include <iostream>

using namespace std;

int main()
{
	int a=1, b=2;
	pair<int, int> tmp;
	tmp=make_pair(a, b);
	
	cout<<tmp.first<<' '<<tmp.second;
	
	return 0;
}