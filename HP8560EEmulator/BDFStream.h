#ifndef __BDF__H__
#define __BDF__H__

#include <istream>
#include <string>

class BDFStream {
public:
  BDFStream(std::istream &stream);
  ~BDFStream();

  void startLine();
  std::string readWord();
  int readInt();
  void endLine();

private:
  std::istream &m_stream;
  std::string m_lineBuffer;
  std::string::iterator m_lineBufferIterator;
};

#endif
