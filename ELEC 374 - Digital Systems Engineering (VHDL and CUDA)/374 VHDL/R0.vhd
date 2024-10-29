library ieee;
use ieee.std_logic_1164.all;

entity R0 is
	port(
		--Control Signals
		clr  	: in std_logic;	--Clear
		clk		: in std_logic;	--Clock
		R0in  	: in std_logic;	--Enable
		--Inputs
		BusMuxOut 	: in std_logic_vector(31 downto 0); --BusMuxOut(input)
		--Outputs
		BusMuxIn-R0	: out std_logic_vector(31 downto 0)	--BusMuxIn-Rx(output)
	);
end entity;

architecture rtl of R0 is
begin

	process (clk, clr) is
	begin
      if (clr = '1') then	--If clear = '1', q = '000000000000000000000000000000000'
        BusMuxIn-R0 <= (others => '0'); 
	  elsif rising_edge(clk) then
		if R0in = '1' then
			BusMuxIn-R0 <= BusMuxOut;
		end if;
	  end if;
		
	end process;

end architecture;