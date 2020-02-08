/**
 *      功能：sockets类
 *      作者：jiacobi
 *      日期：2020.2.8
 **/

#pragma once

#include <stdint.h>
#include "../base/Platform.h"

// struct tcp_info is in <netinet/tcp.h>
struct tcp_info;

namespace net {
    class InetAddress;

    class Socket 
    {
    public:
        explicit Socket(int sockfd) : sockfd_(sockfd) {}
        ~Socket();

        SOCKET fd() const { return sockfd_; }
        bool getTcpInfoString(char *buf, int len) const;

        void bindAddress(const InetAddress& localaddr);
        void listen();
        int accept(InetAddress *peeraddr);

        void shutdownWrite();
        void setTcpNoDelay(bool on);
        void setReuseAddr(bool on);
        void setReusePort(bool on);
        void setKeepAlive(bool on);

    private:
        const SOCKET sockfd_;
    };

	namespace sockets
	{
		///
		/// Creates a socket file descriptor,
		/// abort if any error.
        SOCKET createOrDie();
        SOCKET createNonblockingOrDie();

        void setNonBlockAndCloseOnExec(SOCKET sockfd);

        void setReuseAddr(SOCKET sockfd, bool on);
        void setReusePort(SOCKET sockfd, bool on);

        SOCKET connect(SOCKET sockfd, const struct sockaddr_in& addr);
		void bindOrDie(SOCKET sockfd, const struct sockaddr_in& addr);
		void listenOrDie(SOCKET sockfd);
        SOCKET accept(SOCKET sockfd, struct sockaddr_in* addr);
        int32_t read(SOCKET sockfd, void *buf, int32_t count);
#ifndef WIN32
		ssize_t readv(SOCKET sockfd, const struct iovec *iov, int iovcnt);
#endif
		int32_t write(SOCKET sockfd, const void *buf, int32_t count);
		void close(SOCKET sockfd);
		void shutdownWrite(SOCKET sockfd);

		void toIpPort(char* buf, size_t size, const struct sockaddr_in& addr);
		void toIp(char* buf, size_t size, const struct sockaddr_in& addr);
		void fromIpPort(const char* ip, uint16_t port, struct sockaddr_in* addr);

		int getSocketError(SOCKET sockfd);

		const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr);
		struct sockaddr* sockaddr_cast(struct sockaddr_in* addr);
		const struct sockaddr_in* sockaddr_in_cast(const struct sockaddr* addr);
		struct sockaddr_in* sockaddr_in_cast(struct sockaddr* addr);

		struct sockaddr_in getLocalAddr(SOCKET sockfd);
		struct sockaddr_in getPeerAddr(SOCKET sockfd);
		bool isSelfConnect(SOCKET sockfd);
	}
}