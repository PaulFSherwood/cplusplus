################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tic\ tac\ toe.cpp 

OBJS += \
./src/tic\ tac\ toe.o 

CPP_DEPS += \
./src/tic\ tac\ toe.d 


# Each subdirectory must supply rules for building sources it contributes
src/tic\ tac\ toe.o: ../src/tic\ tac\ toe.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/tic tac toe.d" -MT"src/tic\ tac\ toe.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


