#! /bin/sh
echo "Enter Num VFs: "
read num_vf
echo "Enter Dev Num: "
read dev_num
echo $num_vf > /sys/bus/pci/devices/0000:65:00.$dev_num/sriov_numvfs
