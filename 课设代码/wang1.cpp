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


//vector<STY> siyuanshi(); //������Ԫʽ
vector<STY>FourStyle;//vectorΪ�����Ԫʽ������
vector<SymbolNode>Symbol;


deque<string> SEM;
int t_value;//�м����ֵ t��1��2��3....






void WHILE()//ѭ�����while��Ԫʽ
{
	SEND_FORMULA("wh", " ", " ", " ", 0);
}


void DO()//ѭ�����do��Ԫʽ
{
	string tM;					//tM��quat(E)������ս������
	tM = *SEM.begin();			//tM������ջ��Ԫ��
	SEM.pop_front();			//ջ��Ԫ�س�ջ
	SEND_FORMULA("do", tM, " ", " ", 0);//����do��Ԫʽ
}



void WHILEEND()//ѭ�����while������Ԫʽ
{
	SEND_FORMULA("we", " ", " ", " ", 0);
}


void GEQ(string oper)//˫Ŀ�������Ԫʽ
{

}


void GEQSingle(string oper)//��Ŀ�������Ԫʽ ��
{

}



void ASSI(string newString, int t)//��ֵ������Ԫʽ
{
	string tM;
	tM = *SEM.begin();//tM������ջ��Ԫ��
	SEM.pop_front();//ջ��Ԫ�س�ջ
	SEND_FORMULA("=", tM, " ", newString, t);
}


