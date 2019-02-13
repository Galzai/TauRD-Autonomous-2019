################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SimulatorClient/tcp_client.cpp 

OBJS += \
./SimulatorClient/tcp_client.o 

CPP_DEPS += \
./SimulatorClient/tcp_client.d 


# Each subdirectory must supply rules for building sources it contributes
SimulatorClient/%.o: ../SimulatorClient/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 -ccbin aarch64-linux-gnu-g++ -gencode arch=compute_52,code=sm_52 -m64 -odir "SimulatorClient" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 --compile -m64 -ccbin aarch64-linux-gnu-g++  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


