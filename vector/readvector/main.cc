// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 8月 13 18:56:36 2020 (+0800)
// Last-Updated: 四 8月 13 19:32:54 2020 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 3
// URL: http://wuhongyi.cn 

// 模板来自于 李晶

#include "UserClass.hh"
#include "TFile.h"
#include "TTree.h"
#include <iostream>

int main(int argc, char *argv[])
{
  if(argc < 2)
    {
      std::cout<< "eg. ./xxx  [run number]" <<std::endl;
      exit(1);
    }
  
  int N = atoi(argv[1]);

  auto filer = new TFile(TString::Format("/data/rootdata/run%d.root",N),"READ");
  auto treer = (TTree*)filer->Get("t");

  auto filew = new TFile(TString::Format("data%d.root",N),"RECREATE");
  auto treew = new TTree("t","xxx");

  auto it = new UserClass(treer);
  it->Loop(treew);

  treew->Write();
  filew->Close();
  
  return 0;
}

// 
// main.cc ends here
