//Name: Sumir Mathur
//Id: 2015KUCP1017

/* ~ reprsents epsilon */

#include <bits/stdc++.h>
using namespace std;

map<string,vector<string>> productions;

char first(string prod)
{
	if(prod == "~")
		return '~';
	else if(islower(prod[0]))
		return prod[0];
	else
	{	
		string symbol = "";
		symbol += prod[0];
		vector<string> temp = productions.find(symbol);
		
		for(int k=0; k<temp.size(); k++)
			first(temp[k]);
	}
	
	return 1;
		
}
 
void First(string startSymbol)
{
	map<string,vector<char> > firsts;
	map<string,vector<string> >::iterator it1 = productions.begin();
	map<string,vector<char> >::iterator it2;
	
	vector<char> set;
	
	for(int k=0; k<it1->second.size(); k++)
	{
		first(it1->second[k]);
	}
}

int main()
{
    FILE* file = freopen("input.txt","r",stdin);
    int i=0;
    string arr[10];
    string startSymbol="";
    
	map<string,vector<string> >::iterator it;
	
    while(cin>>arr[i])
    {
		
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
	
	First(startSymbol);    
	
		for(it=productions.begin(); it!=productions.end(); it++) 
		{	
			cout<<it->first<<"->";
			for(int k=0; k<it->second.size(); k++)
			{
				if(it->second[k] == "~")
					cout<<"NULL";
				else
				cout<<it->second[k]<<"|";
			}
			cout<<endl;
        }
    
    fclose(file);
    return 0;
}

