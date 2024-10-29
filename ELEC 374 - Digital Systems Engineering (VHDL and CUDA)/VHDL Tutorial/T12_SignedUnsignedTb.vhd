library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all; --How to import signed and unsigned types

entity T12_SignedUnsignedTb is
end entity;

architecture sim of T12_SignedUnsignedTb is
	
	--So far the vectors we've shown are just seen a s collection of 1's  and 0's. If we want to use the value that the 1's and 0's of the vector represent (ex '1000' = 8), we will need to use signed and unsigned keywords.
	--To use the signed and unsigned keyword you will need to import a library (shown above)

	signal UnsCnt : unsigned(7 downto 0) := (others =>'0');
	signal SigCnt : signed(7 downto 0) := (others =>'0');
	
	signal Uns4 : unsigned(4 downto 0) := "1000";
	signal Sig4 : signed(4 downto 0) := "1000";
	
	signal Uns8 : unsigned(7 downto 0) := (others =>'0');
	signal Sig8 : signed(7 downto 0) := (others =>'0');
	
begin

	process is
	begin
		
		wait for 10 ns;
		
		--Wrapping counter
		--When you try to add past the maximum value of these counters (FF) they restart at 0 (00)
		UnsCnt <= UnsCnt + 1;
		SigCnt <= SigCnt + 1;
		
		--Adding Signals
		Uns8 <= Uns8 + Uns4;
		Sig8 <= Sig8 +Sig4;
		
		--*Note: you will see when adding the signals, that there is a difference betwene the signed and unsigned types.
		--Signed type may represent both positive and negative integers, while the unsigned type may only represent positve integers (including 0)
		--The signed type tells if a number is positive or negative by the sign bit (the left most bit), so the 1000 above is actually interpreted as -8
		
	
	end process;

end architecture;