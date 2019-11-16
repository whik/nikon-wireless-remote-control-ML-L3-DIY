/*
- Github: https://github.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Gitee : https://gitee.com/whik/nikon-wireless-remote-control-ML-L3-DIY.git
- Blog  : www.wangchaochao.top
*/
module ml_l3_pulse_gen( 

input clk_50M,  //20ns
input rst_n,
input trig,     //negedge trig

output pulse
);

parameter T1_2000US  = 100000;
parameter T2_28000US = 1400000;
parameter T3_400US   = 20000;
parameter T4_1580US  = 79000;
parameter T5_400US   = T3_400US;
parameter T6_3580US  = 179000;
parameter T7_400US   = T3_400US;

parameter T1_STS = 1;
parameter T2_STS = 2;
parameter T3_STS = 3;
parameter T4_STS = 4;
parameter T5_STS = 5;
parameter T6_STS = 6;
parameter T7_STS = 7;
parameter T8_STS = 8;
parameter T0_STS = 0;
parameter TIME_38KHZ = 658;

reg [7:0] cur_sts;
reg [31:0] cnt_38khz;
reg [31:0] cnt;
reg [31:0] cnt_max;

reg en;
reg pwm_38k;
reg trig_reg;

assign pulse = (en) ? pwm_38k : 0;

always @ (posedge clk_50M)
begin
    trig_reg <= trig;
end

always @ (posedge clk_50M)
begin
    if(!rst_n)
        cnt_max <= 0;
    else 
    begin
        case (cur_sts)
            T0_STS : cnt_max <= 0;
            T1_STS : cnt_max <= T1_2000US;
            T2_STS : cnt_max <= T2_28000US;
            T3_STS : cnt_max <= T3_400US;
            T4_STS : cnt_max <= T4_1580US;
            T5_STS : cnt_max <= T5_400US;
            T6_STS : cnt_max <= T6_3580US;
            T7_STS : cnt_max <= T7_400US;
            default : cnt_max <= 0;        
        endcase
    end
end

always @ (posedge clk_50M)
begin
    if(!rst_n)
        en <= 0;
    else
    begin
        case (cur_sts)
            1,3,5,7 : en <= 1;
            2,4,6,0 : en <= 0;
            default : en <= 0;
        endcase
    end
end

always @ (posedge clk_50M)
begin
    if(!rst_n)
        cnt <= 0;
    else
    begin
        if(cur_sts != T0_STS && cnt < cnt_max)
            cnt <= cnt + 1;
        else 
            cnt <= 0;
    end
end

always @ (posedge clk_50M)
begin
    if(!rst_n)
        cur_sts <= T0_STS;
    else 
    begin
        case (cur_sts)
            T0_STS:
                if(trig_reg & !trig)
                    cur_sts <= T1_STS;
            T1_STS:
                if(cnt == T1_2000US)
                    cur_sts <= T2_STS;
            T2_STS:
                if(cnt == T2_28000US)
                    cur_sts <= T3_STS;        
            T3_STS:
                if(cnt == T3_400US)
                    cur_sts <= T4_STS;        
            T4_STS:
                if(cnt == T4_1580US)
                    cur_sts <= T5_STS;        
            T5_STS:
                if(cnt == T5_400US)
                    cur_sts <= T6_STS;        
            T6_STS:
                if(cnt == T6_3580US)
                    cur_sts <= T7_STS;        
            T7_STS:
                if(cnt == T7_400US)
                    cur_sts <= T0_STS;        
            default : 
                cur_sts <= T0_STS;
        endcase 
    end
end

/* 38KHz counter */
always @ (posedge clk_50M)
begin
    if(!rst_n)
        cnt_38khz <= 0;
    else 
    begin
        if(en && cnt_38khz < TIME_38KHZ)
            cnt_38khz <= cnt_38khz + 1;
        else 
            cnt_38khz <= 0;
    end
end

/* generate 38KHz pwm */
always @ (posedge clk_50M)
begin
    if(!rst_n)
        pwm_38k <= 0;
    else if(cnt_38khz == TIME_38KHZ)
        pwm_38k <= ~pwm_38k;
end

endmodule

