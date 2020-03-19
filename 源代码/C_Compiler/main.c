#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "GlobVar.h"

void err(int n);
void endjump();
void j2statement();
void j2rparent();
void j2rbracket();
void j2rbrace();
void j2facnext();
void j2fundec();
void j2dec();
void j2condec();
void j2sem();
void j2lbrace();

void nextch();
void sytosym(enum Symbol sy,char sym[]);
void get_a_sym();
void nextsym();

int lookup(char idl[]);
void testsemicolon();
enum types gettype();
void entering(char id[], enum objecttyp objtyp, enum types type,int isfun, int isglobal);
void variable_entering(char temp[],enum types type, int isglobal);
void array_entering(enum types type,int sizes);
void arr_variable_entering(char temp[],enum types type, int isglobal);
int const_entering(enum types type, int isglobal);
void id_entering(char name[],enum objecttyp objtyp,enum types type,int adr);
void ids_entering();
void parameterlist(enum types type);
void constdec(enum types type, int isglobal);
void variabledec(char temp[],enum types type, int isglobal);
void fun_entering(char name[],int refs,enum types type);
void functiondec(enum types type);
void proceduredec();

void statement();
void returnstatement();
void printfstatement();
void scanfstatement();
void linestatement();
void ifstatement();
void forstatement();
void whilestatement();
int factor();
int term();
int simpleexpression();
void assignment(struct Tab tabi);
void selector(struct Tab tabi);
void codition();

void inmidcode(char op[],char v1[],char v2[],char v3[]);
char * newlabel();
char * newvar();
void printmidcode();

int isnum(char var[]);
int lookup_addr(char name[]);
int lookup_func(char name[]);
void instack(char var[], int sizes);
void inaddr(int type, int tmi, int t, int glob);
void midcodetoasm();
void callop();
void GOTOop();
void BZop();
void labop();
void plusop();
void minuop();
void mulop();
void divop();
void grtop();
void geqop();
void lssop();
void leqop();
void eqlop();
void neqop();
void assop();
void sassop();
void getaop();
void scfop();
void prtop();
void fpaop();
void retop();
void paraop();
void funcop();

int lookup_ref(int j,char name[]);
void ref_entering(int j, char name[]);
void ref_count();
void sorttable(int fun);

int lookup_nodelist(int nl, char op[], int left, int right);
int lookup_nodetabname(int nt, char name[]);
void DAG();
void lookup_nodetabindex(int nt, int index);
int can_in(int x);
int all_in(int nl);








void inmidcode(char op[],char v1[],char v2[],char v3[]) {
	strcpy(midcodelist[midcodeiter].op, op);
	strcpy(midcodelist[midcodeiter].var1, v1);
	strcpy(midcodelist[midcodeiter].var2, v2);
	strcpy(midcodelist[midcodeiter].var3, v3);
	midcodeiter++;
}
char * newlabel() {
	char label[20];
	sprintf(label, "LAB%d", labelcnt++);
	return label;
}
char * newvar() {
	char var[20];
	sprintf(var,"$%d",varcnt++);
	return var;
}
void printmidcode() {
	int i = 0;
	for (i = 0; i < midcodeiter; i++) {
		/*
		if (strcmp(midcodelist[i].op, "func") == 0) {
			fprintf(midcode, "%s\t%s()\n", midcodelist[i].var1, midcodelist[i].var3);
			continue;
		}
		if (strcmp(midcodelist[i].op, "call") == 0) {
			if (strcmp(midcodelist[i].var3, "") != 0) {
				fprintf(midcode, "%s\t%s\n%s=RET\n", midcodelist[i].op, midcodelist[i].var1, midcodelist[i].var3);
				continue;
			}
		}
		if (strcmp(midcodelist[i].op, "minu") == 0) {
			fprintf(midcode, "%s=%s-%s\n", midcodelist[i].var3, midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, "plus") == 0) {
			fprintf(midcode, "%s=%s+%s\n", midcodelist[i].var3, midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, "mul") == 0) {
			fprintf(midcode, "%s=%s*%s\n", midcodelist[i].var3, midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, "div") == 0) {
			fprintf(midcode, "%s=%s/%s\n", midcodelist[i].var3, midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, "[]=") == 0) {
			fprintf(midcode, "%s[%s]=%s\n", midcodelist[i].var3, midcodelist[i].var2, midcodelist[i].var1);
			continue;
		}
		if (strcmp(midcodelist[i].op, "=") == 0) {
			fprintf(midcode, "%s=%s\n", midcodelist[i].var3, midcodelist[i].var1);
			continue;
		}
		if (strcmp(midcodelist[i].op, "geta") == 0) {
			fprintf(midcode, "%s=%s[%s]\n", midcodelist[i].var3, midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, "<") == 0) {
			fprintf(midcode, "%s<%s\n", midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, "<=") == 0) {
			fprintf(midcode, "%s<=%s\n", midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, ">") == 0) {
			fprintf(midcode, "%s>%s\n", midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, ">=") == 0) {
			fprintf(midcode, "%s>=%s\n", midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		if (strcmp(midcodelist[i].op, "==") == 0) {
			fprintf(midcode, "%s==%s\n", midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}if (strcmp(midcodelist[i].op, "!=") == 0) {
			fprintf(midcode, "%s!=%s\n", midcodelist[i].var1, midcodelist[i].var2);
			continue;
		}
		*/
		fprintf(midcode, "%s\t%s\t%s\t%s\n", midcodelist[i].op, midcodelist[i].var1, midcodelist[i].var2, midcodelist[i].var3);
	}
}









void err(int n){
           printf("in line %d, in sym %d: %s\n",linenum, cc, msg[n]);
}

void nextch() {
	if (cc == ll) {
		if(feof(in)) {
			printf("success");
			fprintf(out, "\n");
			fprintf(out, "program complete");
			ch = EOF;
			return;
		}
		/*if (errpos != 0) {
			if(skipflag){ endjump(); }
			fprintf(out, "\n");
			errpos = 0;
		}*/
		linenum++;
		ll = 0;
		cc = 0;
		while ((ch = fgetc(in)) != '\n')
		{
			if(ch!=EOF){
				ll = ll + 1;
				line[ll] = ch;
				fputc(ch,out);
			}
			else
			{
				break;
			}
		}
		fputc('\n', out);
		fflush(out);
		ll = ll + 1;
		line[ll] = ' ';
	}
	cc = cc + 1;
	ch = line[cc];
	return;
}

void sytosym(enum Symbol sy,char sym[]) {
	strcpy(sym, "");
	switch (sy)
	{
	case charsy:
		strcpy(sym, "charsy");
		break;
	case constsy:
		strcpy(sym, "constsy");
		break;
	case elsesy:
		strcpy(sym,"elsesy");
		break;
	case forsy:
		strcpy(sym, "forsy");
		break;
	case ifsy:
		strcpy(sym, "ifsy");
		break;
	case intsy:
		strcpy(sym, "intsy");
		break;
	case mainsy:
		strcpy(sym, "mainsy");
		break;
	case printsy:
		strcpy(sym, "printsy");
		break;
	case returnsy:
		strcpy(sym, "returnsy");
		break;
	case scanfsy:
		strcpy(sym, "scanfsy");
		break;
	case voidsy:
		strcpy(sym, "voidsy");
		break;
	case whilesy:
		strcpy(sym, "whilesy");
		break;
           case intcon:
		strcpy(sym, "intcon");
		break;
           case charcon:
		strcpy(sym, "charcon");
		break;
           case stringcon:
		strcpy(sym, "stringcon");
		break;
           case plussign:
		strcpy(sym, "plussign");
		break;
           case minussign:
		strcpy(sym, "minussign");
		break;
           case timessign:
		strcpy(sym, "timessign");
		break;
           case divisionsign:
		strcpy(sym, "divisionsign");
		break;
           case eql:
		strcpy(sym, "eql");
		break;
           case neq:
		strcpy(sym, "neq");
		break;
           case gtr:
		strcpy(sym, "gtr");
		break;
	case geq:
		strcpy(sym, "geq");
		break;
	case lss:
		strcpy(sym, "lss");
		break;
	case leq:
		strcpy(sym, "leq");
		break;
	case lparent:
		strcpy(sym, "lparent");
		break;
	case rparent:
		strcpy(sym, "rparent");
		break;
	case lbracket:
		strcpy(sym, "lbracket");
		break;
	case rbracket:
		strcpy(sym, "rbracket");
		break;
	case lbrace:
		strcpy(sym, "lbrace");
		break;
	case rbrace:
		strcpy(sym, "rbrace");
		break;
	case comma:
		strcpy(sym, "comma");
		break;
	case semicolon:
		strcpy(sym, "semicolon");
		break;
	case colon:
		strcpy(sym, "colon");
		break;
	case becomes:
		strcpy(sym, "becomes");
		break;
           case ident:
		strcpy(sym, "ident");
		break;
           case comments:
                      strcpy(sym, "comments");
                      break;
	default:
		strcpy(sym, "");
		break;
	}
}

void get_a_sym(){
           char temp_str[alng]="\0";
           char temp_char[100]={'\0'};
           int k = 0;
           int i;
           while(ch == ' '||ch == '\t'){
                      nextch();
           }
           if(ch==EOF) return;
           if((isalpha(ch))||(ch == '_')){
                      strcpy(temp_str,"\0");
                      k = 0;
                      memset(idl, '\0', sizeof(idl));
                      while(isalpha(ch) || isdigit(ch) || ch == '_'){
                                 temp_str[k] = tolower(ch);
                                 k++;
                                 nextch();
                      }
                      strcpy(idl, temp_str);
                      for(i=0;i<nkw;i++){
                                 if(strcmp(temp_str,key[i])==0){
                                            break;
                                 }
                      }
                      if(i<nkw){
                                 sy = ksy[i];
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     %s\n",sym, temp_str);
                      }
                      else{
                                 sy = ident;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     %s\n",sym, temp_str);
                      }
           }
           else if (isdigit(ch)){
                      inum = ch - '0';
                      k = 1;
                      while(1){
                                 nextch();
                                 if(!isdigit(ch)) break;
                                 inum = inum * 10 + ch - '0';
                                 k++;
                      }
                      if((k>kmax)||(inum>nmax)){
                                 printf("k is bigger than kmax or inum is bigger than nmax\n");
                                 err(28);
                                 inum = 0;
                                 k = 1;
                      }
                      sy = intcon;
                      sytosym(sy, sym);
                      fprintf(lex_result, "%s:     %d\n",sym, inum);
           }
           else{
                      switch(ch){
                      case '!':{
                                 nextch();
                                 if(ch == '='){
                                            sy = neq;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     '!='\n",sym);
                                            nextch();
                                 }
                                 else printf("'!' is illegal\n");
                                 break;
                      }
                      case ':':{
                                 nextch();
                                 sy = colon;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     ':'\n", sym);
                                 break;
                      }
                      case '=':{
                                 nextch();
                                 if(ch == '='){
                                            sy = eql;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     '=='\n", sym);
                                            nextch();
                                 }
                                 else{
                                            sy = becomes;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     '='\n", sym);
                                 }
                                 break;
                      }
                      case '<':{
                                 nextch();
                                 if(ch == '='){
                                            sy = leq;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     '<='\n", sym);
                                            nextch();
                                 }
                                 else{
                                            sy = lss;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     '<'\n", sym);
                                 }
                                 break;
                      }
                      case '>':{
                                 nextch();
                                 if(ch == '='){
                                            sy = geq;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     '>='\n", sym);
                                            nextch();
                                 }
                                 else{
                                            sy = gtr;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     '>'\n", sym);
                                 }
                                 break;
                      }
                      case '(':{
                                 nextch();
                                 sy = lparent;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     '('\n",sym);
                                 break;
                      }
                      case '{':{
                                 nextch();
                                 sy = lbrace;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     '{'\n",sym);
                                 break;
                      }
                      case ')':{
                                 nextch();
                                 sy = rparent;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     ')'\n",sym);
                                 break;
                      }
                      case '}':{
                                 nextch();
                                 sy = rbrace;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     '}'\n",sym);
                                 break;
                      }
                      case '[':{
                                 nextch();
                                 sy = lbracket;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     '['\n",sym);
                                 break;
                      }
                      case ']':{
                                 nextch();
                                 sy = rbracket;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     ']'\n",sym);
                                 break;
                      }
                      case ',':{
                                 nextch();
                                 sy = comma;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     ','\n",sym);
                                 break;
                      }
                      case ';':{
                                 nextch();
                                 sy = semicolon;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     ';'\n",sym);
                                 break;
                      }
                      case '+':{
                                 nextch();
                                 sy = plussign;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     '+'\n",sym);
                                 break;
                      }
                      case '-':{
                                 nextch();
                                 sy = minussign;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     '-'\n",sym);
                                 break;
                      }
                      case '*':{
                                 nextch();
                                 sy = timessign;
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     '*'\n",sym);
                                 break;
                      }
                      case '\'':{
                                 temp_char[0] = '\'';
                                 nextch();
                                 if(!isalpha(ch)&&!isdigit(ch)&&(ch!='+')&&(ch!='*')&&(ch!='_')){
                                            printf("charcon cannot be %c\n",ch);
                                            err(30);
                                            temp_char[1] = ch;
                                            stab[sx] = ch;
                                            inum = (int)ch;
                                            if(ch == '\''){
                                                       printf("missing right \'\n");
                                                       err(4);
                                                       temp_char[2] = '\'';
                                                       temp_char[3] = '\0';
                                                       sy = charcon;
                                                       sytosym(sy, sym);
                                                       fprintf(lex_result, "%s:     %s\n",sym, temp_char);
                                                       nextch();
                                                       return;
                                            }
                                 }
                                 else{
                                            temp_char[1] = ch;
                                            stab[sx] = ch;
                                            inum = (int)ch;
                                 }
                                 nextch();
                                 if(ch!='\''){
                                            printf("charcon misses rparent\n");
                                            err(4);
                                            temp_char[2] = '\'';
                                            temp_char[3] = '\0';
                                            sy = charcon;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     %s\n",sym, temp_char);
                                            nextch();
                                 }
                                 else{
                                            temp_char[2] = '\'';
                                            temp_char[3] = '\0';
                                            sy = charcon;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     %s\n", sym, temp_char);
                                            nextch();
                                 }
                                 break;
                      }
                      case '"':{
                                 i = 0;
                                 while(cc!=ll){
                                            nextch();
                                            if(ch == '"') break;
                                            if((ch<32)||(ch>126)||(ch==34)){
                                                       printf("%d cannot be in a string\n",ch);
                                                       err(29);
                                                       continue;
                                            }
                                            temp_char[i] = ch;
                                            if (sx + i == smax) {
					printf("stab over");
				}
				stab[sx + i] = ch;
				i++;
                                 }
                                 temp_char[i] = '\0';
                                 if(cc == ll){
                                            printf("missing sth in the string\n");
                                            err(2);
                                            sy = stringcon;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     %s\n",sym, temp_char);
                                 }
                                 inum = sx;
			sleng = i;
			sx = sx + i;
                                 sy = stringcon;
                                 strcpy(idl,temp_char);
                                 sytosym(sy, sym);
                                 fprintf(lex_result, "%s:     %s\n",sym, temp_char);
                                 nextch();
                                 break;
                      }
                      case '/':{
                                 nextch();
                                 if(ch == '/'){
                                            cc = ll;
                                            sy = comments;
                                            sytosym(sy, sym);
                                            nextch();
                                 }
                                 else if(ch == '*'){
                                            nextch();
                                            while(1){
                                                       if(ch == '*'){
                                                                  nextch();
                                                                  if(ch == '/'){
                                                                             sy = comments;
                                                                             sytosym(sy, sym);
                                                                             nextch();
                                                                             break;
                                                                  }
                                                                  else continue;
                                                       }
                                                       else nextch();
                                            }
                                 }
                                 else{
                                            sy = divisionsign;
                                            sytosym(sy, sym);
                                            fprintf(lex_result, "%s:     '/'\n",sym);
                                 }
                                 break;
                      }
                      default:{
                                 printf("%c is illegal\n",ch);
                                 err(3);
                                 nextch();
                                 break;
                      }
                      }
           }
           //sytosym(sy, sym);
           //fprintf(lex_result, "%s\n", sym);
}

