 %Exercise 2
theta = 0:pi/32:8*pi; %theta from 0 to 8pi with delta theta = pi/32
r = exp(sin(theta))-2*cos(4.*theta)- sin((2.*theta - pi)/24).^5 ;
subplot(1,1,1);
figure
polar(theta,r,'--r') % to represent in polar coordinates
title('Exercise 2 - Butterfly Curve')
