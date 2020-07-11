#include <iostream>
#include"head.h"
#include "Tips.h"

using namespace std;
int main()
{
	int count;
	bool flag;
	count = GetToken(); //Token序列
	//cout << count << endl; //单词个数
	system("pause");
	flag = ANALYSIS();
	if (flag == true) 
		cout << "语法分析完成！" << endl;
	system("pause");
	cout << "四元式：" << endl;
	OUTPUT(); //输出显示四元式
	//OUTPUTStoreSymbolNode();  //输出显示符号表
	system("pause");
	cout << "带有活跃信息的四元式" << endl;
	TargetCode();  //输出显示目标代码
	return 0;
}
