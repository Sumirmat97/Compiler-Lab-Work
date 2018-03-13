//Name: Sumir Mathur
//Id: 2015KUCP1017
//check if the given grammar is LL1 or not

/* ~ represents epsilon and the first rule of grammar is for start symbol */

#include <bits/stdc++.h>
using namespace std;

string startSymbol="";
map<string,vector<string> > productions;
map<string,set<char> > firsts; //contains set of FIRST of all symbols
map<string,set<char> > follows; //contains set of FOLLOW of all symbols
vector<string> visited;
map<pair<char,char> ,string > predictiveParsingTable;

set<char> first(string symbol, vector<string> prods)
{
    set<char> temp;
    set<char>::iterator itTemp = temp.begin();

    if(find(visited.begin(), visited.end(), symbol) != visited.end())
    {
        map<string, set<char> >::iterator it2;
        it2 = firsts.find(symbol);
        if(it2 != firsts.end())
            temp.insert(it2->second.begin(),it2->second.end());
        return temp;
    }
    visited.push_back(symbol);
    vector<string> tempProds; //to keep productions having same non terminals as the symbol on Lhs to stop infinite recursion

    for(int k=0; k<prods.size(); k++)
    {
        int l = 0;
        for(l=0; l<prods[k].length(); l++)
        {
            if(prods[k][l]>=65 && prods[k][l]<=90)
            {
                map<string, vector<string> >::iterator it;
                set<char> s;
                set<char>::iterator it2;

                string Lhs = "";
                Lhs += prods[k][l];
                if(Lhs == symbol) //if the symbol itself comes in the production delay the substring of that production to see if the first of that symbol has ~ or not
                {
                    tempProds.push_back(prods[k].substr(l,prods[k].length()-l));
                    break;
                }
                it = productions.find(Lhs);
                s = first(Lhs,it->second);
                firsts[Lhs] = s; //insert the first of the symbol

                it2 = s.find('~');
                if(it2 == s.end())
                {
                    temp.insert(s.begin(),s.end());
                    break;
                }
                else
                {
                    s.erase(it2);
                    temp.insert(s.begin(),s.end());
                }

            }
            else
            {
                temp.insert(itTemp,prods[k][l]);
                break;
            }
        }
        if(l == prods[k].length())
            temp.insert(itTemp,'~');
    }

    itTemp = temp.find('~');            //if ~ was found in temp that means ~ can be put in the productions where the symbol came on RHS
    if(itTemp != temp.end())
        for(int k=0; k<tempProds.size(); k++)
        {
            for(int l=0; l<tempProds[k].length(); l++)
            {
                string s = "";
                s += tempProds[k][l];
                if(s == symbol) //removing the symbol because now its is ~ ( i.e. NULL)
                    continue;

                else if(tempProds[k][l]>=65 && tempProds[k][l]<=90)
                {
                    map<string, vector<string> >::iterator it;
                    set<char> s;
                    set<char>::iterator it2;

                    string Lhs = "";
                    Lhs += tempProds[k][l];
                    it = productions.find(Lhs);
                    s = first(Lhs,it->second);
                    firsts[Lhs] = s; //insert the first of the symbol

                    it2 = s.find('~');
                    if(it2 == s.end())
                    {
                        temp.insert(s.begin(),s.end());
                        break;
                    }
                    else
                    {
                        s.erase(it2);
                        temp.insert(s.begin(),s.end());
                    }
                }
                else
                {
                    temp.insert(itTemp,tempProds[k][l]);
                    break;
                }
            }
        }

    return temp;
}

void First()
{
	map<string,set<char> >::iterator it2;

	map<string,vector<string> >::iterator it1;

    for(it1=productions.begin(); it1!=productions.end(); it1++)
    {
        set<char> temp;
        if(find((visited).begin(), visited.end(), it1->first) == visited.end())
        {
            temp = first(it1->first,it1->second);
            firsts[it1->first] = temp;
        }
    }
}

