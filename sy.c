#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 1000
#define STRING_SIZE 10000

bool check_precedence(char , char);
void read_expression(char *, char *);
void push(char, char *, int *);
char pop(char *, int *);
bool isop(char);
bool associativity(char);


int main()
{
    char *output;
    output = malloc(STRING_SIZE);

    char in[] = "3+4*2/(1-5)^2^3";

    read_expression(in, output);
    printf("%s", output);

}


bool check_precedence(char f_o, char s_o)
{
    // Returns True if f_o Has Greater Or Equal Precedence Than s_o
    if (f_o == s_o)
        return true;
    else if (f_o == '^')
        return true;
    else if(s_o != '^' &&  (f_o == '*' || f_o == '/'))
        return true;
    else if(s_o != '^' && s_o != '*' && s_o != '/' && f_o == '+' || f_o == '-')
        return true;
    else
        return false;
}   

void read_expression(char *input, char *output)
{
    char *operator_stack = malloc(STACK_SIZE);
    char ch;
    int top = -1;
    int pos = 0, out_pos = 0;
    push('\0', operator_stack, &top);

    while(input[pos] != '\0')
    {
        if(isdigit(input[pos]))
            output[out_pos++] = input[pos];

        else if(isop(input[pos]))
        {

           if(operator_stack[top] == '\0')
            {
                push(input[pos], operator_stack, &top);
            // printf("%c, %d",operator_stack[top], top);

            }

            else
            {
                while(operator_stack[top] != 0 && operator_stack[top] != ')' && associativity(input[pos]) &&  check_precedence(operator_stack[top], input[pos]))
                {
                    output[out_pos++] = pop(operator_stack, &top);
                }

                push(input[pos],operator_stack, &top);

            }
        }
        
        else if (input[pos] == '(')
            push(input[pos], operator_stack, &top);
        
        else if(input[pos] == ')')
        {
            while(operator_stack[top] != '\0' && operator_stack[top] != '(')
            {
                ch = pop(operator_stack, &top);
                if(ch == '\0')
                {
                    printf("Mismatched Parentheses");
                    return;
                }
                output[out_pos++] = ch;
                    
            }

           pop(operator_stack, &top);
        }
        pos ++;
    }

    while (operator_stack[top] != '\0')
        output[out_pos++] = pop(operator_stack, &top);
    
}

void push(char value, char *stack, int *top)
{
    stack[++(*top)] = value;
}

char pop(char *stack, int *top)
{
    char tmp = stack[*top];
    stack[(*top)--] = '\0';
    
    return tmp;
}

bool isop(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return true;
    else
        return false;
}

bool associativity(char op)
{
    if (op == '^')
        return false;
    else
        return true;
}