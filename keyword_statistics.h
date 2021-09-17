#pragma warning(disable : 4996)
#include<sys/types.h>
#include<sys/stat.h>
#include<iostream>
#include<vector>
#include<map>
#include<stdio.h>
#include<stack>
using namespace std;

map <string,int> key;  //关键字枚举标记 

int total_cnt=0;  //关键字出现数量记录
int switch_cnt = 0;  //switch统计数量
vector <int> case_cnt;  //每组case出现数量
int if_else_cnt = 0;
int if_elseif_else_cnt = 0;
int else_if_cnt = 0;
int else_cnt = 0;

vector <string> keyword_in_file;  //用于存储文件中出现的所有关键字 
vector <string> if_and_else_in_file;  //用于存储文件中出现的所有if，else，else-if以及大括号

char file_path[100];
int output_level;  //完成等级
FILE * fp;

void InitKey();  //初始化关键字 

void Input();

void OpenAndReadFileToWord();  //打开文件，文件内容按字母读出并把是关键字的字母合并成关键字

void StatisticsLevel1();  //统计：完成等级1要求
void OutputLevel1();  //输出：完成等级1要求

void StatisticsLevel2(); 
void OutputLevel2();

void StatisticsLevel3And4();

void OutputLevel3();

void OutputLevel4();

void KeywordStatistics();  //关键字统计函数，方便main函数使用

/////////////////////////////////////realize///////////////////////////////////////////

void InitKey()  //初始化关键字标记 
{
	key["auto"] = key["double"] = key["int"] = key["struct"]
		= key["break"] = key["else"] = key["long"] = key["switch"]
		= key["case"] = key["enum"] = key["register"] = key["typedef"]
		= key["char"] = key["extern"] = key["return"] = key["union"]
		= key["const"] = key["float"] = key["short"] = key["unsigned"]
		= key["continue"] = key["for"] = key["signed"] = key["void"]
		= key["default"] = key["goto"] = key["sizeof"] = key["volatile"]
		= key["do"] = key["if"] = key["static"] = key["while"] = 1;
}

void Input()
{
	cout << "请输入“文件路径”：";
	cin >> file_path;
	cout << "请输入“输出等级”：";
	cin >> output_level;
}

void OpenAndReadFileToWord()
{
	fp = fopen( file_path, "r");
	if (fp == NULL)
	{
		printf("falt to open the file : %s.\n", file_path);
		return;
	}
	else {
		cout << "成功打开文件" << endl;
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
						keyword_in_file.push_back(a_word);
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
				last_is_alpha = false;
				if (c == '{' || c == '}') {
					string temp = "";
					temp += c;
					if_and_else_in_file.push_back(temp);
				}
			}
		}
		if (key[a_word]) {  //该单词是关键字 
			keyword_in_file.push_back(a_word);
		}
		fclose(fp);
	}
}

void StatisticsLevel1()
{
	for (int i = 0;i < keyword_in_file.size();i++) {
		total_cnt++;
	}
}

void OutputLevel1()  //输出等级1：输出关键字统计信息
{
	cout << "total num: " << total_cnt << endl;
}

void StatisticsLevel2()
{
	StatisticsLevel1();
	bool have_switch = false;
	int case_num = 0;
	for (int i = 0;i < keyword_in_file.size();i++) {
		if (keyword_in_file[i] == "switch") {
			if (have_switch) {  //出现过switch，把case数量存起来
				case_cnt.push_back(case_num);
				case_num = 0;
			}
			else {
				have_switch = true;
			}
			switch_cnt++;
		}
		if (keyword_in_file[i] == "case") {
			case_num++;
		}
	}
	case_cnt.push_back(case_num);
}

void OutputLevel2()  //输出等级2：输出有几组switch case结构，同时输出每组对应的case个数
{
	OutputLevel1();
	cout << "switch num: " << switch_cnt << endl;
	cout << "case num:";
	for (int i = 0;i < case_cnt.size();i++) {
		cout << " " << case_cnt[i];
	}
	cout << endl;
}

void StatisticsLevel3And4()
{
	StatisticsLevel2();
	stack <string> s;
	stack <int> have_elseif;  //如果出现else if则置为true,每个大括号对应一个栈位

	for (int i = 0;i < if_and_else_in_file.size();i++) {
		if (if_and_else_in_file[i] == "{") {
			s.push("{");
			have_elseif.push(0);
		}
		else if (if_and_else_in_file[i] == "}") {
			while (s.top() != "{") {
				s.pop();
			}
			s.pop();
			have_elseif.pop();
		}
		else if (if_and_else_in_file[i] == "if") {
			s.push("if");
			have_elseif.pop();
			have_elseif.push(0);
		}
		else if (if_and_else_in_file[i] == "else_if") {
			have_elseif.pop();
			have_elseif.push(1);
		}
		else if (if_and_else_in_file[i] == "else") {
			if (have_elseif.top()) {
				if_elseif_else_cnt++;
			}
			else {
				if_else_cnt++;
			}
			have_elseif.pop();
			have_elseif.push(0);
			while (s.top() != "if") {
				s.pop();
			}
			s.pop();
		}
	}
}

void OutputLevel3()  //输出等级3：输出有几组if else结构
{
	OutputLevel2();
	cout << "if-else num: " << if_else_cnt << endl;
}


void OutputLevel4()  //输出等级4：输出有几组if，else if，else结构
{
	OutputLevel3();
	cout << "if-elseif-else num: " << if_elseif_else_cnt << endl;
}

void KeywordStatistics()
{
	InitKey();
	Input();
	OpenAndReadFileToWord();
	if (output_level == 1) {
		StatisticsLevel1();
		OutputLevel1();
	}
	else if (output_level == 2) {
		StatisticsLevel2();
		OutputLevel2();
	}
	else if (output_level == 3) {
		StatisticsLevel3And4();
		OutputLevel3();
	}
	else {
		StatisticsLevel3And4();
		OutputLevel4();
	}
}
