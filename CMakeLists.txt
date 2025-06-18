# CMakeLists.txt: главный файл проекта PCManager
# Система мониторинга и управления ПК на C++ с Qt6
#
cmake_minimum_required(VERSION 3.16)
project(PCManager VERSION 1.0.0 LANGUAGES CXX)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка политик CMake
if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

# Автоматическая обработка Qt-специфичных файлов
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Поиск Qt6 через vcpkg
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Включаем директории заголовков
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Исходные файлы Core модуля
set(CORE_SOURCES
    src/core/app.cpp
    src/core/app.h
)

# Исходные файлы модулей мониторинга
set(MONITOR_SOURCES
    src/modules/system_monitor.cpp
    src/modules/system_monitor.h
    src/modules/cpu_monitor.cpp
    src/modules/cpu_monitor.h
    src/modules/ram_monitor.cpp
    src/modules/ram_monitor.h
    src/modules/gpu_monitor.cpp
    src/modules/gpu_monitor.h
    src/modules/disk_monitor.cpp
    src/modules/disk_monitor.h
    src/modules/process_monitor.cpp
    src/modules/process_monitor.h
)

# Исходные файлы GUI
set(GUI_SOURCES
    src/gui/main_window.cpp
    src/gui/main_window.h
    src/gui/dashboard_widget.cpp
    src/gui/dashboard_widget.h
)

# Главный файл приложения
set(MAIN_SOURCE
    src/main.cpp
)

# Все исходные файлы проекта
set(ALL_SOURCES
    ${MAIN_SOURCE}
    ${CORE_SOURCES}
    ${MONITOR_SOURCES}
    ${GUI_SOURCES}
)

# Создание исполняемого файла
qt_add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# Добавление ресурсов Qt
 qt_add_resources(${PROJECT_NAME} "app_resources"
     PREFIX "/"
     FILES resources/styles.qrc
 )

# Подключение Qt модулей
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core
    Qt6::Widgets
)

# Платформо-зависимые настройки
if(WIN32)
    # Windows-специфичные библиотеки
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        pdh      # Performance Data Helper для мониторинга
        psapi    # Process Status API
        kernel32
        user32
    )
    
    # Отключаем консольное окно в Release
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
    endif()
    
elseif(UNIX AND NOT APPLE)
    # Linux-специфичные настройки
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        pthread
        dl
    )
    
elseif(APPLE)
    # macOS-специфичные настройки
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE ON)
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        "-framework IOKit"
        "-framework CoreFoundation"
    )
endif()

# NVIDIA GPU мониторинг (опционально)
if(EXISTS "${CMAKE_SOURCE_DIR}/include/nvml.h")
    target_compile_definitions(${PROJECT_NAME} PRIVATE NVML_SUPPORT)
    if(WIN32)
        # Поиск NVIDIA ML библиотеки
        find_library(NVML_LIB nvml PATHS 
            "C:/Program Files/NVIDIA Corporation/NVSMI"
            "C:/Windows/System32"
        )
        if(NVML_LIB)
            target_link_libraries(${PROJECT_NAME} PRIVATE ${NVML_LIB})
        endif()
    endif()
endif()

# Настройки компилятора
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Debug/Release конфигурации
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE_BUILD)
endif()

# Тесты (опционально)
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Установка (опционально)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)