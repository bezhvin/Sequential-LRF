#ifndef SEQ_H
#define SEQ_H

namespace kaldi {
namespace nnet2 {

class Affine2FixedAffine: public Nnet,protected  FixedAffineComponent{
Nnet *nnet2_;
int32 id;
public:
Affine2FixedAffine(Nnet *a, int32 i):Nnet(),nnet2_(a),id(i){} // constructor to initialize nnet2_ .
~Affine2FixedAffine(){}
int32 Getid(){return id;}

void  FixIt() {
  FixedAffineComponent * newcomp=new FixedAffineComponent;
  std::vector<Component*> &component2_=(nnet2_->GetComponentPure());
  AffineComponent *c = static_cast<AffineComponent*>(component2_[id]);
   if (c != NULL) {
        newcomp->SetParams(c->LinearParams(),c->BiasParams());
        component2_[id]=newcomp;
      nnet2_->SetIndexes();
      nnet2_->Check();
      
        }
   else {
     cout << "WARNING: No component was fixed.... ";
     }
}

};

}
}
#endif

