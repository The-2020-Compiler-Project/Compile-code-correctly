#include"Tips.h"
#include"head.h"
#include<vector>
#include<stack>
#include<fstream>
using namespace std;

struct block_begin_end //基本块划分形成的块
{
	int begin; //标记一个基本块的四元式开始序号
	int end;  //标记一个基本块的四元式最后序号
};

struct RDL    //单寄存器
{
	string data;  //寄存器中的数据
	int state;   //该数据的活跃信息；y-1;n-0;
};

/********************************************/
//这三个本.cpp应通用
//这样就可以达到在这个.cpp中各个函数中随意使用该四元式
extern vector<STY> FourStyle;
extern vector<SymbolNode> Symbol; //一个严重问题，Symbol到这个.cpp后，数量多了一倍，但在siyuanshi.cpp中没有问题
vector<block_begin_end> block;
/********************************************/

void GetBlock();        // 基本块划分；存在block中
void ActiveInfo(int i); //活跃信息填写；存在FourStyle中
void InitSymbol();      //一个块完成后，把Symbol表重置

void TargetCode()
{
	OUTPUT();
	OUTPUTStoreSymbolNode();
	unsigned int i;
	unsigned int j;
	unsigned int locate;
	unsigned int locate_1;
	vector<string> OBJ;//存放目标代码
	stack<string> SEM;
	vector<string>iden; //需要预先进行分配内存的标志符
	string s1; //用来存放当下的目标代码
	string s2; //用来存放当下的目标代码
	string s3;
	string ss;//用来表示+-*/对应的目标代码
	string su;
	RDL R; //模拟单寄存器
	fstream Targetcode;
	int a = 0;
	//FourStyle = siyuanshi();
	//进行块划分
	GetBlock();

	//寄存器初始化
	R.data = "\0";
	R.state = 0;

	for (i = 0; i < block.size(); i++) 
	{
		ActiveInfo(i);   //活跃信息填写；存在FourStyle中；逆序来设置
		for (j = block[i].begin; j <= block[i].end; j++)
		{
			if (FourStyle[j].third != "\0" && FourStyle[j].t == 1)  //四元式j 运算结果不为空字符 并且是活跃
			{
				su = FourStyle[j].third;
				iden.push_back(su); //得到要进行存储，并需要开辟空间的一系列数据
							     	//0-临时变量；1-非临时变量
			}
		}
	}

	//进行汇编语言的预编写；
	//采取先写到一个vector OBJ中，完成之后再向文件中写
	//数据端
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
	//堆栈段
	s1 = "SSEG   SEGMENT   STACK";
	OBJ.push_back(s1);
	s1 = "STK   DB   80H DUP(0)";
	OBJ.push_back(s1);
	s1 = "SSEG   ENDS";
	OBJ.push_back(s1);
	//代码段
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
		//取块进行活跃信息的标记
		//最后活跃信息放在FourStyle的f,s,t,中
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
		//进行目标代码编写
		for (j = block[i].begin; j <= block[i].end; j++)
		{

			//加减乘除
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
						//活跃
						if (FourStyle[j].f == 1)
						{
							s1 = "MOV " + FourStyle[j].first + ",AL";
							s2 = ss + " AL," + FourStyle[j].second;
							OBJ.push_back(s1);
							OBJ.push_back(s2);
						}
						else  //不活跃
						{
							s1 = ss + " AL," + FourStyle[j].second;
							OBJ.push_back(s1);
						}
					}
					else if (R.data == FourStyle[j].second && (FourStyle[j].deli == "+" || FourStyle[j].deli == "*"))
					{
						if (FourStyle[j].s == 1) //活跃
						{
							s1 = "MOV " + FourStyle[j].second + ",AL";
							OBJ.push_back(s1);
						}
						//不管活不活跃
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
			//赋值

			//逻辑运算
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
						//活跃
						if (FourStyle[j].f == 1)
						{
							s1 = "MOV " + FourStyle[j].first + ",AL";
							s2 = "MOV AL,AL " + ss + " " + FourStyle[j].second;
							OBJ.push_back(s1);
							OBJ.push_back(s2);
						}
						else  //不活跃
						{
							s1 = "MOV AL,AL " + ss + " " + FourStyle[j].second;
							OBJ.push_back(s1);
						}
					}
					else if (R.data == FourStyle[j].second && (FourStyle[j].deli == "!=" || FourStyle[j].deli == "=="
						|| FourStyle[j].deli == "&&" || FourStyle[j].deli == "||"))
					{
						if (FourStyle[j].s == 1) //活跃
						{
							s1 = "MOV " + FourStyle[j].second + ",AL";
							OBJ.push_back(s1);
						}
						//不管活不活跃
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

			//!运算
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
						//活跃
						if (FourStyle[j].f == 1)
						{
							s1 = "MOV " + FourStyle[j].first + ",AL";
							s2 = "MOV AL,NOT AL";
							OBJ.push_back(s1);
							OBJ.push_back(s2);
						}
						else  //不活跃
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
					//这时候不应该看寄存器中存的数据的state，而是看FourStyle中的；
					//因为FourStyle中是最新的
					if (FourStyle[j].f == 1)
					{
						s1 = "MOV " + FourStyle[j].first + ",AL";
						OBJ.push_back(s1);
					}
				}
				//我认为这时候不是first，但是可以是third，那么只需要LD就可以了
				else if (R.data != FourStyle[j].first)
				{
					//不是third并且活跃的时候才需要ST，其他的只需要LD
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
				//防止这个时候寄存器中有数据
				//主要是我每次在最后都会把寄存器中的数据该为该次的third的相关数据；
				//所以在wh这里寄存器可能会有东西存在
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
				s2 = "JBE   OUT" + to_string(a);//当不满足条件的时候，跳出去		
				OBJ.push_back(s1);
				OBJ.push_back(s2);
				s3 = "OUT" + to_string(a);  //逆序压栈
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

			//函数
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

			//每一句结束，寄存器中都会有一个数据
			//放在每句的最后，是因为每次读一个句子进行编写目标代码的时候，刚开始的时候寄存器中的东西是上一个句子的third
			//不需要针对if做修改，因为if中的third是\0；所以在ActiveInfo时，并没有修改，其t还是0
			R.data = FourStyle[j].third;
			R.state = FourStyle[j].t;
		}
		//在一个块完成后，要把Symbol的数据重置归“零”
		InitSymbol();
	}

	//结尾处理

	s1 = "MOV   AH,4CH";
	s2 = "INT   21H";
	OBJ.push_back(s1);
	OBJ.push_back(s2);
	s1 = "CSEG   ENDS";
	s2 = "      END   START";
	OBJ.push_back(s1);
	OBJ.push_back(s2);

	Targetcode.open("TargetCode.ASM", ios::out);
	//输出信息；
	for (i = 0; i < OBJ.size(); i++)
	{
		cout << i << "  " << OBJ[i] << endl;
		Targetcode << i << "  " << OBJ[i] << endl;
	}

}