void nextsym(){
           get_a_sym();
           while(sy == comments){
                      get_a_sym();
           }
           //sytosym(sy, sym);
           //fprintf(lex_result, "%s\n", sym);
}









void endjump() {
	while (errpos < cc) {
		fprintf(out, "-");
		errpos = errpos + 1;
	}
	skipflag = 0;
}

void j2statement() {
	skipflag = 1;
	while ( sy != ifsy && sy != lbrace && sy != scanfsy &&
		sy != printsy && sy != semicolon && sy != returnsy  && sy!=rbrace)
	{
		nextsym();
	}
	if (sy == semicolon) {
		nextsym();
	}
	if (skipflag)endjump();
}

void j2rparent() {
	skipflag = 1;
	while (sy != rparent)
	{
		nextsym();
	}
	if (skipflag)endjump();
}

void j2rbracket() {
	skipflag = 1;
	while (sy != rbracket )
	{
		nextsym();
	}
	if (skipflag)endjump();
}

void j2rbrace() {
	skipflag = 1;
	while (sy != rbrace)
	{
		nextsym();
	}
	if (skipflag)endjump();
}

void j2facnext() {
	skipflag = 1;
	while (sy != plussign && sy != minussign && sy != timessign && sy!=divisionsign && sy!=rparent && sy!=semicolon)
	{
		nextsym();
	}
	if (skipflag)endjump();
}

void j2fundec() {
	skipflag = 1;
	while (sy != voidsy && sy != intsy && sy != charsy)
	{
		nextsym();
	}
	if (skipflag)endjump();
}

void j2dec() {
	skipflag = 1;
	while ( sy!=intsy && sy!=charsy)
	{
		nextsym();
	}
	if (skipflag)endjump();
}

void j2condec() {
	skipflag = 1;
	while (sy != constsy && sy != intsy && sy != charsy)
	{
		nextsym();
	}
	if (skipflag)endjump();
}

void j2sem() {
	skipflag = 1;
	while (sy != semicolon)
	{
		nextsym();
	}
	nextsym();
	if (skipflag)endjump();
}

void j2lbrace() {
	skipflag = 1;
	while (sy != lbrace) {
		nextsym();
	}
	if (skipflag)endjump();
}









int lookup(char idl[]) {
	int i, j;
	j = t;
	i = ftab[f - 1].refs;
	strcpy(tab[0].name, idl);
	while (strcmp(tab[j].name, idl)!=0) {
		j = tab[j].link;
	}
	if (j == 0) {
		while (strcmp(tab[i].name,idl)!=0)
		{
			i = tab[i].link;
		}
		return i;
	}
	else return j;
}

void testsemicolon() {
	if (sy == semicolon) {
		nextsym();
	}
	else {
		err(9);
	}
}

enum types gettype() {
	if (sy!=intsy && sy != charsy) {
		err(7);
		return notyp;
	}
	if (sy == intsy) {
		nextsym();
		return ints;
	}
	else {
		nextsym();
		return chars;
	}
}

void entering(char id[], enum objecttyp objtyp, enum types type,int isfun, int isglobal) {
	int j = 0, l = 0;
	if (t == tmax) {
		exit(0);
	}
	strcpy(tab[0].name, id);
	if (isfun) {
		if (f) {
			j = ftab[f - 1].refs;
		}
		else {
			j = t;
		}
	}
	else {
		if (tab[t].obj == funktion) {
			j = 0;
		}else{
			j = t;
		}
	}
	l = j;
	while (strcmp(tab[j].name,id)!=0)
	{
		j = tab[j].link;
	}
	if (j != 0) {
		err(6);
	}
	else {
		t = t + 1;
		strcpy(tab[t].name, id);
		tab[t].link = l;
		tab[t].obj = objtyp;
		tab[t].type = type;
		tab[t].refs = 0;
		tab[t].adr = 0;
		tab[t].normal = 0;
		tab[t].isglobal = isglobal;
	}
}

void variable_entering(char temp[],enum types type, int isglobal) {
	entering(temp, variable, type,0, isglobal);
	if(type == ints){
                      inmidcode("int","","",temp);
	}
	else{
                      inmidcode("char","","",temp);
	}
	ftab[f - 1].sizes++;
}

void array_entering(enum types type,int sizes) {
	if (sizes > xmax) {
		err(28);
		sizes = 0;
	}
	if (a == amax) {
		exit(0);
	}
	else {
		a = a + 1;
		atab[a].eltype  = type;
		atab[a].sizes = sizes;
		if (type == ints) {
			atab[a].elsize = 4;
		}
		else {
			atab[a].elsize = 1;
		}
	}
}

void arr_variable_entering(char temp[],enum types type, int isglobal) {
	char name[100];
	char numstr[30];
	strcpy(name, temp);
	entering(temp, variable, type,0, isglobal);
	if (sy == lbracket) {
		nextsym();
		if (sy == intcon && inum > 0) {
			array_entering(type, inum);
			itoa(inum,numstr,10);
			if (type == ints) {
				inmidcode("ints", "", numstr, name);
			}
			else {
				tab[t].adr = 100;
				inmidcode("chars", "", numstr, name);
			}
			ftab[f - 1].sizes += inum;
			nextsym();
		}
		else {
			err(31);
			array_entering(type, 0);
			itoa(inum,numstr,10);
			if (type == ints) {
				inmidcode("ints", "", numstr, name);
			}
			else {
				tab[t].adr = 100;
				inmidcode("chars", "", numstr, name);
			}
			nextsym();
		}
		if (sy == rbracket) {
			nextsym();
		}
		else {
			err(12);
			j2sem();
		}
		tab[t].type = arrays;
		tab[t].refs = a;
		tab[t].isglobal = isglobal;
	}
}

int const_entering(enum types type, int isglobal) {
	// int x;
	char numstr[10];
	if (sy == ident) {
		entering(idl, constant, type,0, isglobal);
		nextsym();
		if (sy == becomes) {
			nextsym();
		}
		else
		{
			err(22);
			if (sy == eql) {
				nextsym();
			}
			else {
				j2sem();
				return -1;
			}
		}
		if (type == chars) {
			tab[t].adr = inum;
			itoa(inum,numstr,10);
			inmidcode("const", "char",numstr , tab[t].name);
			nextsym();
		}
		else {
			sign = 1;
			if (sy == plussign || sy == minussign) {
				if (sy == minussign)sign = -1;
				nextsym();
			}
			if (sy == intcon) {
				tab[t].adr = sign*inum;
				itoa(tab[t].adr, numstr, 10);
				inmidcode("const", "int", numstr, tab[t].name);
				nextsym();
			}
			else {
				err(7);
				j2sem();
				return -1;
			}
		}
	}
	else {
		err(7);
		j2sem();
		return -1;
	}
	return 0;
}

void id_entering(char name[],enum objecttyp objtyp,enum types type,int adr) {
	t = t + 1;
	strcpy(tab[t].name, name);
	tab[t].link = t - 1;
	tab[t].adr = adr;
	tab[t].normal = 1;
	tab[t].obj = objtyp;
	tab[t].paranum = 0;
	tab[t].refs = 0;
	tab[t].type = type;
}

void ids_entering() {
	id_entering("char", typel, chars, 1);
	id_entering("int", typel, ints, 1);
}

void parameterlist(enum types type) {
	if (sy == intsy) {
		type = ints;
	}
	else if (sy == charsy) {
		type = chars;
	}
	else {
		err(32);
	}
	nextsym();
	if (sy == ident) {
		entering(idl, variable, type, 0, 0);
		if (type == ints) {
			inmidcode("para", "int", "", idl);
		}
		else {
			inmidcode("para", "char", "", idl);
		}
		tab[ftab[f - 1].refs].paranum++;
		ftab[f - 1].paranum++;
		ftab[f - 1].sizes++;
		nextsym();
		if (sy == comma || sy == rparent) {
			if (sy == comma)
			{
				nextsym();
				parameterlist(type);
			}
			else {
				nextsym();
			}
		}
		else {
			err(32);
			j2lbrace();
		}
	}
	else {
		err(32);
		j2lbrace();
	}
	fprintf(gra_result,"This is a parameter list.\n");
	//printf("This is a parameter list.\n");
}

void constdec(enum types type, int isglobal) {
	// int errflag;
	if(sy != constsy){
                      printf("This is not a constant declaration\n");
	}
	while (sy == constsy) {
		nextsym();
		if ((type = gettype()) == notyp) {
			j2sem();
			continue;
		}
		if (const_entering(type, isglobal) == -1) {
			continue;
		}
		if (f != 0)ftab[f - 1].sizes++;
		while (sy == comma)
		{
			nextsym();
			if (const_entering(type, isglobal) == -1) {
				continue;
			}
			if (f != 0)ftab[f - 1].sizes++;
		}
		testsemicolon();
	}
	fprintf(gra_result, "This is a constant declaration.\n");
	// printf("This is a constant declaration.\n");
}

void variabledec(char temp[],enum types type, int isglobal) {
	char name[100];
	if (sy == semicolon || sy == comma) {
		variable_entering(temp,type, isglobal);
		while (sy == comma) {
			nextsym();
			if (sy == ident) {
				strcpy(name, idl);
				nextsym();
				if (sy == semicolon || sy == comma) {
					variable_entering(name, type, isglobal);
				}
				else if (sy == lbracket) {
					arr_variable_entering(name, type, isglobal);
				}
				else {
					variable_entering(name, type, isglobal);
				}
			}
		}
	}
	else if (sy == lbracket) {
		arr_variable_entering(temp, type, isglobal);
		while (sy == comma) {
			nextsym();
			if (sy == ident) {
				strcpy(name, idl);
				nextsym();
				if (sy == semicolon || sy == comma) {
					variable_entering(name, type, isglobal);
				}
				else if (sy == lbracket) {
					arr_variable_entering(name, type, isglobal);
				}
				else {
					variable_entering(name, type, isglobal);
				}
			}
		}
	}
	else {
		variable_entering(temp, type, isglobal);
	}
	testsemicolon();
	fprintf(gra_result,"This is a variable declaration.\n");
	// printf("This is a variable declaration.\n");
}

void fun_entering(char name[],int refs,enum types type) {
	strcpy(ftab[f].name, name);
	ftab[f].refs = refs;
	ftab[f].type = type;
	ftab[f].paranum = 0;
	ftab[f].offset = 4;
	f++;
}

