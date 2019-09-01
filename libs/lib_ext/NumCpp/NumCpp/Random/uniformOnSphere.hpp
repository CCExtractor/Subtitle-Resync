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
/// Such a distribution produces random numbers uniformly
///	distributed on the unit sphere of arbitrary dimension dim.
///
#pragma once

#include "NumCpp/Core/Error.hpp"
#include "NumCpp/Core/Shape.hpp"
#include "NumCpp/Core/Types.hpp"
#include "NumCpp/NdArray.hpp"
#include "NumCpp/Random/generator.hpp"

#include "boost/random/uniform_on_sphere.hpp"

#include <algorithm>
#include <string>

namespace nc
{
    namespace random
    {
        //============================================================================
        // Method Description:
        ///						Such a distribution produces random numbers uniformly
        ///						distributed on the unit sphere of arbitrary dimension dim.
        ///
        /// @param				inNumPoints
        /// @param				inDims: dimension of the sphere (default 2)
        /// @return
        ///				NdArray
        ///
        template<typename dtype>
        NdArray<dtype> uniformOnSphere(uint32 inNumPoints, uint32 inDims = 2)
        {
            if (inDims < 0)
            {
                THROW_INVALID_ARGUMENT_ERROR("input dimension must be greater than or equal to zero.");
            }

            boost::random::uniform_on_sphere<dtype> dist(inDims);

            NdArray<dtype> returnArray(inNumPoints, inDims);
            for (uint32 i = 0; i < inNumPoints; ++i)
            {
                std::vector<dtype> point = dist(generator_);
                for (uint32 dim = 0; dim < inDims; ++dim)
                {
                    returnArray(i, dim) = point[dim];
                }
            }

            return returnArray;
        }
    }
}
