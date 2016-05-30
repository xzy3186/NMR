//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 25 17:36:08 2016 by ROOT version 5.34/04
// from TTree AutoTree/Automatic filled Tree
// found on file: DataFiles/r0071.root
//////////////////////////////////////////////////////////

#ifndef NQR_h
#define NQR_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <iostream>
#include <set>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class NQR {
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
   UShort_t        TAC_Delta_gH;
   UShort_t        TAC_Delta_gG;
   UShort_t        ADC1_7_VOIE_8;
   UShort_t        ADC1_7_VOIE_9;
   UShort_t        ADC1_7_VOIE_10;
   UShort_t        ADC1_7_VOIE_11;
   UShort_t        ADC1_7_VOIE_12;
   UShort_t        ADC1_7_VOIE_13;
   UShort_t        ADC1_7_VOIE_14;
   UShort_t        ADC1_7_VOIE_15;
   UShort_t        E_GammaH_H;
   UShort_t        Broken2;
   UShort_t        Broken;
   UShort_t        E_GammaG_H;
   UShort_t        E_GammaG_L;
   UShort_t        Broken3;
   UShort_t        E_GammaH_L;
   UShort_t        ADC1_7_VOIE_23;
   UShort_t        ADC1_7_VOIE_24;
   UShort_t        ADC1_7_VOIE_25;
   UShort_t        ADC1_7_VOIE_26;
   UShort_t        ADC1_7_VOIE_27;
   UShort_t        ADC1_7_VOIE_28;
   UShort_t        ADC1_7_VOIE_29;
   UShort_t        ADC1_7_VOIE_30;
   UShort_t        ADC1_7_VOIE_31;
   UShort_t        trigger;
   UShort_t        config;
   UShort_t        FLAG;
   UShort_t        FIELD;
   UShort_t        FIELD2;
   UShort_t        POLARITY;
   UShort_t        FREQ;
   UShort_t        FREQ2;
   UShort_t        RF_OFF_ON;
   UShort_t        SR_TACUp_UP;
   UShort_t        SR_TACUp;
   UShort_t        SR_TACDown_UP;
   UShort_t        SR_TACDown;
   UShort_t        SR_Clock_UP;
   UShort_t        SR_Clock;
   UShort_t        SR_Clock_DT_UP;
   UShort_t        SR_Clock_DT;
   UShort_t        SR_Ncycle_UP;
   UShort_t        SR_Ncycle;
   UShort_t        SR_TiD3_UP;
   UShort_t        SR_TiD3;

   //some variables for near-line analysis
   double E_GammaH_cal, E_GammaG_cal;
   int NumFreq;
   double gFreq[30], gAsymm[30], gFreqErr[30], gAsymmErr[30];
   int CtsUp[5000], CtsDown[5000];
   Long64_t time, time_previous, time_present;
   std::set<int> freqset;
   std::set<int>::iterator itfreqset;
   TGraphErrors *gNQR;
   TH1F *h_GammaH_cal, *h_GammaG_cal;
   TH1F *h_EUp, *h_EDown;
   //TH1F *h_TAC_delta_gH, *h_TAC_delta_gG;

   //calibration parameters of gamma
   double a1_GammaH_L;  //slope for April 2016 
   double a2_GammaH_L;  //slope for April 2016 
   double a1_GammaG_L;  //slope for April 2016 
   double a2_GammaG_L;  //slope for April 2016 

   double b1_GammaH_L;  //offset for April 2016
   double b2_GammaH_L;  //offset for April 2016
   double b1_GammaG_L;  //offset for April 2016
   double b2_GammaG_L;  //offset for April 2016

   double c1_GammaH_L;   //2nd-order term, for 2016
   double c2_GammaH_L;   //2nd-order term for 2016
   double c1_GammaG_L;    //2nd-order term for 2016   
   double c2_GammaG_L;   //2nd-order term for 2016

   //parameters read from input file
   int Mod;
   int TimeCut;
   int EUpMin, EUpMax;
   int EDeltaUpMin, EDeltaUpMax;
   int TACUpMin, TACUpMax;
   int EDownMin, EDownMax;
   int EDeltaDownMin, EDeltaDownMax;
   int TACDownMin, TACDownMax;

   //parameters read from fitting input file
   double Amp, BaseL, Width, LarmorFreq;

   // List of branches
   TBranch        *b_E_Up;   //!
   TBranch        *b_E_deltaUp;   //!
   TBranch        *b_E_Down;   //!
   TBranch        *b_E_deltaDown;   //!
   TBranch        *b_TAC_Up;   //!
   TBranch        *b_TAC_Down;   //!
   TBranch        *b_TAC_Delta_gH;   //!
   TBranch        *b_TAC_Delta_gG;   //!
   TBranch        *b_ADC1_7_VOIE_8;   //!
   TBranch        *b_ADC1_7_VOIE_9;   //!
   TBranch        *b_ADC1_7_VOIE_10;   //!
   TBranch        *b_ADC1_7_VOIE_11;   //!
   TBranch        *b_ADC1_7_VOIE_12;   //!
   TBranch        *b_ADC1_7_VOIE_13;   //!
   TBranch        *b_ADC1_7_VOIE_14;   //!
   TBranch        *b_ADC1_7_VOIE_15;   //!
   TBranch        *b_E_GammaH_H;   //!
   TBranch        *b_Broken2;   //!
   TBranch        *b_Broken;   //!
   TBranch        *b_E_GammaG_H;   //!
   TBranch        *b_E_GammaG_L;   //!
   TBranch        *b_Broken3;   //!
   TBranch        *b_E_GammaH_L;   //!
   TBranch        *b_ADC1_7_VOIE_23;   //!
   TBranch        *b_ADC1_7_VOIE_24;   //!
   TBranch        *b_ADC1_7_VOIE_25;   //!
   TBranch        *b_ADC1_7_VOIE_26;   //!
   TBranch        *b_ADC1_7_VOIE_27;   //!
   TBranch        *b_ADC1_7_VOIE_28;   //!
   TBranch        *b_ADC1_7_VOIE_29;   //!
   TBranch        *b_ADC1_7_VOIE_30;   //!
   TBranch        *b_ADC1_7_VOIE_31;   //!
   TBranch        *b_trigger;   //!
   TBranch        *b_config;   //!
   TBranch        *b_FLAG;   //!
   TBranch        *b_FIELD;   //!
   TBranch        *b_FIELD2;   //!
   TBranch        *b_POLARITY;   //!
   TBranch        *b_FREQ;   //!
   TBranch        *b_FREQ2;   //!
   TBranch        *b_RF_OFF_ON;   //!
   TBranch        *b_SR_TACUp_UP;   //!
   TBranch        *b_SR_TACUp;   //!
   TBranch        *b_SR_TACDown_UP;   //!
   TBranch        *b_SR_TACDown;   //!
   TBranch        *b_SR_Clock_UP;   //!
   TBranch        *b_SR_Clock;   //!
   TBranch        *b_SR_Clock_DT_UP;   //!
   TBranch        *b_SR_Clock_DT;   //!
   TBranch        *b_SR_Ncycle_UP;   //!
   TBranch        *b_SR_Ncycle;   //!
   TBranch        *b_SR_TiD3_UP;   //!
   TBranch        *b_SR_TiD3;   //!

   NQR(char* filename, TTree *tree=0);
   virtual ~NQR();
   virtual Int_t    Cut();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     InitPara();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual int      ReadPara(char* filename);
   virtual int      ReadFitPara(char* filename);
   virtual void     CalibGammaH();
   virtual void     CalibGammaG();
   virtual void     MakeNQR();
   virtual void     FitNQR(double fit_low, double fit_high);
};

