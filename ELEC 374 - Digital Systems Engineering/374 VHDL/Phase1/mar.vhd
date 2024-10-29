-- ------------------------------------------------------
-- mar.vhd: code for an MAR reg.
--
-- B. Lachhman
-- March 1st 2023
-- ------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity mar is
port(
    mar_clk, mar_clr, mar_en : in std_logic;
    mar_datain : in std_logic_vector(31 downto 0);
    mar_dataout : out std_logic_vector(31 downto 0)
);
end entity;

architecture behavioral of mar is
begin
    process(mar_clk, mar_clr, mar_en, mar_datain)
        begin
        if(mar_clr = '1') then
            mar_dataout <= (others => '0');
        elsif(mar_clk'event and mar_clk = '1') then
            if(mar_en = '0') then
                mar_dataout <= mar_datain;
            end if;
        end if;
    end process;
end behavioral;