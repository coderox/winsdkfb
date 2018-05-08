project(winsdkfb CXX)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/winsdkfb/winsdkfb.Shared"
    "${CMAKE_CURRENT_SOURCE_DIR}/winsdkfb/winsdkfb.Shared/Generated"
)

execute_process(COMMAND "codegen.cmd"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/winsdkfb/winsdkfb.Shared"
                RESULT_VARIABLE git_result
)

##########
# winsdkfb
file(GLOB WINSDKFB_COMMON_SOURCES 
    "winsdkfb/winsdkfb.Shared/*.h" 
    "winsdkfb/winsdkfb.Shared/*.cpp"
    "winsdkfb/winsdkfb.Shared/*.xaml"
    "winsdkfb/winsdkfb.Shared/Themes/*.xaml"
)

list(FILTER WINSDKFB_COMMON_SOURCES EXCLUDE REGEX ".xaml.*")
list(FILTER WINSDKFB_COMMON_SOURCES EXCLUDE REGEX "FacebookLoginButton.*")
list(FILTER WINSDKFB_COMMON_SOURCES EXCLUDE REGEX "PPNew.*")

file(GLOB WINSDKFB_CONTROL_SOURCES
    "winsdkfb/winsdkfb.Shared/*.xaml"
    "winsdkfb/winsdkfb.Shared/*.xaml.cpp"
    "winsdkfb/winsdkfb.Shared/*.xaml.h"
    "winsdkfb/winsdkfb.Shared/Controls/*.xaml"
    "winsdkfb/winsdkfb.Shared/Controls/*.xaml.cpp"
    "winsdkfb/winsdkfb.Shared/Controls/*.xaml.h"
    "winsdkfb/winsdkfb.Shared/FacebookLoginButton.cpp"
    "winsdkfb/winsdkfb.Shared/FacebookLoginButton.h"
)

file(GLOB WINSDKFB_THEME_SOURCES
    "winsdkfb/winsdkfb.Shared/Themes/*.xaml"
)

file(GLOB WINSDKFB_GENERATED_SOURCES 
    "winsdkfb/winsdkfb.Shared/Generated/*.h" 
    "winsdkfb/winsdkfb.Shared/Generated/*.cpp"
)

file(GLOB WINSDKFB_APPEVENTS_SOURCES 
    "winsdkfb_uwp/winsdkfb_uwp/FBAppEvents/*.h" 
    "winsdkfb_uwp/winsdkfb_uwp/FBAppEvents/*.cpp"
)

file(GLOB WINSDKFB_CONTENT_SOURCES 
    "winsdkfb/winsdkfb.Shared/Images/*.png" 
)
set_property(SOURCE ${WINSDKFB_CONTENT_SOURCES} PROPERTY VS_DEPLOYMENT_CONTENT 1)

message(STATUS ${WINSDKFB_APPEVENTS_SOURCES})

add_library(winsdkfb SHARED 
            ${WINSDKFB_COMMON_SOURCES} 
            ${WINSDKFB_CONTROL_SOURCES} 
            ${WINSDKFB_GENERATED_SOURCES} 
            ${WINSDKFB_THEME_SOURCES}
            ${WINSDKFB_APPEVENTS_SOURCES}
            ${WINSDKFB_CONTENT_SOURCES}
)

source_group("Controls" FILES ${WINSDKFB_CONTROL_SOURCES})
source_group("Themes" FILES ${WINSDKFB_THEME_SOURCES})
source_group("Generated" FILES ${WINSDKFB_GENERATED_SOURCES})
source_group("Content" FILES ${WINSDKFB_CONTENT_SOURCES})

set_property(TARGET winsdkfb PROPERTY VS_WINRT_COMPONENT TRUE)
set_property(TARGET winsdkfb PROPERTY VS_GLOBAL_ROOTNAMESPACE winsdkfb)

set_target_properties(winsdkfb PROPERTIES COMPILE_FLAGS "/Yupch.h")
set_source_files_properties(winsdkfb/winsdkfb.Shared/pch.cpp PROPERTIES COMPILE_FLAGS "/Ycpch.h")
