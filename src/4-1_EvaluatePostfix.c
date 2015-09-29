/*
 * 功能：后缀表达式求值，只包含+-/*
 *
 * 作者：孙明琦
 *
 * 代码片段，直接提交函数部分即可
 */

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