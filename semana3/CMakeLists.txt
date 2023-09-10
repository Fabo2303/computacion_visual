cmake_minimum_required(VERSION 3.26)
project(semana3)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.26)
project(semana2)

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

add_gl_executable(taller03 main.cpp)
add_gl_executable(taller03_c ejercicio2a.cpp)
add_gl_executable(taller03_a ejercicio3a.cpp)
add_gl_executable(taller03_b ejercicio4a.cpp)
add_gl_executable(taller03_d ejercicio5a.cpp)
