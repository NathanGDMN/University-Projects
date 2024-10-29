library ieee;
use ieee.std_logic_1164.all;

entity T11_StdLogicVectorTb is
end entity;

architecture sim of T11_StdLogicVectorTb is

	--Below is the syntax for how you declare a signal vector. You can view the std_vector type as a single wire and the std_logic_vector as a collection of wires.
	signal Slv1 : std_logic_vector(7 downto 0);
	signal Slv2 : std_logic_vector(7 downto 0) := (others => '0'); --To assign each bit in a vector a value, we use (others => '0')
	signal Slv3 : std_logic_vector(7 downto 0) := (others => '1'); 
	signal Slv4 : std_logic_vector(7 downto 0) := x"AA"; --You can also assign the bit values using hexadecimal
	signal Slv5 : std_logic_vector(7 to 0) := "10101010"; --Or using decimal
	signal Slv6 : std_logic_vector(7 downto 0) := "00000001";
	
	--*Note you can change the 'downto' in the vector declaration to 'to' to reverse the ways the bits are assinged values--instead of the first bit in '10' being in the 2 position its in the 1 position (big vs little endian)
	
begin

	--Shift register
	process is
	begin
		
		wait for 10 ns;
		
		for i in Slv6'left downto Slv6'right +1 loop --Shifting all bits in Slv6 one position to the left every 10ns 
			--*Note the Slv6'left is a way of making this loop apply to all bit regardless of vector size. The above is equivalent to:
			--for i in 7 downto 1 loop 
			Slv6(i) <= Slv6(i-1);
		end loop;
		
		Slv6(Slv6'right) <= Slv6(Slv6'left); --Slv6(0) <= Slv6(7)
	
	end process;

end architecture;