%{
	int countVowels = 0;
	int countConsonants = 0;
%}
%%
[aeiouAEIOU] {countVowels++;}
[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNOPQRSTVWXYZ] { countConsonants++; }
[\n] { 	return; }
%%

main()
{
	printf("Enter a string ");
	yylex();
	printf("Count of vowels = %d\n",countVowels);
	printf("Count of consonants = %d\n",countConsonants);
	
}

