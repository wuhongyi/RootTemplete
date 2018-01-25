// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 12月  8 19:21:20 2016 (+0800)
// Last-Updated: 四 1月 25 20:02:33 2018 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 17
// URL: http://wuhongyi.cn 

// 编译指令
// g++ `root-config --cflags --glibs` -l Spectrum  main.cc -o wu

#include "RVersion.h"//版本判断
#include "TApplication.h"
#include "TArrow.h"
#include "TAxis.h"
#include "TBenchmark.h"
#include "TBranch.h"
#include "TBrowser.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TColor.h"
#include "TCutG.h"
#include "TDatime.h"
#include "TError.h"
#include "TF1.h"
#include "TF2.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TFormula.h"
#include "TGaxis.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TLine.h"
#include "TList.h"
#include "TLorentzVector.h"
#include "TMarker.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TMatrixDEigen.h"
#include "TMultiGraph.h"
#include "TNtuple.h"
#include "TObject.h"
#include "TPad.h"
#include "TPaveLabel.h"
#include "TPaveStats.h"
#include "TPaveText.h"
#include "TRandom.h"
#include "TRandom1.h"
#include "TRandom2.h"
#include "TRandom3.h"
#include "TRint.h"
#include "TROOT.h"
#include "TSlider.h"
#include "TSpectrum.h"
#include "TSpectrum2.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTimer.h"
#include "TTimeStamp.h"
#include "TTree.h"
#include "TVector3.h"
#include "TVectorD.h"

// #define NDEBUG
#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char *argv[])
{
  // Create an interactive ROOT application
  TRint *theApp = new TRint("Rint", &argc, argv);

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  int run;
  int run1,run2;
  if(argc != 2 && argc != 3)
    {
      std::cout<<"argc != 2 || argc != 3"<<std::endl;
      return 1;
    }
  else
    {
      std::stringstream ss;
      if(argc == 2)
	{
	  ss.clear();
	  ss<<argv[1];
	  ss>>run;
	  std::cout<<"run number: "<<run<<std::endl;
	}

      if(argc == 3)
	{
	  ss.clear();
	  ss<<argv[1];
	  ss>>run1;
	  ss.clear();
	  ss<<argv[2];
	  ss>>run2;
	  std::cout<<"run number start: "<<run1 <<"  stop: "<<run2<<std::endl;
	}
    }
  
  //初始参数
  TString TreeName="tree";//这里为要处理的文件中 tree name
  TChain *fChain=new TChain(TreeName);
  fChain->SetCacheSize(100*1024*1024);
  TString dir = gSystem->DirName(__FILE__);//获取当前文件main.cc所在路径 
  dir.ReplaceAll("/./","/");

  //=======================================================
  //以下两个选一个： 手动填写root文件所在路径或者直接使用当前文件所在路径
  // gSystem->Setenv("Dir","/run/media/wuhongyi/RIBLLDATA/rootfile/exp2");//手动填写路径
  gSystem->Setenv("Dir",dir);//当前文件路径

  //=======================================================

  if(argc == 2)
    {
      fChain->Add(TString::Format("$Dir/run%04d.root",run).Data());//用户需要修改文件名
    }

  if(argc == 3)
    {
      for(int i = run1 ; i<= run2 ; ++i)
	{
	  std::cout<<i<<std::endl;
	  TString infile = TString::Format("$Dir/run%04d.root",i);//用户需要修改文件名
	  fChain->Add(infile);
	}
    }
  
  // fChain->Print();

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  // 用户需要替换以下的数据结构
  
  // Declaration of leaf types
  Double_t        dxse[3][16];
  Double_t        dyse[3][16];
  Double_t        dxle[3][16];
  Double_t        dyle[3][16];
  Double_t        t2;
  
  // List of branches
  TBranch        *b_dxse;   //!
  TBranch        *b_dyse;   //!
  TBranch        *b_dxle;   //!
  TBranch        *b_dyle;   //!
  TBranch        *b_t2;   //!

  fChain->SetBranchAddress("dxse", dxse, &b_dxse);
  fChain->SetBranchAddress("dyse", dyse, &b_dyse);
  fChain->SetBranchAddress("dxle", dxle, &b_dxle);
  fChain->SetBranchAddress("dyle", dyle, &b_dyle);
  fChain->SetBranchAddress("t2", &t2, &b_t2);
  
  std::cout <<std::endl<< "=== Running Hongyi Wu Analysis ===" << std::endl;

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
  gBenchmark->Start("tree");//计时开始
  
  Long64_t TotalEntry = fChain->GetEntries();//拿到TChain中总entry行数
  
  std::cout<<"TotalEntry:  "<<TotalEntry<<std::endl;

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  for (Long64_t entry = 0; entry < TotalEntry; ++entry)
    {//循环处理从这里开始
      fChain->GetEvent(entry);//这个是重点，拿到TChain中第entry行数据
      if(entry % 10000 == 0) std::cout<<"Process "<<entry<<" / "<<TotalEntry<<std::endl;
      // 用户需要在这里补充处理每个entry的程序


      
    }//循环处理到这里结束
  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


  std::cout<<std::endl;
  gBenchmark->Show("tree");//计时结束并输出时间
  
  // and enter the event loop...
  theApp->Run();
  delete theApp;
  return 0;
}

// 
// main.cc ends here
