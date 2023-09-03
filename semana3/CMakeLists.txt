cmake_minimum_required(VERSION 3.26)
project(semana3)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)
add_executable(taller03_a ejercicio3a.cpp)
add_executable(taller03_b ejercicio4a.cpp)

target_link_libraries(main ${OPENGL_LIBRARIES})
target_link_libraries(main ${GLUT_LIBRARIES})
target_link_libraries(main -lfreeglut -lglu32 -lopengl32)

target_link_libraries(taller03_a ${OPENGL_LIBRARIES})
target_link_libraries(taller03_a ${GLUT_LIBRARIES})
target_link_libraries(taller03_a -lfreeglut -lglu32 -lopengl32)

target_link_libraries(taller03_b ${OPENGL_LIBRARIES})
target_link_libraries(taller03_b ${GLUT_LIBRARIES})
target_link_libraries(taller03_b -lfreeglut -lglu32 -lopengl32)
