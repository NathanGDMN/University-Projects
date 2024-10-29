library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--This BiDirectionalBus basically turns the two modules of BusEnc and BusMux and connects them using portmap into one module.

entity BiDirectionalBus is
	--Inputs:
	port(
		--Inputs For BusMux:
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
		BusMuxInR10		: in std_logic_vector(31 downto 0);
		BusMuxInR11		: in std_logic_vector(31 downto 0);
		BusMuxInR12		: in std_logic_vector(31 downto 0);
		BusMuxInR13		: in std_logic_vector(31 downto 0);
		BusMuxInR14		: in std_logic_vector(31 downto 0);
		BusMuxInR15		: in std_logic_vector(31 downto 0);
		
		BusMuxInHI		: in std_logic_vector(31 downto 0);
		BusMuxInLO		: in std_logic_vector(31 downto 0);
		
		BusMuxInZhigh	: in std_logic_vector(31 downto 0);
		BusMuxInZlow	: in std_logic_vector(31 downto 0);
		
		BusMuxInPC		: in std_logic_vector(31 downto 0);	
		BusMuxInMDR		: in std_logic_vector(31 downto 0);
		BusMuxIn_InPort	: in std_logic_vector(31 downto 0);
		C_sign_extended	: in std_logic_vector(31 downto 0);
		
		--Inputs for 32-5 Encoder
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
		BusMuxOut : out std_logic_vector(31 downto 0)
	);
	
end entity;

architecture rtl of BiDirectionalBus is
	
	--Signals between encoder and BusMux:
	signal S0 : std_logic;
	signal S1 : std_logic;
	signal S2 : std_logic;
	signal S3 : std_logic;
	signal S4 : std_logic;
	
begin
	--Instantiate Encoder
	i_Enc : entity work.BusEnc(rtl) port map (
		--Connect Inputs
		R0out	=> R0out,
		R1out	=> R1out,
		R2out 	=> R2out,
		R3out 	=> R3out, 
		R4out 	=> R4out,
		R5out 	=> R5out,
		R6out 	=> R6out,
		R7out	=> R7out,
		R8out	=> R8out,
		R9out 	=> R9out, 
		R10out 	=> R10out,
		R11out 	=> R11out,
		R12out 	=> R12out, 
		R13out 	=> R13out, 
		R14out 	=> R14out,
		R15out 	=> R15out,
		
		HIout 	=> HIout,
		LOout 	=> LOout,
		
		Zhighout 	=> Zhighout,
		Zlowout 	=> Zlowout,
		
		PCout 	=> PCout, 
		MDRout 	=> MDRout,
		
		InPortout => InPortout,
		Cout => Cout,
		
		--Connect Signals between encoder and BusMux
		S0 => S0,
		S1 => S1,
		S2 => S2,
		S3 => S3,
		S4 => S4
	);

	--Instantiate BusMux
	i_Mux : entity work.BusMux(rtl) port map (
		--Connect Inputs
		BusMuxInR0		=> BusMuxInR0,
		BusMuxInR1		=> BusMuxInR1,
		BusMuxInR2		=> BusMuxInR2,
		BusMuxInR3		=> BusMuxInR3,
		BusMuxInR4		=> BusMuxInR4,
		BusMuxInR5		=> BusMuxInR5,
		BusMuxInR6		=> BusMuxInR6,
		BusMuxInR7		=> BusMuxInR7,
		BusMuxInR8		=> BusMuxInR8,
		BusMuxInR9		=> BusMuxInR9,
		BusMuxInR10	=> BusMuxInR10,
		BusMuxInR11	=> BusMuxInR11,
		BusMuxInR12	=> BusMuxInR12,
		BusMuxInR13	=> BusMuxInR13,
		BusMuxInR14	=> BusMuxInR14,
		BusMuxInR15	=> BusMuxInR15,
		
		BusMuxInHI		=> BusMuxInHI,
		BusMuxInLO		=> BusMuxInLO,
		
		BusMuxInZhigh	=> BusMuxInZhigh,
		BusMuxInZlow	=> BusMuxInZlow,
		
		BusMuxInPC		=> BusMuxInPC,
		BusMuxInMDR	=> BusMuxInMDR,
		BusMuxIn_InPort	=> BusMuxIn_InPort,
		C_sign_extended	=> C_sign_extended,
		
		--Connect Signals between encoder and BusMux
		S0 => S0,
		S1 => S1,
		S2 => S2,
		S3 => S3,
		S4 => S4,
		
		--Connect Output
		BusMuxOut => BusMuxOut
	);

end architecture;