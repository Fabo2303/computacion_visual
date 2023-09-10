cmake_minimum_required(VERSION 3.26)
project(semana1)

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
endfunction()

add_gl_executable(taller01_b decagonos.cpp)
add_gl_executable(taller01_c lineas_dentadas.cpp)
add_gl_executable(taller01_d lineas_engranaje.cpp)