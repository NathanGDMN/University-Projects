%-----------ELEC 326 Group Simulation Activity 1-----------
%------------------------Question 2------------------------

%-----Part 1-----:
%--Load Random Variables:
RV1file = load('RV1.mat');
RV2file = load('RV2.mat');
RV3file = load('RV3.mat');

RV1 = RV1file.RV1;
RV2 = RV2file.RV2;
RV3 = RV3file.RV3;

%--Calculate Mean
meanRV1 = mean(RV1);
meanRV2 = mean(RV2);
meanRV3 = mean(RV3);

%--Calculate Variance
varianceRV1 = variance(RV1);
varianceRV2 = variance(RV2);
varianceRV3 = variance(RV3);

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

function m = mean(RV)
    m = sum(RV)/length(RV);
end