void functiondec(enum types type) {
	char funname[100],name[100];
	strcpy(funname, idl);
	entering(idl, funktion, type, 1, 0);
	if (type == ints) {
		inmidcode("func", "int", "", idl);
	}
	else if(type == chars){
		inmidcode("func", "char", "", idl);
	}
	else {
		inmidcode("func","void","",idl);
	}
	fun_entering(idl, t,type);
	if(sy == lparent){
                      nextsym();
                      if (sy == rparent){
                                 err(34);
                                 tab[t].paranum = 0;
                                 nextsym();
                      }
                      else {
                                 parameterlist(type);
                      }
	}
	if (sy == lbrace)nextsym();
	else {
		err(24);
		j2condec();
	}
	if (sy == constsy) constdec(type, 0);
	while (sy == intsy || sy == charsy)
	{
		if (sy == intsy) {
			type = ints;
		}
		else {
			type = chars;
		}
		nextsym();
		if (sy == ident) {
			strcpy(name, idl);
			nextsym();
			variabledec(name,type,0);
		}
	}
	linestatement();
	if (sy == rbrace) {
		nextsym();
	}
	else err(19);
	inmidcode("end","","",funname);
	fprintf(gra_result,"This is a function declaration.\n");
	//printf("This is a function declaration.\n");
}

void proceduredec() {
	// int n;
	char temp[100];
	enum types type = notyp;
	if (sy == constsy) { constdec(type,1); }
	if (sy != voidsy && sy != intsy && sy != charsy) {
		err(22);
		j2fundec();
	}
	while (sy == intsy || sy == charsy) {
		if (sy == intsy) {
			type = ints;
		}
		else {
			type = chars;
		}
		nextsym();
		if (sy == ident) {
			strcpy(temp, idl);
			nextsym();
			if (sy == lparent) {
				retflag = 0;
				funtypflag = 1;
				functiondec(type);
				if (retflag == 0)err(20);
				break;
			}
			else if (sy == lbrace){
                                            retflag = 0;
                                            funtypflag = 1;
                                            functiondec(type);
                                            if (retflag == 0) err(20);
                                            break;
			}
			else {
				variabledec(temp,type,1);
			}
		}
		else {
			err(11);
			j2lbrace();
		}
	}
	if (sy != voidsy && sy != intsy && sy != charsy) {
		err(22);
		j2fundec();
	}
	while (sy == voidsy || sy == intsy || sy == charsy) {
		switch (sy)
		{
		case voidsy: {
			type = notyp;
			funtypflag = 0;
			break;
		}
		case intsy: {type = ints; funtypflag = 1; break; }
		case charsy: {type = chars; funtypflag = 1; break; }
		default:{err(22); j2fundec();}
		}
		nextsym();
		if (sy == ident) {
			nextsym();
			if (sy == lparent) {
				retflag = 0;
				functiondec(type);
				if (funtypflag == 1) {
					if (retflag == 0) {
						err(20);
					}
				}
			}
			else if (sy == lbrace){
                                            retflag = 0;
                                            functiondec(type);
                                            if (funtypflag == 1){
                                                       if(retflag == 0){
                                                                  err(20);
                                                       }
                                            }
			}
		}
		else if (sy == mainsy) {
			if (type != notyp) {
				err(33);
			}
			nextsym();
                                 if(sy == lparent){
                                            nextsym();
                                            if(sy == rparent){
                                                       nextsym();
                                                       if(sy == lbrace){
                                                                  functiondec(type);
                                                       }
                                                       else{
                                                                  err(37);
                                                                  j2lbrace();
                                                       }
                                            }
                                            else{
                                                       err(36);
                                                       j2lbrace();
                                            }
                                 }
			break;
		}
	}
	if (strcmp(ftab[f - 1].name, "main") != 0) {
		err(25);
	}
	fprintf(gra_result,"This is a proceduredec!!!!!\n");
	//printf("This is a proceduredec!!!!!\n");
}

void linestatement() {
	while (1) {
		if (sy == ident || sy == ifsy || sy == forsy ||
			sy == whilesy || sy == lbrace || sy == scanfsy ||
			sy == printsy || sy == semicolon || sy == returnsy) {
			statement();
		}
		else if (sy == rbrace) {
			break;
		}
		else {
			err(22);
			j2statement();
		}
	}
	fprintf(gra_result,"This is a linestatement.\n");
	//printf("This is a linestatement.\n");
}

void returnstatement() {
	char var3[200];
	int temp;
	nextsym();
	retflag = 1;
	if (sy == lparent) {
		if (funtypflag == 0)err(20);
		nextsym();
		facerrflag = 0;
		temp = simpleexpression();
		if (facerrflag == 1) {
			j2rparent();
		}
		strcpy(var3,nowvar);
		if (sy == rparent) {
                                 inmidcode("ret","","",var3);
			nextsym();
			testsemicolon();
		}
	}
	else if (sy == semicolon) {
		if (funtypflag == 1)err(38);
		inmidcode("ret","","","");
		nextsym();
	}
	else {
		err(22); j2sem();
	}
	fprintf(gra_result,"This is a returnstatement.\n");
	//printf("This is a returnstatement.\n");
}

void printfstatement() {
	char var1[200] = { '\0' }, var2[200] = { '\0' };
	int prttype = 2;
	nextsym();
	if (sy == lparent) {
		nextsym();
		if (sy == stringcon) {
                                 strcpy(stringtab[stringiter], idl);
                                 itoa(stringiter, var1, 10);
                                 stringiter++;
                                 inmidcode("prt",var1,"",(cla == CHAR)?"char":"int");
			nextsym();
			if (sy == comma) {
				nextsym();
				facerrflag = 0;
				prttype = simpleexpression();
				if (facerrflag == 1) {
					j2rparent();
				}
				strcpy(var2, nowvar);
				if (sy != rparent) {
					err(18);
					j2sem();
				}
				else {
					nextsym();
					testsemicolon();
				}
				if(prttype == 1) inmidcode("prt","",var2,"int");
				if(prttype == 0) inmidcode("prt","",var2,"char");
				//inmidcode("prt","",var2,(cla == CHAR)?"char":"int");
			}
			else if (sy == rparent) {
				nextsym();
				testsemicolon();
			}
		}
		else {
			facerrflag = 0;
			prttype = simpleexpression();
			if (facerrflag == 1) {
				j2rparent();
			}
			strcpy(var2, nowvar);
			if (sy != rparent) {
				err(18);
				j2sem();
			}
			else {
				nextsym();
				testsemicolon();
			}
			if(prttype == 1) inmidcode("prt","",var2,"int");
			if(prttype == 0) inmidcode("prt","",var2,"char");
			//inmidcode("prt","",var2,(cla == CHAR)?"char":"int");
		}
		//inmidcode("prt",var1,var2,(cla == CHAR)?"char":"int");
		fprintf(gra_result, "This is a printfstatement.\n");
		//printf("This is a printfstatement.\n");
	}
}

void scanfstatement() {
	int i;
	nextsym();
	if (sy == lparent) {
		nextsym();
		if (sy != ident) {
			err(11);
			j2sem();
			return;
		}
		i = lookup(idl);
		if (i != 0) {
			if (tab[i].obj != variable) {
				err(22);
				j2sem();
				return;
			}
			inmidcode("scf","","",idl);
			nextsym();
		}
		else {
			err(16);
			j2sem();
			return;
		}
		while (sy == comma)
		{
			nextsym();
			if (sy != ident) {
				err(11);
				j2sem();
				return;
			}
			i = lookup(idl);
			if (i != 0) {
				if (tab[i].obj != variable) {
					err(22);
					j2sem();
					return;
				}
				inmidcode("scf", "", "", idl);
				nextsym();
			}
			else {
				err(16);
				j2sem();
				return;
			}
		}
		if (sy == rparent) {
			nextsym();
			testsemicolon();
		}
		else {
			err(18);
			j2sem();
			return;
		}
		fprintf(gra_result,"This is a scanfstatement.\n");
		//printf("This is a scanfstatement.\n");
	}
	else {
		err(17);
		j2sem();
		return;
	}
}

int simpleexpression() {
	enum Symbol op;
	char var1[200], var2[200], var3[200];
	int returnvalue = 2;
	int temp;
	if (sy == plussign || sy == minussign) {
		op = sy;
		nextsym();
		temp = term();
		if (op == plussign) {
			strcpy(var3, nowvar);
		}
		else {
                                 strcpy(var2, nowvar);
                                 strcpy(var3, newvar());
			ftab[f - 1].sizes++;
			inmidcode("minu","0",var2,var3);
		}
		returnvalue = 1;
	}
	else {
		returnvalue = term();
		strcpy(var3, nowvar);
	}
	while (sy == plussign || sy == minussign) {
                      strcpy(var1, var3);
		op = sy;
		nextsym();
		temp = term();
		strcpy(var2, nowvar);
		strcpy(var3, newvar());
		ftab[f - 1].sizes++;
		if (op == plussign) {
			inmidcode("plus",var1,var2,var3);
		}
		else {
			inmidcode("minu",var1,var2,var3);
		}
		returnvalue = 1;
	}
	strcpy(nowvar, var3);
	fprintf(gra_result, "This is a simpleexpression.\n");
	//print("simpleexpression return value: %d\n",returnvalue);
	return returnvalue;
	//printf("This is a simpleexpression.\n");
}

int term() {
	char var1[200], var2[200], var3[200];
	enum Symbol op;
	int returnvalue = 2;
	int temp;
	returnvalue = factor();
	strcpy(var3, nowvar);
	while (sy == timessign || sy == divisionsign)
	{
	           strcpy(var1,var3);
		op = sy;
		nextsym();
		returnvalue = 1;
		temp = factor();
		if (op == timessign) {
                                 strcpy(var2, nowvar);
			strcpy(var3, newvar());
			ftab[f - 1].sizes++;
                                 inmidcode("mul",var1,var2,var3);
		}
		else {
		           strcpy(var2, nowvar);
			strcpy(var3, newvar());
			ftab[f - 1].sizes++;
			inmidcode("div",var1,var2,var3);
		}
		intintint = 1;
	}
	strcpy(nowvar, var3);
	fprintf(gra_result,"This is a term.\n");
	//print("term return value: %d\n",returnvalue);
	return returnvalue;
	//printf("This is a term.\n");
}

int factor() {
	int i, j,sign,returnvalue,temp;
	char paravar[200][200];
	int paracon = 0,k;
	char var3[30],t[30];
	returnvalue = 2;
	if (sy == plussign || sy == minussign || sy == ident || sy == charcon || sy == intcon || sy == lparent)
	{
		if (sy == ident)
		{
			i = lookup(idl);
			if (i != 0) {
				nextsym();
				switch (tab[i].obj) {
				case constant: {
				           strcpy(nowvar, tab[i].name);
				           if (tab[i].type == ints) returnvalue = 1;
				           if (tab[i].type == chars) returnvalue = 1;
					break;
				}
				case variable: {
					if (sy == lbracket)
					{
						if (tab[i].type != arrays) {
							err(22);
							facerrflag = 1;
							return returnvalue;
						}
						if (tab[i].adr == 100) returnvalue = 0;
						else returnvalue = 1;
						selector(tab[i]);
						if (isnum(nowvar)) {
							if (tab[i].type == arrays && atab[tab[i].refs].sizes <= atoi(nowvar)) {
								err(35);
							}
						}
						strcpy(t, nowvar);
						strcpy(nowvar, newvar());
						ftab[f - 1].sizes++;
						inmidcode("geta", tab[i].name, t, nowvar);
						intintint = 1;
					}
					else {
                                                                  if (tab[i].type == ints) returnvalue = 1;
                                                                  if (tab[i].type == chars) returnvalue = 0;
                                                                  if (tab[i].isglobal == 1){
                                                                             strcpy(nowvar, newvar());
                                                                             strcpy(var3, tab[i].name);
                                                                             inmidcode("=",var3, "", nowvar);
                                                                             ftab[f - 1].sizes++;
                                                                             //strcpy(nowvar,tab[i].name);
                                                                  }
                                                                  else{
                                                                             strcpy(nowvar,tab[i].name);
                                                                  }
					}
					break;
				}
				case funktion: {
					if (tab[i].type == notyp) {
						returnvalue = 2;
						err(20);
					}
					if (tab[i].type == ints) returnvalue = 1;
                                                       if (tab[i].type == chars) returnvalue = 0;
					if (sy == lparent) {
						nextsym();
						if (tab[i].paranum == 0) {
							if (sy == rparent) {
								err(34);
								strcpy(var3, newvar());
								ftab[f - 1].sizes++;
								inmidcode("call", tab[i].name, "", var3);
								strcpy(nowvar, var3);
								nextsym();
							}
							else { err(18); facerrflag = 1; return returnvalue;
							}
						}
						else {
							for (j = 1; j < tab[i].paranum; j++) {
								facerrflag = 0;
								temp = simpleexpression();
								if (facerrflag == 1) {
									j2rparent();
									break;
								}
								strcpy(paravar[paracon++], nowvar);
								if (sy != comma) {
									err(15); j2rparent(); break;
								}
								nextsym();
							}
							if (j == tab[i].paranum) {
								facerrflag = 0;
								temp = simpleexpression();
								if (facerrflag == 1) {
									j2rparent();
								}
								strcpy(paravar[paracon++], nowvar);
							}
							for (k = 0; k < paracon; k++) {
								inmidcode("PUSH", "", "", paravar[k]);
							}
							if (sy == rparent) {
                                                                                        strcpy(var3, newvar());
								ftab[f - 1].sizes++;
								inmidcode("call", tab[i].name,"",var3);
								strcpy(nowvar, var3);
								nextsym();
							}
							else { err(18); facerrflag = 1; return returnvalue;
	 						}
						}
					}
					else{
						if (tab[i].paranum != 0) {
							err(36);
							j2sem();
						}
						else{
                                                                             strcpy(var3, newvar());
                                                                             ftab[f - 1].sizes++;
                                                                             inmidcode("call", tab[i].name, "", var3);
                                                                             strcpy(nowvar, var3);
						}
					}
					break;
				}
				case typel:{
				           intintint = 1;
						   returnvalue = 2;
				           break;
                                            }
				}
			}
			else {
				err(16);
				facerrflag = 1;
				return returnvalue;
			}
		}
		else if (sy == plussign || sy == minussign || sy == charcon || sy == intcon)
		{
			sign = 1;
			if (sy == charcon)
			{
			           sprintf(nowvar, "%d", inum);
				cla = CHAR;
				charcharchar = 1;
				returnvalue = 0;
			}
			else if (sy == plussign) {
				nextsym();
				intintint = 1;
				returnvalue = 1;
			}
			else if (sy == minussign) {
				sign = -1;
				nextsym();
				intintint = 1;
				returnvalue = 1;
			}
			if (sy == intcon) {
                                            sprintf(nowvar, "%d", sign*inum);
				cla = INT;
				intintint = 1;
				returnvalue = 1;
			}
			nextsym();
		}
		else if (sy == lparent)
		{
			nextsym();
			facerrflag = 0;
			temp = simpleexpression();
			if (facerrflag == 1) {
				j2rparent();
			}
			intintint = 1;
			if (sy == rparent)
				nextsym();
			else { err(18); facerrflag = 1; return returnvalue; }
			returnvalue = 1;
		}
	}
	else { err(22); facerrflag = 1; return returnvalue;
	}
	fprintf(gra_result,"This is a factor.\n");
	return returnvalue;
	//printf("This is a factor.\n");
}

