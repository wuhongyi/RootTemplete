// UserClass.hh --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 8月 13 19:03:26 2020 (+0800)
// Last-Updated: 四 8月 13 19:20:10 2020 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 2
// URL: http://wuhongyi.cn 

#ifndef _USERCLASS_H_
#define _USERCLASS_H_

#include "TTree.h"
#include <vector>

#define MAXTRACELEN 65536

typedef struct rawXIA
{
   Short_t         sr;
   Bool_t          pileup;
   Bool_t          outofr;
   Short_t         cid;
   Short_t         sid;
   Short_t         ch;
   UShort_t        evte;
   Long64_t        ts;
   Long64_t        ets;
   Short_t         cfd;
   Bool_t          cfdft;
   Short_t         cfds;
   UInt_t          trae;
   UInt_t          leae;
   UInt_t          gape;
   Double_t        base;
   UInt_t          qs[8];
   // UShort_t        ltra;
   // UShort_t        data[MAXTRACELEN];   //[ltra]
   // UShort_t        dt[MAXTRACELEN];   //[ltra]
   Int_t           nevt;

} rawXIA;


class UserClass
{
public:
  UserClass() {treer = NULL; treew = NULL;}
  UserClass(TTree *tr);
  virtual ~UserClass();

  void Init();
  void NewBranch();
  void Loop(TTree *tw);


  Double_t x1,x2,x3;
  
  TTree *treer;
  TTree *treew;

  std::vector<rawXIA>* br_xia;
};

#endif /* _USERCLASS_H_ */

// 
// UserClass.hh ends here
