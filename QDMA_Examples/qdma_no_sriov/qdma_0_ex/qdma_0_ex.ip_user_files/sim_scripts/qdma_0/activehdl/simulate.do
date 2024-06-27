onbreak {quit -force}
onerror {quit -force}

asim +access +r +m+qdma_0 -L xilinx_vip -L xpm -L gtwizard_ultrascale_v1_7_12 -L xil_defaultlib -L qdma_v4_0_8 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.qdma_0 xil_defaultlib.glbl

set NumericStdNoWarnings 1
set StdArithNoWarnings 1

do {wave.do}

view wave
view structure

do {qdma_0.udo}

run -all

endsim

quit -force
