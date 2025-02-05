#include <iostream>
#include "vec3.h"


int main()
{
    const int image_width = 800;
    const int image_height = 800;

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush << std::endl;
        for (int i = 0; i < image_width; ++i)
        {
            vec3 color(double(i)/image_width,double(j)/image_height,0.2);
            color.write_color(std::cout);
        }
    }
    std::cerr << "\nDone.\n";
}