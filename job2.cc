#include<iostream>
#include<cstdio>
using namespace std;
class file
{
private:
	FILE* fp;

public:

	file(const char* data,const char * mode="r")
{
	fp=fopen(data,mode);
}
	void getfilesize(int& filesize);
	int read(void* buff, int size );
	void free();
	~file();
};
	
	void file::getfilesize(int& filesize)
{
	fseek(fp,0,SEEK_END);
	filesize=ftell(fp);
	rewind(fp);
}
	int file::read(void* buff, int size )
{
	fread(buff,1,size,fp);
	rewind(fp);
}
	void file::free()
{
	fclose(fp);
}
	file::~file()
{
	cout<<fp<<endl;
}
	int main()
{	file a("data");
	int c;
	file d(a);
	a.getfilesize(c);
	char b[60]="";
	char e[60]="";
	d.read(e,sizeof(e)-1);
	a.read(b,sizeof(b)-1);
	d.free();
cout<<b<<c<<'\n'<<e;
	int i,j,k;
	i=1;
	j=2;
	k=3;
	(i=j)=k;
cout<<i<<j<<k<<endl;
	return 0;
}