void selector(struct Tab tabi) {
	// char t[30];
	int temp;
	nextsym();
	facerrflag = 0;
	temp = simpleexpression();
	if (temp != 1){
		err(41);
	}
	if (facerrflag == 1) {
		j2rbracket();
	}
	if (sy == rbracket) {
		nextsym();
	}
	else
		err(12);
           fprintf(gra_result, "This is a selector.\n");
           //printf("This is a selector.\n");
}

void condition() {
	char var1[200], var2[200], var3[200];
	enum Symbol op;
	int lefttype = 2;
	int righttype = 2;
	facerrflag = 0;
	lefttype = simpleexpression();
	if (facerrflag == 1) {
		j2rparent();
	}
	strcpy(var1, nowvar);
	if (sy == eql || sy == neq || sy == geq || sy == gtr || sy == lss || sy == leq) {
		op = sy;
		nextsym();
		facerrflag = 0;
		righttype = simpleexpression();
		if (lefttype != righttype) err(14);
		if (facerrflag == 1) {
			j2rparent();
		}
		strcpy(var2, nowvar);
		strcpy(var3, newvar());
		ftab[f - 1].sizes++;
		if (op == lss) {
			inmidcode("<",var1,var2,var3);
		}
		else if (op == leq) {
			inmidcode("<=", var1, var2, var3);
		}
		else if (op == gtr) {
			inmidcode(">", var1, var2, var3);
		}
		else if (op == geq) {
			inmidcode(">=", var1, var2, var3);
		}
		else if (op == neq) {
			inmidcode("!=", var1, var2, var3);
		}
		else if (op == eql) {
			inmidcode("==", var1, var2, var3);
		}
	}
	else {
                      strcpy(var2, "0");
		strcpy(var3, newvar());
		ftab[f - 1].sizes++;
		inmidcode("!=",var1,var2,var3);
	}
	strcpy(nowvar, var3);
	fprintf(gra_result,"This is a condition.\n");
	//printf("This is a condition.\n");
}

void assignment(struct Tab tabi) {
	char var1[200],var2[200], var3[200];
	int lefttype = 2;
	int righttype = 2;
	strcpy(var3,tabi.name);
	strcpy(var2,"");
	if (sy == lbracket) {
                      if (tabi.adr == 100) lefttype = 0;
                      else lefttype = 1;
		selector(tabi);
		strcpy(var2, nowvar);
		if (isnum(nowvar)) {
			if (tabi.type == arrays && atab[tabi.refs].sizes <= atoi(nowvar)) {
				err(35);
			}
		}
	}
	else{
                      if(tabi.type == ints) lefttype = 1;
                      if(tabi.type == chars) lefttype = 0;
	}
	if (sy == becomes)
		nextsym();
	else {
		err(22);
		if (sy == eql) {
			nextsym();
		}
		else {
			j2sem();
		}
	}
	facerrflag = 0;
	righttype = simpleexpression();
	strcpy(var1, nowvar);
	//printf("%d,%d\n",lefttype,righttype);
	if(lefttype!=righttype){
	           //printf("%d,%d\n",lefttype,righttype);
                      err(14);
	}
	//if (tabi.type == chars && intintint == 1) err(14);
	//if (tabi.type == ints && charcharchar == 1 && intintint == 0) err(14);
	//if (tabi.type == arrays && tabi.adr == 100 && intintint == 1) err(14);
	//if (tabi.type == arrays && tabi.adr != 100 && charcharchar == 1 && intintint == 0) err(14);

	if (strcmp(var2, "") != 0) {
		inmidcode("[]=", var1, var2, var3);
	}
	else {
		inmidcode("=", var1, "", var3);
	}
	if (facerrflag == 1) {
		j2sem();
	}
	else {
		testsemicolon();
	}
	fprintf(gra_result, "This is an assignment.\n");
	//printf("This is an assignment.\n");
}

void ifstatement() {
	char label1[20],label2[20],result[200];
	strcpy(label1, newlabel());
	strcpy(label2, newlabel());
	nextsym();
	if (sy == lparent) {
		nextsym();
		condition();
		strcpy(result,nowvar);
		inmidcode("BZ", "  ", "  ", label1);
		if (sy == rparent) {
			nextsym();
			statement();
			inmidcode("GOTO", "  ", "  ", label2);
			inmidcode("lab:", "", "", label1);
			if (sy == elsesy){
				nextsym();
				statement();
			}
			inmidcode("lab:", "", "", label2);
		}
		else {
			err(18); j2sem();
		}
	}
	else { err(17); j2sem(); }
	fprintf(gra_result,"This is a ifstatement.\n");
	//printf("This is a ifstatement.\n");
}

void statement() {
	int i,j;
	char paravar[200][200];
	int paracon=0,t,temp;
	if (sy == ident) {}
	switch (sy) {
	case ident: {
		i = lookup(idl);
		if (i != 0) {
			nextsym();
			switch (tab[i].obj) {
			case constant:case typel: err(22); j2sem(); break;
			case variable:assignment(tab[i]); break;
			case funktion: {
				if (sy == lparent) {
					nextsym();
					if (tab[i].paranum == 0) {
						if (sy == rparent) {
							err(34);
							inmidcode("call", tab[i].name, "", "");
							nextsym();
							testsemicolon();
						}
						else { err(18); j2sem(); }
					}
					else {
						for (j = 1; j < tab[i].paranum; j++) {
							facerrflag = 0;
							temp = simpleexpression();
							if (facerrflag == 1) {
								j2rparent();
								break;
							}
							strcpy(paravar[paracon++], nowvar);
							if (sy != comma) {
								err(15); j2rparent(); break;
							}
							else {
								nextsym();
							}
						}
						if (j == tab[i].paranum) {
							facerrflag = 0;
							temp = simpleexpression();
							if (facerrflag == 1) {
								j2rparent();
							}
							strcpy(paravar[paracon++], nowvar);
						}
						for (t = 0; t < paracon; t++) {
							inmidcode("PUSH", "", "", paravar[t]);
						}
						if (sy == rparent) {
                                                                             inmidcode("call", tab[i].name, "", "");
							nextsym();
							testsemicolon();
						}
						else { err(18); j2sem(); }
					}
				}
				else{
					if (tab[i].paranum != 0){
						err(36);
						j2sem();
					}
					inmidcode("call", tab[i].name, "", "");
					testsemicolon();
				}
				break;
			}
			}
		}
		else {
			err(16);
			j2sem();
		}
		break;
	}
	case ifsy: ifstatement(); break;
	case forsy: forstatement(); break;
	case whilesy: whilestatement(); break;
	case lbrace: {
		nextsym();
		linestatement();
		if (sy != rbrace) {
			err(19);
		}
		else {
			nextsym();
		}
		break;
	}
	case scanfsy: scanfstatement(); break;
	case printsy: printfstatement(); break;
	case semicolon: {
		nextsym();
		break;
	}
	case returnsy: returnstatement(); break;
	default: {
		err(22);
		j2sem();
		break;
	}
	}
	fprintf(gra_result,"This is a statement.\n");
	//printf("This is a statement.\n");
}

void whilestatement() {
	char label1[20],label2[20],result[200];
	strcpy(label1, newlabel());
	strcpy(label2, newlabel());
	inmidcode("lab:","","",label1);
	nextsym();
	if(sy != lparent){
		err(17);
	}
	else{
		nextsym();
	}
	condition();
	strcpy(result, nowvar);
	inmidcode("BZ", "  ", "  ", label2);
	if(sy != rparent){
		err(18);
	}
	else{
		nextsym();
	}
	statement();
	inmidcode("GOTO", "  ", "  ", label1);
	inmidcode("lab:","","",label2);
	fprintf(gra_result,"This is a whilestatement.\n");
	//printf("This is a whilestatement.\n");
}

void forstatement(){
           int i = 0;
           int j = 0;
		   int lefttype = 2;
		   int righttype = 2;
           char label1[20],label2[20],label3[20],label4[20];
           char var1[200],var2[200],var3[200],var4[200];
           enum Symbol op;
	strcpy(label1, newlabel());
	strcpy(label2, newlabel());
	strcpy(label3, newlabel());
	strcpy(label4, newlabel());
           nextsym();
           if(sy != lparent){
		err(17);
	}
	else{
		nextsym();
	}
	if(sy != ident){
                      err(39);
	}
	else{
                      i = lookup(idl);
                      if (i != 0) {
                                 strcpy(var3,tab[i].name);
                                 if(tab[i].type == ints) lefttype = 1;
                                 if(tab[i].type == chars) lefttype = 0;
                                 switch (tab[i].obj) {
                                 case variable: {
                                            nextsym();
                                            if(sy == eql){
                                                       err(40);
                                                       nextsym();
                                                       facerrflag = 0;
                                                       righttype = simpleexpression();
													   if(lefttype != righttype) err(14);
                                                       strcpy(var1, nowvar);
                                                       inmidcode("=", var1, "", var3);
                                                       if (facerrflag == 1) {
                                                                  j2sem();
                                                       }
                                                       else {
                                                                  testsemicolon();
                                                       }
                                            }
                                            else if(sy == becomes){
                                                       nextsym();
                                                       facerrflag = 0;
                                                       righttype = simpleexpression();
													   if(lefttype != righttype) err(14);
                                                       strcpy(var1, nowvar);
                                                       inmidcode("=", var1, "", var3);
                                                       if (facerrflag == 1) {
                                                                  j2sem();
                                                       }
                                                       else {
                                                                  testsemicolon();
                                                       }
                                            }
                                            else{
                                                       err(22);
                                                       j2sem();
                                            }
                                            break;
                                 }
                                 default:{
                                            err(22);
                                            j2sem();
                                 }
                                 }
                      }
                      else{
                                 err(16);
                                 j2sem();
                      }
	}
	inmidcode("GOTO","","",label4);
	inmidcode("lab:", "", "", label1);
	condition();
	testsemicolon();
	inmidcode("BZ", "", "", label2);
	inmidcode("GOTO","","",label4);
	inmidcode("lab:", "", "", label3);
	if(sy != ident){
                      err(39);
	}
	else{
                      i = lookup(idl);
                      if (i != 0) {
                                 strcpy(var4,tab[i].name);
                                 switch (tab[i].obj) {
                                 case variable: {
                                            nextsym();
                                            if(sy == eql){
                                                       err(40);
                                                       nextsym();
                                                       if(sy == ident){
                                                                  j = lookup(idl);
                                                                  if (j!=0){
                                                                             nextsym();
                                                                             switch(tab[j].obj){
                                                                             case variable:{
                                                                                        strcpy(nowvar,tab[j].name);
                                                                                        break;
                                                                             }
                                                                             default:{break;}
                                                                             }
                                                                  }
                                                                  else{
                                                                             err(16);
                                                                             facerrflag = 1;
                                                                             return;
                                                                  }
                                                                  strcpy(var1,nowvar);
                                                                  if(sy == plussign||sy == minussign){
                                                                             op = sy;
                                                                             nextsym();
                                                                             if(sy == intcon){
                                                                                        sprintf(nowvar, "%d", inum);
                                                                                        cla = INT;
                                                                                        strcpy(var2, nowvar);
                                                                                        strcpy(var3, newvar());
                                                                                        ftab[f - 1].sizes++;
                                                                                        if (op == plussign) {
                                                                                                   inmidcode("plus",var1,var2,var3);
                                                                                        }
                                                                                        else {
                                                                                                   inmidcode("minu",var1,var2,var3);
                                                                                        }
                                                                                        inmidcode("=", var3, "", var4);
                                                                                        inmidcode("GOTO","","",label1);
                                                                                        nextsym();
                                                                             }
                                                                             else{err(22); j2rparent();}
                                                                  }
                                                       }
                                                       else{err(22); j2rparent();}
                                            }
                                            else if(sy == becomes){
                                                       nextsym();
                                                       if(sy == ident){
                                                                  j = lookup(idl);
                                                                  if (j!=0){
                                                                             nextsym();
                                                                             switch(tab[j].obj){
                                                                             case variable:{
                                                                                        strcpy(nowvar,tab[j].name);
                                                                                        break;
                                                                             }
                                                                             default:{break;}
                                                                             }
                                                                  }
                                                                  else{
                                                                             err(16);
                                                                             facerrflag = 1;
                                                                             return;
                                                                  }
                                                                  strcpy(var1,nowvar);
                                                                  if(sy == plussign||sy == minussign){
                                                                             op = sy;
                                                                             nextsym();
                                                                             if(sy == intcon){
                                                                                        sprintf(nowvar, "%d", inum);
                                                                                        cla = INT;
                                                                                        strcpy(var2, nowvar);
                                                                                        strcpy(var3, newvar());
                                                                                        ftab[f - 1].sizes++;
                                                                                        if (op == plussign) {
                                                                                                   inmidcode("plus",var1,var2,var3);
                                                                                        }
                                                                                        else {
                                                                                                   inmidcode("minu",var1,var2,var3);
                                                                                        }
                                                                                        inmidcode("=", var3, "", var4);
                                                                                        inmidcode("GOTO","","",label1);
                                                                                        nextsym();
                                                                             }
                                                                             else{err(22); j2rparent();}
                                                                  }
                                                       }
                                                       else{err(22); j2rparent();}
                                            }
                                            else{
                                                       err(22);
                                                       j2rparent();
                                            }
                                            break;
                                 }
                                 default:{
                                            err(22);
                                            j2sem();
                                 }
                                 }
                      }
                      else{
                                 err(16);
                                 j2rparent();
                      }
	}
	if(sy != rparent){
                      err(18);
	}
	else{
                      nextsym();
	}
	inmidcode("lab:", "", "", label4);
	statement();
	inmidcode("GOTO","","",label3);
	inmidcode("lab:", "", "", label2);
	fprintf(gra_result,"This is a forstatement.\n");
	//printf("This is a forstatement.\n");
}









