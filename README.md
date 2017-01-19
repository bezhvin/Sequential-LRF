# Sequential Low Rank Factorization (LRF):

LRF is one of the compressin techniques employed to reduce the size of the DNNs. The first attempts in using this scheme in acoustic modeling are presented in [[1](https://36e9b848-a-62cb3a1a-s-sites.googlegroups.com/site/tsainath/tsainath_lowRank.pdf?attachauth=ANoY7crXw4iHzBJDj-xd8VL9wXWdx67-9Y-aPn712j5mt-uvkiBN5ftO4uNQCgIxNer8LM4obfhwTPUpXDB4XwGNyJ49YlWEKonZ3_tfdPwmDfNZKgtPXIpLIhyayPwOe4vQEB81FgWoPLhNQrTCUR0NxFN-YGgGzsLQr0MqA93s2gPQ83kDF8QWQN0-x3qJh8LU9mN7RADezfbZIU0o-N3EXwcovtQGSg%3D%3D&attredirects=0)] and [[2](https://www.microsoft.com/en-us/research/wp-content/uploads/2013/01/svd_v2.pdf)].

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
    
    
    
