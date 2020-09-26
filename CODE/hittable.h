#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class material;

struct hit_record
{
    /* data */
    // 交点
    vec3 p;
    // 法线
    vec3 normal;

    shared_ptr<material> mat_ptr;

    // 交点距离离起点距离
    double t;
    // 是否是外部入射
    bool front_face;
    // 设置此次反射的法线
    inline void set_face_normal(const ray& r, const vec3& outward_normal){
        // 是否外部入射
        front_face = dot(r.direction(),outward_normal) < 0;
        // 如果是，不变；不是，取反方向
        normal = front_face?outward_normal:-outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif