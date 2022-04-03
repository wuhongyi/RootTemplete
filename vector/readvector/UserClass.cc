// UserClass.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 8月 13 19:03:40 2020 (+0800)
// Last-Updated: 二 10月  6 12:35:37 2020 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 4
// URL: http://wuhongyi.cn 

#include "UserClass.hh"
#include <iostream>

UserClass::UserClass(TTree *tr)
{
  treer = tr;

  Init();
}

UserClass::~UserClass()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UserClass::Init()
{
  if(treer == NULL) return;
  treer->SetBranchAddress("xia",&br_xia);
}

void UserClass::NewBranch()
{
  treew->Branch("x1",&x1,"x1/D");
  treew->Branch("x2",&x2,"x2/D");
  treew->Branch("x3",&x3,"x3/D");
}

void UserClass::Loop(TTree *tw)
{
  if(tw == NULL) return;
  treew = tw;
  NewBranch();


  
  Long64_t TotalEntry = treer->GetEntries();
  for(Long64_t i = 0 ; i < TotalEntry; i++)//loop
    {
      treer->GetEntry(i);
      if(i % 10000 == 0) std::cout<<"Process "<<i<<" / "<<TotalEntry<<std::endl;

      if(br_xia->size())
	{
	  x1 = (*br_xia)[0].sr;
	  x2 = (*br_xia)[0].ch;
	  x3 = (*br_xia)[0].evte;
	}

      treew->Fill();
    }
  
}


// 
// UserClass.cc ends here










