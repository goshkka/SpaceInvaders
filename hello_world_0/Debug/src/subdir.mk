################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/aliens.c \
../src/banner.c \
../src/bullets.c \
../src/bunkers.c \
../src/gameFunctions.c \
../src/globals.c \
../src/platform.c \
../src/spaceship.c \
../src/tank.c \
../src/vdmaTest.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/aliens.o \
./src/banner.o \
./src/bullets.o \
./src/bunkers.o \
./src/gameFunctions.o \
./src/globals.o \
./src/platform.o \
./src/spaceship.o \
./src/tank.o \
./src/vdmaTest.o 

C_DEPS += \
./src/aliens.d \
./src/banner.d \
./src/bullets.d \
./src/bunkers.d \
./src/gameFunctions.d \
./src/globals.d \
./src/platform.d \
./src/spaceship.d \
./src/tank.d \
./src/vdmaTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


