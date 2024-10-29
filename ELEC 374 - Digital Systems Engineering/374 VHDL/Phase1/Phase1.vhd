library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--This file is for connecting all of the components of Phase1 

entity Phase1 is
	port (
	--Clear:
	Clear : in std_logic; 
	
	--Clock Signal:
	Clock : in std_logic;

	---Control Signals for telling Bus what register value to Output---
	R0out 	: in std_logic;
	R1out 	: in std_logic;
	R2out 	: in std_logic;
	R3out 	: in std_logic;
	R4out 	: in std_logic;
	R5out 	: in std_logic;
	R6out 	: in std_logic;
	R7out 	: in std_logic;
	R8out 	: in std_logic;
	R9out 	: in std_logic;
	R10out 	: in std_logic;
	R11out 	: in std_logic;
	R12out 	: in std_logic;
	R13out 	: in std_logic;
	R14out 	: in std_logic;
	R15out 	: in std_logic;
		
	HIout 	: in std_logic;
	LOout 	: in std_logic;
		
	Zhighout: in std_logic;
	Zlowout : in std_logic;
		
	PCout 	: in std_logic;
	MDRout 	: in std_logic;
		
	InPortout : in std_logic;
	Cout 	: in std_logic;
	
	---Control Signals for telling which register to save output from Bus (enable)---
	R0in 	: in std_logic;
	R1in 	: in std_logic;
	R2in 	: in std_logic;
	R3in 	: in std_logic;
	R4in 	: in std_logic;
	R5in 	: in std_logic;
	R6in 	: in std_logic;
	R8in 	: in std_logic;
	R9in 	: in std_logic;
	R10in 	: in std_logic;
	R11in 	: in std_logic;
	R12in 	: in std_logic;
	R13in 	: in std_logic;
	R14in 	: in std_logic;
	R15in 	: in std_logic;
	
	HIin 	: in std_logic;
	LOin 	: in std_logic;
	
	Zhighin : in std_logic;
	Zlowin 	: in std_logic;
	
	PCin 	: in std_logic;
	MDRin 	: in std_logic;
	
	InPortin: in std_logic;
	Cin 	: in std_logic
	
	--Y Register--
	Yin : in std_logic; --On the diagram, you can write to Y but only the ALU can recieve output
	
	---Control Signal for selecting ALU operation:
	ALU_Sel : std_logic_vector(3 downto 0);
	);
end entity;

