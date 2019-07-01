#ifndef BROKER_BROKER_INTERFACE_H
#define BROKER_BROKER_INTERFACE_H

extern "C" {
    #include <libavformat/avformat.h>
};

class BrokerInterface {
public:
    virtual ~BrokerInterface() = delete;

    BrokerInterface& probe() = delete;

};

#endif //define BROKER_BROKER_INTERFACE_H
