/*
��Ϊ����ֻ��Ҫʶ�������ʲô�Ϳ��ԣ�������������Թ�������Ĳ��ֻ���ע��
*/
#include"head.h"
#include"Tips.h"
#include<iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include<string>
using namespace std;

typedef struct//��̬���飬Token��Ϣ�����ʷ������Լ���Ӧ��ֵ
{
	string type;
	int locate;
}Node;
//�ؼ��ֺͱ�ʶ�����ܹ����ã����ǿ���ö��
//�ؼ���
const string KT[] = { "int","main","float","if","else","while","string" };
//���
const string PT[] = { "(" , ")" , "{" , "}" ,";"  , "." ,"#","+","- ","*","/","=","<",">","<=",">=","==","!=","!","||","&&" };
//��ʶ���������������ַ���
vector<string> IT, CT, ST;
vector<Node> datain;

void FA(char c, int& state, int& flag);//����״̬װ��
int FindTable(string s, int& flag);//���
void FA_Delete(char c, int &state, int &flag);//ȥ���ո񼰻��з���
void FA_Key(char c, int &state, int &flag);//�ؼ��ֵĴ���
void FA_CTone(char c, int &state, int &flag);//���ִ���
void FA_CTtwo(char c, int &state, int &flag);//float ��Ϊint,ͳһ��������

void FA_CHT(char c, int &state, int &flag);//ת��ST,���ַ���Ϊ�ַ�����ȡ��char���ͣ��ַ�����
void FA_ST(char c, int &state, int &flag);//�ַ�����
void FA_PT(char c, int &state, int &flag);//�������
int InsertVector(string s, int flag); //flag��ȷ��Ҫ������д,���뺯���������м�����Ԫ�أ�������ڣ��ͷ��ظ���������λ�ã��������ڣ��ͼ��룬������λ��

int  GetToken(void)//����Token����
{
	int flag = 0;//���ڽ����ж�ʶ�𣬵�flag��=0ʱ��˵���ҵ�����Щ�����ַ���һ����𣻿�������while������һ���ж���
	int locate;
	int state = 1;
	string s;
	char c;
	Node node;
	int count; // ��¼��node���ж���Ԫ��
	ifstream infile;
	//д���ļ���
	fstream out_files;
	out_files.open("token.txt", ios::out);

	infile.open("file.txt");
	//������infile.peek()��������Ԥ����һ������ֹ���ո��Ǳ�Ҳѭ����
	//�����Զ������ҵ���Ӧ���
	cout << "���ɵ�Token�������£�" << endl;

	while (!infile.eof() && infile.peek() != EOF)//�ж������Ƿ�Ϊ������
	{
		infile.get(c);//ʹ��get()���Զ������ַ��������ո�
		FA(c, state, flag);
		if (flag == 0)
		{
			if (int(c) == 39 || int(c) == 34 || int(c) == 32 || c == '\n');  //��ֹ��'��" �� ��/n���żӽ�ȥ��
			else s += c;//ͳһchar���ͺ�string��ȡ��char����
		}
		else if (3 < flag && flag < 6)
		{
			locate = FindTable(s, flag);//������
			node.type = "string";//����ȷ��
			node.locate = locate;//���ʷ�����ȷ��
			datain.push_back(node);//���ýڵ����뵽datain��
			cout << s  << "   < " << node.locate << "  " << node.type << " > " << endl;//�����token����
			out_files << s  << "   < " << node.locate << "  " << node.type << " > " << endl;
			s = "\0";
			state = 1;
			locate = flag = 0;
		}
		else
		{
			locate = FindTable(s, flag);//Ϊ��ͬ������Ʋ�ͬ�ĵ�flagֵ
			if (flag == 1)
			{
				node.type = "key";//�ؼ���
			}
			else if (flag == 2)
			{
				node.type = "float";
			}
			else if (flag == 6)
			{
				node.type = "deli";//���
			}
			else if (flag == 10)
			{
				node.type = "iden";//��ʶ��
			}
			node.locate = locate;
			datain.push_back(node);
			cout << s << "   < " << node.locate << "  " << node.type << " > " << endl;
			out_files << s << "   < " << node.locate << "  " << node.type << " > " << endl;
			state = 1;
			locate = flag = 0;
			s = "\0";
			FA(c, state, flag);  //ÿ�����¿�ʼ�ж�ʱ���������ڵ�һ���͸ı�flag�ġ����Կ�����ôд
			if (int(c) == 39 || int(c) == 34 || int(c) == 32 || c == '\n'); //��ֹ��',", ,\n ���żӽ�ȥ��
			else s += c;
		}
	}
	count = datain.size();//��¼�ڵ�ĸ���
	return count;//��󷵻����ɵ�token���а���������
}

