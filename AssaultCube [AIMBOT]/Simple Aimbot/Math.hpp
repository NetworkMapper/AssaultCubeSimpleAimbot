#define _USE_MATH_DEFINES
#include <math.h>

namespace Math {
    inline float RadToAng(float Rad) {
        return (Rad * (180.0 / M_PI)); // merci la cock i love da math
    }

    inline float AngToRad(float Rad) {
        return (Rad / (180.0 * M_PI)); // merci la cock i love da math
    }
}