//Name: Sumir Mathur
//Id: 2015KUCP1017
//Find FIRST and FOLLOW of the grammar given in file input.txt

/* ~ represents epsilon and the first rule of grammar is for start symbol */

#include <bits/stdc++.h>
using namespace std;

string startSymbol="";
map<string,vector<string> > productions;
map<string,set<char> > firsts; //contains set of FIRST of all symbols
map<string,set<char> > follows; //contains set of FOLLOW of all symbols
vector<string> visited;

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
                    firsts[Lhs] = s; //insert the first of the symbol and mark it visited

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

    set<char>::iterator it3;

    cout<<"Firsts:\n";
    for(it2=firsts.begin(); it2!=firsts.end(); it2++)
    {
        cout<<it2->first<<" - (";
        for(it3=it2->second.begin(); it3!=it2->second.end(); it3++)
        {
            if(it3 != it2->second.begin()) cout<<", ";
            if(*it3 == '~')
                cout<<"NULL";
            else
                cout<<*it3;
        }
        cout<<")"<<endl;
    }
    cout<<endl;
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

    set<char>::iterator it3;

    cout<<"Follows:\n";
    for(it2=follows.begin(); it2!=follows.end(); it2++)
    {
        cout<<it2->first<<" - (";
        for(it3=it2->second.begin(); it3!=it2->second.end(); it3++)
        {
            if(it3 != it2->second.begin()) cout<<", ";
            if(*it3 == '~')
                cout<<"NULL";
            else
                cout<<*it3;
        }
        cout<<")"<<endl;
    }
}

int main()
{
    FILE* file = freopen("input.txt","r",stdin);
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

    fclose(file);
    return 0;
}