int isnum(char var[]) {
	if ((var[0] >= '0' && var[0] <= '9') || var[0] == '-' || var[0] == '+') {
		return 1;
	}
	return 0;
}

int lookup_addr(char name[]) {
	int i;
	for (i = ap-1; i >=0; i--) {
		if (strcmp(addrlist[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}

int lookup_func(char name[]) {
	int i;
	for (i = 0; i < f; i++) {
		if (strcmp(ftab[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}
void instack(char var[],int sizes) {
	if (sizes == 1) {
		fprintf(aim_code, "li $t0 %d\n", atoi(var));
		fprintf(aim_code, "sw $t0 0x%x($sp)\n",offset);
	}
	offset = offset + 4*sizes;
}

void inaddr(int type,int tmi,int t,int glob) {
	if (tmi == 1) {
		strcpy(addrlist[ap].name, midcodelist[mi].var3);
	}
	else {
		strcpy(addrlist[ap].name, midcodelist[tmi].var3);
	}

	addrlist[ap].addr = offset;
	addrlist[ap].isglo = glob;
	addrlist[ap].type = type;

	ap++;
}
void midcodetoasm() {
	int tmi,sizes,i;
	mi = ap = sizes = 0;
	tmi = mi;
	fprintf(aim_code, ".data\n");
	for(i = 0; i<stringiter; i++){
                      fprintf(aim_code, "string%d: .asciiz \"%s\"\n", i, stringtab[i]);
	}
           fprintf(aim_code, ".text\n");
	while (mi < midcodeiter)
	{
		while (strcmp(midcodelist[tmi].op, "const") == 0)
		{
			sizes++;
			tmi++;
		}
		while (strcmp(midcodelist[tmi].op, "int") == 0 ||
			strcmp(midcodelist[tmi].op, "char") == 0 ||
			strcmp(midcodelist[tmi].op, "ints") == 0 ||
			strcmp(midcodelist[tmi].op, "chars") == 0
			) {
			if (strcmp(midcodelist[tmi].var2, "") == 0) {
				sizes++;
			}
			else {
				sizes = sizes + atoi(midcodelist[tmi].var2);
			}
			tmi++;
		}
		fprintf(aim_code, "subi $sp $sp %d\n", 4 * sizes);
		fprintf(aim_code, "addi $t8 $sp 0\n");
		while (strcmp(midcodelist[mi].op,"const") == 0)
		{

			if (strcmp(midcodelist[mi].var1, "int") == 0 || strcmp(midcodelist[mi].var1, "ints") == 0) {
				inaddr(INT,1,0,1);
			}
			else {
				inaddr(CHAR,1,0,1);
			}
			instack(midcodelist[mi].var2, 1);
			mi++;
		}
		while (strcmp(midcodelist[mi].op,"int") == 0 ||
			strcmp(midcodelist[mi].op,"char") == 0 ||
			strcmp(midcodelist[mi].op, "ints") == 0 ||
			strcmp(midcodelist[mi].op, "chars") == 0){

			if (strcmp(midcodelist[mi].op, "int") == 0 || strcmp(midcodelist[mi].op, "ints")==0) {
				inaddr(INT,1,0,1);
			}
			else {
				inaddr(CHAR,1,0,1);
			}
			if (strcmp(midcodelist[mi].var2, "") == 0) {
				offset += 4;
			}
			else instack("0", atoi(midcodelist[mi].var2));
			mi++;
		}

		fprintf(aim_code,"j main\n");

		while (strcmp(midcodelist[mi].op,"func") == 0){
			fprintf(aim_code, "%s:",midcodelist[mi].var3);
			funid = lookup_func(midcodelist[mi].var3);
			strcpy(funcname, midcodelist[mi].var3);
			if (strcmp(funcname, "main") == 0) {
				ismain = 1;
			}
			mi++;
			funcop();

		}

	}

}

void funcop() {
	int tmi,i,tap,n;
	offset = 4;
	tmi = mi;
	tap = ap;
	i = lookup_func(funcname);
	fprintf(aim_code, "subi $sp $sp 40\nsw $ra 4($sp)\nsw $t9 8($sp)\n");
	fprintf(aim_code, "sw $s0 12($sp)\n");
	fprintf(aim_code, "sw $s1 16($sp)\n");
	fprintf(aim_code, "sw $s2 20($sp)\n");
	fprintf(aim_code, "sw $s3 24($sp)\n");
	fprintf(aim_code, "sw $s4 28($sp)\n");
	fprintf(aim_code, "sw $s5 32($sp)\n");
	fprintf(aim_code, "sw $s6 36($sp)\n");
	fprintf(aim_code, "sw $s7 40($sp)\n");
	fprintf(aim_code, "addi $t9 $sp 0\n");
	fprintf(aim_code, "subi $sp $sp %d\n", 4 * ftab[i].sizes);
	if (strcmp(midcodelist[mi].op, "para") == 0) paraop();
	while (strcmp(midcodelist[mi].op, "const") == 0)
	{

		if (strcmp(midcodelist[mi].var1, "int") == 0 || strcmp(midcodelist[mi].var1, "ints") == 0) {
			inaddr(INT, 1, 0, 0);
		}
		else {
			inaddr(CHAR, 1, 0, 0);
		}
		if ((n=lookup_ref(funid, midcodelist[mi].var3)) == -1) {
			instack(midcodelist[mi].var2, 1);
		}
		else {
			offset += 4;
			fprintf(aim_code, "li $s%d %d\n",n, atoi(midcodelist[mi].var2));
		}
		mi++;
	}
	while (strcmp(midcodelist[mi].op, "int") == 0 ||
		strcmp(midcodelist[mi].op, "char") == 0 ||
		strcmp(midcodelist[mi].op, "ints") == 0 ||
		strcmp(midcodelist[mi].op, "chars") == 0) {

		if (strcmp(midcodelist[mi].op, "int") == 0 || strcmp(midcodelist[mi].op, "ints") == 0) {
			inaddr(INT, 1, 0, 0);
		}
		else {
			inaddr(CHAR, 1, 0, 0);
		}
		if (strcmp(midcodelist[mi].var2, "") == 0) {
			offset += 4;
		}
		else {
			instack("0", atoi(midcodelist[mi].var2));
		}
		mi++;
	}
	while (strcmp(midcodelist[tmi].op, "end") != 0) {

		if (midcodelist[tmi].var1[0] == '$' && lookup_addr(midcodelist[tmi].var1) == -1) {

			inaddr(INT, tmi,0,0);
			offset += 4;
		}
		if (midcodelist[tmi].var2[0] == '$' && lookup_addr(midcodelist[tmi].var2) == -1) {

			inaddr(INT,tmi,0,0);
			offset += 4;
		}
		if (midcodelist[tmi].var3[0] == '$' && lookup_addr(midcodelist[tmi].var3) == -1) {

			if (strcmp(midcodelist[tmi].op, "call") == 0) {
                                            if(ftab[lookup_func(midcodelist[tmi].var1)].type==ints){
                                                       inaddr(INT,tmi,0,0);
                                            }
                                            else if(ftab[lookup_func(midcodelist[tmi].var1)].type==chars){
                                                       inaddr(CHAR,tmi,0,0);
                                            }
			}
			else if(strcmp(midcodelist[tmi].op, "geta") == 0){
				inaddr(addrlist[lookup_addr(midcodelist[tmi].var1)].type,tmi,0,0);
			}
			else {
				inaddr(INT, tmi,0,0);
			}
			offset += 4;
		}
		tmi++;
	}



	while (strcmp(midcodelist[mi].op, "end") != 0) {

		if (strcmp(midcodelist[mi].op, "plus") == 0) plusop();
		if (strcmp(midcodelist[mi].op, "minu") == 0) minuop();
		if (strcmp(midcodelist[mi].op, "mul") == 0) mulop();
		if (strcmp(midcodelist[mi].op, "div") == 0) divop();
		if (strcmp(midcodelist[mi].op, ">") == 0) grtop();
		if (strcmp(midcodelist[mi].op, ">=") == 0) geqop();
		if (strcmp(midcodelist[mi].op, "<") == 0) lssop();
		if (strcmp(midcodelist[mi].op, "<=") == 0) leqop();
		if (strcmp(midcodelist[mi].op, "!=") == 0) neqop();
		if (strcmp(midcodelist[mi].op, "==") == 0) eqlop();
		if (strcmp(midcodelist[mi].op, "=") == 0) assop();
		if (strcmp(midcodelist[mi].op, "[]=") == 0) sassop();
		if (strcmp(midcodelist[mi].op, "geta") == 0) getaop();
		if (strcmp(midcodelist[mi].op, "lab:") == 0) labop();
		if (strcmp(midcodelist[mi].op, "scf") == 0) scfop();
		if (strcmp(midcodelist[mi].op, "prt") == 0) prtop();
		if (strcmp(midcodelist[mi].op, "BZ") == 0) BZop();
		if (strcmp(midcodelist[mi].op, "GOTO") == 0) GOTOop();
		if (strcmp(midcodelist[mi].op, "PUSH") == 0) fpaop();
		if (strcmp(midcodelist[mi].op, "call") == 0) callop();
		if (strcmp(midcodelist[mi].op, "ret") == 0) retop();

		mi++;
	}
	fprintf(aim_code, "fend_%s:\n", funcname);
	fprintf(aim_code, "addi $sp $t9 0\n");
	fprintf(aim_code, "lw $s0 12($sp)\n");
	fprintf(aim_code, "lw $s1 16($sp)\n");
	fprintf(aim_code, "lw $s2 20($sp)\n");
	fprintf(aim_code, "lw $s3 24($sp)\n");
	fprintf(aim_code, "lw $s4 28($sp)\n");
	fprintf(aim_code, "lw $s5 32($sp)\n");
	fprintf(aim_code, "lw $s6 36($sp)\n");
	fprintf(aim_code, "lw $s7 40($sp)\n");
	fprintf(aim_code, "lw $ra 4($sp)\nlw $t9 8($sp)\naddi $sp $sp 40\n");
	if (ismain) {
		fprintf(aim_code, "li $v0 10\nsyscall\n");
	}
	else {
		fprintf(aim_code, "jr $ra\n");
	};
	mi++;
	ap = tap;
}
void callop() {
	int i=0,j=0,n=-1;
	fprintf(aim_code, "jal %s\n", midcodelist[mi].var1);
	if (strcmp(midcodelist[mi].var3, "") != 0) {
		if ((n=lookup_ref(funid, midcodelist[mi].var3)) != -1) {
			fprintf(aim_code, "addi $s%d $v0 0\n", n);
		}
		else {
			i = lookup_addr(midcodelist[mi].var3);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "sw $v0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "sw $v0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	j = lookup_func(midcodelist[mi].var1);
	if (j != -1) {
		ftab[j].offset = 4;
	}
}
void GOTOop() {
	fprintf(aim_code, "j %s\n", midcodelist[mi].var3);
}
void BZop() {
	fprintf(aim_code, "bne $t0 1 %s\n", midcodelist[mi].var3);
}
void labop() {
	fprintf(aim_code, "%s:\n", midcodelist[mi].var3);
}

void plusop() {
	int i=0, j=0, k=0,n1=-1,n2=-1,n3=-1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
		k = lookup_addr(midcodelist[mi].var3);
		if (n1 == -1 && n2 == -1) {
			fprintf(aim_code, "addu $t0 $t0 $t1\n");
		}
		else if (n1 == -1 && n2 !=-1) {
			fprintf(aim_code, "addu $t0 $t0 $s%d\n",n2);
		}
		else if (n1 != -1 && n2 == -1) {
			fprintf(aim_code, "addu $t0 $s%d $t1\n", n1);
		}
		else {
			fprintf(aim_code, "addu $t0 $s%d $s%d\n", n1,n2);
		}
		if (addrlist[k].isglo) {
			fprintf(aim_code, "sw $t0 0x%x($t8)\n", addrlist[k].addr);
		}
		else {
			fprintf(aim_code, "sw $t0 0x%x($sp)\n", addrlist[k].addr);
		}
	}
	else {
		if (n1 == -1 && n2 == -1) {
			fprintf(aim_code, "addu $s%d $t0 $t1\n",n3);
		}
		else if (n1 == -1 && n2 != -1) {
			fprintf(aim_code, "addu $s%d $t0 $s%d\n", n3,n2);
		}
		else if (n1 != -1 && n2 == -1) {
			fprintf(aim_code, "addu $s%d $s%d $t1\n", n3, n1);
		}
		else {
			fprintf(aim_code, "addu $s%d $s%d $s%d\n",n3, n1, n2);
		}
	}

}
void minuop() {
	int i=0, j=0, k=0,n1=-1,n2 = -1,n3 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
		k = lookup_addr(midcodelist[mi].var3);
		if (n1 == -1 && n2 == -1) {
			fprintf(aim_code, "sub $t0 $t0 $t1\n");
		}
		else if (n1 == -1 && n2 != -1) {
			fprintf(aim_code, "sub $t0 $t0 $s%d\n", n2);
		}
		else if (n1 != -1 && n2 == -1) {
			fprintf(aim_code, "sub $t0 $s%d $t1\n", n1);
		}
		else {
			fprintf(aim_code, "sub $t0 $s%d $s%d\n", n1, n2);
		}
		if (addrlist[k].isglo) {
			fprintf(aim_code, "sw $t0 0x%x($t8)\n", addrlist[k].addr);
		}
		else {
			fprintf(aim_code, "sw $t0 0x%x($sp)\n", addrlist[k].addr);
		}
	}
	else {
		if (n1 == -1 && n2 == -1) {
			fprintf(aim_code, "sub $s%d $t0 $t1\n", n3);
		}
		else if (n1 == -1 && n2 != -1) {
			fprintf(aim_code, "sub $s%d $t0 $s%d\n", n3, n2);
		}
		else if (n1 != -1 && n2 == -1) {
			fprintf(aim_code, "sub $s%d $s%d $t1\n", n3, n1);
		}
		else {
			fprintf(aim_code, "sub $s%d $s%d $s%d\n", n3, n1, n2);
		}
	}
}
void mulop() {
	int i=0, j=0, k=0,n1 = -1,n2 = -1,n3 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
		k = lookup_addr(midcodelist[mi].var3);
		if (n1 == -1 && n2 == -1) {
			fprintf(aim_code, "mul $t0 $t0 $t1\n");
		}
		else if (n1 == -1 && n2 != -1) {
			fprintf(aim_code, "mul $t0 $t0 $s%d\n", n2);
		}
		else if (n1 != -1 && n2 == -1) {
			fprintf(aim_code, "mul $t0 $s%d $t1\n", n1);
		}
		else {
			fprintf(aim_code, "mul $t0 $s%d $s%d\n", n1, n2);
		}
		if (addrlist[k].isglo) {
			fprintf(aim_code, "sw $t0 0x%x($t8)\n", addrlist[k].addr);
		}
		else {
			fprintf(aim_code, "sw $t0 0x%x($sp)\n", addrlist[k].addr);
		}
	}
	else {
		if (n1 == -1 && n2 == -1) {
			fprintf(aim_code, "mul $s%d $t0 $t1\n", n3);
		}
		else if (n1 == -1 && n2 != -1) {
			fprintf(aim_code, "mul $s%d $t0 $s%d\n", n3, n2);
		}
		else if (n1 != -1 && n2 == -1) {
			fprintf(aim_code, "mul $s%d $s%d $t1\n", n3, n1);
		}
		else {
			fprintf(aim_code, "mul $s%d $s%d $s%d\n", n3, n1, n2);
		}
	}
}
void divop() {
	int i=0, j=0, k=0,n1 = -1,n2 = -1,n3 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
		k = lookup_addr(midcodelist[mi].var3);
		if (n1 == -1 && n2 == -1) {
			fprintf(aim_code, "div $t0 $t0 $t1\n");
		}
		else if (n1 == -1 && n2 != -1) {
			fprintf(aim_code, "div $t0 $t0 $s%d\n", n2);
		}
		else if (n1 != -1 && n2 == -1) {
			fprintf(aim_code, "div $t0 $s%d $t1\n", n1);
		}
		else {
			fprintf(aim_code, "div $t0 $s%d $s%d\n", n1, n2);
		}
		if (addrlist[k].isglo) {
			fprintf(aim_code, "sw $t0 0x%x($t8)\n", addrlist[k].addr);
		}
		else {
			fprintf(aim_code, "sw $t0 0x%x($sp)\n", addrlist[k].addr);
		}
	}
	else {
		if (n1 == -1 && n2 == -1) {
			fprintf(aim_code, "div $s%d $t0 $t1\n", n3);
		}
		else if (n1 == -1 && n2 != -1) {
			fprintf(aim_code, "div $s%d $t0 $s%d\n", n3, n2);
		}
		else if (n1 != -1 && n2 == -1) {
			fprintf(aim_code, "div $s%d $s%d $t1\n", n3, n1);
		}
		else {
			fprintf(aim_code, "div $s%d $s%d $s%d\n", n3, n1, n2);
		}
	}
}
//		>
void grtop() {
	int i = 0, j = 0, n1 = -1, n2 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if (n1 == -1 && n2 == -1)fprintf(aim_code, "slt $t0 $t1 $t0\n");
	if (n1 != -1 && n2 == -1)fprintf(aim_code, "slt $t0 $t1 $s%d\n",n1);
	if (n1 == -1 && n2 != -1)fprintf(aim_code, "slt $t0 $s%d $t0\n",n2);
	if (n1 != -1 && n2 != -1)fprintf(aim_code, "slt $t0 $s%d $s%d\n",n2,n1);

}
//		>=
void geqop() {
	int i = 0, j = 0, n1 = -1, n2 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if (n1 == -1 && n2 == -1) {
		fprintf(aim_code, "slt $t0 $t0 $t1\n");
		fprintf(aim_code, "slti $t0 $t0 1\n");
	}
	if (n1 != -1 && n2 == -1) {
		fprintf(aim_code, "slt $t0 $s%d $t1\n",n1);
		fprintf(aim_code, "slti $t0 $t0 1\n");
	}
	if (n1 == -1 && n2 != -1) {
		fprintf(aim_code, "slt $t0 $t0 $s%d\n",n2);
		fprintf(aim_code, "slti $t0 $t0 1\n");
	}
	if (n1 != -1 && n2 != -1) {
		fprintf(aim_code, "slt $t0 $s%d $s%d\n",n1,n2);
		fprintf(aim_code, "slti $t0 $t0 1\n");
	}

}
//		<
void lssop() {
	int i = 0, j = 0, n1 = -1, n2 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if (n1 == -1 && n2 == -1) {
		fprintf(aim_code, "slt $t0 $t0 $t1\n");
	}
	if (n1 != -1 && n2 == -1) {
		fprintf(aim_code, "slt $t0 $s%d $t1\n",n1);
	}
	if (n1 == -1 && n2 != -1) {
		fprintf(aim_code, "slt $t0 $t0 $s%d\n",n2);
	}
	if (n1 != -1 && n2 != -1) {
		fprintf(aim_code, "slt $t0 $s%d $s%d\n",n1,n2);
	}

}
//		<=
void leqop() {
	int i = 0, j = 0, n1 = -1, n2 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if (n1 == -1 && n2 == -1) {
		fprintf(aim_code, "slt $t0 $t1 $t0\n");
		fprintf(aim_code, "slti $t0 $t0 1\n");
	}
	if (n1 != -1 && n2 == -1) {
		fprintf(aim_code, "slt $t0 $t1 $s%d\n",n1);
		fprintf(aim_code, "slti $t0 $t0 1\n");
	}
	if (n1 == -1 && n2 != -1) {
		fprintf(aim_code, "slt $t0 $s%d $t0\n",n2);
		fprintf(aim_code, "slti $t0 $t0 1\n");
	}
	if (n1 != -1 && n2 != -1) {
		fprintf(aim_code, "slt $t0 $s%d $s%d\n",n2,n1);
		fprintf(aim_code, "slti $t0 $t0 1\n");
	}
}
//		==
void eqlop() {
	int i = 0, j = 0, n1 = -1, n2 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if (n1 == -1 && n2 == -1) {
		fprintf(aim_code, "slt $t2 $t0 $t1\n");
		fprintf(aim_code, "slti $t2 $t2 1\n");
		fprintf(aim_code, "slt $t3 $t1 $t0\n");
		fprintf(aim_code, "slti $t3 $t3 1\n");
		fprintf(aim_code, "and $t0 $t2 $t3\n");
	}
	if (n1 != -1 && n2 == -1) {
		fprintf(aim_code, "slt $t2 $s%d $t1\n",n1);
		fprintf(aim_code, "slti $t2 $t2 1\n");
		fprintf(aim_code, "slt $t3 $t1 $s%d\n",n1);
		fprintf(aim_code, "slti $t3 $t3 1\n");
		fprintf(aim_code, "and $t0 $t2 $t3\n");
	}
	if (n1 == -1 && n2 != -1) {
		fprintf(aim_code, "slt $t2 $t0 $s%d\n",n2);
		fprintf(aim_code, "slti $t2 $t2 1\n");
		fprintf(aim_code, "slt $t3 $s%d $t0\n",n2);
		fprintf(aim_code, "slti $t3 $t3 1\n");
		fprintf(aim_code, "and $t0 $t2 $t3\n");
	}
	if (n1 != -1 && n2 != -1) {
		fprintf(aim_code, "slt $t2 $s%d $s%d\n",n1,n2);
		fprintf(aim_code, "slti $t2 $t2 1\n");
		fprintf(aim_code, "slt $t3 $s%d $s%d\n",n2,n1);
		fprintf(aim_code, "slti $t3 $t3 1\n");
		fprintf(aim_code, "and $t0 $t2 $t3\n");
	}

}
//		!=
void neqop() {
	int i = 0, j = 0, n1 = -1, n2 = -1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if (isnum(midcodelist[mi].var2)) {
		fprintf(aim_code, "li $t1 %d\n", atoi(midcodelist[mi].var2));
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
	}
	if (n1 == -1 && n2 == -1) {
		fprintf(aim_code, "slt $t2 $t0 $t1\n");
		fprintf(aim_code, "slt $t3 $t1 $t0\n");
		fprintf(aim_code, "or $t0 $t2 $t3\n");
	}
	if (n1 != -1 && n2 == -1) {
		fprintf(aim_code, "slt $t2 $s%d $t1\n",n1);
		fprintf(aim_code, "slt $t3 $t1 $s%d\n",n1);
		fprintf(aim_code, "or $t0 $t2 $t3\n");
	}
	if (n1 == -1 && n2 != -1) {
		fprintf(aim_code, "slt $t2 $t0 $s%d\n",n2);
		fprintf(aim_code, "slt $t3 $s%d $t0\n",n2);
		fprintf(aim_code, "or $t0 $t2 $t3\n");
	}
	if (n1 != -1 && n2 != -1) {
		fprintf(aim_code, "slt $t2 $s%d $s%d\n",n1,n2);
		fprintf(aim_code, "slt $t3 $s%d $s%d\n",n2,n1);
		fprintf(aim_code, "or $t0 $t2 $t3\n");
	}

}
//		=
void assop() {
	int i=0, j=0,n1=-1,n2=-1;
	if (isnum(midcodelist[mi].var1)) {
		fprintf(aim_code, "li $t0 %d\n", atoi(midcodelist[mi].var1));
	}
	else {
		if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
			i = lookup_addr(midcodelist[mi].var1);
			if (i != -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
		}
	}
	if ((n2 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
		j = lookup_addr(midcodelist[mi].var3);
		if (j != -1) {
			if (n1 == -1) {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "sw $t0 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "sw $t0 0x%x($sp)\n", addrlist[j].addr);
				}
			}
			else {
				if (addrlist[j].isglo) {
					fprintf(aim_code, "sw $s%d 0x%x($t8)\n", n1,addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "sw $s%d 0x%x($sp)\n", n1,addrlist[j].addr);
				}
			}
		}
	}
	else {
		if (n1 == -1) {
			fprintf(aim_code, "addi $s%d $t0 0\n",n2);
		}
		else {
			fprintf(aim_code, "addi $s%d $s%d 0\n", n2,n1);
		}
	}

}
//		[]=
void sassop() {
	int i=0, j=0, k=0,n1 = -1,n2 = -1;
	int ad1=0;
	i = lookup_addr(midcodelist[mi].var3);
	if (i != -1)ad1 = addrlist[i].addr;
	if (isnum(midcodelist[mi].var2)) {
		ad1 = ad1 + atoi(midcodelist[mi].var2) * 4;
		if (isnum(midcodelist[mi].var1)) {
			fprintf(aim_code, "li $t0 %s\n", midcodelist[mi].var1);
		}
		else {
			if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
				j = lookup_addr(midcodelist[mi].var1);
				if (j != -1) {
					if (addrlist[j].isglo) {
						fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[j].addr);
					}
					else {
						fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[j].addr);
					}
				}
			}
		}
		if (n1 == -1) {
			if (addrlist[i].isglo) {
				fprintf(aim_code, "sw $t0 0x%x($t8)\n", ad1);
			}
			else {
				fprintf(aim_code, "sw $t0 0x%x($sp)\n", ad1);
			}
		}
		else {
			if (addrlist[i].isglo) {
				fprintf(aim_code, "sw $s%d 0x%x($t8)\n",n1, ad1);
			}
			else {
				fprintf(aim_code, "sw $s%d 0x%x($sp)\n",n1, ad1);
			}
		}
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			k = lookup_addr(midcodelist[mi].var2);
			if (k != -1) {
				if (addrlist[k].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[k].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[k].addr);
				}
			}
			fprintf(aim_code, "mul $t1 $t1 4\naddi $t1 $t1 %d\n", ad1);
		}
		else {
			fprintf(aim_code, "mul $t1 $s%d 4\naddi $t1 $t1 %d\n", n2, ad1);
		}

		if (isnum(midcodelist[mi].var1)) {
			fprintf(aim_code, "li $t0 %s\n", midcodelist[mi].var1);
		}
		else {
			if ((n1 = lookup_ref(funid, midcodelist[mi].var1)) == -1) {
				j = lookup_addr(midcodelist[mi].var1);
				if (j != -1) {
					if (addrlist[j].isglo) {
						fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[j].addr);
					}
					else {
						fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[j].addr);
					}
				}
			}
		}
		if (addrlist[i].isglo) {
			fprintf(aim_code, "addu $t1 $t1 $t8\n");
		}
		else {
			fprintf(aim_code, "addu $t1 $t1 $sp\n");
		}
		if (n1 == -1) {
			fprintf(aim_code, "sw $t0 ($t1)\n");
		}
		else {
			fprintf(aim_code, "sw $s%d ($t1)\n",n1);
		}
	}
}
//		geta
void getaop() {
	int i=0, j=0,k=0,n2 = -1,n3 = -1;
	int ad1=0,ad2=0;
	i = lookup_addr(midcodelist[mi].var1);
	if (i != -1)ad1 = addrlist[i].addr;
	if (isnum(midcodelist[mi].var2)) {
		ad1 = ad1 + atoi(midcodelist[mi].var2) * 4;
		if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
			j = lookup_addr(midcodelist[mi].var3);
			if (j != -1)ad2 = addrlist[j].addr;
			if (addrlist[i].isglo) {
				fprintf(aim_code, "lw $t0 0x%x($t8)\n", ad1);
			}
			else {
				fprintf(aim_code, "lw $t0 0x%x($sp)\n", ad1);
			}
			if (addrlist[j].isglo) {
				fprintf(aim_code, "sw $t0 0x%x($t8)\n", ad2);
			}
			else {
				fprintf(aim_code, "sw $t0 0x%x($sp)\n", ad2);
			}
		}
		else {
			if (addrlist[i].isglo) {
				fprintf(aim_code, "lw $s%d 0x%x($t8)\n",n3, ad1);
			}
			else {
				fprintf(aim_code, "lw $s%d 0x%x($sp)\n",n3, ad1);
			}
		}
	}
	else {
		if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
			k = lookup_addr(midcodelist[mi].var2);
			if (k != -1) {
				if (addrlist[k].isglo) {
					fprintf(aim_code, "lw $t1 0x%x($t8)\n", addrlist[k].addr);
				}
				else {
					fprintf(aim_code, "lw $t1 0x%x($sp)\n", addrlist[k].addr);
				}
			}
			fprintf(aim_code, "mul $t1 $t1 4\naddi $t1 $t1 %d\n", ad1);
		}
		else {
			fprintf(aim_code, "mul $t1 $s%d 4\naddi $t1 $t1 %d\n",n2, ad1);
		}
		if (addrlist[i].isglo) {
			fprintf(aim_code, "addu $t1 $t1 $t8\n");
		}
		else {
			fprintf(aim_code, "addu $t1 $t1 $sp\n");
		}
		if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
			fprintf(aim_code, "lw $t0 ($t1)\n");
			j = lookup_addr(midcodelist[mi].var3);
			if (j != -1) {
				ad2 = addrlist[j].addr;
				if (addrlist[j].isglo) {
					fprintf(aim_code, "sw $t0 0x%x($t8)\n", addrlist[j].addr);
				}
				else {
					fprintf(aim_code, "sw $t0 0x%x($sp)\n", addrlist[j].addr);
				}
			}
		}
		else {
			fprintf(aim_code, "lw $s%d ($t1)\n",n3);
		}
	}
}
//		scf,,,c
void scfop() {
	int i=0,ad = 0, ty=0,n3 = -1;
	i = lookup_addr(midcodelist[mi].var3);
	if (i != -1) {
		ad = addrlist[i].addr;
		ty = addrlist[i].type;
		if (ty == INT) {
			fprintf(aim_code, "li $v0 5\nsyscall\n");
			if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "sw $v0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "sw $v0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
			else {
				fprintf(aim_code, "addi $s%d $v0 0\n", n3);
			}

		}
		else {
			fprintf(aim_code, "li $v0 12\nsyscall\n");
			if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
				if (addrlist[i].isglo) {
					fprintf(aim_code, "sw $v0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "sw $v0 0x%x($sp)\n", addrlist[i].addr);
				}
			}
			else {
				fprintf(aim_code, "addi $s%d $v0 0\n", n3);
			}
		}
	}
}
//		prt,a,b,,
void prtop() {
	int ad = 0, j=0,type=INT;
	int n2 = -1;
	/*while (midcodelist[mi].var1[i]!='\0')
	{
		fprintf(aim_code, "li $v0 11\nli $a0 %d\nsyscall\n", midcodelist[mi].var1[i]);
		i++;
	}*/
	if (strcmp(midcodelist[mi].var1, "\0") != 0){
                      fprintf(aim_code, "li $v0 4\nla $a0 string%d\nsyscall\n",atoi(midcodelist[mi].var1));
	}
	if (strcmp(midcodelist[mi].var2, "") != 0) {
		if (isnum(midcodelist[mi].var2) && strcmp(midcodelist[mi].var3, "char") == 0) {
			fprintf(aim_code, "li $v0 11\nli $a0 %d\nsyscall\n", atoi(midcodelist[mi].var2));
		}
		else if (isnum(midcodelist[mi].var2)) {
			fprintf(aim_code, "li $v0 1\nli $a0 %d\nsyscall\n", atoi(midcodelist[mi].var2));
		}
		else {
			j = lookup_addr(midcodelist[mi].var2);
			if (j != -1) {
				ad = addrlist[j].addr;
				type = addrlist[j].type;
			}
			//if (type == INT) {
			if(strcmp(midcodelist[mi].var3, "int") == 0){
				if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
					if (addrlist[j].isglo) {
						fprintf(aim_code, "li $v0 1\nlw $a0 0x%x($t8)\nsyscall\n", addrlist[j].addr);
					}
					else {
						fprintf(aim_code, "li $v0 1\nlw $a0 0x%x($sp)\nsyscall\n", addrlist[j].addr);
					}
				}
				else {
					fprintf(aim_code, "li $v0 1\naddi $a0 $s%d 0\nsyscall\n", n2);
				}
			}
			else {
				if ((n2 = lookup_ref(funid, midcodelist[mi].var2)) == -1) {
					if (addrlist[j].isglo) {
						fprintf(aim_code, "li $v0 11\nlw $a0 0x%x($t8)\nsyscall\n", addrlist[j].addr);
					}
					else {
						fprintf(aim_code, "li $v0 11\nlw $a0 0x%x($sp)\nsyscall\n", addrlist[j].addr);
					}
				}
				else {
					fprintf(aim_code, "li $v0 11\naddi $a0 $s%d 0\nsyscall\n", n2);
				}
			}
		}
	}
}
//		PUSH,,,c
void fpaop() {
	int i = 0, tmi = 0, j = 0, ad = 0, sizes = 0, pushnum = 0, pushoff = 0, n3 = -1;
	tmi = mi;
	while (strcmp(midcodelist[tmi].op, "call") != 0) {
		if (strcmp(midcodelist[tmi].op, "PUSH") == 0) {
			pushnum++;
		}
		tmi++;
	}
	j = lookup_func(midcodelist[tmi].var1);
	sizes = ftab[j].sizes;
	pushoff = ftab[j].offset;
	if (isnum(midcodelist[mi].var3)) {
		fprintf(aim_code, "li $t0 %s\n", midcodelist[mi].var3);
	}
	else {
		if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
			i = lookup_addr(midcodelist[mi].var3);
			if (i != -1) {
				ad = addrlist[i].addr;
				if (addrlist[i].isglo) {
					fprintf(aim_code, "lw $t0 0x%x($t8)\n", addrlist[i].addr);
				}
				else {
					fprintf(aim_code, "lw $t0 0x%x($sp)\n", addrlist[i].addr);
				}

			}
		}
	}
	fprintf(aim_code, "addi $t7 $sp 0\n");
	fprintf(aim_code, "subi $t7 $t7 %d\n", sizes * 4 + 40 - pushoff);
	ftab[j].offset += 4;
	if (n3 == -1) {
		fprintf(aim_code, "sw $t0 ($t7)\n");
	}
	else {
		fprintf(aim_code, "sw $s%d ($t7)\n", n3);
	}
}




