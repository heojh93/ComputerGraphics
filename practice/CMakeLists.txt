# -*- mode: cmake; -*-
cmake_minimum_required(VERSION 2.8)
project(OgreFltk)
if(APPLE)
	# sudo port install glfw freeglut
	include_directories("/opt/local/include")
endif()
if(UNIX)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG -Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG -Wall")
else()
	include_directories("${OgreFltk_SOURCE_DIR}/freeglut/include")
endif()

add_executable(p31 "practice3_1.cpp" )
add_executable(p32 "practice3_2.cpp" )
add_executable(p32s "practice3_2_smooth.cpp" )
add_executable(p33 "practice3_3.cpp" )
add_executable(p34 "practice3_4.cpp" )
add_executable(snake "snake.cpp")
if(APPLE)
	set(GLUT_LIBS
		/System/Library/Frameworks/CoreFoundation.framework
		/System/Library/Frameworks/IOKit.framework
		/System/Library/Frameworks/Cocoa.framework
		/System/Library/Frameworks/OpenGL.framework
		/opt/local/lib/libglfw.dylib
		#/opt/local/lib/libglut.dylib
		/System/Library/Frameworks/GLUT.framework
		/opt/local/lib/libfreeimage.dylib
		)

elseif(UNIX)
	set(GLUT_LIBS 
		GL
		GLU
		glut
		)
else()
	set(GLUT_LIBS 
		OpenGL32.lib
		glu32.lib
		"${OgreFltk_SOURCE_DIR}/freeglut/lib/freeglut.lib"
		)
endif()
target_link_libraries(p31 ${GLUT_LIBS})
target_link_libraries(p32 ${GLUT_LIBS})
target_link_libraries(p32s ${GLUT_LIBS})
target_link_libraries(p33 ${GLUT_LIBS})
target_link_libraries(p34 ${GLUT_LIBS})
target_link_libraries(snake ${GLUT_LIBS})
