
//Name: Sumir Mathur
//Id: 2015KUCP1017

#include <bits/stdc++.h>

using namespace std;

bool isValid(string str){
	
	if(str[0] == 'i')
	{
		if(str[1] == 'f' && str[2] == '\0')
			return true;
	}
	else if(str[0] == 'f')
	{
		if(str[1] == 'o' && str[2] == 'r' && str[3] == '\0')
			return true;
	}	
	else if(str[0] == 'e')
	{
		if(str[1] == 'l' && str[2] == 's' && str[3] == 'e' && str[4] == '\0')
			return true;
	}
	else if(str[0] == 'w')
	{
		if(str[1] == 'h' && str[2] == 'i' && str[3] == 'l' && str[4] == 'e' && str[5] == '\0')
			return true;
	}
	
	return false;
}
	
int main()
{
	FILE *fin = freopen("input.txt", "r", stdin);
	FILE *fout = freopen("output.txt", "w", stdout);
	
	int t;
	cin>>t;
	
	while(t--)
	{
		string str;
		cin>>str;
		
		if(isValid(str))
			cout<<"Valid\n";
		else
			cout<<"Invalid\n";
	}
	
	fclose(fin);
	fclose(fout);
	
	return 0;
}
