#include <iostream>
#include <cstring>
using namespace std;



class Animal
{
private:
	int id;
	char name[44];

public:
	Animal()
	{
	}

	Animal(int id, const char* name):id(id)
	{
		strcpy(this->name, name);
	}	

	void eat()
	{
		cout<<"I can eat!"<<endl;
	}
};


class Horse : virtual public Animal //虚继承
{
public:
	Horse()
	{
	}

	Horse(int id, const char* name):Animal(id, name)
	{
	}	

	void run()
	{
		cout<<"I can run fast!"<<endl;
	}

};


class Donkey : virtual public Animal //虚继承
{
public:
	Donkey()
	{
	}

	Donkey(int id, const char* name):Animal(id, name)
	{
	}	

	void carry()
	{
		cout<<"I can carry more!"<<endl;
	}

};


class Mule : virtual public Horse, virtual public Donkey 
{
public:
	Mule()
	{
	}

	Mule(int id, const char* name):Horse(id, name), Donkey(id, name)
	{
	}
};




int main()
{
	Mule m;

	cout<<sizeof m<<endl;
	
	m.run();
	m.carry();	
	
	return 0;
}
