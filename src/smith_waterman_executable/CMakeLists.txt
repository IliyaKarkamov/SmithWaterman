project(smith_waterman_executable)

add_executable(${PROJECT_NAME} src/main.cpp "src/smith_waterman.h" "src/smith_waterman.cpp")

target_link_libraries(${PROJECT_NAME} smith_waterman_utils)

if (GENERATE_INSTALL)
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION bin)
endif ()