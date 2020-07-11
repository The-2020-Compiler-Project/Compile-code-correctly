#include"head.h"
#include"Tips.h"
#include<iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include<string>
using namespace std;

typedef struct//动态数组，Token信息，单词分类码以及对应的值
{
	string type;
	int locate;
}Node;
//关键字和标识符不能够重用，但是可以枚举
//关键字
const string KT[] = { "int","main","float","if","else","while","string" };
//界符
const string PT[] = { "(" , ")" , "{" , "}" ,";"  , "." ,"#","+","- ","*","/","=","<",">","<=",">=","==","!=","!","||","&&" };
//标识符，算数常数，字符串
vector<string> IT, CT, ST;
vector<Node> datain;

void FA(char c, int& state, int& flag);//进行状态装换
int FindTable(string s, int& flag);//查表
void FA_Delete(char c, int& state, int& flag);//去除空格及换行符号
void FA_Key(char c, int& state, int& flag);//关键字的处理
void FA_CTone(char c, int& state, int& flag);//数字处理
void FA_CTtwo(char c, int& state, int& flag);//float 改为int,统一数据类型

void FA_CHT(char c, int& state, int& flag);//转到ST,将字符改为字符串，取消char类型，字符处理
void FA_ST(char c, int& state, int& flag);//字符处理
void FA_PT(char c, int& state, int& flag);//界符处理
int InsertVector(string s, int flag); //flag来确定要向哪里写,插入函数，向类中加入新元素，如果存在，就返回该数据所在位置，若不存在，就加入，并返回位置

int  GetToken(void)//生成Token序列
{
	int flag = 0;//用于进入判断识别，当flag！=0时，说明找到了这些连续字符的一个类别；可以跳出while进入下一个判断中
	int locate;
	int state = 1;
	string s;
	char c;
	Node node;
	int count; // 记录在node中有多少元素
	ifstream infile;
	//写入文件中
	fstream out_files;
	out_files.open("token.txt", ios::out);

	infile.open("file.txt");
	//后边这个infile.peek()的作用是预读下一个，防止最后空格那边也循环。
	//进入自动机，找到相应类别
	cout << "生成的Token序列如下：" << endl;

	while (!infile.eof() && infile.peek() != EOF)
	{
		infile.get(c);//使用get()可以读所有字符（包括空格）
		FA(c, state, flag);
		if (flag == 0)
		{
			if (int(c) == 39 || int(c) == 34 || int(c) == 32 || c == '\n');  //防止把'，" ， ，/n符号加进去；
			else s += c;//统一char类型和string，取消char类型
		}
		else if (3 < flag && flag < 6)
		{
			locate = FindTable(s, flag);//查表操作
			node.type = "string";//类型确定
			node.locate = locate;//单词分类码确定
			datain.push_back(node);//将该节点送入到datain中
			cout << s << "   < " << node.locate << "  " << node.type << " > " << endl;//输出该token序列
			out_files << s << "   < " << node.locate << "  " << node.type << " > " << endl;
			s = "\0";
			state = 1;
			locate = flag = 0;
		}
		else
		{
			locate = FindTable(s, flag);
			if (flag == 1)
			{
				node.type = "key";//关键字
			}
			else if (flag == 2)
			{
				node.type = "float";
			}
			else if (flag == 6)
			{
				node.type = "deli";//界符
			}
			else if (flag == 10)
			{
				node.type = "iden";//标识符
			}
			node.locate = locate;
			datain.push_back(node);
			cout << s << "   < " << node.locate << "  " << node.type << " > " << endl;
			out_files << s << "   < " << node.locate << "  " << node.type << " > " << endl;
			state = 1;
			locate = flag = 0;
			s = "\0";
			FA(c, state, flag);  //每当从新开始判断时，都不会在第一个就改变flag的。所以可以这么写
			if (int(c) == 39 || int(c) == 34 || int(c) == 32 || c == '\n'); //防止把',", ,\n 符号加进去；
			else s += c;
		}
	}
	count = datain.size();//记录节点的个数
	return count;//最后返回生成的token序列包含的组数
}

void FA(char c, int& state, int& flag)//状态转换
{
	switch (state)
	{
	case 1:FA_Delete(c, state, flag); break;
	case 2:FA_Key(c, state, flag); break;
	case 3:FA_CTone(c, state, flag); break;   //不区分int float但是保留这两个函数，只是在最后的flag中修改
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
	else if (int(c) == 32 || int(c) == '\n'); //把空格和回车整走
	else state = 7;
}


void FA_Key(char c, int& state, int& flag)//关键字
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
	else flag = 1;
}


void FA_CTone(char c, int& state, int& flag)//常数
{
	if (47 < int(c) && int(c) < 58);
	else if (c == '.') { state = 4; }
	else flag = 2;
}


void FA_CTtwo(char c, int& state, int& flag)//常数
{
	if (47 < int(c) && int(c) < 58);
	else flag = 2;  //float 改为 Int,不区分float int ，float全部上跳
}


void FA_CHT(char c, int& state, int& flag)//字符处理
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'));
	else if (int(c) == 39) flag = 5;   //下跳到st,取消char类型
}


void FA_ST(char c, int& state, int& flag)//字符串
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9'));
	else if (int(c) == 34) flag = 5;
}


void FA_PT(char c, int& state, int& flag)//界符
{
	//if中的都是可能是两个_字符_做为界符的
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == '=' || c == '!');  //不全，只是在我所给的txt中用到的
	else flag = 6; //一下就出去的都是一个字符作为界符的  对于多读的c,在上级函数中有处理
}




int FindTable(string s, int& flag)//查表
{
	int i = 0, flag_1 = 0;
	if (flag == 1)
	{
		for (i = 0; i < (sizeof(KT) / sizeof(KT[0])); i++)
		{
			if (s == KT[i]) { flag_1 = 1; break; }
		}
		if (flag_1); //flag_1=1说明找到了
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




int InsertVector(string s, int flag) //如果存在，就返回该数据所在位置，若不存在，就加入，并返回位置
{
	int i = 0;
	int flag_1 = 0;
	vector<string>* p;
	vector<string> ::iterator ite;
	switch (flag)
	{
	case 1: p = &IT; break; //必须通过指针指向该链表，才能对该链表进行改变
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
			i++;//i++的顺序不能放在上边，不然会不统一
		}
	}
	if (flag_1 == 0) (*p).push_back(s);
	return i;
}


string BackType(int i)//返回该数据的type  在datain中的
{
	return datain[i].type;
}

int BackLocate(int i) //返回该数据的locate，单词分类码
{
	return datain[i].locate;
}

string BackData(int flag, int locate)//flag由type决定 ，返回flag对应的表的locate位置
{
	int i;
	switch (flag)
	{
	case 1: return KT[locate]; break;
	case 2: return PT[locate]; break;
	case 3: return ST[locate]; break;
	case 4: return CT[locate]; break;
	case 5: return IT[locate]; break;
	default: {cout << "error" << endl;
	return "\0"; 
	break;
	}
	}
}