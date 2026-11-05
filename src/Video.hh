#ifndef VIDEO_HH
#define VIDEO_HH

#include <cstdint>
#include <vector>
#include <string>

extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

class Video
{
public:
    Video();
    virtual ~Video();

    bool initVideo();
    bool readFrame();
    int getWidth() const;
    int getHeight() const;
    const uint8_t *getPixels() const;

    void close();

protected:
    bool openInput(const char *path);

    AVFormatContext *formatCtx = nullptr;
    AVCodecParameters *codecPar = nullptr;
    const AVCodec *codec = nullptr;
    AVCodecContext *codecCtx = nullptr;
    AVFrame *frame = nullptr;
    AVPacket *packet = nullptr;
    SwsContext *swsCtx = nullptr;

    int videoStreamIndex = -1;
    std::vector<uint8_t> rgbBuffer;
};

#endif