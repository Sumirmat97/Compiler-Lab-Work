%%
[\t]+
is |
are |
am |
was |
were { printf("%s is a valid Helping Verbs",yytext); } 
[a-zA-Z]+ { printf("%s is not a valid Helping Verbs",yytext); }
%%
main()
{
	yylex();
}
