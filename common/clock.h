#ifndef CLOCK_H_
#define CLOCK_H_

#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

class Clock {
private:
    typedef std::chrono::high_resolution_clock chrono_clock;
    typedef std::chrono::milliseconds milliseconds;

    chrono_clock::time_point first_time;
    chrono_clock::time_point time;
    milliseconds time_per_tick;
    int tick_count;
    // auto ms_int = duration_cast<milliseconds>(t2 - t1);
public:
    explicit Clock(unsigned int ms):
            first_time(chrono_clock::now()), time(first_time), time_per_tick(ms), tick_count(0) {}

    void resetnow() {
        first_time = chrono_clock::now();
        time = first_time;
    }

    void resetnext() {
        tick_count = 0;
        first_time = chrono_clock::now();
        time = first_time + time_per_tick;
    }

    void setnext() { time += time_per_tick; }


    int measure() {
        chrono_clock::time_point new_time = chrono_clock::now();
        auto ms_duration = std::chrono::duration_cast<milliseconds>(new_time - time);
        time = new_time;

        return ms_duration.count();
    }

    int tickcount() {
        return tick_count;
        //auto total_ticks = std::chrono::duration_cast<milliseconds>(time - first_time);
        //return (total_ticks / time_per_tick) - 1;
    }

    void tickRest() {
        chrono_clock::time_point new_time = chrono_clock::now();
        auto ahead_dur = std::chrono::duration_cast<milliseconds>(time - new_time);

        if (ahead_dur.count() > 0) {
            std::this_thread::sleep_for(ahead_dur);
            time += time_per_tick;
            tick_count++;
            
            // std::cout << "Ahead by " << ahead_dur.count() << "ms :" << tickcount() << " ticks\n";
        } else {
            // Simplificadamente
            milliseconds until_next = time_per_tick + ahead_dur % time_per_tick;
            std::this_thread::sleep_for(until_next);
            
            milliseconds lost = -ahead_dur + until_next; // Multiplo de time per stick
            
            time += lost;
            tick_count+= 1 + lost/time_per_tick;
            
        }
    }
    
    void tickNoRest() {
        chrono_clock::time_point new_time = chrono_clock::now();
        auto ahead_dur = std::chrono::duration_cast<milliseconds>(time - new_time);

        if (ahead_dur.count() > 0) {
            std::this_thread::sleep_for(ahead_dur);
            time += time_per_tick;
            tick_count++;
            // std::cout << "Ahead by " << ahead_dur.count() << "ms :" << tickcount() << " ticks\n";
        } else {

            // int behind = -ahead_dur.count();
            // int lost = behind - %  ms_per_tick;
            // Lost deberia dar un multiplo de  ms_per_tick.. i.e tiempo
            // total en iteraciones perdido. La cantidad de iteraciones perdidas es
            // (lost / ms_per_tick) basicamente.

            // Simplificadamente
            milliseconds lost = -ahead_dur + ahead_dur % time_per_tick;

            time += time_per_tick + lost;
            tick_count+= 1+ lost/time_per_tick;
            
            // std::cout << "Behind by " << -ahead_dur.count() << "ms lost " << lost.count()
            //           << "ms:: " << tickcount() << "ticks\n";
        }
    }

};
#endif
