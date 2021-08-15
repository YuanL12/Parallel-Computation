#include <iostream>

// Fast Inverse Square Root from Quake III Arena
float Q_rsqrt(float number){
    long i; 
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = * ( long * ) &y;                        // evil floating point bit hack
    i = 0x5f3759df - ( i >> 1);                 // what the fuck?
    y = * ( float * ) &i;
    y = y * (threehalfs - ( x2 * y * y ) );     // 1st iteration
    // y = y * (threehalfs - ( x2 * y * y ) );  // 2nd iteration, can be removed
    return y;
}

int main()
{

    std::cout << Q_rsqrt(2) << std::endl;
    return 0;
}