#include<stdio.h>
#include<string.h>
#include"pl0.h"

int main(void) {
    init();
    lexicalAnalysis(); // 词法分析
    return 0;
}

void init() { // 初始化函数 start
    // 保留字
    strcpy(keyWord[0], "begin");
    strcpy(keyWord[1], "call");
    strcpy(keyWord[2], "const");
    strcpy(keyWord[3], "do");
    strcpy(keyWord[4], "end");
    strcpy(keyWord[5], "if");
    strcpy(keyWord[6], "odd");
    strcpy(keyWord[7], "procedure");
    strcpy(keyWord[8], "read");
    strcpy(keyWord[9], "then");
    strcpy(keyWord[10], "var");
    strcpy(keyWord[11], "while");
    strcpy(keyWord[12], "write");
    strcpy(keyWord[13], "studentid");
    strcpy(keyWord[14], "name");
    strcpy(keyWord[15], "Jenny");

    // 运算符
    strcpy(operator[0], "+");
    strcpy(operator[1], "-");
    strcpy(operator[2], "*");
    strcpy(operator[3], "/");
    strcpy(operator[4], "=");
    strcpy(operator[5], "#");
    strcpy(operator[6], "<");
    strcpy(operator[7], "<=");
    strcpy(operator[8], ">");
    strcpy(operator[9], ">=");
    strcpy(operator[10], ":=");

    // 界符
    delimiter[0] = '(';
    delimiter[1] = ')';
    delimiter[2] = ',';
    delimiter[3] = ';';
    delimiter[4] = '.';
} // 初始化函数 end

bool lexicalAnalysis() { // 词法分析函数 start
    num = 0;
    fSource = fopen("source.txt", "r"); // 读取源程序文件
    fLexical = fopen("lexical.txt", "w"); // 词法分析结果文件

    if (!fSource) {
        printf("Can't open the source file!\n");
        return false;
    }

    if (!fLexical) {
        printf("Can't open the lexical file!\n");
        return false;
    }
    while ((ch = fgetc(fSource)) != EOF) {
        if (isEmpty(ch)) { // 空格
            continue;
        }
        else if (isLetter(ch)) { // 字母
            char str[100];
            int i = 0;
            str[i++] = ch;
            while ((ch = fgetc(fSource)) != EOF && (isLetter(ch) || isDigit(ch))) {
                str[i++] = ch;
            }
            str[i] = '\0';
            if (isKeyWord(str)) {
                printf("%d %s %s\n", ++num, "保留字", str);
                fprintf(fLexical, "%d %s %s\n", num, "保留字", str);
            }
            else {
                printf("%d %s %s\n", ++num, "标识符", str);
                fprintf(fLexical, "%d %s %s\n", num, "标识符", str);
            }
            ungetc(ch, fSource);
        }
        else if (isDigit(ch)) { // 数字
            char str[100];
            int i = 0;
            str[i++] = ch;
            while ((ch = fgetc(fSource)) != EOF && isDigit(ch)) {
                str[i++] = ch;
            }
            str[i] = '\0';
            printf("%d %s %s\n", ++num, "数字", str);
            fprintf(fLexical, "%d %s %s\n", num, "数字", str);
            ungetc(ch, fSource);
        }
        else if (isOperator(ch)) { // 运算符
            char str[100];
            int i = 0;
            str[i++] = ch;
            if ((ch = fgetc(fSource)) != EOF) {
                str[i++] = ch;
                str[i] = '\0';
                if (isOperator(ch)) {
                    printf("%d %s %s\n", ++num, "运算符", str);
                    fprintf(fLexical, "%d %s %s\n", num, "运算符", str);
                }
                else {
                    str[i - 1] = '\0';
                    printf("%d %s %s\n", ++num, "运算符", str);
                    fprintf(fLexical, "%d %s %s\n", num, "运算符", str);
                    ungetc(ch, fSource);
                }
            }
            else {
                str[i] = '\0';
                printf("%d %s, %s\n", ++num, "运算符", str);
                fprintf(fLexical, "%d %s %s\n", num, "运算符", str);
            }
        }
        else if (isDelimiter(ch)) { // 界符
            char str[100];
            str[0] = ch;
            str[1] = '\0';
            printf("%d %s %s\n", ++num, "界符", str);
            fprintf(fLexical, "%d %s %s\n", num, "界符", str);
            if(str[0] == '.'){
                break;
            }
        }
        else {
            printf("%d %s, %c\n", ++num, "非法", ch);
            fprintf(fLexical, "%d %s %c\n", num, "非法", ch);
            return false;
        }
    }
    fclose(fSource); // 关闭源程序文件
    fclose(fLexical); // 关闭词法分析结果文件
    return true;
} // 词法分析函数 end

bool isEmpty(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
} // 判断是否为空格

bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
} // 判断是否为字母

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
} // 判断是否为数字

bool isKeyWord(char* str) {
    for (int i = 0; i < keyWordNum; i++) {
        if (strcmp(str, keyWord[i]) == 0) {
            return true;
        }
    }
    return false;
} // 判断是否为保留字

bool isOperator(char ch) {
    for (int i = 0; i < operatorNum; i++) {
        if (ch == operator[i][0]) {
            return true;
        }
    }
    return false;
} // 判断是否为运算符

bool isDelimiter(char ch) {
    for (int i = 0; i < delimiterNum; i++) {
        if (ch == delimiter[i]) {
            return true;
        }
    }
    return false;
} // 判断是否为界符
