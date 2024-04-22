//
// Created by Tame on 2024/4/11.
//

#ifndef PL0_H
#define PL0_H

/* PL/0 编译系统C版本头文件 pl0.h */

#include<stdio.h>
#include<string.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#define norw 16 // 保留字个数
#define al 10 // 保留字或标识符的最大长度
#define nmax 14 // 数字的最大位数

enum symbol { // 符号
    nul, // 非法字符 0
    ident, // 标识符 1
    number, // 数字 2
    plus, minus, times, slash, eql, neq, lss, leq, gtr, geq, becomes, // 运算符 3-13
    lparen, rparen, comma, semicolon, period, // 界符 14-18
    // 保留字 19-34
    beginsym, callsym, constsym, dosym, endsym, ifsym, jennysym, namesym, oddsym, procsym,
    readsym, studentidsym, thensym, varsym, whilesym, writesym
};

#define symnum 32 // 符号个数

#define getchdo if(getch() == -1) return -1; // 读取一个字符

FILE* fsource; // 源程序文件指针
FILE* flexical; // 词法分析结果文件指针

char keyWord[norw][al]; // 保留字
char operator[11][3]; // 运算符
char delimiter[5][2]; // 界符
enum symbol wsym[norw]; // 保留字对应的符号值
enum symbol ssym[256]; // 单字符的符号值

char ch; // 当前读入的字符
char line[81]; // 当前读取的行
int ll; // 当前行的长度
int cc; // 当前字符的索引号
int index; // 词法分析结果的索引号

enum symbol sym; // 当前的符号
char a[al + 1]; // 当前读取的标识符
char str[al+1]; // 当前读取的字符串
int num; // 当前读入的数字

void init(); // 初始化函数
int lexicalAnalysis(); // 词法分析函数
int getsym(); // 读取一个符号
int getch(); // 读取一行

#endif //PL0_H
