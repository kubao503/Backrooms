#ifndef TIMER_5324532_H
#define TIMER_5324532_H

#include <chrono>   // for std::chrono functions
#include <iostream> // for printing results

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using clock_type = std::chrono::steady_clock;
    using second_type = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_type> m_beg{clock_type::now()};

public:
    void reset()
    {
        m_beg = clock_type::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
    }

    void start()
    {
        reset();
    }
    void stop()
    {
        static int counter{0};
        static double measuredTime{0.0};
        ++counter;
        measuredTime += elapsed();
        if (counter % 10000 == 0)
        {
            std::cerr << "fps :" << counter / measuredTime / 100.0 << '\n';
        }
    }
};

#endif
