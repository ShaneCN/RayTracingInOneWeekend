#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class material
{
private:
    /* data */
public:
    virtual bool scatter(
        const ray& r_in,const hit_record& rec,
        vec3& attenuation,ray& scatterd
    ) const = 0;
};

class lambertian : public material {
    public:
        lambertian(const vec3& a): albedo(a) {}
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, 
            vec3& attenuation, ray& scattered) const {
                vec3 scatter_direction = rec.normal + random_unit_vector();
                scattered = ray(rec.p,scatter_direction);
                attenuation = albedo;
                return true;
            }
    public:
        vec3 albedo;
};

class metal:public material {
    public:
        metal(const vec3& a):albedo(a) {}
        metal(const vec3& a, double f):albedo(a),fuzz(f<1?f:1){}
        virtual bool scatter(const ray& r_in,const hit_record& rec,
                             vec3& attenuation, ray& scattered)const{
            vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
            scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
//            scattered = ray(rec.p,reflected);
            attenuation = albedo;
            return (dot(scattered.direction(),rec.normal)>0);
        }
        vec3 albedo;
        double fuzz;
};

double schlick(double cosine, double ref_idx) {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

class dielectric:public material{
    public:
        dielectric(double ri):ref_idx(ri) {}


        // r_in 入射光线, rec 碰撞记录, attenuation 衰减系数, scattered 折射后光线方向
        virtual bool scatter(const ray& r_in,const hit_record& rec, vec3& attenuation, ray& scattered) const {
            attenuation = vec3(1.0,1.0,1.0);
            double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

            vec3 unit_direction = unit_vector(r_in.direction());
            double cos_theta = ffmin(dot(-unit_direction,rec.normal),1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
            if(etai_over_etat * sin_theta > 1.0){
                vec3 reflected = reflect(unit_direction, rec.normal);
                scattered = ray(rec.p, reflected);
                return true;
            }
            double reflect_prob = schlick(cos_theta,etai_over_etat);
            if(random_double()<reflect_prob){
                vec3 reflected = reflect(unit_direction, rec.normal);
                scattered = ray(rec.p, reflected);
                return true;
            }
            vec3 refracted = refract(unit_direction,rec.normal,etai_over_etat);
            scattered = ray(rec.p,refracted);
            return true;
        }
        double ref_idx;
};



#endif