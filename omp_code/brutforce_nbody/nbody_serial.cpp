#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "bruteforce_nbody_serial.hpp"
#include "model_serial.hpp"

arithmetic_type mirror_position(const arithmetic_type mirror_pos, const arithmetic_type position)
{
    arithmetic_type delta = std::fabs(mirror_pos - position);
    return (position <= mirror_pos) ? mirror_pos + delta : mirror_pos - delta;
}

int get_num_iterations_per_output_step()
{
    char* val = std::getenv("NBODY_ITERATIONS_PER_OUTPUT");
    if (!val)
        return 1;
    return std::stoi(val);
}

int main()
{
    const int iterations_per_output = get_num_iterations_per_output_step();

    std::vector<particle_type> particles;
    std::vector<vector_type> velocities;

    arithmetic_type particle_mass = total_mass / num_particles;

    random_particle_cloud particle_distribution0{
        vector_type{0.0f, 100.0f, 0.0f},
        vector_type{10.0f, 15.0f, 11.0f},
        particle_mass, 0.1f * particle_mass,
        vector_type{0.0f, -26.0f, 5.0f},
        vector_type{5.0f, 20.0f, 12.0f}
    };

    random_particle_cloud particle_distribution1{
        vector_type{50.0f, 5.0f, 0.0f},
        vector_type{17.0f, 7.0f, 5.0f},
        particle_mass, 0.1f * particle_mass,
        vector_type{-5.0f, 20.0f, 1.0f},
        vector_type{18.0f, 11.0f, 8.0f}
    };

    random_particle_cloud particle_distribution2{
        vector_type{-50.0f, -100.0f, 0.0f},
        vector_type{10.0f, 10.0f, 14.0f},
        particle_mass, 0.1f * particle_mass,
        vector_type{5.0f, 5.0f, -1.0f},
        vector_type{10.0f, 6.0f, 5.0f}
    };

    particle_distribution0.sample(0.2 * num_particles, particles, velocities);

    std::vector<particle_type> particles_cloud1, particles_cloud2;
    std::vector<vector_type> velocities_cloud1, velocities_cloud2;
    particle_distribution1.sample(0.4 * num_particles, particles_cloud1, velocities_cloud1);
    particle_distribution2.sample(0.4 * num_particles, particles_cloud2, velocities_cloud2);

    particles.insert(particles.end(), particles_cloud1.begin(), particles_cloud1.end());
    particles.insert(particles.end(), particles_cloud2.begin(), particles_cloud2.end());
    velocities.insert(velocities.end(), velocities_cloud1.begin(), velocities_cloud1.end());
    velocities.insert(velocities.end(), velocities_cloud2.begin(), velocities_cloud2.end());

    std::ofstream outputfile{"output.txt"};
    for (std::size_t t = 0; t < num_timesteps; ++t)
    {
        // Compute forces
        std::vector<vector_type> forces(particles.size(), vector_type{0.0f, 0.0f, 0.0f});
        for (std::size_t i = 0; i < particles.size(); ++i)
        {
            vector_type force{0.0f, 0.0f, 0.0f};
            const particle_type& my_particle = particles[i];

            for (std::size_t j = 0; j < particles.size(); ++j)
            {
                if (i != j)
                {
                    const particle_type& other_particle = particles[j];
                    vector_type R{
                        other_particle.getX() - my_particle.getX(),
                        other_particle.getY() - my_particle.getY(),
                        other_particle.getZ() - my_particle.getZ()
                    };

                    arithmetic_type r2 = R.x * R.x + R.y * R.y + R.z * R.z + gravitational_softening;
                    arithmetic_type r_inv = 1.0f / std::sqrt(r2);
                    arithmetic_type r_inv3 = r_inv * r_inv * r_inv;

                    force.x += other_particle.getW() * r_inv3 * R.x;
                    force.y += other_particle.getW() * r_inv3 * R.y;
                    force.z += other_particle.getW() * r_inv3 * R.z;
                }
            }

            forces[i] = force;
        }

        // Time integration
        for (std::size_t i = 0; i < particles.size(); ++i)
        {
            particle_type& p = particles[i];
            vector_type& v = velocities[i];
            const vector_type& acceleration = forces[i];

            // Update velocity and position
            v.x += acceleration.x * dt;
            v.y += acceleration.y * dt;
            v.z += acceleration.z * dt;

            p.getX() += v.x * dt;
            p.getY() += v.y * dt;
            p.getZ() += v.z * dt;

            // Reflect particle position and invert velocities
            if (p.getX() <= -half_cube_size)
            {
                v.x = std::fabs(v.x);
                p.getX() = mirror_position(-half_cube_size, p.getX());
            }
            else if (p.getX() >= half_cube_size)
            {
                v.x = -std::fabs(v.x);
                p.getX() = mirror_position(half_cube_size, p.getX());
            }

            if (p.getY() <= -half_cube_size)
            {
                v.y = std::fabs(v.y);
                p.getY() = mirror_position(-half_cube_size, p.getY());
            }
            else if (p.getY() >= half_cube_size)
            {
                v.y = -std::fabs(v.y);
                p.getY() = mirror_position(half_cube_size, p.getY());
            }

            if (p.getZ() <= -half_cube_size)
            {
                v.z = std::fabs(v.z);
                p.getZ() = mirror_position(-half_cube_size, p.getZ());
            }
            else if (p.getZ() >= half_cube_size)
            {
                v.z = -std::fabs(v.z);
                p.getZ() = mirror_position(half_cube_size, p.getZ());
            }
        }

        if (t % iterations_per_output == 0)
        {
            std::cout << "Writing output to output.txt file" << std::endl;
            for (std::size_t i = 0; i < particles.size(); ++i)
            {
                outputfile << particles[i].getX() << " "
                           << particles[i].getY() << " "
                           << particles[i].getZ() << " " << i << std::endl;
            }
        }
    }

    outputfile.close();
    return 0;
}

