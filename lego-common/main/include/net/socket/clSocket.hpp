/**
 *  Establece la definición de la clase Socket para efectuar la comunicación
 *  de procesos que no comparten memoria, utilizando un esquema de memoria
 *  distribuida.  El desarrollo de esta clase se hará en varias etapas, primero
 *  los métodos necesarios para los clientes, en la otras etapas los métodos para el servidor,
 *  manejo de IPv6, conexiones seguras y otros
 *
 *  Universidad de Costa Rica
 *  ECCI
 *  CI0123 Proyecto integrador de redes y sistemas operativos
 *  2023-i
 *  Grupos: 2 y 3
 *
 * (versión Ubuntu)
 *
 **/

#ifndef Socket_h
#define Socket_h

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <openssl/ssl.h>
class Socket {

    public:
        Socket( char, bool IPv6 = false );	// char == 's' => stream, char == 'd' => datagram
        Socket( int );				// int = socket descriptor
        ~Socket();
        int Connect( const char * host, int port );
        int Connect( const char * host, const char * service );
        void Close();
        int Read( void * buffer, size_t size );
        int Write( const void * text, size_t size );
        int Write( const char * buffer );	// size is calculated with strlen
        int Listen( int backlog );
        int Bind( int port );
        Socket * Accept();
        int Shutdown( int mode );		// mode = { SHUT_RD, SHUT_WR, SHUT_RDWR }
        void SetIDSocket( int newId );
        
        ssize_t sendTo(const void *buffer /*message*/, size_t length, void *pDest_addr);
        ssize_t recvFrom(void* buf, size_t len, void* addr);

        void InitSSLContext();
        void InitSSL();
        void SSLLoadCertificates( const char * certFileName,
          const char * keyFileName );
        int SSLConnect( const char* host, int port );
        int SSLConnect( char* host, char* service );
        int SSLRead( void * buffer, int size ); // AI said to use size_t instead of int
        int SSLWrite( const void * text, int size ); // AI said to use const void instead of just void
        void SSLInitServer( const char * certFileName,
          const char * keyFileName);
        void SSLCreate( Socket * original );
        void SSLAccept();
        const char * SSLGetCipher();
        void SSLInitServerContext();
        void SSLShowCerts();
    private:
        int idSocket;
        int port;
        bool ipv6;
        void * SSLContext;	// SSL context
	      void * SSLStruct;	// SSL BIO basis input output

    int socketFD;
    fd_set read_fds{};
    struct timeval timeout{
            5, 0
    };
    bool isReadReady();
};

#endif

