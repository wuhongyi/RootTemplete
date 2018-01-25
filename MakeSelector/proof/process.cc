// process.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 7月  5 09:31:13 2015 (+0800)
// Last-Updated: 三 3月 16 23:21:54 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 78
// URL: http://wuhongyi.cn 

#include <unistd.h>
#include <fcntl.h>

#include<cstdlib>
#include <cstdio>
#include <iostream>
#include "TChain.h"
#include "TString.h"
#include "TSystem.h"
#include "TProof.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//特别说明：每次执行都需要 root process.cc
void process()
{
  //初始参数
  TString TreeName="cond_data";//这里为要处理的文件中 tree name
  TString Macro="Analysis";//将会在当前文件所在目录生成 XXXXXX.h XXXXXX.C 两个文件
  Int_t type=1;//0表示普通执行  1表示编译成动态库来执行。
  TProof::Open("workers=4");//线程数
  // create first the chain with all the files
  TChain *chain=new TChain(TreeName);
  // eventually, start Proof Lite on cores
  chain->SetProof();
  std::cout << "Creating the chain" << std::endl;
  chain->SetCacheSize(20*1024*1024);
  TString dir = gSystem->DirName(__FILE__);//获取当前文件路径
  dir.ReplaceAll("/./","/");
  // std::cout<<dir<<std::endl;
  //=======================================================
  //以下两个选一个： 手动填写root文件所在路径 或 者直接使用当前文件所在路径
  // gSystem->Setenv("Dir","/home/wuhongyi");//手动填写路径
  gSystem->Setenv("Dir",dir);//当前文件路径
  //=======================================================
  //将要处理的文件放在这里，支持tree名相同的多个结构相同的文件。特别适合用于Geant4多线程模拟的输出文件处理。
  chain->Add("$Dir/conductivity*.root");//采用通配符
  // chain->Add("$Dir/dstarmb.root");
  // chain->Add("$Dir/dstarp1a.root");
  // chain->Add("$Dir/dstarp1b.root");
  // chain->Add("$Dir/dstarp2.root");

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  std::cout <<std::endl<< "=== Run Hongyi Wu Analysis ===" << std::endl;

   TString MacroFileC=Macro+".C";
   TString MacroFileH=Macro+".h";
   if(access(MacroFileC,F_OK)!=-1 && access(MacroFileH,F_OK)!=-1)  
     {  
       std::cout<<"File "<<MacroFileC <<" exists !  Start Process()"<<std::endl;
       if (type == 0)
	 {
	   chain->Process(MacroFileC);
	 }
       else if (type == 1)   {
	 // use AClic  add a + at the end
	 MacroFileC += "+";
	 chain->Process(MacroFileC);
       }
       else if (type == 2) {//预留其它执行
	 std::cout<<"type error !"<<std::endl;
	 exit(1);
       }
     }  
   else  
     {  
       std::cout<<"File "<<MacroFileC <<" no exists !  Start generate files :"<<std::endl;
       if(access(MacroFileC,F_OK)==0) system("rm "+MacroFileC);
       if(access(MacroFileH,F_OK)==0) system("rm "+MacroFileH);
       //使用老版的"selector"模式
       chain->MakeSelector(Macro);//ROOT6.06以下版本
       // chain->MakeSelector(Macro,"=legacy");//ROOT6.06及以上版本
       //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
       //使用6.06版本提供的"Reader"模式
       // chain->MakeSelector(Macro);
       //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
       std::cout<<"Please fill processing function in the file "<<MacroFileH<<" and "<<MacroFileC<<" ."<<std::endl;
       std::cout<<"Please run again ! "<<std::endl;
     }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 时间信息输出：
// 在.h
// TDatime tBegin, tNow;
// 在.C
// 在Begin(TTree * /*tree*/)
// tBegin.Set(); printf("*==* ---------- Begin of Master Job ----------");
// tBegin.Print();
// 在Terminate()
// tNow.Set(); printf("*==* ---------- End of Master Job ---------- ");
// tNow.Print();

// 继承于TObject的可放进TSelectorList，多线程跑完自己合并，然后可在Terminate()拿出来
// 在SlaveBegin(TTree * /*tree*/)
//// add all booked histograms to output list(only really needed for PROOF)
// fOutput->AddAll(gDirectory->GetList());

// 在Terminate()
// //retrieve output from output list
// h= dynamic_cast<TH1F *>(fOutput->FindObject("h"));

// 
// process.cc ends here

















