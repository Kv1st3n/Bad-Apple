#include "AsciiVideo.hh"
#include <iostream>

bool AsciiVideo::initAscii(const char *path, int width, int height)
{
    asciiWidth = width;
    asciiHeight = height;

    if (!openInput(path))
    {
        return false;
    }

    swsCtx = sws_getContext(
        codecCtx->width, codecCtx->height, codecCtx->pix_fmt,
        asciiWidth, asciiHeight, AV_PIX_FMT_GRAY8,
        SWS_BILINEAR, nullptr, nullptr, nullptr);

    if (!swsCtx)
    {
        std::cerr << "Could not create scaler.\n";
        return false;
    }

    grayBuffer.resize(asciiWidth * asciiHeight);
    return true;
}

bool AsciiVideo::readAsciiFrame(std::string &out)
{
    const int rampLength = ramp.length();

    while (av_read_frame(formatCtx, packet) >= 0)
    {
        if (packet->stream_index == videoStreamIndex)
        {
            avcodec_send_packet(codecCtx, packet);
            av_packet_unref(packet);

            if (avcodec_receive_frame(codecCtx, frame) == 0)
            {
                uint8_t *dst[1] = 
                { 
                    grayBuffer.data() 
                };

                int dstStride[1] = 
                { 
                    asciiWidth 
                };

                sws_scale(swsCtx, frame->data, frame->linesize, 0, codecCtx->height, dst, dstStride);

                out.clear();
                for (int y = 0; y < asciiHeight; ++y)
                {
                    for (int x = 0; x < asciiWidth; ++x)
                    {
                        uint8_t b = grayBuffer[y * asciiWidth + x];
                        out += ramp[(b * (rampLength - 1)) / 255];
                    }
                    out += '\n';
                }
                return true;
            }
        }
        else
        {
            av_packet_unref(packet);
        }
    }
    return false;
}