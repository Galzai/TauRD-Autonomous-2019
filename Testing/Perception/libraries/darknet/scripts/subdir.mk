################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Perception/libraries/darknet/scripts/kmeansiou.c 

OBJS += \
./Perception/libraries/darknet/scripts/kmeansiou.o 

C_DEPS += \
./Perception/libraries/darknet/scripts/kmeansiou.d 


# Each subdirectory must supply rules for building sources it contributes
Perception/libraries/darknet/scripts/%.o: ../Perception/libraries/darknet/scripts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 -gencode arch=compute_52,code=sm_52  -odir "Perception/libraries/darknet/scripts" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 --compile  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


