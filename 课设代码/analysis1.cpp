#include"head.h"
#include<string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include<deque>
using namespace std;
void Program(int& i, bool& flag);  //函数块 
void State_table(int& i, bool& flag);  //语句块 
void Do_state(int& i, bool& flag);   //声明语句 
void Exe_state(int& i, bool& flag);   //执行语句 
void Judge_block(int& i, bool& flag);   //if 
void Judge_one(int& i, bool& flag);     //判断条件 ！ 
void Judge_two(int& i, bool& flag);     //判断条件 
void Judge_three(int& i, bool& flag);     //&&， || 
void Judge_four(int& i, bool& flag);      //后继算术表达式 
void Judge_five(int& i, bool& flag);        //> < =······ 
void Else_block(int& i, bool& flag);   //else
void Loop_block(int& i, bool& flag);    //循环 
void Arith_ex(int& i, bool& flag);       //算术表达式 
void Arith_one(int& i, bool& flag);       //加减 
void Term(int& i, bool& flag);               //项 
void Term_one(int& i, bool& flag);  //乘除 
void Factor(int& i, bool& flag);    //因子 
void Arith_qu(int& i, bool& flag); //语法分析函数定义
//vector<STY>FourStyle; //四元式
//ector<SymbolNode>Symbol;  //符号表
deque<string> SEM; 
int t_value;//中间变量值t

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
	return flag;
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
	type = BackType(i);
	if (type == "key")  //声明语句
	{
		locate = BackLocate(i);
		data = BackData(1, locate);
		if (data == "float" || data == "string"|| data == "int") //变量声明判断
		{
			i++;
			type = BackType(i);
			if (type == "iden")  //变量
			{
				locate = BackLocate(i);
				data = BackData(5, locate);
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
		if (data == "(")  //判断括号 
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

	else if (type == "float")  //float数据 
	{
		locate = BackLocate(i);
		data = BackData(4, locate);
		SEM.push_front(data);
		i++;
	}
	else
	{
		locate = BackLocate(i);
		data = BackData(1, locate);
		if (type == "string")   //标识符 
		{
			locate = BackLocate(i);
			data = BackData(3, locate);
			SEM.push_front(data);
			i++;
		}
	}

}


