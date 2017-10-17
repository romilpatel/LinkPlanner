clear all 
close all;

I_0=1; %intensidade inicial
a=1; % raio de core

u=8.6; %CDO em vacuo
w=10e-305;    %%é melhor escolher w=0 ou por aí w=10e-305
L=5; % index L
M=3; % index M

x=linspace(-2,2,150); % cria uma matriz de pontos para x
y=linspace(-2,2,150); % cria uma matriz de pontos para y

[X,Y]=meshgrid(x,y); % é para desenhar à 3D

i=1;

for x=linspace(-2,2,150)

  j=1;  

  for y=linspace(-2,2,150)
     if L==0
        sine=1;
     else
        sine=(sin(L*atan(x/y)))^2;
     end
     if sqrt(x.^2+y.^2)<=a
         I=(I_0*(besselj(L,u*sqrt(x.^2+y.^2)/a))^2*(sine)^2); % resolução da equação de Bessel de 1º grau
     elseif sqrt(x.^2+y.^2)>=a  
         I=(I_0*(besselj(L,u)/besselk(L,w))^2*(besselk(L,w*sqrt(x.^2+y.^2)/a))^2*(sine)^2); %resolução da equação de Bessel modificada de 2º grau
     end
   
    K(1,j)=I;
    j=j+1;
 
  end
    
    KK(i,:)=K;
    i=i+1;

end

if L==0
   axis_z=1.5;
elseif L==1
   axis_z=0.35;
elseif L==2
   axis_z=0.3;
elseif L==3;
   axis_z=0.25;
elseif L==4
   axis_z=0.25;
elseif L>=5
   axis_z=0.2;      
end   
   
figure(1)
mesh(X,Y,KK)
%colormap(gray(1))
axis([-2 2 -2 2 0 axis_z]);

figure(2)
mesh(X,Y,KK)
colormap(gray(256)),imagesc(KK)
axis off