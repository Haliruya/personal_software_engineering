#include<bits/stdc++.h>
using namespace std;

int main()
{
	//输入文件路径和完成等级 
	char file_path[100];
	int completion_level;
	cout<<"请输入文件路径和完成等级："; 
	cin>>file_path>>completion_level;
	
	//打开文件
	FILE * fp;
	extern int errno;
	fp=fopen(file_path,"r");
	if(fp==NULL)
	{
		printf("cant't open the file %s.\n",file_path);
		printf("errno:%d\n",errno);
		printf("ERR:%s\n",strerror(errno));
		return -1;
	}
	else{
		cout<<"open file success."<<endl;
	}
	return 0;
}