architecture sim of Phase1 is
	--Signals Inbetween registers and Bus:
	signal BusMuxInR0		:  std_logic_vector(31 downto 0);
	signal BusMuxInR1		:  std_logic_vector(31 downto 0);
	signal BusMuxInR2		:  std_logic_vector(31 downto 0);
	signal BusMuxInR3		:  std_logic_vector(31 downto 0);
	signal BusMuxInR4		:  std_logic_vector(31 downto 0);
	signal BusMuxInR5		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInR6		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInR7		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInR8		:  std_logic_vector(31 downto 0);
	signal BusMuxInR9		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInR10		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInR11		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInR12		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInR13		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInR14		:  std_logic_vector(31 downto 0);
	signal BusMuxInR15		:  std_logic_vector(31 downto 0);
		
	signal BusMuxInHI		:  std_logic_vector(31 downto 0) ;
	signal BusMuxInLO		:  std_logic_vector(31 downto 0) ;
		
	signal BusMuxInZhigh	:  std_logic_vector(31 downto 0) ;
	signal BusMuxInZlow		:  std_logic_vector(31 downto 0) ;
		
	signal BusMuxInPC		:  std_logic_vector(31 downto 0) ;	
	signal BusMuxInMDR		:  std_logic_vector(31 downto 0) ;
	signal BusMuxIn_InPort	:  std_logic_vector(31 downto 0) ;
	signal C_sign_extended	:  std_logic_vector(31 downto 0) ;
	
	signal BusMuxOut : std_logic_vector(31 downto 0);
	
	--Signals Inbetween ALU registers and Bus:
	signal AluInY			:  std_logic_vector(31 downto 0) ; --Signal for A
	signal AluOutput		:  std_logic_vector(64 downto 0) ;
	signal AluCarryFlag		:  std_logic;
	
	begin
	----------Instantiate Bus----------
	i_Bus : entity work.BiDirectionalBus(rtl) port map (
		--Control Signals
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
		
		InPortout 	=> InPortout,
		Cout 		=> Cout,
		
		--Bus inputs
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
		BusMuxInR10		=> BusMuxInR10,
		BusMuxInR11		=> BusMuxInR11,
		BusMuxInR12		=> BusMuxInR12,
		BusMuxInR13		=> BusMuxInR13,
		BusMuxInR14		=> BusMuxInR14,
		BusMuxInR15		=> BusMuxInR15,
		
		BusMuxInHI		=> BusMuxInHI,
		BusMuxInLO		=> BusMuxInLO,
		
		BusMuxInZhigh	=> BusMuxInZhigh,
		BusMuxInZlow	=> BusMuxInZlow,
		
		BusMuxInPC		=> BusMuxInPC,
		BusMuxInMDR		=> BusMuxInMDR,
		BusMuxIn_InPort	=> BusMuxIn_InPort,
		C_sign_extended	=> C_sign_extended,
		
		BusMuxOut => BusMuxOut
	);
	
	----------Instantiate Registers----------
	i_R0 : entity work.R0(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R0in,
		d => BusMuxOut,
		q => BusMuxInR0
	);
	i_R1 : entity work.R1(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R1in,
		d => BusMuxOut,
		q => BusMuxInR1
	);
	i_R2 : entity work.R2(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R2in,
		d => BusMuxOut,
		q => BusMuxInR2
	);
	i_R3 : entity work.R3(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R3in,
		d => BusMuxOut,
		q => BusMuxInR3
	);
	i_R4 : entity work.R4(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R4in,
		d => BusMuxOut,
		q => BusMuxInR4
	);
	i_R5 : entity work.R5(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R5in,
		d => BusMuxOut,
		q => BusMuxInR5
	);
	i_R6 : entity work.R6(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R6in,
		d => BusMuxOut,
		q => BusMuxInR6
	);
	i_R7 : entity work.R7(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R7in,
		d => BusMuxOut,
		q => BusMuxInR7
	);
	i_R8 : entity work.R8(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R8in,
		d => BusMuxOut,
		q => BusMuxInR8
	);
	i_R9 : entity work.R9(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R9in,
		d => BusMuxOut,
		q => BusMuxInR9
	);
	i_R10 : entity work.R10(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R10in,
		d => BusMuxOut,
		q => BusMuxInR10
	);
	i_R11 : entity work.R11(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R11in,
		d => BusMuxOut,
		q => BusMuxInR11
	);
	i_R12 : entity work.R12(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R12in,
		d => BusMuxOut,
		q => BusMuxInR12
	);
	i_R13 : entity work.R13(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R13in,
		d => BusMuxOut,
		q => BusMuxInR13
	);
	i_R14 : entity work.R14(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R14in,
		d => BusMuxOut,
		q => BusMuxInR14
	);
	i_R15 : entity work.R15(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => R15in,
		d => BusMuxOut,
		q => BusMuxInR15
	);
	i_HI : entity work.HI(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => HIin,
		d => BusMuxOut,
		q => BusMuxInHI
	);
	i_LO : entity work.LO(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => LOin,
		d => BusMuxOut,
		q => BusMuxInLO
	);
	
	i_Zhigh : entity work.Zhigh(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => Zhighin,
		d => BusMuxOut,
		q => BusMuxInZhigh
	);
	i_Zlow : entity work.Zlow(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => Zhighlow,
		d => BusMuxOut,
		q => BusMuxInZlow
	);
	
	i_PC : entity work.PC(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => PCin,
		d => BusMuxOut,
		q => BusMuxInPC
	);
	i_MDR : entity work.MDR(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => MDRin,
		d => BusMuxOut,
		q => BusMuxInMDr
	);
	
	i_InPort : entity work.InPort(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => InPortin,
		d => BusMuxOut,
		q => BusMuxIn_InPort
	);
	
	i_C : entity work.C(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => Cin,
		d => BusMuxOut,
		q => C_sign_extended
	);
	
	--Y Register
	i_Y : entity work.Y(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => Yin,
		d => BusMuxOut, --Recieves input from Bus
		q => AluInY		--Outputs to ALU
	);
	
	
	i_IR : entity work.IR(rtl) port map (
		clr => Clear,
		clk => Clock,
		enable => PCin,
		d => BusMuxOut,
		q => BusMuxInIR
	);
	----------Instantiate ALU----------
	
	
end architecture;