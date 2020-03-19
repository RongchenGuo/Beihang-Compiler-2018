// 错误处理
void err(int n);      // 报第n号错误
void endjump();       // 在跳过的部分画下划线
void j2statement(); // 跳到下一条语句
void j2rparent();   // 跳到右括号
void j2rbracket();  // 跳到右方括号
void j2rbrace();    // 跳到右大括号
void j2facnext();   // 跳到下一个因子
void j2fundec();    // 跳到函数声明
void j2dec();       // 跳到变量声明
void j2condec();    // 跳到常量声明
void j2sem();       // 跳到分号
void j2lbrace();    // 跳到左大括号

// 词法分析
void nextch();        // 读取下一个字符
void nextsym();       // 读取下一个除注释外的单词
void sytosym(enum Symbol sy,char sym[]);    // 将对应sy转换为字符串用于输出
void get_a_sym();       // 读取下一个单词

// 语法分析
int lookup(char idl[]);                        // 查询变量是否在符号表中
void testsemicolon();                       // 检测分号并读取下一单词
enum types gettype();
void entering(char id[], enum objecttyp objtyp, enum types type,int isfun);     // 填符号表
void variable_entering(char temp[],enum types type);                             // 向符号表中填变量
void array(_enteringenum types type,int sizes);                                  // 向符号表中填数组
void arr_variable_entering(char temp[],enum types type,int isglobal);                        // 向符号表中填数组或变量
int const_entering(enum types type);                                             // 向符号表中填常量
void id_entering(char name[],enum objecttyp objtyp,enum types type,int adr);     // 保留字填表
void ids_entering();                            // 保留字填表
void parameterlist(enum types type);        // 参数表
void constdec(enum types type);             // 常量说明（定义）
void variabledec(char temp[],enum types type); // 变量定义
void fun_entering(char name[],int refs,enum types type);
void functiondec(enum types type);            // 函数定义
void proceduredec();                               // 程序

void statement();                           // 语句
void returnstatement();                     // 返回语句
void printstatement();                      // 打印语句
void scanfstatement();                      // 读入语句
void linestatement();                       // 语句列
void ifstatement();                         // if语句
void forstatement();                        // for循环
void whilestatement();                      // while循环
void factor();                              // 因子
void term();                                // 项
void simpleexpression();                    // 表达式
void assignment(struct Tab tabi);           // 赋值
void selector(struct Tab tabi);             // 数组下标
void codition();                            // 条件

// 中间代码生成
void inmidcode(char op[],char v1[],char v2[],char v3[]);          // 将一条中间代码加入中间midcodelist
char * newlabel();                          // 生成一个新标签
char * newvar();                            // 生成一个新变量
void printmidcode();                        // 中间代码输出到文件

// 目标代码生成
int isnum(char var[]);                      // 判断数字
int lookup_addr(char name[]);                   // 查找变量在addrlist中的地址
int lookup_func(char name[]);                   // 查找函数在函数表ftab中的地址
void instack(char var[], int sizes);        // 变量入栈
void inaddr(int type, int tmi, int t, int glob);       // 变量填入addrlist
void midcodetoasm();             // 中间代码生成目标代码
void callop();				// 函数调用处理
void GOTOop();				// 生成j 跳转语句
void BZop();				// 不等于1时跳转
void labop();				// 生成新标签
void plusop();				// 加
void minuop();				// 减
void mulop();				// 乘
void divop();				// 除
void grtop();				// 大于
void geqop();				// 大于等于
void lssop();				// 小于
void leqop();				// 小于等于
void eqlop();				// 等于
void neqop();				// 不等于
void assop();				// 赋值
void sassop();				// 数组元素赋值[]=
void getaop();				// 将数组元素的值赋给变量
void scfop();				// 读入
void prtop();				// 输出
void fpaop();				// 函数调用时参数的值PUSH,,,c
void retop();				// 返回语句
void paraop();				// 参数
void funcop();				// 函数

// 引用计数法分配寄存器
int lookup_ref(int j,char name[]);		// 查找变量是否分配了寄存器，返回寄存器编号
void ref_entering(int j, char name[]);	// 将变量的引用次数+1，若是未入表的临时变量，将其入表，引用次数置1
void ref_count();						// 遍历中间代码，以函数为单位统计变量的引用次数
void sorttable(int fun);				// 对变量按其引用次数从高到低排序

// DAG图
void DAG();										// 生成DAG图
int lookup_nodelist(int nl, char op[], int left, int right);	// 查询节点存放地址
int lookup_nodetabname(int nt, char name[]);	// 按名称查询节点表
void lookup_nodetabindex(int nt, int index);	// 按下标索引查询节点表
int can_in(int x);						// DAG图导出时判断节点是否可以进入队列
int all_in(int nl);						// DAG图导出时判断是否所有中间结点均已进入队列
