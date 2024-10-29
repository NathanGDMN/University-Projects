library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity BusEnc is
	port(
		--Inputs
		R0out : in std_logic;
		R1out : in std_logic;
		R2out : in std_logic;
		R3out : in std_logic;
		R4out : in std_logic;
		R5out : in std_logic;
		R6out : in std_logic;
		R7out : in std_logic;
		R8out : in std_logic;
		R9out : in std_logic;
		R10out : in std_logic;
		R11out : in std_logic;
		R12out : in std_logic;
		R13out : in std_logic;
		R14out : in std_logic;
		R15out : in std_logic;
		
		HIout : in std_logic;
		LOout : in std_logic;
		
		Zhighout : in std_logic;
		Zlowout : in std_logic;
		
		PCout : in std_logic;
		MDRout : in std_logic;
		
		InPortout : in std_logic;
		Cout : in std_logic;
		
		--Output
		S0 : out std_logic;
		S1 : out std_logic;
		S2 : out std_logic;
		S3 : out std_logic;
		S4 : out std_logic
		
	);
end entity;

architecture rtl of BusEnc is 

	signal input : std_logic_vector(31 downto 0); --Concatenate all inputs into a single 32 bit vector 

begin

	process (
		R0out, R1out, R2out, R3out, R4out, R5out, R6out, R7out, R8out, R9out, R10out, R11out, R12out, R13out, R14out, R15out, 
		HIout, LOout, Zhighout, Zlowout, PCout, MDRout, InPortout, Cout
	) is 
	begin
		
		input <= "00000000" & Cout & InPortout & MDRout & PCout & Zlowout & Zhighout & LOout & HIout & R15out & R14out & R13out & R12out & R11out & R10out & R9out & R8out & R7out & R6out & R5out & R4out & R3out & R2out & R1out & R0out;
		--*8 Zeros are added on to the front cause input is a 32 bit vector but we only take 24 inputs
		
		case input is
			when "00000000000000000000000000000001"  =>
				S0 <= '0';
				S1 <= '0';
				S2 <= '0';
				S3 <= '0';
				S4 <= '0';
			when "00000000000000000000000000000010"  =>
				S0 <=  '0';
				S1 <=  '0';
				S2 <=  '0';
				S3 <=  '0';
				S4 <= '1';
			when "00000000000000000000000000000100"  =>
				S0 <= '0';
				S1 <= '0';
				S2 <= '0';
				S3 <= '1';
				S4 <='0';
			when "00000000000000000000000000001000"  =>
				S0 <= '0';
				S1 <= '0';
				S2 <= '0';
				S3 <= '1';
				S4 <= '1';
			when "00000000000000000000000000010000"  =>
				S0 <= '0';
				S1 <= '0';
				S2 <= '1';
				S3 <= '0';
				S4 <= '0';
			when "00000000000000000000000000100000"  =>
				S0 <= '0';
				S1 <= '0';
				S2 <= '1';
				S3 <= '0';
				S4 <= '1';
			when "00000000000000000000000001000000"  =>
				S0 <= '0';
				S1 <= '0';
				S2 <= '1';
				S3 <= '1';
				S4 <= '0';
			when "00000000000000000000000010000000"  =>
				S0 <= '0';
				S1 <= '0';
				S2 <= '1';
				S3 <= '1';
				S4 <= '1';
			when "00000000000000000000000100000000"  =>
				S0 <= '0';
				S1 <= '1';
				S2 <= '0';
				S3 <= '0';
				S4 <= '0';
			when "00000000000000000000001000000000"  =>
				S0 <= '0';
				S1 <= '1';
				S2 <= '0';
				S3 <= '0';
				S4 <= '1';
			when "00000000000000000000010000000000"  =>
				S0 <= '0';
				S1 <= '1';
				S2 <= '0';
				S3 <= '1';
				S4 <= '0';
			when "00000000000000000000100000000000"  =>
				S0 <= '0';
				S1 <= '1';
				S2 <= '0';
				S3 <= '1';
				S4 <= '1';
			when "00000000000000000001000000000000"  =>
				S0 <= '0';
				S1 <= '1';
				S2 <= '1';
				S3 <= '0';
				S4 <= '0';
			when "00000000000000000010000000000000"  =>
				S0 <= '0';
				S1 <= '1';
				S2 <= '1';
				S3 <= '0';
				S4 <= '1';
			when "00000000000000000100000000000000"  =>
				S0 <= '0';
				S1 <= '1';
				S2 <= '1';
				S3 <= '1';
				S4 <= '0';
			when "00000000000000001000000000000000"  =>
				S0 <= '0';
				S1 <= '1';
				S2 <= '1';
				S3 <= '1';
				S4 <= '1';
			when "00000000000000010000000000000000"  =>
				S0 <= '1';
				S1 <= '0';
				S2 <= '0';
				S3 <= '0';
				S4 <= '0';
			when "00000000000000100000000000000000"  =>
				S0 <= '1';
				S1 <= '0';
				S2 <= '0';
				S3 <= '0';
				S4 <= '1';
			when "00000000000001000000000000000000"  =>
				S0 <= '1';
				S1 <= '0';
				S2 <= '0';
				S3 <= '1';
				S4 <= '0';
			when "00000000000010000000000000000000"  =>
				S0 <= '1';
				S1 <= '0';
				S2 <= '0';
				S3 <= '1';
				S4 <= '1';
			when "00000000000100000000000000000000"  =>
				S0 <= '1';
				S1 <= '0';
				S2 <= '1';
				S3 <= '0';
				S4 <= '0';
			when "00000000001000000000000000000000"  =>
				S0 <= '1';
				S1 <= '0';
				S2 <= '1';
				S3 <= '0';
				S4 <= '1';
			when "00000000010000000000000000000000"  =>
				S0 <= '1';
				S1 <= '0';
				S2 <= '1';
				S3 <= '1';
				S4 <= '0';
			when "00000000100000000000000000000000"  =>
				S0 <= '1';
				S1 <= '0';
				S2 <= '1';
				S3 <= '1';
				S4 <= '1';
			when "00000001000000000000000000000000"  =>
				S0 <= '1';
				S1 <= '1';
				S2 <= '0';
				S3 <= '0';
				S4 <= '0';
			when others => --Indicate an error if input does not equal one of above values
				S0 <= 'X';
				S1 <= 'X';
				S2 <= 'X';
				S3 <= 'X';
				S4 <= 'X';
		end case;
	
	
	end process;
	
end architecture;