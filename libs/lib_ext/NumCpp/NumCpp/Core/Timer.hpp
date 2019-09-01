/// @file
/// @author David Pilger <dpilger26@gmail.com>
/// [GitHub Repository](https://github.com/dpilger26/NumCpp)
/// @version 1.1
///
/// @section License
/// Copyright 2019 David Pilger
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this
/// software and associated documentation files(the "Software"), to deal in the Software
/// without restriction, including without limitation the rights to use, copy, modify,
/// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
/// permit persons to whom the Software is furnished to do so, subject to the following
/// conditions :
///
/// The above copyright notice and this permission notice shall be included in all copies
/// or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
/// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
/// PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
/// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
/// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.
///
/// @section Description
/// A timer class for timing code execution
///
#pragma once

#include "NumCpp/Core/Types.hpp"

#include <chrono>
#include <iostream>
#include <string>

namespace nc
{
    //================================================================================
    ///						A timer class for timing code execution
    template<typename TimeUnit = std::chrono::milliseconds>
    class Timer
    {
    public:
        //==============================Typedefs======================================
        typedef std::chrono::high_resolution_clock		ChronoClock;
        typedef std::chrono::time_point<ChronoClock>	TimePoint;

    private:
        //==============================Attributes====================================
        std::string		name_{ "" };
        std::string		unit_{ "" };
        TimePoint		start_;

        void setUnits()
        {
            if (std::is_same<TimeUnit, std::chrono::hours>::value)
            {
                unit_ = " hours";
            }
            else if (std::is_same<TimeUnit, std::chrono::minutes>::value)
            {
                unit_ = " minutes";
            }
            else if (std::is_same<TimeUnit, std::chrono::seconds>::value)
            {
                unit_ = " seconds";
            }
            else if (std::is_same<TimeUnit, std::chrono::milliseconds>::value)
            {
                unit_ = " milliseconds";
            }
            else if (std::is_same<TimeUnit, std::chrono::microseconds>::value)
            {
                unit_ = " microseconds";
            }
            else if (std::is_same<TimeUnit, std::chrono::nanoseconds>::value)
            {
                unit_ = " nanoseconds";
            }
            else
            {
                unit_ = " time units of some sort";
            }
        }

    public:
        //============================================================================
        ///						Constructor
        ///
        Timer() noexcept :
            start_(ChronoClock::now())
        {
            setUnits();
        }

        //============================================================================
        ///						Constructor
        ///
        /// @param      inName
        ///
        Timer(const std::string& inName) noexcept :
            name_(inName + " "),
            start_(ChronoClock::now())
        {
            setUnits();
        }

        //============================================================================
        ///						Sets/changes the timer name
        ///
        /// @param      inName
        ///
        void setName(const std::string& inName) noexcept
        {
            name_ = inName + " ";
        }

        //============================================================================
        ///						Starts the timer
        ///
        void tic() noexcept
        {
            start_ = ChronoClock::now();
        }

        //============================================================================
        /// Method Description:
        ///						Stops the timer
        ///
        /// @return     ellapsed time in specified time units
        ///
        uint64 toc() noexcept
        {
            const auto duration = static_cast<uint64>(std::chrono::duration_cast<TimeUnit>(ChronoClock::now() - start_).count());
            std::cout << name_ << "Elapsed Time = " << duration << unit_ << std::endl;
            return duration;
        }
    };
}
