include_directories(${INCLUDE_DIR} ${INCLUDE_DIR}/commands)

file(GLOB SOURCES "${SRC_DIR}/*.cpp" "${SRC_DIR}/commands/*.cpp")
file(GLOB HEADERS
        "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp"
        "${INCLUDE_DIR}/commands/*.h" "${INCLUDE_DIR}/commands/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} pthread)
set_target_properties(${PROJECT_NAME} PROPERTIES ${TARGET_PROPERTIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

install(TARGETS ${EXECUTABLES_LIST} RUNTIME DESTINATION bin)

