#include<stdio.h>
#include<string.h>
#include"pl0.h"

int main(void) {
    init();
    lexicalAnalysis(); // �ʷ�����
    return 0;
}

void init() { // ��ʼ������ start
    // ������
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

    // �����
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

    // ���
    delimiter[0] = '(';
    delimiter[1] = ')';
    delimiter[2] = ',';
    delimiter[3] = ';';
    delimiter[4] = '.';
} // ��ʼ������ end

bool lexicalAnalysis() { // �ʷ��������� start
    num = 0;
    fSource = fopen("source.txt", "r"); // ��ȡԴ�����ļ�
    fLexical = fopen("lexical.txt", "w"); // �ʷ���������ļ�

    if (!fSource) {
        printf("Can't open the source file!\n");
        return false;
    }

    if (!fLexical) {
        printf("Can't open the lexical file!\n");
        return false;
    }
    while ((ch = fgetc(fSource)) != EOF) {
        if (isEmpty(ch)) { // �ո�
            continue;
        }
        else if (isLetter(ch)) { // ��ĸ
            char str[100];
            int i = 0;
            str[i++] = ch;
            while ((ch = fgetc(fSource)) != EOF && (isLetter(ch) || isDigit(ch))) {
                str[i++] = ch;
            }
            str[i] = '\0';
            if (isKeyWord(str)) {
                printf("%d %s %s\n", ++num, "������", str);
                fprintf(fLexical, "%d %s %s\n", num, "������", str);
            }
            else {
                printf("%d %s %s\n", ++num, "��ʶ��", str);
                fprintf(fLexical, "%d %s %s\n", num, "��ʶ��", str);
            }
            ungetc(ch, fSource);
        }
        else if (isDigit(ch)) { // ����
            char str[100];
            int i = 0;
            str[i++] = ch;
            while ((ch = fgetc(fSource)) != EOF && isDigit(ch)) {
                str[i++] = ch;
            }
            str[i] = '\0';
            printf("%d %s %s\n", ++num, "����", str);
            fprintf(fLexical, "%d %s %s\n", num, "����", str);
            ungetc(ch, fSource);
        }
        else if (isOperator(ch)) { // �����
            char str[100];
            int i = 0;
            str[i++] = ch;
            if ((ch = fgetc(fSource)) != EOF) {
                str[i++] = ch;
                str[i] = '\0';
                if (isOperator(ch)) {
                    printf("%d %s %s\n", ++num, "�����", str);
                    fprintf(fLexical, "%d %s %s\n", num, "�����", str);
                }
                else {
                    str[i - 1] = '\0';
                    printf("%d %s %s\n", ++num, "�����", str);
                    fprintf(fLexical, "%d %s %s\n", num, "�����", str);
                    ungetc(ch, fSource);
                }
            }
            else {
                str[i] = '\0';
                printf("%d %s, %s\n", ++num, "�����", str);
                fprintf(fLexical, "%d %s %s\n", num, "�����", str);
            }
        }
        else if (isDelimiter(ch)) { // ���
            char str[100];
            str[0] = ch;
            str[1] = '\0';
            printf("%d %s %s\n", ++num, "���", str);
            fprintf(fLexical, "%d %s %s\n", num, "���", str);
            if(str[0] == '.'){
                break;
            }
        }
        else {
            printf("%d %s, %c\n", ++num, "�Ƿ�", ch);
            fprintf(fLexical, "%d %s %c\n", num, "�Ƿ�", ch);
            return false;
        }
    }
    fclose(fSource); // �ر�Դ�����ļ�
    fclose(fLexical); // �رմʷ���������ļ�
    return true;
} // �ʷ��������� end

bool isEmpty(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
} // �ж��Ƿ�Ϊ�ո�

bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
} // �ж��Ƿ�Ϊ��ĸ

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
} // �ж��Ƿ�Ϊ����

bool isKeyWord(char* str) {
    for (int i = 0; i < keyWordNum; i++) {
        if (strcmp(str, keyWord[i]) == 0) {
            return true;
        }
    }
    return false;
} // �ж��Ƿ�Ϊ������

bool isOperator(char ch) {
    for (int i = 0; i < operatorNum; i++) {
        if (ch == operator[i][0]) {
            return true;
        }
    }
    return false;
} // �ж��Ƿ�Ϊ�����

bool isDelimiter(char ch) {
    for (int i = 0; i < delimiterNum; i++) {
        if (ch == delimiter[i]) {
            return true;
        }
    }
    return false;
} // �ж��Ƿ�Ϊ���
