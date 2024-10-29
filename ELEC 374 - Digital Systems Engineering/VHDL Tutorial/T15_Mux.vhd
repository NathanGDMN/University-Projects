library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--The usual way of simulating hardware using vhdl involves creating modules (that represent hardware), and then using those in a simulaton (testbench).
--Below is the module file

entity T15_Mux is
	port(
		--Inputs
		Sig1 : in unsigned(7 downto 0);
		Sig2 : in unsigned(7 downto 0);
		Sig3 : in unsigned(7 downto 0);
		Sig4 : in unsigned(7 downto 0);
		
		Sel : in unsigned(1 downto 0);
		
		--Outputs
		Output : unsigned(7 downto 0) --*Note: you do NOT close off the last port statement with a semi-colon
	);
end entity;

architecture rtl of T15_Mux is --Since we are not in a testbench file, naming the architecture 'sim' would be miss leading. A common architecture name for modules is rtl 
begin

	--4-1 MUX using case-when
	process (Sel, Sig1, Sig2, Sig3, Sig4) is
	begin
	
		case Sel is 
			when "00" =>
				Output <= Sig1;
			when "01" =>
				Output <= Sig2;
			when "10" =>
				Output <= Sig3;
			when "11" =>
				Output <= Sig4;
			when others =>
				Output <= (others => 'X');
		end case;
		
	end process;
	

end architecture;