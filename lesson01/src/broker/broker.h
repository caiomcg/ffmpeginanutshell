#ifndef BROKER_BROKER_H
#define BROKER_BROKER_H

#include <memory>

class Broker final {
private:
    // These need a shared access as they are required by the muxer/demuxer or
    // compressor/decompressor
    std::shared_ptr<AVFormatContext> format_context_; 
    std::shared_ptr<AVCodecContext>  codec_context_;
    std::shared_ptr<AVCodec>         codec_;
public:
    explicit Broker(const char* input);
    ~Broker();

    Broker(Broker&& rhs);
    Broker& operator=(const Broker&& rhs);

    Broker(const Broker&) = delete;
    Broker& operator=(const Broker&) = delete;
};

#endif // define BROKER_BROKER_H
