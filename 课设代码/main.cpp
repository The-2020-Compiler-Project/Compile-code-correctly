#include <iostream>
#include"head.h"
#include "Tips.h"

using namespace std;
int main()
{
	int count;
	bool flag;
	count = GetToken(); //Token����
	cout << count << endl; //���ʸ���
	system("pause");
	flag = ANALYSIS();
	if (flag == true) 
		cout << "�﷨������ɣ�" << endl;
	else cout << "�﷨��������" << endl;
	system("pause");
	cout << "��Ԫʽ��" << endl;
	OUTPUT(); //�����ʾ��Ԫʽ
	system("pause");
	cout << "���ű�" << endl;
	OUTPUTStoreSymbolNode();  //�����ʾ���ű�
	system("pause");
	cout << "Ŀ����룺" << endl;
	TargetCode();  //�����ʾĿ�����
	return 0;
}
