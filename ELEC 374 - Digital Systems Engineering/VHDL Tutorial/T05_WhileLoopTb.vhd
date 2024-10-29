entity T05_WhileLoopTb is
end entity;

architecture sim of T05_WhileLoopTb is
begin

	process is
	variable i : integer := 0; --On the left is a variable declaration example
	
	begin
		
		--The following is the syntax for a while loop in Vhdl.
		while i < 10 loop
			report "i=" & integer'image(i);
			i := i + 1; --Like with any other language the while loops do not increment themselves
			--*Note: in vhdl an assignment statement to a variable is done with :=
		end;
		
		wait;
	
	end process;

end architecture;