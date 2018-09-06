#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fp=fopen("code.zip","r");
	fseek(fp,-8,SEEK_END);
	char a[20];
	fread(a,1,8,fp);
	printf("%s",a);
	return 0;
}
