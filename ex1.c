#include <stdio.h>
#include <stdlib.h>
#define NUMBER 256
#define MAX_DEGREE 1000

typedef struct {
    int coef[MAX_DEGREE + 1];
} Polynomial;

int yylval;
int yylex();
int symbol;

// prototypes of functions
Polynomial E();
Polynomial E1(Polynomial value);
Polynomial T();
Polynomial M();
void Z();

Polynomial zero_poly();
Polynomial add_poly(Polynomial a, Polynomial b);
Polynomial sub_poly(Polynomial a, Polynomial b);
Polynomial monom(int coef, int exp);
void print_poly(Polynomial p);

void next_symbol(){
    symbol=yylex();
}

void error()
{
    printf("Syntax Error\n");
    exit(1);
}

Polynomial zero_poly()
{
    Polynomial p;
    int i;
    for (i=0; i<=MAX_DEGREE; i++)
        p.coef[i]=0;
    return p;
}

Polynomial add_poly(Polynomial a, Polynomial b)
{
    Polynomial result=zero_poly();
    int i;
    for (i=0; i<=MAX_DEGREE; i++)
        result.coef[i]=a.coef[i]+b.coef[i];
    return result;
}

Polynomial sub_poly(Polynomial a, Polynomial b)
{
    Polynomial result=zero_poly();
    int i;
    for (i=0; i<=MAX_DEGREE; i++)
        result.coef[i]=a.coef[i]-b.coef[i];
    return result;
}

Polynomial monom(int coef, int exp)
{
    Polynomial p=zero_poly();
    if (exp<0 || exp>MAX_DEGREE)
        error();
    p.coef[exp]=coef;
    return p;
}

int main(){
    next_symbol();
    while(symbol!=0)
    {
        Z();
        next_symbol();
    }
    return 0;
}

void Z()
{
    Polynomial result=E();
    print_poly(result);
    if (symbol!='\n' && symbol!=0)
    {
        error();
    }
}

Polynomial E()
{
    return E1(T());
}

Polynomial E1(Polynomial value)
{
    if (symbol=='\n' || symbol==')' || symbol==0)
        return value;
    else
    {
        if (symbol=='+')
        {
            next_symbol();
            return E1(add_poly(value, T()));
        }
        else if (symbol=='-')
        {
            next_symbol();
            return E1(sub_poly(value, T()));
        }
        else
            error();
    }
    return value;
}

Polynomial T()
{
    if (symbol=='(')
    {
        next_symbol();
        Polynomial value=E();
        if (symbol==')')
        {
            next_symbol();
            return value;
        }
        else
            error();
    }
    else
        return M();
    return zero_poly();
}

Polynomial M()
{
    if (symbol==NUMBER)
    {
        int coef=yylval;
        int exp=0;
        next_symbol();

        if (symbol=='Y')
        {
            exp=1;
            next_symbol();
            if (symbol=='^')
            {
                next_symbol();
                if (symbol==NUMBER)
                {
                    exp=yylval;
                    next_symbol();
                }
                else
                    error();
            }
        }
        return monom(coef, exp);
    }
    else if (symbol=='Y')
    {
        int exp=1;
        next_symbol();
        if (symbol=='^')
        {
            next_symbol();
            if (symbol==NUMBER)
            {
                exp=yylval;
                next_symbol();
            }
            else
                error();
        }
        return monom(1, exp);
    }
    else
        error();
    return zero_poly();
}

void print_poly(Polynomial p)
{
    int i;
    int first=1;
    for (i=MAX_DEGREE; i>=0; i--)
    {
        if (p.coef[i]!=0)
        {
            int coef=p.coef[i];
            int abs_coef=coef;
            if (abs_coef<0)
                abs_coef=-abs_coef;

            if (first)
            {
                if (coef<0)
                    printf("- ");
                first=0;
            }
            else
            {
                if (coef<0)
                    printf(" - ");
                else
                    printf(" + ");
            }

            if (i==0)
                printf("%d", abs_coef);
            else if (i==1)
            {
                if (abs_coef==1)
                    printf("Y");
                else
                    printf("%d Y", abs_coef);
            }
            else
            {
                if (abs_coef==1)
                    printf("Y ^ %d", i);
                else
                    printf("%d Y ^ %d", abs_coef, i);
            }
        }
    }
    if (first)
        printf("0");
    printf("\n");
}

int yywrap(void) { return 1; }
