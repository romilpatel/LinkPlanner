clear all
close all
clc
%%
clc
load translate.txt
%plot(translate,'.')

%axis([0 length(translate) min(translate)*(1.1) max(translate)*(1.1)])

VAR(i)=var(translate);
i=i+1;



VAR(length(VAR)-3:length(VAR))

delete translate.txt

%%
x=-70:2:-20;