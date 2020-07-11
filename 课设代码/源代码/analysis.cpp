#include "Tips.h"
#include"head.h"
#include<string>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <stack>
#include<deque>
#include <sstream>
using namespace std;
void Program(int& i, bool& flag);
void State_table(int& i, bool& flag);
void Do_state(int& i, bool& flag);
void Exe_state(int& i, bool& flag);
void Judge_block(int& i, bool& flag);
void Judge_one(int& i, bool& flag);
void Judge_two(int& i, bool& flag);
void Judge_three(int& i, bool& flag);
void Judge_four(int& i, bool& flag);
void Judge_five(int& i, bool& flag);
void Else_block(int& i, bool& flag);
void Loop_block(int& i, bool& flag);
void Arith_ex(int& i, bool& flag);
void Arith_one(int& i, bool& flag);
void Term(int& i, bool& flag);
void Term_one(int& i, bool& flag);
void Factor(int& i, bool& flag);
void Arith_qu(int& i, bool& flag); //语法分析函数定义
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
void StoreSymbolNode(string data, int type, int state);
void OUTPUTStoreSymbolNode();
void out_files();
void Insertnewsymbol(string data, string intype, string wordtype);
void outnewsymbol();
vector<STY>FourStyle; //四元式
vector<SymbolNode>Symbol;  //符号表
deque<string> SEM; 
int t_value;//中间变量值t
typedef struct//符号表信息
{
	string wordname;
	string wordtype;
	string intype;
}newsymbol;
vector<newsymbol> new_chart;
bool ANALYSIS()//返回值，判断分析成功与否
{
	int i = 0;
	string type;
	int locate;
	string data;
	bool flag;
	Program(i, flag);//next-w即i++，读取下一个单词，flag为标记，只有flag为1才能继续分析，否则输出错误。
	type = BackType(i); //返回第i个数据的类型
	if (type == "deli")  //界符
	{
		locate = BackLocate(i); //返回当前单词在token对应类中的位置
		data = BackData(2, locate); //返回当前单词
		if (data == "#")  //分析完成
		{
			flag = true;
		}
		else flag = false;
	}
	out_files();
	outnewsymbol();
	return flag;
	if (flag == false)
	{
		cout << "错误位置：" << i <<  endl;
		cout << "语法分析错误，任意键退出程序！";
		system("pause");
		exit(0);
	}
}


void Program(int& i, bool& flag)  //函数
{
	string type; //类型定义
	int locate; //类中位置
	string data;  //1单词

	type = BackType(i);
	if (type == "key") //关键字
	{
		locate = BackLocate(i);
		data = BackData(1, locate);  //返回在token序列中的信息
		if (data == "int")
		{
			flag = true;
			i++;
			locate = BackLocate(i);
			data = BackData(1, locate);  //读下一个单词
			if (data == "main")
			{
				flag = true;
				i++;
				type = BackType(i);
				if (type == "deli")  //界符
				{
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "(")
					{
						flag = true;
						i++;
						type = BackType(i);
						if (type == "deli")  //界符
						{
							locate = BackLocate(i);
							data = BackData(2, locate);
							if (data == ")")
							{
								flag = true;
								i++;
							}
							else flag = false;
						}
						else flag = false;
					}
					else flag = false;
				}
				else flag = false;
				if (flag == false)
				{
					cout << "错误位置：" << i << endl;
					cout << "语法分析错误，任意键退出程序！";
					system("pause");
					exit(0);
				}
				type = BackType(i);
				if (type == "deli")  //界符
				{
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "{")
					{
						flag = true;
						i++;
						State_table(i, flag);
						locate = BackLocate(i); //语句块分析完成返回当前单词相关数据
						data = BackData(2, locate);
						if (data == "}")
						{
							flag = true;
							i++;
						}
						else flag = false;
					}
					else flag = false;
				}

			}
			else flag = false;
		}

		else flag = false;
	}
	if (flag == false)
	{
		cout << "错误位置：" << i <<  endl;
		cout << "语法分析错误，任意键退出程序！";
		system("pause");
		exit(0);
	}
}


void State_table(int& i, bool& flag)  //语句块
{
	Do_state(i, flag);  //声明语句
	Exe_state(i, flag);  //执行语句
}


