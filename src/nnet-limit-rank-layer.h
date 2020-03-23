#ifndef SEQ_H
#define SEQ_H

namespace kaldi {
namespace nnet2 {

class SEQ: public Nnet, public AffineComponent{
Nnet *nnet2_;
public:
SEQ(Nnet *a):Nnet(),nnet2_(a){} // constructor to initialize nnet2_ .
Nnet * GetSeqNnet(){return nnet2_;}

void  LimitRankOfLayer2(int32 dim, int32 comp_id) {
    
  std::vector<Component*> &component2_=(nnet2_->GetComponentPure());
  AffineComponent *a = NULL, *b = NULL,
        *c = dynamic_cast<AffineComponent*>(component2_[comp_id]); 
   if (c != NULL) {
      c->LimitRank(dim, &a, &b);
      delete c;
      component2_[comp_id] = a;
      component2_.insert(component2_.begin() + comp_id + 1, b);
      nnet2_->SetIndexes();
      nnet2_->Check();
      return;    
      }
     
       KALDI_ERR << "No affine component found.";
       exit(1);
      } 

 
    Vector<BaseFloat> GetSingularValues(int32 comp_id){
        std::vector<Component*> &component2_=(nnet2_->GetComponentPure());
        AffineComponent *c = dynamic_cast<AffineComponent*>(component2_[comp_id]); 
        if (c != NULL) {
           Matrix<BaseFloat> M (c->LinearParams());
           int32 rows = M.NumRows(), cols = M.NumCols(), rc_min = std::min(rows, cols);
           Vector<BaseFloat> s(rc_min);
           Matrix<BaseFloat> U(rows, rc_min), Vt(rc_min, cols);
          // Do the destructive svd M = U diag(s) V^T.  It actually outputs the transpose of V.
           M.DestructiveSvd(&s, &U, &Vt);
           SortSvd(&s, &U, &Vt); // Sort the singular values from largest to smallest.
          return s;
                       }
         KALDI_ERR << "No affine component found.";
       exit(1);
      }

  }; // END OF CLASS SEQ
  } // end of namespace nnet2
  } // end of namespace kaldi
 



#endif
