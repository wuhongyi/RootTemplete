//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Mar  9 07:56:11 2014 by ROOT version 5.34/09
// from TTree dna/dnaphysics
// found on file: dna.root
//////////////////////////////////////////////////////////

#ifndef wuhongyi_h
#define wuhongyi_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class wuhongyi : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Double_t        flagParticle;
   Double_t        flagProcess;
   Double_t        x;
   Double_t        y;
   Double_t        z;
   Double_t        totalEnergyDeposit;
   Double_t        stepLength;
   Double_t        kineticEnergyDifference;

   // List of branches
   TBranch        *b_flagParticle;   //!
   TBranch        *b_flagProcess;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_totalEnergyDeposit;   //!
   TBranch        *b_stepLength;   //!
   TBranch        *b_kineticEnergyDifference;   //!

   wuhongyi(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~wuhongyi() { }
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

   TFile* f;
   TTree* t;
   double fParticle;
   double fProcess;
   double px;
   double py;
   double pz;
   double tEnergyDeposit;
   double sLength;
   double kEnergyDifference;
   ClassDef(wuhongyi,0);
};

#endif

#ifdef wuhongyi_cxx
void wuhongyi::Init(TTree *tree)
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

   fChain->SetBranchAddress("flagParticle", &flagParticle, &b_flagParticle);
   fChain->SetBranchAddress("flagProcess", &flagProcess, &b_flagProcess);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("totalEnergyDeposit", &totalEnergyDeposit, &b_totalEnergyDeposit);
   fChain->SetBranchAddress("stepLength", &stepLength, &b_stepLength);
   fChain->SetBranchAddress("kineticEnergyDifference", &kineticEnergyDifference, &b_kineticEnergyDifference);
}

Bool_t wuhongyi::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef wuhongyi_cxx
