cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(piccolo-uac2 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.5.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.5.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()
# Initialize the SDK
pico_sdk_init()

set(CMAKE_C_FLAGS_RELEASE "-O3 -fno-data-sections")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fno-data-sections")

# This cuts binary size, but disables alarms.
#  target_compile_definitions(hardware_timer INTERFACE PICO_TIME_DEFAULT_ALARM_POOL_DISABLED=1)

add_executable(uac2
  uac2.c
)

#pico_set_binary_type(uac2 copy_to_ram)
#pico_define_boot_stage2(uac2-div4 ${PICO_DEFAULT_BOOT_STAGE2_FILE})
#target_compile_definitions(uac2-div4 PRIVATE PICO_FLASH_SPI_CLKDIV=4)
#pico_set_boot_stage2(uac2 uac2-div4)
target_link_libraries(uac2
  #hardware_pio
  #hardware_spi
  #pico_multicore
  pico_stdlib
)
pico_add_extra_outputs(uac2)
