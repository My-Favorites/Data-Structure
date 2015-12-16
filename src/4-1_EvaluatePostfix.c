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

ElementType EvalPostfix(char *expr)
{
    double operand[Max_Expr * 4] = {0};
    int  operand_head = 0;
    while (*expr)
    {
        switch (*expr)
        {
        case '+':
            if (expr[1] == ' ' || expr[1] == '\0')
            {
                operand_head -= 2;
                if (operand_head < 0)
                {
                    return Infinity;
                }
                operand[operand_head] += operand[operand_head + 1];
                operand_head++;
            }
            else
            {
                int count = sscanf(expr, "%lf", operand + operand_head);
                if (count != 1)
                {
                    return Infinity;
                }
                do
                {
                    expr++;
                } while (*expr && *expr != ' ');
                operand_head++;
            }
            break;
        case '-':
            if (expr[1] == ' ' || expr[1] == '\0')
            {
                operand_head -= 2;
                if (operand_head < 0)
                {
                    return Infinity;
                }
                operand[operand_head] -= operand[operand_head + 1];
                operand_head++;
            }
            else
            {
                int count = sscanf(expr, "%lf", operand + operand_head);
                if (count != 1)
                {
                    return Infinity;
                }
                while (*expr && *expr != ' ')
                {
                    expr++;
                }
                operand_head++;
            }
            break;
        case '*':
            operand_head -= 2;
            if (operand_head < 0)
            {
                return Infinity;
            }
            operand[operand_head] *= operand[operand_head + 1];
            operand_head++;
            break;
        case '/':
            operand_head -= 2;
            if (operand_head < 0)
            {
                return Infinity;
            }
            if (operand[operand_head + 1] == 0.0)
            {
                return Infinity;
            }
            operand[operand_head] /= operand[operand_head + 1];
            operand_head++;
            break;
        case'0':case '1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':case'.':
        {
            int count = sscanf(expr, "%lf", operand + operand_head);
            if (count != 1)
            {
                return Infinity;
            }
            do
            {
                expr++;
            } while (*expr && *expr != ' ');
            operand_head++;
            break;
        }
        case' ':
            break;
        default:
            return Infinity;
        }
        expr++;
    }
    if (operand_head != 1)
    {
        return Infinity;
    }
    return operand[0];
}
