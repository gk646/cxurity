#ifndef CXURITY_SRC_ENTITY_ML_AUTOENCODER_H_
#define CXURITY_SRC_ENTITY_ML_AUTOENCODER_H_

#include "../headers/pch.h"

using namespace torch;

struct Encoder : nn::Module {
  nn::Linear linear{nullptr};
  nn::ReLU relu{nullptr};
  Encoder(int64_t input_size, int64_t hidden_size);

  Tensor forward(torch::Tensor x) {
    x = linear(x);
    x = relu(x);
    return x;
  }
};

struct Decoder : nn::Module {
  nn::Linear linear{nullptr};
  nn::Sigmoid sigmoid{nullptr};
  Decoder(int64_t hidden_size, int64_t output_size) {
    linear = register_module("linear", nn::Linear(hidden_size, output_size));
    sigmoid = register_module(
        "sigmoid",
        nn::Sigmoid());  // Use sigmoid to ensure output is in the same range as input
  }

  Tensor forward(torch::Tensor x) {
    x = linear(x);
    x = sigmoid(x);
    return x;
  }
};

struct AutoEncoder : nn::Module {
  std::shared_ptr<Encoder> encoder{nullptr};
  std::shared_ptr<Decoder> decoder{nullptr};
  AutoEncoder(int64_t input_size, int64_t hidden_size, int64_t output_size) {
    encoder = register_module("encoder", std::make_shared<Encoder>(input_size, hidden_size));
    decoder = register_module("decoder", std::make_shared<Decoder>(hidden_size, output_size));
  }

  std::pair<torch::Tensor, torch::Tensor> forward(torch::Tensor x) {
    torch::Tensor encoded = encoder->forward(x);
    torch::Tensor decoded = decoder->forward(encoded);
    return std::make_pair(encoded, decoded);
  }
};

#endif  //CXURITY_SRC_ENTITY_ML_AUTOENCODER_H_
