#ifndef STAT_UTIL
#define STAT_UTIL
// #include <thread>
// #include <fstream>
// #include <iostream>
// #include <sstream>
#include <chrono>
#include <ctime>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <numeric>
// #include <queue>
// #include <mutex>
// #include "M_Image.h"
// #include <atomic>
// #include <map>

class Stat_Util
{
public:
    template<typename F>
    static auto timefunc(F incomingFunct)
    {
        auto start = std::chrono::steady_clock::now();
        incomingFunct();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        return elapsed_seconds.count();
    }

    Stat_Util()
    {

    }
};

#endif