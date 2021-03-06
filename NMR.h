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
   double FieldAvgHP;
   double FieldAvgCenterBefore; //magnetic field at the center position, calibrated before the run
   double FieldAvgCenterAfter; //magnetic field at the center position, calibrated after the run
   double FieldAvgCenter; //magnetic field at the center position, average of the previous two
   double FitCent, FitCentError, FitAmp, FitAmpError;
   double E_GammaH_cal, E_GammaG_cal;
   int NumFreq;
   vector<double> VecAsymm, VecAsymmError;
   int CtsUp[5000], CtsDown[5000];
   int MaxAsymmFreq;
   Long64_t time;
   std::set<int> freqset;
   std::set<int>::iterator itfreqset;
   vector < pair<Long64_t, int> > TiD3_T, TiD3_T_cut;
   int IfTiD3;
   TGraphErrors *gSpec;
   TGraph *gTiD3_T, *gTiD3_T_cut;
   TH1F *h_GammaH_cal, *h_GammaG_cal;
   TH1F *h_GammaAll, *h_GammaAll_notime;
   TH2F *h_GG_Matrix;
   TH1F *h_GammaH_cal_notime, *h_GammaG_cal_notime;
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

   double d2_GammaH_L; //3rd-order
   double d2_GammaG_L;
   double e2_GammaH_L; //4th-order
   double e2_GammaG_L;

   //parameters read from input file
   int NMRorNQR; //0: NMR, 1: NQR
   int IfField; //0: no requirement on field readout, 1: require non-zero field readout
   int II2; //nuclear spin x 2
   int TimeCut;
   int TiD3Cut;
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

   NMR(const char* filename, TTree *tree=0);
   virtual ~NMR();
   virtual Int_t    Cut();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     InitPara();
   virtual void     Analysis(int MergeLow=3000, int MergeHigh=4000, int MergeFreq=3500);//merge range combine all the frequencies in the range to the single point at MergeFreq.
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual int      ReadPara(const char* filename);
   virtual int      ReadFitPara(const char* filename);
   virtual void     CalibGammaH();
   virtual void     CalibGammaG();
   virtual void     MakeSpec();
   virtual void     MakeSpec(int dim, int* vecFreq, double* vecAsymm, double* vecAsymmError);
   virtual void     PlotSpec();
   virtual void     SaveSpec();
   virtual void     FitSpec(int type, double fit_low, double fit_high, double bin_low, double bin_high, int IfText=1, const char* canvas="c2", int index_all=1, int index=0);
   virtual void     DrawBaseLine(double bl, double ble, double bin_low, double bin_high, const char* canvas="c2", int index_all=1, int index=0);
   virtual void     FitSpecCompare(double fit_low, double fit_high);
   virtual void     Bootstrapping(int MergeLow=3000, int MergeHigh=4000, int MergeFreq=3500);
   virtual Long64_t GetTime();
   virtual double   GetFieldHP();
   virtual double   GetFieldCenterBefore();
   virtual double   GetFieldCenterAfter();
   virtual double   GetFieldCenter();
   virtual double   CalFieldCenterBefore(double FieldHP);
   virtual double   CalFieldCenterAfter(double FieldHP);
   virtual double   CalFieldCenter(double FieldHP);
   virtual Long64_t GetTACUpScalar();
   virtual Long64_t GetTACDownScalar();
   virtual Long64_t GetTiD3();
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
   IfTiD3 = 0;
   E_GammaH_cal = 0;
   E_GammaG_cal = 0;
   FitCent = 0;
   FitCentError = 0;
   FitAmp = 0;
   FitAmpError = 0;
   time = 0;
   MaxAsymmFreq = 0;
   for(int i=0; i<5000; i++){
      CtsUp[i]=0;
      CtsDown[i]=0;
   }
   if(gROOT->FindObject("h_GammaH_cal")!=0){
      gROOT->FindObject("h_GammaH_cal")->Delete();
   }
   h_GammaH_cal = new TH1F("h_GammaH_cal","h_GammaH_cal",4000,0,4000);
   if(gROOT->FindObject("h_GammaG_cal")!=0){
      gROOT->FindObject("h_GammaG_cal")->Delete();
   }
   h_GammaG_cal = new TH1F("h_GammaG_cal","h_GammaG_cal",4000,0,4000);
   if(gROOT->FindObject("h_GammaH_cal_notime")!=0){
      gROOT->FindObject("h_GammaH_cal_notime")->Delete();
   }
   h_GammaH_cal_notime = new TH1F("h_GammaH_cal_notime","h_GammaH_cal_notime",4000,0,4000);
   if(gROOT->FindObject("h_GammaG_cal_notime")!=0){
      gROOT->FindObject("h_GammaG_cal_notime")->Delete();
   }
   h_GammaG_cal_notime = new TH1F("h_GammaG_cal_notime","h_GammaG_cal_notime",4000,0,4000);
   if(gROOT->FindObject("h_GammaAll")!=0){
      gROOT->FindObject("h_GammaAll")->Delete();
   }
   h_GammaAll = new TH1F("h_GammaAll","h_GammaAll",6000,0,6000);
   if(gROOT->FindObject("h_GammaAll_notime")!=0){
      gROOT->FindObject("h_GammaAll_notime")->Delete();
   }
   h_GammaAll_notime = new TH1F("h_GammaAll_notime","h_GammaAll_notime",6000,0,6000);

   if(gROOT->FindObject("h_EUp")!=0){
      gROOT->FindObject("h_EUp")->Delete();
   }
   h_EUp = new TH1F("h_EUp","h_EUp",1600,0,16000);
   if(gROOT->FindObject("h_EDown")!=0){
      gROOT->FindObject("h_EDown")->Delete();
   }
   h_EDown = new TH1F("h_EDown","h_EDown",1600,0,16000);
   if(gROOT->FindObject("h_GG_Matrix")!=0){
      gROOT->FindObject("h_GG_Matrix")->Delete();
   }
   h_GG_Matrix = new TH2F("h_GG_Matrix","h_GG_Matrix",4000,0,4000,4000,0,4000);
   //h_TAC_delta_gH = new TH1F("h_TAC_delta_gH","h_TAC_delta_gH",1600,0,16000);
   //h_TAC_delta_gG = new TH1F("h_TAC_delta_gG","h_TAC_delta_gG",1600,0,16000);
   TiD3_T.clear();
   TiD3_T_cut.clear();

   //a1_GammaH_L = 0.263796;  //slope for April 2016 
   //b1_GammaH_L =-0.595466;  //offset for April 2016
   //c1_GammaH_L = -7.16087e-8;   //2nd-order term, for 2016

   //a2_GammaH_L = 0.264627;  //slope for April 2016 
   //b2_GammaH_L =-3.42253;  //offset for April 2016
   //c2_GammaH_L = -6.05763e-8;   //2nd-order term for 2016

   //a1_GammaG_L = 0.290285;  //slope for April 2016 
   //b1_GammaG_L = 6.34802;  //offset for April 2016
   //c1_GammaG_L = 1.51486e-6;    //2nd-order term for 2016

   //a2_GammaG_L = 0.295908;  //slope for April 2016 
   //b2_GammaG_L = 1.16329;  //offset for April 2016
   //c2_GammaG_L = 1.17181e-7;   //2nd-order term for 2016

   //Updated calibration parameters
   a1_GammaH_L = 0.263473;  //slope for April 2016 
   b1_GammaH_L =-0.446142;  //offset for April 2016
   c1_GammaH_L = 2.9876e-8; //2nd-order term, for 2016

   a2_GammaH_L = 0.263756;  //slope for April 2016 
   b2_GammaH_L =-1.3925;   //offset for April 2016
   c2_GammaH_L = 2.97358e-8;  //2nd-order term for 2016

   a1_GammaG_L = 0.292499;  //slope for April 2016 
   b1_GammaG_L = 5.29869;  //offset for April 2016
   c1_GammaG_L = 7.49365e-7;    //2nd-order term for 2016

   a2_GammaG_L = 0.296244;  //slope for April 2016 
   b2_GammaG_L = 0.499282;  //offset for April 2016
   c2_GammaG_L = 7.3398e-8;   //2nd-order term for 2016

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

