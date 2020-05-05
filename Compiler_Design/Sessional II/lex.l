%{
#include <stdio.h>   
%}

numbers ([0-9])+
variables 

%%
while               {return WHILE;}

%%