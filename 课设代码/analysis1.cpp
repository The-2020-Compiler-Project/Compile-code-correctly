#include"head.h"
#include<string>
#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include<deque>
using namespace std;
void Program(int& i, bool& flag);  //������ 
void State_table(int& i, bool& flag);  //���� 
void Do_state(int& i, bool& flag);   //������� 
void Exe_state(int& i, bool& flag);   //ִ����� 
void Judge_block(int& i, bool& flag);   //if 
void Judge_one(int& i, bool& flag);     //�ж����� �� 
void Judge_two(int& i, bool& flag);     //�ж����� 
void Judge_three(int& i, bool& flag);     //&&�� || 
void Judge_four(int& i, bool& flag);      //����������ʽ 
void Judge_five(int& i, bool& flag);        //> < =������������ 
void Else_block(int& i, bool& flag);   //else
void Loop_block(int& i, bool& flag);    //ѭ�� 
void Arith_ex(int& i, bool& flag);       //�������ʽ 
void Arith_one(int& i, bool& flag);       //�Ӽ� 
void Term(int& i, bool& flag);               //�� 
void Term_one(int& i, bool& flag);  //�˳� 
void Factor(int& i, bool& flag);    //���� 
void Arith_qu(int& i, bool& flag); //�﷨������������
//vector<STY>FourStyle; //��Ԫʽ
//ector<SymbolNode>Symbol;  //���ű�
deque<string> SEM; 
int t_value;//�м����ֵt

bool ANALYSIS()//����ֵ���жϷ����ɹ����
{
	int i = 0;
	string type;
	int locate;
	string data;
	bool flag;
	Program(i, flag);//next-w��i++����ȡ��һ�����ʣ�flagΪ��ǣ�ֻ��flagΪ1���ܼ��������������������
	type = BackType(i); //���ص�i�����ݵ�����
	if (type == "deli")  //���
	{
		locate = BackLocate(i); //���ص�ǰ������token��Ӧ���е�λ��
		data = BackData(2, locate); //���ص�ǰ����
		if (data == "#")  //�������
		{
			flag = true;
		}
		else flag = false;

	}
	out_files();
	return flag;
}