Float_t rand05(){
   return rand()*1.0/RAND_MAX - 0.5;
}

void NMR::CalibGammaH(){
   double ee = E_GammaH_L+rand05();
   if(E_GammaH_L<=3000){
      E_GammaH_cal = a1_GammaH_L*ee + b1_GammaH_L + c1_GammaH_L*ee*ee;
   }else{
      E_GammaH_cal = a2_GammaH_L*ee + b2_GammaH_L + c2_GammaH_L*ee*ee;
   }
}

void NMR::CalibGammaG(){
   double ee = E_GammaG_L+rand05();
   if(E_GammaG_L<=3000){
      E_GammaG_cal = a1_GammaG_L*ee + b1_GammaG_L + c1_GammaG_L*ee*ee;
   }else{
      E_GammaG_cal = a2_GammaG_L*ee + b2_GammaG_L + c2_GammaG_L*TMath::Power(ee,2) + d2_GammaG_L*TMath::Power(ee,3) + e2_GammaG_L*TMath::Power(ee,4);
   }
}

Int_t NMR::Cut()
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   int bGammaH = 0;
   if(E_GammaH_cal>1939 && E_GammaH_cal<1945){
      bGammaH = 1;
   }
   int bGammaG = 0;
   if(E_GammaG_cal>1939 && E_GammaG_cal<1945){
      bGammaG = 1;
   }
   if(bGammaH || bGammaG){
      return 1;
   }else{
      return 0;
   }
}

Long64_t NMR::GetTime(){
   return SR_Clock_UP*pow(2,16)+SR_Clock;
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

Long64_t NMR::GetTACUpScalar(){
   return SR_TACUp_UP*pow(2,16)+SR_TACUp;
}

Long64_t NMR::GetTACDownScalar(){
   return SR_TACDown_UP*pow(2,16)+SR_TACDown;
}

Long64_t NMR::GetTiD3(){
   return SR_TiD3_UP*pow(2,16)+SR_TiD3;
}
#endif // #ifdef NMR_cxx
