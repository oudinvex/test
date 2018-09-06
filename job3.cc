#include<iostream>
#include<string>
using namespace std;
class stringup:public string
{
public:
	stringup();
	stringup(const char* str);
};

stringup::stringup()
{
}
stringup::stringup(const char* str):string(str)
{
}

int main()
{
	stringup str="learning";
	cout<<str.size()<<endl;
	return 0;
}