void FA(char c, int& state, int& flag)//״̬ת��
{
	switch (state)
	{
	case 1:FA_Delete(c, state, flag); break;
	case 2:FA_Key(c, state, flag); break;
	case 3:FA_CTone(c, state, flag); break;   //������int float���Ǳ���������������ֻ��������flag���޸�
	case 4:FA_CTtwo(c, state, flag); break;
	case 5:FA_CHT(c, state, flag); break;
	case 6:FA_ST(c, state, flag); break;
	case 7:FA_PT(c, state, flag); break;
	}
}

void FA_Delete(char c, int& state, int& flag)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))  state = 2;
	else if ('0' <= c && c <= '9') state = 3;
	else if (int(c) == 39) state = 5;
	else if (int(c) == 34) state = 6;
	else if (int(c) == 32 || int(c) == '\n'); //�ѿո�ͻس�����
	else state = 7;
}


void FA_Key(char c, int& state, int& flag)//�ؼ���
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
	else flag = 1;
}


void FA_CTone(char c, int& state, int& flag)//����
{
	if (47 < int(c) && int(c) < 58);
	else if (c == '.') { state = 4; }
	else flag = 2;
}


void FA_CTtwo(char c, int& state, int& flag)//����
{
	if (47 < int(c) && int(c) < 58);
	else flag = 2;  //float ��Ϊ Int,������float int ��floatȫ������
}


void FA_CHT(char c, int& state, int& flag)//�ַ�����
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'));
	else if (int(c) == 39) flag = 5;   //������st,ȡ��char����
}


void FA_ST(char c, int& state, int& flag)//�ַ���
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'));
	else if (int(c) == 34) flag = 5;
}


void FA_PT(char c, int& state, int& flag)//���
{
	//if�еĶ��ǿ���������_�ַ�_��Ϊ�����
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == '=' || c == '!');  //��ȫ��ֻ������������txt���õ���
	else flag = 6; //һ�¾ͳ�ȥ�Ķ���һ���ַ���Ϊ�����  ���ڶ����c,���ϼ��������д���
}




int FindTable(string s, int& flag)//���
{
	int i = 0, flag_1 = 0;
	if (flag == 1)
	{
		for (i = 0; i < (sizeof(KT) / sizeof(KT[0])); i++)
		{
			if (s == KT[i]) { flag_1 = 1; break; }
		}
		if (flag_1); //flag_1=1˵���ҵ���
		else
		{
			i = InsertVector(s, flag); //IT
			flag = 10;
		}
	}
	else if (flag == 2) i = InsertVector(s, flag);//CT
	else if (flag == 5) i = InsertVector(s, flag);//ST
	else if (flag == 6)
	{
		for (i = 0; i < (sizeof(PT) / sizeof(PT[0])); i++)
		{
			if (s == PT[i]) break;
		}
	}
	return i;
}




int InsertVector(string s, int flag) //������ڣ��ͷ��ظ���������λ�ã��������ڣ��ͼ��룬������λ��
{
	int i = 0;
	int flag_1 = 0;
	vector<string>* p;
	vector<string> ::iterator ite;
	switch (flag)
	{
	case 1: p = &IT; break; //����ͨ��ָ��ָ����������ܶԸ�������иı�
	case 2: p = &CT; break;
	case 5:p = &ST; break;
	default:cout << "error" << endl; return 0;
	}
	if ((*p).empty())
	{
		(*p).push_back(s);
		flag_1 = 1;
	}
	else
	{
		for (ite = (*p).begin(); ite != (*p).end(); ite++)
		{
			if (*ite == s) { flag_1 = 1; break; }
			i++;//i++��˳���ܷ����ϱߣ���Ȼ�᲻ͳһ
		}
	}
	if (flag_1 == 0) (*p).push_back(s);
	return i;
}


string BackType(int i)//���ظ����ݵ�type  ��datain�е�
{
	return datain[i].type;
}

int BackLocate(int i) //���ظ����ݵ�locate�����ʷ�����
{
	return datain[i].locate;
}

string BackData(int flag, int locate)//flag��type���� ������flag��Ӧ�ı��locateλ��
{
	int i;
	switch (flag)
	{
	case 1: return KT[locate]; break;
	case 2: return PT[locate]; break;
	case 3: return ST[locate]; break;
	case 4: return CT[locate]; break;
	case 5: return IT[locate]; break;
	default: {cout << "error" << endl; return "\0"; break; }
	}
}
