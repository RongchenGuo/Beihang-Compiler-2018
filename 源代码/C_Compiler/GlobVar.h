#ifndef GLOBVAR_H_INCLUDED
#define GLOBVAR_H_INCLUDED

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLineLen 1000          // 输入文件每行的最大长度
#define alng 100                 // 标识符的最大长度
#define MaxSymLen 15             // Sym最大长度
#define nkw 12                   // 保留字个数
#define MaxKeyWordLen 15         // 保留字最大长度
#define kmax 10                  // 整数最大长度
#define nmax 2147483647          // 整数最大值
#define tmax 10000               // 符号表tab最大容量
#define amax 30                  // 数组表atab最大容量
#define fmax 30                  // 函数索引表ftab最大容量
#define smax 60000               // 字符串常量表
#define lmax 7                   // 分程序索引表display最大容量，最多7层

#define llng 121
#define emax 322
#define emin -292
#define c2max 20
#define csmax 30
#define cmax 800
#define ermax 58
#define omax 63
#define xmax 2147483647
#define nmax 2147483647
#define lineleng 132
#define linelimit 200
#define stacksize 1450
#define Maxcode 1000             // 中间代码最大数量
int midcodeiter = 0;             // 中间代码行数
int labelcnt = 0;
int varcnt = 0;
struct Midcode
{
	char op[100] ;
	char var1[100];
	char var2[100];
	char var3[100];
}midcodelist[Maxcode],midcodeopt[Maxcode],midtemp,pushlist[Maxcode];

struct Addr
{
	char name[100];       // 常量或变量的名字
	int addr;             // 常量或变量所存的地址与0x2ffc的偏移量
	int type;             // const\int\char
	int isglo;            // 是否为全局常量或变量
}addrlist[2000];                 // 常量或变量列表
int mi = 0;                      // 当前读到中间代码的第几行
int ismain = 0;                  // 当前要生成目标代码的函数是否为main函数
int offset = 4;                  // 当前$sp的位置，与0x2ffc的偏移量
int funid;                       // 当前要生成目标代码的函数在函数表ftab的序号
char funcname[100];              // 当前要生成目标代码的函数名称
int ap=0;                        // addrlist 中存储的总的常量变量数

char ch;                         // 保存当前字符
char sym[MaxSymLen];             // sy保存当前单词

FILE *in, *out, *lex_result, *gra_result, *sem_result,*midcode,*aim_code,*mid_opt_file;
char line[MaxLineLen];           // 缓冲行
int cc = 0;                      // 当前读到缓冲行的位置
int ll = 0;                      // 缓冲行当前长度
int linenum = 0;                 // 缓冲行是源文件的第几行
int inum = 0;                    // 当前读到的整数值或字符的ascii值
int errpos = 0;                  // 上次打印出错标志的位置下标
int skipflag = 0;
int retflag;
int funtypflag;
int facerrflag = 0;

char id[100];
char idl[100];                   // 当前读到的字符串内容（变成小写）
char nowvar[200];                // 当前处理得到的结果或读到的字符
int facerflag;
int lc = 0;
int sx = 0;                      // stab当前总长度
int sleng = 0;                   // 当前字符串长度
int tn;
int tabnum[100];
int t = 0;
int a = 0;
int f = 0;                       //  程序中总的函数个数
int sign,dx,prt,prb;
int charcharchar = 0;
int intintint = 0;


char key[nkw][MaxKeyWordLen] = {"char","const","else","for","if","int","main","printf","return","scanf","void","while"};
                                 // 保留字集合
enum Symbol {
           charsy,constsy,elsesy,forsy,ifsy,intsy,mainsy,printsy,returnsy,scanfsy,voidsy,whilesy,
           intcon,charcon,stringcon,
           plussign,minussign,timessign,divisionsign,
	eql, neq, gtr, geq, lss, leq,
	lparent, rparent, lbracket, rbracket, lbrace, rbrace, comma, semicolon, colon, becomes,
	ident, comments
}sy;                             // 单词种类集合，sy保存当前字符
enum Symbol ksy[nkw]={charsy,constsy,elsesy,forsy,ifsy,intsy,mainsy,printsy,returnsy,scanfsy,voidsy,whilesy};;
                                 // 保留字对应的单词种类
enum objecttyp {constant,variable, typel, funktion};
enum types {notyp, ints, chars, arrays};
char stab[smax];                 // 字符串常量表
char stringtab[100][100];        // 字符串常量表
int stringiter = 0;
int display[lmax];               // 分程序索引表
struct Tab{;
           char name[100];
           int paranum;
           enum objecttyp obj;
           enum types type;
           int refs;
           int normal;
           int adr;
           int link;
           int isglobal;
};
struct Tab tab[tmax];            // 符号表
struct Ref_Tab{
           char name[100];
           int num;
};
struct funtab{
           char name[100];       // 函数名
           int paranum;          // 参数个数
           int offset;           // 此函数中下一个参数的偏移量
           int rt;               // 此函数中变量个数
           struct Ref_Tab ref_tab[100];     // 每个变量对应的引用次数（已排序）
           int refs;             // 函数在符号表中的地址
           int sizes;            // 函数中变量个数
           enum types type;      // 函数返回类型
}ftab[fmax];                     // 函数索引表
struct Atab{
           enum types eltype;
           int elref, low, high, elsize, sizes;
}atab[amax];                     // 数组表

struct Nodetab
{
	char name[100];
	int index;
}nodetab[100];
struct Nodelist
{
	char op[100];
	int is_leaf;
	int in_order;
	int pi;
	int left_index;
	int right_index;
	int parent_index[100];
}*nodelist[100] = { NULL };

char msg[100][1000]= {                       // 错误信息存储
	"缺少源文件",		//0
	"文件不完整",		//1
	"缺少\"",			//2
	"不可接受的字符",		//3
	"缺少“'”",			//4
	"超出符号表范围",		//5
	"变量名冲突",		//6
	"常量声明失败",		//7
	"等号右侧字符非法",		//8
	"丢失“;”",			//9
	"关键字错误",		//10
	"丢失标识符",		//11
	"丢失“]”",			//12
	"调用函数未定义",		//13
	"赋值或比较两边类型不一致",		//14
	"形参个数不匹配",		//15
	"未定义变量",		//16
	"丢失“(”",			//17
	"丢失“)”",			//18
	"丢失“}”",			//19
	"函数返回错误",		//20
	"表达式缺失或错误",		//21
	"句子不合法",		//22
	"给常数赋值",		//23
	"缺少“{”",			//24
	"缺少main函数",		//25
	"常量没有初始化",		//26
	"数字有前零",		//27
	"数字过大",		//28
	"字符串内容错误",		//29
	"字符内容错误",		//30
	"变量声明失败",		//31
	"参数错误",		//32
	"函数声明错误",		//33
	"函数定义或调用无参数时有括号",  //34
	"数组下标越界",		//35
	"主函数main后缺少左括号",        //36
	"主函数main后缺少右括号",        //37
	"有返回值函数无返回值",          //38
	"for循环缺少初值或步长",         //39
	"推测赋值符错写成了等于号",       //40
	"数组下标必须为整型"			//41
};

enum Class{ INT,CHAR}cla;
enum Symbol sps[200]; //special symbols } {index类型为char}


#endif // GLOBVAR_H_INCLUDED
