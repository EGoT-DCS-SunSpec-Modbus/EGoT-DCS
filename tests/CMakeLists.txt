add_executable(all-tests 
    main.cpp 
    simple-test.cpp)

target_link_libraries(all-tests gtest gmock gtest_main)
target_include_directories(all-tests PUBLIC ${Boost_INCLUDE_DIRS})
add_test(all-tests all-tests)
