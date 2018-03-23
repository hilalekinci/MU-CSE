x = 0.9; %Test Value for sinx approximation
n = 15; %Up to term x^15/15!
FindPercentErrorSinx(x,n) %Calling function

function FindPercentErrorSinx(x,n)%Function that takes 2 parameters
                                  % x if or degree, n is for term up to
terms=1:2:n;%For sinx approximation terms will be 1,3,5,7,9,..,n                      
facts=factorial(terms); %Find factorial of term
x_power=x.^terms;       %Find power of terms
signs=(-1).^((terms-1)/2); %We need terms +,-,+,-,+,.. in order
quotes=x_power ./facts;
series=signs.*quotes;
sinxApproximation=cumsum(series);
display(sinxApproximation);
figure(1)
plot (sinxApproximation); 
title('Sin(x) Approximation');
xlabel('number of terms'); ylabel('Sin(x) approximation');
true=sin(x); %Get true value of sin(x) and calculate error
percent_realative_error=abs((true-sinxApproximation)/true*100);
display(percent_realative_error)
figure(2)
plot(1:1:8,(abs(percent_realative_error)));
title('Percent Relative Error for sin(x)');
xlabel('number of terms'); ylabel('percent relatidve error');
end