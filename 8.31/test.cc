#include<iostream>
using namespace std;
class a
{
	public:
	virtual void test1()=0;
	void test2()
{
	cout<<"a(test2)"<<endl;
}
	virtual void test3()
{
	cout<<"a(test3)"<<endl;
}
	virtual ~a(){};
};

class b:public a
{
public:
	virtual ~b(){};
	void test1()
{
	cout<<"b(test1)"<<endl;
}
	void test2()
	{
	cout<<"b(test2)"<<endl;
	}
	void test3()
	{	
	cout<<"b(test3)"<<endl;
	}
};
	int main()
{
	a *flag=new b;
	flag->test1();
	flag->test2();
	flag->test3();
	b *flag2=new b;
	flag2->test1();
	flag2->test2();
	flag->test3();

	return 0;
}
