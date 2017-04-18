%% Não esquecer de usar o sqrt de alpha, pois os valores nas variáveis 
% alpha são os números de fotões
clearvars
close all
clc

files=dir('*.txt');

F1= @(x,alpha) sqrt(2/pi)*exp(-2*(x-alpha*cos(pi/4)/sqrt(2)).^2);
F2= @(x,alpha) sqrt(2/pi)*exp(-2*(x-alpha*sin(pi/4)/sqrt(2)).^2);

dataphas=load(files(1).name);
[H,X]=hist(dataphas,100);
normfactor=.6404;
BER=zeros(1,length(files)/2);
BERT=BER;

alpha=1;


for i=1:length(files)/2;
 
    dataphas=load(files(i).name);
    dataquad=load(files(i+length(files)/2).name);
    
    
    bins=50;
    [h1,x1]=hist(dataphas,bins);
    
    %    if i~=1;
    %        normfactor=abs(mean(dataphas))/alpha;
    %    end
    
    
    x1=x1/normfactor;
    h1=h1/trapz(x1,h1);
    
    [h2,x2]=hist(dataquad,bins);
    x2=x2/normfactor;
    h2=h2/trapz(x2,h2); 

    xint1=min(x1):1e-3:max(x1);
    xint2=min(x2):1e-3:max(x2);
    hint1=interp1(x1,h1,xint1);
    hint2=interp1(x2,h2,xint2);
    
    figure
    plot(xint1,hint1,x1,F1(x1,sqrt(alpha(i))))
    figure
    plot(xint2,hint2,x2,F2(x2,sqrt(alpha(i))))
    
    
    xint1=xint1(xint1>=0);
    xint2=xint2(xint2>=0);
    
    %Yint1=sqrt(2/pi)*exp(-2*(xint1-sqrt(alpha(i))).^2);
    
    if ~isempty(xint1)
        hint1=hint1(1:length(xint1));
        hint2=hint2(1:length(xint2));
        Px=trapz(xint1,hint1)
        Py=trapz(xint2,hint2)
        
        PX=trapz(xint1,F1(xint1,sqrt(alpha(i))))
        PY=trapz(xint2,F2(xint2,sqrt(alpha(i))))
        
        BER(i)=1-Px*Py;
        BERT(i)=1-PX*PY;
    else
        BER(i)=0;
        BERT(i)=0;
    end
    
end

xlabel('quadrature x')
ylabel('probability density')


%legend('\alpha^2=0','\alpha^2=0.25','\alpha^2=0.5','\alpha^2=0.75','\alpha^2=1','\alpha^2=1.5','\alpha^2=2','\alpha^2=3','\alpha^2=4','\alpha^2=5')


Alpha=linspace(0,5,1e3);

BERt=(2*erfc(sqrt(2)*(sqrt(Alpha)/2)).*erfc(sqrt(2)*(sqrt(Alpha)/2))+erfc(sqrt(2)*(sqrt(Alpha)/2)).^2)/6;
%erfc(sqrt(2)*sqrt(Alpha))./2;
figure
plot(alpha,BER,'*',Alpha,BERt,alpha,BERT,'+k')
xlabel('pulse  intensity (photon/pulse)')
ylabel('BER')
legend('numerical results','theoretical results')