onbreak {quit -force}
onerror {quit -force}

asim +access +r +m+axi_bram_ctrl_1 -L xilinx_vip -L xpm -L axi_bram_ctrl_v4_1_6 -L xil_defaultlib -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.axi_bram_ctrl_1 xil_defaultlib.glbl

set NumericStdNoWarnings 1
set StdArithNoWarnings 1

do {wave.do}

view wave
view structure

do {axi_bram_ctrl_1.udo}

run -all

endsim

quit -force
