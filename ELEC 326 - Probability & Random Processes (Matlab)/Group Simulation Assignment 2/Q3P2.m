%-----------ELEC 326 Group Simulation Activity 2-----------
%------------------------Question 3------------------------

%-----Part 2-----:
%--Load Random Variables:
Hfile = load('H.mat');
H = Hfile.H;

%--Convert pmf matrix columns into thier own pmfs:
pmfOfXGiven40 = columnToPMF(H,40); 
pmfOfXGiven10 = columnToPMF(H,10);

%--Plot extracted PMFs
fig1 = plotV(pmfOfXGiven40,'Conditional PMF of x Given y=40', 'r');
fig2 = plotV(pmfOfXGiven10,'Conditional PMF of x Given y=10', 'b');
comparison = plot2V(pmfOfXGiven40,pmfOfXGiven10, 'Comparison of PMFs of x, Given y=40 vs y=10', 'r', 'b');

function rtp = columnToPMF(H,column)
    %Place all probabilities from matrix column into own array
    Htemp = H(:,column);
    
    %Adjust probabilities so that sum = 1
    rtp = Htemp*adjustmentFactor(Htemp);
end

function f = adjustmentFactor(columnArray)
    %Logic:
    %   1 should equal sum of probabilities
    %   Sum of probabilities from matrix will not equal 1 as they are still
    %       assuming possibilities where y!=40 or y!=10 are possible
    %   Thus, to find factor not multiply those probabilities by, simply
    %       divide 1 by the sum of the probabilities from matrix(<1) 
    f = 1/sum(columnArray);
end

function fig = plotV(H, plotName, colour)
    %Create Plot:
    fig  = figure('Name', plotName); %second argument is just window name
    stem(0:100, H, colour); %Plots H(i) values at positions RV(i-1)
    title(plotName, 'FontWeight', 'Normal');
    xlabel('x Values');
    ylabel('Probability');
end
function fig = plot2V(H1,H2, plotName, colour1, colour2)
    %Create Plot:
    fig  = figure('Name', plotName); %second argument is just window name
    stem(0:100, H1, colour1); %Plots H(i) values at positions RV(i-1)
    hold on
    stem(0:100, H2, colour2);
    hold off
    title(plotName, 'FontWeight', 'Normal');
    xlabel('x Values');
    ylabel('Probability');
end
