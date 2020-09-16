cmake_minimum_required(VERSION 3.4.1) ##CMake최소버전 선택

#curl_path라는 변수에 미리 빌드된 라이브러리가 있는 경로를 할당한다.
set(curl_path ${CMAKE_SOURCE_DIR}/cpp/prebuilt/android/${ANDROID_ABI}/libcurl.a)
set(aes_path ${CMAKE_SOURCE_DIR}/cpp/aesTool)
#미리 빌드된 라이브러리를 사용하기 위해 curl라는 이름의 STATIC, IMPORTED로 설정된 라이브러리를 추가한다.
add_library(curl STATIC IMPORTED)
#이후, set_target_properties함수로 curl에 미리 빌드된 라이브러리의 경로를 할당한다.
set_target_properties(
        curl
        PROPERTIES IMPORTED_LOCATION
        ${curl_path}
)
#컴파일시간에 CMake가 헤더파일을 찾을수 있게 하기위해 헤더파일의 경로를 입력한다.
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/cpp/prebuilt/android/include/curl)

#필수...
find_library(log_lib log)
find_library(z_lib z)

#위에서 curl에대한 설정은 마쳤고 native-lib라는 라이브러리에 curl을 갖다 붙일것이다.
#test.cpp라는 curl을 활용하는 cpp파일을 생성하고 이를 native-lib이라는 라이브러리로 만든다.
add_library(
        native-lib
        SHARED
        cpp/test.cpp
)

##이건 뭔지 모름..
message(warning ${z_lib})
#마지막으로 curl과 log_lib, z_lib 을 native-lib에 붙이면 native-lib만 불러서 c/c++에 정의된 함수를 사용할 수 있다.
target_link_libraries(native-lib ${log_lib} curl ${z_lib})
#필수...
find_library(log_lib log)
find_library(z_lib z)

add_library( # Sets the name of the library.
        fooLib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${aes_path}/aes.h
        ${aes_path}/aes.c
        ${aes_path}/hex_utils.h
        ${aes_path}/hex_utils.c
        ${aes_path}/tools.h
        ${aes_path}/tools.cpp
        ${aes_path}/aes_utils.h
        ${aes_path}/aes_utils.c
        ${aes_path}/foo_tools.cpp
        )
target_link_libraries( # Specifies the target library.
        fooLib

        # included in the NDK.
        ${z_lib}
        ${log_lib})