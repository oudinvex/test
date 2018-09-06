#include <iostream>
#include <string>
using namespace std;


class Student
{
private:
	int sno;
	string name;

public:
	Student();
	Student(int sno, string name);

	void show();

	static string school; //定义静态属性

	static void test(); //声明静态方法
};


//静态属性初始化
string Student::school = "武汉大学";


Student::Student()
{
}


Student::Student(int sno, string name)name(name)
{
	this->sno = sno;
}


void Student::show()
{
	cout<<sno<<' '<<name<<endl;
}


void Student::test()
{
	//不能使用this指针
	//name = "张三"; //错误
	//show(); //错误
	
	Student::school = "华中科技大学";
	cout<<school<<endl;
}


int main()
{
	Student::school = "清华大学";
	cout<<Student::school<<endl;
	Student::test();

	Student s1, s2(1002, "李四", '1');
	s1.school = "北京大学";
	cout<<s2.school<<endl;
	s2.test();
	s1.show();
	s2.show();
	

	return 0;
}
