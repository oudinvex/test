#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;


class string_dj : public string
{
public:
	string_dj();
	string_dj(const char* str);

	//新增方法
	operator int()
	{
		return ::atoi(this->c_str());
	}

	//同名覆盖
	int size() const
	{
		return 3;
	}
};


string_dj::string_dj()
{
}

string_dj::string_dj(const char* str):string(str)
{
}


int main()
{
	string_dj str1 = "hello";

	cout<<str1[2]<<endl;

	cin>>str1;

	cout<<int(str1)<<endl;

	cout<<str1<<endl;
	cout<<str1.size()<<endl;

	if(str1 == "abcdef")
	{
		cout<<"yes"<<endl;
	}
	else
	{
		cout<<"no"<<endl;
	}

	string_dj str2;
	str2 = str1;
	str2 = ",world...";
	string str3;
	str3 = str1 + str2;
	cout<<str3<<endl;

	return 0;
}
