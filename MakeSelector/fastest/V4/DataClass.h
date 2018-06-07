//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun  7 09:12:42 2018 by ROOT version 6.12/06
// from TChain tree/
//////////////////////////////////////////////////////////

#ifndef DataClass_h
#define DataClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

class DataClass : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
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
   UShort_t        ltra;
   UShort_t        data[1];   //[ltra]
   UShort_t        dt[1];   //[ltra]
   Int_t           nevt;

   // List of branches
   TBranch        *b_sr;   //!
   TBranch        *b_pileup;   //!
   TBranch        *b_outofr;   //!
   TBranch        *b_cid;   //!
   TBranch        *b_sid;   //!
   TBranch        *b_ch;   //!
   TBranch        *b_evte;   //!
   TBranch        *b_ts;   //!
   TBranch        *b_ets;   //!
   TBranch        *b_cfd;   //!
   TBranch        *b_cfdft;   //!
   TBranch        *b_cfds;   //!
   TBranch        *b_trae;   //!
   TBranch        *b_leae;   //!
   TBranch        *b_gape;   //!
   TBranch        *b_base;   //!
   TBranch        *b_qs;   //!
   TBranch        *b_ltra;   //!
   TBranch        *b_data;   //!
   TBranch        *b_dt;   //!
   TBranch        *b_nevt;   //!

   DataClass(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~DataClass() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(DataClass,0);
};

#endif

#ifdef DataClass_cxx
void DataClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("sr", &sr, &b_sr);
   fChain->SetBranchAddress("pileup", &pileup, &b_pileup);
   fChain->SetBranchAddress("outofr", &outofr, &b_outofr);
   fChain->SetBranchAddress("cid", &cid, &b_cid);
   fChain->SetBranchAddress("sid", &sid, &b_sid);
   fChain->SetBranchAddress("ch", &ch, &b_ch);
   fChain->SetBranchAddress("evte", &evte, &b_evte);
   fChain->SetBranchAddress("ts", &ts, &b_ts);
   fChain->SetBranchAddress("ets", &ets, &b_ets);
   fChain->SetBranchAddress("cfd", &cfd, &b_cfd);
   fChain->SetBranchAddress("cfdft", &cfdft, &b_cfdft);
   fChain->SetBranchAddress("cfds", &cfds, &b_cfds);
   fChain->SetBranchAddress("trae", &trae, &b_trae);
   fChain->SetBranchAddress("leae", &leae, &b_leae);
   fChain->SetBranchAddress("gape", &gape, &b_gape);
   fChain->SetBranchAddress("base", &base, &b_base);
   fChain->SetBranchAddress("qs", qs, &b_qs);
   fChain->SetBranchAddress("ltra", &ltra, &b_ltra);
   fChain->SetBranchAddress("data", &data, &b_data);
   fChain->SetBranchAddress("dt", &dt, &b_dt);
   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
}

Bool_t DataClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef DataClass_cxx
