#include <cstdio>
#include <iostream>
using namespace std;
const int maxSize = 20;
int getPriority(char i) { // 得到符号的优先级
    switch (i) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
}
int infixToPostfix(char infix[], char s2[]) {
    char s1[maxSize];
    // 符号堆栈
    int top1 = -1, top2 = -1;
    // top1是符号堆栈的标号, top2是结果数组的标号
    int stackMax = 0;
    // 记录堆栈最大处的标号
    int i = 0;
    // 指向原数组的标号
    while (infix[i] != '\0')
    // 控制循环的原数组循环的末尾
    {
        if (('a' <= infix[i] && infix[i] <= 'z') ||
                (('0' <= infix[i] && infix[i] <= '9')))
        // 如果选到数字或者字母, 直接写入结果数组
        {
            s2[++top2] = infix[i];
            i++;
        } else if (infix[i] == '(')
        // 如果遇到左括号, 直接写入符号堆栈
        {
            s1[++top1] = '(';
            if (top1 > stackMax)
                stackMax = top1;
            i++;
        } else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' ||
                             infix[i] == '/')
        // 如果遇到运算符则分类讨论
        {
            if (top1 == -1 || s1[top1] == '(' ||
                    getPriority(infix[i]) > getPriority(s1[top1]))
            // 若在栈底, 在括号底, 或者操作符优先级高, 则操作符入栈
            {
                s1[++top1] = infix[i];
                if (top1 > stackMax)
                    stackMax = top1;
                i++;
            } else // 否则出栈
                s2[++top2] = s1[top1--];
        } else if (infix[i] == ')')
        // 如果遇到右括号, 则将其与对应左括号之间的符号出栈
        {
            while (s1[top1] != '(')
                s2[++top2] = s1[top1--];
            top1--;
            i++;
        }
    }
    while (top1 != -1)
        // 这里将堆栈中剩余的符号推出堆栈
        s2[++top2] = s1[top1--];
    return stackMax + 1;
    // 这里top1是堆栈标号, 必须+1才是数目
}

int top2 = -1;
char s2[maxSize];
char infix[maxSize];

int main() {
    scanf("%s", infix);
    cout << infixToPostfix(infix, s2) << endl;
    int i = 0;
    while (s2[i] != '\0')
        cout << s2[i++];
    cout << endl;
    return 0;
}