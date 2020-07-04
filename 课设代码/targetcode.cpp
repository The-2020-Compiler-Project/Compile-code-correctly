#include<vector>
#include<stack>
#include<fstream>
using namespace std;

struct block_begin_end  //基本块划分形成的块
{
	int begin;
	int end;
};

struct RDL
{
	string data;  //寄存器中的数据
	int state;      //该数据的活跃信息；y-1;n-0;
};

void GetBlock();         // 基本块划分；存在block中
void ActiveInfo(int i); //活跃信息填写；存在FourStyle中
void InitSymbol();     //一个块完成后，把Symbol表重置

void TargetCode()    //目标代码生成的主要函数
{

   RDL R; //模拟单寄存器


   GetBlock();   //块划分
 }

void GetBlock()  //基本块划分；存在block中
{
 }

void ActiveInfo(int i)   //活跃信息填写；存在FourStyle中；逆序来设置
{
int j;   //基本块内，逆序

//for (j = block[i].end; j >= block[i].begin; j--)//标志了四元式的序号
	{
                }
}

void InitSymbol()  //一个块完成后，把Symbol表重置
                            //非临时变量出来的时候变为y，临时变量初值为n
{
                unsigned int i;
	/*for (i = 0; i < Symbol.size() / 2 ; i++)          //非临时时1，临时是0；
	{
		if (Symbol[i].type == 1) Symbol[i].state = 1; //非临时变量出来的时候变为y ；
		else Symbol[i].state = 0;                     //临时变量初值为n
	}*/
}
