//
// Created by Tame on 2024/4/11.
//

#ifndef PL0_H
#define PL0_H

/* PL/0 编译系统C版本头文件 pl0.h */

typedef enum bool {
    false,
    true
} bool; // 自定义bool类型

#define keyWordNum 16 // 保留字个数
#define keyWordLength 10 // 保留字最大长度
#define operatorNum 11 // 运算符个数
#define operatorLength 3 // 运算符最大长度
#define delimiterNum 5 // 界符个数
#define delimiterLength 3 // 界符最大长度

FILE* fSource; // 源程序文件指针
FILE* fLexical; // 词法分析结果文件指针
char keyWord[keyWordNum][keyWordLength]; // 保留字表
char operator[operatorNum][operatorLength]; // 运算符表
char delimiter[delimiterNum]; // 界符表
char ch; // 当前读入的字符
int num; // 当前读取的索引号

void init(); // 初始化函数
bool lexicalAnalysis(); // 词法分析函数
bool isEmpty(char ch); // 判断是否为空格
bool isLetter(char ch); // 判断是否为字母
bool isDigit(char ch); // 判断是否为数字
bool isKeyWord(char* str); // 判断是否为保留字
bool isOperator(char ch); // 判断是否为运算符
bool isDelimiter(char ch); // 判断是否为界符

#endif //PL0_H
