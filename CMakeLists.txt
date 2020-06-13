cmake_minimum_required(VERSION 3.15)

project(SFML-Finding-Game)

set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(SRC
    "main.cpp"
    "src/Game.cpp"
    "include/Game.h"
    "src/Components/AnimationComponent.cpp"
    "include/Components/AnimationComponent.h"
    "src/Components/MovementComponent.cpp"
    "include/Components/MovementComponent.h"
    "src/Entity/Diamond.cpp"
    "include/Entity/Diamond.h"
    "src/Entity/Entity.cpp"
    "include/Entity/Entity.h"
    "src/Entity/Player.cpp"
    "include/Entity/Player.h"
    "src/States/CreditsState.cpp"
    "include/States/CreditsState.h"
    "src/States/GameState.cpp"
    "include/States/GameState.h"
    "src/States/MainMenuState.cpp"
    "include/States/MainMenuState.h"
    "src/States/State.cpp"
    "include/States/State.h"
    "src/UI/Button.cpp"
    "include/UI/Button.h"
    "src/UI/PauseMenu.cpp"
    "include/UI/PauseMenu.h"
    "src/UI/TextTagSystem.cpp"
    "include/UI/TextTagSystem.h"
)

include_directories("include" "include/Components" "include/Entity" "include/States" "include/UI")
add_executable(SFML-Finding-Game ${SRC})

# Static Runtime
if(WIN32 AND MSVC AND ${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.15.0")
	set_property(TARGET SFML-Finding-Game PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
endif()

target_link_libraries(SFML-Finding-Game sfml-graphics sfml-audio)

install(TARGETS SFML-Finding-Game DESTINATION .)
install(DIRECTORY shaders DESTINATION .)
install(DIRECTORY res DESTINATION .)