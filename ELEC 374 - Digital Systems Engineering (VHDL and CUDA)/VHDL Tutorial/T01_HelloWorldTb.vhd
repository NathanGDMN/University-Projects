--The following is the general layout of a vhdl file:
entity T01_HelloWorldTb is
--The entity defines the inputs and outputs for a module.
end entity;

architecture sim of T01_HelloWorldTb is
begin
--The architecture section is where we put most of the logic and al;gorithms

	process is
	--Variables in VHDL are usually decared here
	
	begin
	--Most of our code is put within processes
	--Think of processes as a program thread, code inside of it is executed sequentialy from top to bottom
	
		report "Hello World";
		wait; --By using wait without a specified time, we cause the program thread to pause forever.
	
	end process;

end architecture;