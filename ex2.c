#include <stdio.h>
#include <stdlib.h>
#define NUMBER 256
#define HEAD 257
#define LENGTH 258
#define TAIL 259
#define CONCAT 260
#define MAX_LIST 1000

typedef struct {
    int v[MAX_LIST];
    int len;
} List;

int yylval;
int yylex();
int symbol;

// prototypes of functions
List LE();
List LE1(List value);
List L();
int IE();
List Enum();
void Z();

List empty_list();
void add_end(List *list, int value);
List cons(int value, List list);
List concat(List a, List b);
List tail_list(List list);
int head_list(List list);
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

List cons(int value, List list)
{
    List result=empty_list();
    int i;
    if (list.len+1>MAX_LIST)
        error();
    result.v[0]=value;
    result.len=1;
    for (i=0; i<list.len; i++)
        result.v[i+1]=list.v[i];
    result.len=list.len+1;
    return result;
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

List tail_list(List list)
{
    List result=empty_list();
    int i;
    if (list.len==0)
        error();
    for (i=1; i<list.len; i++)
        add_end(&result, list.v[i]);
    return result;
}

int head_list(List list)
{
    if (list.len==0)
        error();
    return list.v[0];
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
    if (symbol==HEAD || symbol==LENGTH || symbol==NUMBER)
    {
        int value=IE();
        if (symbol==':')
        {
            next_symbol();
            List result=cons(value, L());
            result=LE1(result);
            print_list(result);
        }
        else
            printf("%d\n", value);
    }
    else
        print_list(LE());

    if (symbol!='\n' && symbol!=0)
    {
        error();
    }
}

List LE()
{
    return LE1(L());
}

List LE1(List value)
{
    if (symbol==CONCAT)
    {
        next_symbol();
        return concat(value, LE());
    }
    return value;
}

List L()
{
    if (symbol==TAIL)
    {
        next_symbol();
        return tail_list(LE());
    }
    else if (symbol=='(')
    {
        List value;
        next_symbol();
        value=LE();
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
    else if (symbol==NUMBER || symbol==HEAD || symbol==LENGTH)
    {
        int value=IE();
        if (symbol==':')
        {
            next_symbol();
            return cons(value, L());
        }
        else
            error();
    }
    else
        error();
    return empty_list();
}

int IE()
{
    if (symbol==NUMBER)
    {
        int value=yylval;
        next_symbol();
        return value;
    }
    else if (symbol==HEAD)
    {
        List value;
        next_symbol();
        value=LE();
        return head_list(value);
    }
    else if (symbol==LENGTH)
    {
        List value;
        next_symbol();
        value=LE();
        return value.len;
    }
    else if (symbol=='(')
    {
        int value;
        next_symbol();
        value=IE();
        if (symbol==')')
        {
            next_symbol();
            return value;
        }
        else
            error();
    }
    else
        error();
    return 0;
}

List Enum()
{
    List result=empty_list();
    add_end(&result, IE());
    while(symbol==',')
    {
        next_symbol();
        add_end(&result, IE());
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
