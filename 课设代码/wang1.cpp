#include "Tips.h"
#include"head.h"
#include<string>
#include <iostream>
#include <vector>
using namespace std;


void SEND_FORMULA(string deli, string first, string second, string third, int t);
void IF();
void ELSE();
void IFEND();
void WHILE();
void DO();
void WHILEEND();
void GEQ(string oper);
void GEQSingle(string oper);
void ASSI(string newString, int t);
void OUTPUT();


//vector<STY> siyuanshi(); //返回四元式
vector<STY>FourStyle;//vector为存放四元式的容器
vector<SymbolNode>Symbol;


deque<string> SEM;
int t_value;//中间变量值 t的1，2，3....






void WHILE()//循环语句while四元式
{
	SEND_FORMULA("wh", " ", " ", " ", 0);
}


void DO()//循环语句do四元式
{
	string tM;					//tM：quat(E)后的最终结果符号
	tM = *SEM.begin();			//tM：等于栈顶元素
	SEM.pop_front();			//栈顶元素出栈
	SEND_FORMULA("do", tM, " ", " ", 0);//生成do四元式
}



void WHILEEND()//循环语句while结束四元式
{
	SEND_FORMULA("we", " ", " ", " ", 0);
}


void GEQ(string oper)//双目运算符四元式
{

}


void GEQSingle(string oper)//单目运算符四元式 ！
{

}



void ASSI(string newString, int t)//赋值运算四元式
{
	string tM;
	tM = *SEM.begin();//tM：等于栈顶元素
	SEM.pop_front();//栈顶元素出栈
	SEND_FORMULA("=", tM, " ", newString, t);
}


