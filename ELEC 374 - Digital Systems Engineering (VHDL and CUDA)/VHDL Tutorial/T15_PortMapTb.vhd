library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--The usual way of simulating hardware using vhdl involves creating modules (that represent hardware), and then using those in a simulaton (testbench).
--Below is the testbench file

--Note: when compiling the files involved in a testbench all modules must be compiled before the testbench otherwise you'll get a "Unknown Expanded Name" error
--Fix for this error is shown in T15 video

entity T15_PortMapTb is
end entity;

architecture sim of T15_PortMapTb is

	signal Sig1 : unsigned(7 downto 0) := x"AA";
	signal Sig2 : unsigned(7 downto 0) := x"BB";
	signal Sig3 : unsigned(7 downto 0) := x"CC";
	signal Sig4 : unsigned(7 downto 0) := x"DD";
	
	signal Sel : unsigned(1 downto 0) := (others => '0');
	
	signal Output : unsigned(7 downto 0);
	
begin
	--Instantiate Multiplex Module
	i_Mux1 : entity work.T15_Mux(rtl) port map(
		Sel => Sel,
		Sig1 => Sig1,
		Sig2 => Sig2,
		Sig3 => Sig3,
		Sig4 => Sig4,
		Output => Output
	);

	--Testbench Process
	process is 
	begin
		wait for 10ns;
		Sel <= Sel +1;
		wait for 10ns;
		Sel <= Sel +1;
		wait for 10ns;
		Sel <= Sel +1;
		wait for 10ns;
		Sel <= Sel +1;
		wait for 10ns;
		Sel <= "UU";
		wait;
	end process;

end architecture;