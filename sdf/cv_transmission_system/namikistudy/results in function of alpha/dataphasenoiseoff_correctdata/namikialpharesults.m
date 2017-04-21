%% Não esquecer de usar o sqrt de alpha, pois os valores nas variáveis 
% alpha são os números de fotões
clearvars
close all
clc

files=dir('*.txt');

phi=0;

F= @(x,alpha) 1/sqrt(2*pi)*(exp(-2*(x-alpha*cos(phi)).^2)+exp(-2*(x+alpha*cos(phi)).^2));

dataphas=load(files(5).name);
[H,X]=hist(dataphas,100);
normfactor=abs(mean(dataphas));
BER=zeros(1,length(files)/2);
BERT=BER;

alpha=[0 .25 .5 .75 1 1.5 2 3 4 5];

figure
for i=5:5%length(files)/2;
    
    dataphas=load(files(i).name);
    dataquad=load(files(i+length(files)/2).name);
    
    data=[dataphas' dataquad'];
    
    bins=100;
    [h1,x1]=hist(dataphas,bins);
    
    %    if i~=1;
    %        normfactor=abs(mean(dataphas))/alpha;
    %    end
    
    
    x1=x1/normfactor;
    h1=h1/trapz(x1,h1);
    
    [h2,x2]=hist(dataquad,bins);
    x2=x2/normfactor;
    h2=h2/trapz(x2,h2);
    
    [h,x]=hist(data,bins);
    x=x/normfactor;
    h=h/trapz(x,h);
    
    hold on
    plot(x1,h1)
    

    xint1=min(x1):1e-3:max(x1);
    hint1=interp1(x1,h1,xint1);
    
    xint1=xint1(xint1<0);
    
    Yint1=sqrt(2/pi)*exp(-2*(xint1-sqrt(alpha(i))).^2);
    
    if length(xint1)~=0
        hint1=hint1(1:length(xint1));
        BER(i)=trapz(xint1,hint1)/1;
        BERT(i)=trapz(xint1,Yint1)/1;
    else
        BER(i)=0;
        BERT(i)=0;
    end
    
end

xlabel('quadrature x')
ylabel('probability density')
%legend('\alpha^2=0','\alpha^2=0.25','\alpha^2=0.5','\alpha^2=0.75','\alpha^2=1','\alpha^2=1.5','\alpha^2=2','\alpha^2=3','\alpha^2=4','\alpha^2=5')


Alpha=linspace(0,5,1e3);

BERt=erfc(sqrt(2)*sqrt(Alpha))./(2);
figure
plot(alpha,BER,'*',Alpha,BERt)
xlabel('pulse  intensity (photon/pulse)')
ylabel('BER')
legend('numerical results','theoretical results')