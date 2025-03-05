/*
 * This file is part of hipSYCL, a SYCL implementation based on CUDA/HIP
 *
 * Copyright (c) 2018 Aksel Alpay
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BRUTEFORCE_NBODY_HPP
#define BRUTEFORCE_NBODY_HPP

#include <cmath>
#include <cstdlib>
//#include <sycl/sycl.hpp>
#include <vector>

using arithmetic_type = float;

struct vector_type {
    arithmetic_type x, y, z;
};

struct particle_type {
    arithmetic_type x, y, z, w;

    arithmetic_type& getX() { return x; }
    arithmetic_type& getY() { return y; }
    arithmetic_type& getZ() { return z; }
    arithmetic_type& getW() { return w; }

    const arithmetic_type& getX() const { return x; }
    const arithmetic_type& getY() const { return y; }
    const arithmetic_type& getZ() const { return z; }
    const arithmetic_type& getW() const { return w; }
};

constexpr arithmetic_type total_mass = 100000.f;
constexpr std::size_t num_particles = 40000;
constexpr std::size_t num_timesteps = 400;
constexpr std::size_t local_size = 12800;
constexpr arithmetic_type gravitational_softening = 1.e-4f;
constexpr arithmetic_type dt = 0.1f;
constexpr arithmetic_type cube_size = 400.0f;
constexpr arithmetic_type half_cube_size = 0.5f * cube_size;

#endif // BRUTEFORCE_NBODY_HPP
