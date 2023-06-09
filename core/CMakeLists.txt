cmake_minimum_required(VERSION 3.1.0)

# Set the dll/lib filename
set(Utilities_filename "Utilities")

# Set the include folder. Relative to this file path
set(IncludePath "include")
 
# Macro to search for files with given file ending.
# call:
#   FILE_DIRECTORIES(H_FILES *.h)
#
# all *.h files will be saved in the H_FILES variable
MACRO(FILE_DIRECTORIES return_list ending)
    FILE(GLOB_RECURSE new_list ${ending})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

# Get all source files
FILE_DIRECTORIES(H_FILES *.h)
FILE_DIRECTORIES(CPP_FILES *.cpp)

# Combine headers and cources
set(SOURCES
    ${CPP_FILES}
    ${H_FILES}
)

# Print files which are contained in the library
message("Create library with files:")
FOREACH(file ${SOURCES})
    message("  File: " ${file})
ENDFOREACH()


# Create the library, one for shared (dll+lib) and one static (lib)
add_library(Utilities_shared SHARED ${SOURCES})
add_library(Utilities_static STATIC ${SOURCES})

# Set preprocessor definitions which are used in code to switch between the dllExport ...
target_compile_definitions(Utilities_shared PRIVATE  UTILITIES_LIB)
target_compile_definitions(Utilities_static PRIVATE  BUILD_STATIC UTILITIES_LIB)

# Set the compiler properties and output file name
set_target_properties(Utilities_shared PROPERTIES LINKER_LANGUAGE CXX  OUTPUT_NAME "${Utilities_filename}" DEBUG_POSTFIX "-d" )
set_target_properties(Utilities_static PROPERTIES LINKER_LANGUAGE CXX  OUTPUT_NAME "${Utilities_filename}-s" DEBUG_POSTFIX "-d")

# Add the include path to the library
target_include_directories(Utilities_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${IncludePath}>)
target_include_directories(Utilities_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${IncludePath}>)

# Define the install path
install(TARGETS Utilities_shared DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_INSTALL_FOLDER}")
install(TARGETS Utilities_static DESTINATION "${CMAKE_INSTALL_PREFIX}/${RELATIVE_INSTALL_FOLDER}")

#target_link_libraries(Utilities_shared ${SFML_EditorWidget_dependencies})
#target_link_libraries(Utilities_static ${SFML_EditorWidget_dependencies})
