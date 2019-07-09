#include "prober.h"

#include <stdexcept>

Prober::Prober(const char* input) {
    auto error_code = 0;

    if ((error_code = avformat_open_input(&this->format_context_, input, nullptr, nullptr)) != 0) { // Open the file
        throw std::runtime_error("Prober: Could not open file " + input);
    }

    if (avformat_find_stream_info(this->format_context_, nullptr) < 0) { // Find the best stream information
        throw std::runtime_error("Could not fetch stream info"); // Throw an exception if failed
    }

    av_dump_format(this->format_context_, 0, input, 0);

    int video_stream_index = av_find_best_stream(this->format_context_, AVMEDIA_TYPE_VIDEO, -1, -1, &(this->codec_), 0); // Search for the best stream and store its index

    if (video_stream_index < 0) {
        throw std::runtime_error("Could not find best stream");  // Throw an exception if failed
    }

    this->stream_ = this->format_context_->streams[video_stream_index];  // Get the best stream

    if (!(this->codec_ = avcodec_find_decoder(this->stream_->codecpar->codec_id))) {  // Find decoder codec
        throw std::runtime_error("Could find decoder codec.");
    }

    if (!(this->codec_context_ = avcodec_alloc_context3(this->codec_))) { // Alloc codec context
        throw std::runtime_error("Could not alloc codec context.");
    }

    if ((error_code = avcodec_parameters_to_context(this->codec_context_, this->stream_->codecpar)) < 0) {                                                // Fetch the error code
        throw std::runtime_error("Could not copy codec context to codec parameters of input stream: ");  // Throw an exception if failed
    }

    // The flag below should only be used with experimental ffmpeg features
    //this->codec_context_->strict_std_compliance = -2;

    if (avcodec_open2(this->codec_context_, this->codec_, nullptr) < 0) { // Open the codec
        throw std::runtime_error("Could not open codec"); // Throw an exception if failed
    }
}
Prober::~Prober() {
    if (this->codec_context_ != nullptr) {
        avcodec_free_context(&this->codec_context_);
        this->codec_context_ = nullptr;
    }
    if (this->codec_ != nullptr) {
        avformat_close_input(&this->format_context_);
        this->format_context_ = nullptr;
    }
}

Prober::Prober(Prober&& rhs) {
    std::swap(this->format_context_, rhs.format_context_);
    std::swap(this->stream_, rhs.stream_);
    std::swap(this->codec_context_, rhs.codec_context_);
    std::swap(this->codec_, rhs.codec_);
}

Prober& Prober::operator=(Prober&& rhs) {
    std::swap(this->format_context_, rhs.format_context_);
    std::swap(this->stream_, rhs.stream_);
    std::swap(this->codec_context_, rhs.codec_context_);
    std::swap(this->codec_, rhs.codec_);

    return this;
}

AVCodecContext* Prober::getCodecContext() const {
    return this->codec_context_;
}

AVFormatContext* Prober::getFormatContext() const {
    return this->format_context_;
}

AVCodec* Prober::getCodec() const {
    return this->codec_;
}
