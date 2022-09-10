cmake_minimum_required(VERSION 2.8)

project(main)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-lrt")

# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)  

# find_library (CMWCMX_LIBRARIES_C NAMES libcmw-cmx.a PATHS "/usr/local/lib")
# find_library (CMWCMX_LIBRARIES_CPP NAMES libcmw-cmx-cpp.a PATHS "/usr/local/lib")
find_library (CMWCMX_LIBRARIES_C NAMES cmw-cmx PATHS "/usr/local/lib")
find_library (CMWCMX_LIBRARIES_CPP NAMES cmw-cmx-cpp PATHS "/usr/local/lib")

include_directories( "/usr/local/include/cmw-cmx" )
add_executable(main main.cpp)
target_link_libraries(main "${CMWCMX_LIBRARIES_C}" "${CMWCMX_LIBRARIES_CPP}")
