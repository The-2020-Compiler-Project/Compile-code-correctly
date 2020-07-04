#include "Tips.h"
#include"head.h"
#include<string>
#include <iostream>
#include <vector>
#include<deque>
#include <sstream>
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


void SEND_FORMULA(string deli, string first, string second, string third, int t)//将四元式送入结构体数组
{
    STY  temSty;
	temSty.deli = deli;			//四元式中的算符
	temSty.first = first;		//第一个运算数据
	temSty.second = second;		//第二个运算数据
	temSty.third = third;		//运算结果符号
	temSty.f = 0;				//第一个运算数据的活跃信息
	temSty.s = 0;				//第二个运算数据的活跃信息
	temSty.t = t;				//运算结果符号的活跃信息

	FourStyle.push_back(temSty);//push_back在vector类中作为在vector尾部加入一个数据（vector为存放四元式的容器）
}


void IF()//条件语句if四元式
{
	string tM;					//tM：quat(E)后的最终结果符号
	tM = *SEM.begin();			//tM：等于栈顶元素
	SEM.pop_front();			//栈顶元素出栈
	SEND_FORMULA("if", tM, " ", " ", 0);//生成if四元式
}


void ELSE() //条件语句else四元式
{
	SEND_FORMULA("el", " ", " ", " ", 0);
}



void IFEND()//条件语句if结束四元式
{
	SEND_FORMULA("ie", " ", " ", " ", 0);
}


void GEQ(string oper)//双目运算符四元式
{
	
}


void GEQSingle(string oper)//单目运算符四元式 ！
{

}


/*vector<STY> siyuanshi()//返回四元式
{
	return FourStyle;
}*/