void GetBlock()   // 基本块划分；存在block中
{
	unsigned int i;  //因为vector中 .size()的返回值是无符号数
	int n;
	block_begin_end a;
	a.begin = 0;
	for (i = 0; i < FourStyle.size(); i++)
	{   //如果遇到这些就直接end；                         push_back的作用是 vector尾部加入一个数据；
		if (FourStyle[i].deli == "if") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "el") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "ie") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "wh") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "do") { a.end = i; block.push_back(a); a.begin = i + 1; }
		if (FourStyle[i].deli == "we") { a.end = i; block.push_back(a); a.begin = i + 1; }
	}
	n = FourStyle.size();
	//为了防止最后的四元式是一系列的赋值语句
	//如果只有上述的块结束标记，会导致丢掉很多语句
	if (FourStyle[n - 1].deli != "if"    &&FourStyle[n - 1].deli != "el"  && FourStyle[n - 1].deli != "ie"
	 && FourStyle[n - 1].deli != "wh"    &&FourStyle[n - 1].deli != "do"  && FourStyle[n - 1].deli != "we")
	{
		a.end = n - 1;
		block.push_back(a);
	}
}

void ActiveInfo(int i)   //活跃信息填写；存在FourStyle中；逆序来设置
{
	unsigned int m;
	int first;
	int second;
	int third;
	int j;   //基本块内，逆序

	//这个块，活跃信息用逆序来设置
	for (j = block[i].end; j >= block[i].begin; j--)//只是标志了四元式的序号
	{
		first = -1;
		second = -1;
		third = -1;
		//在Symbol中找到对应的数据
		for (m = 0; m < Symbol.size(); m++)  //Symbol数据出现问题，重复了一倍
		{
			if (FourStyle[j].first  == Symbol[m].data) first = m;
			if (FourStyle[j].second == Symbol[m].data) second = m;
			if (FourStyle[j].third  == Symbol[m].data) third = m;
			//要注意到，四元式的后三个元素并不一定都是符号；可以是常数、字符串、或者空；并不一定都是符号的；
			//所以，到循环结束的时候first,second,third可能有的是-1；
		}
		
		//对该四元式标记活跃信息
		if (first != -1)
		{
			FourStyle[j].f = Symbol[first].state;
			Symbol[first].state = 1;//活跃是1
		}
		if (second != -1)
		{
			FourStyle[j].s = Symbol[second].state;
			Symbol[second].state = 1;
		}
		if (third != -1)
		{
			FourStyle[j].t = Symbol[third].state;
			Symbol[third].state = 0;//不活跃是0
		}
	}
}

void InitSymbol()  //一个块完成后，把Symbol表重置
{
	unsigned int i;
	for (i = 0; i < Symbol.size() / 2 ; i++)          //非临时时1，临时是0；
	{
		if (Symbol[i].type == 1) Symbol[i].state = 1; //非临时变量出来的时候变为y ；
		else Symbol[i].state = 0;                     //临时变量初值为n
	}
}
