#include<bits/stdc++.h>
using namespace std; 

map <string,int> key;  //�ؼ���ö�ٱ�� 
map <string,int> cnt;  //�ؼ��ֳ���������¼ 

void InitKey()  //��ʼ���ؼ��ֱ�� 
{
	key["auto"]=key["double"]=key["int"]=key["struct"]
	=key["break"]=key["else"]=key["long"]=key["switch"]
	=key["case"]=key["enum"]=key["register"]=key["typedef"]
	=key["char"]=key["extern"]=key["return"]=key["union"]
	=key["const"]=key["float"]=key["short"]=key["unsigned"]
	=key["continue"]=key["for"]=key["signed"]=key["void"]
	=key["default"]=key["goto"]=key["sizeof"]=key["volatile"]
	=key["do"]=key["if"]=key["static"]=key["while"]=1;
}

int main()
{
	//��ʼ���ؼ��� 
	InitKey();
	
	//�����ļ�·������ɵȼ� 
	char file_path[100];
	int completion_level;
	cout<<"�������ļ�·������ɵȼ���"; 
	cin>>file_path>>completion_level;
	
	//���ļ�
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
	
	//��ȡ�ļ����ݣ����ַ������ϲ��ɵ��� 
	vector <string> word;  //���ڴ洢���йؼ��� 
	char c;  //string����ֱ��+char 
	string a_word="";
	bool last_is_alpha=false;  //��һ���ַ��Ƿ�����ĸ 
	while((c=fgetc(fp))!=EOF){                        
		if(isalpha(c)){          
			a_word+=c;
			last_is_alpha=true;
		}
		else{
			if(last_is_alpha){  //һ�����ʽ��� 
				if(key[a_word]){  //�õ����ǹؼ��� 
					word.push_back(a_word);
					cnt["total"]++; 
					cnt[a_word]++;
				}
				a_word="";	 
			}
			last_is_alpha=false;
		}
	}
	if(key[a_word]){  //�õ����ǹؼ��� 
		word.push_back(a_word);
		cnt["total"]++; 
		cnt[a_word]++;
	}
	fclose(fp); 
	
	//��ɵȼ�1 ���
	map <string,int>::iterator iter;  //���������� 
	for(iter=cnt.begin();iter!=cnt.end();iter++){
		cout<<iter->first<<" num: "<<iter->second<<endl;
	}
	return 0;
} 
