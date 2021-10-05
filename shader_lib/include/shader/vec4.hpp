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

#include "vec3.hpp"

extern "C"
{

    struct vec4
    {
        vec4() = default;
        vec4(const vec3 &v, float w_)
            : x(v.x)
            , y(v.y)
            , z(v.z)
            , w(w_)
        {
        }
        vec4(float x_, float y_, float z_, float w_)
            : x(x_)
            , y(y_)
            , z(z_)
            , w(w_)
        {
        }

        float x;
        float y;
        float z;
        float w;
    };

} // extern "C"
