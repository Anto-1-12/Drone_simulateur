cmake_minimum_required(VERSION 3.10)

project(Simulateur_De_Drone VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "C:/SFML")

include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

include_directories(
    PRIVATE_HEADER 
    ${PROJECT_SOURCE_DIR}/cpp
    )

file(
    GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    ${PROJECT_SOURCE_DIR}/cpp/*.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE

)

# ---- Copie les assets dans le dossier de build ----
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/cpp/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)