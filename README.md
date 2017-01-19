# Sequential Low Rank Factorization (LRF):

LRF is one of the compressin techniques employed to reduce the size of the DNNs. The first attempts in using this scheme in acoustic modeling were presented in [[1](http://ieeexplore.ieee.org/document/6638949/)] and [[2](https://www.microsoft.com/en-us/research/wp-content/uploads/2013/01/svd_v2.pdf)].

This project aims at compressing a DNN trained with [KALDI ASR-toolikt]( http://kaldi-asr.org/) using sequential low-rank-factorization with SVD. Noting that kaldi has some LRF implementations as [nnet-am-limit-rank-final.cc](https://github.com/kaldi-asr/kaldi/blob/master/src/nnet2bin/nnet-am-limit-rank-final.cc) and [nnet-am-limit-rank.cc](https://github.com/kaldi-asr/kaldi/blob/master/src/nnet2bin/nnet-am-limit-rank.cc). These availabe scripts, however, does not allow us to apply SVD on any arbitrary linear weight layer of a DNN. Indeed, this could be accomplished with small changes of the current methods of the corresponding classes; however, this repository includes scripts allowing to have such functionality without messing with Kaldi files (at least not a lot!).

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
    
    
    
