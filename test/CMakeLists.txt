# This is free and unencumbered software released into the public domain.
#
# Anyone is free to copy, modify, publish, use, compile, sell, or
# distribute this software, either in source code form or as a compiled
# binary, for any purpose, commercial or non-commercial, and by any
# means.
#
# In jurisdictions that recognize copyright laws, the author or authors
# of this software dedicate any and all copyright interest in the
# software to the public domain. We make this dedication for the benefit
# of the public at large and to the detriment of our heirs and
# successors. We intend this dedication to be an overt act of
# relinquishment in perpetuity of all present and future rights to this
# software under copyright law.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# For more information, please refer to <http://unlicense.org/>

cmake_minimum_required(VERSION 3.15)
project(utest)

include(CTest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

# Base warning flags and whether -std= flags are supported.
# MSVC and clang-cl use /std: and don't accept -std=, so we skip
# the standard flag for those compilers.
set(UTEST_MSVC_WARNINGS "/Wall /WX /wd4514 /wd5045")
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set(UTEST_C_WARNINGS "-Wall -Wextra -Werror")
  set(UTEST_C_USE_STD_FLAG TRUE)
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
  if(CMAKE_C_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    set(UTEST_C_WARNINGS "${UTEST_MSVC_WARNINGS}")
    set(UTEST_C_USE_STD_FLAG FALSE)
  else()
    set(UTEST_C_WARNINGS "-Wall -Wextra -Weverything -Werror -Wno-poison-system-directories")
    set(UTEST_C_USE_STD_FLAG TRUE)
  endif()
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  set(UTEST_C_WARNINGS "${UTEST_MSVC_WARNINGS}")
  set(UTEST_C_USE_STD_FLAG FALSE)
else()
  message(WARNING "Unknown C compiler '${CMAKE_C_COMPILER_ID}'!")
  set(UTEST_C_WARNINGS "")
  set(UTEST_C_USE_STD_FLAG FALSE)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(UTEST_CXX_WARNINGS "-Wall -Wextra -Werror")
  set(UTEST_CXX_USE_STD_FLAG TRUE)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    set(UTEST_CXX_WARNINGS "${UTEST_MSVC_WARNINGS}")
    set(UTEST_CXX_USE_STD_FLAG FALSE)
  else()
    set(UTEST_CXX_WARNINGS "-Wall -Wextra -Weverything -Werror -Wno-poison-system-directories")
    set(UTEST_CXX_USE_STD_FLAG TRUE)
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(UTEST_CXX_WARNINGS "${UTEST_MSVC_WARNINGS}")
  set(UTEST_CXX_USE_STD_FLAG FALSE)
else()
  message(WARNING "Unknown C++ compiler '${CMAKE_CXX_COMPILER_ID}'!")
  set(UTEST_CXX_WARNINGS "")
  set(UTEST_CXX_USE_STD_FLAG FALSE)
endif()

# Helper: set compile flags for a C source file (warnings + standard).
function(utest_set_c_flags FILE STANDARD)
  if(UTEST_C_USE_STD_FLAG)
    set_source_files_properties(${FILE} PROPERTIES
      COMPILE_FLAGS "${UTEST_C_WARNINGS} ${STANDARD}")
  else()
    set_source_files_properties(${FILE} PROPERTIES
      COMPILE_FLAGS "${UTEST_C_WARNINGS}")
  endif()
endfunction()

# Helper: set compile flags for a C++ source file (warnings + standard + extras).
function(utest_set_cxx_flags FILE STANDARD)
  set(EXTRA_FLAGS ${ARGN})
  if(UTEST_CXX_USE_STD_FLAG)
    set_source_files_properties(${FILE} PROPERTIES
      COMPILE_FLAGS "${UTEST_CXX_WARNINGS} ${STANDARD} ${EXTRA_FLAGS}")
  else()
    set_source_files_properties(${FILE} PROPERTIES
      COMPILE_FLAGS "${UTEST_CXX_WARNINGS} ${EXTRA_FLAGS}")
  endif()
endfunction()

# C files — each compiled under a specific C standard.
utest_set_c_flags(main.c  "-std=gnu89")
utest_set_c_flags(test.c  "-std=gnu89")
utest_set_c_flags(test99.c "-std=c99")

list(FIND CMAKE_C_COMPILE_FEATURES c_std_11 IDX)
if(${IDX} GREATER -1)
  utest_set_c_flags(test11.c "-std=c11")

  if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set_source_files_properties(type_printers.c PROPERTIES
      COMPILE_FLAGS "-std=gnu11")
  endif()
endif()

# C++ files — each compiled under a specific C++ standard.
utest_set_cxx_flags(test.cpp   "" "-Wno-c++98-compat")
utest_set_cxx_flags(test98.cpp "-std=gnu++98")
utest_set_cxx_flags(test11.cpp "-std=c++11" "-Wno-c++98-compat")
utest_set_cxx_flags(test14.cpp "-std=c++14" "-Wno-c++98-compat")
utest_set_cxx_flags(test17.cpp "-std=c++17" "-Wno-c++98-compat")
utest_set_cxx_flags(test20.cpp "-std=c++20" "-Wno-c++98-compat")
if(MSVC OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
  utest_set_cxx_flags(test_no_exceptions.cpp "" "/EHs-c-")
else()
  utest_set_cxx_flags(test_no_exceptions.cpp "-std=gnu++98" "-fno-exceptions")
endif()

set(UTEST_TEST_SOURCES
  ../utest.h
  test_shared.h
  main.c
  test.c
  test99.c
  test11.c
  test.cpp
  test98.cpp
  test11.cpp
  test14.cpp
  test17.cpp
  test20.cpp
  test_no_exceptions.cpp
  stdint_include.c
  type_printers.c
  type_printers.cpp
  side_effects.c
  side_effects.cpp
)

function(utest_register_test NAME)
  add_test(NAME ${NAME} COMMAND $<TARGET_FILE:${NAME}>)
  set_tests_properties(${NAME} PROPERTIES
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${NAME}>)
endfunction()

function(utest_add_random_order_tests NAME)
  add_test(NAME ${NAME}_random_order
    COMMAND $<TARGET_FILE:${NAME}> --random-order)
  add_test(NAME ${NAME}_random_order_seed
    COMMAND $<TARGET_FILE:${NAME}> --random-order=42)
  set_tests_properties(${NAME}_random_order ${NAME}_random_order_seed PROPERTIES
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${NAME}>)
endfunction()

# Helper: add a test executable and register it with CTest.
function(utest_add_test NAME)
  add_executable(${NAME} ${UTEST_TEST_SOURCES})
  utest_register_test(${NAME})
endfunction()

utest_add_test(utest_test)
utest_add_random_order_tests(utest_test)

# Whole-program-optimization variant.
utest_add_test(utest_test_wpo)
if(MSVC)
  target_compile_options(utest_test_wpo PRIVATE "$<$<CONFIG:RELEASE>:/GL>")
  target_link_options(utest_test_wpo PRIVATE "$<$<CONFIG:RELEASE>:/LTCG>")
endif()

if(MSVC)
  # Build a second test binary linked against the static CRT (/MT)
  # to ensure we work with both static and dynamic libc linkage.
  set_property(TARGET utest_test PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
  utest_add_test(utest_test_mt)
  set_property(TARGET utest_test_mt PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Some sanitizer runtimes can't initialise on every host even when
# the toolchain links them fine — e.g. clang's TSan and MSan on
# aarch64 only ship shadow-memory layouts for 39-, 42- and 48-bit
# user VMAs, but Raspberry Pi OS' kernel is configured with
# CONFIG_ARM64_VA_BITS=47. The binary builds, but aborts before
# main with "FATAL: ThreadSanitizer: unsupported VMA range". Probe
# each candidate sanitizer with try_run and skip the ones whose
# runtime can't start. Result is cached so reconfigure is cheap;
# delete CMakeCache.txt to re-probe (e.g. after changing kernels).
function(utest_check_sanitizer_runs SAN OUT_VAR)
  set(CACHE_VAR "UTEST_SAN_${SAN}_RUNS")
  if(DEFINED ${CACHE_VAR})
    set(${OUT_VAR} ${${CACHE_VAR}} PARENT_SCOPE)
    return()
  endif()

  set(PROBE_SRC "${CMAKE_BINARY_DIR}/utest_san_probe_${SAN}.c")
  file(WRITE "${PROBE_SRC}" "int main(void) { return 0; }\n")

  try_run(RUN_RESULT COMPILE_RESULT
    "${CMAKE_BINARY_DIR}/utest_san_probe_${SAN}"
    "${PROBE_SRC}"
    COMPILE_DEFINITIONS "-fsanitize=${SAN}" "-fno-omit-frame-pointer"
    LINK_OPTIONS "-fsanitize=${SAN}"
  )

  if(COMPILE_RESULT AND "${RUN_RESULT}" STREQUAL "0")
    set(RESULT TRUE)
    message(STATUS "Sanitizer ${SAN}: usable")
  else()
    set(RESULT FALSE)
    message(STATUS "Sanitizer ${SAN}: skipping "
                   "(compile=${COMPILE_RESULT}, run=${RUN_RESULT})")
  endif()

  set(${CACHE_VAR} ${RESULT} CACHE INTERNAL
      "Whether the ${SAN} sanitizer runtime starts on this host")
  set(${OUT_VAR} ${RESULT} PARENT_SCOPE)
endfunction()

if(("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang") AND NOT "${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}" STREQUAL "MSVC")
  set(UTEST_SANITIZER_CANDIDATES
    address
    undefined
    thread
  )

  if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang")
    set(UTEST_SANITIZER_CANDIDATES ${UTEST_SANITIZER_CANDIDATES} memory)
  endif()

  set(UTEST_SANITIZERS)
  foreach(UTEST_SANITIZER ${UTEST_SANITIZER_CANDIDATES})
    if(CMAKE_CROSSCOMPILING)
      list(APPEND UTEST_SANITIZERS ${UTEST_SANITIZER})
    else()
      utest_check_sanitizer_runs(${UTEST_SANITIZER} UTEST_SAN_RUNS)
      if(UTEST_SAN_RUNS)
        list(APPEND UTEST_SANITIZERS ${UTEST_SANITIZER})
      endif()
    endif()
  endforeach()

  foreach(UTEST_SANITIZER ${UTEST_SANITIZERS})
    utest_add_test(utest_${UTEST_SANITIZER}_test)
    utest_add_random_order_tests(utest_${UTEST_SANITIZER}_test)
    target_compile_options(utest_${UTEST_SANITIZER}_test PRIVATE -fsanitize=${UTEST_SANITIZER} -fno-omit-frame-pointer)
    target_link_options(utest_${UTEST_SANITIZER}_test PRIVATE -fsanitize=${UTEST_SANITIZER})
  endforeach()
endif()
