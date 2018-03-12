//Name: Sumir Mathur
//Id: 2015KUCP1017

//using ^ in input file to depict epsilon

#include <bits/stdc++.h>
using namespace std;

int main()
{
    FILE* file = freopen("input.txt","r",stdin);
    int i=0;
	string a;
    char arr[15][30];    
	char *startSymbol;
	
	
    while(cin>>arr[i])
    {
		int j=0;
		char *prod[5];
		for(int k=0; k<5; k++)
			prod[k] = NULL;
			
		int hasRecursion = 0;
		
		startSymbol = strtok(arr[i], "->");
		
		char* temp = strtok(NULL, "->");
		prod[j] = strtok(temp, "|");
		
		while (prod[j] != NULL) 
		{
			if(prod[j][0] == '^') //to convert to epsilon
			{
				prod[j] = "NULL";
			}
			
			if(prod[j][0] == startSymbol[0])
			{
				 hasRecursion = 1;
				 prod[j] += 1;
				 cout<<startSymbol<<"->"<<prod[j]<<startSymbol<<'\''<<endl;
				 cout<<startSymbol<<'\''<<"->"<<"NULL"<<endl;	
				 prod[j] = NULL;
			}
				
			prod[++j] = strtok(NULL, "|");
		}
		
		
		if(hasRecursion)
		{
			for(int k=0; k<5; k++)
			{
				if(prod[k])
				{		
					cout<<startSymbol<<'\''<<"->"<<prod[k]<<startSymbol<<'\''<<"\n";
				}
			}
		}
		else if(!hasRecursion)
		{
			for(int k=0; k<5; k++)
				if(prod[k])
					cout<<startSymbol<<"->"<<prod[k]<<"\n";
		}
		
		
		cout<<endl;
		
		i++;
	}    
    
    fclose(file);
    return 0;
}
