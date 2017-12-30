#include "BDFStream.h"

BDFStream::BDFStream(std::istream &stream) : m_stream(stream) {

}

BDFStream::~BDFStream() {

}

void BDFStream::startLine() {
  m_lineBuffer.clear();
  std::getline(m_stream, m_lineBuffer);
  m_lineBufferIterator = m_lineBuffer.begin();

  if(m_stream.fail() || m_stream.eof()) {
    throw std::runtime_error("unexpected end of file");
  }
}

std::string BDFStream::readWord() {
  std::string word;
  enum {
    BeforeFirst,
    Normal,
    String,
    EscapedString
  } state = BeforeFirst;

  while(m_lineBufferIterator != m_lineBuffer.end()) {
    char ch = *(m_lineBufferIterator++);

    switch(state) {
    case BeforeFirst:
      if(ch == '"')
        state = String;
      else if(!isspace(ch)) {
        word.push_back(ch);
        state = Normal;
      }

      break;

    case Normal:
      if(ch == '"')
        state = String;
      else if(isspace(ch))
        goto endLoop;
      else
        word.push_back(ch);

      break;

    case String:
      if(ch == '"')
        state = Normal;
      else if(ch == '\\')
        state = EscapedString;
      else
        word.push_back(ch);

      break;

    case EscapedString:
      word.push_back(ch);
      state = String;

      break;
    }
  }
  endLoop:

  if(state != Normal)
    throw std::runtime_error("unexpected end of token");

  return word;
}

int BDFStream::readInt() {
  return std::stoi(readWord());
}

void BDFStream::endLine() {
  if(m_lineBufferIterator != m_lineBuffer.end())
    throw std::runtime_error("extra tokens at the end of line");
}
