//Name: Sumir Mathur
//Id: 2015KUCP1017
//implementation of operator precedence parser
/* ~ represents epsilon and the first rule of grammar is for start symbol */

#include <bits/stdc++.h>
using namespace std;

string startSymbol="";
map<string,vector<string> > productions;

//+,-,*,/,^,%,a,$
char operatorPrecedenceTable[8][8]={        //e represents equal precedence

            /*stack    +    -   *   /   ^   %   a   $  */

            /*  + */  '>', '>','<','<','<','<','<','>',

            /*  - */  '>', '>','<','<','<','<','<','>',

            /*  * */  '>', '>','>','>','<','>','<','>',

            /*  / */  '>', '>','>','>','<','>','<','>',

            /*  ^ */  '>', '>','>','>','<','>','<','>',

            /*  % */  '>', '>','>','>','<','>','<','>',

            /*  a */  '>', '>','>','>','>','>','e','>',

            /*  $ */  '<', '<','<','<','<','<','<','>',

            };

char getPrecedence(char topOfStack, char inputSymbol)
{
    int row,column;

    if(islower(topOfStack))
        row = 6;
    else
        switch(topOfStack)
        {
            case '+': row = 0;break;
            case '-': row = 1;break;
            case '*': row = 2;break;
            case '/': row = 3;break;
            case '^': row = 4;break;
            case '%': row = 5;break;
            case '$': row = 7;break;
        }

    if(islower(inputSymbol))
        column = 6;
    else
        switch(inputSymbol)
        {
            case '+': column = 0;break;
            case '-': column = 1;break;
            case '*': column = 2;break;
            case '/': column = 3;break;
            case '^': column = 4;break;
            case '%': column = 5;break;
            case '$': column = 7;break;
            default: cout<<inputSymbol<<" is not acceptable in this parser\n";
                    return '0';
        }
    return operatorPrecedenceTable[row][column];
}

bool isOperator(char a)
{
    switch(a)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%': return true;
    }
    return false;
}

bool checkIfOperatorGrammar()
{
    map<string, vector<string> >::iterator it;
    for(it=productions.begin(); it!=productions.end(); it++)
    {
        for(int k=0; k<it->second.size(); k++)
        {
            string rhs = it->second[k];
            if(rhs == "~")
                return false;

            if(rhs.length()==1 && isupper(rhs[0]))
                return false;

            if(rhs.length()%2 != 1)
                return false;

            for(int l=0; l<rhs.length(); l++)
            {
               if(l%2 == 0)
               {
                   //check if terminal or non terminal
                   if(isOperator(rhs[l]))
                        return false;
               }
               else
               {
                   //check if operator
                   if(!isOperator(rhs[l]))
                        return false;
               }
            }
        }
    }
    return true;
}

char getSymbol(string str)
{
    map<string, vector<string> >::iterator it;

    for(it=productions.begin(); it!=productions.end(); it++)
    {
        for(int k=0; k<it->second.size(); k++)
        {
            if(str == it->second[k])
                return it->first[0];
        }
    }

    return '0';
}

string showStack(vector<char> stck)
{
    string str="";
    for(int k=0; k<stck.size(); k++)
        str+=stck[k];

    if(str == "")
        return "empty";
    return str;
}

