#7.1前工作总结#
&emsp;这一次的课程设计对我而言是一次很大的挑战，基础不扎实，而且语义分析的符号表与四元式等内容掌握的不到位，因此我在课程设计前进行了对课程内容的复习与巩固，以及查找类似内容的实例进行学习，与组内成员一起参考类似编译器的资料，并初步做一些课程设计前的准备。
第一次上机初步与组员完成对文法的设计。
#7.1个人工作总结#
&emsp;第二次上机我与李龙泽、刘永亮等同学对符号表的结构进行了讨论和设计，最终我们决定采用结构体的方式来进行存储符号表的单个信息，并采用vector来存储符号总表，其他的类型表，函数表数组表等均采用类似的结构。并且与另一位负责语义分析的李龙泽同学大致确定了四元式所用的函数。
符号表结构（暂定）：  
//符号表总表结构  
vector  
typedef struct  
{  
&emsp;		string data;  //名称  
&emsp;		//datatype;  数据类型  
&emsp;		string type; //种类  
&emsp;		int locate;   //地址  
}SymbolNode;  
//函数表  
typedef struct  
{  
&emsp;		int depth//嵌套层次  
&emsp;		int cnumbers;  //数据上界  
&emsp;		//参数表  
&emsp;		int inlocate;   //入口地址  
}ArrayChart;  
//数组表  
typedef struct  
{  
&emsp;		int low;  //数组下界  
&emsp;		int up;  //数据上界  
&emsp;		int arraytype; //种类  
&emsp;		int length;   //地址  
}ArrayChart;  
//类型表  
typedef struct  
{  
&emsp;		int kindtype;  //类型代码  
&emsp;		//不同类型指针  
}KindChart;  
#7.2个人工作总结#
语义分析部分代码的编写。 与李龙泽同学基本完成四元式的主要函数。
&emsp; 主要函数及功能：  （负责部分四元式）
&emsp; void WHILE()//循环语句while四元式
&emsp; void DO()//循环语句do四元式
&emsp; void WHILEEND()//循环语句while结束四元式
&emsp; void GEQSingle(string oper)//单目运算符四元式 
&emsp; void ASSI(string newString, int t)//赋值运算四元式
#问题及解决方案#
 1.符号表设计过程中某些信息的存储问题
在设计符号表时，对于不同的表其存储类型也不同，需要设立不同的指针分别指向这些不同的表，目前已经解决了大部分表中数据类型的问题，对于一些复杂的类型指针仍在尝试解决中。
 2.四元式的代码编写
&emsp;对于四元式中单目运算符和双目运算符的函数存在一定的难度，在和李龙泽同学一起研究学习以及参考实例后，选择通过流来实现字符串和数字的转换，完成了关键步骤。 