file(GLOB BLD_SRC *.cpp)

add_library(BugLoggerDrv SHARED ${BLD_SRC})
target_link_libraries(BugLoggerDrv VBXIDrvSDK)