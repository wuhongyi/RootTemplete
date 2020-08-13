// raw2vector.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 四 8月 13 18:26:35 2020 (+0800)
// Last-Updated: 四 8月 13 18:53:17 2020 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 1
// URL: http://wuhongyi.cn 

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


void raw2vector()
{

  std::vector<rawXIA> rawxia_vec;
  rawXIA rawxia;

  TFile *filew = new TFile("output.root","RECREATE");
  if(!filew->IsOpen())
    {
      std::cout<<"Can't open root file"<<std::endl;
    }
 
  // filew->ls("");
  filew->cd();
  TTree *treew = new TTree("t","Hongyi Wu Data");

  treew->Branch("xia",&rawxia_vec);

  
  for (int i = 0; i < 10000; ++i)
    {
      rawxia_vec.clear();

      int mhit = int(gRandom->Rndm()*10+1);
      for (int j = 0; j < mhit; ++j)
	{
	  rawxia.sr = 100;
	  rawxia.ch = gRandom->Rndm()*15;
	  rawxia.evte = gRandom->Rndm()*65535;
	  rawxia.ts = 1000*i+100*j;
	  rawxia.nevt = i;
	  rawxia_vec.push_back(rawxia);
	}

      treew->Fill();//loop
    }


 


  filew->cd();
  treew->Write();
  filew->Close();

}

// 
// raw2vector.cc ends here










