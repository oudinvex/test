#include<iostream>
#include<string>
#include<list>
struct 	Book
{
	int isbn;
	std::string name;
	float price;
	//friend std::istream operator>>(std::istream& in,Book& b);
};

std::istream operator>>(std::istream& in,Book& b)
{
	std::cout<<"请按提示输入书籍信息：\n";
	std::cout<<"ISBN:";
	in >> b.isbn;
	std::cout<<"书名";
	in>>b.name;
	std::cout<<"单价：";
	in>>b.price;
}
int main()
{
	std::list<Book> books;
	Book b;
	for(int i=0;i<5;i++)
	{
	std::cin>>b;
	books.push_back(b);
	}
	return 0;
}


