add_executable(app main.cpp)
target_link_libraries(app PRIVATE Boost::boost SunSpecModbus IEEE2030-5)
target_include_directories(app PUBLIC 
	${SunSpecModbus_INCLUDE_DIR} 
	${Boost_INCLUDE_DIRS} 
	${IEEE2030-5_INCLUDE_DIRS})
