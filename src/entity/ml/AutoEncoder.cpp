#include <cmath>

#include "AutoEncoder.h"
using namespace torch;

Encoder::Encoder(uint8_t in, uint8_t maxCompression, uint8_t levels)
    : layers(register_module("layers",
                             AutoEncoder::constructLayers(true, in, maxCompression, levels))) {}

torch::Tensor Encoder::forward(torch::Tensor x) {
  return layers->forward(x);
}

Decoder::Decoder(uint8_t maxCompression, uint8_t out, uint8_t levels)
    : layers(register_module("decoder_layers",
                             AutoEncoder::constructLayers(false, maxCompression, out, levels))) {}

Tensor Decoder::forward(torch::Tensor x) {
  return layers->forward(x);
}

AutoEncoder::AutoEncoder(uint8_t in, uint8_t maxCompression, uint8_t levels) {
  encoder = register_module("encoder", std::make_shared<Encoder>(in, maxCompression, levels));
  decoder = register_module("decoder", std::make_shared<Decoder>(maxCompression, in, levels));
}
torch::Tensor AutoEncoder::forward(Tensor x) {
  Tensor encoded = encoder->forward(x);
  Tensor decoded = decoder->forward(encoded);
  return decoded;
}

torch::nn::Sequential AutoEncoder::constructLayers(bool compressing, int in, int out, int levels) {
  torch::nn::Sequential layers;
  int size_increment = (out - in) / levels;
  int current_size = in;

  for (size_t i = 0; i < levels; ++i) {
    int next_size;
    if (compressing) {
      next_size = std::max(current_size + size_increment, out);
      if (i == levels - 1) {
        next_size = out;
      }
    } else {
      next_size = std::min(current_size + size_increment, out);
      if (i == 0) {
        next_size = out - (levels-1) * size_increment;
      }
    }

    layers->push_back(torch::nn::Linear(current_size, next_size));
    layers->push_back(torch::nn::ReLU());

    current_size = next_size;
  }

  return layers;
}
