################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CU_SRCS += \
../Perception/libraries/darknet/src/activation_kernels.cu \
../Perception/libraries/darknet/src/avgpool_layer_kernels.cu \
../Perception/libraries/darknet/src/blas_kernels.cu \
../Perception/libraries/darknet/src/col2im_kernels.cu \
../Perception/libraries/darknet/src/convolutional_kernels.cu \
../Perception/libraries/darknet/src/crop_layer_kernels.cu \
../Perception/libraries/darknet/src/deconvolutional_kernels.cu \
../Perception/libraries/darknet/src/dropout_layer_kernels.cu \
../Perception/libraries/darknet/src/im2col_kernels.cu \
../Perception/libraries/darknet/src/maxpool_layer_kernels.cu \
../Perception/libraries/darknet/src/network_kernels.cu 

CPP_SRCS += \
../Perception/libraries/darknet/src/http_stream.cpp \
../Perception/libraries/darknet/src/yolo_console_dll.cpp \
../Perception/libraries/darknet/src/yolo_v2_class.cpp 

C_SRCS += \
../Perception/libraries/darknet/src/activation_layer.c \
../Perception/libraries/darknet/src/activations.c \
../Perception/libraries/darknet/src/art.c \
../Perception/libraries/darknet/src/avgpool_layer.c \
../Perception/libraries/darknet/src/batchnorm_layer.c \
../Perception/libraries/darknet/src/blas.c \
../Perception/libraries/darknet/src/box.c \
../Perception/libraries/darknet/src/captcha.c \
../Perception/libraries/darknet/src/cifar.c \
../Perception/libraries/darknet/src/classifier.c \
../Perception/libraries/darknet/src/coco.c \
../Perception/libraries/darknet/src/col2im.c \
../Perception/libraries/darknet/src/compare.c \
../Perception/libraries/darknet/src/connected_layer.c \
../Perception/libraries/darknet/src/convolutional_layer.c \
../Perception/libraries/darknet/src/cost_layer.c \
../Perception/libraries/darknet/src/cpu_gemm.c \
../Perception/libraries/darknet/src/crnn_layer.c \
../Perception/libraries/darknet/src/crop_layer.c \
../Perception/libraries/darknet/src/cuda.c \
../Perception/libraries/darknet/src/darknet.c \
../Perception/libraries/darknet/src/data.c \
../Perception/libraries/darknet/src/deconvolutional_layer.c \
../Perception/libraries/darknet/src/demo.c \
../Perception/libraries/darknet/src/detection_layer.c \
../Perception/libraries/darknet/src/detector.c \
../Perception/libraries/darknet/src/dice.c \
../Perception/libraries/darknet/src/dropout_layer.c \
../Perception/libraries/darknet/src/gemm.c \
../Perception/libraries/darknet/src/getopt.c \
../Perception/libraries/darknet/src/gettimeofday.c \
../Perception/libraries/darknet/src/go.c \
../Perception/libraries/darknet/src/gru_layer.c \
../Perception/libraries/darknet/src/im2col.c \
../Perception/libraries/darknet/src/image.c \
../Perception/libraries/darknet/src/layer.c \
../Perception/libraries/darknet/src/list.c \
../Perception/libraries/darknet/src/local_layer.c \
../Perception/libraries/darknet/src/matrix.c \
../Perception/libraries/darknet/src/maxpool_layer.c \
../Perception/libraries/darknet/src/network.c \
../Perception/libraries/darknet/src/nightmare.c \
../Perception/libraries/darknet/src/normalization_layer.c \
../Perception/libraries/darknet/src/option_list.c \
../Perception/libraries/darknet/src/parser.c \
../Perception/libraries/darknet/src/region_layer.c \
../Perception/libraries/darknet/src/reorg_layer.c \
../Perception/libraries/darknet/src/reorg_old_layer.c \
../Perception/libraries/darknet/src/rnn.c \
../Perception/libraries/darknet/src/rnn_layer.c \
../Perception/libraries/darknet/src/rnn_vid.c \
../Perception/libraries/darknet/src/route_layer.c \
../Perception/libraries/darknet/src/shortcut_layer.c \
../Perception/libraries/darknet/src/softmax_layer.c \
../Perception/libraries/darknet/src/super.c \
../Perception/libraries/darknet/src/swag.c \
../Perception/libraries/darknet/src/tag.c \
../Perception/libraries/darknet/src/tree.c \
../Perception/libraries/darknet/src/upsample_layer.c \
../Perception/libraries/darknet/src/utils.c \
../Perception/libraries/darknet/src/voxel.c \
../Perception/libraries/darknet/src/writing.c \
../Perception/libraries/darknet/src/yolo.c \
../Perception/libraries/darknet/src/yolo_layer.c 

