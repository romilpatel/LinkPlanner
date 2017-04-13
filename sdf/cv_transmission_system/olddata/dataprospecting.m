clear all
close all


files=dir('*.txt');

powerIndBm=-15:-1:-50;

Var=zeros(1,length(files));

for i=1:length(files)
    
    data=load(files(i).name);
    Var(i)=var(data);
end

