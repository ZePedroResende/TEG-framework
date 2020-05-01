//
// Created by resende on 30/04/2020.
//

#ifndef TEG_LOGGER_HPP
#define TEG_LOGGER_HPP

#include <mutex>
#include <iostream>
#include <string_view>

class logger {
protected:
    logger()   {}

public:
    static logger& instance(){
        static logger lg;
        return lg;
    }

    logger(logger const &) = delete;
    logger& operator=(logger const &) = delete;

    void log(std::basic_string<char> message) {
        std::lock_guard<std::mutex> lock(mt);
        std::cout << "LOG: " << message << std::endl;
    }

private:
    std::mutex mt;
};
#endif //TEG_LOGGER_HPP
