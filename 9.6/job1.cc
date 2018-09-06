/*
 * 功能1：拷贝文件
 * 		失败返回false成功返回ture
 *
 *功能2：求文件长度
 *		失败返回0成功返回长度int
 * 功能3：输出文件md5值
 * 作者：oudinvex 2018.9.6
 */

#include<iostream>
#include<fstream>
#include <cstdio>
#include"md5.h"
using namespace std;
int copyfile(char *data1,char *data2)
{
	ifstream in;
	ofstream out;
	in.open(data1,ios::binary);
	if(in.fail())
	{
	cout<<"文件不存在"<<endl;
	in.close();
	out.close();
	return 0;
	}
	out.open(data2,ios::binary | ios::trunc);
	if(out.fail())
{
	cout<<"文件不存在"<<endl;
	in.close();
	out.close();
	return 0;
}
	else
{
	out<<in.rdbuf();
	out.close();
	in.close();
	return 1;
}
}
int main(int argc,char *argv[3])
{
if(argc!=3)
{
	cout<<"无法识别指令"<<endl;
}
else
{
	if(copyfile(argv[1],argv[2]))
	{
	cout<<"复制成功"<<endl;
	}
	else
	{	
	cout<<"复制失败"<<endl;
	}
}
	ofstream num;
	num.open(argv[1],ios::in | ios::ate);
	if(num.fail())
{
	cout<<"打开失败"<<endl;
	num.close();
}
	else
{
	int number;
	number=num.tellp();
	cout<<"文件大小为："<<number<<" 字节"<<endl;
	num.close();
	char* a=NULL;
	a = new char[number];
	if(!(a = new char[number]))
	{
	cout<<"内存不足"<<endl;
	return 0;
	}
	ifstream md5;
	md5.open(argv[1],ios::in | ios::binary);
	if(md5.fail())
	{
	cout<<"md5加密失败"<<endl;
	md5.close();
	}
	else
	{
	md5.read(a,number);
	cout<<md5_encrypt(a,number)<<endl;
	md5.close();
	}
	delete a;
}	
		
	return 0;
}