bool isAcceptable(string input)
{
    vector<char> symbols;
    vector<char> parsingStack;
    int i=0;

    parsingStack.push_back('$');
    while(i < input.length())
    {
        if(!parsingStack.empty())
        {
            char precedence = getPrecedence(parsingStack.back(),input[i]);
            if(precedence == '0')
                return false;
            else if(precedence == '>')
            {
                //pop
                char top = parsingStack.back();
                parsingStack.pop_back();
                char symbol;
                string str="";
                if(isOperator(top))
                {
                    if(!symbols.empty())
                    {
                        str+=symbols.back(); symbols.pop_back();
                    }
                    else
                        return false;
                    str+=top;
                    if(!symbols.empty())
                    {
                        str+=symbols.back(); symbols.pop_back();
                    }
                    else
                        return false;
                    symbol = getSymbol(str);
                    if(symbol!='0')
                    {
                        symbols.push_back(symbol);
                        cout<<"string: "<<input.substr(i)<<"  Stack is: "<<showStack(parsingStack)<<"  Stack 2 is: "<<showStack(symbols)<<"  Remarks: reduce using "<<symbol<<"->"<<str<<endl;
                    }
                    else
                        return false;
                }
                else if(top == '$')
                {
                    break;
                }
                else
                {
                    str+=top;
                    symbol = getSymbol(str);
                    if(symbol!='0')
                    {
                        symbols.push_back(symbol);
                        cout<<"string: "<<input.substr(i)<<"  Stack is: "<<showStack(parsingStack)<<"  Stack 2 is: "<<showStack(symbols)<<"  Remarks: reduce using "<<symbol<<"->"<<str<<endl;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            else
            {
                //push
                parsingStack.push_back(input[i]);
                cout<<"string: "<<input.substr(i)<<"  Stack is: "<<showStack(parsingStack)<<"  Stack 2 is: "<<showStack(symbols)<<"  Remarks: shift "<<input[i]<<endl;
                i++;

            }
        }
        else
            return false;
    }
    if(input[i] == '$' && parsingStack.empty() && symbols.back() == startSymbol[0])
        return true;

    return false;
}

int main()
{
    FILE* file = freopen("inputGrammar.txt","r",stdin);
    int i=0;
    int noOfProductionRules;
    int noOfInputStrings;
    bool isCorrect = false;

    string arr[10];
    vector<string> inputStrings;

	map<string,vector<string> >::iterator it;
    cin>>noOfProductionRules;

    while(noOfProductionRules--)
    {
        cin>>arr[i];
		string symbol;
		vector<string> temp;

		int pos1 = arr[i].find("->");
		symbol = arr[i].substr(0,pos1);

        if(i==0) //first input begins with start symbol
			startSymbol = symbol;

		int pos2 = arr[i].find("|");

		if(pos2 == -1) //has only one production
		{
			temp.push_back(arr[i].substr(pos1+2));
			productions[symbol] = temp;
			i++;
			continue;
		}

		temp.push_back(arr[i].substr(pos1+2,pos2 - (pos1+2)));
		pos1 = pos2;
		pos2 = arr[i].find("|",pos1+1);

		while (pos2 != -1)
		{
			temp.push_back(arr[i].substr(pos1+1,pos2 - (pos1+1)));
			pos1=pos2;
			pos2 = arr[i].find("|",pos1+1);
		}
		temp.push_back(arr[i].substr(pos1+1));

		productions[symbol] = temp;

        i++;
	}

	i=0;
	cin>>noOfInputStrings;
	string str;
	while(noOfInputStrings--)
    {
        cin>>str;
        inputStrings.push_back(str);
    }

    cout<<"The grammar is:\n";

    for(it=productions.begin(); it!=productions.end(); it++)
    {
        cout<<it->first<<"->";
        for(int k=0; k<it->second.size(); k++)
        {
            if(it->second[k] == "~")
                cout<<"NULL";
            else
                cout<<it->second[k];
            if(k<it->second.size()-1)
                cout<<"|";
        }
        cout<<endl;
    }
    cout<<"\n";

    isCorrect = checkIfOperatorGrammar();
    if(isCorrect)
    {
        cout<<"The grammar is correct\n\n";
        for(int g=0; g<inputStrings.size(); g++)
        {
            cout<<"The input string is "<<inputStrings[g]<<endl;
            if(isAcceptable(inputStrings[g]))
                cout<<"\nThe string is acceptable";
            else
                cout<<"\nThe string is not acceptable";

            cout<<"\n-------------------------------\n\n";
        }
    }
    else
        cout<<"The grammar is incorrect";

    fclose(file);
    return 0;
}


