// main.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 6月  7 05:45:42 2018 (+0800)
// Last-Updated: 四 6月  7 09:25:53 2018 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 14
// URL: http://wuhongyi.cn 

#include "UserClass.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "TChain.h"
#include "TString.h"
#include "TSystem.h"
#include "RVersion.h"//版本判断

//吴鸿毅(wuhongyi@qq.com) 单线程-多文件-数据处理模板
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char *argv[])
{
  if(argc < 2)
    {
      std::cout<< "argc:" << argc <<std::endl;
      std::cout<<"./wu option"<<std::endl;
      std::cout<<"./wu regenerate  mean remove Dataclass and regenerate. It need make clean;make"<<std::endl;
      gSystem->Exit(1);
    }
  
  // int N = atoi(argv[1]);//cstdlib
  

  
  //初始参数
  TString TreeName = "tree";//这里为要处理的文件中 tree name，必须修改！！！

  TChain *chain = new TChain(TreeName);
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
  chain->Add("$Dir/*.root");//采用通配符
  // chain->Add("$Dir/why.root");

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  Int_t typeSelector = 0;//0表示老版的"selector"模式   1表示6.06.00开始提供的"Reader"模式

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
#if ROOT_VERSION_CODE < ROOT_VERSION(6,0,0)
  std::cout<<"-_- ROOT 软件版本太低，请使用6.00.00 及以上版本 ##"<<std::endl;
  gSystem->Exit(1);
#endif
  std::cout <<std::endl<< "=== Run Hongyi Wu Analysis ===" << std::endl;

  TString Macro = "DataClass";
  TString MacroFileC = Macro+".C";
  TString MacroFileH = Macro+".h";

  if(TString(argv[1]) == "regenerate")
    {
      gSystem->Exec("rm -f "+MacroFileC);
      gSystem->Exec("rm -f "+MacroFileH);
      
      std::cout<<"....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......"<<std::endl;
      std::cout<<"@@ Please fill processing function in the file UserClass.h and UserClass.C ."<<std::endl;
      std::cout<<"@@ Please  make clean;make "<<std::endl;
      std::cout<<"@@ Please run again ! "<<std::endl;
      
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
    }
  else
    {
      UserClass *userclass = new UserClass;
      chain->Process(userclass,argv[1]);
    }    
  
  return 0;
}

// 
// main.cc ends here
