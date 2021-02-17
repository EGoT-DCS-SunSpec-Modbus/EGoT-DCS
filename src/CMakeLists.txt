add_executable(app main.cpp)
target_link_libraries(app PRIVATE Boost::boost SunSpecModbus SEP::Model)
target_include_directories(app PUBLIC 
	${SunSpecModbus_INCLUDE_DIR} 
	${Boost_INCLUDE_DIRS} 
	${SEP_INCLUDE_DIRS})
