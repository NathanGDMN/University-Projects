library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity BiDirectionalBus_tb is
end entity;

architecture sim of BiDirectionalBus_tb is
	
	--Bus Inputs:
	signal R0out :  std_logic := "1"; --Output = R1in
	signal R1out :  std_logic := "0";
	signal R2out :  std_logic := "0";
	signal R3out :  std_logic := "0";
	signal R4out :  std_logic := "0";
	signal R5out :  std_logic := "0";
	signal R6out :  std_logic := "0";
	signal R7out :  std_logic := "0";
	signal R8out :  std_logic := "0";
	signal R9out :  std_logic := "0";
	signal R10out :  std_logic := "0";
	signal R11out :  std_logic := "0";
	signal R12out :  std_logic := "0";
	signal R13out :  std_logic := "0";
	signal R14out :  std_logic := "0";
	signal R15out :  std_logic := "0"; 
		
	signal HIout :  std_logic := "0";
	signal LOout :  std_logic := "0";
		
	signal Zhighout :  std_logic := "0";
	signal Zlowout : std_logic := "0";
		
	signal PCout : std_logic := "0";
	signal MDRout : std_logic := "0";
		
	signal InPortout : std_logic := "0";
	signal Cout : std_logic := "0";
	
	signal BusMuxInR0		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR1		:  std_logic_vector(31 downto 0) := (others =>'1'); --R1 = "11111111..."
	signal BusMuxInR2		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR3		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR4		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR5		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR6		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR7		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR8		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR9		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR10		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR11		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR12		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR13		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR14		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInR15		:  std_logic_vector(31 downto 0) := (others =>'0');
		
	signal BusMuxInHI		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInLO		:  std_logic_vector(31 downto 0) := (others =>'0');
		
	signal BusMuxInZhigh	:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxInZlow	:  std_logic_vector(31 downto 0) := (others =>'0');
		
	signal BusMuxInPC		:  std_logic_vector(31 downto 0) := (others =>'0');	
	signal BusMuxInMDR		:  std_logic_vector(31 downto 0) := (others =>'0');
	signal BusMuxIn_InPort	:  std_logic_vector(31 downto 0) := (others =>'0');
	signal C_sign_extended	:  std_logic_vector(31 downto 0) := (others =>'0');
	
	--Bus Output
	signal Output : std_logic_vector(31 downto 0);
	
	--Instantiate Registers
	i_Bus : entity work.BiDirectionalBus(rtl) port map (
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
		
		BusMuxOut => Output;
	);
	
begin

end architecture;