#endif

#ifdef NQR_cxx
NQR::NQR(char* filename, TTree *tree) : fChain(0) 
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

NQR::~NQR()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NQR::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NQR::LoadTree(Long64_t entry)
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

void NQR::InitPara(){
   //initialize all the variables defined by myself
   NumFreq = 0;
   E_GammaH_cal = 0;
   E_GammaG_cal = 0;
   time = 0;
   time_previous = 0;
   time_present = 0;
   for(int i=0; i<30; i++){
      gFreq[i]=0;
      gAsymm[i]=0;
      gFreqErr[i]=0;
      gAsymmErr[i]=0;
   }
   for(int i=0; i<5000; i++){
      CtsUp[i]=0;
      CtsDown[i]=0;
   }
   freqset.clear();
   h_GammaH_cal = new TH1F("h_GammaH_cal","h_GammaH_cal",4000,0,4000);
   h_GammaG_cal = new TH1F("h_GammaG_cal","h_GammaG_cal",4000,0,4000);
   h_EUp = new TH1F("h_EUp","h_EUp",1600,0,16000);
   h_EDown = new TH1F("h_EDown","h_EDown",1600,0,16000);
   //h_TAC_delta_gH = new TH1F("h_TAC_delta_gH","h_TAC_delta_gH",1600,0,16000);
   //h_TAC_delta_gG = new TH1F("h_TAC_delta_gG","h_TAC_delta_gG",1600,0,16000);

   a1_GammaH_L = 0.263796;  //slope for April 2016 
   a2_GammaH_L = 0.264627;  //slope for April 2016 
   a1_GammaG_L = 0.290285;  //slope for April 2016 
   a2_GammaG_L = 0.295908;  //slope for April 2016 

   b1_GammaH_L =-0.595466;  //offset for April 2016
   b2_GammaH_L =-3.42253;  //offset for April 2016
   b1_GammaG_L = 6.34802;  //offset for April 2016
   b2_GammaG_L = 1.16329;  //offset for April 2016

   c1_GammaH_L = -7.16087e-8;   //2nd-order term, for 2016
   c2_GammaH_L = -6.05763e-8;   //2nd-order term for 2016
   c1_GammaG_L = 1.51486e-6;    //2nd-order term for 2016   
   c2_GammaG_L = 1.17181e-7;   //2nd-order term for 2016
}

