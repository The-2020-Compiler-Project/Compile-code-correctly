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


//vector<STY> siyuanshi(); //������Ԫʽ
vector<STY>FourStyle;//vectorΪ�����Ԫʽ������
vector<SymbolNode>Symbol;


deque<string> SEM;
int t_value;//�м����ֵ t��1��2��3....


void SEND_FORMULA(string deli, string first, string second, string third, int t)//����Ԫʽ����ṹ������
{
    STY  temSty;
	temSty.deli = deli;			//��Ԫʽ�е����
	temSty.first = first;		//��һ����������
	temSty.second = second;		//�ڶ�����������
	temSty.third = third;		//����������
	temSty.f = 0;				//��һ���������ݵĻ�Ծ��Ϣ
	temSty.s = 0;				//�ڶ����������ݵĻ�Ծ��Ϣ
	temSty.t = t;				//���������ŵĻ�Ծ��Ϣ

	FourStyle.push_back(temSty);//push_back��vector������Ϊ��vectorβ������һ�����ݣ�vectorΪ�����Ԫʽ��������
}


void IF()//�������if��Ԫʽ
{
	string tM;					//tM��quat(E)������ս������
	tM = *SEM.begin();			//tM������ջ��Ԫ��
	SEM.pop_front();			//ջ��Ԫ�س�ջ
	SEND_FORMULA("if", tM, " ", " ", 0);//����if��Ԫʽ
}


void ELSE() //�������else��Ԫʽ
{
	SEND_FORMULA("el", " ", " ", " ", 0);
}



void IFEND()//�������if������Ԫʽ
{
	SEND_FORMULA("ie", " ", " ", " ", 0);
}


void GEQ(string oper)//˫Ŀ�������Ԫʽ
{
	
}


void GEQSingle(string oper)//��Ŀ�������Ԫʽ ��
{

}


/*vector<STY> siyuanshi()//������Ԫʽ
{
	return FourStyle;
}*/

