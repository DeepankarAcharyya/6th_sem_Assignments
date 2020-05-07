%{
#include<string.h>
#include "bison.tab.h"    
%}

%%
"repeatwhile"             {return RWHILE;}
"True"                    {return TRUE;}
"False"                   {return FALSE;}
"!"                       {return NOT;}
"=="                      {return EQUAL;}
">"                       {return GREATER_THAN;}
"<"                       {return SMALLER_THAN;}
[0-9]+                    {yylval.val=atoi(yytext); return N;}
[a-zA-Z]+([A-Za-z0-9])*   {sscanf(yytext,"%s",yylval.name);return ID;}
[\t|\n|\r|" "]            {;}
.                         {return yytext[0];}
%%
int yywrap (void) {return 1;}