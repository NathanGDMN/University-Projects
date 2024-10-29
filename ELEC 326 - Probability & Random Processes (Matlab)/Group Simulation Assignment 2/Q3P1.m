%-----------ELEC 326 Group Simulation Activity 2-----------
%------------------------Question 3------------------------

%-----Part 1-----:
%--Load Random Variables:
Hfile = load('H.mat');
H = Hfile.H;

%Estimate Probabilities 
xLessThan70 = estimateProbabilityLessThan(H, 70,length(H));
xLessThan19 = estimateProbabilityLessThan(H, 19,length(H));  

xBetween20and70 = xLessThan70-xLessThan19;

function ep = estimateProbabilityLessThan(H, x,y) %x is row, y is column
    probabilitySum = 0;
    for i=1:1:x     %For every row
        for j=1:1:y     %For every column
            probabilitySum = double(probabilitySum) + double(H(i,j));
            %disp(H(x,y));
        end
    end
    ep = probabilitySum;
end