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

#ifndef VANETWORK_SOCKET
#define VANETWORK_SOCKET

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vaNetwork/SocketHandle.h>
#include <vaNetwork/NonCopyable.h>
#include <vector>

namespace vaNetwork {
    
    
class SocketSelector;

////////////////////////////////////////////////////////////
/// \brief Base class for all the socket types
///
////////////////////////////////////////////////////////////
class SFML_API Socket : NonCopyable
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Status codes that may be returned by socket functions
    ///
    ////////////////////////////////////////////////////////////
    enum Status
    {
        Done,         ///< The socket has sent / received the data
        NotReady,     ///< The socket is not ready to send / receive data yet
        Disconnected, ///< The TCP socket has been disconnected
        Error         ///< An unexpected error happened
    };

    ////////////////////////////////////////////////////////////
    /// \brief Some special values used by sockets
    ///
    ////////////////////////////////////////////////////////////
    enum
    {
        AnyPort = 0 ///< Special value that tells the system to pick any available port
    };

public :

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~Socket();

    ////////////////////////////////////////////////////////////
    /// \brief Set the blocking state of the socket
    ///
    /// In blocking mode, calls will not return until they have
    /// completed their task. For example, a call to Receive in
    /// blocking mode won't return until some data was actually
    /// received.
    /// In non-blocking mode, calls will always return immediately,
    /// using the return code to signal whether there was data
    /// available or not.
    /// By default, all sockets are blocking.
    ///
    /// \param blocking True to set the socket as blocking, false for non-blocking
    ///
    /// \see IsBlocking
    ///
    ////////////////////////////////////////////////////////////
    void SetBlocking(bool blocking);

    ////////////////////////////////////////////////////////////
    /// \brief Tell whether the socket is blocking or non-blocking mode
    ///
    /// \return True if the socket is blocking, false otherwise
    ///
    /// \see SetBlocking
    ///
    ////////////////////////////////////////////////////////////
    bool IsBlocking() const;

protected :

    ////////////////////////////////////////////////////////////
    /// \brief Types of protocols that the socket can use
    ///
    ////////////////////////////////////////////////////////////
    enum Type
    {
        Tcp, ///< TCP protocol
        Udp  ///< UDP protocol
    };

    ////////////////////////////////////////////////////////////
    /// \brief Structure holding the data of a pending packet
    ///
    ////////////////////////////////////////////////////////////
    struct PendingPacket
    {
        PendingPacket();

        Uint32            Size;         ///< Data of packet size
        std::size_t       SizeReceived; ///< Number of size bytes received so far
        std::vector<char> Data;         ///< Data of the packet
    };

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// This constructor can only be accessed by derived classes.
    ///
    /// \param type Type of the socket (TCP or UDP)
    ///
    ////////////////////////////////////////////////////////////
    Socket(Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Return the internal handle of the socket
    ///
    /// The returned handle may be invalid if the socket
    /// was not created yet (or already destroyed).
    /// This function can only be accessed by derived classes.
    ///
    /// \return The internal (OS-specific) handle of the socket
    ///
    ////////////////////////////////////////////////////////////
    SocketHandle GetHandle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Create the internal representation of the socket
    ///
    /// This function can only be accessed by derived classes.
    ///
    ////////////////////////////////////////////////////////////
    void Create();

    ////////////////////////////////////////////////////////////
    /// \brief Create the internal representation of the socket
    ///        from a socket handle
    ///
    /// This function can only be accessed by derived classes.
    ///
    /// \param handle OS-specific handle of the socket to wrap
    ///
    ////////////////////////////////////////////////////////////
    void Create(SocketHandle handle);

    ////////////////////////////////////////////////////////////
    /// \brief Close the socket gracefully
    ///
    /// This function can only be accessed by derived classes.
    ///
    ////////////////////////////////////////////////////////////
    void Close();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    PendingPacket myPendingPacket; ///< Temporary data of the packet currently being received

private :

    friend class SocketSelector;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Type         myType;       ///< Type of the socket (TCP or UDP)
    SocketHandle mySocket;     ///< Socket descriptor
    bool         myIsBlocking; ///< Current blocking mode of the socket
};


}
#endif


////////////////////////////////////////////////////////////
/// \class vaNetwork::Socket
/// \ingroup network
///
/// This class mainly defines internal stuff to be used by
/// derived classes.
///
/// The only public features that it defines, and which
/// is therefore common to all the socket classes, is the
/// blocking state. All sockets can be set as blocking or
/// non-blocking.
///
/// In blocking mode, socket functions will hang until
/// the operation completes, which means that the entire
/// program (well, in fact the current thread if you use
/// multiple ones) will be stuck waiting for your socket
/// operation to complete.
///
/// In non-blocking mode, all the socket functions will
/// return immediately. If the socket is not ready to complete
/// the requested operation, the function simply returns
/// the proper status code (Socket::NotReady).
///
/// The default mode, which is blocking, is the one that is
/// generally used, in combination with threads or selectors.
/// The non-blocking mode is rather used in real-time
/// applications that run an endless loop that can poll
/// the socket often enough, and cannot afford blocking
/// this loop.
///
/// \see vaNetwork::TcpListener, vaNetwork::TcpSocket, vaNetwork::UdpSocket
///
////////////////////////////////////////////////////////////