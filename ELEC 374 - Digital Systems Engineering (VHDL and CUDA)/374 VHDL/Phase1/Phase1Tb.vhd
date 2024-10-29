library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Phase1Tb is
end entity;

architecture sim of Phase1Tb is
	
	--Control Signals:
	
	
	--Instantiate Registers
	i_R0 : entity work.R0(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable = > R0in,
	);
	
begin
	