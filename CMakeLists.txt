cmake_minimum_required(VERSION 3.10)

project(cpp_indie_studio)


#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
					-std=c++14 \
					-W -Wextra -g\
					-I irrlicht \
					-I sources/Object \
					-I sources/MyAudio \
					-I sources/MyEvent \
					-I sources/MainMenu \
					-I sources/Exception \
					-I sources/MapHandler \
					-I sources/InitDevice \
					-I sources/GameHandler \
					-I sources/BombermanCore \
					-I sources/Menu/ \
					")

include_directories(irrlicht)

set(SRC
    sources/main.cpp
	sources/BombermanCore/BombermanCore.cpp
	sources/Exception/Exception.cpp
	sources/Exception/ExceptionMenu.cpp
	sources/Exception/ExceptionMap.cpp
	sources/Exception/ExceptionIndie.cpp
	sources/Exception/ExceptionPlayer.cpp
	sources/Exception/ExceptionObject.cpp
	sources/GameHandler/GameHandler.cpp
	sources/InitDevice/initDevice.cpp
	sources/MyEvent/MyEvent.cpp
	sources/MyAudio/MyAudio.cpp
	sources/Menu/AMenu.cpp
	sources/Menu/MainMenu/MainMenu.cpp
	sources/Menu/MainMenu/EndMenu.cpp
	sources/MapHandler/MapHandler.cpp
	sources/Object/Object.cpp
	sources/Object/Floor/Floor.cpp
	sources/Object/Wall/Wall.cpp
	sources/Object/Bomb/Bomb.cpp
	sources/Object/Fire/Fire.cpp
	sources/Object/Box/Box.cpp
	sources/Object/Player/Player.cpp
	sources/Object/PowerUp/PowerUp.cpp
    irrlicht/irrlicht.h
	)

add_executable(bomberman ${SRC})
target_link_libraries(bomberman Irrlicht GL X11 Xxf86vm
        sfml-audio)