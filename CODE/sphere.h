#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable {
    public:
        sphere(){}
        sphere(vec3 cen, double r):center(cen),radius(r){};
        sphere(vec3 cen, double r,shared_ptr<material> m):
            center(cen), radius(r), mat_ptr(m){};

        virtual bool hit(const ray& r, double t_min, double tmax, hit_record& rec) const;

    public:
        vec3 center;
        double radius;
        shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // 光线起点到圆心的向量
    vec3 oc = r.origin() - center;
    // 二次方程参数
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b * half_b - a*c;

    // 求根公式delta判别
    // 如果ray与sphere有两个交点
    if(discriminant>0){
        // 求出近的交点距离
        auto root = sqrt(discriminant);
        auto temp = (-half_b - root)/a;
        // 如果交点距离在范围以内
        if(temp<t_max&&temp>t_min){
            // 记录这个交点距离
            rec.t = temp;
            // 求出交点
            rec.p = r.at(rec.t);
            // 法线单位向量
            rec.normal = (rec.p - center) / radius;
            // 外法线方向
            vec3 outward_normal = (rec.p - center) / radius;
            // 保证法线和光线相反
            rec.set_face_normal(r,outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        // 假设光线穿过小球，计算远端交点
        temp = (-half_b+root) / a;
        if(temp < t_max && temp > t_min){
            rec.t = temp;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center)/radius;
                        // 外法线方向
            vec3 outward_normal = (rec.p - center) / radius;
            // 保证法线和光线相反
            rec.set_face_normal(r,outward_normal);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    // 如果距离不在追踪范围内
    return false;
}

#endif