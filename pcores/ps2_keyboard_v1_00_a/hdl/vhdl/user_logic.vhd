------------------------------------------------------------------------------
-- user_logic.vhd - entity/architecture pair
------------------------------------------------------------------------------
--
-- ***************************************************************************
-- ** Copyright (c) 1995-2011 Xilinx, Inc.  All rights reserved.            **
-- **                                                                       **
-- ** Xilinx, Inc.                                                          **
-- ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
-- ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
-- ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
-- ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
-- ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
-- ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
-- ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
-- ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
-- ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
-- ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
-- ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
-- ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
-- ** FOR A PARTICULAR PURPOSE.                                             **
-- **                                                                       **
-- ***************************************************************************
--
------------------------------------------------------------------------------
-- Filename:          user_logic.vhd
-- Version:           1.00.a
-- Description:       User logic.
-- Date:              Sun Nov 24 14:04:03 2013 (by Create and Import Peripheral Wizard)
-- VHDL Standard:     VHDL'93
------------------------------------------------------------------------------
-- Naming Conventions:
--   active low signals:                    "*_n"
--   clock signals:                         "clk", "clk_div#", "clk_#x"
--   reset signals:                         "rst", "rst_n"
--   generics:                              "C_*"
--   user defined types:                    "*_TYPE"
--   state machine next state:              "*_ns"
--   state machine current state:           "*_cs"
--   combinatorial signals:                 "*_com"
--   pipelined or register delay signals:   "*_d#"
--   counter signals:                       "*cnt*"
--   clock enable signals:                  "*_ce"
--   internal version of output port:       "*_i"
--   device pins:                           "*_pin"
--   ports:                                 "- Names begin with Uppercase"
--   processes:                             "*_PROCESS"
--   component instantiations:              "<ENTITY_>I_<#|FUNC>"
------------------------------------------------------------------------------

-- DO NOT EDIT BELOW THIS LINE --------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

-- DO NOT EDIT ABOVE THIS LINE --------------------

--USER libraries added here

------------------------------------------------------------------------------
-- Entity section
------------------------------------------------------------------------------
-- Definition of Generics:
--   C_NUM_REG                    -- Number of software accessible registers
--   C_SLV_DWIDTH                 -- Slave interface data bus width
--
-- Definition of Ports:
--   Bus2IP_Clk                   -- Bus to IP clock
--   Bus2IP_Resetn                -- Bus to IP reset
--   Bus2IP_Data                  -- Bus to IP data bus
--   Bus2IP_BE                    -- Bus to IP byte enables
--   Bus2IP_RdCE                  -- Bus to IP read chip enable
--   Bus2IP_WrCE                  -- Bus to IP write chip enable
--   IP2Bus_Data                  -- IP to Bus data bus
--   IP2Bus_RdAck                 -- IP to Bus read transfer acknowledgement
--   IP2Bus_WrAck                 -- IP to Bus write transfer acknowledgement
--   IP2Bus_Error                 -- IP to Bus error response
------------------------------------------------------------------------------

entity user_logic is
  generic
  (
    -- ADD USER GENERICS BELOW THIS LINE ---------------
    --USER generics added here
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_NUM_REG                      : integer              := 4;
    C_SLV_DWIDTH                   : integer              := 32
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
    
	 --USER ports added here
--	 clk, rst : in std_logic;
		ps2d, ps2c : in std_logic;
--		rx_en : in std_logic;
--		rx_done_tick : out std_logic;
		shift_en : out std_logic;
		dout : out std_logic_vector(7 downto 0);
		myinterrupt : out std_logic;
		
    -- ADD USER PORTS ABOVE THIS LINE ------------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol ports, do not add to or delete
    Bus2IP_Clk                     : in  std_logic;
    Bus2IP_Resetn                  : in  std_logic;
    Bus2IP_Data                    : in  std_logic_vector(C_SLV_DWIDTH-1 downto 0);
    Bus2IP_BE                      : in  std_logic_vector(C_SLV_DWIDTH/8-1 downto 0);
    Bus2IP_RdCE                    : in  std_logic_vector(C_NUM_REG-1 downto 0);
    Bus2IP_WrCE                    : in  std_logic_vector(C_NUM_REG-1 downto 0);
    IP2Bus_Data                    : out std_logic_vector(C_SLV_DWIDTH-1 downto 0);
    IP2Bus_RdAck                   : out std_logic;
    IP2Bus_WrAck                   : out std_logic;
    IP2Bus_Error                   : out std_logic
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );

  attribute MAX_FANOUT : string;
  attribute SIGIS : string;

  attribute SIGIS of Bus2IP_Clk    : signal is "CLK";
  attribute SIGIS of Bus2IP_Resetn : signal is "RST";

