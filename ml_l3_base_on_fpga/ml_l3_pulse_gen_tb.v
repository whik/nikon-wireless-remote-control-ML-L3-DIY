/*
- Github: https://github.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Gitee : https://gitee.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Blog  : www.wangchaochao.top
*/
`timescale 1ns/100ps

module ml_l3_pulse_gen_tb;

parameter SYSCLK_PERIOD = 20;// 50MHZ

reg SYSCLK;
reg NSYSRESET;
reg trig;

wire pulse;

initial
begin
    SYSCLK = 1'b0;
    NSYSRESET = 1'b0;
    trig = 0;
end

initial
begin
    #(SYSCLK_PERIOD * 10 )
        NSYSRESET = 1'b0;
        trig = 0;
    #(SYSCLK_PERIOD * 1000 )
        NSYSRESET = 1'b1;
    #(SYSCLK_PERIOD * 10 )
        trig = 1;
    #SYSCLK_PERIOD
        trig = 0;
end

always @(SYSCLK)
    #(SYSCLK_PERIOD / 2.0) SYSCLK <= !SYSCLK;

ml_l3_pulse_gen ml_l3_pulse_gen_0 (
    // Inputs
    .clk_50M(SYSCLK),
    .rst_n(NSYSRESET),
    .trig(trig),

    // Outputs
    .pulse(pulse)
);

endmodule

