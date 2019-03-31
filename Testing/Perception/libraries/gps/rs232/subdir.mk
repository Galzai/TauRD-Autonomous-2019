################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Perception/libraries/gps/rs232/rs232.c 

OBJS += \
./Perception/libraries/gps/rs232/rs232.o 

C_DEPS += \
./Perception/libraries/gps/rs232/rs232.d 


# Each subdirectory must supply rules for building sources it contributes
Perception/libraries/gps/rs232/%.o: ../Perception/libraries/gps/rs232/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-10.0/bin/nvcc -I/usr/local/zed/include/ -I/usr/include/ -G -g -O0 -gencode arch=compute_52,code=sm_52  -odir "Perception/libraries/gps/rs232" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-10.0/bin/nvcc -I/usr/local/zed/include/ -I/usr/include/ -G -g -O0 --compile  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


