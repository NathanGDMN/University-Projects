entity T03_LoopTb is
end entity;

architecture sim of T03_LoopTb is
begin

	process is
	begin
		
		report "Hello";
		
		--Below is the syntax for a loop in  VHDL
		loop
			report "peekaboo";
			exit; --A loop with not automatically end when it reaches the end so you have to tell it to using the exit; function
			--Without this, the loop would loop infinitly, think of a while(true){...} loop in any other language
		end loop
		
		report "Goodbye";
	
	end process;

end architecture;