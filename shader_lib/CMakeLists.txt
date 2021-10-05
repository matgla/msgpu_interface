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

add_library(msgpu_interface_shader)
add_library(msgpu::interface::shader ALIAS msgpu_interface_shader)


set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include/shader)

target_sources(msgpu_interface_shader
    PUBLIC 
        ${include_dir}/shader.hpp
        ${include_dir}/vec3.hpp
        ${include_dir}/vec4.hpp
        ${include_dir}/globals.hpp
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/vec3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vec4.cpp
)

target_include_directories(msgpu_interface_shader
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(msgpu_interface_shader PUBLIC -include ${include_dir}/shader.hpp)
