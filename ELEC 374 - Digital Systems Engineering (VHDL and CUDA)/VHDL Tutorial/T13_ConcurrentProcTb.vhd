library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity T13_ConcurrentProcTb is
end entity;

architecture sim of T13_ConcurrentProcTb is
	
	signal Uns : unsigned(5 downto 0) := (others => '0');
	signal Mul1 : unsigned(7 downto 0);
	signal Mul2 : unsigned(7 downto 0);
	signal Mul3 : unsigned(7 downto 0);
	
begin

	process is
	begin
	
		Uns <= Uns +1;
		
		wait for 10 ns;
	end process;
	
	-- Process multiplying Uns by 4
	process is
	begin
		--This process uses bit shifting. If Uns is '000001' (1), Mul1 wil be '00001000'(4). If Uns is '000111'(7), Mull wil be '00011100'(28).
	
		Mul1 <= Uns & "00"; --*Note: You can not assign a smaller signal to a larger signal without a ocmpilation error, this is why we add the two bits.
		
		wait on Uns;
		
	end process;
	
	--Equivalent process using sensitivity list
	process(Uns)
	begin
		
		Mul2 <= Uns & "00"; 
		
	end process;
	
	--Equivalent process using a concurrent statement
	Mul3 <= Uns & "00"; 
	
	--A concurrent process is simply an asiignment to a signal within the architecture part of the vhdl file (outside of a process)
	--A concurrent process is simply treated as a sensitivity list that is sensitive to all signals to the right of the assignment operator(<=)

end architecture;