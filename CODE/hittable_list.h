#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;
class hittable_list:public hittable{
    public:
        hittable_list(){}
        hittable_list(shared_ptr<hittable_list> object){add(object);}
        
        // 清空对象
        void clear(){objects.clear();}
        // 增长对象列表
        void add(shared_ptr<hittable> object){objects.push_back(object);}
        // 是否有碰撞
        virtual bool hit(const ray& r,double t_min,double tmax,hit_record& rec) const;

    public:
        // 对象列表
        std::vector<shared_ptr<hittable>> objects;
};

// 是否有碰撞 r为光线，t_min 为最小追踪时间，t_max 为最长追踪时间，rec是碰撞记录
bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // 创建一个 hit记录
    hit_record temp_rec;
    // 记录是否碰撞
    bool hit_anything = false;
    auto closest_so_far = t_max;

    // 遍历所有对象
    for(const auto& object : objects){
        // 如果有对象和这个光线发生碰撞
        if(object->hit(r,t_min,closest_so_far,temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif

