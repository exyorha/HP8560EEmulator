#ifndef __BDF_CHARACTER__H__
#define __BDF_CHARACTER__H__

#include <string>
#include <vector>

#include "BDFGlyphOffsets.h"
#include "BDFBoundingBox.h"

class BDFCharacter {
public:
  BDFCharacter();
  ~BDFCharacter();

  inline const std::string &name() const { return m_name; }
  inline void setName(const std::string &name) { m_name = name; }

  inline unsigned int encoding() const { return m_encoding; }
  inline void setEncoding(unsigned int encoding) { m_encoding = encoding; }

  inline BDFGlyphOffsets &offsets() { return m_offsets; }
  inline const BDFGlyphOffsets &offsets() const { return m_offsets; }
  inline void setOffsets(const BDFGlyphOffsets &offsets) { m_offsets = offsets; }

  inline BDFBoundingBox &boundingBox() { return m_boundingBox; }
  inline const BDFBoundingBox &boundingBox() const { return m_boundingBox; }
  inline void setBoundingBox(const BDFBoundingBox &boundingBox) { m_boundingBox = boundingBox; }

  inline std::vector<unsigned char> &bitmapData() { return m_bitmapData; }
  inline const std::vector<unsigned char> &bitmapData() const { return m_bitmapData; }
  inline void setBitmapData(const std::vector<unsigned char> &bitmapData) { m_bitmapData = bitmapData; }

private:
  std::string m_name;
  unsigned int m_encoding;
  BDFGlyphOffsets m_offsets;
  BDFBoundingBox m_boundingBox;
  std::vector<unsigned char> m_bitmapData;
};

#endif
