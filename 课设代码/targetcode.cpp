#include"Tips.h"
#include"head.h"
#include<vector>
#include<stack>
#include<fstream>
using namespace std;

struct block_begin_end //�����黮���γɵĿ�
{
	int begin; //���һ�����������Ԫʽ��ʼ���
	int end;  //���һ�����������Ԫʽ������
};

struct RDL    //���Ĵ���
{
	string data;  //�Ĵ����е�����
	int state;   //�����ݵĻ�Ծ��Ϣ��y-1;n-0;
};

/********************************************/
//��������.cppӦͨ��
//�����Ϳ��Դﵽ�����.cpp�и�������������ʹ�ø���Ԫʽ
extern vector<STY> FourStyle;
extern vector<SymbolNode> Symbol; //һ���������⣬Symbol�����.cpp����������һ��������siyuanshi.cpp��û������
vector<block_begin_end> block;
/********************************************/

void GetBlock();        // �����黮�֣�����block��
void ActiveInfo(int i); //��Ծ��Ϣ��д������FourStyle��
void InitSymbol();      //һ������ɺ󣬰�Symbol������

void TargetCode()
{
	OUTPUT();
	OUTPUTStoreSymbolNode();
	unsigned int i;
	unsigned int j;
	unsigned int locate;
	unsigned int locate_1;
	vector<string> OBJ;//���Ŀ�����
	stack<string> SEM;
	vector<string>iden; //��ҪԤ�Ƚ��з����ڴ�ı�־��
	string s1; //������ŵ��µ�Ŀ�����
	string s2; //������ŵ��µ�Ŀ�����
	string s3;
	string ss;//������ʾ+-*/��Ӧ��Ŀ�����
	string su;
	RDL R; //ģ�ⵥ�Ĵ���
	fstream Targetcode;
	int a = 0;
	//FourStyle = siyuanshi();
	//���п黮��
	GetBlock();

	//�Ĵ�����ʼ��
	R.data = "\0";
	R.state = 0;

	for (i = 0; i < block.size(); i++) 
	{
		ActiveInfo(i);   //��Ծ��Ϣ��д������FourStyle�У�����������
		for (j = block[i].begin; j <= block[i].end; j++)
		{
			if (FourStyle[j].third != "\0" && FourStyle[j].t == 1)  //��Ԫʽj ��������Ϊ���ַ� �����ǻ�Ծ
			{
				su = FourStyle[j].third;
				iden.push_back(su); //�õ�Ҫ���д洢������Ҫ���ٿռ��һϵ������
							     	//0-��ʱ������1-����ʱ����
			}
		}
	}

	//���л�����Ե�Ԥ��д��
	//��ȡ��д��һ��vector OBJ�У����֮�������ļ���д
	//���ݶ�
	s1 = "DSEG   SEGMENT";
	OBJ.push_back(s1);
	//
	for (i = 0; i < iden.size(); i++)
	{
		s1 = iden[i] + "   " + "DB" + "   " + "?";
		OBJ.push_back(s1);
	}
	//cout << "DSduan mei wen ti" << endl;
	s1 = "DSEG   ENDS";
	OBJ.push_back(s1);
	//��ջ��
	s1 = "SSEG   SEGMENT   STACK";
	OBJ.push_back(s1);
	s1 = "STK   DB   80H DUP(0)";
	OBJ.push_back(s1);
	s1 = "SSEG   ENDS";
	OBJ.push_back(s1);
	//�����
	s1 = "CSEG   SEGMENT";
	OBJ.push_back(s1);
	s1 = "      ASSUME   CS:DSEG,DS:DSEG";
	OBJ.push_back(s1);
	s1 = "START:   MOV AX,DSEG";
	OBJ.push_back(s1);
	s1 = "         MOV DS,AX";
	OBJ.push_back(s1);
	s1 = "         MOV AX,0000H";
	OBJ.push_back(s1);

	for (i = 0; i < block.size(); i++)
	{
		//ȡ����л�Ծ��Ϣ�ı��
		//����Ծ��Ϣ����FourStyle��f,s,t,��
		ActiveInfo(i);
		//********************

		for (j = block[i].begin; j <= block[i].end; j++)
		{
			cout << FourStyle[j].deli << "  ";
			cout << FourStyle[j].first << "(" << FourStyle[j].f << ")" << "   ";
			cout << FourStyle[j].second << "(" << FourStyle[j].s << ")" << "   ";
			cout << FourStyle[j].third << "(" << FourStyle[j].t << ")" << "   ";
			cout << endl;
		}
		//********************
		//����Ŀ������д
		for (j = block[i].begin; j <= block[i].end; j++)
		{

			//�Ӽ��˳�
			if (FourStyle[j].deli == "+" || FourStyle[j].deli == "-"
				|| FourStyle[j].deli == "*" || FourStyle[j].deli == "/")
			{
				if (FourStyle[j].deli == "+") ss = "ADD";
				if (FourStyle[j].deli == "-") ss = "SUB";
				if (FourStyle[j].deli == "*") ss = "MUL";
				if (FourStyle[j].deli == "/") ss = "DIV";

				if (R.data == "\0")
				{
					s1 = "MOV AL," + FourStyle[j].first;
					s2 = ss + " AL," + FourStyle[j].second;
					OBJ.push_back(s1);
					OBJ.push_back(s2);
				}
				else
				{
					if (R.data == FourStyle[j].first)
					{
						//��Ծ
						if (FourStyle[j].f == 1)
						{
							s1 = "MOV " + FourStyle[j].first + ",AL";
							s2 = ss + " AL," + FourStyle[j].second;
							OBJ.push_back(s1);
							OBJ.push_back(s2);
						}
						else  //����Ծ
						{
							s1 = ss + " AL," + FourStyle[j].second;
							OBJ.push_back(s1);
						}
					}
					else if (R.data == FourStyle[j].second && (FourStyle[j].deli == "+" || FourStyle[j].deli == "*"))
					{
						if (FourStyle[j].s == 1) //��Ծ
						{
							s1 = "MOV " + FourStyle[j].second + ",AL";
							OBJ.push_back(s1);
						}
						//���ܻ��Ծ
						s2 = ss + " AL," + FourStyle[j].first;
						OBJ.push_back(s2);
					}
					else
					{
						if (R.state == 1)
						{
							s1 = "MOV " + R.data + ",AL";
							OBJ.push_back(s1);
						}
						s2 = "MOV AL," + FourStyle[j].first;
						s3 = ss + " AL," + FourStyle[j].second;
						OBJ.push_back(s2);
						OBJ.push_back(s3);
					}
				}
			}
			//��ֵ

			//�߼�����
			if (FourStyle[j].deli == ">" || FourStyle[j].deli == "<"
				|| FourStyle[j].deli == ">=" || FourStyle[j].deli == "<="
				|| FourStyle[j].deli == "==" || FourStyle[j].deli == "!="
				|| FourStyle[j].deli == "&&" || FourStyle[j].deli == "||")
			{
				if (FourStyle[j].deli == ">") ss = "GT";
				if (FourStyle[j].deli == "<") ss = "LT";
				if (FourStyle[j].deli == ">=") ss = "GE";
				if (FourStyle[j].deli == "<=") ss = "LE";
				if (FourStyle[j].deli == "==") ss = "EQ";
				if (FourStyle[j].deli == "!=") ss = "NE";
				if (FourStyle[j].deli == "&&") ss = "AND";
				if (FourStyle[j].deli == "||") ss = "OR";

				if (R.data == "\0")
				{
					s1 = "MOV AL," + FourStyle[j].first;
					s2 = "MOV AL,AL " + ss + " " + FourStyle[j].second;
					OBJ.push_back(s1);
				}
				else
				{
					if (R.data == FourStyle[j].first)
					{
						//��Ծ
						if (FourStyle[j].f == 1)
						{
							s1 = "MOV " + FourStyle[j].first + ",AL";
							s2 = "MOV AL,AL " + ss + " " + FourStyle[j].second;
							OBJ.push_back(s1);
							OBJ.push_back(s2);
						}
						else  //����Ծ
						{
							s1 = "MOV AL,AL " + ss + " " + FourStyle[j].second;
							OBJ.push_back(s1);
						}
					}
					else if (R.data == FourStyle[j].second && (FourStyle[j].deli == "!=" || FourStyle[j].deli == "=="
						|| FourStyle[j].deli == "&&" || FourStyle[j].deli == "||"))
					{
						if (FourStyle[j].s == 1) //��Ծ
						{
							s1 = "MOV " + FourStyle[j].second + ",AL";
							OBJ.push_back(s1);
						}
						//���ܻ��Ծ
						s2 = "MOV AL,AL " + ss + " " + FourStyle[j].first;
						OBJ.push_back(s2);
					}
					else
					{
						if (R.state == 1)
						{
							s1 = "MOV " + R.data + ",AL";
							OBJ.push_back(s1);
						}
						s2 = "MOV AL," + FourStyle[j].first;
						s3 = "MOV AL,AL " + ss + " " + FourStyle[j].second;
						OBJ.push_back(s2);
						OBJ.push_back(s3);
					}
				}
			}

			//!����
			if (FourStyle[j].deli == "!")
			{
				if (R.data == "\0")
				{
					s1 = "MOV AL,NOT" + FourStyle[j].first;
					OBJ.push_back(s1);
				}
				else
				{
					if (R.data == FourStyle[j].first)
					{
						//��Ծ
						if (FourStyle[j].f == 1)
						{
							s1 = "MOV " + FourStyle[j].first + ",AL";
							s2 = "MOV AL,NOT AL";
							OBJ.push_back(s1);
							OBJ.push_back(s2);
						}
						else  //����Ծ
						{
							s1 = "MOV AL,NOT AL";
							OBJ.push_back(s1);
						}
					}
					else
					{
						if (R.state == 1)
						{
							s1 = "MOV " + R.data + ",AL";
							OBJ.push_back(s1);
						}
						s2 = "MOV AL,NOT" + FourStyle[j].first;
						OBJ.push_back(s2);
					}
				}
			}

			if (FourStyle[j].deli == "=")
			{
				if (R.data == "\0")
				{
					s1 = "MOV AL," + FourStyle[j].first;
					OBJ.push_back(s1);
				}
				else if (R.data == FourStyle[j].first)
				{
					//��ʱ��Ӧ�ÿ��Ĵ����д�����ݵ�state�����ǿ�FourStyle�еģ�
					//��ΪFourStyle�������µ�
					if (FourStyle[j].f == 1)
					{
						s1 = "MOV " + FourStyle[j].first + ",AL";
						OBJ.push_back(s1);
					}
				}
				//����Ϊ��ʱ����first�����ǿ�����third����ôֻ��ҪLD�Ϳ�����
				else if (R.data != FourStyle[j].first)
				{
					//����third���һ�Ծ��ʱ�����ҪST��������ֻ��ҪLD
					if (R.state == 1 && R.data != FourStyle[j].third)
					{
						s1 = "MOV " + R.data + ",AL";
						OBJ.push_back(s1);
					}
					s2 = "MOV AL," + FourStyle[j].first;
					OBJ.push_back(s2);
				}
			}

			if (FourStyle[j].deli == "if")
			{
				if (R.data == "\0")
				{
					s1 = "MOV AL," + FourStyle[j].first;
					OBJ.push_back(s1);
				}
				else if (R.data == FourStyle[j].first)
				{
					if (FourStyle[j].f == 1)
					{
						s1 = "MOV " + FourStyle[j].first + ",AL";
						OBJ.push_back(s1);
					}
				}
				else
				{
					if (R.state == 1)
					{
						s1 = "MOV " + R.data + ",AL";
						OBJ.push_back(s1);
					}
					s2 = "MOV AL," + FourStyle[j].first;
					OBJ.push_back(s2);
				}
				s1 = "IF AL GT 00H";
				OBJ.push_back(s1);
			}

			if (FourStyle[j].deli == "el")
			{
				if (R.data != "\0" && R.state == 1)
				{
					s1 = "MOV " + R.data + ",AL";
					OBJ.push_back(s1);
				}
				s1 = "ELSE";
				OBJ.push_back(s1);
			}

			if (FourStyle[j].deli == "ie")
			{
				if (R.data != "\0" && R.state == 1)
				{
					s1 = "MOV " + R.data + ",AL";
					OBJ.push_back(s1);
				}
				s1 = "ENDIF";
				OBJ.push_back(s1);
			}

			if (FourStyle[j].deli == "wh")
			{
				//��ֹ���ʱ��Ĵ�����������
				//��Ҫ����ÿ������󶼻�ѼĴ����е����ݸ�Ϊ�ôε�third��������ݣ�
				//������wh����Ĵ������ܻ��ж�������
				if (R.data != "\0" && R.state == 1)
				{
					s1 = "MOV " + R.data + ",R";
					OBJ.push_back(s1);
				}
			}

			if (FourStyle[j].deli == "do")
			{
				if (R.data == "\0")
				{
					s1 = "MOV AL," + FourStyle[j].first;
					OBJ.push_back(s1);
				}
				else if (R.data == FourStyle[j].first)
				{
					if (FourStyle[j].f == 1)
					{
						s1 = "MOV " + FourStyle[j].first + ",AL";
						OBJ.push_back(s1);
					}
				}
				else
				{
					if (R.state == 1)
					{
						s1 = "MOV " + R.data + ",AL";
						OBJ.push_back(s1);
					}
					s1 = "MOV AL," + FourStyle[j].first;
				}
				s1 = "LOOP" + to_string(a) + ": " + "CMP   AL,00H";
				s2 = "JBE   OUT" + to_string(a);//��������������ʱ������ȥ		
				OBJ.push_back(s1);
				OBJ.push_back(s2);
				s3 = "OUT" + to_string(a);  //����ѹջ
				SEM.push(s3);
				s3 = "LOOP" + to_string(a);
				SEM.push(s3);
				a++;
			}

			if (FourStyle[j].deli == "we")
			{
				if (R.data != "\0" && R.state == 1)
				{
					s1 = "MOV " + R.data + ",AL";
					OBJ.push_back(s1);
				}
				s3 = SEM.top();
				s1 = "JMP   " + s3;
				OBJ.push_back(s1);
				SEM.pop();
				s3 = SEM.top();
				s1 = s3 + ":";
				OBJ.push_back(s1);
				SEM.pop();

			}

			if (FourStyle[j].deli == "print")
			{
				if (R.data != "\0" && R.state == 1)
				{
					s1 = "MOV " + R.data + ",AL";
					OBJ.push_back(s1);
				}
				s1 = "LEA DX," + FourStyle[j].third;
				s2 = "MOV AH,09H";
				s3 = "INT 21H";
				OBJ.push_back(s1);
				OBJ.push_back(s2);
				OBJ.push_back(s3);
			}

			//����
			if (FourStyle[j].deli == "func_de")
			{
				if (R.data != "\0" && R.state == 1)
				{
					s1 = "MOV " + R.data + ",AL";
					OBJ.push_back(s1);
				}
				s1 = FourStyle[j].third + "  PROC   NEAR";
				OBJ.push_back(s1);
				SEM.push(FourStyle[j].third);
			}

			if (FourStyle[j].deli == "func_end")
			{
				if (R.data != "\0" && R.state == 1)
				{
					s1 = "MOV " + R.data + ",AL";
					OBJ.push_back(s1);
				}
				s1 = "RET";
				OBJ.push_back(s1);
				s2 = SEM.top();
				s1 = s2 + "   ENDP";
				SEM.pop();
				OBJ.push_back(s1);
			}

			if (FourStyle[j].deli == "func_use")
			{
				if (R.data != "\0" && R.state == 1)
				{
					s1 = "MOV " + R.data + ",AL";
					OBJ.push_back(s1);
				}
				s1 = "CALL   " + FourStyle[j].third;
				OBJ.push_back(s1);
			}

			//ÿһ��������Ĵ����ж�����һ������
			//����ÿ����������Ϊÿ�ζ�һ�����ӽ��б�дĿ������ʱ�򣬸տ�ʼ��ʱ��Ĵ����еĶ�������һ�����ӵ�third
			//����Ҫ���if���޸ģ���Ϊif�е�third��\0��������ActiveInfoʱ����û���޸ģ���t����0
			R.data = FourStyle[j].third;
			R.state = FourStyle[j].t;
		}
		//��һ������ɺ�Ҫ��Symbol���������ù顰�㡱
		InitSymbol();
	}

	//��β����

	s1 = "MOV   AH,4CH";
	s2 = "INT   21H";
	OBJ.push_back(s1);
	OBJ.push_back(s2);
	s1 = "CSEG   ENDS";
	s2 = "      END   START";
	OBJ.push_back(s1);
	OBJ.push_back(s2);

	Targetcode.open("TargetCode.ASM", ios::out);
	//�����Ϣ��
	for (i = 0; i < OBJ.size(); i++)
	{
		cout << i << "  " << OBJ[i] << endl;
		Targetcode << i << "  " << OBJ[i] << endl;
	}

}

