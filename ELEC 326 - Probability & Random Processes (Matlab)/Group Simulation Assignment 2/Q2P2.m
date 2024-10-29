%-----------ELEC 326 Group Simulation Activity 2-----------
%------------------------Question 2------------------------

%-----Part 2-----:
%--Load Random Variables:
RV1file = load('RV1.mat');
RV2file = load('RV2.mat');
RV3file = load('RV3.mat');

RV1 = RV1file.RV1;
RV2 = RV2file.RV2;
RV3 = RV3file.RV3;

%--Calculate covariance for each pair of RVs
covariance12 = covariance(RV1, RV2);
covariance13 = covariance(RV1,RV3);

%--Calculate standard deviation for each RV
RV1deviation  = deviation(RV1);
RV2deviation  = deviation(RV2);
RV3deviation  = deviation(RV3);

%--Calculate Correlation
correlation12 = correlation(covariance12, RV1deviation, RV2deviation);
correlation13 = correlation(covariance13, RV1deviation, RV3deviation);

function c = covariance(RV1, RV2)
    %Calculate Means
    meanRV1 = mean(RV1);
    meanRV2 = mean(RV2);
    
    %Calculate Covariance
    c = 0;
    for i=1:1:length(RV1)
       c = c + (RV1(i)- meanRV1) * (RV2(i)-meanRV2); %c += (RV1(i)- mean(RV1)) * (RV2(i)-mean(RV2)
    end
    c = c / (length(RV1)-1);
end

function m = mean(RV)
    m = sum(RV)/length(RV);
end

function d = deviation(RV)
    %Calculate Variance
    v = variance(RV);
    %Calculate Standard Deviation
    d = sqrt(v);
end

function v = variance(RV)
    m = mean(RV);
    
    variances = double.empty(length(RV),0);
    i=1;
    while i<=length(RV)
        variances(i) = (RV(i)-m)^2;
        i = i+1;
    end
    v = sum(variances)/length(RV);
end

function crl =correlation(covariance, deviation1, deviation2)
    crl = covariance / (deviation1*deviation2);
end

