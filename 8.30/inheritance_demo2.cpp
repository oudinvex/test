#include <iostream>
#include <string>
using namespace std;


class Person
{
private:
	int id;
	string name;
	char* phone;

public:
	Person()
	{
		phone = new char[12];
		phone[0] = '\0';
		cout<<"Person()"<<endl;
	}

	Person(int id, string name):id(id), name(name)
	{
		phone = new char[12];
		phone[0] = '\0';
		cout<<"Person(int, string)"<<endl;
	}

	~Person()
	{
		delete []phone;
		cout<<"~Person()"<<endl;
	}

	void show() const
	{
		cout<<id<<' '<<name<<endl;
	}
};


class English : public Person
{

};

class American : public Person
{

};


class Chinese : public Person
{
private:
	bool taijian;
	char* gongfu;

public:
	Chinese():Person(1000, "未知")
	{
		gongfu = new char[101];
		cout<<"Chinese()"<<endl;
	}

	Chinese(int id, string name, bool taijian):Person(id, name), taijian(taijian)
	{
		gongfu = new char[101];
		cout<<"Chinese(int, string, bool)"<<endl;
	}

	~Chinese()
	{
		delete []gongfu;
		cout<<"~Chinese()"<<endl;
	}

	void show() const //同名覆盖
	{
		Person::show(); //调用父类中的show方法
		cout<<taijian<<endl;
	}

	void guonian()
	{
		cout<<"I can 过年！"<<endl;
	}
	
};


class HubeiRen : public Chinese
{
public:
	HubeiRen()
	{
		cout<<"HubeiRen()"<<endl;
	}	

	HubeiRen(int id, string name, bool tianjian):Chinese(id, name, tianjian)
	{
	}
};



int main()
{
	Chinese c1;
	c1.show();

	Chinese c2(1001, "张三", true);
	
	c2.show();

	HubeiRen h;

	return 0;
}
