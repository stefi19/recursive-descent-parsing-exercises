#include <stdio.h>
#include <stdlib.h>
#define NUMBER 256
#define MAP 257
#define INC 258
#define DEC 259
#define FILTER 260
#define ODD 261
#define EVEN 262
#define CONCAT 263
#define MAX_LIST 1000

typedef struct {
    int v[MAX_LIST];
    int len;
} List;

int yylval;
int yylex();
int symbol;

// prototypes of functions
List E();
List E1(List value);
List L();
List Enum();
void Z();

List empty_list();
void add_end(List *list, int value);
List concat(List a, List b);
List map_inc(List list);
List map_dec(List list);
List filter_odd(List list);
List filter_even(List list);
void print_list(List list);

void next_symbol(){
    symbol=yylex();
}

void error()
{
    printf("Syntax Error\n");
    exit(1);
}

List empty_list()
{
    List list;
    list.len=0;
    return list;
}

void add_end(List *list, int value)
{
    if (list->len>=MAX_LIST)
        error();
    list->v[list->len]=value;
    list->len++;
}

List concat(List a, List b)
{
    List result=empty_list();
    int i;
    if (a.len+b.len>MAX_LIST)
        error();
    for (i=0; i<a.len; i++)
        add_end(&result, a.v[i]);
    for (i=0; i<b.len; i++)
        add_end(&result, b.v[i]);
    return result;
}

List map_inc(List list)
{
    List result=empty_list();
    int i;
    for (i=0; i<list.len; i++)
        add_end(&result, list.v[i]+1);
    return result;
}

List map_dec(List list)
{
    List result=empty_list();
    int i;
    for (i=0; i<list.len; i++)
        add_end(&result, list.v[i]-1);
    return result;
}

List filter_odd(List list)
{
    List result=empty_list();
    int i;
    for (i=0; i<list.len; i++)
        if (list.v[i]%2!=0)
            add_end(&result, list.v[i]);
    return result;
}

List filter_even(List list)
{
    List result=empty_list();
    int i;
    for (i=0; i<list.len; i++)
        if (list.v[i]%2==0)
            add_end(&result, list.v[i]);
    return result;
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
    print_list(E());
    if (symbol!='\n' && symbol!=0)
    {
        error();
    }
}

List E()
{
    return E1(L());
}

List E1(List value)
{
    if (symbol==CONCAT)
    {
        next_symbol();
        return concat(value, E());
    }
    return value;
}

List L()
{
    if (symbol==MAP)
    {
        next_symbol();
        if (symbol==INC)
        {
            next_symbol();
            return map_inc(L());
        }
        else if (symbol==DEC)
        {
            next_symbol();
            return map_dec(L());
        }
        else
            error();
    }
    else if (symbol==FILTER)
    {
        next_symbol();
        if (symbol==ODD)
        {
            next_symbol();
            return filter_odd(L());
        }
        else if (symbol==EVEN)
        {
            next_symbol();
            return filter_even(L());
        }
        else
            error();
    }
    else if (symbol=='(')
    {
        List value;
        next_symbol();
        value=E();
        if (symbol==')')
        {
            next_symbol();
            return value;
        }
        else
            error();
    }
    else if (symbol=='[')
    {
        List value=empty_list();
        next_symbol();
        if (symbol!=']')
            value=Enum();
        if (symbol==']')
        {
            next_symbol();
            return value;
        }
        else
            error();
    }
    else
        error();
    return empty_list();
}

List Enum()
{
    List result=empty_list();
    if (symbol==NUMBER)
    {
        add_end(&result, yylval);
        next_symbol();
    }
    else
        error();

    while(symbol==',')
    {
        next_symbol();
        if (symbol==NUMBER)
        {
            add_end(&result, yylval);
            next_symbol();
        }
        else
            error();
    }
    return result;
}

void print_list(List list)
{
    int i;
    printf("[");
    for (i=0; i<list.len; i++)
    {
        if (i>0)
            printf(", ");
        printf("%d", list.v[i]);
    }
    printf("]\n");
}

int yywrap(void) { return 1; }
