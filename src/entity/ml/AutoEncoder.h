#ifndef CXURITY_SRC_ENTITY_ML_AUTOENCODER_H_
#define CXURITY_SRC_ENTITY_ML_AUTOENCODER_H_

#include "../headers/pch.h"

struct Encoder : torch::nn::Module {
  torch::nn::Sequential layers;

  Encoder(uint8_t in, uint8_t maxCompression, uint8_t levels);
  torch::Tensor forward(torch::Tensor x);
};

struct Decoder : torch::nn::Module {
  torch::nn::Sequential layers;
  Decoder(uint8_t maxCompression, uint8_t out, uint8_t levels);

  torch::Tensor forward(torch::Tensor x);
};

struct AutoEncoder : torch::nn::Module {
  std::shared_ptr<Encoder> encoder;
  std::shared_ptr<Decoder> decoder;

  AutoEncoder(uint8_t in, uint8_t maxCompression, uint8_t levels);

  torch::Tensor forward(torch::Tensor x);
  static torch::nn::Sequential constructLayers(bool compressing, int in, int out, int levels);
};

#endif  //CXURITY_SRC_ENTITY_ML_AUTOENCODER_H_
