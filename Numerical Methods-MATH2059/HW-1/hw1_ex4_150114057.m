   %Test Value 1
   t=linspace(0, 6*pi); 
   func = 8 * exp(-0.25*t).*sin(t - 2);
   
   %Test Value 2
   %x=linspace(0.01, 2); 
   %func = exp(4*x).*sin(1./x);
 
   %Test Value 3
   %x=linspace(0, 2);  
   %func =humps(x);
   
 [difference] = FindDifference(func,t);%Calling function
 function [difference]=FindDifference(f,t)%Parameter func is for function,
    plot(t, f);                            %Parameter t is for range
    ylabel('function');
    xlabel('range');
    grid on;
    difference = abs(max(f)- min(f)); %Find min and max values and 
                                 %Calculate difference using abs function
    sprintf('The min value = %f\nThe max value = %f', min(f), max(f))
    sprintf('\nThe difference value = %f ',difference)
 end