void Do_state(int& i, bool& flag) //声明语句
{
	string type;
	int locate;
	string data;
	string datatype;
	string intype = "v";
	type = BackType(i);
	if (type == "key")  //声明语句
	{
		locate = BackLocate(i);
		data = BackData(1, locate);
		datatype = data;
		if (data == "float" || data == "string"|| data == "int") //变量声明判断
		{
			i++;
			type = BackType(i);
			if (type == "iden")  //变量
			{
				locate = BackLocate(i);
				data = BackData(5, locate);
				Insertnewsymbol(data, datatype, intype);
				StoreSymbolNode(data, 1, 1);
				i++;
				type = BackType(i);
				if (type == "deli")  //界符
				{
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == ";") //变量声明末尾应为;
					{
						i++;
						Do_state(i, flag);
					}

				}
			}
		}
	}
}


void Exe_state(int& i, bool& flag)  //执行语句
{
	string type;  //类型
	int locate, b;  //位置
	string data, data1, data2; //单词数据
	type = BackType(i);
	if (type == "iden")
	{
		locate = BackLocate(i);
		data1 = BackData(5, locate);
		SEM.push_front(data);  //存储运算符左侧运算量
		i++;
		type = BackType(i);  //读取下一个单词，并开始判断运算 
		if (type == "deli")   //界符（若不为界符则错误）
		{
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == "=")  //赋值运算等式
			{
				flag = true;
				i++;
				b = i;
				Arith_ex(i, flag);    //若运算符右侧为算术表达式
				type = BackType(b);
				if (type == "string")  //若为字符串
				{
					ASSI(data1, 2);  //赋值运算四元式
				}
				else ASSI(data1, 0);
				locate = BackLocate(i);
				data = BackData(2, locate);
				if (data == ";")  //语句末尾为;
				{
					flag = true;
					i++;
					Exe_state(i, flag);
				}
				else flag = false;
			}
			else flag = false;
		}
		if (flag == false)
		{
			cout << "错误位置：" << i << endl;
			cout << "语法分析错误，任意键退出程序！";
			system("pause");
			exit(0);
		}
	}
	else
	{
		if (type == "key")
		{
			locate = BackLocate(i);
			data = BackData(1, locate);
			if (data == "if")
			{

				i++;
				Judge_block(i, flag);

				Exe_state(i, flag);
			}
			else
			{
				if (data == "while")
				{

					i++;
					Loop_block(i, flag);

					Exe_state(i, flag);
				}
			}
		}
	}

}


void Judge_block(int& i, bool& flag)  //判断语句块
{

	string type; //类型
	int locate;  //对应类中位置
	string data;  //单词数据
	type = BackType(i);
	if (type == "deli")  //界符
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "(")
		{
			flag = true;
			i++;
			Judge_one(i, flag);  //判断条件
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == ")") //判断条件结束，进入if语句块
			{
				IF();
				flag = true;
				i++;
				locate = BackLocate(i);
				data = BackData(2, locate);
				if (data == "{") //开始为大括号
				{
					flag = true;
					i++;
					Exe_state(i, flag);  //执行语句
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "}")   //if语句块大括号包括，结束。
					{
						flag = true;
						i++;
						Else_block(i, flag);
						IFEND();
					}
					else flag = false;
				}
				else flag = false;
			}
			else flag = false;
		}
		else flag = false;
	}
	if (flag == false)
	{
		cout << "错误位置：" << i  << endl;
		cout << "语法分析错误，任意键退出程序！";
		system("pause");
		exit(0);
	}
}


void Judge_one(int& i, bool& flag)//!情况
{

	string type;
	int locate;
	string data;

	type = BackType(i);
	if (type == "deli") //界符（！情况）
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "!")
		{
			i++;
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == "(") //！后面跟（判断
			{
				flag = true;
				i++;
				Judge_two(i, flag);  //条件表达式判断是否正确
				locate = BackLocate(i);
				data = BackData(2, locate);
				if (data == ")")
				{
					GEQSingle("!");   
					flag = true;
					i++;
				}
				else flag = false;
			}
			else flag = false;
		}
		if (flag == false)
		{
			cout << "错误位置：" << i << endl;
			cout << "语法分析错误，任意键退出程序！";
			system("pause");
			exit(0);
		}
	}
	else Judge_two(i, flag);
}


void Judge_two(int& i, bool& flag)
{
	Judge_four(i, flag);
	Judge_three(i, flag); //界符与或判断

}

void Judge_three(int& i, bool& flag)//&&,||
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli")  //是界符
	{
		locate = BackLocate(i);
		data = BackData(2, locate);//判断界符种类
		if (data == "&&")
		{
			i++;
			Judge_one(i, flag); //是不是！情况
			GEQ("&&");
		}
		else
		{
			if (data == "||")
			{
				i++;
				Judge_one(i, flag);//是不是！情况
				GEQ("||");
			}
		}
	}

}

