#include<bits/stdc++.h>
using namespace std;

int main()
{
	char file_path[100];
	int completion_level;
	cout<<"请输入文件路径和完成等级："; 
	cin>>file_path>>completion_level;
	
	//打开文件
	FILE * fp;
	extern int errno;
	fp=fopen(file_path,"r");
	char c;
	while((c=fgetc(fp))!=EOF){
		cout<<"读出字符："<<c<<endl;
	}
	return 0;
}
