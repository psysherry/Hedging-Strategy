clc,clear,clf
filename = 'rearrange_data.csv';data = csvread(filename);

%separate groups to calculate alpha and sigma
k=500;
j=5;
alpha_sigma=zeros(k,2);
X=zeros(k,1);
for i=1:(252000-k)/j
    data_S=data(1+(i-1)*j:(i-1)*j+k,1);
    data_R=data(1+(i-1)*j:(i-1)*j+k,2);
    alpha_sigma(i,1)=mean(data_R)*252;
    alpha_sigma(i,2)=SD(data_R)/sqrt(1/252);
    X(i)=mean(data_S);
end
%alpha as a constant
alpha=mean(alpha_sigma(:,1))

load census;

%alpha graph
figure(1)
hold on
plot(X,alpha_sigma(:,1))
[f1,gof1]=fit(X,alpha_sigma(:,1),'poly1')
plot(f1,X,alpha_sigma(:,1))
xlabel('Stock Price')
ylabel('Alpha')
hold off

%sigma graph with polynomials
figure(2)
hold on
plot(X,alpha_sigma(:,2))
[f2,gof2]=fit(X,alpha_sigma(:,2),'poly2')
[f3,gof3]=fit(X,alpha_sigma(:,2),'poly3')
[f4,gof4]=fit(X,alpha_sigma(:,2),'poly4')
a1=plot(f2,X,alpha_sigma(:,2),'r'); M1="2 degree poly";
a2=plot(f3,X,alpha_sigma(:,2),'g'); M2="3 degree poly";
a3=plot(f4,X,alpha_sigma(:,2),'k'); M3="4 degree poly";
legend([a1;a2;a3], M1, M2, M3)
xlabel('Stock Price')
ylabel('Sigma')
hold off

%sigma graphs with rational polynomial
figure(3)
hold on
x = X; y = alpha_sigma(:,2);
[f5,gof5]=fit(X,alpha_sigma(:,2),'rat32')
b1=plot(f5,X,alpha_sigma(:,2),'y');N1="rational poly";
b2=plot(f4,X,alpha_sigma(:,2),'k');N2="4 degree poly";
legend([b1;b2], N1,N2)
xlabel('Stock Price')
ylabel('Sigma')
hold off

%Cross Validation
load carbig
N = length(x);
sse2 = 0; sse3=0; sse4=0; sse5=0;
check1=0;check2=0;check3=0;check4=0;
for k=1:200
    for i = 1:100
        [train,testo] = crossvalind('LeaveMOut',N,1);
        yhat2=polyval(polyfit(x(train),y(train),2),x(testo));
        yhat3=polyval(polyfit(x(train),y(train),3),x(testo));
        yhat4=polyval(polyfit(x(train),y(train),4),x(testo));   
        sse2 = sse2 + sum((yhat2 - y(testo)).^2);
        sse3 = sse3 + sum((yhat3 - y(testo)).^2);
        sse4 = sse4 + sum((yhat4 - y(testo)).^2);
    end
    CVerr2=sse2/100;
    CVerr3=sse3/100;
    CVerr4=sse4/100;
    if CVerr2>CVerr3
        check1=check1+1;
    end
    if CVerr2>CVerr4
        check2=check2+1;
    end
    if CVerr3>CVerr4
        check3=check3+1;
    end
end
check1
check2
check3