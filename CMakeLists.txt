cmake_minimum_required(VERSION 3.22)
project(uni_mobil_p)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

include(CPM.cmake)

############ CPM ############

CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG 10.1.1
)

CPMAddPackage(
        NAME gsl
        GITHUB_REPOSITORY microsoft/GSL
        GIT_TAG v4.0.0
)

CPMAddPackage(
        NAME oatpp
        GITHUB_REPOSITORY oatpp/oatpp
        GIT_TAG 1.3.0
)

CPMAddPackage(
        NAME oatpp-swagger
        GITHUB_REPOSITORY oatpp/oatpp-swagger
        GIT_TAG 1.3.0
        OPTIONS
        "OATPP_MODULES_LOCATION CUSTOM"
        "OATPP_DIR_SRC ${oatpp_SOURCE_DIR}"
)

CPMAddPackage(
        NAME oatpp-postgresql
        GITHUB_REPOSITORY oatpp/oatpp-postgresql
        GIT_TAG 1.3.0
        OPTIONS
        "OATPP_MODULES_LOCATION CUSTOM"
        "OATPP_DIR_SRC ${oatpp_SOURCE_DIR}"
        "OATPP_BUILD_TESTS OFF"

)

find_package(fmt REQUIRED)
find_package(gsl REQUIRED)

link_libraries(fmt::fmt)
include_directories(${fmt_INCLUDE_DIRS})
include_directories(${gsl_SOURCE_DIR}/include)

############# OATPP ###############

add_library(uni_mobil_p-lib
        src/AppComponent.hpp
        src/controller/MobilController.hpp
        src/dto/DtoError.hpp
        src/enum/EnumErrorType.hpp
        src/db/MobilDatabase.hpp
        src/service/MobilService.hpp
        src/service/MobilService.cpp
        src/dto/DtoPlace_OUT.hpp
        src/dto/DtoUser_OUT.hpp
        src/dto/DtoVisit_OUT.hpp
        src/dto/DtoComment_OUT.hpp
        src/dto/DtoComment_IN.hpp
        src/dto/DtoPlace_IN.hpp
        src/dto/DtoUser_IN.hpp
        src/dto/DtoRegister_IN.hpp
        src/dto/DtoAdminVisit_IN.hpp
        src/dto/DtoAdminComment_IN.hpp
        src/dto/DtoAuth_DB.hpp
)

find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-swagger 1.3.0 REQUIRED)
find_package(oatpp-postgresql 1.3.0 REQUIRED)

target_link_libraries(uni_mobil_p-lib
        PUBLIC oatpp
        PUBLIC oatpp-swagger
        PUBLIC oatpp-postgresql
        PUBLIC oatpp-test
)

target_include_directories(uni_mobil_p-lib PUBLIC src)

## add executables

add_executable(uni_mobil_p-exe
        src/App.cpp
        )
target_link_libraries(uni_mobil_p-exe
        uni_mobil_p-lib
)
add_dependencies(uni_mobil_p-exe uni_mobil_p-lib)

add_executable(uni_mobil_p-test
        test/tests.cpp
)

target_link_libraries(uni_mobil_p-test uni_mobil_p-lib)
add_dependencies(uni_mobil_p-test uni_mobil_p-lib)

set_target_properties(uni_mobil_p-lib uni_mobil_p-exe uni_mobil_p-test PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(uni_mobil_p-lib INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

add_definitions(
        ## define path to swagger-ui static resources folder
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_SOURCE_DIR}/res"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"

        ## TODO: USE THIS TO SET THE CONNECTION STRING
        -DPG_CONNECTION_STRING="host=localhost port=5432 dbname=mobil_db user=Supervisor password=Supervisor"

        ## TODO: USE THIS TO SET URI OF THE SERVER
        -DSERVER_URI="http://localhost:8000"
)

################ TESTS #################

enable_testing()
add_test(project-tests uni_mobil_p-test)

################ WARNINGS ###############

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(uni_mobil_p-exe INTERFACE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
    target_compile_options(uni_mobil_p-lib INTERFACE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
    target_compile_options(uni_mobil_p-test INTERFACE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
    if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
        target_compile_options(uni_mobil_p-exe INTERFACE -g -O0)
        target_compile_options(uni_mobil_p-lib INTERFACE -g -O0)
        target_compile_options(uni_mobil_p-test INTERFACE -g -O0)
    elseif (CMAKE_BUILD_TYPE EQUAL "RELEASE")
        target_compile_options(uni_mobil_p-exe INTERFACE -O3)
        target_compile_options(uni_mobil_p-lib INTERFACE -O3)
        target_compile_options(uni_mobil_p-test INTERFACE -O3)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(uni_mobil_p-exe INTERFACE /W4 /w14640 /permissive-)
    target_compile_options(uni_mobil_p-lib INTERFACE /W4 /w14640 /permissive-)
    target_compile_options(uni_mobil_p-test INTERFACE /W4 /w14640 /permissive-)
    if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
        target_compile_options(uni_mobil_p-exe INTERFACE /Zi)
        target_compile_options(uni_mobil_p-lib INTERFACE /Zi)
        target_compile_options(uni_mobil_p-test INTERFACE /Zi)
    elseif (CMAKE_BUILD_TYPE EQUAL "RELEASE")
        target_compile_options(uni_mobil_p-exe INTERFACE /O2)
        target_compile_options(uni_mobil_p-lib INTERFACE /O2)
        target_compile_options(uni_mobil_p-test INTERFACE /O2)
    endif ()
endif()
