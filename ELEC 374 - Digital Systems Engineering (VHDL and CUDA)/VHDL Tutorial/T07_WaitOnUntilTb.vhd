entity T07_WaitOnUntilTb is
end entity;

architecture sim of T07_WaitOnUntilTb is

	signal CountUp : integer := 0;
	signal CountDown : integer := 10;


begin

	process is
	begin
		
		CountUp <= CountUp +1;
		CountDown <= CountDown -1;
		
		wait for 10 ns;
	
	end process;
	
	--Below will show you multiple ways to make up a process:
	
	process is 
	begin 
		--When the program reaches the below line the program will wait until either CountUp, or CountDown is changed before continuing
		wait on CountUp, CountDown;
		report "CountUp=" & integer'image(CountUp) &
			"CountDown=" & integer'image(CountDown);	
		
	end process;
	
	process is
	begin
		--The below wait until line will be evaluated everytime CountUp or CountDown changes value. If the given condition is met (in this case, if they're equal) the process will coninue until the next line.
		wait until CountUp=CountDown;
		report "Jackpot";
		
	end process;

end architecture;