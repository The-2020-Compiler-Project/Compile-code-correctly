#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int GetToken();
bool ANALYSIS();
string BackType(int i);
int BackLocate(int i);
string BackData(int flag, int locate);
void OUTPUT();
void OUTPUTStoreSymbolNode();
typedef struct
{
	string deli;//Ëã·û t1=a*b
	string first;//a
	string second;//b
	string third;//t1
	int f;
	int s;
	int t;
}STY;
typedef struct
{
	string data;
	int  type;
	int state;
}SymbolNode;
void TargetCode();
#endif // HEAD_H_INCLUDED

