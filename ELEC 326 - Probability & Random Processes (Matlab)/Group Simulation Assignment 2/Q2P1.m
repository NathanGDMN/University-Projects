%-----------ELEC 326 Group Simulation Activity 2-----------
%------------------------Question 2------------------------

%-----Part 1-----:
%--Load Random Variables:
RV1file = load('RV1.mat');
RV2file = load('RV2.mat');
RV3file = load('RV3.mat');

RV1 = RV1file.RV1;
RV2 = RV2file.RV2;
RV3 = RV3file.RV3;

%--Create vectors to hold number of occurences
%* Vectors need to be of dimensions (101 x 101) as eachRV can produce 
%   values in the range:   [0,1,2,...100] -- 101 different numbers
H1 = countOccurrences(RV1,RV2); %Occurences of (RV1, RV2)
H2 = countOccurrences(RV1,RV3); %Occurences of (RV1, RV3)

%--Divide vectors by number of trials to get pdf
H1 = H1/length(RV1);
H2 = H2/length(RV1);

%--Plot Vectors
fig1 = plotV(H1,"Joint PMF of RV1 and RV2");
fig2 = plotV(H2,"Joint PMF of RV1 and RV3");

function cO = countOccurrences(RV1,RV2)
    %Create matrix to store occurences:
    cO = zeros(101,101);
    %Count occurences and store in matrix
    for i=1:1:length(RV1)
        cO(RV1(i)+1,RV2(i)+1) =  cO(RV1(i)+1,RV2(i)+1) + 1; %cO(RV1(i)+1,RV1(i)+1)+= 1
    end
    %*H(1,1) will hold count of number of (0,0), H(2,1) will hold
       %count of number of (1,0), RV(2,2) will hold count of number of
       %(1,1),... ect.
end

function fig = plotV(H, plotName)
    %Create Plot:
    fig  = figure('Name', plotName); %second argument is just window name
    s = surf(H); %Plots H(i) values
    s.EdgeColor = 'blue';
    s.FaceColor = 'interp';
    title(plotName, 'FontWeight', 'Normal');
    xlabel('First RV Values');
    ylabel('Second RV Values');
    zlabel('Probability');
end