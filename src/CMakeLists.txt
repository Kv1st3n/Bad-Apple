add_library(src_library STATIC
    AsciiVideo.hh
    AsciiVideo.cxx
    Audio.hh
    Audio.cxx
    Window.hh
    Window.cxx
    Player.hh
    Player.cxx
    Video.hh
    Video.cxx
)

target_include_directories(src_library PUBLIC .)

target_link_libraries(src_library PUBLIC
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
    PkgConfig::AVCODEC
    PkgConfig::AVFORMAT
    PkgConfig::AVUTIL
    PkgConfig::SWSCALE
)

target_compile_features(src_library PRIVATE cxx_std_20)