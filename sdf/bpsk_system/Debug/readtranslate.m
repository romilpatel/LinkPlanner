clear all
close all
clc

load translate.txt
plot(translate,'.')

axis([0 length(translate) min(translate)*(1.1) max(translate)*(1.1)])