clearvars
close all
clc

% numerical

files=dir('*.txt');


data1=load(files(1).name);
data2=load(files(2).name);

bins=100;
[h1,x1]=hist(data1,bins);
x1=x1/abs(mean(data1));
h1=h1/trapz(x1,h1);

[h2,x2]=hist(data2,bins);
x2=x2/abs(mean(data2));
h2=h2/trapz(x2,h2);

plot(x1,h1,x2,h2)

% theoretical
f= @(x,alpha,phi) sqrt(2/pi)*exp(-2*(x-alpha*cos(phi)).^2);

phi1=pi;
phi2=0;
alpha=1;
start=min(x1);
finish=max(x1);
y1=f(x1,alpha,phi1);

y2=f(x2,alpha,phi2);

hold on
plot(x1,y1,'k',x2,y2,'k')
xlabel('quadrature x')
ylabel('probability')
title('|\alpha|=1, P_{LO}=1 mW')
% result of correct basis
data=[data1' data2'];
[h,x]=hist(data,bins*2);
x=x/mean(abs(data));
h=h/trapz(x,h);

figure
plot(x,h)

F= @(x,alpha) 1/sqrt(2*pi)*(exp(-2*(x-alpha).^2)+exp(-2*(x+alpha).^2));
Y=F(x,alpha);
hold on
plot(x,Y)
xlabel('quadrature x')
ylabel('probability')
title('|\alpha|=1, P_{LO}=1 mW')

% interpolation of results
Xint2=min(x2):.0001:max(x2);
Hint2=interp1(x2,h2,Xint2);

Xint=min(x):.0001:max(x);
Hint=interp1(x,h,Xint);
Yint=F(Xint,alpha);

% find zeros
up=length(Xint);
down=1;
mid=ceil((up-down)/2);
zero=0;
while zero==0
    if Xint(mid)*Xint(up)<0;
        down=mid;
    else
        up=mid;
    end
    
    mid=down+ceil((up-down)/2);
    
    if up-down==1
        zero=1;
    end
end

clear mid;

% choose closest to zero
g=[down up];
G=[Xint(down) Xint(up)];
Ind0=g(abs(G)==min(abs(G)));

if Xint(Ind0)~=0
    warning('Ind0 not completely centered')
end



% determination of PSE
PSE=zeros(1,Ind0-1);
XX=zeros(1,Ind0-1);
Indminus=Ind0;
Indplus=Ind0;
j=1;

while Indminus>1 && Indplus<length(Hint)
    PSE(j)=trapz(Xint(1:Indminus),Hint(1:Indminus))+trapz(Xint(Indplus:length(Xint)),Hint(Indplus:length(Xint)));
    XX(j)=Xint(Indplus);
    Indminus=Indminus-1;
    Indplus=Indplus+1;
    j=j+1;
end

XX(j:length(XX))=[];
PSE(j:length(PSE))=[];

XXX=[0 XX];
PSEt=(erfc(sqrt(2)*(XXX+alpha))+erfc(sqrt(2)*(XXX-alpha)))/2;
BERt=erfc(sqrt(2)*(XXX+alpha))./(2*PSEt);

figure
plot(XX,PSE,XXX,PSEt)
xlabel('threshold [x_0]')
ylabel('post selection efficiency')
title('|\alpha|=1, P_{LO}=1 mW')

% determination of BER
XXXX=Xint2(Xint2<0);
HHHH=Hint2(1:length(XXXX));

% interpolation of PSE to use in BER
PSEint=interp1(XX,PSE,abs(XXXX));

BER=zeros(1,length(PSEint));

ind=length(HHHH);
j=1;
while ind>1
    BER(j)=trapz(XXXX(1:ind),HHHH(1:ind))./PSEint(j);
    j=j+1;
    ind=ind-1;
end

figure
plot(abs(XXXX),fliplr(BER),XXX,BERt)
xlabel('threshold [x_0]')
ylabel('bit error rate')
title('|\alpha|=1, P_{LO}=1 mW')