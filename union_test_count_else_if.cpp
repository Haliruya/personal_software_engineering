#include<bits/stdc++.h>
using namespace std; 

int cnt=0;
map <string,int> key;  //关键字枚举标记 
vector <string> if_and_else_in_file;  //用于存储文件中出现的所有if，else，else-if以及花括号 
int else_if_cnt = 0;

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
	char c;  //string可以直接+char 
	string a_word = "";
	bool last_is_alpha = false;  //上一个字符是否是字母 
	bool last_is_else = false;  //上一个单词是否是else

	while ((c = fgetc(fp)) != EOF) {
		if (isalpha(c)) {
			a_word += c;
			last_is_alpha = true;
		}
		else {
			if (last_is_alpha) {  //一个单词结束 
				if (key[a_word]) {  //该单词是关键字 
					if (a_word == "else") {
						if_and_else_in_file.push_back("else");
						if (c != ' ' && c != '\n') {
							last_is_else = false;
						}
						else {
							last_is_else = true;
						}
					}
					if (a_word == "if") {
						if (last_is_else) {
							last_is_else = false;
							if_and_else_in_file[if_and_else_in_file.size() - 1] += "_if";
							else_if_cnt++;
						}
						else {
							if_and_else_in_file.push_back("if");
						}
					}
				}
				a_word = "";
			}
			else {
				if (c != ' ' && c != '\n') {
					last_is_else = false;
				}
			}
			if (c == '{' || c == '}') {
				string temp = "";
				temp += c;
				if_and_else_in_file.push_back(temp);
			}
			last_is_alpha = false;
		}
	}
	fclose(fp);
	
	//输出所有的if、else、else-if和花括号 
	cout << "num of else-if is:" << else_if_cnt << endl;
	for (int i = 0;i < if_and_else_in_file.size();i++) {
		cout << if_and_else_in_file[i] << endl;
	}
	return 0;
} 
