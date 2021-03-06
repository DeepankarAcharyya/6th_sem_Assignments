%{
#include<string.h>
#include "bison.tab.h"    
extern flag;
%}

%%
"repeatwhile"             {return RWHILE;}
"True"                    {return TRUE;}
"False"                   {return FALSE;}
"!"                       {flag=1;return NOT;}
"=="                      {sscanf(yytext,"%s",yylval.sym); return EQUAL;}
">"                       {sscanf(yytext,"%s",yylval.sym); return GREATER_THAN;}
"<"                       {sscanf(yytext,"%s",yylval.sym); return SMALLER_THAN;}
"$"                       {yyterminate();}
[0-9]+                    {yylval.val=atoi(yytext); return N;}
[a-zA-Z]+([A-Za-z0-9])*   {sscanf(yytext,"%s",yylval.name); return ID;}
[\t|\n|\r|" "]            {;}
.                         {return yytext[0];}
%%

int yywrap (void) {
    return 0;
}