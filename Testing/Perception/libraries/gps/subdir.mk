################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Perception/libraries/gps/an_packet_protocol.c \
../Perception/libraries/gps/packet_example.c \
../Perception/libraries/gps/spatial_packets.c 

OBJS += \
./Perception/libraries/gps/an_packet_protocol.o \
./Perception/libraries/gps/packet_example.o \
./Perception/libraries/gps/spatial_packets.o 

C_DEPS += \
./Perception/libraries/gps/an_packet_protocol.d \
./Perception/libraries/gps/packet_example.d \
./Perception/libraries/gps/spatial_packets.d 


# Each subdirectory must supply rules for building sources it contributes
Perception/libraries/gps/%.o: ../Perception/libraries/gps/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-10.0/bin/nvcc -I/usr/local/zed/include/ -I/usr/include/ -G -g -O0 -gencode arch=compute_52,code=sm_52  -odir "Perception/libraries/gps" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-10.0/bin/nvcc -I/usr/local/zed/include/ -I/usr/include/ -G -g -O0 --compile  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


