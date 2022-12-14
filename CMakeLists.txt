#ifndef CMAKELISTS_TXT
#define CMAKELISTS_TXT
cmake_minimum_required(VERSION 3.10)

project(Vecplot VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VP_SOURCE_DIR
    src
)


link_directories(${PROJECT_SOURCE_DIR}/lib)
# include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR})

set(VP_SOURCES
    ${VP_SOURCE_DIR}/main.cpp
    ${VP_SOURCE_DIR}/CoordinateSystem.cpp
    ${VP_SOURCE_DIR}/VectorPlot.cpp
    ${VP_SOURCE_DIR}/Application.cpp
    ${VP_SOURCE_DIR}/MainWindow.cpp
)

set(VP_HEADERS
    ${VP_SOURCE_DIR}/CoordinateSystem.hpp
    ${VP_SOURCE_DIR}/VectorPlot.hpp
    ${VP_SOURCE_DIR}/Application.hpp
    ${VP_SOURCE_DIR}/MainWindow.hpp
)

set(VP_LIBS
    MGeomerty
    AbstractGL
    Raytracer
    LogUtils
    Vector
    Widgets
    GEditor
    ColorDialog
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-fPIC -Weverything -O1 -Wno-implicit-int-conversion -Wno-documentation -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded -Wno-weak-vtables -Wno-sign-conversion -Wno-covered-switch-default -Werror=return-type)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # add_compile_options(-Wall -Wextra -Wno-error=padded -Wno-weak-vtables)
    set (GNU_SANITIZE_FLAGS
        -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
    )
    add_compile_options(-ggdb3 -O1 -fmax-errors=1
    # add_compile_options(-ggdb3 -O3 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE 
        ${GNU_SANITIZE_FLAGS}
    )
    add_link_options(${GNU_SANITIZE_FLAGS} -rdynamic)
endif()


foreach(lib ${VP_LIBS})
    add_subdirectory(${VP_SOURCE_DIR}/${lib})
endforeach()

add_subdirectory(${VP_SOURCE_DIR}/Plugins)

add_executable(main ${VP_SOURCES} ${VP_HEADERS})
add_executable(geditor src/GEMain.cpp)

target_link_libraries(main PUBLIC ${VP_LIBS})
target_link_libraries(geditor PUBLIC ${VP_LIBS})
set_property(TARGET geditor PROPERTY ENABLE_EXPORTS ON)

# target_include_directories(main PUBLIC 
    # ${VP_SOURCE_DIR}/MGeomerty
# )


#endif /* CMAKELISTS_TXT */
