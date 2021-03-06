#ifndef __PROCESS_NODE_HPP__
#define __PROCESS_NODE_HPP__

#include <arpa/inet.h>
#include <unistd.h>

#include <sstream>

#include <glog/logging.h>

namespace process {

// Represents a remote "node" (encapsulates IP address and port).
class Node
{
public:
  Node() : ip(0), port(0) {}

  Node(uint32_t _ip, uint16_t _port) : ip(_ip), port(_port) {}

  bool operator < (const Node& that) const
  {
    if (ip == that.ip) {
      return port < that.port;
    } else {
      return ip < that.ip;
    }
  }

  bool operator == (const Node& that) const
  {
    return (ip == that.ip && port == that.port);
  }

  bool operator != (const Node& that) const
  {
    return !(*this == that);
  }

  uint32_t ip;
  uint16_t port;
};

inline std::ostream& operator << (std::ostream& stream, const Node& node)
{
  char ip[INET_ADDRSTRLEN];
  if (inet_ntop(AF_INET, (in_addr*) &node.ip, ip, INET_ADDRSTRLEN) == NULL) {
    PLOG(FATAL) << "Failed to get human-readable IP address for '"
                << node.ip << "'";
  }
  stream << ip << ":" << node.port;
  return stream;
}

} // namespace process {

#endif // __PROCESS_NODE_HPP__
