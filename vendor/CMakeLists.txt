set(CMSIS_F0_PATH "cmsis-device-f0/Source/Templates/gcc")
set(STARTUP_stm32f070f6 "startup_stm32f070x6.s")

set(STARTUP_FILE "${CMAKE_CURRENT_LIST_DIR}/${STARTUP_${MCU}}")

file(GLOB_RECURSE VENDOR_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.c"
    "${CMAKE_CURRENT_LIST_DIR}/*.h"
)
set_source_files_properties(${VENDOR_SOURCES} PROPERTIES SKIP_LINTING ON)

add_library(stm32_system
    cmsis-device-f0/Source/Templates/system_stm32f0xx.c
    ${STARTUP_FILE}
)
target_include_directories(stm32_system PUBLIC
    cmsis-6/CMSIS/Core/Include
    cmsis-device-f0/Include
)

file(GLOB STM32_LL_SOURCE "stm32f0xx-hal-driver/Src/stm32f0xx_ll_*.c")
list(FILTER STM32_LL_SOURCE EXCLUDE REGEX ".*_usb\\.c$")

add_library(stm32_ll ${STM32_LL_SOURCE})
target_include_directories(stm32_ll PUBLIC
    cmsis-6/CMSIS/Core/Include
    cmsis-device-f0/Include
    stm32f0xx-hal-driver/Inc
)
target_compile_options(stm32_ll PRIVATE -w)
