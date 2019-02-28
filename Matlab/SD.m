function [ SD ] = SD( data )

sum=0;
average=mean(data);
for i=1:length(data)
    sum=(data(i)-average)^2+sum;
end

SD=sqrt(sum/length(data));

end

