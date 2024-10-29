timesRan = 0;
H1 = int16.empty(100,0);

for i=1:1:100
    timesRan = timesRan + 1;
    H1(i) = i;
end

H1(100) = 1
