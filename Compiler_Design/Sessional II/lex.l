%{
  #include "tokens.h"
%}

%%
repeatwhile               {return WHILE;}
"=="                      {return EQUAL;}
">"                       {return GREATER_THAN;}
"<"                       {return SMALLER_THAN;}
[0-9]+                    {return NUM;}
[a-zA-Z]+([A-Za-z0-9])*   {return IDENTIFIER;}
[\t|\n|\r|" "]            {;}
.                         {return yytext[0];}
%%