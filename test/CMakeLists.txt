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

project(utest)
cmake_minimum_required(VERSION 3.15)

set(UTEST_USE_SANITIZER "" CACHE STRING "Set which Clang Sanitizer to use")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

function(set_flags file msvc gcc clang_extra)
  if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set_source_files_properties("${file}" PROPERTIES COMPILE_FLAGS "${gcc}")
  elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
      set_source_files_properties("${file}" PROPERTIES COMPILE_FLAGS "${msvc}")
    else()
      set_source_files_properties("${file}" PROPERTIES COMPILE_FLAGS "${gcc} ${clang_extra}")
    endif()
  elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    set_source_files_properties("${file}" PROPERTIES COMPILE_FLAGS "${msvc}")
  else()
    message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
  endif()
endfunction()

set(MSVC_WARNINGS "/Wall /WX /wd4514 /wd5045")
set(GCC_WARNINGS "-Wall -Wextra -Werror")
set(CLANG_WARNINGS "-Weverything")

set_flags(main.c "${MSVC_WARNINGS}" "${GCC_WARNINGS} -std=gnu89" "${CLANG_WARNINGS}")
set_flags(test.c "${MSVC_WARNINGS}" "${GCC_WARNINGS} -std=gnu89" "${CLANG_WARNINGS}")
set_flags(test99.c "${MSVC_WARNINGS}" "${GCC_WARNINGS} -std=c99" "${CLANG_WARNINGS}")

list(FIND CMAKE_C_COMPILE_FEATURES c_std_11 IDX)
if (${IDX} GREATER -1)
  set_flags(test11.c "${MSVC_WARNINGS} /std:c11" "${GCC_WARNINGS} -std=c11" "${CLANG_WARNINGS}")

  if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
      set_source_files_properties(type_printers.c PROPERTIES
        COMPILE_FLAGS "-std=gnu11")
  endif()
endif()

set_flags(test.cpp "${MSVC_WARNINGS}" "${GCC_WARNINGS} -std=gnu++98" "${CLANG_WARNINGS}")
set_flags(test_no_exceptions.cpp "${MSVC_WARNINGS} /EHs-c-" "${GCC_WARNINGS} -fno-exceptions -std=gnu++98" "${CLANG_WARNINGS}")

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_11 IDX)
if (${IDX} GREATER -1)
  set_flags(test11.cpp "${MSVC_WARNINGS}" "${GCC_WARNINGS} -std=c++11" "${CLANG_WARNINGS}")
endif()

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_14 IDX)
if (${IDX} GREATER -1)
  set_flags(test14.cpp "${MSVC_WARNINGS} /std:c++14" "${GCC_WARNINGS} -std=c++14" "${CLANG_WARNINGS}")
endif()

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_17 IDX)
if (${IDX} GREATER -1)
  set_flags(test17.cpp "${MSVC_WARNINGS} /std:c++17" "${GCC_WARNINGS} -std=c++17" "${CLANG_WARNINGS}")
endif()

set(SOURCES
  ../utest.h
  main.c
  test.c
  test11.c
  test99.c
  test.cpp
  test11.cpp
  test14.cpp
  test17.cpp
  test_no_exceptions.cpp
  stdint_include.c
  type_printers.c
  type_printers.cpp
  side_effects.c
  side_effects.cpp
)

add_executable(utest_test ${SOURCES})

if(NOT "${UTEST_USE_SANITIZER}" STREQUAL "")
  target_compile_options(utest_test PUBLIC -fno-omit-frame-pointer -fsanitize=${UTEST_USE_SANITIZER})
  target_link_options(utest_test PUBLIC -fno-omit-frame-pointer -fsanitize=${UTEST_USE_SANITIZER})
endif()

add_executable(utest_test_wpo ${SOURCES})

if(NOT "${UTEST_USE_SANITIZER}" STREQUAL "")
  target_compile_options(utest_test_wpo PUBLIC -fno-omit-frame-pointer -fsanitize=${UTEST_USE_SANITIZER})
  target_link_options(utest_test_wpo PUBLIC -fno-omit-frame-pointer -fsanitize=${UTEST_USE_SANITIZER})
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  target_compile_options(utest_test_wpo PRIVATE "$<$<CONFIG:RELEASE>:/GL>")
  target_link_options(utest_test_wpo PRIVATE "$<$<CONFIG:RELEASE>:/LTCG>")
endif()

add_executable(utest_test_mt ${SOURCES})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
    target_compile_options(utest_test_mt PUBLIC "/MT")
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  target_compile_options(utest_test_mt PUBLIC "/MT")
endif()
