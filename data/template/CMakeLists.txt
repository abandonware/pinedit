
# Generate Make-template and pinball-template
set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix ${CMAKE_INSTALL_PREFIX})
set(datadir ${CMAKE_INSTALL_PREFIX}/share/games)
configure_file(pinball-template.in "${PROJECT_BINARY_DIR}/pinball-template" @ONLY)

find_file(SDL_CONFIG sdl-config PATHS /usr/bin)
execute_process(COMMAND which install OUTPUT_VARIABLE INSTALL)
configure_file(Make-template.in "${PROJECT_BINARY_DIR}/Make-template" @ONLY)

# Install everything.
set (PINEDIT_TEMPLATE_FILES ModuleScript.cpp pinball.pbl "${PROJECT_BINARY_DIR}/Make-template")

install(FILES ${PINEDIT_TEMPLATE_FILES} DESTINATION share/games/${PINEDIT_EXEC_NAME}/template)


install(FILES "${PROJECT_BINARY_DIR}/pinball-template" DESTINATION games)
