################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/IPS.c \
../code/Inductor.c \
../code/PID.c \
../code/TFT.c \
../code/camera.c \
../code/element.c \
../code/function.c \
../code/image_process.c \
../code/motor.c \
../code/round.c \
../code/sao_xian.c 

OBJS += \
./code/IPS.o \
./code/Inductor.o \
./code/PID.o \
./code/TFT.o \
./code/camera.o \
./code/element.o \
./code/function.o \
./code/image_process.o \
./code/motor.o \
./code/round.o \
./code/sao_xian.o 

COMPILED_SRCS += \
./code/IPS.src \
./code/Inductor.src \
./code/PID.src \
./code/TFT.src \
./code/camera.src \
./code/element.src \
./code/function.src \
./code/image_process.src \
./code/motor.src \
./code/round.src \
./code/sao_xian.src 

C_DEPS += \
./code/IPS.d \
./code/Inductor.d \
./code/PID.d \
./code/TFT.d \
./code/camera.d \
./code/element.d \
./code/function.d \
./code/image_process.d \
./code/motor.d \
./code/round.d \
./code/sao_xian.d 


# Each subdirectory must supply rules for building sources it contributes
code/%.src: ../code/%.c code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fG:/AURIX-v1.8.0-workspace/Camera_car_zyx/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

code/%.o: ./code/%.src code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


