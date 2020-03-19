#ifndef GLOBVAR_H_INCLUDED
#define GLOBVAR_H_INCLUDED

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLineLen 1000          // �����ļ�ÿ�е���󳤶�
#define alng 100                 // ��ʶ������󳤶�
#define MaxSymLen 15             // Sym��󳤶�
#define nkw 12                   // �����ָ���
#define MaxKeyWordLen 15         // ��������󳤶�
#define kmax 10                  // ������󳤶�
#define nmax 2147483647          // �������ֵ
#define tmax 10000               // ���ű�tab�������
#define amax 30                  // �����atab�������
#define fmax 30                  // ����������ftab�������
#define smax 60000               // �ַ���������
#define lmax 7                   // �ֳ���������display������������7��

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
#define Maxcode 1000             // �м�����������
int midcodeiter = 0;             // �м��������
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
	char name[100];       // ���������������
	int addr;             // �������������ĵ�ַ��0x2ffc��ƫ����
	int type;             // const\int\char
	int isglo;            // �Ƿ�Ϊȫ�ֳ��������
}addrlist[2000];                 // ����������б�
int mi = 0;                      // ��ǰ�����м����ĵڼ���
int ismain = 0;                  // ��ǰҪ����Ŀ�����ĺ����Ƿ�Ϊmain����
int offset = 4;                  // ��ǰ$sp��λ�ã���0x2ffc��ƫ����
int funid;                       // ��ǰҪ����Ŀ�����ĺ����ں�����ftab�����
char funcname[100];              // ��ǰҪ����Ŀ�����ĺ�������
int ap=0;                        // addrlist �д洢���ܵĳ���������

char ch;                         // ���浱ǰ�ַ�
char sym[MaxSymLen];             // sy���浱ǰ����

FILE *in, *out, *lex_result, *gra_result, *sem_result,*midcode,*aim_code,*mid_opt_file;
char line[MaxLineLen];           // ������
int cc = 0;                      // ��ǰ���������е�λ��
int ll = 0;                      // �����е�ǰ����
int linenum = 0;                 // ��������Դ�ļ��ĵڼ���
int inum = 0;                    // ��ǰ����������ֵ���ַ���asciiֵ
int errpos = 0;                  // �ϴδ�ӡ�����־��λ���±�
int skipflag = 0;
int retflag;
int funtypflag;
int facerrflag = 0;

char id[100];
char idl[100];                   // ��ǰ�������ַ������ݣ����Сд��
char nowvar[200];                // ��ǰ����õ��Ľ����������ַ�
int facerflag;
int lc = 0;
int sx = 0;                      // stab��ǰ�ܳ���
int sleng = 0;                   // ��ǰ�ַ�������
int tn;
int tabnum[100];
int t = 0;
int a = 0;
int f = 0;                       //  �������ܵĺ�������
int sign,dx,prt,prb;
int charcharchar = 0;
int intintint = 0;


char key[nkw][MaxKeyWordLen] = {"char","const","else","for","if","int","main","printf","return","scanf","void","while"};
                                 // �����ּ���
enum Symbol {
           charsy,constsy,elsesy,forsy,ifsy,intsy,mainsy,printsy,returnsy,scanfsy,voidsy,whilesy,
           intcon,charcon,stringcon,
           plussign,minussign,timessign,divisionsign,
	eql, neq, gtr, geq, lss, leq,
	lparent, rparent, lbracket, rbracket, lbrace, rbrace, comma, semicolon, colon, becomes,
	ident, comments
}sy;                             // �������༯�ϣ�sy���浱ǰ�ַ�
enum Symbol ksy[nkw]={charsy,constsy,elsesy,forsy,ifsy,intsy,mainsy,printsy,returnsy,scanfsy,voidsy,whilesy};;
                                 // �����ֶ�Ӧ�ĵ�������
enum objecttyp {constant,variable, typel, funktion};
enum types {notyp, ints, chars, arrays};
char stab[smax];                 // �ַ���������
char stringtab[100][100];        // �ַ���������
int stringiter = 0;
int display[lmax];               // �ֳ���������
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
struct Tab tab[tmax];            // ���ű�
struct Ref_Tab{
           char name[100];
           int num;
};
struct funtab{
           char name[100];       // ������
           int paranum;          // ��������
           int offset;           // �˺�������һ��������ƫ����
           int rt;               // �˺����б�������
           struct Ref_Tab ref_tab[100];     // ÿ��������Ӧ�����ô�����������
           int refs;             // �����ڷ��ű��еĵ�ַ
           int sizes;            // �����б�������
           enum types type;      // ������������
}ftab[fmax];                     // ����������
struct Atab{
           enum types eltype;
           int elref, low, high, elsize, sizes;
}atab[amax];                     // �����

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

char msg[100][1000]= {                       // ������Ϣ�洢
	"ȱ��Դ�ļ�",		//0
	"�ļ�������",		//1
	"ȱ��\"",			//2
	"���ɽ��ܵ��ַ�",		//3
	"ȱ�١�'��",			//4
	"�������ű�Χ",		//5
	"��������ͻ",		//6
	"��������ʧ��",		//7
	"�Ⱥ��Ҳ��ַ��Ƿ�",		//8
	"��ʧ��;��",			//9
	"�ؼ��ִ���",		//10
	"��ʧ��ʶ��",		//11
	"��ʧ��]��",			//12
	"���ú���δ����",		//13
	"��ֵ��Ƚ��������Ͳ�һ��",		//14
	"�βθ�����ƥ��",		//15
	"δ�������",		//16
	"��ʧ��(��",			//17
	"��ʧ��)��",			//18
	"��ʧ��}��",			//19
	"�������ش���",		//20
	"���ʽȱʧ�����",		//21
	"���Ӳ��Ϸ�",		//22
	"��������ֵ",		//23
	"ȱ�١�{��",			//24
	"ȱ��main����",		//25
	"����û�г�ʼ��",		//26
	"������ǰ��",		//27
	"���ֹ���",		//28
	"�ַ������ݴ���",		//29
	"�ַ����ݴ���",		//30
	"��������ʧ��",		//31
	"��������",		//32
	"������������",		//33
	"�������������޲���ʱ������",  //34
	"�����±�Խ��",		//35
	"������main��ȱ��������",        //36
	"������main��ȱ��������",        //37
	"�з���ֵ�����޷���ֵ",          //38
	"forѭ��ȱ�ٳ�ֵ�򲽳�",         //39
	"�Ʋ⸳ֵ����д���˵��ں�",       //40
	"�����±����Ϊ����"			//41
};

enum Class{ INT,CHAR}cla;
enum Symbol sps[200]; //special symbols } {index����Ϊchar}


#endif // GLOBVAR_H_INCLUDED