void NQR::Init(TTree *tree)
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

   fChain->SetBranchAddress("E_Up", &E_Up, &b_E_Up);
   fChain->SetBranchAddress("E_deltaUp", &E_deltaUp, &b_E_deltaUp);
   fChain->SetBranchAddress("E_Down", &E_Down, &b_E_Down);
   fChain->SetBranchAddress("E_deltaDown", &E_deltaDown, &b_E_deltaDown);
   fChain->SetBranchAddress("TAC_Up", &TAC_Up, &b_TAC_Up);
   fChain->SetBranchAddress("TAC_Down", &TAC_Down, &b_TAC_Down);
   fChain->SetBranchAddress("TAC_Delta_gH", &TAC_Delta_gH, &b_TAC_Delta_gH);
   fChain->SetBranchAddress("TAC_Delta_gG", &TAC_Delta_gG, &b_TAC_Delta_gG);
   fChain->SetBranchAddress("ADC1_7_VOIE_8", &ADC1_7_VOIE_8, &b_ADC1_7_VOIE_8);
   fChain->SetBranchAddress("ADC1_7_VOIE_9", &ADC1_7_VOIE_9, &b_ADC1_7_VOIE_9);
   fChain->SetBranchAddress("ADC1_7_VOIE_10", &ADC1_7_VOIE_10, &b_ADC1_7_VOIE_10);
   fChain->SetBranchAddress("ADC1_7_VOIE_11", &ADC1_7_VOIE_11, &b_ADC1_7_VOIE_11);
   fChain->SetBranchAddress("ADC1_7_VOIE_12", &ADC1_7_VOIE_12, &b_ADC1_7_VOIE_12);
   fChain->SetBranchAddress("ADC1_7_VOIE_13", &ADC1_7_VOIE_13, &b_ADC1_7_VOIE_13);
   fChain->SetBranchAddress("ADC1_7_VOIE_14", &ADC1_7_VOIE_14, &b_ADC1_7_VOIE_14);
   fChain->SetBranchAddress("ADC1_7_VOIE_15", &ADC1_7_VOIE_15, &b_ADC1_7_VOIE_15);
   fChain->SetBranchAddress("E_GammaH_H", &E_GammaH_H, &b_E_GammaH_H);
   fChain->SetBranchAddress("Broken2", &Broken2, &b_Broken2);
   fChain->SetBranchAddress("Broken", &Broken, &b_Broken);
   fChain->SetBranchAddress("E_GammaG_H", &E_GammaG_H, &b_E_GammaG_H);
   fChain->SetBranchAddress("E_GammaG_L", &E_GammaG_L, &b_E_GammaG_L);
   fChain->SetBranchAddress("Broken3", &Broken3, &b_Broken3);
   fChain->SetBranchAddress("E_GammaH_L", &E_GammaH_L, &b_E_GammaH_L);
   fChain->SetBranchAddress("ADC1_7_VOIE_23", &ADC1_7_VOIE_23, &b_ADC1_7_VOIE_23);
   fChain->SetBranchAddress("ADC1_7_VOIE_24", &ADC1_7_VOIE_24, &b_ADC1_7_VOIE_24);
   fChain->SetBranchAddress("ADC1_7_VOIE_25", &ADC1_7_VOIE_25, &b_ADC1_7_VOIE_25);
   fChain->SetBranchAddress("ADC1_7_VOIE_26", &ADC1_7_VOIE_26, &b_ADC1_7_VOIE_26);
   fChain->SetBranchAddress("ADC1_7_VOIE_27", &ADC1_7_VOIE_27, &b_ADC1_7_VOIE_27);
   fChain->SetBranchAddress("ADC1_7_VOIE_28", &ADC1_7_VOIE_28, &b_ADC1_7_VOIE_28);
   fChain->SetBranchAddress("ADC1_7_VOIE_29", &ADC1_7_VOIE_29, &b_ADC1_7_VOIE_29);
   fChain->SetBranchAddress("ADC1_7_VOIE_30", &ADC1_7_VOIE_30, &b_ADC1_7_VOIE_30);
   fChain->SetBranchAddress("ADC1_7_VOIE_31", &ADC1_7_VOIE_31, &b_ADC1_7_VOIE_31);
   fChain->SetBranchAddress("trigger", &trigger, &b_trigger);
   fChain->SetBranchAddress("config", &config, &b_config);
   fChain->SetBranchAddress("FLAG", &FLAG, &b_FLAG);
   fChain->SetBranchAddress("FIELD", &FIELD, &b_FIELD);
   fChain->SetBranchAddress("FIELD2", &FIELD2, &b_FIELD2);
   fChain->SetBranchAddress("POLARITY", &POLARITY, &b_POLARITY);
   fChain->SetBranchAddress("FREQ", &FREQ, &b_FREQ);
   fChain->SetBranchAddress("FREQ2", &FREQ2, &b_FREQ2);
   fChain->SetBranchAddress("RF_OFF_ON", &RF_OFF_ON, &b_RF_OFF_ON);
   fChain->SetBranchAddress("SR_TACUp_UP", &SR_TACUp_UP, &b_SR_TACUp_UP);
   fChain->SetBranchAddress("SR_TACUp", &SR_TACUp, &b_SR_TACUp);
   fChain->SetBranchAddress("SR_TACDown_UP", &SR_TACDown_UP, &b_SR_TACDown_UP);
   fChain->SetBranchAddress("SR_TACDown", &SR_TACDown, &b_SR_TACDown);
   fChain->SetBranchAddress("SR_Clock_UP", &SR_Clock_UP, &b_SR_Clock_UP);
   fChain->SetBranchAddress("SR_Clock", &SR_Clock, &b_SR_Clock);
   fChain->SetBranchAddress("SR_Clock_DT_UP", &SR_Clock_DT_UP, &b_SR_Clock_DT_UP);
   fChain->SetBranchAddress("SR_Clock_DT", &SR_Clock_DT, &b_SR_Clock_DT);
   fChain->SetBranchAddress("SR_Ncycle_UP", &SR_Ncycle_UP, &b_SR_Ncycle_UP);
   fChain->SetBranchAddress("SR_Ncycle", &SR_Ncycle, &b_SR_Ncycle);
   fChain->SetBranchAddress("SR_TiD3_UP", &SR_TiD3_UP, &b_SR_TiD3_UP);
   fChain->SetBranchAddress("SR_TiD3", &SR_TiD3, &b_SR_TiD3);
   Notify();
}