void Judge_four(int& i, bool& flag) //后继算术表达式
{
	Arith_ex(i, flag); //算术表达式
	Judge_five(i, flag); //连接运算符> < >= ······等

}

void Judge_five(int& i, bool& flag)//ω2 < > <= >= == !=运算符判断
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli") //首先要求是界符
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "<" || data == ">" || data == "<=" || data == ">=" || data == "==" || data == "!=")
		{
			i++;
			Arith_ex(i, flag);//算术表达式
			GEQ(data);
		}
	}
}

void Else_block(int& i, bool& flag) //else语句块
{
	string type;  //单词类型
	int locate;  //对应token类位置
	string data;  //单词
	type = BackType(i);
	if (type == "key")  //else语句块开头为else，所以必须为关键字
	{
		locate = BackLocate(i);
		data = BackData(1, locate);
		if (data == "else")  //判断是否为else
		{  
			ELSE();  
			i++;
			type = BackType(i);
			if (type == "deli")  //else语句块括号判断
			{
				locate = BackLocate(i);
				data = BackData(2, locate);
				if (data == "{")  //括号判断
				{
					flag = true;
					i++;
					Exe_state(i, flag);  //else语句块函数
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "}")  //判断是否为右括号结束
					{
						flag = true;
						i++;
					}
					else flag = false;
				}
				else flag = false;
			}
		}

	}
	if (flag == false)
	{
		cout << "错误位置：" << i  << endl;
		cout << "语法分析错误，任意键退出程序！";
		system("pause");
		exit(0);
	}
}

void Loop_block(int& i, bool& flag)  //循环语句块
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli")  //判断while后面是否为括号，若不是括号则错误。
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "(")
		{
			WHILE();
			flag = true;
			i++;
			Judge_one(i, flag);   //判断循环条件是否为！的情况
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == ")")//条件判断完成
			{

				flag = true;
				i++;
				locate = BackLocate(i);
				data = BackData(2, locate);
				DO();
				if (data == "{")  //循环语句块大括号判断
				{
					flag = true;
					i++;
					Exe_state(i, flag);  //块内执行语句
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "}")
					{
						WHILEEND();  
						flag = true;
						i++;
					}
					else flag = false;
				}
				else flag = false;
			}
			else flag = false;
		}
		else flag = false;
	}
	if (flag == false)
	{
		cout << "错误位置：" << i  << endl;
		cout << "语法分析错误，任意键退出程序！";
		system("pause");
		exit(0);
	}
}


void Arith_ex(int& i, bool& flag) //算术表达式函数
{
	Term(i, flag);
	Arith_one(i, flag);
}

void Arith_one(int& i, bool& flag)//ω0 +或- 加法或减法算术表达式
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli")
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "+" || data == "-")
		{
			i++;
			Term(i, flag);
			GEQ(data);
			Arith_one(i, flag);
		}

	}

}  //

void Term(int& i, bool& flag)  //算术表达式项函数
{
	Factor(i, flag);
	Term_one(i, flag);
} 

void Term_one(int& i, bool& flag)//ω1 *或/ 乘法或除法算术表达式
{
	string type;
	int locate;
	string data;
	//bool fla;
	type = BackType(i);
	if (type == "deli")
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "*" || data == "/")
		{
			i++;
			Factor(i, flag);
			GEQ(data);
			Term_one(i, flag);
		}
	}

}

void Factor(int& i, bool& flag)  //括号因子函数
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli") //界符
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "(")
		{  
			i++;
			Arith_ex(i, flag);
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == ")")
			{
				flag = true;
				i++;
			}
			else flag = false;

		}
	}
	else Arith_qu(i, flag);
	if (flag == false)
	{
		cout << "错误位置：" << i << endl;
		cout << "语法分析错误，任意键退出程序！";
		system("pause");
		exit(0);
	}
}

void Arith_qu(int& i, bool& flag)  //定义的算数因子函数
{

	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "iden")
	{
		locate = BackLocate(i);
		data = BackData(5, locate);
		SEM.push_front(data);
		i++;
	}

	else if (type == "float")
	{
		// i++;
		locate = BackLocate(i);
		data = BackData(4, locate);
		SEM.push_front(data);
		i++;
	}
	else
		//if(data=="string")
	{
		locate = BackLocate(i);
		data = BackData(1, locate);
		//cout << "daolee" << endl;
		if (type == "string")
		{
			//i++;
			locate = BackLocate(i);
			data = BackData(3, locate);
			SEM.push_front(data);
			i++;
		}
	}

}


