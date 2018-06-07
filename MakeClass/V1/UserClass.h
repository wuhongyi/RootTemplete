// UserClass.h --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 6月  7 09:41:12 2018 (+0800)
// Last-Updated: 四 6月  7 09:59:12 2018 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn

#ifndef _USERCLASS_H_
#define _USERCLASS_H_

#include "DataClass.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class TTree;

class UserClass : public DataClass
{
 public:
  UserClass(TTree *tree);
  virtual ~UserClass();

  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  virtual Int_t    Cut(Long64_t entry);
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  



  
};

#endif /* _USERCLASS_H_ */

// 
// UserClass.h ends here
