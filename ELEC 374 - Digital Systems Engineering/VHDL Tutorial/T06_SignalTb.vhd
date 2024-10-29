entity T06_SignalTb is
end entity;

architecture sim of T06_SignalTb is

--Signals may only be declared between the architecture is tage and teh begin tag below -- the declaritive region of the vhdl file
	signal MySignal : integer := 0;


begin

	process is
		--Up until now we have been using variables for everything. However the scope of a variable is only within the process where it was declared.
		--If you want to use a variable within multiple processes in a architecture, you use signals (declaration shown above)
		variable MyVariable : integer := 0; --On the left is a variable declaration example
	
	begin
		
		MyVariable := MyVariable + 1;
		
		--*Note: notation for signal assignment statements are different than that of variables the below assignment will return an error
		--MySignal := MySignal + 1;
		
		--The following is the correct assignment statement notation for Signals
		MySignal <= MySignal + 1;
		
		report "MyVariable=" & integer'image(MyVariable) &
			"MySignal=" & integer'image(MySignal);
			
		wait for 10 ns;
		--The wait statement is vary important for signals!!!!
		--Unlike variables that instantly update when assigned, signals only update when they reach a wait statement.
		--If multiple assignments are made before a wait statement only the last assignment will happen.
	
	end process;

end architecture;