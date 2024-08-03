#define _USE_MATH_DEFINES
#include <math.h>

namespace Math {
    inline float RadToAng(float Rad) {
        return (float)(Rad * (180.0 / M_PI));
    }

    inline float AngToRad(float Rad) {
        return (float)(Rad / (180.0 * M_PI));
    }
}
