set(MASTERMIND_LIB_SOURCES
    impl/heuristics_data.c
    impl/mastermind.c
    impl/mastermind_representation.c
)
set(MASTERMIND_LIB_HEADERS
    impl/heuristics_data.h
    impl/mastermind.h
)

add_library(mastermind ${MASTERMIND_LIB_SOURCES} ${MASTERMIND_LIB_HEADERS})
target_include_directories(mastermind PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})