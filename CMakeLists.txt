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

project(
    utest
    VERSION 0.0.1
    DESCRIPTION "Single header unit testing framework for C and C++"
    HOMEPAGE_URL "https://github.com/sheredom/utest.h"
    LANGUAGES C
)

# ---- Warning guard ----

# Protect dependents from this project's warnings if the guard isn't disabled
set(utest_warning_guard SYSTEM)
if(utest_INCLUDE_WITHOUT_SYSTEM)
  set(utest_warning_guard "")
endif()

# ---- Declare library ----

add_library(utest INTERFACE)
add_library(utest::utest ALIAS utest)

target_include_directories(
    utest
    ${utest_warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

# ---- Install ----

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(utest_directory utest)
set(utest_include_directory "${CMAKE_INSTALL_INCLUDEDIR}/${utest_directory}")

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
    DESTINATION "${utest_include_directory}"
    COMPONENT utest_Development
)

install(
    TARGETS utest
    EXPORT utestTargets
    INCLUDES DESTINATION "${utest_include_directory}"
)

write_basic_package_version_file(
    utest-config-version.cmake
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

set(utest_install_cmakedir "${CMAKE_INSTALL_LIBDIR}/cmake/${utest_directory}")

install(
    DIRECTORY "${PROJECT_SOURCE_DIR}/cmake/modules"
    DESTINATION "${utest_install_cmakedir}"
    COMPONENT utest_Development
)

install(
    FILES
    "${PROJECT_SOURCE_DIR}/cmake/utest-config.cmake"
    "${PROJECT_BINARY_DIR}/utest-config-version.cmake"
    DESTINATION "${utest_install_cmakedir}"
    COMPONENT utest_Development
)

install(
    EXPORT utestTargets
    NAMESPACE utest::
    DESTINATION "${utest_install_cmakedir}"
    COMPONENT utest_Development
)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  include(CPack)
endif()
