This project demonstrates the steps needed to add a Gradle module that exposes a C++ library to be consumed by an application module.

1) Create the original 'app' project with File->New->New Project->Native C++.
2) Add a second module 'lib' with File->New->New Module->Android Library.
3) Create a new file lib/src/main/cpp/CMakeLists.txt:
    ```
    project("other-lib")
    add_library(${CMAKE_PROJECT_NAME} STATIC other-lib.cpp)
    target_link_libraries(${CMAKE_PROJECT_NAME})
    ```
4)  Create a new file lib/src/main/cpp/other-lib.cpp:
    ```
    const char * otherLibFunction() {
        return "Hello from other lib";
    }
    ```
5) Create a new file lib/src/main/cpp/include/other-lib.h:
    ```
    #ifndef MY_APPLICATION_OTHER_LIB_H
    #define MY_APPLICATION_OTHER_LIB_H
    const char * otherLibFunction();
    #endif
    ```
6) Modify app/src/main/cpp/native-lib.cpp to consume the header:
    ```
    ...
    #include "other-lib.h"
    ...
        std::string hello = otherLibFunction();
        return env->NewStringUTF(hello.c_str());
    }
    ...
    ```
7) Modify lib/build.gradle.kts to build export the library:
    ```
    android {
        ...
        externalNativeBuild {
            cmake {
                path = file("src/main/cpp/CMakeLists.txt")
                version = "3.22.1"
            }
        }
        buildFeatures {
            prefabPublishing = true
        }
        prefab {
            create("other-lib") {
                libraryName = "libother-lib"
                headers = "src/main/cpp/include"
            }
        }
    }
    ```
8) Modify app/build.gradle.kts to consume the library:
    ```
    android {
        ...
        buildFeatures {
            prefab = true
        }
    }

    dependencies {
        implementation(project(":lib"))
        ...
    }
    ```
9) Modify app/src/main/cpp/CMakeLists.txt to reference the exported library:
    ```
    project("myapplication")
    ...
    find_package(lib REQUIRED CONFIG)
    ...
    target_link_libraries(${CMAKE_PROJECT_NAME}
            ...
            lib::other-lib)
    ```
