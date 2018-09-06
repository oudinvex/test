#include <iostream>
#include <string>
using namespace std;


class Student
{
private:
	int sno;
	string name;

	const char sex; //定义常属性
public:
	static const string school; //静态常属性

	mutable int i;

public:
	Student();
	Student(int sno, string name, char sex);
	explicit Student(int sno);

	void show();
	void show() const;

	void test() const; //声明常方法

	void fun();
};


const string Student::school = "北京大学";


Student::Student():sex('0')
{
}

Student::Student(int sno):sno(sno)
{
}

Student::Student(int sno, string name, char sex):name(name), sex(sex)
{
	this->sno = sno;
}


void Student::fun()
{
}

void Student::show()
{
	cout<<"show()"<<endl;
	//this->sex = '1'; //错误
	cout<<sno<<' '<<name<<' '<<sex<<endl;
}


void Student::show() const
{
	cout<<"show() const"<<endl;
	cout<<sno<<' '<<name<<' '<<sex<<endl;
}


//定义常方法
void Student::test() const
{
	i = 3;
	//this->sno++; //错误
	//this->name = "未知"; //错误
	cout<<this->sno<<' '<<this->name<<endl;

	show(); //错误，在常方法中不能调用非常方法
}


int main()
{
	Student s1(1001, "张三", '0'), s2;
	s1.test();
	s1.show();

	//常对象
	const Student s3(1003, "王五", '1');
	s3.show();
	//s3.fun(); //错误
	s3.i++;

	//常对象引用
	const Student& s4 = s1;
	s4.show();
	//s4.fun(); //错误
	s4.i = 6;

	//常对象指针
	const Student* p = &s1;
	p->show();
	//p->fun(); //错误
	p->i = 8;

	cout<<s1.i<<endl;
	

	cout<<Student::school<<endl;

	Student s = Student(1005);
	Student ss;
	ss = Student(1005);

	return 0;
}
