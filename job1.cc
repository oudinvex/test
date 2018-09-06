#include<string>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
class book
{
	private:
	int isbn;
	string name;
public:
	book():isbn(0),name("未知")
{
	cout<<"book()"<<endl;
}
	book(int isbn,const char* name):isbn(isbn),name(name)
{
}
	void show()
{
	cout<<isbn<<' '<<name<<endl;
}
	~book()
{
cout<<"end"<<isbn<<endl;
}
};
int main()
{
/*	book b2(2,"hi");
	book b1(1,"hallo");
	book b3(3,"hallo again");
	b1.show();
	b2.show();
	b3.show();*/
	book* b4=new book(4,"c++从入门到入土");
	b4->show();
	delete b4;
	cout<<"hellow git"<<endl;

	return 0;
}
