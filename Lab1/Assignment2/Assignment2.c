
//Name: Sumir Mathur
//Id: 2015KUCP1017

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

int main()
{
    freopen("input.c","r",stdin);
    char c;
    int isIden=0,isNumber=0,isOperator=0,isString=0;
    long count=0;
	char operators[]="+-*/=><!&|%^?:",term[]=",;(){}";
    while(c!=EOF){
        c=getc(stdin);
        if(c=='\\'&&isString)
        {
            c=getc(stdin);
        }
        else if(c=='\"')
        {
            if(isString)
            {
                isString=false;
            }
            else
            {
                count++;
                isString=true;
            }
        }
        else if(isString)
        {
            continue;
        }
        else if(isalpha(c)||c=='_')
        {
            if(!isIden)
            {
                count++;
                isIden=true;
            }
        }
        else if(isdigit(c))
        {
            if((!isNumber&&!isIden)||c=='.')
            {
                count++;
                isNumber=true;
            }
        }
        else if(isblank(c))
        {
            isIden=isNumber=isOperator=isString=false;
        }
        else if(charOcc(operators,c))
        {
            if(!isOperator)
            {
                count++;
                isIden=isNumber=isOperator=isString=false;
                isOperator=true;
            }
        }
        else if(charOcc(term,c))
        {
            count++;
            isIden=isNumber=isOperator=isString=false;
        }
    }
    printf("%ld\n",count);
    return 0;
}
