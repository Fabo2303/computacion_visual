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

add_gl_executable(Main primitive_quadri.cpp)
add_gl_executable(Ejemplo ejemplo.cpp)
add_gl_executable(Jaja jaja.cpp)
add_gl_executable(Prueba cuboRotaConTeclado.cpp)
add_gl_executable(Ejercicio_1 ejercicio1.cpp)
add_gl_executable(Ejercicio_2 ejercicio2.cpp)
add_gl_executable(Ejercicio_3 ejercicio3.cpp)
add_executable(Ejercicio_4 ejercicio4.cpp figures.cpp)
target_link_libraries(Ejercicio_4 ${OPENGL_LIBRARIES})
target_link_libraries(Ejercicio_4 ${GULT_LIBRARIES})
target_link_libraries(Ejercicio_4 -lopengl32 -g -lfreeglut)
add_gl_executable(Ejercicio_5 ejercicio5.cpp)
add_gl_executable(Ejercicio_6 ejercicio6.cpp)
add_gl_executable(Ejercicio_7 ejercicio7.cpp)
add_gl_executable(Pr pruebas_elipsticas.cpp)