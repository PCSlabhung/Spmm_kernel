the pre_process folder contain C++ code for scheduling weight
the HLS_code folder is for C++ code which describe the hardware
HLS_code still has some flaw
the hardware itself can achieve II = 1 
It is done by declare another BRAM(named hand_partition_output) which is perfectly partition
However the cost is that the bottleneck is writing the BRAM (named hand_partition_output) back to output_matrix
the resolution might be array_reshape

version two 
add loop exit condition , fix data type to smaller bit number , still cannot find the fast way to load BRAM(hand_partition_output) to output_matrix