Bool_t NQR::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NQR::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Float_t rand05(){
   return rand()*1.0/RAND_MAX - 0.5;
}

void NQR::CalibGammaH(){
   if(E_GammaH_L<=3000){
      E_GammaH_cal = a1_GammaH_L*Float_t(E_GammaH_L + rand05()) + b1_GammaH_L + c1_GammaH_L*Float_t(E_GammaH_L + rand05())*Float_t(E_GammaH_L + rand05());
   }else{
      E_GammaH_cal = a2_GammaH_L*Float_t(E_GammaH_L + rand05()) + b2_GammaH_L + c2_GammaH_L*Float_t(E_GammaH_L + rand05())*Float_t(E_GammaH_L + rand05());
   }
}

void NQR::CalibGammaG(){
   if(E_GammaG_L<=3000){
      E_GammaG_cal = a1_GammaG_L*Float_t(E_GammaG_L + rand05()) + b1_GammaG_L + c1_GammaG_L*Float_t(E_GammaG_L + rand05())*Float_t(E_GammaG_L + rand05());
   }else{
      E_GammaG_cal = a2_GammaG_L*Float_t(E_GammaG_L + rand05()) + b2_GammaG_L + c2_GammaG_L*Float_t(E_GammaG_L + rand05())*Float_t(E_GammaG_L + rand05());
   }
}

Int_t NQR::Cut()
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   int bGammaH = 0;
   if((E_GammaH_cal>926 && E_GammaH_cal<934)||(E_GammaH_cal>505 && E_GammaH_cal<515)){
      bGammaH = 1;
   }
   int bGammaG = 0;
   if((E_GammaG_cal>926 && E_GammaG_cal<934)||(E_GammaG_cal>505 && E_GammaG_cal<515)){
      bGammaG = 1;
   }
   if(bGammaH || bGammaG){
      return 1;
   }else{
      return 0;
   }
}
#endif // #ifdef NQR_cxx
