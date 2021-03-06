CMAKE_MINIMUM_REQUIRED (VERSION 3.13)

SET (CMAKE_CXX_STANDARD 17)

PROJECT (yunikEngine)

SET (YUNIKENGINE_BUILD_TARGET_SHARED "yunikEngine_shared")
SET (YUNIKENGINE_BUILD_TARGET_STATIC "yunikEngine_static")

OPTION (YUNIKENGINE_BUILD_SHARED "Build the shared library" OFF)
OPTION (YUNIKENGINE_BUILD_STATIC "Build the static library" ON)
OPTION (YUNIKENGINE_BUILD_TEST "Build the test example" OFF)

SET (YUNIKENGINE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/include)

ADD_SUBDIRECTORY (${CMAKE_SOURCE_DIR}/lib)
ADD_SUBDIRECTORY (${CMAKE_SOURCE_DIR}/src)

IF (YUNIKENGINE_BUILD_TEST)
    ADD_SUBDIRECTORY (${CMAKE_SOURCE_DIR}/test)
ENDIF ()

# CPack settings
IF (YUNIKENGINE_BUILD_SHARED)
    INSTALL (
        TARGETS ${YUNIKENGINE_BUILD_TARGET_SHARED}
        DESTINATION "bin"
    )
ENDIF ()

IF (YUNIKENGINE_BUILD_STATIC)
    INSTALL (
        TARGETS ${YUNIKENGINE_BUILD_TARGET_STATIC}
        DESTINATION "bin"
    )
ENDIF ()

INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/yunikEngine
    DESTINATION "include"
)

SET (CPACK_GENERATOR "ZIP")
SET (CPACK_PACKAGE_VERSION "0.1.0")

INCLUDE (CPack)
