# Target interfaccia con le opzioni di warning comuni.
add_library(dama_warnings INTERFACE)
target_compile_options(dama_warnings INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
)

add_library(dama_engine
  engine.cpp
  game_state.cpp
)
add_library(dama::engine ALIAS dama_engine)

target_include_directories(dama_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dama_engine PUBLIC dama_warnings)
 