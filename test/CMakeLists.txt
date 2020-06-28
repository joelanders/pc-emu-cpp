set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    unit_tests
    main.cpp
    add.cpp
    )

target_include_directories(unit_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.72.0)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    # add_executable(progname file1.cxx file2.cxx)
    #target_link_libraries(progname ${Boost_LIBRARIES})
endif ()

target_link_libraries(
    unit_tests
    gtest_main
    mylib_static
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
