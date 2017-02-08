// With this code, you can factorize a specific layer,
// layers are considered to be indexed from 0; thus, the 0th layer is an input layer
// which we skip in this work. This is used for layerwise factorization.



#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "nnet2/nnet-limit-rank.h"
#include "nnet2/am-nnet.h"
#include "hmm/transition-model.h"
#include "tree/context-dep.h"
#include "nnet2/nnet-limit-rank-layer.h"



int main(int argc, char* argv[]){

try {
    using namespace kaldi;
    using namespace kaldi::nnet2;
    typedef kaldi::int32 int32;

    const char *usage =
        "It employs low-rank factorization for a specific layer. \n"
        "Usage: nnet-am-limit-rank-layer --dim=200 --layer=1 final.mdl final_factorized.mdl\n";
    
    bool binary_write = true;
    NnetLimitRankOpts config;
    int32 dim = 200;
    int32 layer=1;
    std::vector<int32> layerid;
        
    ParseOptions po(usage);
    po.Register("binary", &binary_write, "Write output in binary mode");
    po.Register("dim", &dim, "Dimension to retain");
    po.Register("layer", &layer, "Layer number to factorize");
    po.Read(argc, argv);
    config.Register(&po);
    config.num_threads=1;
    if (po.NumArgs()!=2){
    po.PrintUsage();
    exit(1);
    }

    std::string nnet_rxfilename = po.GetArg(1),
    nnet_wxfilename = po.GetArg(2);
  
    TransitionModel trans_model;
    AmNnet am_nnet;
    {
    bool binary;
    Input ki(nnet_rxfilename, &binary);
    trans_model.Read(ki.Stream(), binary);
    am_nnet.Read(ki.Stream(), binary);
    am_nnet.Info();
    } 

   for (int32 i = 0; i < am_nnet.GetNnet().NumComponents(); i++){
       if (dynamic_cast<const AffineComponent*>(&(am_nnet.GetNnet().GetComponent(i))) != NULL)
          layerid.push_back(i);
       }
   if (layer > layerid.size()-1)
    KALDI_ERR << "The network does not have " << layer 
              << " Affinecomponents (Max: " << layerid.size()-1
              << ").";  
 
    SEQ NnetSeq(&am_nnet.GetNnet());  // Ampersand is required to get the ADDRESS.
//    Vector<BaseFloat> out=NnetSeq.GetSingularValues(layerid[layer]);
    NnetSeq.LimitRankOfLayer2(dim,layerid[layer]);
 

   
    
    
         
  
     {
      Output ko(nnet_wxfilename, binary_write);
      trans_model.Write(ko.Stream(), binary_write);
      am_nnet.Write(ko.Stream(), binary_write);
    }
    KALDI_LOG << "Limited rank of neural net " << nnet_rxfilename
              << " and copied to " << nnet_wxfilename;
    return 0;
} catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return -1;
  }



}


