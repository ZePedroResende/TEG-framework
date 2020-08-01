#include <iostream>
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main() {
  zmq::context_t ctx;
  zmq::socket_t sock(ctx, zmq::socket_type::pub);
  sock.bind("tcp://*:8082");
  while (true) {
    sock.send(zmq::buffer(""), zmq::send_flags::sndmore);
    sock.send(zmq::str_buffer("{thread_id: 1, data_id: 5, function_id: 3}"));
    zmq_sleep(5);
  }

  return 0;
}
