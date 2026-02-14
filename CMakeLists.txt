cmake_minimum_required(VERSION 4.1)
project(purpurea
        HOMEPAGE_URL https://github.com/crazybolillo/purpurea
        LANGUAGES C ASM
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_CLANG_TIDY clang-tidy)
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -fno-integrated-as")

set(MCU "stm32f070f6")
set(MCU_FAMILY "STM32F070x6")

set(CPU_FLAGS -mthumb -mcpu=cortex-m0 -nostdlib)
set(COMPILER_FLAGS -ffunction-sections -fdata-sections)
add_compile_options(${CPU_FLAGS} ${COMPILER_FLAGS})

include(vendor/arm-cmake/utils.cmake)
if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    include(vendor/arm-cmake/clang_utils.cmake)
    clang_utils_get_arm_gcc_sysroot(${ARM_GCC_C_COMPILER} "${CPU_FLAGS}")
    clang_utils_get_arm_gcc_multilib_dir(${ARM_GCC_C_COMPILER} "${CPU_FLAGS}")
    clang_utils_get_arm_gcc_lib_dir(${ARM_GCC_C_COMPILER} "${CPU_FLAGS}")
    clang_utils_get_arm_gcc_crt(${ARM_GCC_SYSROOT} ${ARM_GCC_MULTIDIR} ${ARM_GCC_LIBGCC_DIR})
    string(APPEND CMAKE_EXE_LINKER_FLAGS
            " -nostdlib -L${ARM_GCC_SYSROOT}/lib/${ARM_GCC_MULTIDIR} -L${ARM_GCC_LIBGCC_DIR}")
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -lgcc -lnosys -lc")
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    string(REGEX MATCH ".*\.specs.*" has_specs "${CMAKE_EXE_LINKER_FLAGS}")

    if(NOT has_specs)
        string(APPEND CMAKE_EXE_LINKER_FLAGS " --specs=nosys.specs")
    endif()
endif()

string(APPEND CMAKE_C_LINK_EXECUTABLE " -Wl,-Map,<TARGET_BASE>.map")

set(LINKER_FILE "${CMAKE_CURRENT_LIST_DIR}/${MCU}.ld")
string(APPEND CMAKE_EXE_LINKER_FLAGS " -T ${LINKER_FILE} -Wl,--gc-sections")

add_compile_definitions(${MCU_FAMILY})

add_subdirectory(vendor)
add_subdirectory(src)
