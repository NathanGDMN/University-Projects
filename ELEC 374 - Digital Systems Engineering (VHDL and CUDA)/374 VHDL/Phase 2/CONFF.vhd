library ieee;
use ieee.std_logic_1164.all;

entity CONFF is
	port(
		BusInput : in std_logic_vector(31 downto 0);
		IR : in std_logic_vector(31 downto 0);
		
		CON : out std_logic
	);
end entity;

architecture rtl of CONFF is
	
	signal IR_20_19 : std_logic_vector(1 downto 0);
	signal Ra : std_logic_vector(3 downto 0);
	
	--Branch condition signals
	signal branchCondition : std_logic_vector(3 downto 0);
	
	signal ifZero : std_logic;		--0
	signal ifNotZero : std_logic;	--1
	signal ifPositive: std_logic;	--2
	signal ifNegative : std_logic;  --3
	
begin
	
	IR_20_19 <= IR(20) & IR(19);
	Ra <= IR(26) & IR(25) & IR(24) * IR(23);
	
	decodeIR : process (IR_20_19) is
	begin
		case IR_20_19 is
			when "00" =>
				branchCondition <= "0001";
			when "01" =>
				branchCondition <= "0010";
			when "10" =>
				branchCondition <= "0100";
			when "11" =>
				branchCondition <= "1000";
			when others =>
		end case;
	end process;
	
	logic : process (branchCondition, BusInput) is
	begin
		case branchCondition is
			when "0001" => 
				--branch if zero
				if Ra = "0000" then
					CON <= '1';
				else
					CON <= '0';
				end if;
			when "0001" => 
				--branch if nonzero
				if Ra /= "0000" then
					CON <= '1';
				else
					CON <= '0';
				end if;	
			when "0001" => 
				--branch if positive
				if Ra(3) = '1' then
					CON <= '0';
				else
					CON <= '1';
				end if;	
			when "0001" => 
				--branch if negative
				if Ra(3) = '0' then
					CON <= '1';
				else
					CON <= '0';
				end if;	
			when others => 
				CON <= 'X';
		end case;
	end process;

end architecture;