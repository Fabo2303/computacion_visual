cmake_minimum_required(VERSION 3.26)
project(semana1)

set(CMAKE_CXX_STANDARD 17)

add_executable(semana1 main.cpp)
add_executable(taller01_b decagonos.cpp)
add_executable(taller01_c lineas_dentadas.cpp)
add_executable(taller01_d lineas_engranaje.cpp)

target_link_libraries(taller01_d ${OPENGL_LIBRARIES})
target_link_libraries(taller01_d ${GLUT_LIBRARIES})
target_link_libraries(taller01_d -lfreeglut -lglu32 -lopengl32)

target_link_libraries(taller01_c ${OPENGL_LIBRARIES})
target_link_libraries(taller01_c ${GLUT_LIBRARIES})
target_link_libraries(taller01_c -lfreeglut -lglu32 -lopengl32)

target_link_libraries(taller01_b ${OPENGL_LIBRARIES})
target_link_libraries(taller01_b ${GLUT_LIBRARIES})
target_link_libraries(taller01_b -lfreeglut -lglu32 -lopengl32)