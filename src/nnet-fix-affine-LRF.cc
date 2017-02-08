// This code takes a DNN as an input, looks at weight layers
//  and if two linear layers are in row, the first one will be 
//  freezed. This is used when a DNN with factorized layers 
//  is used for adaptation



#include "base/kaldi-common.h"
#include "util/common-utils.h"
#include "nnet2/nnet-limit-rank.h"
#include "nnet2/am-nnet.h"
#include "hmm/transition-model.h"
#include "tree/context-dep.h"
#include "nnet2/fix-layer-LRF.h"
#include <typeinfo>



int main(int argc, char* argv[]){

try {
    using namespace kaldi;
    using namespace kaldi::nnet2;
    typedef kaldi::int32 int32;

    const char *usage =
        "Two arguments are required, the first one is an input DNN with \n"
        "factorized layers (two linear layers in row), and the second \n"
        "one is the output DNN with less updatable affinecomponents. \n"
        "Usage: nnet-fix-affine-LRF  final_factorized.mdl fixed_factorized.mdl\n";

      bool binary_write=true;
      vector<int32> layerid;
      ParseOptions po(usage);
      po.Register("binary", &binary_write, "Write output in binary mode");
      po.Read(argc, argv);
      if (po.NumArgs()!=2){
        po.PrintUsage();
        exit(1);
        }

     string nnet_rxfilename=po.GetArg(1),
       nnet_wxfilename=po.GetArg(2);


    TransitionModel trans_model;
    AmNnet am_nnet; 
    {
    bool binary;
    Input ki(nnet_rxfilename, &binary); 
    trans_model.Read(ki.Stream(), binary);
    am_nnet.Read(ki.Stream(), binary); 
    }


   
    int32 count=0;
    for (int32 i=0; i<am_nnet.GetNnet().NumComponents(); i++)
       if (dynamic_cast<AffineComponent*>(&(am_nnet.GetNnet().GetComponent(i))) && dynamic_cast<AffineComponent*>(&(am_nnet.GetNnet().GetComponent(i+1)))) {
               Affine2FixedAffine ans(&am_nnet.GetNnet(),i);
               ans.FixIt();
               count++;
               }


     if (count==0) cout << "WARNING: nothing has changed in the new model."
               << "Make sure the model is factorized.";
     
 {
      Output ko(nnet_wxfilename, binary_write);
      trans_model.Write(ko.Stream(), binary_write);
      am_nnet.Write(ko.Stream(), binary_write);
    }
    KALDI_LOG << "New model copied to " << nnet_wxfilename;
    return 0;


} catch (const std::exception &e){
  cerr << e.what() << endl;
  return -1;
  }

}
