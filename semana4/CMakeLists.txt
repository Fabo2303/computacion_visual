cmake_minimum_required(VERSION 3.26)
project(semana4)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(COMMON_LIBS
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        -lfreeglut
        -lglu32
        -lopengl32
)

function(add_gl_executable target_name source_file)
    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name} ${COMMON_LIBS})
    include_directories(${CMAKE_SOURCE_DIR})
endfunction()

add_gl_executable(Main main.cpp)
add_executable(taller04_a ejercicio1.cpp polares.cpp)
target_link_libraries(taller04_a ${OPENGL_LIBRARIES})
target_link_libraries(taller04_a ${GULT_LIBRARIES})
target_link_libraries(taller04_a -lopengl32 -g -lfreeglut)