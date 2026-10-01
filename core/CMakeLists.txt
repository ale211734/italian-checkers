# Target interfaccia con le opzioni di warning comuni.
add_library(dama_warnings INTERFACE)
target_compile_options(dama_warnings INTERFACE
  $<$<COMPILE_LANGUAGE:CXX>:/W4>
)

add_library(dama_engine
  engine.cpp
)
add_library(dama::engine ALIAS dama_engine)

target_include_directories(dama_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(dama_engine PUBLIC dama_warnings)
 