void GetBlock()   // �����黮�֣�����block��
{
	unsigned int i;  //��Ϊvector�� .size()�ķ���ֵ���޷�����
	int n;
	block_begin_end a;
	a.begin = 0;
	for (i = 0; i < FourStyle.size(); i++)
	{   //���������Щ��ֱ��end��                         push_back�������� vectorβ������һ�����ݣ�
		if (FourStyle[i].deli == "if") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "el") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "ie") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "wh") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "do") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "we") { a.end = i; block.push_back(a); a.begin = i + 1; }
	}
	n = FourStyle.size();
	//Ϊ�˷�ֹ������Ԫʽ��һϵ�еĸ�ֵ���
	//���ֻ�������Ŀ������ǣ��ᵼ�¶����ܶ����
	if (FourStyle[n - 1].deli != "if"    &&FourStyle[n - 1].deli != "el"  && FourStyle[n - 1].deli != "ie"
	 && FourStyle[n - 1].deli != "wh"    &&FourStyle[n - 1].deli != "do"  && FourStyle[n - 1].deli != "we")
	{
		a.end = n - 1;
		block.push_back(a);
	}
}

void ActiveInfo(int i)   //��Ծ��Ϣ��д������FourStyle�У�����������
{
	unsigned int m;
	int first;
	int second;
	int third;
	int j;   //�������ڣ�����

	//����飬��Ծ��Ϣ������������
	for (j = block[i].end; j >= block[i].begin; j--)//ֻ�Ǳ�־����Ԫʽ�����
	{
		first = -1;
		second = -1;
		third = -1;
		//��Symbol���ҵ���Ӧ������
		for (m = 0; m < Symbol.size(); m++)  //Symbol���ݳ������⣬�ظ���һ��
		{
			if (FourStyle[j].first  == Symbol[m].data) first = m;
			if (FourStyle[j].second == Symbol[m].data) second = m;
			if (FourStyle[j].third  == Symbol[m].data) third = m;
			//Ҫע�⵽����Ԫʽ�ĺ�����Ԫ�ز���һ�����Ƿ��ţ������ǳ������ַ��������߿գ�����һ�����Ƿ��ŵģ�
			//���ԣ���ѭ��������ʱ��first,second,third�����е���-1��
		}
		
		//�Ը���Ԫʽ��ǻ�Ծ��Ϣ
		if (first != -1)
		{
			FourStyle[j].f = Symbol[first].state;
			Symbol[first].state = 1;//��Ծ��1
		}
		if (second != -1)
		{
			FourStyle[j].s = Symbol[second].state;
			Symbol[second].state = 1;
		}
		if (third != -1)
		{
			FourStyle[j].t = Symbol[third].state;
			Symbol[third].state = 0;//����Ծ��0
		}
	}
}

void InitSymbol()  //һ������ɺ󣬰�Symbol������
{
	unsigned int i;
	for (i = 0; i < Symbol.size() / 2 ; i++)          //����ʱʱ1����ʱ��0��
	{
		if (Symbol[i].type == 1) Symbol[i].state = 1; //����ʱ����������ʱ���Ϊy ��
		else Symbol[i].state = 0;                     //��ʱ������ֵΪn
	}
}
