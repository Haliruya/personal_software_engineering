#include<bits/stdc++.h>
using namespace std; 

int cnt=0;
map <string,int> key;  //�ؼ���ö�ٱ�� 
vector <string> if_and_else_in_file;  //���ڴ洢�ļ��г��ֵ�����if��else��else-if�Լ������� 
int else_if_cnt = 0;

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
	char c;  //string����ֱ��+char 
	string a_word = "";
	bool last_is_alpha = false;  //��һ���ַ��Ƿ�����ĸ 
	bool last_is_else = false;  //��һ�������Ƿ���else

	while ((c = fgetc(fp)) != EOF) {
		if (isalpha(c)) {
			a_word += c;
			last_is_alpha = true;
		}
		else {
			if (last_is_alpha) {  //һ�����ʽ��� 
				if (key[a_word]) {  //�õ����ǹؼ��� 
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
	
	//������е�if��else��else-if�ͻ����� 
	cout << "num of else-if is:" << else_if_cnt << endl;
	for (int i = 0;i < if_and_else_in_file.size();i++) {
		cout << if_and_else_in_file[i] << endl;
	}
	return 0;
} 
