################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/data/shoot.c \
../src/data/soundConverter.c 

OBJS += \
./src/data/shoot.o \
./src/data/soundConverter.o 

C_DEPS += \
./src/data/shoot.d \
./src/data/soundConverter.d 


# Each subdirectory must supply rules for building sources it contributes
src/data/%.o: ../src/data/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


