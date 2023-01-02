add_executable(dllprojexe WIN32)

file(GLOB_RECURSE SRC_EXE_FILES CONFIGURE_DEPENDS
    "*_exe.cpp"
)

target_sources(dllprojexe PRIVATE ${SRC_EXE_FILES} hook.cpp)

target_compile_options(dllprojexe PUBLIC "/std:c++latest")

target_include_directories(dllprojexe PUBLIC include)

target_link_libraries(dllprojexe
  PRIVATE
    fmt::fmt
)

file(GLOB_RECURSE SRC_DLL_FILES CONFIGURE_DEPENDS
    "*_dll.cpp"
)

add_library(dllprojdll SHARED)

target_sources(dllprojdll PRIVATE ${SRC_DLL_FILES})

target_compile_options(dllprojdll PUBLIC "/std:c++latest")

target_include_directories(dllprojdll PUBLIC include)

target_link_libraries(dllprojdll
  PRIVATE
    fmt::fmt
)