set<char> follow(string symbol)
{
    set<char> temp;
    set<char>::iterator itTemp = temp.begin();
    map<string, vector<string> >::iterator it;

    if(find(visited.begin(), visited.end(), symbol) != visited.end())
    {
        map<string, set<char> >::iterator it2;
        it2 = follows.find(symbol);
        if(it2 != follows.end())
            temp.insert(it2->second.begin(),it2->second.end());
        return temp;
    }
    visited.push_back(symbol);

    if(symbol == startSymbol)
    {
       follows[symbol].insert('$');
    }

    for(it=productions.begin(); it!=productions.end(); it++)
    {
        string Lhs = it->first;
        vector<string> Rhs = it->second;

        for(int k=0; k<Rhs.size(); k++)
        {
            int flag=0; //becomes 1 if the symbol is found in a production
            int l;
            for(l=0; l<Rhs[k].length(); l++)
            {
                if(!flag && Rhs[k][l]!=symbol[0])
                    continue;
                else if(flag)
                {
                    if(Rhs[k][l]>=65 && Rhs[k][l]<=90)
                    {
                        //find first of this k,l
                        map<string, set<char> >::iterator it3;
                        set<char> s;
                        set<char>::iterator it4;

                        string str = "";
                        str += Rhs[k][l];

                        it3 = firsts.find(str);
                        if(it3 != firsts.end())
                            s = it3->second;

                        it4 = s.find('~');
                        if(it4 == s.end())
                        {
                            follows[symbol].insert(s.begin(),s.end());
                            break;
                        }
                        else
                        {
                            s.erase(it4);
                            follows[symbol].insert(s.begin(),s.end());
                        }
                    }
                    else
                    {
                        follows[symbol].insert(Rhs[k][l]);
                        break;
                    }
                }
                else if(!flag && Rhs[k][l] == symbol[0])
                    flag = 1;
            }
            if(flag && l == Rhs[k].length())
            {
                set<char> s;
                s = follow(Lhs);
                follows[symbol].insert(s.begin(),s.end());
            }
        }

    }
    return follows[symbol];
}

void Follow()
{
    visited.clear();
    map<string,set<char> >::iterator it2;
	map<string,vector<string> >::iterator it1;
    set<char> tempStart;

    tempStart = follow(startSymbol);
    follows[startSymbol] = tempStart;
    for(it1=productions.begin(); it1!=productions.end(); it1++)
    {
        set<char> temp;

        if(find((visited).begin(), visited.end(), it1->first) == visited.end())
        {
            temp = follow(it1->first);
        }
    }
}

set<char> firstOfString(string alpha)
{
    set<char> firstSet;
    map<string, set<char> >::iterator it1;
    int k=0;
    for(k=0; k<alpha.length(); k++)
    {
        set<char> temp;
        set<char>::iterator it2;
        if(isupper(alpha[k]))
        {
            it1 = firsts.find(string(1, alpha[k]));
            if(it1 != firsts.end())
                temp = it1->second;

            it2 = temp.find('~');
            if(it2 != temp.end())
            {
                temp.erase(it2);
                firstSet.insert(temp.begin(),temp.end());
            }
            else
            {
                firstSet.insert(temp.begin(),temp.end());
                break;
            }
        }
        else
        {
            firstSet.insert(alpha[k]);
            break;
        }
    }
    if(k == alpha.length())
        firstSet.insert('~');

    return firstSet;
}
int insertIntoTable(string symbol, string prod, set<char> first)
{
    string str =  symbol + ":" + prod;
    set<char>::iterator it;
    int foundEpsilon = 0;
    int foundEndMarker = 0; //end marker is $

    it = first.find('~');
    if(it != first.end())
    {
        first.erase(it);
        foundEpsilon = 1;
    }

    for(it=first.begin(); it!=first.end(); it++)
    {
        pair<char,char > p = make_pair(symbol[0],*it);
        if(predictiveParsingTable.find(p) != predictiveParsingTable.end() && str!=predictiveParsingTable.find(p)->second)
        {
            return 0;
        }
        else
            predictiveParsingTable[p] = str;
    }

    if(foundEpsilon)
    {
        set<char> follow = follows.find(symbol)->second;

        it = follow.find('$');
        if(it != follow.end())
        {
            follow.erase(it);
            foundEndMarker = 1;
        }

        str = symbol + ":" + "~";
        for(it=follow.begin(); it!=follow.end(); it++)
        {
            pair<char,char > p = make_pair(symbol[0],*it);
            if(predictiveParsingTable.find(p) != predictiveParsingTable.end() && str!=predictiveParsingTable.find(p)->second)
            {
                return 0;
            }
            else
                predictiveParsingTable[p] = str;
        }
    }

    if(foundEpsilon && foundEndMarker)
    {
        str = symbol + ":" + prod;
        pair<char,char > p = make_pair(symbol[0],'$');
        if(predictiveParsingTable.find(p) != predictiveParsingTable.end() && str!=predictiveParsingTable.find(p)->second)
        {
            return 0;
        }
        else
            predictiveParsingTable[p] = str;
    }

    return 1;
}

void constructPredictiveParsingTable()
{
	map<string,vector<string> >::iterator it1;

    for(it1=productions.begin(); it1!=productions.end(); it1++)
    {
        set<char>::iterator it2;

        string A = it1->first;
        for(int k =0; k<it1->second.size(); k++)
        {
            set<char> temp;
            string alpha = it1->second[k];
            temp = firstOfString(alpha);
            int done = insertIntoTable(A,alpha,temp);
            if(!done)
            {
                cout<<"The grammar is not LL1\n";
                return;
            }
        }
    }
    if(it1 == productions.end())
        cout<<"The grammar is LL1\n";
}

int main()
{
    FILE* file = freopen("input1.txt","r",stdin);
    int i=0;
    string arr[10];

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

	First();
    Follow();
    constructPredictiveParsingTable();

    fclose(file);
    return 0;
}


