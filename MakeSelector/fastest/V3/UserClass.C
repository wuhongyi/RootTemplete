// UserClass.C --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 二 6月  5 04:03:08 2018 (+0800)
// Last-Updated: 二 6月  5 04:42:45 2018 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 14
// URL: http://wuhongyi.cn 

#define  UserClass_cxx
#include "UserClass.h"
#include "DataClass.h"
#include "DataClass.C"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UserClass::Init(TTree *tree)
{
  DataClass::Init(tree);
}

Bool_t UserClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

  
   return kTRUE;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UserClass::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   gBenchmark->Start("tree");//计时开始
   CountEntry = 0;
   Percent = 0;
   PercentOld = 100;
   // ----------------------------------------

   
}

void UserClass::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t UserClass::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either DataClass::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

  CountEntry++;//自加，每执行一次自加一
  ProgressBar(CountEntry,fChain->GetEntries());
  // ----------------------------------------


  
  // b_evte->GetEntry(entry);
  // std::cout<<entry<<"  "<<evte<<std::endl;

  
   return kTRUE;
}

void UserClass::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void UserClass::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.


  
   // ----------------------------------------
  std::cout<<std::endl;
  gBenchmark->Show("tree");//计时结束并输出时间
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UserClass::ProgressBar(Long64_t i,Long64_t total)
{
  Percent = (int)(100.0*(double)i/(double)total);
  if(Percent != PercentOld)
    {
      std::cout<<"\r"<<Percent<<"% [";

      int temp = (int)((double)Percent/(double)100 * 50);
      for (int i = 0; i < temp-1; ++i)
	{
	  std::cout << "=";
	}
      std::cout<<">";
      for (int j = 0; j < 50-temp-1; ++j)
	{
	  std::cout<<" ";
	}
      std::cout<<"]  ";
    }
  else
    {
      std::cout << "\r" ;
    }
  std::cout << flush;
  PercentOld = Percent;
}


// 
// UserClass.C ends here
