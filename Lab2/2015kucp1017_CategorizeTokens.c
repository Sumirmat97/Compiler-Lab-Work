//Name: Sumir Mathur
//Id: 2015KUCP1017

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define true 1
#define false 0

int charOcc(char *s,char c)
{
    int i,count=0;
    for (i = 0; s[i] != '\0'; i++) {
      if (s[i] == c)
         count++;
   }
   return count;
}

void clearTokenField(char str[])
{
    int i;
    for(i=0; i<strlen(str); i++)
    {
        str[i] = '\0';

    }
}

void insertInToken(char str[],int index, char c)
{
    str[index] = c;
    str[index+1] = '\0';
}

int strIsKeyword(char str[], char *Keywords[])
{
    int i;
    for(i=0; i<32; i++)
    {
        if(strcmp(str,Keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int isIden=0, isNumber=0, isOperator=0, isString=0, isTerminal=0, isKeyword=0;

void analyse(char str[], int *stringIndex, char *Keywords[])
{
    if(strIsKeyword(str,Keywords))
        isKeyword = true;

    if(isNumber)
        printf("%s is a Number\n",str);

    if(isOperator)
        printf("%s is an Operator\n",str);

    if(isTerminal)
        printf("%s is a Terminal\n",str);

    if(isString)
        printf("%s is a String\n",str);

    if(isKeyword)
        printf("%s is a Keyword\n",str);
    else if(isIden)
        printf("%s is an Identifier\n",str);

    isIden=isNumber=isOperator=isString=isTerminal=isKeyword=false;

    clearTokenField(str);
    *stringIndex = 0;
}

int main()
{
    FILE* file = freopen("input.c","r",stdin);
    char c;

    char str[25];
    int stringIndex = 0;
    char operators[]="+-*/=><!&|%^?:~#",term[]=",;(){}[]";
    char *Keywords[] = { "auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char",
                        "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default",
                        "goto", "sizeof", "volatile", "do", "if", "static", "while"};

    int i;

	for(i=0; i<25; i++)
	    str[i] = '\0';

    while((c = getc(stdin)) != EOF){

        if(c=='\\'&&isString)
        {
            insertInToken(str,stringIndex,c);
            stringIndex++;
            c=getc(stdin);
        }

        else if(c=='\"' || c=='\'')
        {
            if(isString)
            {
                isString=false;
                insertInToken(str,stringIndex,c);
                stringIndex++;

                printf("%s is a String\n",str);
                clearTokenField(str);
                stringIndex = 0;
            }
            else
            {
                isString=true;
            }
        }

        else if(isString)
        {
            insertInToken(str,stringIndex,c);
            stringIndex++;
            continue;
        }

        else if(isalpha(c)||c=='_')
        {
            if(!isIden)
            {
                analyse(str,&stringIndex,Keywords);
                isIden=true;
            }
        }

        else if(isdigit(c))
        {
            if((!isNumber&&!isIden))
            {
                analyse(str,&stringIndex,Keywords);
                isNumber=true;
            }
        }

        else if(isblank(c) || c == '\n')
        {
            analyse(str,&stringIndex,Keywords);
        }

        else if(charOcc(operators,c) || c=='.' && isIden)  //. is used in the case of structure objects accessing their members
        {

            if(!isOperator)
            {
                analyse(str,&stringIndex,Keywords);
                isIden=isNumber=isOperator=isString=false;
                isOperator=true;
            }
        }

        else if(charOcc(term,c))
        {
            analyse(str,&stringIndex,Keywords);
            isIden=isNumber=isOperator=isString=false;
            isTerminal = true;

        }

        if(!isblank(c) && c != '\n')
        {
            insertInToken(str,stringIndex,c);
            stringIndex++;
        }
    }

    fclose(file);
    return 0;
}