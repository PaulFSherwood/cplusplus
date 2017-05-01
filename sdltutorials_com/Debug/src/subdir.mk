################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CApp.cpp \
../src/CApp_OnCleanup.cpp \
../src/CApp_OnEvent.cpp \
../src/CApp_OnInit.cpp \
../src/CApp_OnLoop.cpp \
../src/CApp_OnRender.cpp \
../src/CEvent.cpp \
../src/CSurface.cpp 

OBJS += \
./src/CApp.o \
./src/CApp_OnCleanup.o \
./src/CApp_OnEvent.o \
./src/CApp_OnInit.o \
./src/CApp_OnLoop.o \
./src/CApp_OnRender.o \
./src/CEvent.o \
./src/CSurface.o 

CPP_DEPS += \
./src/CApp.d \
./src/CApp_OnCleanup.d \
./src/CApp_OnEvent.d \
./src/CApp_OnInit.d \
./src/CApp_OnLoop.d \
./src/CApp_OnRender.d \
./src/CEvent.d \
./src/CSurface.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


