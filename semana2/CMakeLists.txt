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

add_gl_executable(taller02_1_a caracol.cpp)
add_gl_executable(taller02_1_b rosal.cpp)
add_gl_executable(taller02_1_c cardioide.cpp)
add_gl_executable(taller02_1_d espiral.cpp)
add_gl_executable(taller02_2_1 yinyan.cpp)
add_gl_executable(taller02_3_1 hiperbole.cpp)
add_gl_executable(aux_a caracol_pascal.cpp)
add_gl_executable(aux_b cisoide_diocles.cpp)
add_gl_executable(aux_c concoides_nicomenes.cpp)
add_gl_executable(aux_d gludisk.cpp)
add_gl_executable(aux_e lemniscata.cpp)
add_gl_executable(aux_f nefroide_freeth.cpp)
add_gl_executable(aux_g parabola.cpp)
add_gl_executable(aux_h circulo.cpp)
add_gl_executable(aux_i rosa2.cpp)