OBJS += \
./Perception/libraries/darknet/src/activation_kernels.o \
./Perception/libraries/darknet/src/activation_layer.o \
./Perception/libraries/darknet/src/activations.o \
./Perception/libraries/darknet/src/art.o \
./Perception/libraries/darknet/src/avgpool_layer.o \
./Perception/libraries/darknet/src/avgpool_layer_kernels.o \
./Perception/libraries/darknet/src/batchnorm_layer.o \
./Perception/libraries/darknet/src/blas.o \
./Perception/libraries/darknet/src/blas_kernels.o \
./Perception/libraries/darknet/src/box.o \
./Perception/libraries/darknet/src/captcha.o \
./Perception/libraries/darknet/src/cifar.o \
./Perception/libraries/darknet/src/classifier.o \
./Perception/libraries/darknet/src/coco.o \
./Perception/libraries/darknet/src/col2im.o \
./Perception/libraries/darknet/src/col2im_kernels.o \
./Perception/libraries/darknet/src/compare.o \
./Perception/libraries/darknet/src/connected_layer.o \
./Perception/libraries/darknet/src/convolutional_kernels.o \
./Perception/libraries/darknet/src/convolutional_layer.o \
./Perception/libraries/darknet/src/cost_layer.o \
./Perception/libraries/darknet/src/cpu_gemm.o \
./Perception/libraries/darknet/src/crnn_layer.o \
./Perception/libraries/darknet/src/crop_layer.o \
./Perception/libraries/darknet/src/crop_layer_kernels.o \
./Perception/libraries/darknet/src/cuda.o \
./Perception/libraries/darknet/src/darknet.o \
./Perception/libraries/darknet/src/data.o \
./Perception/libraries/darknet/src/deconvolutional_kernels.o \
./Perception/libraries/darknet/src/deconvolutional_layer.o \
./Perception/libraries/darknet/src/demo.o \
./Perception/libraries/darknet/src/detection_layer.o \
./Perception/libraries/darknet/src/detector.o \
./Perception/libraries/darknet/src/dice.o \
./Perception/libraries/darknet/src/dropout_layer.o \
./Perception/libraries/darknet/src/dropout_layer_kernels.o \
./Perception/libraries/darknet/src/gemm.o \
./Perception/libraries/darknet/src/getopt.o \
./Perception/libraries/darknet/src/gettimeofday.o \
./Perception/libraries/darknet/src/go.o \
./Perception/libraries/darknet/src/gru_layer.o \
./Perception/libraries/darknet/src/http_stream.o \
./Perception/libraries/darknet/src/im2col.o \
./Perception/libraries/darknet/src/im2col_kernels.o \
./Perception/libraries/darknet/src/image.o \
./Perception/libraries/darknet/src/layer.o \
./Perception/libraries/darknet/src/list.o \
./Perception/libraries/darknet/src/local_layer.o \
./Perception/libraries/darknet/src/matrix.o \
./Perception/libraries/darknet/src/maxpool_layer.o \
./Perception/libraries/darknet/src/maxpool_layer_kernels.o \
./Perception/libraries/darknet/src/network.o \
./Perception/libraries/darknet/src/network_kernels.o \
./Perception/libraries/darknet/src/nightmare.o \
./Perception/libraries/darknet/src/normalization_layer.o \
./Perception/libraries/darknet/src/option_list.o \
./Perception/libraries/darknet/src/parser.o \
./Perception/libraries/darknet/src/region_layer.o \
./Perception/libraries/darknet/src/reorg_layer.o \
./Perception/libraries/darknet/src/reorg_old_layer.o \
./Perception/libraries/darknet/src/rnn.o \
./Perception/libraries/darknet/src/rnn_layer.o \
./Perception/libraries/darknet/src/rnn_vid.o \
./Perception/libraries/darknet/src/route_layer.o \
./Perception/libraries/darknet/src/shortcut_layer.o \
./Perception/libraries/darknet/src/softmax_layer.o \
./Perception/libraries/darknet/src/super.o \
./Perception/libraries/darknet/src/swag.o \
./Perception/libraries/darknet/src/tag.o \
./Perception/libraries/darknet/src/tree.o \
./Perception/libraries/darknet/src/upsample_layer.o \
./Perception/libraries/darknet/src/utils.o \
./Perception/libraries/darknet/src/voxel.o \
./Perception/libraries/darknet/src/writing.o \
./Perception/libraries/darknet/src/yolo.o \
./Perception/libraries/darknet/src/yolo_console_dll.o \
./Perception/libraries/darknet/src/yolo_layer.o \
./Perception/libraries/darknet/src/yolo_v2_class.o 

CU_DEPS += \
./Perception/libraries/darknet/src/activation_kernels.d \
./Perception/libraries/darknet/src/avgpool_layer_kernels.d \
./Perception/libraries/darknet/src/blas_kernels.d \
./Perception/libraries/darknet/src/col2im_kernels.d \
./Perception/libraries/darknet/src/convolutional_kernels.d \
./Perception/libraries/darknet/src/crop_layer_kernels.d \
./Perception/libraries/darknet/src/deconvolutional_kernels.d \
./Perception/libraries/darknet/src/dropout_layer_kernels.d \
./Perception/libraries/darknet/src/im2col_kernels.d \
./Perception/libraries/darknet/src/maxpool_layer_kernels.d \
./Perception/libraries/darknet/src/network_kernels.d 

