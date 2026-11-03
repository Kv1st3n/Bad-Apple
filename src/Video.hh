#ifndef VIDEO_HH
#define VIDEO_HH

#include <cstdint>
#include <vector>

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

class Video
{
public:
    Video();
    ~Video();

    bool initVideo();
    bool readFrame();

    int getWidth() const;
    int getHeight() const;
    const uint8_t *getPixels() const;

private:
    AVFormatContext *formatCtx = nullptr;
    AVCodecParameters *codecPar = nullptr;
    const AVCodec *codec = nullptr;
    AVCodecContext *codecCtx = nullptr;
    AVFrame *frame = nullptr;
    AVPacket *packet = nullptr;
    SwsContext *swsCtx = nullptr;

    int videoStreamIndex = -1;
    std::vector<uint8_t> rgbBuffer;

    int asciiWidth = 120;
    int asciiHeight = 45;
};

#endif