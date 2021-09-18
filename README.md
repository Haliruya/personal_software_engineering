# personal_software_engineering
personal programming 1  

**写在前头：**  
yee~这里是软件工程第一次个人编程作业。  
最后的成果文件是 keyword_statistics.h 和 main.cpp，其它都是各部分功能测试代码。  
文件中代码百分百 C++ 且纯手工编写，因此有的算法可能略显呆滞。  

**题目要求：**  
    写一个程序，使它可以对读入的 C 或 C++ 代码文件进行不同等级的关键字提取。  
   * 基础要求：输出关键字的总数  
   * 进阶要求：输出有几组 switch case 结构，同时输出每组对应的 case 个数  
   * 拔高要求：输出有几组 if else 结构  
   * 终极要求：输出有几组 if，else if，else 结构  
   在完成更高要求的情况前要完成前置要求。  
    
**整体思路：**  
       先标记出所有关键字，然后按字符读取文件内容，把其中的字母组合成单词（指的是广义上的单词，由连在一起的字母组成）并判断是否是关键字，是则存入数组。前两个要求可以通过遍历该关键字数组来完成，后两个要求考虑到 if 和 else 会出现套娃现象，要通过大括号来判断层次，并且 else if 结构也要提取出来作为一个存储单元，因此创建了另一个存放 if、else、else if 和大括号的数组，并借助栈来对付套娃现象，完成后两个要求。
    
**代码拆分：**  
   * void InitKey()：用 map <string,int> 初始化关键字标记  
   * void Input()：输入文件路径和完成等级  
   * void OpenAndReadFileToWord()：打开并按字符读取文件内容然后转化为单词，利用标记提取出关键字存入“关键字数组” 、提取出 if、else、else if 和大括号存入“if else数组”  
   * void StatisticsLevel1()：遍历“关键字数组”，统计关键字总数  
   * void OutputLevel1()：输出关键字总数  
   * void StatisticsLevel2()：遍历“关键字数组”，统计 switch 和 case 数量  
   * void OutputLevel2()：输出 switch 和 case 数量  
   * void StatisticsLevel3And4()：遍历“if else数组”，借助栈来统计 if-else 和if-elseif-else 的数量  
   * void OutputLevel3()：输出 if-else 数量  
   * void OutputLevel4()：输出 if-elseif-else 数量  
   * void KeywordStatistics()：最后合成的函数，在main函数中直接调用该函数即可实现题目要求的功能  

其他详情见csdn作业帖
