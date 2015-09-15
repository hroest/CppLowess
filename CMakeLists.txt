project("CppLowess")
cmake_minimum_required(VERSION 2.6)

include_directories("include")

## platform dependent compiler flags:
include(CheckCXXCompilerFlag)
if (NOT WIN32) # we only want fPIC on non-windows systems (fPIC is implicitly true there)
  CHECK_CXX_COMPILER_FLAG("-fPIC" WITH_FPIC)
  if (WITH_FPIC)
    add_definitions(-fPIC)
  endif()

  # Only add those definitions on non-windows systems
  add_definitions(-Wall -Wextra -Wno-non-virtual-dtor -Wno-long-long -Wno-variadic-macros)
  add_definitions(--pedantic)
  # Careful, this generates several hundred warnings ... 
  # add_definitions(-Wconversion)
endif()

add_executable(testLowess src/tests/testLowess.cpp)