//		ret,,,[c]
void retop() {
	int i=0,n3 = -1;
	if (strcmp(midcodelist[mi].var3, "") != 0) {
		if (isnum(midcodelist[mi].var3)) {
			fprintf(aim_code, "li $v0 %d\n", atoi(midcodelist[mi].var3));
		}
		else {
			if ((n3 = lookup_ref(funid, midcodelist[mi].var3)) == -1) {
				i = lookup_addr(midcodelist[mi].var3);
				if (i != -1) {
					if (addrlist[i].isglo) {
						fprintf(aim_code, "lw $v0 0x%x($t8)\n", addrlist[i].addr);
					}
					else {
						fprintf(aim_code, "lw $v0 0x%x($sp)\n", addrlist[i].addr);
					}
				}
			}
			else {
				fprintf(aim_code, "addi $v0 $s%d 0\n", n3);
			}
		}
	}
	fprintf(aim_code, "j fend_%s\n",funcname);
}
//		para,char,,c
void paraop() {
	int ty = 0;
	while (strcmp(midcodelist[mi].op, "para") == 0) {
		ty = (strcmp(midcodelist[mi].var1, "int") == 0) ? INT : CHAR;
		inaddr(ty, 1, 1, 0);
		offset = offset + 4;
		mi++;
	}
}









