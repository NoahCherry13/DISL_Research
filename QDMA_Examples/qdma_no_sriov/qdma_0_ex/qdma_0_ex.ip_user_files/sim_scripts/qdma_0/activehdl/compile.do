vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xpm
vlib activehdl/gtwizard_ultrascale_v1_7_12
vlib activehdl/xil_defaultlib
vlib activehdl/qdma_v4_0_8

vmap xilinx_vip activehdl/xilinx_vip
vmap xpm activehdl/xpm
vmap gtwizard_ultrascale_v1_7_12 activehdl/gtwizard_ultrascale_v1_7_12
vmap xil_defaultlib activehdl/xil_defaultlib
vmap qdma_v4_0_8 activehdl/qdma_v4_0_8

vlog -work xilinx_vip  -sv2k12 "+incdir+/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source" "+incdir+../../../ipstatic/hdl/verilog" "+incdir+/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"/opt/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"/opt/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"/opt/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"/opt/Xilinx/Vivado/2021.2/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work gtwizard_ultrascale_v1_7_12  -v2k5 "+incdir+../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source" "+incdir+../../../ipstatic/hdl/verilog" "+incdir+/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_bit_sync.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gte4_drp_arb.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gthe4_delay_powergood.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtye4_delay_powergood.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gthe3_cpll_cal.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gthe3_cal_freqcnt.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gthe4_cpll_cal.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gthe4_cpll_cal_rx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gthe4_cpll_cal_tx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gthe4_cal_freqcnt.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtye4_cpll_cal.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtye4_cpll_cal_rx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtye4_cpll_cal_tx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtye4_cal_freqcnt.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtwiz_buffbypass_rx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtwiz_buffbypass_tx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtwiz_reset.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtwiz_userclk_rx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtwiz_userclk_tx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtwiz_userdata_rx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_gtwiz_userdata_tx.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_reset_sync.v" \
"../../../ipstatic/hdl/gtwizard_ultrascale_v1_7_reset_inv_sync.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source" "+incdir+../../../ipstatic/hdl/verilog" "+incdir+/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/sim/gtwizard_ultrascale_v1_7_gtye4_channel.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/sim/qdma_0_pcie4_ip_gt_gtye4_channel_wrapper.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/sim/gtwizard_ultrascale_v1_7_gtye4_common.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/sim/qdma_0_pcie4_ip_gt_gtye4_common_wrapper.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/sim/qdma_0_pcie4_ip_gt_gtwizard_gtye4.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/sim/qdma_0_pcie4_ip_gt_gtwizard_top.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/sim/qdma_0_pcie4_ip_gt.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gtwizard_top.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_phy_ff_chain.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_phy_pipeline.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_async_fifo.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_cc_intfc.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_cc_output_mux.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_cq_intfc.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_cq_output_mux.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_intfc_int.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_intfc.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_rc_intfc.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_rc_output_mux.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_rq_intfc.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_rq_output_mux.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_512b_sync_fifo.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram_16k_int.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram_16k.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram_32k.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram_4k_int.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram_msix.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram_rep_int.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram_rep.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram_tph.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_bram.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_gt_channel.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_gt_common.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_phy_clk.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_phy_rst.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_phy_rxeq.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_phy_txeq.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_sync_cell.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_sync.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_cdr_ctrl_on_eidle.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_receiver_detect_rxterm.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_gt_phy_wrapper.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_init_ctrl.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_pl_eq.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_vf_decode.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_pipe.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_phy_top.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_seqnum_fifo.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_sys_clk_gen_ps.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/qdma_0_pcie4_ip_pcie4_uscale_core_top.v" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/sim/qdma_0_pcie4_ip.v" \

vlog -work qdma_v4_0_8  -sv2k12 "+incdir+../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source" "+incdir+../../../ipstatic/hdl/verilog" "+incdir+/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../ipstatic/hdl/qdma_v4_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source" "+incdir+../../../ipstatic/hdl/verilog" "+incdir+/opt/Xilinx/Vivado/2021.2/data/xilinx_vip/include" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/qdma_0hdl/verilog/qdma_0_core_top.sv" \
"../../../../qdma_0_ex.gen/sources_1/ip/qdma_0/sim/qdma_0.sv" \

vlog -work xil_defaultlib \
"glbl.v"

