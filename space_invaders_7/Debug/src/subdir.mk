################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/alienDeathSound.c \
../src/aliens.c \
../src/banner.c \
../src/bullets.c \
../src/bunkers.c \
../src/gameFunctions.c \
../src/globals.c \
../src/platform.c \
<<<<<<< HEAD:space_invaders_7/Debug/src/subdir.mk
../src/shoot.c \
../src/sounds.c \
../src/spaceShip.c \
../src/spaceShipDeathSound.c \
../src/spaceShipSound.c \
=======
../src/spaceShip.c \
>>>>>>> 0b25e6347213efdffebb22c5d710600b9778881b:hello_world_0/Debug/src/subdir.mk
../src/tank.c \
../src/tankDeath.c \
../src/vdmaTest.c \
../src/xa97_l.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/alienDeathSound.o \
./src/aliens.o \
./src/banner.o \
./src/bullets.o \
./src/bunkers.o \
./src/gameFunctions.o \
./src/globals.o \
./src/platform.o \
<<<<<<< HEAD:space_invaders_7/Debug/src/subdir.mk
./src/shoot.o \
./src/sounds.o \
./src/spaceShip.o \
./src/spaceShipDeathSound.o \
./src/spaceShipSound.o \
=======
./src/spaceShip.o \
>>>>>>> 0b25e6347213efdffebb22c5d710600b9778881b:hello_world_0/Debug/src/subdir.mk
./src/tank.o \
./src/tankDeath.o \
./src/vdmaTest.o \
./src/xa97_l.o 

C_DEPS += \
./src/alienDeathSound.d \
./src/aliens.d \
./src/banner.d \
./src/bullets.d \
./src/bunkers.d \
./src/gameFunctions.d \
./src/globals.d \
./src/platform.d \
<<<<<<< HEAD:space_invaders_7/Debug/src/subdir.mk
./src/shoot.d \
./src/sounds.d \
./src/spaceShip.d \
./src/spaceShipDeathSound.d \
./src/spaceShipSound.d \
=======
./src/spaceShip.d \
>>>>>>> 0b25e6347213efdffebb22c5d710600b9778881b:hello_world_0/Debug/src/subdir.mk
./src/tank.d \
./src/tankDeath.d \
./src/vdmaTest.d \
./src/xa97_l.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