int lookup_nodelist(int nl, char op[],int left, int right) {
	int i = 0;
	for (i = 1; i <= nl; i++) {
		if (nodelist[i] == NULL) {
			printf("´íÀ²");
		}
		else {
			if (strcmp(op, nodelist[i]->op) == 0 && left == nodelist[i]->left_index
				&& right == nodelist[i]->right_index) {
				return i;
			}
		}
	}
	return -1;
}
int lookup_nodetabname(int nt,char name[]) {
	int i = 0;
	for (i = 0; i < nt; i++) {
		if (strcmp(name, nodetab[i].name) == 0) {
			return i;
		}
	}
	return nt;
}
void DAG() {
	// struct Nodelist *head, *child1,*child2,*p;
	struct Nodelist *child1,*child2,*p;
	int left, right,first;
	char var3[100],temp[100];
	int mi,optmi = 0,nt,nl,i,j,k,mnt = 0;
	int order[100],od;
	for (mi = 0; mi < midcodeiter; mi++) {
		memset(nodetab, '\0', 100 * sizeof(struct Nodetab));
		for (i = 0; i < 100; i++) {
			if (nodelist[i] != NULL) {
				nodelist[i] = NULL;
				//free(nodelist[i]);
			}
		}
		nt = 0;
		nl = 0;
		od = 0;
		if (strcmp(midcodelist[mi].op, "=") == 0 || strcmp(midcodelist[mi].op, "minu") == 0 ||
			strcmp(midcodelist[mi].op, "plus") == 0 || strcmp(midcodelist[mi].op, "mul") == 0 ||
			strcmp(midcodelist[mi].op, "div") == 0) {
			while (strcmp(midcodelist[mi].op, "=") == 0 || strcmp(midcodelist[mi].op, "minu") == 0 ||
				strcmp(midcodelist[mi].op, "plus") == 0 || strcmp(midcodelist[mi].op, "mul") == 0 ||
				strcmp(midcodelist[mi].op, "div") == 0) {
				midtemp = midcodelist[mi];
				//z=x
				if (strcmp(midcodelist[mi].op, "=") == 0) {
					i = lookup_nodetabname(nt, midtemp.var1);
					if (i == nt) {
						//		if (!isnum(midtemp.var1)) {
						child1 = (struct Nodelist*)malloc(sizeof(struct Nodelist));
						strcpy(child1->op, "");
						child1->pi = 0;
						child1->is_leaf = 1;
						child1->in_order = 0;
						child1->left_index = 0;
						child1->right_index = 0;
						memset(child1->parent_index,0,400);
						nodelist[++nl] = child1;
						nodetab[nt].index = nl;
						strcpy(nodetab[nt].name, midtemp.var1);
						left = nl;
						nt++;
						//		}
					}
					else {
						left = nodetab[i].index;
						child1 = nodelist[left];
					}
					k = lookup_nodetabname(nt, midtemp.var3);
					if (k == nt) {
						strcpy(nodetab[nt].name, midtemp.var3);
						nodetab[nt].index = left;
						nt++;
					}
					else {
						if (nodelist[nodetab[k].index]->is_leaf == 1 && !isnum(nodetab[k].name) && nodetab[k].index!=left) {
							strcpy(midcodeopt[optmi].var1, nodetab[k].name);
							strcpy(temp, nodetab[k].name);
							strcpy(nodetab[k].name, "$");
							strcat(nodetab[k].name, temp);
							strcpy(midcodeopt[optmi].op, "=");
							strcpy(midcodeopt[optmi].var3, nodetab[k].name);
							fprintf(mid_opt_file, "%s\t%s\t%s\t%s\n", midcodeopt[optmi].op, midcodeopt[optmi].var1, midcodeopt[optmi].var2, midcodeopt[optmi].var3);

							optmi++;
							strcpy(nodetab[nt].name, midtemp.var3);
							nodetab[nt].index = left;
							nt++;
						}
						else {
							nodetab[k].index = left;
						}
					}
				}
				//z=x op y
				if (strcmp(midcodelist[mi].op, "minu") == 0 ||
					strcmp(midcodelist[mi].op, "plus") == 0 || strcmp(midcodelist[mi].op, "mul") == 0 ||
					strcmp(midcodelist[mi].op, "div") == 0)
				{
					i = lookup_nodetabname(nt, midtemp.var1);
					if (i == nt) {
						//		if (!isnum(midtemp.var1)) {
						child1 = (struct Nodelist*)malloc(sizeof(struct Nodelist));
						strcpy(child1->op, "");
						child1->in_order = 0;
						child1->pi = 0;
						child1->is_leaf = 1;
						child1->left_index = 0;
						child1->right_index = 0;
						memset(child1->parent_index,'\0',100);
						nodelist[++nl] = child1;
						nodetab[nt].index = nl;
						strcpy(nodetab[nt].name, midtemp.var1);
						left = nl;
						nt++;
						//		}
					}
					else {
						left = nodetab[i].index;
						child1 = nodelist[left];
					}
					j = lookup_nodetabname(nt, midtemp.var2);
					if (j == nt) {
						child2 = (struct Nodelist*)malloc(sizeof(struct Nodelist));
						strcpy(child2->op, "");
						child2->in_order = 0;
						child2->pi = 0;
						child2->is_leaf = 1;
						child2->left_index = 0;
						child2->right_index = 0;
						memset(child2->parent_index,'\0',100);
						nodelist[++nl] = child2;
						nodetab[nt].index = nl;
						strcpy(nodetab[nt].name, midtemp.var2);
						right = nl;
						nt++;
					}
					else {
						right = nodetab[j].index;
						child2 = nodelist[right];
					}
					k = lookup_nodelist(nl, midtemp.op, left, right);
					if (k == -1) {
						p = (struct Nodelist*)malloc(sizeof(struct Nodelist));
						strcpy(p->op, midtemp.op);
						p->in_order = 0;
						p->pi = 0;
						p->is_leaf = 0;
						p->left_index = left;
						p->right_index = right;
						memset(p->parent_index,'\0',100);
						nodelist[++nl] = p;
						child1->parent_index[child1->pi++] = nl;
						child2->parent_index[child2->pi++] = nl;
						k = nl;
					}
					i = lookup_nodetabname(nt, midtemp.var3);
					if (i == nt) {
						strcpy(nodetab[nt].name, midtemp.var3);
						nodetab[nt].index = k;
						nt++;
					}
					else {
						if (nodelist[nodetab[i].index]->is_leaf == 1 && !isnum(nodetab[i].name)) {
							strcpy(midcodeopt[optmi].var1, nodetab[i].name);
							strcpy(temp, nodetab[i].name);
							strcpy(nodetab[i].name, "$");
							strcat(nodetab[i].name, temp);
							strcpy(midcodeopt[optmi].op, "=");
							strcpy(midcodeopt[optmi].var3, nodetab[i].name);
							fprintf(mid_opt_file, "%s\t%s\t%s\t%s\n", midcodeopt[optmi].op, midcodeopt[optmi].var1, midcodeopt[optmi].var2, midcodeopt[optmi].var3);

							optmi++;
							strcpy(nodetab[nt].name, midtemp.var3);
							nodetab[nt].index = k;
							nt++;
						}
						else {
							nodetab[i].index = k;
						}
					}
				}
				mi++;
			}
			mi--;
			for (i = 1; i <= nl; i++) {
				if (nodelist[i]->is_leaf == 1) {
					lookup_nodetabindex(nt, i);
					if (tn > 1) {
						for (j = 1; j < tn; j++) {
							strcpy(midcodeopt[optmi].op, "=");
							strcpy(midcodeopt[optmi].var1, nodetab[tabnum[0]].name);
							strcpy(midcodeopt[optmi].var3, nodetab[tabnum[j]].name);
							fprintf(mid_opt_file, "%s\t%s\t%s\t%s\n", midcodeopt[optmi].op, midcodeopt[optmi].var1, midcodeopt[optmi].var2, midcodeopt[optmi].var3);
							optmi++;
						}
					}
				}
			}
			while (1) {
				for (i = 1; i <= nl; i++) {
					if (can_in(i)) {
						order[od++] = i;
						nodelist[i]->in_order = 1;
						j = nodelist[i]->left_index;
						while (j != 0)
						{
							if (can_in(j)) {
								order[od++] = j;
								nodelist[j]->in_order = 1;

							}
							j = nodelist[j]->left_index;
						}
					}
				}
				if (all_in(nl)) {
					break;
				}
			}
			while (od > 0) {
				od--;
				strcpy(midcodeopt[optmi].op, nodelist[order[od]]->op);
				left = nodelist[order[od]]->left_index;
				right = nodelist[order[od]]->right_index;
				lookup_nodetabindex(nt, left);
				for (i = 0; i < tn; i++) {
					if (nodetab[tabnum[i]].name[0] != '$') {
						strcpy(midcodeopt[optmi].var1, nodetab[tabnum[i]].name);
						break;
					}
				}
				if (tn != 0) {
					if (i == tn) {
						strcpy(midcodeopt[optmi].var1, nodetab[tabnum[0]].name);
					}
				}
				else {
					strcpy(midcodeopt[optmi].var1, "");
				}
				lookup_nodetabindex(nt, right);
				for (i = 0; i < tn; i++) {
					if (nodetab[tabnum[i]].name[0] != '$') {
						strcpy(midcodeopt[optmi].var2, nodetab[tabnum[i]].name);
						break;
					}
				}
				if (tn != 0) {
					if (i == tn) {
						strcpy(midcodeopt[optmi].var2, nodetab[tabnum[0]].name);
					}
				}
				else {
					strcpy(midcodeopt[optmi].var2, "");
				}
				lookup_nodetabindex(nt, order[od]);
				first = 1;
				for (i = 0; i < tn; i++) {
					if (nodetab[tabnum[i]].name[0] != '$') {
						if (first) {
							strcpy(midcodeopt[optmi].var3, nodetab[tabnum[i]].name);
							strcpy(var3, nodetab[tabnum[i]].name);
							fprintf(mid_opt_file, "%s\t%s\t%s\t%s\n", midcodeopt[optmi].op, midcodeopt[optmi].var1, midcodeopt[optmi].var2, midcodeopt[optmi].var3);
							optmi++;
							first = 0;
						}
						else {
							strcpy(midcodeopt[optmi].op, "=");
							strcpy(midcodeopt[optmi].var1, var3);
							strcpy(midcodeopt[optmi].var3, nodetab[tabnum[i]].name);
							fprintf(mid_opt_file, "%s\t%s\t%s\t%s\n", midcodeopt[optmi].op, midcodeopt[optmi].var1, midcodeopt[optmi].var2, midcodeopt[optmi].var3);
							optmi++;
						}
					}
				}
				if (first) {
					strcpy(midcodeopt[optmi].var3, nodetab[tabnum[0]].name);
					fprintf(mid_opt_file, "%s\t%s\t%s\t%s\n", midcodeopt[optmi].op, midcodeopt[optmi].var1, midcodeopt[optmi].var2, midcodeopt[optmi].var3);
					optmi++;
				}
			}

		}
		else {
			midcodeopt[optmi] = midcodelist[mi];
			fprintf(mid_opt_file, "%s\t%s\t%s\t%s\n", midcodeopt[optmi].op, midcodeopt[optmi].var1, midcodeopt[optmi].var2, midcodeopt[optmi].var3);
			optmi++;
		}
	}
	memset(midcodelist, '\0', 1000 * sizeof(struct Midcode));
	for (midcodeiter = 0; midcodeiter < optmi; midcodeiter++) {
		midcodelist[midcodeiter] = midcodeopt[midcodeiter];
	}
}
void lookup_nodetabindex(int nt,int index) {
	int i;
	tn = 0;
	for (i = 0; i < nt; i++) {
		if (nodetab[i].index == index) {
			tabnum[tn++] = i;
		}
	}
}
int can_in(int x) {
	int i, p;
	if (nodelist[x]->is_leaf == 0) {
		if (nodelist[x]->in_order == 1) {
			return 0;
		}
		if (nodelist[x]->pi == 0) {
			return 1;
		}
		for (i = 0; i < nodelist[x]->pi; i++) {
			p = nodelist[x]->parent_index[i];
			if (nodelist[p]->in_order != 1) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
int all_in(int nl) {
	int i;
	for (i = 1; i <= nl; i++) {
		if (nodelist[i]->is_leaf == 0 && nodelist[i]->in_order == 0) {
			return 0;
		}
	}
	return 1;
}









int lookup_ref(int j,char name[]) {
	int i;
	for (i = 0; i < ftab[j].rt && i<8; i++) {
		if (strcmp(ftab[j].ref_tab[i].name, name)==0) {
			return i;
		}
	}
	return -1;
}
void ref_entering(int j,char name[]) {
	int i= 0;
	for (i = 0; i < ftab[j].rt; i++) {
		if (strcmp(ftab[j].ref_tab[i].name, name)==0) {
			ftab[j].ref_tab[i].num++;
			return;
		}
	}
	if (name[0] == '$') {
		strcpy(ftab[j].ref_tab[ftab[j].rt].name, name);
		ftab[j].ref_tab[ftab[j].rt++].num = 1;
	}
}
void ref_count() {
	int i,j,k;
	for (i = 0; i < midcodeiter; i++) {
		if (strcmp(midcodelist[i].op, "func") != 0) {
			continue;
		}
		j = lookup_func(midcodelist[i].var3);
		if (j != -1) {
			if (j != f - 1) {
				for (k = ftab[j].refs + 1 + ftab[j].paranum; k < ftab[j + 1].refs; k++) {
					if (tab[k].type != arrays) {
						strcpy(ftab[j].ref_tab[ftab[j].rt].name, tab[k].name);
						ftab[j].ref_tab[ftab[j].rt++].num = 1;
					}
				}
			}
			else {
				for (k = ftab[j].refs + 1 + ftab[j].paranum; k < t; k++) {
					if (tab[k].type != arrays) {
						strcpy(ftab[j].ref_tab[ftab[j].rt].name, tab[k].name);
						ftab[j].ref_tab[ftab[j].rt++].num = 1;
					}
				}
			}
		}
		else {
			err(0);
		}
		while (strcmp(midcodelist[i].op, "end") != 0) {
			ref_entering(j, midcodelist[i].var1);
			ref_entering(j, midcodelist[i].var2);
			ref_entering(j, midcodelist[i].var3);
			i++;
		}
		sorttable(j);
	}
}
void sorttable(int fun) {
	int i, j;
	struct Ref_Tab temp;
	for (i = 0; i < ftab[fun].rt; i++) {
		for (j = i; j < ftab[fun].rt; j++) {
			if (ftab[fun].ref_tab[j].num > ftab[fun].ref_tab[i].num) {
				temp = ftab[fun].ref_tab[i];
				ftab[fun].ref_tab[i] = ftab[fun].ref_tab[j];
				ftab[fun].ref_tab[j] = temp;
			}
		}
	}
}










int main()
{
    int optflag = 0;
    char FilePathName[1024] = { '\0' };
    printf("Plz enter file path name:\n");
    scanf("%s",FilePathName);
    printf("Plz choose optflg:");
    scanf("%d",&optflag);
    in = fopen(FilePathName,"r");
    // in = fopen("16231181_test.txt", "r");
    out = fopen("16231181_result1.txt", "w");
    lex_result = fopen("16231181_lex_result.txt", "w");
    gra_result = fopen("16231181_gra_result.txt", "w");
    midcode = fopen("16231181_midcode.txt","w");
    mid_opt_file = fopen("16231181_mid_opt_file.txt","w");
    if (optflag == 0) aim_code = fopen("16231181_aimcode.asm", "w");
    else              aim_code = fopen("16231181_aimcode_opt.asm", "w");
    if (!in) {
		err(0);
		exit(0);
	}
    nextch();
    nextsym();
    ids_entering();
    proceduredec();
    printmidcode();
    if (optflag) {
		DAG();
		ref_count();
	}
    midcodetoasm();
    return 0;
}
