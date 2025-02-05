#include "ray.h"
#include <iostream>


/* 
 * 这个方程用射线（光线）和球的交点数量来求一条光线是否和球体相交
 * 如果相交，b*b - 4a*c会是一个大于0的数
 */
double hit_sphere(const vec3& center, double radius, const ray&r) {
    // light source to circle center ray
    vec3 oc = r.origin() - center;
    auto a = dot(r.dir,r.dir);
    auto half_b = dot(oc,r.dir);
    auto c = dot(oc,oc) + -1 * (radius * radius);
    auto discriminant = half_b*half_b - a*c;
    if(discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

vec3 ray_color(const ray& r){
    auto t = hit_sphere(vec3(0,0,-1),0.5,r);
    if(t > 0){
        vec3 N = unit_vector(r.at(t)-vec3(0,0,-1));
        return 0.5*vec3(N.x()+1,N.y()+1,N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.dir);
    t = 0.5*(unit_direction.y()+1);
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
}

int main(){
    const int image_width = 800;
    const int image_height = 400;

    std::cout<<"P3\n" << image_width<< " "<< image_height<< "\n255\n";
    vec3 lower_left_corner(-2.0,-1.0,-1.0);
    vec3 horizontal(4,0,0);
    vec3 vertical(0,2,0);
    vec3 origin(0,0,0);
    for (int j = image_height - 1; j>=0;--j){
        std::cerr << "\rScanlines remaining: " <<j<< ' ' << std::flush;
        for(int i = 0;i<image_width;++i){
            auto u=double(i) / image_width;
            auto v=double(j) / image_height;
            ray r(origin, lower_left_corner+u*horizontal+v*vertical);
            vec3 color = ray_color(r);
            color.write_color(std::cout);
        }
    }
    std::cerr << "\nDone.\n";
}