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
/// A module for interacting with python with boost interface
///
#pragma once

#ifdef INCLUDE_BOOST_PYTHON_INTERFACE

#include "NumCpp/Core/Error.hpp"
#include "NumCpp/Core/Shape.hpp"
#include "NumCpp/NdArray.hpp"
#include "NumCpp/PythonInterface/BoostNumpyNdarrayHelper.hpp"

#include "boost/python.hpp"
#include "boost/python/numpy.hpp"

#include <map>
#include <string>

namespace nc
{
    namespace boostPythonInterface
    {
        //============================================================================
        ///						Converts from a boost ndarray to a NumCpp NdArray<T>
        ///
        /// @param      inArray
        ///
        /// @return     NdArray<T>
        ///
        template<typename dtype>
        inline NdArray<dtype> boost2Nc(const boost::python::numpy::ndarray& inArray)
        {
            BoostNdarrayHelper helper(inArray);
            if (helper.numDimensions() > 2)
            {
                THROW_RUNTIME_ERROR("Can only convert 1 and 2 dimensional arrays.");
            }

            Shape arrayShape;
            if (helper.numDimensions() == 1)
            {
                arrayShape.rows = 1;
                arrayShape.cols = static_cast<uint32>(helper.shape().front());

                NdArray<dtype> returnArray(arrayShape);
                for (uint32 i = 0; i < arrayShape.size(); ++i)
                {
                    returnArray[i] = static_cast<dtype>(helper(i));
                }

                return returnArray;
            }
            else
            {
                arrayShape.rows = static_cast<uint32>(helper.shape().front());
                arrayShape.cols = static_cast<uint32>(helper.shape()[1]);

                NdArray<dtype> returnArray(arrayShape);
                uint32 i = 0;
                for (uint32 row = 0; row < arrayShape.rows; ++row)
                {
                    for (uint32 col = 0; col < arrayShape.cols; ++col)
                    {
                        returnArray[i++] = static_cast<dtype>(helper(row, col));
                    }
                }

                return returnArray;
            }
        }

        //============================================================================
        ///						Converts from a NumCpp NdArray<T> to a boost ndarray
        ///
        /// @param      inArray
        ///
        /// @return     ndarray
        ///
        template<typename dtype>
        inline boost::python::numpy::ndarray nc2Boost(const NdArray<dtype>& inArray) noexcept
        {
            const Shape inShape = inArray.shape();
            boost::python::tuple shape = boost::python::make_tuple(inShape.rows, inShape.cols);
            BoostNdarrayHelper newNdArrayHelper(shape);

            for (uint32 row = 0; row < inShape.rows; ++row)
            {
                for (uint32 col = 0; col < inShape.cols; ++col)
                {
                    newNdArrayHelper(row, col) = static_cast<double>(inArray(row, col));
                }
            }
            return newNdArrayHelper.getArray();
        }

        //============================================================================
        ///						converts a boost python list to a std::vector
        ///
        /// @param      inList
        ///
        /// @return     std::vector<T>
        ///
        template<typename T>
        inline std::vector<T> list2vector(const boost::python::list& inList) noexcept
        {
            return std::vector<T>(boost::python::stl_input_iterator<T>(inList), boost::python::stl_input_iterator<T>());
        }

        //============================================================================
        ///						converts a std::vector to a boost python list
        ///
        /// @param      inVector
        ///
        /// @return     boost::python::list
        ///
        template <typename T>
        inline boost::python::list vector2list(std::vector<T>& inVector) noexcept
        {
            boost::python::list outList;
            for (auto& value : inVector)
            {
                outList.append(value);
            }

            return outList;
        }

        //============================================================================
        ///						converts a std::map in to a boost python dictionary
        ///
        /// @param      inMap
        ///
        /// @return     boost::python::dict
        ///
        template <class Key, class Value>
        inline boost::python::dict map2dict(const std::map<Key, Value>& inMap) noexcept
        {
            boost::python::dict dictionary;
            for (auto& keyValue : inMap)
            {
                dictionary[keyValue.first] = keyValue.second;
            }
            return dictionary;
        }
    }
}
#endif
