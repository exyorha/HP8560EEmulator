#ifndef __BDF_FILE__H__
#define __BDF_FILE__H__

#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

#include "BDFBoundingBox.h"
#include "BDFGlyphOffsets.h"
#include "BDFCharacter.h"

class BDFFile {
public:
    BDFFile();
    ~BDFFile();

    inline const std::string &version() const { return m_version; }
    inline void setVersion(const std::string &version) { m_version = version; }

    inline const std::string &fontName() const { return m_fontName; }
    inline void setFontName(const std::string &fontName) { m_fontName = fontName; }

    inline int pointSize() const { return m_pointSize; }
    inline void setPointSize(int pointSize) { m_pointSize = pointSize; }

    inline int xResolution() const { return m_xResolution; }
    inline void setXResolution(int xResolution) { m_xResolution = xResolution; }

    inline int yResolution() const { return m_yResolution; }
    inline void setYResolution(int yResolution) { m_yResolution = yResolution; }

    inline int metricsSet() const { return m_metricsSet; }
    inline void setMetricsSet(int metricsSet) { m_metricsSet = metricsSet; }

    inline BDFBoundingBox &fontBoundingBox() { return m_fontBoundingBox; }
    inline const BDFBoundingBox &fontBoundingBox() const { return m_fontBoundingBox; }
    inline void setFontBoundingBox(const BDFBoundingBox &fontBoundingBox) { m_fontBoundingBox = fontBoundingBox; }

    inline BDFGlyphOffsets &defaultOffsets() { return m_defaultOffsets; }
    inline const BDFGlyphOffsets &defaultOffsets() const { return m_defaultOffsets; }
    inline void setDefaultOffsets(const BDFGlyphOffsets &defaultOffsets) { m_defaultOffsets = defaultOffsets; }

    inline std::unordered_map<std::string, std::string> &properties() { return m_properties; }
    inline const std::unordered_map<std::string, std::string> &properties() const { return m_properties; }
    inline void setProperties(const std::unordered_map<std::string, std::string> &properties) { m_properties = properties; }

    inline std::vector<BDFCharacter> &characters() { return m_characters; }
    inline const std::vector<BDFCharacter> &characters() const { return m_characters; }
    inline void setCharacters(const std::vector<BDFCharacter> &characters) { m_characters = characters; }

    static BDFFile parse(const std::string &filename);
    static BDFFile parse(std::istream &stream);

    bool getProperty(const std::string &key, std::string &value) const;
    bool getProperty(const std::string &key, int &value) const;
    bool lookupCodePoint(unsigned int encoding, const BDFCharacter *&character) const;

private:
    std::string m_version, m_fontName;
    int m_pointSize, m_xResolution, m_yResolution, m_metricsSet;
    BDFBoundingBox m_fontBoundingBox;
    BDFGlyphOffsets m_defaultOffsets;
    std::unordered_map<std::string, std::string> m_properties;
    std::vector<BDFCharacter> m_characters;
};

#endif
