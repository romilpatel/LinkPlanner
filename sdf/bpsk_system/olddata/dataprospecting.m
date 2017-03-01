clear all
close all
clc

data=load('11.txt');
size=430;
nPulses=890;
bfsumdata=zeros(size,nPulses);
sumdata=zeros(1,nPulses);
for i=1:nPulses;
    bfsumdata(:,i)=data(1+(i-1)*size:i*size);
    sumdata(i)=sum(bfsumdata(:,i));
end
Var=var(sumdata)
