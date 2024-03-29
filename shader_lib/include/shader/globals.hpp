/*
 *   Copyright (c) 2021 Mateusz Stadnik

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "vec4.hpp"

extern "C"
{
    constexpr int shader_in_arguments_size  = 5;
    constexpr int shader_out_arguments_size = 5;
    extern void **in_argument[shader_in_arguments_size];
    extern void **out_argument[shader_out_arguments_size];

    extern vec4 gl_Position;

} // extern "C"