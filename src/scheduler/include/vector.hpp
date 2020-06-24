//
// Created by resende on 6/20/20.
//

#ifndef TEG_VECTOR_HPP
#define TEG_VECTOR_HPP

#include <mutex>
#include <data.hpp>

class DataVector {
public:

    DataVector(DataVector &&datavetor) {
        std::unique_lock<std::mutex> lck(datavetor.mutex);
        data = datavetor.data;
    }

    DataVector() : DataVector(100) {

    }

    explicit DataVector(int size) : data(size, Data()) {
    }

    Data* front() {
        std::unique_lock<std::mutex> lck(mutex);
        if (!data.empty()){
            return &data[current];
        }
        else{
            return nullptr;
        }
    }

    void erase() {

        std::unique_lock<std::mutex> lck(mutex);
        current++;
    }

    int size(){
        std::unique_lock<std::mutex> lck(mutex);
        return data.size();
    }

    bool empty() {
        std::unique_lock<std::mutex> lck(mutex);
        return current < data.size();
    }


private:
    std::mutex mutex;
    std::vector<Data> data;
    int current;
};

#endif //TEG_VECTOR_HPP
