################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Bsp.c" \
"../Sources/Hal.c" \
"../Sources/UART.c" \
"../Sources/arm_cm0.c" \
"../Sources/main.c" \
"../Sources/main_functions.c" \
"../Sources/mcg.c" \
"../Sources/sa_mtb.c" \
"../Sources/servo.c" \

C_SRCS += \
../Sources/Bsp.c \
../Sources/Hal.c \
../Sources/UART.c \
../Sources/arm_cm0.c \
../Sources/main.c \
../Sources/main_functions.c \
../Sources/mcg.c \
../Sources/sa_mtb.c \
../Sources/servo.c \

OBJS += \
./Sources/Bsp.o \
./Sources/Hal.o \
./Sources/UART.o \
./Sources/arm_cm0.o \
./Sources/main.o \
./Sources/main_functions.o \
./Sources/mcg.o \
./Sources/sa_mtb.o \
./Sources/servo.o \

C_DEPS += \
./Sources/Bsp.d \
./Sources/Hal.d \
./Sources/UART.d \
./Sources/arm_cm0.d \
./Sources/main.d \
./Sources/main_functions.d \
./Sources/mcg.d \
./Sources/sa_mtb.d \
./Sources/servo.d \

OBJS_QUOTED += \
"./Sources/Bsp.o" \
"./Sources/Hal.o" \
"./Sources/UART.o" \
"./Sources/arm_cm0.o" \
"./Sources/main.o" \
"./Sources/main_functions.o" \
"./Sources/mcg.o" \
"./Sources/sa_mtb.o" \
"./Sources/servo.o" \

C_DEPS_QUOTED += \
"./Sources/Bsp.d" \
"./Sources/Hal.d" \
"./Sources/UART.d" \
"./Sources/arm_cm0.d" \
"./Sources/main.d" \
"./Sources/main_functions.d" \
"./Sources/mcg.d" \
"./Sources/sa_mtb.d" \
"./Sources/servo.d" \

OBJS_OS_FORMAT += \
./Sources/Bsp.o \
./Sources/Hal.o \
./Sources/UART.o \
./Sources/arm_cm0.o \
./Sources/main.o \
./Sources/main_functions.o \
./Sources/mcg.o \
./Sources/sa_mtb.o \
./Sources/servo.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Bsp.o: ../Sources/Bsp.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Bsp.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Bsp.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Hal.o: ../Sources/Hal.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Hal.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Hal.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/UART.o: ../Sources/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/UART.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/arm_cm0.o: ../Sources/arm_cm0.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/arm_cm0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/arm_cm0.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_functions.o: ../Sources/main_functions.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main_functions.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main_functions.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcg.o: ../Sources/mcg.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcg.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcg.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/servo.o: ../Sources/servo.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/servo.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/servo.o"
	@echo 'Finished building: $<'
	@echo ' '


