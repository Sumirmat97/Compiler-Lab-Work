%%
auto |
double |
int |	
struct |
break | 
else |
long |	
switch |
case |
enum |
register |
typedef |
char |
extern |
return | 
union |
const | 
float |
short |	
unsigned |
continue |
for	|
signed |
void |
default |
goto |
sizeof |
volatile |
do |
if |
static |
while  { printf("%s is a keyword",yytext); }
[_a-zA-Z][a-zA-Z_0-9]* { printf("%s is an identifier",yytext); }
.* { printf("%s is not a valid keyword or identifier",yytext);}
%%

main()
{
	printf("Enter a string ");
	yylex();	
}

