// ������
void err(int n);      // ����n�Ŵ���
void endjump();       // �������Ĳ��ֻ��»���
void j2statement(); // ������һ�����
void j2rparent();   // ����������
void j2rbracket();  // �����ҷ�����
void j2rbrace();    // �����Ҵ�����
void j2facnext();   // ������һ������
void j2fundec();    // ������������
void j2dec();       // ������������
void j2condec();    // ������������
void j2sem();       // �����ֺ�
void j2lbrace();    // �����������

// �ʷ�����
void nextch();        // ��ȡ��һ���ַ�
void nextsym();       // ��ȡ��һ����ע����ĵ���
void sytosym(enum Symbol sy,char sym[]);    // ����Ӧsyת��Ϊ�ַ����������
void get_a_sym();       // ��ȡ��һ������

// �﷨����
int lookup(char idl[]);                        // ��ѯ�����Ƿ��ڷ��ű���
void testsemicolon();                       // ���ֺŲ���ȡ��һ����
enum types gettype();
void entering(char id[], enum objecttyp objtyp, enum types type,int isfun);     // ����ű�
void variable_entering(char temp[],enum types type);                             // ����ű��������
void array(_enteringenum types type,int sizes);                                  // ����ű���������
void arr_variable_entering(char temp[],enum types type,int isglobal);                        // ����ű�������������
int const_entering(enum types type);                                             // ����ű������
void id_entering(char name[],enum objecttyp objtyp,enum types type,int adr);     // ���������
void ids_entering();                            // ���������
void parameterlist(enum types type);        // ������
void constdec(enum types type);             // ����˵�������壩
void variabledec(char temp[],enum types type); // ��������
void fun_entering(char name[],int refs,enum types type);
void functiondec(enum types type);            // ��������
void proceduredec();                               // ����

void statement();                           // ���
void returnstatement();                     // �������
void printstatement();                      // ��ӡ���
void scanfstatement();                      // �������
void linestatement();                       // �����
void ifstatement();                         // if���
void forstatement();                        // forѭ��
void whilestatement();                      // whileѭ��
void factor();                              // ����
void term();                                // ��
void simpleexpression();                    // ���ʽ
void assignment(struct Tab tabi);           // ��ֵ
void selector(struct Tab tabi);             // �����±�
void codition();                            // ����

// �м��������
void inmidcode(char op[],char v1[],char v2[],char v3[]);          // ��һ���м��������м�midcodelist
char * newlabel();                          // ����һ���±�ǩ
char * newvar();                            // ����һ���±���
void printmidcode();                        // �м����������ļ�

// Ŀ���������
int isnum(char var[]);                      // �ж�����
int lookup_addr(char name[]);                   // ���ұ�����addrlist�еĵ�ַ
int lookup_func(char name[]);                   // ���Һ����ں�����ftab�еĵ�ַ
void instack(char var[], int sizes);        // ������ջ
void inaddr(int type, int tmi, int t, int glob);       // ��������addrlist
void midcodetoasm();             // �м��������Ŀ�����
void callop();				// �������ô���
void GOTOop();				// ����j ��ת���
void BZop();				// ������1ʱ��ת
void labop();				// �����±�ǩ
void plusop();				// ��
void minuop();				// ��
void mulop();				// ��
void divop();				// ��
void grtop();				// ����
void geqop();				// ���ڵ���
void lssop();				// С��
void leqop();				// С�ڵ���
void eqlop();				// ����
void neqop();				// ������
void assop();				// ��ֵ
void sassop();				// ����Ԫ�ظ�ֵ[]=
void getaop();				// ������Ԫ�ص�ֵ��������
void scfop();				// ����
void prtop();				// ���
void fpaop();				// ��������ʱ������ֵPUSH,,,c
void retop();				// �������
void paraop();				// ����
void funcop();				// ����

// ���ü���������Ĵ���
int lookup_ref(int j,char name[]);		// ���ұ����Ƿ�����˼Ĵ��������ؼĴ������
void ref_entering(int j, char name[]);	// �����������ô���+1������δ������ʱ����������������ô�����1
void ref_count();						// �����м���룬�Ժ���Ϊ��λͳ�Ʊ��������ô���
void sorttable(int fun);				// �Ա����������ô����Ӹߵ�������

// DAGͼ
void DAG();										// ����DAGͼ
int lookup_nodelist(int nl, char op[], int left, int right);	// ��ѯ�ڵ��ŵ�ַ
int lookup_nodetabname(int nt, char name[]);	// �����Ʋ�ѯ�ڵ��
void lookup_nodetabindex(int nt, int index);	// ���±�������ѯ�ڵ��
int can_in(int x);						// DAGͼ����ʱ�жϽڵ��Ƿ���Խ������
int all_in(int nl);						// DAGͼ����ʱ�ж��Ƿ������м�����ѽ������
