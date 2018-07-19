//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 22 10:58:29 2017 by ROOT version 5.34/36
// from TTree AutoTree/Automatic filled Tree
// found on file: root-files/run157.root
//////////////////////////////////////////////////////////

#ifndef temp_h
#define temp_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class temp {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UShort_t        TRIGGER;
   UShort_t        CONFIG;
   UShort_t        FLAG;
   UShort_t        FIELD;
   UShort_t        FIELD2;
   UShort_t        POLARITY;
   UShort_t        FREQ;
   UShort_t        FREQ2;
   UShort_t        LEFT_RIGHT;
   UShort_t        RF_ON;
   UShort_t        RF_OFF;
   UShort_t        CLOCK_1;
   UShort_t        CLOCK_2;
   UShort_t        TID3EVENT_UP;
   UShort_t        TID3EVENT;
   UShort_t        E_UP;
   UShort_t        E_DELTA_UP;
   UShort_t        E_DOWN;
   UShort_t        E_DELTA_DOWN;
   UShort_t        TAC_UP;
   UShort_t        TAC_DOWN;
   UShort_t        ADC_VOIE_6;
   UShort_t        ADC_VOIE_7;
   UShort_t        E_GAMMA1;
   UShort_t        E_GAMMA2;
   UShort_t        E_GAMMA3;
   UShort_t        ADC_VOIE_11;
   UShort_t        ADC_VOIE_12;
   UShort_t        ADC_VOIE_13;
   UShort_t        ADC_VOIE_14;
   UShort_t        ADC_VOIE_15;
   UShort_t        ED4;
   UShort_t        ED6;
   UShort_t        EXY;
   UShort_t        GH;
   UShort_t        GB;
   UShort_t        DH;
   UShort_t        DB;
   UShort_t        ADC_VOIE_23;
   UShort_t        THFD4;
   UShort_t        THFD6;
   UShort_t        THFXY;
   UShort_t        ADC_VOIE_27;
   UShort_t        ADC_VOIE_28;
   UShort_t        ADC_VOIE_29;
   UShort_t        ADC_VOIE_30;
   UShort_t        ADC_VOIE_31;

   // List of branches
   TBranch        *b_TRIGGER;   //!
   TBranch        *b_CONFIG;   //!
   TBranch        *b_FLAG;   //!
   TBranch        *b_FIELD;   //!
   TBranch        *b_FIELD2;   //!
   TBranch        *b_POLARITY;   //!
   TBranch        *b_FREQ;   //!
   TBranch        *b_FREQ2;   //!
   TBranch        *b_LEFT_RIGHT;   //!
   TBranch        *b_RF_ON;   //!
   TBranch        *b_RF_OFF;   //!
   TBranch        *b_CLOCK_1;   //!
   TBranch        *b_CLOCK_2;   //!
   TBranch        *b_TID3EVENT_UP;   //!
   TBranch        *b_TID3EVENT;   //!
   TBranch        *b_E_UP;   //!
   TBranch        *b_E_DELTA_UP;   //!
   TBranch        *b_E_DOWN;   //!
   TBranch        *b_E_DELTA_DOWN;   //!
   TBranch        *b_TAC_UP;   //!
   TBranch        *b_TAC_DOWN;   //!
   TBranch        *b_ADC_VOIE_6;   //!
   TBranch        *b_ADC_VOIE_7;   //!
   TBranch        *b_E_GAMMA1;   //!
   TBranch        *b_E_GAMMA2;   //!
   TBranch        *b_E_GAMMA3;   //!
   TBranch        *b_ADC_VOIE_11;   //!
   TBranch        *b_ADC_VOIE_12;   //!
   TBranch        *b_ADC_VOIE_13;   //!
   TBranch        *b_ADC_VOIE_14;   //!
   TBranch        *b_ADC_VOIE_15;   //!
   TBranch        *b_ED4;   //!
   TBranch        *b_ED6;   //!
   TBranch        *b_EXY;   //!
   TBranch        *b_GH;   //!
   TBranch        *b_GB;   //!
   TBranch        *b_DH;   //!
   TBranch        *b_DB;   //!
   TBranch        *b_ADC_VOIE_23;   //!
   TBranch        *b_THFD4;   //!
   TBranch        *b_THFD6;   //!
   TBranch        *b_THFXY;   //!
   TBranch        *b_ADC_VOIE_27;   //!
   TBranch        *b_ADC_VOIE_28;   //!
   TBranch        *b_ADC_VOIE_29;   //!
   TBranch        *b_ADC_VOIE_30;   //!
   TBranch        *b_ADC_VOIE_31;   //!

   temp(TTree *tree=0);
   virtual ~temp();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef temp_cxx
temp::temp(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root-files/run157.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root-files/run157.root");
      }
      f->GetObject("AutoTree",tree);

   }
   Init(tree);
}

temp::~temp()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t temp::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t temp::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void temp::Init(TTree *tree)
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
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("TRIGGER", &TRIGGER, &b_TRIGGER);
   fChain->SetBranchAddress("CONFIG", &CONFIG, &b_CONFIG);
   fChain->SetBranchAddress("FLAG", &FLAG, &b_FLAG);
   fChain->SetBranchAddress("FIELD", &FIELD, &b_FIELD);
   fChain->SetBranchAddress("FIELD2", &FIELD2, &b_FIELD2);
   fChain->SetBranchAddress("POLARITY", &POLARITY, &b_POLARITY);
   fChain->SetBranchAddress("FREQ", &FREQ, &b_FREQ);
   fChain->SetBranchAddress("FREQ2", &FREQ2, &b_FREQ2);
   fChain->SetBranchAddress("LEFT_RIGHT", &LEFT_RIGHT, &b_LEFT_RIGHT);
   fChain->SetBranchAddress("RF_ON", &RF_ON, &b_RF_ON);
   fChain->SetBranchAddress("RF_OFF", &RF_OFF, &b_RF_OFF);
   fChain->SetBranchAddress("CLOCK_1", &CLOCK_1, &b_CLOCK_1);
   fChain->SetBranchAddress("CLOCK_2", &CLOCK_2, &b_CLOCK_2);
   fChain->SetBranchAddress("TID3EVENT_UP", &TID3EVENT_UP, &b_TID3EVENT_UP);
   fChain->SetBranchAddress("TID3EVENT", &TID3EVENT, &b_TID3EVENT);
   fChain->SetBranchAddress("E_UP", &E_UP, &b_E_UP);
   fChain->SetBranchAddress("E_DELTA_UP", &E_DELTA_UP, &b_E_DELTA_UP);
   fChain->SetBranchAddress("E_DOWN", &E_DOWN, &b_E_DOWN);
   fChain->SetBranchAddress("E_DELTA_DOWN", &E_DELTA_DOWN, &b_E_DELTA_DOWN);
   fChain->SetBranchAddress("TAC_UP", &TAC_UP, &b_TAC_UP);
   fChain->SetBranchAddress("TAC_DOWN", &TAC_DOWN, &b_TAC_DOWN);
   fChain->SetBranchAddress("ADC_VOIE_6", &ADC_VOIE_6, &b_ADC_VOIE_6);
   fChain->SetBranchAddress("ADC_VOIE_7", &ADC_VOIE_7, &b_ADC_VOIE_7);
   fChain->SetBranchAddress("E_GAMMA1", &E_GAMMA1, &b_E_GAMMA1);
   fChain->SetBranchAddress("E_GAMMA2", &E_GAMMA2, &b_E_GAMMA2);
   fChain->SetBranchAddress("E_GAMMA3", &E_GAMMA3, &b_E_GAMMA3);
   fChain->SetBranchAddress("ADC_VOIE_11", &ADC_VOIE_11, &b_ADC_VOIE_11);
   fChain->SetBranchAddress("ADC_VOIE_12", &ADC_VOIE_12, &b_ADC_VOIE_12);
   fChain->SetBranchAddress("ADC_VOIE_13", &ADC_VOIE_13, &b_ADC_VOIE_13);
   fChain->SetBranchAddress("ADC_VOIE_14", &ADC_VOIE_14, &b_ADC_VOIE_14);
   fChain->SetBranchAddress("ADC_VOIE_15", &ADC_VOIE_15, &b_ADC_VOIE_15);
   fChain->SetBranchAddress("ED4", &ED4, &b_ED4);
   fChain->SetBranchAddress("ED6", &ED6, &b_ED6);
   fChain->SetBranchAddress("EXY", &EXY, &b_EXY);
   fChain->SetBranchAddress("GH", &GH, &b_GH);
   fChain->SetBranchAddress("GB", &GB, &b_GB);
   fChain->SetBranchAddress("DH", &DH, &b_DH);
   fChain->SetBranchAddress("DB", &DB, &b_DB);
   fChain->SetBranchAddress("ADC_VOIE_23", &ADC_VOIE_23, &b_ADC_VOIE_23);
   fChain->SetBranchAddress("THFD4", &THFD4, &b_THFD4);
   fChain->SetBranchAddress("THFD6", &THFD6, &b_THFD6);
   fChain->SetBranchAddress("THFXY", &THFXY, &b_THFXY);
   fChain->SetBranchAddress("ADC_VOIE_27", &ADC_VOIE_27, &b_ADC_VOIE_27);
   fChain->SetBranchAddress("ADC_VOIE_28", &ADC_VOIE_28, &b_ADC_VOIE_28);
   fChain->SetBranchAddress("ADC_VOIE_29", &ADC_VOIE_29, &b_ADC_VOIE_29);
   fChain->SetBranchAddress("ADC_VOIE_30", &ADC_VOIE_30, &b_ADC_VOIE_30);
   fChain->SetBranchAddress("ADC_VOIE_31", &ADC_VOIE_31, &b_ADC_VOIE_31);
   Notify();
}

Bool_t temp::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void temp::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t temp::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef temp_cxx
