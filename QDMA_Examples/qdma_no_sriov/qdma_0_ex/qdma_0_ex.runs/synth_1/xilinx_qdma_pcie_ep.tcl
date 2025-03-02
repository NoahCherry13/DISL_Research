# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
namespace eval ::optrace {
  variable script "/home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.runs/synth_1/xilinx_qdma_pcie_ep.tcl"
  variable category "vivado_synth"
}

# Try to connect to running dispatch if we haven't done so already.
# This code assumes that the Tcl interpreter is not using threads,
# since the ::dispatch::connected variable isn't mutex protected.
if {![info exists ::dispatch::connected]} {
  namespace eval ::dispatch {
    variable connected false
    if {[llength [array get env XILINX_CD_CONNECT_ID]] > 0} {
      set result "true"
      if {[catch {
        if {[lsearch -exact [package names] DispatchTcl] < 0} {
          set result [load librdi_cd_clienttcl[info sharedlibextension]] 
        }
        if {$result eq "false"} {
          puts "WARNING: Could not load dispatch client library"
        }
        set connect_id [ ::dispatch::init_client -mode EXISTING_SERVER ]
        if { $connect_id eq "" } {
          puts "WARNING: Could not initialize dispatch client"
        } else {
          puts "INFO: Dispatch client connection id - $connect_id"
          set connected true
        }
      } catch_res]} {
        puts "WARNING: failed to connect to dispatch server - $catch_res"
      }
    }
  }
}
if {$::dispatch::connected} {
  # Remove the dummy proc if it exists.
  if { [expr {[llength [info procs ::OPTRACE]] > 0}] } {
    rename ::OPTRACE ""
  }
  proc ::OPTRACE { task action {tags {} } } {
    ::vitis_log::op_trace "$task" $action -tags $tags -script $::optrace::script -category $::optrace::category
  }
  # dispatch is generic. We specifically want to attach logging.
  ::vitis_log::connect_client
} else {
  # Add dummy proc if it doesn't exist.
  if { [expr {[llength [info procs ::OPTRACE]] == 0}] } {
    proc ::OPTRACE {{arg1 \"\" } {arg2 \"\"} {arg3 \"\" } {arg4 \"\"} {arg5 \"\" } {arg6 \"\"}} {
        # Do nothing
    }
  }
}

proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
OPTRACE "synth_1" START { ROLLUP_AUTO }
OPTRACE "Creating in-memory project" START { }
create_project -in_memory -part xcvu13p-fhga2104-3-e

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.cache/wt [current_project]
set_property parent.project_path /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_output_repo /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
OPTRACE "Creating in-memory project" END { }
OPTRACE "Adding files" START { }
read_verilog -library xil_defaultlib -sv {
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/axi_st_module.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/dsc_byp_c2h.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/dsc_byp_h2c.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_stm_defines.svh
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_app.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_ecc_enc.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_fifo_lut.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_lpbk.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_qsts.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_stm_c2h_stub.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_stm_h2c_stub.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/qdma_stm_lpbk.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/st_c2h.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/st_h2c.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/user_control.sv
  /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/xilinx_qdma_pcie_ep.sv
}
read_ip -quiet /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.srcs/sources_1/ip/qdma_0/qdma_0.xci
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/synth/qdma_0_pcie4_ip_gt_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/ip_0/synth/qdma_0_pcie4_ip_gt.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/qdma_0_pcie4_ip_board.xdc]
set_property used_in_synthesis false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/ip_pcie4_uscale_plus_impl_x0y1.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/ip_pcie4_uscale_plus_impl_x0y1.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/synth/qdma_0_pcie4_ip_ooc.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/synth/qdma_0_pcie4_ip_late.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/ip_0/source/ip_pcie4_uscale_plus_x0y1.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/qdma_0_board.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/source/qdma_0_pcie4_uscaleplus_ip.xdc]
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/qdma_0/synth/qdma_0_ooc.xdc]

read_ip -quiet /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.srcs/sources_1/ip/axi_bram_ctrl_1/axi_bram_ctrl_1.xci
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/axi_bram_ctrl_1/axi_bram_ctrl_1_ooc.xdc]

read_ip -quiet /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.srcs/sources_1/ip/blk_mem_gen_0/blk_mem_gen_0.xci
set_property used_in_implementation false [get_files -all /home/ncherry/qdma_no_sriov/qdma_0_ex/qdma_0_ex.gen/sources_1/ip/blk_mem_gen_0/blk_mem_gen_0_ooc.xdc]

OPTRACE "Adding files" END { }
# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/xilinx_qdma_pcie_x0y1.xdc
set_property used_in_implementation false [get_files /home/ncherry/qdma_no_sriov/qdma_0_ex/imports/xilinx_qdma_pcie_x0y1.xdc]

set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

OPTRACE "synth_design" START { }
synth_design -top xilinx_qdma_pcie_ep -part xcvu13p-fhga2104-3-e
OPTRACE "synth_design" END { }
if { [get_msg_config -count -severity {CRITICAL WARNING}] > 0 } {
 send_msg_id runtcl-6 info "Synthesis results are not added to the cache due to CRITICAL_WARNING"
}


OPTRACE "write_checkpoint" START { CHECKPOINT }
# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef xilinx_qdma_pcie_ep.dcp
OPTRACE "write_checkpoint" END { }
OPTRACE "synth reports" START { REPORT }
create_report "synth_1_synth_report_utilization_0" "report_utilization -file xilinx_qdma_pcie_ep_utilization_synth.rpt -pb xilinx_qdma_pcie_ep_utilization_synth.pb"
OPTRACE "synth reports" END { }
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
OPTRACE "synth_1" END { }
