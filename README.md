# Sequential-LRF
Employing sequential Low Rank Factorization to DNNs

This project aims at compressing a DNN trained with [KALDI ASR-toolikt]( http://kaldi-asr.org/) using sequential low-rank-factorization with SVD.

# How to use?
The project is made so that the lease possible changes need to be made in the Kaldi set up:
  
1. Download [Kaldi](https://github.com/kaldi-asr/kaldi)
  
2. Prior to installing, you need to add a method (which is a getter) to the Nnet class in /kaldi/src/nnet2/nnet-nnet.h:

      ```c
      // nnet2/nnet-nnet.h
      .
      .
      .
      class Nnet{
      public:
      std::vector<Component*> & GetComponentPure() {
      return components_;
      }
      .
      .
      .
      } // End of class Nnet
     ```
    
    
    
