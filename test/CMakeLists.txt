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

cmake_minimum_required(VERSION 3.14)

project(utest)

set(
    utest_INCLUDE_WITHOUT_SYSTEM
    YES
    CACHE
    INTERNAL
    "Turn the warning guard off to have errors appear in test builds"
)

include(FetchContent)
FetchContent_Declare(utest SOURCE_DIR "${PROJECT_SOURCE_DIR}/..")
FetchContent_MakeAvailable(utest)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(main.c test.c PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Werror -std=gnu89"
  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set_source_files_properties(main.c test.c PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -std=gnu89"
  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  set_source_files_properties(main.c test.c PROPERTIES
    COMPILE_FLAGS "/Wall /WX /wd4514 /wd5045"
  )
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(test99.c PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Werror -std=c99"
  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set_source_files_properties(test99.c PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -std=c99"
  )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  set_source_files_properties(test99.c PROPERTIES
    COMPILE_FLAGS "/Wall /WX /wd4514 /wd5045"
  )
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()

list(FIND CMAKE_C_COMPILE_FEATURES c_std_11 IDX)
if (${IDX} GREATER -1)
  if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
      set_source_files_properties(type_printers.c PROPERTIES
        COMPILE_FLAGS "-std=gnu11")

      set_source_files_properties(test11.c PROPERTIES
        COMPILE_FLAGS "-Wall -Wextra -Werror -std=c11"
      )
  elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
      set_source_files_properties(test11.c PROPERTIES
        COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -std=c11"
      )
  elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    set_source_files_properties(test11.c PROPERTIES
      COMPILE_FLAGS "/Wall /WX /wd4514 /wd5045"
    )
  else()
    message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
  endif()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(test.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Werror -std=gnu++98"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set_source_files_properties(test.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -std=gnu++98"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set_source_files_properties(test.cpp PROPERTIES
    COMPILE_FLAGS "/Wall /WX /wd4514 /wd5045"
  )
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set_source_files_properties(test11.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Werror -std=c++11"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set_source_files_properties(test11.cpp PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra -Weverything -Werror -std=c++11 -Wno-c++98-compat"
  )
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set_source_files_properties(test11.cpp PROPERTIES
    COMPILE_FLAGS "/Wall /WX /wd4514 /wd5045"
  )
else()
  message(WARNING "Unknown compiler '${CMAKE_C_COMPILER_ID}'!")
endif()

add_executable(utest_test
  main.c
  test.c
  test11.c
  test99.c
  test.cpp
  test11.cpp
  stdint_include.c
  type_printers.c
  type_printers.cpp
)

add_executable(utest_test_wpo
  main.c
  test.c
  test11.c
  test99.c
  test.cpp
  test11.cpp
  stdint_include.c
  type_printers.c
  type_printers.cpp
)

target_link_libraries(utest_test PRIVATE utest::utest)
target_link_libraries(utest_test_wpo PRIVATE utest::utest)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  target_compile_options(utest_test_wpo PRIVATE "$<$<CONFIG:RELEASE>:/GL>")
  target_link_options(utest_test_wpo PRIVATE "$<$<CONFIG:RELEASE>:/LTCG>")
endif()
