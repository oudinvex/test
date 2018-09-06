#include <iostream>
using namespace std;


class A
{
private:
	int i;
	
	void test()
	{
		B x;
		dj y;
	}

	typedef struct
	{
		int m;
		double n;
	} B;

public:
	typedef int dj;	

};


int main()
{
	//A::B x;
	A::dj y = 100;
	cout<<y<<endl;
	return 0;
}
