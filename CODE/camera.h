#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
    public:
        // 相机坐标参数
        camera(
            vec3 lookfrom, vec3 lookat, vec3 vup,
            double vfov, // top to bottom, in degrees
            double aspect, double aperture, double focus_dist
        ) {
            origin = lookfrom;
            lens_radius = aperture / 2;

            auto theta = degrees_to_radians(vfov);
            auto half_height = tan(theta/2);
            auto half_width = aspect * half_height;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);
            lower_left_corner = origin
                              - half_width * focus_dist * u
                              - half_height * focus_dist * v
                              - focus_dist * w;

            horizontal = 2*half_width*focus_dist*u;
            vertical = 2*half_height*focus_dist*v;
        }
        camera(vec3 lookfrom,vec3 lookat, vec3 vup,double vfov,double aspect){
            origin = lookfrom;
            vec3 u,v,w;
            auto theta = degrees_to_radians(vfov);
            auto half_height = tan(theta/2);
            auto half_width = aspect * half_height;
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            lower_left_corner = origin - half_width*u - half_height*v - w;

            horizontal = 2*half_width*u;
            vertical = 2*half_height*v;
        }


        camera(double vfov, double aspect) {
            origin = vec3(0,0,0);
            auto theta = degrees_to_radians(vfov);
            auto half_height = tan(theta/2);
            auto half_width = aspect * half_height;

            lower_left_corner = vec3(-half_width,-half_height,-1.0);

            horizontal = vec3(2*half_width,0,0);
            vertical = vec3(0,2*half_height,0);
        }


        camera(){
            lower_left_corner = vec3(-2.0,-1.0,-1.0);
            horizontal = vec3(4.0,0.0,0.0);
            vertical = vec3(0.0,2.0,0.0);
            origin = vec3(0.0,0.0,0.0);
        }
        // 获取摄像机上某个点的光线
        ray get_ray(double s, double t) {
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();

            return ray(
                origin + offset,
                lower_left_corner + s*horizontal + t*vertical - origin - offset
           );
        }

    public:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u,v,w;
        double lens_radius;
};


#endif