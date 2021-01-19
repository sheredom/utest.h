# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

set(script "")
set(tests "")

function(add_command NAME)
  set(_args "")
  foreach(_arg IN LISTS ARGN)
    if(_arg MATCHES "[^-./:a-zA-Z0-9_]")
      set(_args "${_args} [==[${_arg}]==]")
    else()
      set(_args "${_args} ${_arg}")
    endif()
  endforeach()
  set(script "${script}${NAME}(${_args})\n" PARENT_SCOPE)
endfunction()

# Run test executable to get list of available tests
if(NOT EXISTS "${TEST_EXECUTABLE}")
  message(
      FATAL_ERROR
      "Specified test executable '${TEST_EXECUTABLE}' does not exist"
  )
endif()

execute_process(
    COMMAND
    "${TEST_EXECUTOR}" "${TEST_EXECUTABLE}" --list-tests
    OUTPUT_VARIABLE output
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE result
)
if(NOT result EQUAL "0")
  message(
      FATAL_ERROR
      "Error running test executable '${TEST_EXECUTABLE}':\n"
      "  Result: ${result}\n"
      "  Output: ${output}\n"
  )
endif()

string(REPLACE "\n" ";" output "${output}")

foreach(test IN LISTS output)
  set(xunit_output_param "")
  if(NOT TEST_XUNIT_OUTPUT_DIR STREQUAL "")
    # Turn testname into a valid filename by replacing all special characters with "-"
    string(REGEX REPLACE "[/\\:\"|<>]" "-" test_filename "${test}")
    set(xunit_output_param "--output=${TEST_XUNIT_OUTPUT_DIR}/${prefix}${test_filename}${suffix}.xml")
  endif()

  # use escape commas to handle properly test cases with commas inside the name
  string(REPLACE "," "\\," test_name "${test}")

  # ...and add to script
  set(ctest_test_name "${TEST_PREFIX}${test}${TEST_SUFFIX}")
  add_command(
      add_test
      "${ctest_test_name}"
      ${TEST_EXECUTOR}
      "${TEST_EXECUTABLE}"
      "--filter=${test_name}"
      "${xunit_output_param}"
      ${TEST_EXTRA_ARGS}
  )

  add_command(
      set_tests_properties
      "${ctest_test_name}"
      PROPERTIES
      WORKING_DIRECTORY "${TEST_WORKING_DIR}"
      ${TEST_PROPERTIES}
  )

  list(APPEND tests "${ctest_test_name}")
endforeach()

# Create a list of all discovered tests, which users may use to e.g. set
# properties on the tests
add_command(set ${TEST_LIST} ${tests})

# Write CTest script
file(WRITE "${CTEST_FILE}" "${script}")
