#define NQR_cxx
#include "NQR.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

int NQR::ReadPara(char* filename){
   InitPara();
   char temp[300];
   FILE *fin = fopen(filename,"r");
   while(!feof(fin)){
      fscanf(fin,"%s ",temp);
      if(strcmp(temp,"MODULATION")==0){
         fscanf(fin,"%i",&Mod);
      }else if(strcmp(temp,"EUPMIN")==0){
         fscanf(fin,"%i",&EUpMin);
      }else if(strcmp(temp,"EUPMAX")==0){
         fscanf(fin,"%i",&EUpMax);
      }else if(strcmp(temp,"EDELTAUPMIN")==0){
         fscanf(fin,"%i",&EDeltaUpMin);
      }else if(strcmp(temp,"EDELTAUPMAX")==0){
         fscanf(fin,"%i",&EDeltaUpMax);
      }else if(strcmp(temp,"EDOWNMIN")==0){
         fscanf(fin,"%i",&EDownMin);
      }else if(strcmp(temp,"EDOWNMAX")==0){
         fscanf(fin,"%i",&EDownMax);
      }else if(strcmp(temp,"EDELTADOWNMIN")==0){
         fscanf(fin,"%i",&EDeltaDownMin);
      }else if(strcmp(temp,"EDELTADOWNMAX")==0){
         fscanf(fin,"%i",&EDeltaDownMax);
      }else if(strcmp(temp,"END")==0){
         break;
      }else {
         cout<<"Could not read your input keyword. Aborting program."<<endl;
         return 0;
      }
   }
   return 1;
}

Float_t rand05(){
   return rand()*1.0/RAND_MAX - 0.5;
}

void NQR::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L NQR.C
//      Root > NQR t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if(jentry%10000==0){
         cout<<"\r"<<(double)jentry/nentries*100<<"% of events have been analyzed";
      }
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(FLAG==100){
         continue;
      }
      double energy;
      if(E_GammaH_L<=3000){
         energy = a1_GammaH_L*Float_t(E_GammaH_L + rand05()) + b1_GammaH_L + c1_GammaH_L*Float_t(E_GammaH_L + rand05())*Float_t(E_GammaH_L + rand05());
      }else{
         energy = a2_GammaH_L*Float_t(E_GammaH_L + rand05()) + b2_GammaH_L + c2_GammaH_L*Float_t(E_GammaH_L + rand05())*Float_t(E_GammaH_L + rand05());
      }
      h_GammaH_cal->Fill(energy);
      if(E_GammaG_L<=3000){
         energy = a1_GammaG_L*Float_t(E_GammaG_L + rand05()) + b1_GammaG_L + c1_GammaG_L*Float_t(E_GammaG_L + rand05())*Float_t(E_GammaG_L + rand05());
      }else{
         energy = a2_GammaG_L*Float_t(E_GammaG_L + rand05()) + b2_GammaG_L + c2_GammaG_L*Float_t(E_GammaG_L + rand05())*Float_t(E_GammaG_L + rand05());
      }
      h_GammaG_cal->Fill(energy);

      int freq2;
      if(RF_OFF_ON==1000){
         freq2 = FREQ2;
      }else{
         freq2 = FREQ;
      }

      // if (Cut(ientry) < 0) continue;
      bool GoUp = false, GoDown = false;
      if(TAC_Up>500 && TAC_Up<15000 && E_Up>EUpMin && E_Up<EUpMax && E_deltaUp>EDeltaUpMin && E_deltaUp<EDeltaUpMax){
         GoUp = true;
      }
      if(TAC_Down>500 && TAC_Down<15000 && E_Down>EDownMin && E_Down<EDownMax && E_deltaDown>EDeltaDownMin && E_deltaDown<EDeltaDownMax){
         GoDown = true;
      }
      if(GoUp && !GoDown){
         CtsUp[freq2]++;
      }else if(!GoUp && GoDown){
         CtsDown[freq2]++;
      }else{
         continue;
      }
      freqset.insert(freq2);
   }
   cout<<endl;
}

void NQR::MakeNQR(){
   NumFreq = 0;
   cout<< freqset.size() << endl;
   for(itfreqset=freqset.begin(); itfreqset!=freqset.end(); itfreqset++){
      int ffreq = *itfreqset;
      int fup = CtsUp[ffreq], fdown = CtsDown[ffreq];
      gFreq[NumFreq] = ffreq;
      gAsymm[NumFreq] = (double)(fup - fdown)/(fup + fdown);
      gFreqErr[NumFreq] = 0;
      gAsymmErr[NumFreq] = sqrt(4.0*fup*fdown/pow(fup+fdown,3));
      NumFreq++;
      cout<<NumFreq<<" "<<ffreq<<" "<<fup<<" "<<fdown<<endl;
   }
   gNQR = new TGraphErrors(NumFreq,gFreq,gAsymm,gFreqErr,gAsymmErr);
   gNQR->SetMarkerStyle(20);
   gNQR->SetLineWidth(0);
   gNQR->SetMarkerSize(1);
   gNQR->GetXaxis()->SetTitle("Freq. [kHz]");
   gNQR->GetYaxis()->SetTitle("Asymm.");
   gNQR->SetTitle("NQR");
   gNQR->SetName("NQR");
   //g1->Draw("AP");
}
