%-----------ELEC 326 Group Simulation Activity 1-----------
%------------------------Question 2------------------------

%-----Part 3-----:
%--Load Random Variables:
RV1file = load('RV1.mat');
RV2file = load('RV2.mat');
RV3file = load('RV3.mat');

RV1 = RV1file.RV1;
RV2 = RV2file.RV2;
RV3 = RV3file.RV3;

%--Create vectors to hold number of occurences
%* Vectors need to be of length 101 as RV can produce values in the range:
%  [0,1,2,...100] -- 101 different numbers
H1 = countOccurrences(RV1);
H2 = countOccurrences(RV2);
H3 = countOccurrences(RV3);

%--Divide vectors by number of trials to get pdf
H1 = H1/length(RV1);
H2 = H2/length(RV1);
H3 = H3/length(RV1);

%--Calculate Probability that vectors take a value between 10 and 40
p1 = calculateProbabilityBetween(RV1, H1, 10, 40);
p2 = calculateProbabilityBetween(RV2, H2, 10, 40);
p3 = calculateProbabilityBetween(RV2, H2, 10, 40);

function p = calculateProbabilityBetween(RV, H, x1, x2)
    %Experimental Probability
    p(1) = sum(H((x1+1):(x2+1)));
    %Theoretical Probability
    f_x = normalDistribution(RV);
    p(2) = integral(f_x, x1, x2);
end

function cO = countOccurrences(RV)
    cO = zeros(1,101); %101 = 100 (max value in RV) + 1 (space for 0's)
    for i=1:1:length(RV)
        cO(RV(i)+1) =  cO(RV(i)+1) + 1; %cO(RV(i)+1)+= 1
    end
    %*H(1) will hold count of number of zeros in RV, H(2) will hold
       %count of number of ones in RV, RV(3) will hold count of number of
       %twos in RV,... ect.
end

function n = normalDistribution(RV)
    n = @(x) exp(-1.0*(x-mean(RV)) .* (x-mean(RV))/(2.0*variance(RV))) / sqrt(2.0*pi*variance(RV));
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


function m = mean(RV)
    m = sum(RV)/length(RV);
end