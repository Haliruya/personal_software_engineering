#include<bits/stdc++.h>
using namespace std;

int main()
{
	char file_path[100];
	int completion_level;
	cout<<"�������ļ�·������ɵȼ���"; 
	cin>>file_path>>completion_level;
	
	//���ļ�
	FILE * fp;
	extern int errno;
	fp=fopen(file_path,"r");
	char c;
	while((c=fgetc(fp))!=EOF){
		cout<<"�����ַ���"<<c<<endl;
	}
	return 0;
}
