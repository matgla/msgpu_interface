# This file is part of msgpu_interface project.
# Copyright (C) 2021 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.10)

project (msgpu_interface CXX)

find_package (Python3 COMPONENTS Interpreter) 

include(FetchContent)

FetchContent_Declare(
  mspkg
  GIT_REPOSITORY https://github.com/matgla/mspkg.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(mspkg)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${mspkg_SOURCE_DIR}/cmake)
include (mspkg)

setup_mspkg(${mspkg_SOURCE_DIR})

find_program (virtualenv_exec virtualenv)

if (NOT virtualenv_exec)
    message (FATAL_ERROR "Can't find virtualenv")
endif ()

set (generator_venv ${CMAKE_CURRENT_BINARY_DIR}/venv)

file (GLOB virtualenv_file_stamp ${CMAKE_CURRENT_BINARY_DIR}/venv.stamp)

if (NOT virtualenv_file_stamp)
    message ("Configure virtualenv: ${generator_venv}")

    execute_process(
        COMMAND ${virtualenv_exec} -p python3 venv 
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND_ERROR_IS_FATAL ANY 
    )

    if (EXISTS ${generator_venv}/bin/pip)
        set (pip_exec ${generator_venv}/bin/pip) 
    elseif (EXISTS ${generator_venv}/Scripts/pip.exe)
        set (pip_exec ${generator_venv}/Scripts/pip.exe) 
    else ()
        message (FATAL_ERROR "Can't find pip under: ${generator_venv}")
    endif ()

    if(EXISTS ${generator_venv}/bin/python)
        set (python_exec ${generator_venv}/bin/python) 
    elseif (EXISTS ${generator_venv}/Scripts/python.exe)
        set (python_exec ${generator_venv}/Scripts/python.exe) 
    else ()
        message (FATAL_ERROR "Can't find python under: ${generator_venv}")
    endif ()

    execute_process(
        COMMAND ${pip_exec} install -r ${CMAKE_CURRENT_SOURCE_DIR}/message_generator/requirements.txt --upgrade -q -q -q 
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND_ECHO STDOUT
        COMMAND_ERROR_IS_FATAL ANY 
    )

    execute_process(
        COMMAND cmake -E touch ${CMAKE_CURRENT_BINARY_DIR}/venv.stamp 
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND_ECHO STDOUT
        COMMAND_ERROR_IS_FATAL ANY 
    )

endif ()

if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/interface_generated OR DEFINED ENV{REGENERATE_INTERFACE})
    execute_process( 
        COMMAND ${python_exec} ${CMAKE_CURRENT_SOURCE_DIR}/message_generator/generate.py 
        --input ${CMAKE_CURRENT_SOURCE_DIR}/definitions
        --enable-cpp 
        --enable-python
        --output-dir ${PROJECT_BINARY_DIR}/messages
        COMMAND_ECHO STDOUT 
        COMMAND_ERROR_IS_FATAL ANY
    )

    file(TOUCH ${CMAKE_CURRENT_BINARY_DIR}/interface_generated)
endif ()
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/message_generator/generate.py)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/message_generator/cpp_generator.py)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/message_generator/cpp_header_generator.py)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/message_generator/cpp_utils.py)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/message_generator/generator_base.py)
set_property (DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/message_generator/python_generator.py)

add_subdirectory(${PROJECT_BINARY_DIR}/messages/cpp ${PROJECT_BINARY_DIR}/messages/cmake)

add_subdirectory(shader_lib)