#pragma warning(disable : 4996)
#include<sys/types.h>
#include<sys/stat.h>
#include<iostream>
#include<vector>
#include<map>
#include<stdio.h>
using namespace std;

map <string,int> key;  //�ؼ���ö�ٱ�� 

int total_cnt=0;  //�ؼ��ֳ���������¼
int switch_cnt = 0;  //switchͳ������
vector <int> case_cnt;  //ÿ��case��������
int if_else_cnt = 0;
int if_elseif_else_cnt = 0;

vector <string> keyword_in_file;  //���ڴ洢�ļ��г��ֵ����йؼ��� 

char file_path[100];
int output_level;  //��ɵȼ�
FILE * fp;

void InitKey();  //��ʼ���ؼ��� 

void Input();

void OpenAndReadFileToWord();  //���ļ����ļ����ݰ���ĸ���������ǹؼ��ֵ���ĸ�ϲ��ɹؼ���

void StatisticsLevel1();  //ͳ�ƣ���ɵȼ�1Ҫ��
void OutputLevel1();  //�������ɵȼ�1Ҫ��

void StatisticsLevel2(); 
void OutputLevel2();

void StatisticsLevel3();
void OutputLevel3();

void StatisticsLevel4();
void OutputLevel4();

void KeywordStatistics();  //�ؼ���ͳ�ƺ���������main����ʹ��

/////////////////////////////////////realize///////////////////////////////////////////

void InitKey()  //��ʼ���ؼ��ֱ�� 
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
	cout << "�����롰�ļ�·������";
	cin >> file_path;
	cout << "�����롰����ȼ�����";
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
		//��ȡ�ļ����ݣ����ַ������ϲ��ɵ��� 
		char c;  //string����ֱ��+char 
		string a_word = "";
		bool last_is_alpha = false;  //��һ���ַ��Ƿ�����ĸ 
		while ((c = fgetc(fp)) != EOF) {
			if (isalpha(c)) {
				a_word += c;
				last_is_alpha = true;
			}
			else {
				if (last_is_alpha) {  //һ�����ʽ��� 
					if (key[a_word]) {  //�õ����ǹؼ��� 
						keyword_in_file.push_back(a_word);
					}
					a_word = "";
				}
				last_is_alpha = false;
			}
		}
		if (key[a_word]) {  //�õ����ǹؼ��� 
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

void OutputLevel1()  //����ȼ�1������ؼ���ͳ����Ϣ
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
			if (have_switch) {  //���ֹ�switch����case����������
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

void OutputLevel2()  //����ȼ�2������м���switch case�ṹ��ͬʱ���ÿ���Ӧ��case����
{
	OutputLevel1();
	cout << "switch num: " << switch_cnt << endl;
	cout << "case num:";
	for (int i = 0;i < case_cnt.size();i++) {
		cout << " " << case_cnt[i];
	}
	cout << endl;
}

void StatisticsLevel3()
{
	StatisticsLevel1();
	StatisticsLevel2();
}

void OutputLevel3()  //����ȼ�3������м���if else�ṹ
{
	OutputLevel1();
	OutputLevel2();
	cout << "if-else num: " << if_else_cnt << endl;
}

void StatisticsLevel4()
{
	StatisticsLevel1();
	StatisticsLevel2();
	StatisticsLevel3();
}

void OutputLevel4()  //����ȼ�4������м���if��else if��else�ṹ
{
	OutputLevel1();
	OutputLevel2();
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
		StatisticsLevel3();
		OutputLevel3();
	}
	else {
		StatisticsLevel4();
		OutputLevel4();
	}
}
