////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef VANETWORK_ERR
#define VANETWORK_ERR

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vaNetwork/Config.h>
#include <ostream>

namespace vaNetwork {


////////////////////////////////////////////////////////////
/// \brief Standard stream used by SFML to output warnings and errors
///
////////////////////////////////////////////////////////////
SFML_API std::ostream& Err();


}
#endif


////////////////////////////////////////////////////////////
/// \fn vaNetwork::Err
/// \ingroup system
///
/// By default, vaNetwork::Err() outputs to the same location as std::cerr,
/// (-> the stderr descriptor) which is the console if there's
/// one available.
///
/// It is a standard std::ostream instance, so it supports all the
/// insertion operations defined by the STL
/// (operator <<, manipulators, etc.).
///
/// vaNetwork::Err() can be redirected to write to another output, independantly
/// of std::cerr, by using the rdbuf() function provided by the
/// std::ostream class.
///
/// Example:
/// \code
/// // Redirect to a file
/// std::ofstream file("sfml-log.txt");
/// std::streambuf* previous = vaNetwork::Err().rdbuf(file.rdbuf());
///
/// // Redirect to nothing
/// vaNetwork::Err().rdbuf(NULL);
///
/// // Restore the original output
/// vaNetwork::Err().rdbuf(previous);
/// \endcode
///
////////////////////////////////////////////////////////////
