//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 25 17:36:08 2016 by ROOT version 5.34/04
// from TTree AutoTree/Automatic filled Tree
// found on file: DataFiles/r0071.root
//////////////////////////////////////////////////////////

#ifndef NMR_h
#define NMR_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <TH2.h>
#include <iostream>
#include <set>
#include <vector>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class NMR {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UShort_t        E_Up;
   UShort_t        E_deltaUp;
   UShort_t        E_Down;
   UShort_t        E_deltaDown;
   UShort_t        TAC_Up;
   UShort_t        TAC_Down;

   UShort_t        TRIGGER;
   UShort_t        CONFIG;
   UShort_t        FLAG;
   UShort_t        FIELD;
   UShort_t        FIELD2;
   UShort_t        POLARITY;
   UShort_t        FREQ;
   UShort_t        FREQ2;
   UShort_t        RF_ON;
   UShort_t        RF_OFF;

   //some variables for near-line analysis
   double FieldAvgHP;
   double FieldAvgCenterBefore; //magnetic field at the center position, calibrated before the run
   double FieldAvgCenterAfter; //magnetic field at the center position, calibrated after the run
   double FieldAvgCenter; //magnetic field at the center position, average of the previous two
   double FitCent, FitCentError, FitAmp, FitAmpError;
   int NumFreq;
   vector<double> VecAsymm, VecAsymmError;
   int CtsUp[5000], CtsDown[5000];
   int MaxAsymmFreq;
   Long64_t time;
   std::set<int> freqset;
   std::set<int>::iterator itfreqset;
   TGraphErrors *gSpec;

   //parameters read from input file
   int NMRorNQR; //0: NMR, 1: NQR
   int IfField; //0: no requirement on field readout, 1: require non-zero field readout
   int II2; //nuclear spin x 2
   int EUpMin, EUpMax;
   int EDeltaUpMin, EDeltaUpMax;
   int TACUpMin, TACUpMax;
   int EDownMin, EDownMax;
   int EDeltaDownMin, EDeltaDownMax;
   int TACDownMin, TACDownMax;

   //parameters read from fitting input file
   double Amp, BaseL, Width, Centroid, Mod;
   double Amp_low, BaseL_low, Width_low, Centroid_low, Mod_low;
   double Amp_high, BaseL_high, Width_high, Centroid_high, Mod_high;

   // List of branches
   TBranch        *b_E_Up;   //!
   TBranch        *b_E_deltaUp;   //!
   TBranch        *b_E_Down;   //!
   TBranch        *b_E_deltaDown;   //!
   TBranch        *b_TAC_Up;   //!
   TBranch        *b_TAC_Down;   //!

   TBranch        *b_TRIGGER;   //!
   TBranch        *b_CONFIG;   //!
   TBranch        *b_FLAG;   //!
   TBranch        *b_FIELD;   //!
   TBranch        *b_FIELD2;   //!
   TBranch        *b_POLARITY;   //!
   TBranch        *b_FREQ;   //!
   TBranch        *b_FREQ2;   //!
   TBranch        *b_RF_ON;   //!
   TBranch        *b_RF_OFF;   //!

   NMR(const char* filename, TTree *tree=0);
   virtual ~NMR();
   virtual Int_t    Cut();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     InitPara();
   virtual void     Analysis();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual int      ReadPara(const char* filename);
   virtual int      ReadFitPara(const char* filename);
   virtual void     MakeSpec();
   virtual void     MakeSpec(int dim, int* vecFreq, double* vecAsymm, double* vecAsymmError);
   virtual void     PlotSpec();
   virtual void     SaveSpec();
   virtual void     FitSpec(int type, double fit_low, double fit_high);
   virtual void     FitSpecCompare(double fit_low, double fit_high);
   virtual void     Bootstrapping();
   virtual double   GetFieldHP();
   virtual double   GetFieldCenterBefore();
   virtual double   GetFieldCenterAfter();
   virtual double   GetFieldCenter();
   virtual double   CalFieldCenterBefore(double FieldHP);
   virtual double   CalFieldCenterAfter(double FieldHP);
   virtual double   CalFieldCenter(double FieldHP);
};

#endif

#ifdef NMR_cxx
NMR::NMR(const char* filename, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("AutoTree",tree);

   }
   Init(tree);
}

NMR::~NMR()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NMR::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NMR::LoadTree(Long64_t entry)
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

void NMR::InitPara(){
   //initialize all the variables defined by myself
   FieldAvgHP = 0;
   FieldAvgCenterBefore = 0;
   FieldAvgCenterAfter = 0;
   FieldAvgCenter = 0;
   NumFreq = 0;
   freqset.clear();
   VecAsymm.clear();
   VecAsymmError.clear();
   FitCent = 0;
   FitCentError = 0;
   FitAmp = 0;
   FitAmpError = 0;
   MaxAsymmFreq = 0;
   for(int i=0; i<5000; i++){
      CtsUp[i]=0;
      CtsDown[i]=0;
   }
}

void NMR::Init(TTree *tree)
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

   InitPara();

   fChain->SetBranchAddress("E_UP", &E_Up, &b_E_Up);
   fChain->SetBranchAddress("E_DELTA_UP", &E_deltaUp, &b_E_deltaUp);
   fChain->SetBranchAddress("E_DOWN", &E_Down, &b_E_Down);
   fChain->SetBranchAddress("E_DELTA_DOWN", &E_deltaDown, &b_E_deltaDown);
   fChain->SetBranchAddress("TAC_UP", &TAC_Up, &b_TAC_Up);
   fChain->SetBranchAddress("TAC_DOWN", &TAC_Down, &b_TAC_Down);

   fChain->SetBranchAddress("TRIGGER", &TRIGGER, &b_TRIGGER);
   fChain->SetBranchAddress("CONFIG", &CONFIG, &b_CONFIG);
   fChain->SetBranchAddress("FLAG", &FLAG, &b_FLAG);
   fChain->SetBranchAddress("FIELD", &FIELD, &b_FIELD);
   fChain->SetBranchAddress("FIELD2", &FIELD2, &b_FIELD2);
   fChain->SetBranchAddress("POLARITY", &POLARITY, &b_POLARITY);
   fChain->SetBranchAddress("FREQ", &FREQ, &b_FREQ);
   fChain->SetBranchAddress("FREQ2", &FREQ2, &b_FREQ2);
   fChain->SetBranchAddress("RF_ON", &RF_ON, &b_RF_ON);
   fChain->SetBranchAddress("RF_OFF", &RF_OFF, &b_RF_OFF);

   Notify();
}

Bool_t NMR::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NMR::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t NMR::Cut()
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
}

double NMR::GetFieldHP(){
   return FieldAvgHP;
}

double NMR::GetFieldCenterBefore(){
   return FieldAvgCenterBefore;
}

double NMR::GetFieldCenterAfter(){
   return FieldAvgCenterAfter;
}

double NMR::GetFieldCenter(){
   return FieldAvgCenter;
}

double NMR::CalFieldCenterBefore(double FieldHP){
   //double FieldCenter = (FieldHP + 0.971479535)/0.9931743532;
   double FieldCenter = FieldHP * 1.00709 + 0.32;
   return FieldCenter;
}

double NMR::CalFieldCenterAfter(double FieldHP){
   //double FieldCenter = (FieldHP - 0.526407778)/0.992867;
   double FieldCenter = FieldHP * 1.00733 - 0.15;
   return FieldCenter;
}

double NMR::CalFieldCenter(double FieldHP){
   double FieldCenter = (CalFieldCenterBefore(FieldHP)+CalFieldCenterAfter(FieldHP))/2.0;
   return FieldCenter;
}

#endif // #ifdef NMR_cxx
