cmake_minimum_required(VERSION 3.0.0)
project(FepSNMPDriver VERSION 0.1.0)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BINARY_DIR ../../../OutPut/)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/pdb)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)

#if (MSVC)
#    set(CompilerFlags
#        CMAKE_CXX_FLAGS
#        CMAKE_CXX_FLAGS_DEBUG
#        CMAKE_CXX_FLAGS_RELEASE
#        CMAKE_C_FLAGS
#        CMAKE_C_FLAGS_DEBUG
#        CMAKE_C_FLAGS_RELEASE
#        )
#    foreach(CompilerFlag ${CompilerFlags})
#        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
#    endforeach()
#endif(MSVC)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
#set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

#Bring the headers into the project
include_directories(../../DevelopPack_win/include)
include_directories(../../DevelopPack_win/third-party)
include_directories(../../DevelopPack_win/third-party/00.OpcUaSdk/include)
include_directories(../../DevelopPack_win/third-party/00.OpcUaSdk/include/uabase)
include_directories(../../DevelopPack_win/third-party/00.OpcUaSdk/include/uastack)
include_directories(../../DevelopPack_win/third-party/00.OpcUaSdk/include/xmlparser)
include_directories(../../DevelopPack_win/third-party/00.OpcUaSdk/include/uaserver)
include_directories(../../DevelopPack_win/third-party/01.ACE_wrappers)
include_directories(../../DevelopPack_win/third-party/02.SQLite)
include_directories(../../DevelopPack_win/third-party/net-snmp)

#However, the file (GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./src/*.cpp")

add_definitions(-DFEPSNMPDRIVER_EXPORTS)

link_directories(../../DevelopPack_win/lib/x86/release)
link_libraries(ACE) 
link_libraries(uabase) 
link_libraries(uastack) 
link_libraries(Rpcrt4) 
link_libraries(ws2_32) 
link_libraries(DBCommon) 
link_libraries(Version) 
link_libraries(libeay32) 
link_libraries(crypt32) 
link_libraries(xmlparser) 
link_libraries(libxml2) 
link_libraries(DBScriptExecuter) 
link_libraries(DBDriverFrame) 
link_libraries(FEPPlatformClass) 
link_libraries(DBBaseClasses) 
link_libraries(IODrvBoard) 
link_libraries(hyserverredundancy) 

include(CTest)
enable_testing()

#Generate the shared library from the sources
add_library(FepSNMPDriver SHARED ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
