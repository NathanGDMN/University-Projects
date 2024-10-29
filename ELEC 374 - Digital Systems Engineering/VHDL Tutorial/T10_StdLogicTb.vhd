--Below is how you import the library to use the std_logic type
library ieee;
use ieee.std_logic_1164.all;

entity T10_StdLogicTb is
end entity;

architecture sim of T10_StdLogicTb is

	--So far we have only used integer signal and variable type
	--But the most commonly used signal type in vhdl is std_logic, to use it you will need to import the library shown above
	signal Signal1 : std_logic := '0';
	signal Signal2 : std_logic;
	signal Signal3 : std_logic;


begin

	process is
	begin
		
		
		wait for 10 ns;
		Signal1 <= not Signal1; --Inverts signal1 every 10ns
	
	end process;
	
	--Driver A
	process is 
	begin	
		Signal2 = 'Z';
		Signal3 = '0';
		wait; --By using a wait statement here the process will be driving the signal values above forever
		
	end process;
	
	
	--Driver B
	process(Signal1) is --This process will wake eveytime the value of Signal1 is changed
	begin	
		if Signal1 = '0' then
			Signal2 = 'Z';
			Signal3 = 'Z';
		else
			Signal2 = '1';
			Signal3 = '1';
		end if;
		
	end process;
	
	--If you observe the waveform diagram you will notice that dispite having two drivers, the signals somehow sorted themseleves out. On top of this you will notice that some values the signals take were not assigned in either of the drivers.
	--This is because std_logic is a resolved type, this means that if there are two drivers to the same signal, the value will be a result acording to a resolution table (Can look it up)
	
	

end architecture;