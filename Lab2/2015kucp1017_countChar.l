%{
	int count = 0;
%}
%%
[a-zA-Z] count++;
[\n] { 	return count; }
%%

main()
{
	printf("Enter a string ");
	yylex();
	printf("Count = %d\n",count);
}

