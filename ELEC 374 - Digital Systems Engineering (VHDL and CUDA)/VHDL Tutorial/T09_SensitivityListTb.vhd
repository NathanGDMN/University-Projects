entity T09_SensitivityListTb is
end entity;

architecture sim of T09_SensitivityListTb is

	signal CountUp : integer := 0;
	signal CountDown : integer := 10;


begin

	process is
	begin
		
		CountUp <= CountUp +1;
		CountDown <= CountDown -1;
		
		wait for 10 ns;
	
	end process;
	
	
	process is 
	begin 
		
		if CountUp = CountDown then
			report "Process A: Jackpot"
		end if;
		
		wait on CountUp, CountDown;

	end process;
	
	--The process below is logically equivalent to the one above
	--Oppossed to using wait on a more traditional way of making a process sensitive to signals is with the below process() syntax:
	process(CountUp, CountDown) is 
	begin	
		if CountUp = CountDown then
			report "Process B: Jackpot"
		end if;
	end process;

end architecture;