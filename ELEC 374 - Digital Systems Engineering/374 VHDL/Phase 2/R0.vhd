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
		
		--New Additions for Phase 2
		BAout : in std_logic;
		BusMuxInR0 : out std_logic_vector(31 downto 0)
	);
end entity;

architecture rtl of standard32register is
	
	--Register Output
	q : std_logic_vector(31 downto 0)

begin

	register0 : process (clk, clr) is
	begin
      if (clr = '1') then	--If clear = '1', q = '000000000000000000000000000000000'
        q <= (others => '0'); 
	  elsif rising_edge(clk) then
		if enable = '1' then
			q <= d;
		end if;
	  end if;
	end process;
	
	additional : process (BAout, q) is
	begin
		if (BAout = 1) then
			BusMuxInR0 <= (others => '0');
		else
			BusMuxInR0 <= q;
end architecture;