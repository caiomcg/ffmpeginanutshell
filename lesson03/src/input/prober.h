#ifndef INPUT_PROBER_H
#define INPUT_PROBER_H

extern "C" {
  #include "libavcode/avcodec.h"
  #include "libavformat/avformat.h"
};

class Prober {
private:
    AVCodecContext* codec_context_;
    AVFormatContext* format_context_;
    AVCodec* codec_;
    AVStream* stream_;
public:
    explicit Prober(const char* input) noexcept(false);
    ~Prober();

    Prober(Prober&) = delete;
    Prober& operator=(Prober&) = delete;

    Prober(Prober&& rhs);
    Prober& operator=(Prober&& rhs);

    AVCodecContext* getCodecContext() const;
    AVFormatContext* getFormatContext() const;
    AVCodec* getCodec() const;
};

#endif // define INPUT_PROBER_H
