// process.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 日 7月  5 09:31:13 2015 (+0800)
// Last-Updated: 二 6月  5 04:41:38 2018 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 96
// URL: http://wuhongyi.cn 

#include <unistd.h>//要求6.00.00及以上才能被调用
#include <fcntl.h>//要求6.0.0及以上才能被调用
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "TChain.h"
#include "TString.h"
#include "TSystem.h"
#include "RVersion.h"//版本判断

//吴鸿毅(wuhongyi@qq.com) 单线程-多文件-数据处理模板
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//特别说明：每次执行都需要 root process.cc
void process()
{
  //初始参数
  TString TreeName = "tree";//这里为要处理的文件中 tree name，必须修改！！！
  
  TString Macro = "DataClass";//将会在当前文件所在目录生成 DataClass.h DataClass.C 两个文件
  Int_t type = 0;//0表示普通执行  1表示编译成动态库来执行。  当前只能采用 0
  Int_t typeSelector = 0;//0表示老版的"selector"模式   1表示6.06.00开始提供的"Reader"模式
  // create first the chain with all the files
  TChain *chain = new TChain(TreeName);
  std::cout << "Creating the chain" << std::endl;
  chain->SetCacheSize(20*1024*1024);
  TString dir = gSystem->DirName(__FILE__);//获取当前文件路径
  dir.ReplaceAll("/./","/");
  std::cout<<dir<<std::endl;
  //=======================================================
  //以下两个选一个： 手动填写root文件所在路径 或 者直接使用当前文件所在路径
  // gSystem->Setenv("Dir","/home/wuhongyi");//手动填写路径
  gSystem->Setenv("Dir",dir);//当前文件路径
  //=======================================================
  //将要处理的文件放在这里，支持tree名相同的多个结构相同的文件。特别适合用于Geant4多线程模拟的输出文件处理。
  chain->Add("$Dir/*.root");//采用通配符
  // chain->Add("$Dir/why.root");

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#if ROOT_VERSION_CODE < ROOT_VERSION(6,0,0)
  std::cout<<"-_- ROOT 软件版本太低，请使用6.00.00 及以上版本 ##"<<std::endl;
  gSystem->Exit(1);
#endif

  std::cout <<std::endl<< "=== Run Hongyi Wu Analysis ===" << std::endl;

   TString MacroFileC = Macro+".C";
   TString MacroFileH = Macro+".h";
   TString MacroUserClass = "UserClass.C";
   if(access(MacroFileC,F_OK)!=-1 && access(MacroFileH,F_OK)!=-1)  
     {  
       std::cout<<"^_^ File "<<MacroFileC <<" exists !  Start Process()"<<std::endl;
       if (type == 0)
	 {
	   chain->Process(MacroUserClass);
	 }
       else if (type == 1)   {
	 // use AClic  add a + at the end
	 MacroUserClass += "+";
	 chain->Process(MacroUserClass);
       }
       else if (type == 2) {//预留其它执行,比如传递option
	 std::cout<<"type error !"<<std::endl;
	 gSystem->Exit(1);
       }
     }  
   else  
     {  
       std::cout<<"-_- File "<<MacroFileC <<" no exists !  Start generate files :"<<std::endl;
       if(access(MacroFileC,F_OK)==0) system("rm "+MacroFileC);
       if(access(MacroFileH,F_OK)==0) system("rm "+MacroFileH);
       //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
       if(typeSelector == 0)
	 {
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,6,0)
	   chain->MakeSelector(Macro,"=legacy");//ROOT6.06及以上版本
#else
	   chain->MakeSelector(Macro);//ROOT6.06以下版本
#endif
	 }
       else
	 {
#if ROOT_VERSION_CODE < ROOT_VERSION(6,6,0)
	   std::cout<<"-_- ROOT 软件版本太低，请使用6.06.00 及以上版本 ##"<<std::endl;
	   gSystem->Exit(1);
#else
	   chain->MakeSelector(Macro);
#endif
	 }

       //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
       std::cout<<"....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......"<<std::endl;
       std::cout<<"@@ Please fill processing function in the file UserClass.h and UserClass.C ."<<std::endl;
       std::cout<<"@@ Please run again ! "<<std::endl;
     }  
   // gSystem->Exit(1);
}

// 
// process.cc ends here
