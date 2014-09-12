
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 08/20/2014 at 23:40
// Component: WS2812driver
module WS2812driver (
	output  PulseOut,
    output  FIFO_FULL,
    output  FIFO_EMPTY,
	input   CLK
);

//`#start body` -- edit after this line, do not edit this line

localparam  PG_IDLE = 2'd0;
localparam  PG_LOAD = 2'd1;
localparam  PG_DEC_A = 2'd2;
localparam  PG_DEC_B = 2'd3;

reg [1:0] pg_state;
reg pg_out;
reg pg_data_req;
wire pg_det_eq;
wire pg_det_zero;

localparam SHIFTER_IDLE = 2'd0;
localparam SHIFTER_LOAD = 2'd1;
localparam SHIFTER_WAIT = 2'd2;
localparam SHIFTER_SHIFT = 2'd3;
reg [1:0] shifter_state;
reg [2:0] shift_counter;
wire[7:0] comp_val;
wire shift_out;
wire shifter_f0_notempty;
wire shifter_f0_full;
wire shifter_f1_empty;
wire shifter_f1_notfull;

localparam FIFO_IDLE = 2'd0;
localparam FIFO_FEED = 2'd1;
localparam FIFO_WAIT = 2'd2;
localparam FIFO_LOAD = 2'd3;
reg[1:0] fifo_state;
wire f1_feed = (fifo_state==FIFO_FEED)?1'b1:1'b0;
wire f0_load = (fifo_state==FIFO_LOAD)?1'b1:1'b0;
wire d0_load;

//        Your code goes here
assign PulseOut = pg_out;
assign FIFO_EMPTY = f0_load;
assign d0_load = !f0_load;
assign FIFO_FULL = f1_feed;
assign comp_val = shift_out?8'd5:8'd17;

// pulseGen state machine
always @ (posedge CLK) begin
    case(pg_state) 
        PG_IDLE:begin
            pg_out <= 1'b0;
            pg_data_req <= 1'b0;
            if(!shifter_state[0])
                begin
                pg_state <= PG_IDLE;
                end
            else
                begin
                pg_state <= PG_LOAD;
                end
        end
        PG_LOAD:begin
            pg_out <= 1'b1;
            pg_data_req <= 1'b0;
            pg_state <= PG_DEC_A;
        end
        PG_DEC_A:begin
            pg_data_req <= 1'b0;
            if(pg_det_eq)
                begin
                pg_out <= 1'b0;
                pg_state <= PG_DEC_B;
                end
            else
                begin
                pg_out <= 1'b1;
                pg_state <= PG_DEC_A;
                end
        end
        PG_DEC_B:begin
            pg_out <= 1'b0;
            if(pg_det_zero)
                begin
                if(!shifter_state[0])
                    begin
                    pg_state <= PG_IDLE;
                    end
                else
                    begin
                    pg_state <= PG_LOAD;
                    end
                end
            else
                begin
                pg_state <= PG_DEC_B;
                end
            if(pg_det_eq)
                begin
                pg_data_req <= 1'b1;
                end
            else
                begin
                pg_data_req <= 1'b0;
                end
        end
        default:begin
            pg_state <= PG_IDLE;
        end
    endcase
end

