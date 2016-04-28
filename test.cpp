#include <iostream>
#include <map>
#include <cstdlib>
#include <algorithm>

int r() {return rand()%100+1;}

int main()
{
	std::map<int,int> m;
	for(int i=0;i<20;++i)
	{
		int n = r();
		std::cout<<n<<std::endl;
		m[n] = i;
	}
	std::cout<<std::endl;
	std::map<int,int>::iterator n = m.begin();
	while(n!=m.end())
	{
		std::cout<<n->first<<std::endl;
		++n;
	}
	return 0;
}
