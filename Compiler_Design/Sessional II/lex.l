%%
repeatwhile               {return RWHILE;}
"True"                    {return TRUE;}
"False"                   {return FALSE;}
"!"                       {return NOT;}
"=="                      {return EQUAL;}
">"                       {return GREATER_THAN;}
"<"                       {return SMALLER_THAN;}
[0-9]+                    {return N;}
[a-zA-Z]+([A-Za-z0-9])*   {return ID;}
[\t|\n|\r|" "]            {;}
.                         {return yytext[0];}
%%