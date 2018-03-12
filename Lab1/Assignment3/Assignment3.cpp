
//Name: Sumir Mathur
//Id: 2015KUCP1017

#include <bits/stdc++.h>
#define ZERO 48

using namespace std;
	
string ITOA(int num)
{
	
	bool isNegative = false;
	string str = "";
	char c;
	
	if(num < 0){
		isNegative = true;
		num = abs(num);
	}
	
	while(num)
	{
		c = num%10 + ZERO; 
		num /= 10;
		str = c + str; 
	}
	
	if(isNegative)
		str = '-' + str;
		
	str += '\0';
	return str;
}
	
int main()
{
	int num;
	cout<<"Enter a integer: ";
	cin>>num;
	
	cout<<"The string is "<<ITOA(num)<<"\n";
	return 0;
}