CPP_DEPS += \
./Perception/libraries/darknet/src/http_stream.d \
./Perception/libraries/darknet/src/yolo_console_dll.d \
./Perception/libraries/darknet/src/yolo_v2_class.d 

C_DEPS += \
./Perception/libraries/darknet/src/activation_layer.d \
./Perception/libraries/darknet/src/activations.d \
./Perception/libraries/darknet/src/art.d \
./Perception/libraries/darknet/src/avgpool_layer.d \
./Perception/libraries/darknet/src/batchnorm_layer.d \
./Perception/libraries/darknet/src/blas.d \
./Perception/libraries/darknet/src/box.d \
./Perception/libraries/darknet/src/captcha.d \
./Perception/libraries/darknet/src/cifar.d \
./Perception/libraries/darknet/src/classifier.d \
./Perception/libraries/darknet/src/coco.d \
./Perception/libraries/darknet/src/col2im.d \
./Perception/libraries/darknet/src/compare.d \
./Perception/libraries/darknet/src/connected_layer.d \
./Perception/libraries/darknet/src/convolutional_layer.d \
./Perception/libraries/darknet/src/cost_layer.d \
./Perception/libraries/darknet/src/cpu_gemm.d \
./Perception/libraries/darknet/src/crnn_layer.d \
./Perception/libraries/darknet/src/crop_layer.d \
./Perception/libraries/darknet/src/cuda.d \
./Perception/libraries/darknet/src/darknet.d \
./Perception/libraries/darknet/src/data.d \
./Perception/libraries/darknet/src/deconvolutional_layer.d \
./Perception/libraries/darknet/src/demo.d \
./Perception/libraries/darknet/src/detection_layer.d \
./Perception/libraries/darknet/src/detector.d \
./Perception/libraries/darknet/src/dice.d \
./Perception/libraries/darknet/src/dropout_layer.d \
./Perception/libraries/darknet/src/gemm.d \
./Perception/libraries/darknet/src/getopt.d \
./Perception/libraries/darknet/src/gettimeofday.d \
./Perception/libraries/darknet/src/go.d \
./Perception/libraries/darknet/src/gru_layer.d \
./Perception/libraries/darknet/src/im2col.d \
./Perception/libraries/darknet/src/image.d \
./Perception/libraries/darknet/src/layer.d \
./Perception/libraries/darknet/src/list.d \
./Perception/libraries/darknet/src/local_layer.d \
./Perception/libraries/darknet/src/matrix.d \
./Perception/libraries/darknet/src/maxpool_layer.d \
./Perception/libraries/darknet/src/network.d \
./Perception/libraries/darknet/src/nightmare.d \
./Perception/libraries/darknet/src/normalization_layer.d \
./Perception/libraries/darknet/src/option_list.d \
./Perception/libraries/darknet/src/parser.d \
./Perception/libraries/darknet/src/region_layer.d \
./Perception/libraries/darknet/src/reorg_layer.d \
./Perception/libraries/darknet/src/reorg_old_layer.d \
./Perception/libraries/darknet/src/rnn.d \
./Perception/libraries/darknet/src/rnn_layer.d \
./Perception/libraries/darknet/src/rnn_vid.d \
./Perception/libraries/darknet/src/route_layer.d \
./Perception/libraries/darknet/src/shortcut_layer.d \
./Perception/libraries/darknet/src/softmax_layer.d \
./Perception/libraries/darknet/src/super.d \
./Perception/libraries/darknet/src/swag.d \
./Perception/libraries/darknet/src/tag.d \
./Perception/libraries/darknet/src/tree.d \
./Perception/libraries/darknet/src/upsample_layer.d \
./Perception/libraries/darknet/src/utils.d \
./Perception/libraries/darknet/src/voxel.d \
./Perception/libraries/darknet/src/writing.d \
./Perception/libraries/darknet/src/yolo.d \
./Perception/libraries/darknet/src/yolo_layer.d 


# Each subdirectory must supply rules for building sources it contributes
Perception/libraries/darknet/src/%.o: ../Perception/libraries/darknet/src/%.cu
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 -gencode arch=compute_52,code=sm_52  -odir "Perception/libraries/darknet/src" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 --compile --relocatable-device-code=false -gencode arch=compute_52,code=compute_52 -gencode arch=compute_52,code=sm_52  -x cu -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Perception/libraries/darknet/src/%.o: ../Perception/libraries/darknet/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 -gencode arch=compute_52,code=sm_52  -odir "Perception/libraries/darknet/src" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 --compile  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Perception/libraries/darknet/src/%.o: ../Perception/libraries/darknet/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 -gencode arch=compute_52,code=sm_52  -odir "Perception/libraries/darknet/src" -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-10.0/bin/nvcc -I/usr/include/ -G -g -O0 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


