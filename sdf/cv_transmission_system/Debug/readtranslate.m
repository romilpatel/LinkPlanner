clear all
close all
clc

load translate.txt
plot(translate,'.')

axis([0 length(translate) min(translate)*(1.1) max(translate)*(1.1)])

figure

load translate2.txt
plot(translate2,'.')

axis([0 length(translate2) min(translate2)*(1.1) max(translate2)*(1.1)])