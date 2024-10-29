library ieee;
use ieee.std_logic_1164.all;

entity standard32register is
	port(
		--Control Signals
		clr  	: in std_logic;	--Clear
		clk		: in std_logic;	--Clock
		enable  : in std_logic;	--Rxin
		--Input
		d       : in std_logic_vector(31 downto 0); --BusMuxOut
		--Output
		q       : out std_logic_vector(31 downto 0)	--BusMuxIn-Rx(output)
		
		--q can be seen as the data stored in the register.
	);
end entity;

architecture rtl of standard32register is
begin

	process (clk, clr) is
	begin
      if (clr = '1') then	--If clear = '1', q = '000000000000000000000000000000000'
        q <= (others => '0'); 
	  elsif rising_edge(clk) then
		if enable = '1' then
			q <= d;
		end if;
	  end if;
		
	end process;

end architecture;