#ifndef _TIMEMANAGER_HPP
#define _TIMEMANAGER_HPP

#if defined(WIN32) || defined(_WIN32)   // Windows system specific
#include <windows.h>
#else                                   // Unix based system specific
#include <sys/time.h>
#endif

namespace Tools
{   
    struct Time
    {
        // -=- Read-only private members -=-

        double DeltaTime()  { return deltaTime; };
        double GameTime()   { return gameTime;  };


        /* 
            * Usage
            
            - Upon the first summon, the time manager will be created as a static variable.
            - All summons will give back a reference on the TimeManagement.


            ? To store the Time inside of a CLASS, or a STRUCT :

            1- "Tools::Time& time;" inside the class/struct declaration to store it,
            2- ": time(Tools::Time::Summon())" right after the constructor definition to initialize it. 
        */
        static Time& Summon();

        void Update();


    private:
        Time();
        
        void   StartTimer               ();         // start timer
        void   StopTimer                ();         // stop the timer
        double GetElapsedTimeInSec      ();         // get elapsed time in second (Same as getting the deltatime)
        double GetElapsedTimeInMicroSec ();         // get elapsed time in micro-second

        // The deltaTime is the time in SECONDS that has passed between the two last updates.
        double deltaTime; 

        // Total time since PROGRAMS's begining.
        double gameTime;
        
        double startTimeInMicroSec;                 // starting time in micro-second
        double endTimeInMicroSec;                   // ending time in micro-second
        int    stopped;                             // stop flag

    #if defined(WIN32) || defined(_WIN32)
        LARGE_INTEGER frequency;                    // ticks per second
        LARGE_INTEGER startCount;                   //
        LARGE_INTEGER endCount;                     //
    
    #else
        timeval startCount;                         //
        timeval endCount;                           //
    
    #endif
    };
}

#endif