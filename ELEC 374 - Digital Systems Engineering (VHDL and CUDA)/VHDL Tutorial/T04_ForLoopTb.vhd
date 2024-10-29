entity T04_ForLoopTb is
end entity;

architecture sim of T04_ForLoopTb is
begin

	process is
	begin
		
		--The following is the syntax for a for loop in Vhdl.
		--*Note: the below for loop will iterate one for every number in the range 1 to 10 (inclusive) -- 10 times
		for i in 1 to 10 loop
			report "i=" & integer'image(i);
		end;
		
		wait;
	
	end process;

end architecture;