//Name: Sumir Mathur
//Id: 2015KUCP1017

#include <bits/stdc++.h>
using namespace std;

const int ALPHABET_SIZE = 256;
int symbolList[26] = {0};

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool end;
};
 
struct TrieNode *getNode(void)
{
    struct TrieNode *p =  new TrieNode;
 
    p->end = false;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        p->children[i] = NULL;
 
    return p;
}
 
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *p = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i];
        if (!p->children[index])
        {
			p->children[index] = getNode();
		}
        p = p->children[index];
    }
 
    p->end = true;
}

string makeString(char c){

	string str;
	str += c;
	return str; 
}

string getSymbol()
{
	string str = "'";
	for(int i=25; i>=0; i--)
	{
		if(symbolList[i] == 0)
		{
			char temp = i + 'A';
			str = temp + str;
			symbolList[i] = 1;
			break;
		}
	}
	return str;
}

string leftFactoring(struct TrieNode* root, vector<string>& prod, string value)
{
    vector<string> newProd;
    for (int i = 0; i < ALPHABET_SIZE; i++) 
    {
        if (root->children[i]) 
        {
            string a = leftFactoring(root->children[i],prod,makeString(i));
            if(a != "") newProd.push_back(a);
        }
    }
    
    if(newProd.size() == 0)
		return value;
    else if(newProd.size() == 1 && !root->end)
    {
		return value + newProd[0];
	}
    else 
	{   
		string symbol = getSymbol();
		string productions = "";
        int i=0;
        for(i=0;i<newProd.size()-1;i++) 
			productions += newProd[i] + " | ";
		
		productions += newProd[i] + (root->end ? " | NULL" : "");
        
        if(value == "") return productions;
        else
        {
            string newProduction = symbol + " -> " + productions;
            prod.push_back(newProduction);
            
            return value + symbol;
        }
    
	}
	
	return value;		
}
 
int main()
{
    FILE* file = freopen("inputNonDeterministic.txt","r",stdin);
    int i=0;
    string arr[15];    
	
    while(cin>>arr[i])
    {
		struct TrieNode *root = getNode();
		
		string startSymbol;
		vector<string> prod;
		
		int pos1 = arr[i].find("->");
		startSymbol = arr[i].substr(0,pos1);
				
		int pos2 = arr[i].find("|");
		
		if(pos2 == -1) //has only one production therefore no ambiguity
		{
			cout<<arr[i]<<"\n";
			continue;
		}
		
		insert(root, arr[i].substr(pos1+2,pos2 - (pos1+2)));
		pos1 = pos2;
		pos2 = arr[i].find("|",pos1+1);
	
		while (pos2 != -1) 
		{	
			insert(root, arr[i].substr(pos1+1,pos2 - (pos1+1)));
			pos1=pos2;
			pos2 = arr[i].find("|",pos1+1);	
		}
		insert(root, arr[i].substr(pos1+1));
	
		prod.push_back(startSymbol + " -> " + leftFactoring(root,prod,""));
		
		for(int k=prod.size()-1; k >= 0; k--) 
        cout<<prod[k]<<endl;       
        
        i++;	
	}    
    
    fclose(file);
    return 0;
}