end entity user_logic;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture IMP of user_logic is

  --USER signal declarations added here, as needed for user logic
	type statetype is (idle, dps, load);
	signal state_reg, state_next : statetype;
	-- filter
	signal filter_reg, filter_next : std_logic_vector(7 downto 0);
	signal f_ps2c_reg, f_ps2c_next : std_logic;

	signal b_reg, b_next : std_logic_vector(10 downto 0);
	signal n_reg, n_next : unsigned(3 downto 0);
	signal shift_reg, shift_next : std_logic := '0';
	
	signal fall_edge : std_logic;
	signal end_buff : std_logic;
--	signal rx_en : std_logic;
	signal zeros : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
	
  ------------------------------------------
  -- Signals for user logic slave model s/w accessible register example
  ------------------------------------------
  signal slv_reg0                       : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal slv_reg1                       : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal slv_reg2                       : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal slv_reg3                       : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal slv_reg_write_sel              : std_logic_vector(3 downto 0);
  signal slv_reg_read_sel               : std_logic_vector(3 downto 0);
  signal slv_ip2bus_data                : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal slv_read_ack                   : std_logic;
  signal slv_write_ack                  : std_logic;

begin

  --USER logic implementation added here

-- filter 
process (Bus2IP_Clk, Bus2IP_Resetn) 
begin
  if (Bus2IP_Resetn = '0') then
    filter_reg <= (others => '0');
    f_ps2c_reg <= '0';
  elsif (Bus2IP_Clk'event and Bus2IP_Clk='1') then
    filter_reg <= filter_next;
    f_ps2c_reg <= f_ps2c_next;
  end if;
end process;


filter_next <= ps2c & filter_reg(7 downto 1);
f_ps2c_next <= '1' when filter_reg = "11111111" else
               '0' when filter_reg = "00000000" else
               f_ps2c_reg;

fall_edge <= f_ps2c_reg and (not f_ps2c_next);

-- rx_en will need to be set to 1 always by this design
--rx_en <= '1';
zeros <= (others => '0');

-- registers
process (Bus2IP_Clk, Bus2IP_Resetn)
begin
	if (Bus2IP_Resetn = '0') then
		state_reg <= idle;
		n_reg <= (others => '0');
		b_reg <= (others => '0');
		slv_reg0 <= (others => '0');
	elsif (Bus2IP_Clk'event and Bus2IP_Clk='1') then
		state_reg <= state_next;
		n_reg <= n_next;
		b_reg <= b_next;
		shift_reg <= shift_reg;
		slv_reg0 <= zeros or  b_reg(8 downto 1);
	end if;
end process;

-- next-state logic
process(state_reg, n_reg, b_reg, fall_edge, ps2d)

begin
	myinterrupt <= '0';
	--rx_done_tick <= '0';
	state_next <= state_reg;
	n_next <= n_reg;
	b_next <= b_reg;
  
  case state_reg is 
    when idle =>
--      myinterrupt <= '1';
      if (fall_edge = '1') then 
        --shift in start bit
        b_next <= ps2d & b_reg(10 downto 1);
        n_next <= "1001"; -- set count to 8 again
        state_next <= dps;
      end if;
    when dps => 
 --     myinterrupt <= '0';
      if (fall_edge = '1' ) then
        b_next <= ps2d & b_reg(10 downto 1);
        if (n_reg = 0) then 
          state_next <= load;
        else 
          n_next <= n_reg - 1;
        end if;
      end if;
    when load =>
		-- here we handle if signal f0 and following signal are 
		-- asserted - we don't want to transmit them to dout.
      -- one more state to complete last shift
		state_next <= idle;
--		rx_done_tick <= '1';
		myinterrupt <= '1';
		if (b_reg(8 downto 0) = x"12" or b_reg(8 downto 0) = x"59") then
			shift_next <= not shift_reg;
			if (shift_reg = '1') then
--				rx_done_tick <= '0';
				myinterrupt <= '0';
			end if;
		elsif (b_reg(8 downto 0) = "11110000") then
			end_buff <= '1';
--			rx_done_tick <= '0';
			myinterrupt <= '0';
		elsif (end_buff = '1') then
			end_buff <= '0';	
--			rx_done_tick <= '0';
			myinterrupt <= '0';
		end if;
  end case;
end process;

shift_en <= shift_reg;
dout <= b_reg(8 downto 1);



--myinterrupt <= '1';

--  ------------------------------------------
--  -- Example code to read/write user logic slave model s/w accessible registers
--  -- 
--  -- Note:
--  -- The example code presented here is to show you one way of reading/writing
--  -- software accessible registers implemented in the user logic slave model.
--  -- Each bit of the Bus2IP_WrCE/Bus2IP_RdCE signals is configured to correspond
--  -- to one software accessible register by the top level template. For example,
--  -- if you have four 32 bit software accessible registers in the user logic,
--  -- you are basically operating on the following memory mapped registers:
--  -- 
--  --    Bus2IP_WrCE/Bus2IP_RdCE   Memory Mapped Register
--  --                     "1000"   C_BASEADDR + 0x0
--  --                     "0100"   C_BASEADDR + 0x4
--  --                     "0010"   C_BASEADDR + 0x8
--  --                     "0001"   C_BASEADDR + 0xC
--  -- 
--  ------------------------------------------
  slv_reg_write_sel <= Bus2IP_WrCE(3 downto 0);
  slv_reg_read_sel  <= Bus2IP_RdCE(3 downto 0);
  slv_write_ack     <= Bus2IP_WrCE(0) or Bus2IP_WrCE(1) or Bus2IP_WrCE(2) or Bus2IP_WrCE(3);
  slv_read_ack      <= Bus2IP_RdCE(0) or Bus2IP_RdCE(1) or Bus2IP_RdCE(2) or Bus2IP_RdCE(3);
--
--  -- implement slave model software accessible register(s)
--  SLAVE_REG_WRITE_PROC : process( Bus2IP_Clk ) is
--  begin
--
--    if Bus2IP_Clk'event and Bus2IP_Clk = '1' then
--      if Bus2IP_Resetn = '0' then
--        slv_reg0 <= (others => '0');
--        slv_reg1 <= (others => '0');
--        slv_reg2 <= (others => '0');
--        slv_reg3 <= (others => '0');
--      else
--        case slv_reg_write_sel is
--          when "1000" =>
--            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
--              if ( Bus2IP_BE(byte_index) = '1' ) then
--                slv_reg0(byte_index*8+7 downto byte_index*8) <= Bus2IP_Data(byte_index*8+7 downto byte_index*8);
--              end if;
--            end loop;
--          when "0100" =>
--            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
--              if ( Bus2IP_BE(byte_index) = '1' ) then
--                slv_reg1(byte_index*8+7 downto byte_index*8) <= Bus2IP_Data(byte_index*8+7 downto byte_index*8);
--              end if;
--            end loop;
--          when "0010" =>
--            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
--              if ( Bus2IP_BE(byte_index) = '1' ) then
--                slv_reg2(byte_index*8+7 downto byte_index*8) <= Bus2IP_Data(byte_index*8+7 downto byte_index*8);
--              end if;
--            end loop;
--          when "0001" =>
--            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
--              if ( Bus2IP_BE(byte_index) = '1' ) then
--                slv_reg3(byte_index*8+7 downto byte_index*8) <= Bus2IP_Data(byte_index*8+7 downto byte_index*8);
--              end if;
--            end loop;
--          when others => null;
--        end case;
--      end if;
--    end if;
--
--  end process SLAVE_REG_WRITE_PROC;
--
  -- implement slave model software accessible register(s) read mux
  SLAVE_REG_READ_PROC : process( slv_reg_read_sel, slv_reg0, slv_reg1, slv_reg2, slv_reg3 ) is
  begin

    case slv_reg_read_sel is
      when "1000" => slv_ip2bus_data <= slv_reg0;
      when "0100" => slv_ip2bus_data <= slv_reg1;
      when "0010" => slv_ip2bus_data <= slv_reg2;
      when "0001" => slv_ip2bus_data <= slv_reg3;
      when others => slv_ip2bus_data <= (others => '0');
    end case;

  end process SLAVE_REG_READ_PROC;
--
--  ------------------------------------------
--  -- Example code to drive IP to Bus signals
--  ------------------------------------------
  IP2Bus_Data  <= slv_ip2bus_data when slv_read_ack = '1' else
                  (others => '0');

  IP2Bus_WrAck <= slv_write_ack;
  IP2Bus_RdAck <= slv_read_ack;
  IP2Bus_Error <= '0';

end IMP;
