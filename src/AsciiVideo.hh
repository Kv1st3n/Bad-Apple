#ifndef ASCII_VIDEO_HH
#define ASCII_VIDEO_HH

#include "Video.hh"
#include <string>
#include <vector>

class AsciiVideo : public Video
{
public:
    AsciiVideo() = default;
    ~AsciiVideo() override = default;

    bool initAscii(const char *path, int width = 120, int height = 45);
    bool readAsciiFrame(std::string &out, int rampVal);
    int getAsciiWidth() const { return asciiWidth; }
    int getAsciiHeight() const { return asciiHeight; }


private:
    int asciiWidth = 120;
    int asciiHeight = 45;
    std::vector<uint8_t> grayBuffer;
    const std::string ramp1 = "@%#*+=-:. ";
    const std::string ramp2 = " .:-=+*#%@";
};

#endif