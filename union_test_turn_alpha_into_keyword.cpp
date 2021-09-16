#include<bits/stdc++.h>
using namespace std; 

map <string,int> key;  //关键字枚举标记 
map <string,int> cnt;  //关键字出现数量记录 

void InitKey()  //初始化关键字标记 
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
	//初始化关键字 
	InitKey();
	
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
	
	//读取文件内容（按字符）并合并成单词 
	vector <string> word;  //用于存储所有关键字 
	char c;  //string可以直接+char 
	string a_word="";
	bool last_is_alpha=false;  //上一个字符是否是字母 
	while((c=fgetc(fp))!=EOF){                        
		if(isalpha(c)){          
			a_word+=c;
			last_is_alpha=true;
		}
		else{
			if(last_is_alpha){  //一个单词结束 
				if(key[a_word]){  //该单词是关键字 
					word.push_back(a_word);
					cnt["total"]++; 
					cnt[a_word]++;
				}
				a_word="";	 
			}
			last_is_alpha=false;
		}
	}
	if(key[a_word]){  //该单词是关键字 
		word.push_back(a_word);
		cnt["total"]++; 
		cnt[a_word]++;
	}
	fclose(fp); 
	
	//完成等级1 输出
	map <string,int>::iterator iter;  //迭代器遍历 
	for(iter=cnt.begin();iter!=cnt.end();iter++){
		cout<<iter->first<<" num: "<<iter->second<<endl;
	}
	return 0;
} 
