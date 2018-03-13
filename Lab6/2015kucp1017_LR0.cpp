//Name: Sumir Mathur
//Id: 2015KUCP1017
//finding LR(0) items for a grammar
/* ~ represents epsilon and the first rule of grammar is for start symbol */

#include <bits/stdc++.h>
using namespace std;

string startSymbol="";
map<string,vector<string> > productions;
vector<vector<pair<string,string> > > items;


bool ifExists(vector<pair<string, string> > item)
{
    for(int k=0;k<items.size();k++)
        if(item == items[k])
            return true;

    return false;
}

vector<pair<string, string> > Closure(char symbol)
{
    vector<pair<string,string> > closure;
    set<string> visited;
    map<string,vector<string> >::iterator it;

    if(symbol>=65 && symbol<=90)
    {
        string str = string(1,symbol);

        it = productions.find(str);
        if(it!=productions.end())
        {
            visited.insert(it->first);
            for(int l=0; l<it->second.size(); l++)
            {
                pair<string,string> rule ;
                if(it->second[l] != "~")
                    rule = make_pair(str, "." + it->second[l]);
                else
                    rule = make_pair(str, ".");
                closure.push_back(rule);
            }
        }

        for(int k=0; k<closure.size(); k++)
        {
            pair<string,string> p = closure[k];
            int dotPos = p.second.find(".");
            if(dotPos < p.second.length()-1)
            {
                str = string(1,p.second[dotPos+1]);
                if(str[0] >= 65 && str[0] <= 90 && visited.find(str)==visited.end())
                {
                    visited.insert(str);
                    it = productions.find(str);
                    if(it != productions.end())
                    {
                        for(int l=0; l<it->second.size(); l++)
                        {
                            pair<string,string> rule;
                            if(it->second[l] != "~")
                                rule = make_pair(str, "." + it->second[l]);
                            else
                                rule = make_pair(str, ".");
                            closure.push_back(rule);
                        }
                    }
                }
            }
        }
    }

    return closure;
}

void createItems()
{
    map<string ,vector<string> >::iterator it;
    pair<string, string> p = make_pair(startSymbol+"'","."+startSymbol);
    vector<pair<string,string> > item;
    item.push_back(p);

    set<string> visited;

    vector<pair<string, string> > closures = Closure(startSymbol[0]);
    item.insert(item.end(),closures.begin(),closures.end());

    items.push_back(item);// I0 item

    for(int k=0; k<items.size(); k++)
    {
        visited.clear();
        for(int l=0; l<items[k].size(); l++)
        {
            item.clear();
            p = items[k][l];
            int dotPos = p.second.find(".");
            if(dotPos < p.second.length()-1)
            {
                char startAlpha = p.second[dotPos+1];

                for(int m=0; m<items[k].size(); m++)
                {
                    p = items[k][m];
                    dotPos = p.second.find(".");
                    if(visited.find(p.second)==visited.end() && dotPos < p.second.length()-1 && p.second[dotPos+1] == startAlpha)
                    {
                        visited.insert(p.second);
                        p.second[dotPos] = p.second[dotPos+1];
                        p.second[dotPos+1] = '.';
                        pair<string ,string> rule = make_pair(p.first,p.second);
                        item.push_back(rule);
                        if(dotPos+2<p.second.length())
                        {
                            closures = Closure(p.second[dotPos+2]);
                            item.insert(item.end(),closures.begin(),closures.end());
                        }
                    }

                }
                if(!ifExists(item)) //push when same item does not exist
                {
                    items.push_back(item);
                }
            }
        }
    }

    for(int k=0; k<items.size(); k++)
    {
        cout<<"I"<<k<<endl;
        cout<<"--------------"<<endl;
        for(int l=0; l<items[k].size(); l++)
        {
            cout<<items[k][l].first<<"->"<<items[k][l].second<<"\n";
        }
        cout<<"\n";
    }

}

int main()
{
    FILE* file = freopen("inputGrammar1.txt","r",stdin);
    int i=0;
    bool isCorrect = false;

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
	i=0;

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

    createItems();

    fclose(file);
    return 0;
}


