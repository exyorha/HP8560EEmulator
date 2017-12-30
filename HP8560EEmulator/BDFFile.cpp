#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <sstream>

#include "BDFFile.h"
#include "BDFStream.h"

BDFFile::BDFFile() : m_metricsSet(0) {

}

BDFFile::~BDFFile() {

}

BDFFile BDFFile::parse(const std::string &filename) {
    std::ifstream stream;
    stream.exceptions(std::ios::failbit | std::ios::badbit);
    stream.open(filename);
    stream.exceptions(std::ios::badbit);

    return parse(stream);
}

BDFFile BDFFile::parse(std::istream &fstream) {
    BDFFile file;

    BDFStream stream(fstream);

    while(true) {
        stream.startLine();
        std::string type = stream.readWord();
        if(type == "STARTFONT") {
            file.setVersion(stream.readWord());
            stream.endLine();
        } else if(type == "COMMENT") {
            stream.readWord();
            stream.endLine();
        } else if(type == "FONT") {
            file.setFontName(stream.readWord());
            stream.endLine();
        } else if(type == "SIZE") {
            file.setPointSize(stream.readInt());
            file.setXResolution(stream.readInt());
            file.setYResolution(stream.readInt());
            stream.endLine();
        } else if(type == "FONTBOUNDINGBOX") {
            file.fontBoundingBox().width = stream.readInt();
            file.fontBoundingBox().height = stream.readInt();
            file.fontBoundingBox().x = stream.readInt();
            file.fontBoundingBox().y = stream.readInt();
            stream.endLine();
        } else if(type == "METRICSSET") {
            file.setMetricsSet(stream.readInt());
            stream.endLine();
        } else if(type == "SWIDTH") {
            file.defaultOffsets().scalableWidthX = stream.readInt();
            file.defaultOffsets().scalableWidthY = stream.readInt();
            stream.endLine();
        } else if(type == "DWIDTH") {
            file.defaultOffsets().deviceWidthX = stream.readInt();
            file.defaultOffsets().deviceWidthY = stream.readInt();
            stream.endLine();
        } else if(type == "SWIDTH1") {
            file.defaultOffsets().mode1ScalableWidthX = stream.readInt();
            file.defaultOffsets().mode1ScalableWidthY = stream.readInt();
            stream.endLine();
        } else if(type == "DWIDTH1") {
            file.defaultOffsets().mode1DeviceWidthX = stream.readInt();
            file.defaultOffsets().mode1DeviceWidthY = stream.readInt();
            stream.endLine();
        } else if(type == "VVECTOR") {
            file.defaultOffsets().mode0to1OffsetX = stream.readInt();
            file.defaultOffsets().mode0to1OffsetY = stream.readInt();
            stream.endLine();
        } else if(type == "STARTPROPERTIES") {
            int count = stream.readInt();
            stream.endLine();

            for(int index = 0; index < count; index++) {
                stream.startLine();
                std::string key = stream.readWord();
                std::string value = stream.readWord();
                stream.endLine();
                file.properties().insert(std::make_pair(key, value));
            }

            stream.startLine();
            if(stream.readWord() != "ENDPROPERTIES") {
                throw std::runtime_error("Property list terminator is not found");
            }
            stream.endLine();
        } else if(type == "CHARS") {
            int count = stream.readInt();
            stream.endLine();

            file.characters().reserve(file.characters().size() + count);

            for(int index = 0; index < count; index++) {
                stream.startLine();
                type = stream.readWord();

                if(type == "STARTCHAR") {
                    BDFCharacter character;
                    character.setName(stream.readWord());
                    character.setOffsets(file.defaultOffsets());
                    character.setBoundingBox(file.fontBoundingBox());
                    stream.endLine();

                    while(true) {
                        stream.startLine();
                        type = stream.readWord();

                        if(type == "ENCODING") {
                            character.setEncoding(stream.readInt());
                            stream.endLine();
                        } else if(type == "SWIDTH") {
                            character.offsets().scalableWidthX = stream.readInt();
                            character.offsets().scalableWidthY = stream.readInt();
                            stream.endLine();
                        } else if(type == "DWIDTH") {
                            character.offsets().deviceWidthX = stream.readInt();
                            character.offsets().deviceWidthY = stream.readInt();
                            stream.endLine();
                        } else if(type == "SWIDTH1") {
                            character.offsets().mode1ScalableWidthX = stream.readInt();
                            character.offsets().mode1ScalableWidthY = stream.readInt();
                            stream.endLine();
                        } else if(type == "DWIDTH1") {
                            character.offsets().mode1DeviceWidthX = stream.readInt();
                            character.offsets().mode1DeviceWidthY = stream.readInt();
                            stream.endLine();
                        } else if(type == "VVECTOR") {
                            character.offsets().mode0to1OffsetX = stream.readInt();
                            character.offsets().mode0to1OffsetY = stream.readInt();
                            stream.endLine();
                        } else if(type == "BBX") {
                            character.boundingBox().width = stream.readInt();
                            character.boundingBox().height = stream.readInt();
                            character.boundingBox().x = stream.readInt();
                            character.boundingBox().y = stream.readInt();
                            stream.endLine();
                        } else if(type == "BITMAP") {
                            unsigned int bytesPerLine = (character.boundingBox().width + 7) / 8;
                            std::vector<unsigned char> bitmapData(character.boundingBox().height * bytesPerLine);
                            std::vector<unsigned char>::iterator it = bitmapData.begin();

                            for(int line = 0; line < character.boundingBox().height; line++) {
                                stream.startLine();
                                std::string hexString = stream.readWord();
                                stream.endLine();

                                if(hexString.size() != bytesPerLine * 2)
                                    throw std::runtime_error("unexpected length of bitmap data");

                                std::stringstream sstream(hexString);
                                for(unsigned int byte = 0; byte < bytesPerLine; byte++) {
                                    char data[2];
                                    sstream.read(&data[0], 2);
                                    *(it++) = (unsigned char) std::stoul(std::string(data, 2), 0, 16);
                                }
                            }

                            character.setBitmapData(bitmapData);
                        } else if(type == "ENDCHAR") {
                            break;

                        } else {
                            throw std::runtime_error("unknown BDF directive " + type + " in character definition");
                        }
                    }

                    file.characters().push_back(character);
                } else {
                    throw std::runtime_error("unknown BDF directive " + type + " in inter-character space");
                }
            }
        } else if(type == "ENDFONT") {
            stream.endLine();
            break;
        } else {
            throw std::runtime_error("unknown BDF directive " + type);
        }
    }

    return file;
}

bool BDFFile::getProperty(const std::string &key, std::string &value) const {
    std::unordered_map<std::string, std::string>::const_iterator it = m_properties.find(key);
    if(it == m_properties.end())
        return false;
    else {
        value = it->second;
        return true;
    }
}

bool BDFFile::getProperty(const std::string &key, int &value) const {
    std::string string;
    if(getProperty(key, string)) {
        value = stoi(string);
        return true;
    } else {
        return false;
    }
}

bool BDFFile::lookupCodePoint(unsigned int encoding, const BDFCharacter *&character) const {
    for(std::vector<BDFCharacter>::const_iterator it = m_characters.begin(); it != m_characters.end(); it++) {
        if(it->encoding() == encoding) {
            character = &*it;
            return true;
        }
    }

    return false;
}