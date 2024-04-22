#include"pl0.h"

int main(void) {
    init(); // 初始化
    fsource = fopen("source.txt", "r"); // 读取源程序文件
    flexical = fopen("lexical.txt", "w"); // 词法分析结果文件
    if (!fsource) {
        printf("Can't open the source file!\n");
        return -1;
    }
    if (!flexical) {
        printf("Can't open the lexical file!\n");
        return -1;
    }
    ll = 0; // 当前行的长度
    cc = 0; // 当前字符的索引号
    ch = ' '; // 当前读入的字符
    lexicalAnalysis(); // 词法分析
    return 0;
}

void init() { // 初始化函数 start
    /* 设置单字符符号值 */
    for (int i = 0; i < 256; i++) {
        ssym[i] = nul;
    }
    ssym['+'] = plus;
    ssym['-'] = minus;
    ssym['*'] = times;
    ssym['/'] = slash;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['='] = eql;
    ssym[','] = comma;
    ssym['.'] = period;
    ssym['#'] = neq;
    ssym[';'] = semicolon;

    /* 设置保留字名字,按照字母顺序，便于折半查找 */
    strcpy(keyWord[0], "begin");
    strcpy(keyWord[1], "call");
    strcpy(keyWord[2], "const");
    strcpy(keyWord[3], "do");
    strcpy(keyWord[4], "end");
    strcpy(keyWord[5], "if");
    strcpy(keyWord[6], "Jenny");
    strcpy(keyWord[7], "name");
    strcpy(keyWord[8], "odd");
    strcpy(keyWord[9], "procedure");
    strcpy(keyWord[10], "read");
    strcpy(keyWord[11], "studentid");
    strcpy(keyWord[12], "then");
    strcpy(keyWord[13], "var");
    strcpy(keyWord[14], "while");
    strcpy(keyWord[15], "write");

    /* 设置保留字符号值 */
    wsym[0] = beginsym;
    wsym[1] = callsym;
    wsym[2] = constsym;
    wsym[3] = dosym;
    wsym[4] = endsym;
    wsym[5] = ifsym;
    wsym[6] = jennysym;
    wsym[7] = namesym;
    wsym[8] = oddsym;
    wsym[9] = procsym;
    wsym[10] = readsym;
    wsym[11] = studentidsym;
    wsym[12] = thensym;
    wsym[13] = varsym;
    wsym[14] = whilesym;
    wsym[15] = writesym;

    /* 设置运算符号 */
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

    /* 设置界符号 */
    strcpy(delimiter[0], "(");
    strcpy(delimiter[1], ")");
    strcpy(delimiter[2], ",");
    strcpy(delimiter[3], ";");
    strcpy(delimiter[4], ".");
} // 初始化函数 end

int lexicalAnalysis() { // 词法分析函数 start
    index = 0; // 词法分析结果的索引号
    int count = 0; // 计数器
    while (getsym() != -1) { // 词法分析
        if (sym == nul) { // 非法字符
            printf("%d %s %s   ", ++index, "非法", str);
            fprintf(flexical, "%d %s %s\n", index, "非法", str);
        }
        else if (sym == ident) { // 标识符
            printf("%d %s %s   ", ++index, "标识符", a);
            fprintf(flexical, "%d %s %s\n", index, "标识符", a);
        }
        else if (sym == number) { // 数字
            printf("%d %s %d   ", ++index, "数字", num);
            fprintf(flexical, "%d %s %d\n", index, "数字", num);
        }
        else if (sym >= 3 && sym <= 13) { // 运算符
            printf("%d %s %s   ", ++index, "运算符", operator[sym - 3]);
            fprintf(flexical, "%d %s %s\n", index, "运算符", operator[sym - 3]);
        }
        else if (sym >= 14 && sym <= 18) { // 界符
            printf("%d %s %s   ", ++index, "界符", delimiter[sym - 14]);
            fprintf(flexical, "%d %s %s\n", index, "界符", delimiter[sym - 14]);
        }
        else if (sym >= 19 && sym <= 34) { // 保留字
            printf("%d %s %s   ", ++index, "保留字", keyWord[sym - 19]);
            fprintf(flexical, "%d %s %s\n", index, "保留字", keyWord[sym - 19]);
        }
        if (sym == period) { // 词法分析结束
            break;
        }
        if((++count) % 5 == 0) { // 每行输出5个词法分析结果
            printf("\n");
        }
    }
    fclose(fsource); // 关闭源程序文件
    fclose(flexical); // 关闭词法分析结果文件
}

int getsym() { // 词法分析函数 start
    int i, j, k;
    while (ch == ' ' || ch == 10 || ch == 9) { // 跳过空格、换行、制表符
        getchdo; // 读取下一个字符
    }

    if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') { // 处理关键字或标识符
        k = 0;
        do {
            if (k < al) {
                str[k++] = ch;
            }
            getchdo; // 读取下一个字符
        }
        while (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9');
        str[k] = 0;
        strcpy(a, str); // 保存当前读取的标识符
        i = 0;
        j = norw - 1;
        do { // 二分查找
            k = (i + j) / 2;
            if (strcmp(a, keyWord[k]) <= 0) {
                j = k - 1;
            }
            if (strcmp(a, keyWord[k]) >= 0) {
                i = k + 1;
            }
        }
        while (i <= j);
        if (i - 1 > j) { // 是保留字
            sym = wsym[k];
        }
        else { // 标识符
            sym = ident;
        }
    }
    else {
        if (ch >= '0' && ch <= '9') { // 处理数字
            k = 0;
            num = 0;
            sym = number;
            do {
                num = 10 * num + ch - '0';
                k++;
                getchdo; // 读取下一个字符
            }
            while (ch >= '0' && ch <= '9');
        }
        else { // 处理运算符
            if (ch == ':') { // 处理赋值符号
                str[0] = ch;
                getchdo; // 读取下一个字符
                if (ch == '=') {
                    sym = becomes; // :=
                }
                else {
                    str[1] = ch;
                    str[2] = 0;
                    sym = nul; // 非法字符
                }
            }
            else {
                if (ch == '<') {
                    getchdo; // 读取下一个字符
                    if (ch == '=') {
                        sym = leq; // <=
                        getchdo; // 读取下一个字符
                    }
                    else {
                        sym = lss; // <
                    }
                }
                else {
                    if (ch == '>') {
                        getchdo; // 读取下一个字符
                        if (ch == '=') {
                            sym = geq; // >=
                            getchdo; // 读取下一个字符
                        }
                        else {
                            sym = gtr; // >
                        }
                    }

                    else {
                        if (!(ch & 0x80)) { // 单字符
                            sym = ssym[ch];
                            if (sym != period) {
                                getchdo; // 读取下一个字符
                            }
                        }
                        else { // 处理中文字符
                            k = 0;
                            while (ch & 0x80) {
                                str[k++] = ch;
                                getchdo; // 读取下一个字符
                            }
                            str[k] = 0;
                            sym = nul; // 非法字符
                        }
                    }
                }
            }
        }
    }
    return 0;
} // 词法分析函数 end

int getch() { // 读取一行
    if (cc == ll) { // 当前行读取完毕, 读取下一行
        if (feof(fsource)) {
            return -1;
        }
        ll = 0;
        cc = 0;
        ch = ' ';
        while (ch != 10) {
            if (fscanf(fsource, "%c", &ch) == EOF) {
                line[ll] = 0;
                break;
            }
            line[ll++] = ch;
        }
    }
    ch = line[cc++];
    return 0;
}
