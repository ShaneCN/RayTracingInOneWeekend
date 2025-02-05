#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <iostream>

vec3 ray_color(const ray& r, const hittable& world){
    hit_record rec;
    std::cout<<"in ray color!"<<std::endl;
    // 这束光线发生碰撞
    if(world.hit(r,0,infinity,rec)){
        std::cout<<"hited!"<<std::endl;
        return 0.5*(rec.normal+vec3(1,1,1));
    }
    // 如果没有
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
}
int main()
{
    const int image_width = 200;
    const int image_height = 100;
    const int samples_per_pixel = 100;
    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";
    hittable_list world;
    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));
    camera cam;
    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            vec3 color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                // 生成一个随机数，
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world);
            }
            color.write_color(std::cout, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}