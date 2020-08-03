list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ClangFormat)
clangformat_setup(
        main.cpp
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES
    "*.h"
    "*.cpp"
)

message( ${PROJECT_SOURCE_DIR} )
message( "${SRC_FILES}" )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.72.0)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    # add_executable(progname file1.cxx file2.cxx)
    #target_link_libraries(progname ${Boost_LIBRARIES})
endif ()

# static library
# add_library(mylib_static STATIC mylib.cpp CPU.cpp)
add_library(mylib_static STATIC main.cpp CPU.cpp CPU.h Registers.cpp Registers.h Memory.cpp Memory.h LocationBase.cpp LocationBase.h MemoryLocation.cpp MemoryLocation.h MemoryInstruction.cpp MemoryInstruction.h RegisterLocation.cpp RegisterLocation.h InstructionBase.cpp InstructionBase.h InstructionFactory.cpp InstructionFactory.h ArithmeticInstruction.cpp ArithmeticInstruction.h util.cpp util.h)
target_include_directories(
        mylib_static
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        PRIVATE
        ${PROJECT_BINARY_DIR}
)

# shared library
add_library(mylib_shared SHARED mylib.cpp)

# compile main executable
add_executable(main.x main.cpp CPU.cpp CPU.h Registers.cpp Registers.h Memory.cpp Memory.h LocationBase.cpp LocationBase.h MemoryLocation.cpp MemoryLocation.h MemoryInstruction.cpp MemoryInstruction.h RegisterLocation.cpp RegisterLocation.h InstructionBase.cpp InstructionBase.h InstructionFactory.cpp InstructionFactory.h ArithmeticInstruction.cpp ArithmeticInstruction.h util.cpp util.h)
target_include_directories(
        main.x
        PRIVATE
        ${PROJECT_BINARY_DIR}
        PUBLIC
        ${Boost_INCLUDE_DIRS}
)

# link library
target_link_libraries(main.x mylib_static)
target_link_libraries(main.x ${Boost_LIBRARIES})

# install binary
install(TARGETS main.x DESTINATION cmake-example/bin)

# install libs
install(TARGETS mylib_shared DESTINATION cmake-example/lib)
install(TARGETS mylib_static DESTINATION cmake-example/lib)

# install headers
install(FILES ${PROJECT_SOURCE_DIR}/src/mylib.h DESTINATION cmake-example/include)
