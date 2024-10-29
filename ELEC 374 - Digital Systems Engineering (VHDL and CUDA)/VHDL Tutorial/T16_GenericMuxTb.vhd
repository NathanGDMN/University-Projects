library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--Note: when compiling the files involved in a testbench all modules must be compiled before the testbench otherwise you'll get a "Unknown Expanded Name" error
--Fix for this error is shown in T15 video

--Unlike in tutorial 15 (T15), where the ports were declared as a set amount of bits--i.e.(7 down to 0), we here set the ports to a generic size that will be determined by how they're defined in the test bench

entity T16_GenericMuxTb is
end entity;

architecture sim of T16_GenericMuxTb is

	constant DataWidth : integer := 8;

	signal Sig1 : unsigned(DataWidth-1 downto 0) := x"AA";
	signal Sig2 : unsigned(DataWidth-1 downto 0) := x"BB";
	signal Sig3 : unsigned(DataWidth-1  downto 0) := x"CC";
	signal Sig4 : unsigned(DataWidth-1 downto 0) := x"DD";
	
	signal Sel : unsigned(1 downto 0) := (others => '0');
	
	signal Output : unsigned(DataWidth-1 downto 0);
	
begin
	--Instantiate Multiplex Module
	i_Mux1 : entity work.T16_GenericMux(rtl) 
		generic map (DataWidth => DataWidth) --Defining the generic variable in module (Datawidth) as equal to the constant (Datawidth) from this test bench
		--Equivalent to generic map (Datawidth => 8)
		port map(
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