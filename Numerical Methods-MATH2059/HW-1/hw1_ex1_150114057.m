%%
%Exercise 1
clc; 
clear all;
t=0:1/16:100; % t from 0 to 100 delta t = 1/16
x=sin(t).*(exp(cos(t))-2*cos(4.*t)-sin(t./12).^5); %Implementation x and y
y=cos(t).*(exp(cos(t))-2*cos(4.*t)-sin(t./12).^5);
subplot(1,1,1);
figure(1)
plot(t,x,'color','r'); hold on;
plot(t,y,':b'); % for dotted line, used :
xlabel('t') % x-axis label
ylabel('x,y') % y-axis label
legend('x','y') % legend
title('(a)')
grid
figure(2)
plot(x,y)
xlabel('x') % x-axis label
ylabel('y') % y-axis label
title('(b)')
grid