// shifter state machine
always @ (posedge CLK) begin
    case(shifter_state) 
        SHIFTER_IDLE:begin
            shift_counter <= shift_counter;
            if(!shifter_f0_notempty)
                begin
                shifter_state <= SHIFTER_IDLE;
                end
            else
                begin
                shifter_state <= SHIFTER_LOAD;
                end
        end
        SHIFTER_LOAD:begin
            shifter_state <= SHIFTER_WAIT;
            shift_counter <= 3'd6;
        end
        SHIFTER_WAIT:begin
            shift_counter <= shift_counter;
            if(pg_data_req)
                begin
                shifter_state <= SHIFTER_SHIFT;
                end
            else
                begin
                shifter_state <= SHIFTER_WAIT;
                end
        end
        SHIFTER_SHIFT:begin
            shift_counter <= shift_counter - 1;
            if(shift_counter==3'd0)
                begin
                if(!shifter_f0_notempty)
                    begin
                    shifter_state <= SHIFTER_IDLE;
                    end
                else
                    begin
                    shifter_state <= SHIFTER_LOAD;
                    end
                end
            else
                begin
                shifter_state <= SHIFTER_WAIT;
                end
        end
        default:begin
            shifter_state <= SHIFTER_IDLE;
        end
    endcase
end

// fifo state machine
always @ (posedge CLK) begin
    case(fifo_state) 
        FIFO_IDLE:begin
            if(!shifter_f1_empty)
                begin
                fifo_state <= FIFO_FEED;
                end
        end
        FIFO_FEED:begin
/*            if(shifter_f0_full)
                begin*/
                fifo_state <= FIFO_WAIT;
/*                end
            else
                begin
                fifo_state <= FIFO_LOAD;
                end*/
        end
        FIFO_WAIT:begin
            if(shifter_f0_full)
                begin
                fifo_state <= FIFO_WAIT;
                end
            else
                begin
                fifo_state <= FIFO_LOAD;
                end
        end
        FIFO_LOAD:begin
            fifo_state <= FIFO_IDLE;
            end
        default:
            begin
            fifo_state <= FIFO_IDLE;
        end
    endcase
end

cy_psoc3_dp8 #(.cy_dpconfig_a(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:   Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC___F0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:   Load*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:   Wait*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:   Shift*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:   IdleWithFeed*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC___F0, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:   LoadWithFeed*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC_NONE, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:   WaitWithFeed*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP___SL, `CS_A0_SRC__ALU, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:   ShiftWithFeed*/
    8'hFF, 8'h00,  /*CFG9:       */
    8'hFF, 8'hFF,  /*CFG11-10:       */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:       */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0__A1,
    `SC_MSB_DSBL, `SC_MSB_BIT7, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:       */
    7'h00, `SC_FIFO0_DYN_ON,2'h00,
    `SC_FIFO_CLK__DP,`SC_FIFO_CAP_FX,`SC_FIFO_LEVEL,
    `SC_FIFO_ASYNC /*CFG17-16:       */
,`SC_EXTCRC_DSBL,`SC_WRK16CAT_DSBL}
)) shifter(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(CLK),
        /*  input   [02:00]         */  .cs_addr({f1_feed, shifter_state}),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(f0_load),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(d0_load),
        /*  input                   */  .d1_load(1'b0),
        /*  output                  */  .ce0(),
        /*  output                  */  .cl0(),
        /*  output                  */  .z0(),
        /*  output                  */  .ff0(),
        /*  output                  */  .ce1(),
        /*  output                  */  .cl1(),
        /*  output                  */  .z1(),
        /*  output                  */  .ff1(),
        /*  output                  */  .ov_msb(),
        /*  output                  */  .co_msb(),
        /*  output                  */  .cmsb(),
        /*  output                  */  .so(shift_out),
        /*  output                  */  .f0_bus_stat(shifter_f0_notempty),
        /*  output                  */  .f0_blk_stat(shifter_f0_full),
        /*  output                  */  .f1_bus_stat(shifter_f1_notfull),
        /*  output                  */  .f1_blk_stat(shifter_f1_empty)
        /*  output                  */  //.f0_bus_stat(shifter_f0_empty),
        /*  output                  */  //.f0_blk_stat(shifter_f0_full),
        /*  output                  */  //.f1_bus_stat(shifter_f1_full),
        /*  output                  */  //.f1_blk_stat(shifter_f1_empty)
);
cy_psoc3_dp #(.a0_init(23), .a1_init(5), .d0_init(23), 
.d1_init(1), 
.cy_dpconfig(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:      Idle*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_ENBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:      Load*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:      DecA*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGB, /*CFGRAM3:      DecB*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:      */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:      */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:      */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:      */
    8'hFF, 8'h00,  /*CFG9:      */
    8'hFF, 8'hFF,  /*CFG11-10:      */
    `SC_CMPB_A0_D1, `SC_CMPA_A1_A0, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:      */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, `SC_PI_DYN_EN,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:      */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO_ASYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:      */
}
)) pulseGen(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(CLK),
        /*  input   [02:00]         */  .cs_addr({1'b0, pg_state}),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output                  */  .ce0(),
        /*  output                  */  .cl0(),
        /*  output                  */  .z0(pg_det_zero),
        /*  output                  */  .ff0(),
        /*  output                  */  .ce1(pg_det_eq),
        /*  output                  */  .cl1(),
        /*  output                  */  .z1(),
        /*  output                  */  .ff1(),
        /*  output                  */  .ov_msb(),
        /*  output                  */  .co_msb(),
        /*  output                  */  .cmsb(),
        /*  output                  */  .so(),
        /*  output                  */  .f0_bus_stat(),
        /*  output                  */  .f0_blk_stat(),
        /*  output                  */  .f1_bus_stat(),
        /*  output                  */  .f1_blk_stat(),
        
        /* input                    */  .ci(1'b0),     // Carry in from previous stage
        /* output                   */  .co(),         // Carry out to next stage
        /* input                    */  .sir(1'b0),    // Shift in from right side
        /* output                   */  .sor(),        // Shift out to right side
        /* input                    */  .sil(1'b0),    // Shift in from left side
        /* output                   */  .sol(),        // Shift out to left side
        /* input                    */  .msbi(1'b0),   // MSB chain in
        /* output                   */  .msbo(),       // MSB chain out
        /* input [01:00]            */  .cei(2'b0),    // Compare equal in from prev stage
        /* output [01:00]           */  .ceo(),        // Compare equal out to next stage
        /* input [01:00]            */  .cli(2'b0),    // Compare less than in from prv stage
        /* output [01:00]           */  .clo(),        // Compare less than out to next stage
        /* input [01:00]            */  .zi(2'b0),     // Zero detect in from previous stage
        /* output [01:00]           */  .zo(),         // Zero detect out to next stage
        /* input [01:00]            */  .fi(2'b0),     // 0xFF detect in from previous stage
        /* output [01:00]           */  .fo(),         // 0xFF detect out to next stage
        /* input [01:00]            */  .capi(2'b0),   // Software capture from previous stage
        /* output [01:00]           */  .capo(),       // Software capture to next stage
        /* input                    */  .cfbi(1'b0),   // CRC Feedback in from previous stage
        /* output                   */  .cfbo(),       // CRC Feedback out to next stage
        /* input [07:00]            */  .pi(comp_val),     // Parallel data port
        /* output [07:00]           */  .po()          // Parallel data port
);
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
















