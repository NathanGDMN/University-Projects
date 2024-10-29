library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--Unlike in tutorial 15 (T15), where the ports were declared as a set amount of bits--i.e.(7 down to 0), we here set the ports to a generic size that will be determined by how they're defined in the test bench

entity T16_GenericMux is
	
	generic(DataWidth : integer); --The generic width declaration

	port(
		--Inputs
		Sig1 : in unsigned(DataWidth-1 downto 0); --*Note: DataWidth-1 is used here because if you wanted a data width of 8 bits, then the signals should be assign (7 downto 0)
		Sig2 : in unsigned(DataWidth-1 downto 0);
		Sig3 : in unsigned(DataWidth-1 downto 0);
		Sig4 : in unsigned(DataWidth-1 downto 0);
		
		Sel : in unsigned(1 downto 0);
		
		--Outputs
		Output : out unsigned(DataWidth-1 downto 0) --*Note: you do NOT close off the last port statement with a semi-colon
	);
end entity;

architecture rtl of T16_GenericMux is --Since we are not in a testbench file, naming the architecture 'sim' would be miss leading. A common architecture name for modules is rtl 
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