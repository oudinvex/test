#include<iostream>
#include<cstring>
using namespace std;

class test
{
	private:
	
	char* buffer;
	

public:
	test();
	test(const char* str );
	test(const test& str);
	~test();

	int size() const;
	bool empty()const;
	void clear();
	void add(const char* str);
	void insert(int index,const char* str);
	void remove(const char* str);
	void replace(const char* oldstr,const char* newstr);
	const char* serchstr()const;
	int to_int() const;
	float to_float() const;
	
	test operator+(const test& str);
	test operator=(const test& str);
	char operator[](int index);
	bool operator==(const test& str);
	bool operator!=(const test& str);
	bool operator>(const test& str);
	operator int();
	operator float();
	friend istream& operator>>(istream& in,const test& str);
	friend ostream& operator<<(ostream& out,const test& str);
};
	test::test()
{
	buffer=NULL;
}
	int test::size()const
{
	return strlen(buffer);
}
	bool test::empty()const
{
	return (buffer[0]=='\0');
}
	void test::clear()
{
	buffer[0]='\0';
}
	test::test(const char* str)
{
	buffer = new char[strlen(str)+1];
	strcpy(buffer,str);
}

	test::test(const test& str)
{
	buffer = new char [strlen(str.buffer)+1];
	strcpy(buffer,str.buffer);
}
	test::~test()
{
	delete[]buffer;
}

	test test::operator=(const test& str)
{
	delete []buffer;
	buffer=new char[strlen[str.buffer]+1];
	strcpy(buffer,str.buffer);
}
int main()
{
	test str;
	cout<<str.size()<<endl;
	//cout<<str.empty()<<endl;


	return 0;
}
