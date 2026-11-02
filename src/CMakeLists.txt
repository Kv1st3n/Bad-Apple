add_library(src_library STATIC
    window.hh
    window.cxx
)

target_include_directories(src_library PUBLIC .)

target_link_libraries(src_library PUBLIC
    SDL3::SDL3
)

target_compile_features(src_library PRIVATE cxx_std_20)