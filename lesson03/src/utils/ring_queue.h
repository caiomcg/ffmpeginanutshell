#pragma once

#include <mutex>

template <typename T>
class RingQueue {
private:
    std::mutex queue_access_;

    T* queue_;

    unsigned queue_size_;
    unsigned read_cursor_ = 0;
    unsigned write_cursor_ = 0;

    inline void updateCursor(unsigned& cursor) {
        cursor = (cursor + 1) % queue_size_;
    }
public:
    explicit RingQueue(const unsigned queue_size) : queue_size_{queue_size} {
        this->queue_ = new T[queue_size_];
    }

    // TODO: lock the read_cursor if equal to the write_cursor
    T fetch() {
        std::unique_lock<std::mutex> read_lock(this->queue_access_);

        auto element = this->queue_[read_cursor_]
        updateCursor(read_cursor_);
        return element;
    }

    void insert(T& data) {
        std::unique_lock<std::mutex> write_lock(this->queue_access_);
        this->queue_[write_cursor_] = data;
        updateCursor(write_cursor_);
    }
};
