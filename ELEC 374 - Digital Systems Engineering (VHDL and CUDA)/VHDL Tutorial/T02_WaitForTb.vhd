entity T02_WaitForTb is
end entity;

architecture sim of T02_WaitForTb is
begin

	--Processes infintely loop without wait functions
	--In VHDL only wait statements consume time
	--Without wait startements the file would run forever without getting past the initial time step, crashing the simulation 

	process is
	begin
		--This is the start of the process "thread"

		report "peekaboo!";
		
		--before we used the wait; function but that caused tehe program to pause forever.
		wait for 10 ns;
		
		
		--The process will loop back to the start of from here
	end process;

end architecture;