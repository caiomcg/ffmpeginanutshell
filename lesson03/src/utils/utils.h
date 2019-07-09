#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

extern "C" {
    #include "libavutil/avutil.h"
}

namespace Utils {
    // char* getFfmpegErrorMessage(const int& code) {
    //     char buffer[1024]; // TODO: Get maximum buffer
    //     av_strerror(code, buffer, 1024);
    //     return buffer;
    // }
};

#endif // define UTILS_UTILS_H
