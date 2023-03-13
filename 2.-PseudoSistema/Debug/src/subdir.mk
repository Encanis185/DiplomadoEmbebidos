################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AlfonsoJosafatLopezJauregui_Mouse_PowerState.c \
../src/mouserandom.c 

C_DEPS += \
./src/AlfonsoJosafatLopezJauregui_Mouse_PowerState.d \
./src/mouserandom.d 

OBJS += \
./src/AlfonsoJosafatLopezJauregui_Mouse_PowerState.o \
./src/mouserandom.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/AlfonsoJosafatLopezJauregui_Mouse_PowerState.d ./src/AlfonsoJosafatLopezJauregui_Mouse_PowerState.o ./src/mouserandom.d ./src/mouserandom.o

.PHONY: clean-src