void Program(int& i, bool& flag)  //����
{
	string type; //���Ͷ���
	int locate; //����λ��
	string data;  //1����

	type = BackType(i);
	if (type == "key") //�ؼ���
	{
		locate = BackLocate(i);
		data = BackData(1, locate);  //������token�����е���Ϣ
		if (data == "int")
		{
			flag = true;
			i++;
			locate = BackLocate(i);
			data = BackData(1, locate);  //����һ������
			if (data == "main")
			{
				flag = true;
				i++;
				type = BackType(i);
				if (type == "deli")  //���
				{
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "(")
					{
						flag = true;
						i++;
						type = BackType(i);
						if (type == "deli")  //���
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
				if (type == "deli")  //���
				{
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "{")
					{
						flag = true;
						i++;
						State_table(i, flag);
						locate = BackLocate(i); //���������ɷ��ص�ǰ�����������
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


void State_table(int& i, bool& flag)  //����
{
	Do_state(i, flag);  //�������
	Exe_state(i, flag);  //ִ�����
}


void Do_state(int& i, bool& flag) //�������
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "key")  //�������
	{
		locate = BackLocate(i);
		data = BackData(1, locate);
		if (data == "float" || data == "string"|| data == "int") //���������ж�
		{
			i++;
			type = BackType(i);
			if (type == "iden")  //����
			{
				locate = BackLocate(i);
				data = BackData(5, locate);
				StoreSymbolNode(data, 1, 1);
				i++;
				type = BackType(i);
				if (type == "deli")  //���
				{
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == ";") //��������ĩβӦΪ;
					{
						i++;
						Do_state(i, flag);
					}

				}
			}
		}
	}
}


void Exe_state(int& i, bool& flag)  //ִ�����
{
	string type;  //����
	int locate, b;  //λ��
	string data, data1, data2; //��������
	type = BackType(i);
	if (type == "iden")
	{
		locate = BackLocate(i);
		data1 = BackData(5, locate);
		SEM.push_front(data);  //�洢��������������
		i++;
		type = BackType(i);  //��ȡ��һ�����ʣ�����ʼ�ж����� 
		if (type == "deli")   //���������Ϊ��������
		{
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == "=")  //��ֵ�����ʽ
			{
				flag = true;
				i++;
				b = i;
				Arith_ex(i, flag);    //��������Ҳ�Ϊ�������ʽ
				type = BackType(b);
				if (type == "string")  //��Ϊ�ַ���
				{
					ASSI(data1, 2);  //��ֵ������Ԫʽ
				}
				else ASSI(data1, 0);
				locate = BackLocate(i);
				data = BackData(2, locate);
				if (data == ";")  //���ĩβΪ;
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


void Judge_block(int& i, bool& flag)  //�ж�����
{

	string type; //����
	int locate;  //��Ӧ����λ��
	string data;  //��������
	type = BackType(i);
	if (type == "deli")  //���
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "(")
		{
			flag = true;
			i++;
			Judge_one(i, flag);  //�ж�����
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == ")") //�ж���������������if����
			{
				IF();
				flag = true;
				i++;
				locate = BackLocate(i);
				data = BackData(2, locate);
				if (data == "{") //��ʼΪ������
				{
					flag = true;
					i++;
					Exe_state(i, flag);  //ִ�����
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "}")   //if��������Ű�����������
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


void Judge_one(int& i, bool& flag)//!���
{

	string type;
	int locate;
	string data;

	type = BackType(i);
	if (type == "deli") //������������
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "!")
		{
			i++;
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == "(") //����������ж�
			{
				flag = true;
				i++;
				Judge_two(i, flag);  //�������ʽ�ж��Ƿ���ȷ
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
	Judge_three(i, flag); //�������ж�

}

void Judge_three(int& i, bool& flag)//&&,||
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli")  //�ǽ��
	{
		locate = BackLocate(i);
		data = BackData(2, locate);//�жϽ������
		if (data == "&&")
		{
			i++;
			Judge_one(i, flag); //�ǲ��ǣ����
			GEQ("&&");
		}
		else
		{
			if (data == "||")
			{
				i++;
				Judge_one(i, flag);//�ǲ��ǣ����
				GEQ("||");
			}
		}
	}

}

void Judge_four(int& i, bool& flag) //����������ʽ
{
	Arith_ex(i, flag); //�������ʽ
	Judge_five(i, flag); //���������> < >= ��������������

}

void Judge_five(int& i, bool& flag)//��2 < > <= >= == !=������ж�
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli") //����Ҫ���ǽ��
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "<" || data == ">" || data == "<=" || data == ">=" || data == "==" || data == "!=")
		{
			i++;
			Arith_ex(i, flag);//�������ʽ
			GEQ(data);
		}
	}
}

void Else_block(int& i, bool& flag) //else����
{
	string type;  //��������
	int locate;  //��Ӧtoken��λ��
	string data;  //����
	type = BackType(i);
	if (type == "key")  //else���鿪ͷΪelse�����Ա���Ϊ�ؼ���
	{
		locate = BackLocate(i);
		data = BackData(1, locate);
		if (data == "else")  //�ж��Ƿ�Ϊelse
		{  
			ELSE();  
			i++;
			type = BackType(i);
			if (type == "deli")  //else���������ж�
			{
				locate = BackLocate(i);
				data = BackData(2, locate);
				if (data == "{")  //�����ж�
				{
					flag = true;
					i++;
					Exe_state(i, flag);  //else���麯��
					locate = BackLocate(i);
					data = BackData(2, locate);
					if (data == "}")  //�ж��Ƿ�Ϊ�����Ž���
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

void Loop_block(int& i, bool& flag)  //ѭ������
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli")  //�ж�while�����Ƿ�Ϊ���ţ����������������
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "(")
		{
			WHILE();
			flag = true;
			i++;
			Judge_one(i, flag);   //�ж�ѭ�������Ƿ�Ϊ�������
			locate = BackLocate(i);
			data = BackData(2, locate);
			if (data == ")")//�����ж����
			{

				flag = true;
				i++;
				locate = BackLocate(i);
				data = BackData(2, locate);
				DO();
				if (data == "{")  //ѭ������������ж�
				{
					flag = true;
					i++;
					Exe_state(i, flag);  //����ִ�����
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


void Arith_ex(int& i, bool& flag) //�������ʽ����
{
	Term(i, flag);
	Arith_one(i, flag);
}

void Arith_one(int& i, bool& flag)//��0 +��- �ӷ�������������ʽ
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

void Term(int& i, bool& flag)  //�������ʽ���
{
	Factor(i, flag);
	Term_one(i, flag);
} 

void Term_one(int& i, bool& flag)//��1 *��/ �˷�������������ʽ
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

void Factor(int& i, bool& flag)  //�������Ӻ���
{
	string type;
	int locate;
	string data;
	type = BackType(i);
	if (type == "deli") //���
	{
		locate = BackLocate(i);
		data = BackData(2, locate);
		if (data == "(")  //�ж����� 
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

void Arith_qu(int& i, bool& flag)  //������������Ӻ���
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

	else if (type == "float")  //float���� 
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
		if (type == "string")   //��ʶ�� 
		{
			locate = BackLocate(i);
			data = BackData(3, locate);
			SEM.push_front(data);
			i++;
		}
	}

}


