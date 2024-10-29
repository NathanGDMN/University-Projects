library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ALUTb is
end entity;

architecture sim of ALUTb is

	--Signals to change:
	signal operationSelector : std_logic_vector(3 downto 0);
	signal A, B	: std_logic_vector(7 downto 0);
	--Signals to observe:
	signal output : std_logic_vector(7 downto 0);
	signal carry : std_logic;
	
	--Possible operations for easy testing:
	constant Addition : std_logic_vector (3 downto 0) := "0000";
	constant Subtraction : std_logic_vector (3 downto 0) := "0001";
	constant Multiplication : std_logic_vector (3 downto 0) := "0010";
	constant Division : std_logic_vector (3 downto 0) := "0011";
	constant LSL : std_logic_vector (3 downto 0) := "0100";
	constant LSR : std_logic_vector (3 downto 0) := "0101";
	constant RotateL : std_logic_vector (3 downto 0) := "0110";
	constant RotateR : std_logic_vector (3 downto 0) := "0111";
	constant LogicAnd : std_logic_vector (3 downto 0) := "1000";
	constant LogicOr : std_logic_vector (3 downto 0) := "1001";
	constant LogicXor : std_logic_vector (3 downto 0) := "1010";
	constant LogicNor : std_logic_vector (3 downto 0) := "1011";
	constant LogicNand : std_logic_vector (3 downto 0) := "1100";
	constant LogicXnor : std_logic_vector (3 downto 0) := "1101";
	constant GreaterComp : std_logic_vector (3 downto 0) := "1110";
	constant EqualComp : std_logic_vector (3 downto 0) := "1111";
	
begin
	--Instantiate ALU
	i_ALU : entity work.ALU(Behavioral) port map (
		ALU_Sel => operationSelector,
		A => A,
		B => B,
		ALU_Out => output,
		Carryout => carry
	);
	
	process is	--Test process
	begin
		A <= "00001000"; --Set A=8
		B <= "00000010"; --Set B=2
		
		--Select Operation
		operationSelector <= Addition;
		
		wait;
	end process;


end architecture;