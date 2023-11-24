# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/alumno/.pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(lampara_inteligente C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(lampara_inteligente lampara_inteligente.c )

pico_set_program_name(lampara_inteligente "lampara_inteligente")
pico_set_program_version(lampara_inteligente "0.1")

pico_enable_stdio_uart(lampara_inteligente 0)
pico_enable_stdio_usb(lampara_inteligente 1)

add_library(libs
	libs/lcd_i2c.c
)

target_include_directories(libs PUBLIC libs/inc)

target_link_libraries(libs hardware_i2c pico_stdlib)

# Add the standard library to the build
target_link_libraries(lampara_inteligente
        pico_stdlib
        hardware_adc
        hardware_pwm
        libs
)

# Add the standard include files to the build
target_include_directories(lampara_inteligente PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(lampara_inteligente 
)

pico_add_extra_outputs(lampara_inteligente)

