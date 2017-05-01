################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/cola\ machine.cpp 

OBJS += \
./src/cola\ machine.o 

CPP_DEPS += \
./src/cola\ machine.d 


# Each subdirectory must supply rules for building sources it contributes
src/cola\ machine.o: ../src/cola\ machine.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/cola machine.d" -MT"src/cola\ machine.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


