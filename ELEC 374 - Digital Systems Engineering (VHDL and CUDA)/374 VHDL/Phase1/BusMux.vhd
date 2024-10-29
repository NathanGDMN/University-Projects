library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity BusMux is
	port(
		--Controls Signals (From 32-to-5 encoder)
		S0 : in std_logic;
		S1 : in std_logic;
		S2 : in std_logic;
		S3 : in std_logic;
		S4 : in std_logic;
	
		--Inputs
		BusMuxInR0		: in std_logic_vector(31 downto 0);
		BusMuxInR1		: in std_logic_vector(31 downto 0);
		BusMuxInR2		: in std_logic_vector(31 downto 0);
		BusMuxInR3		: in std_logic_vector(31 downto 0);
		BusMuxInR4		: in std_logic_vector(31 downto 0);
		BusMuxInR5		: in std_logic_vector(31 downto 0);
		BusMuxInR6		: in std_logic_vector(31 downto 0);
		BusMuxInR7		: in std_logic_vector(31 downto 0);
		BusMuxInR8		: in std_logic_vector(31 downto 0);
		BusMuxInR9		: in std_logic_vector(31 downto 0);
		BusMuxInR10	: in std_logic_vector(31 downto 0);
		BusMuxInR11	: in std_logic_vector(31 downto 0);
		BusMuxInR12	: in std_logic_vector(31 downto 0);
		BusMuxInR13	: in std_logic_vector(31 downto 0);
		BusMuxInR14	: in std_logic_vector(31 downto 0);
		BusMuxInR15	: in std_logic_vector(31 downto 0);
		
		BusMuxInHI		: in std_logic_vector(31 downto 0);
		BusMuxInLO		: in std_logic_vector(31 downto 0);
		
		BusMuxInZhigh	: in std_logic_vector(31 downto 0);
		BusMuxInZlow	: in std_logic_vector(31 downto 0);
		
		BusMuxInPC		: in std_logic_vector(31 downto 0);	
		BusMuxInMDR	: in std_logic_vector(31 downto 0);
		BusMuxIn_InPort	: in std_logic_vector(31 downto 0);
		C_sign_extended	: in std_logic_vector(31 downto 0);
		
		--Output
		BusMuxOut : out std_logic_vector(31 downto 0)
	);
end entity;

architecture rtl of BusMux is

	signal Sel : std_logic_vector(4 downto 0); --Concatenate the five control signals into one 5-bit select signal

begin

	process (
		S0, S1, S2, S3, S4, 
		BusMuxInR0, BusMuxInR1, BusMuxInR2, BusMuxInR3, BusMuxInR4, BusMuxInR5, BusMuxInR6, BusMuxInR7, BusMuxInR8, BusMuxInR9, BusMuxInR10,BusMuxInR11, BusMuxInR12, BusMuxInR13, BusMuxInR14, BusMuxInR15, BusMuxInHI, BusMuxInLo, BusMuxInZhigh, BusMuxInZlow, BusMuxInPC, BusMuxInMDR, BusMuxIn_InPort, C_sign_extended
	) is
	begin
	
		Sel <= S0 & S1 & S2 & S3 & S4; --Concatenate the five control signals into one 5-bit select signal
		case Sel is 
			when "00000" =>
				BusMuxOut <= BusMuxInR0;
			when "00001" =>
				BusMuxOut <= BusMuxInR1;	
			when "00010" =>
				BusMuxOut <= BusMuxInR2;	
			when "00011" =>
				BusMuxOut <= BusMuxInR3;	
			when "00100" =>
				BusMuxOut <= BusMuxInR4;	
			when "00101" =>
				BusMuxOut <= BusMuxInR5;	
			when "00110" =>
				BusMuxOut <= BusMuxInR6;	
			when "00111" =>
				BusMuxOut <= BusMuxInR7;	
			when "01000" =>
				BusMuxOut <= BusMuxInR8;	
			when "01001" =>
				BusMuxOut <= BusMuxInR9;	
			when "01010" =>
				BusMuxOut <= BusMuxInR10;	
			when "01011" =>
				BusMuxOut <= BusMuxInR11;
			when "01100" =>
				BusMuxOut <= BusMuxInR12;
			when "01101" =>
				BusMuxOut <= BusMuxInR13;
			when "01110" =>
				BusMuxOut <= BusMuxInR14;
			when "01111" =>
				BusMuxOut <= BusMuxInR15;
			when "10000" =>
				BusMuxOut <= BusMuxInHI;
			when "10001" =>	
				BusMuxOut <= BusMuxInLO;
			when "10010" =>	
				BusMuxOut <= BusMuxInZhigh;
			when "10011" =>
				BusMuxOut <= BusMuxInZlow;
			when "10100" =>
				BusMuxOut <= BusMuxInPC;
			when "10101" =>
				BusMuxOut <= BusMuxInMDR;
			when "10110" =>
				BusMuxOut <= BusMuxIn_InPort;
			when "10111" =>
				BusMuxOut <= C_sign_extended;
			--Unused select values:
			--when "11000" =>
			--when "11001" =>
			--when "11010" =>
			--when "11011" =>
			--when "11100" =>
			--when "11101" =>
			--when "11110" =>
			--when "11111" =>
			when others => --Indicate an error if Sel does not equal one of above values
				BusMuxOut <= (others => 'X');
		end case;
		
	end process;	
end architecture;