/* 
 * by スノル
 */
#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

/* Your function will be put here */

ElementType stack[Max_Expr];
int top;

void push(ElementType x) {
    stack[top] = x;
    top++;
}

ElementType pop() {
    if (top <= 0)
        return Infinity;
    top--;
    return stack[top];
}

ElementType EvalPostfix(char *expr)
{

    int i;
    ElementType x, s, t;
    ElementType decimal;
    int negative, digit;

    i = x = top = decimal = negative = digit = 0;
    while (expr[i]) {
        switch (expr[i]) {
            case '+':
                if (expr[i+1] && expr[i+1] != ' ')
                    break;
                if ((t = pop()) == Infinity)
                    return Infinity;
                if ((s = pop()) == Infinity)
                    return Infinity;
                s += t;
                push(s);
                break;
            case '-':
                if (expr[i+1] && expr[i+1] != ' ') {
                    negative = 1;
                    break;
                }
                if ((t = pop()) == Infinity)
                    return Infinity;
                if ((s = pop()) == Infinity)
                    return Infinity;
                s -= t;
                push(s);
                break;
            case '*':
                if ((t = pop()) == Infinity)
                    return Infinity;
                if ((s = pop()) == Infinity)
                    return Infinity;
                s *= t;
                push(s);
                break;
            case '/':
                if ((t = pop()) == Infinity)
                    return Infinity;
                if ((s = pop()) == Infinity)
                    return Infinity;
                if (t == 0)
                    return Infinity;
                s /= t;
                push(s);
                break;
            case '.':
                decimal = 10.0;
                break;
            case ' ':
                if (!digit)
                    break;
                if (negative)
                    x = -x;
                push(x);
                x = negative = decimal = digit = 0;
                break;
            case '0': case '1': case '2': case '3':
            case '4': case '5': case '6': case '7':
            case '8': case '9':
                digit = 1;
                t = expr[i] - '0';
                if (decimal) {
                    x += t / decimal;
                    decimal *= 10;
                } else {
                    x *= 10;
                    x += t;
                }
                break;
            default:
                return Infinity;
        }
        i++;
    }

    if (x != 0) {
        if (top == 0)
            return x;
        else
            return Infinity;
    }

    if (top == 1)
        return pop();
    return Infinity;
}