void IF()
{
	string tM;
	tM = *SEM.begin();
	SEM.pop_front();
	SEND_FORMULA("if", tM, " ", " ", 0);
}


void ELSE()
{
	SEND_FORMULA("el", " ", " ", " ", 0);
}


void IFEND()
{
	SEND_FORMULA("ie", " ", " ", " ", 0);
}


void WHILE()
{
	SEND_FORMULA("wh", " ", " ", " ", 0);
}


void DO()
{
	string tM;
	tM = *SEM.begin();
	SEM.pop_front();
	SEND_FORMULA("do", tM, " ", " ", 0);
}


void WHILEEND()
{
	SEND_FORMULA("we", " ", " ", " ", 0);
}

void GEQ(string oper)//双目运算符四元式
{
	stringstream ss;//通过流来实现字符串和数字的转换
	string numt, Numt = "t";
	ss << t_value;//向流中传值
	ss >> numt;//向numt中写入值
	Numt = Numt + numt;
	string tM, tM1;
	tM = *SEM.begin();
	SEM.pop_front();
	tM1 = *SEM.begin();
	SEM.pop_front();
	SEM.push_front(Numt);
	SEND_FORMULA(oper, tM1, tM, Numt, 0);
	StoreSymbolNode(Numt, 0, 0);
	t_value++;
}


void GEQSingle(string oper)//单目运算符四元式 ！
{
	stringstream ss;
	string numt, Numt = "t";
	ss << t_value;
	ss >> numt;
	Numt = Numt + numt;
	string tM;
	tM = *SEM.begin();
	SEM.pop_front();
	SEM.push_front(Numt);
	SEND_FORMULA(oper, tM, " ", Numt, 0);
	t_value++;
}


void ASSI(string newString, int t)//赋值运算四元式
{
	string tM;
	tM = *SEM.begin();
	SEM.pop_front();
	SEND_FORMULA("=", tM, " ", newString, t);
}

void OUTPUT()
{
	int m;
	for (m = 0; m < FourStyle.size(); m++)           //.size()获取行向量的大小
	{
		cout << "(" << FourStyle[m].deli << "," << FourStyle[m].first << "," << FourStyle[m].second << "," << FourStyle[m].third /*<< "," << FourStyle[m].t */ << ")" << endl;
	}
}

void OUTPUTStoreSymbolNode()
{
	int m;
	for (m = 0; m < Symbol.size(); m++)           //.size()获取行向量的大小
	{
		cout << "(" << Symbol[m].data << "," << Symbol[m].type << "," << Symbol[m].state << ")" << endl;
	}
	cout << m << endl;
}

void out_files()
{
	fstream siyuanshi;
	fstream fuhaobiao;
	unsigned int i;
	siyuanshi.open("FourStyle.txt", ios::out);
	for (i = 0; i < FourStyle.size(); i++)
	{
		siyuanshi << "(" << FourStyle[i].deli << "," << FourStyle[i].first << ","
			<< FourStyle[i].second << "," << FourStyle[i].third << ")" << endl;
	}
	fuhaobiao.open("Symbol.txt", ios::out);
	for (i = 0; i < Symbol.size(); i++)
	{
		fuhaobiao << "(" << Symbol[i].data << "," << Symbol[i].type << "," << Symbol[i].state << ")" << endl;
	}
}

void SEND_FORMULA(string deli, string first, string second, string third, int t)
{
	STY  temSty;
	temSty.deli = deli;
	temSty.first = first;
	temSty.second = second;
	temSty.third = third;
	temSty.f = 0;
	temSty.s = 0;
	temSty.t = t;

	FourStyle.push_back(temSty);
}

void StoreSymbolNode(string data, int type, int state)
{
	SymbolNode Node;
	Node.data = data;
	Node.type = type;
	Node.state = state;
	Symbol.push_back(Node);
}
void Insertnewsymbol(string data, string intype, string wordtype)
{
	newsymbol onesymbol;
	onesymbol.wordname = data;
	onesymbol.intype = intype;
	onesymbol.wordtype = wordtype;
	new_chart.push_back(onesymbol);
}
void outnewsymbol()
{
	int symbollength = new_chart.size();
	cout << "符号表：" << endl;
	cout << "NAME  " << "TYPE  " << "CAT  "<<endl;
	for (int k = 0; k < symbollength; k++)
	{
		cout << new_chart[k].wordname<<",    ";
		cout << new_chart[k].wordtype << ",    ";
		cout << new_chart[k].intype << ",    " << endl;
	}
}