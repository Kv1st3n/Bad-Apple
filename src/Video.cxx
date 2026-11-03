#include "Video.hh"
#include <iostream>

Video::Video()
{

}

Video::~Video()
{
    if (swsCtx)
    {
        sws_freeContext(swsCtx);
    }

    if (frame)
    {
        av_frame_free(&frame);
    }

    if (packet)
    {
        av_packet_free(&packet);
    }

    if (codecCtx)
    {
        avcodec_free_context(&codecCtx);
    }

    if (formatCtx)
    {
        avformat_close_input(&formatCtx);
    }
}

bool Video::initVideo()
{
    const char *path = "BadApple.mp4";

    if (avformat_open_input(&formatCtx, path, nullptr, nullptr) < 0)
    {
        std::cerr << "Could not open file: " << path << "\n";
        return false;
    }

    if (avformat_find_stream_info(formatCtx, nullptr) < 0)
    {
        std::cerr << "Could not find stream info.\n";
        return false;
    }

    for (unsigned int i = 0; i < formatCtx->nb_streams; i++)
    {
        if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1)
    {
        std::cerr << "Could not find video stream in file.\n";
        return false;
    }

    codecPar = formatCtx->streams[videoStreamIndex]->codecpar;
    codec = avcodec_find_decoder(codecPar->codec_id);

    if (!codec)
    {
        std::cerr << "Unsupported codec!\n";
        return false;
    }

    codecCtx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecCtx, codecPar);

    if (avcodec_open2(codecCtx, codec, nullptr) < 0)
    {
        std::cerr << "Could not open video decoder.\n";
        return false;
    }

    frame = av_frame_alloc();
    packet = av_packet_alloc();

    swsCtx = sws_getContext(
        codecCtx->width, codecCtx->height, codecCtx->pix_fmt,
        asciiWidth, asciiHeight, AV_PIX_FMT_GRAY8,
        SWS_BILINEAR, nullptr, nullptr, nullptr
    );

    if (!swsCtx)
    {
        std::cerr << "Could not create scaler.\n";
        return false;
    }

    rgbBuffer.resize(codecCtx->width * codecCtx->height * 4);

    return true;
}

bool Video::readFrame()
{
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
                    rgbBuffer.data() 
                };
                int dstStride[1] = 
                { 
                    codecCtx->width * 4 
                };

                sws_scale(swsCtx, frame->data, frame->linesize, 0,
                          codecCtx->height, dst, dstStride);

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

int Video::getWidth() const
{
    return codecCtx ? codecCtx->width : 0;
}

int Video::getHeight() const
{
    return codecCtx ? codecCtx->height : 0;
}

const uint8_t *Video::getPixels() const
{
    return rgbBuffer.data();
}