#define NQR_cxx
#include "NQR.h"
#include <TH2.h>
#include <TF1.h>
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
      }else if(strcmp(temp,"TIMECUT")==0){
         fscanf(fin,"%i",&TimeCut);
      }else if(strcmp(temp,"TID3CUT")==0){
         fscanf(fin,"%i",&TiD3Cut);
      }else if(strcmp(temp,"EUPMIN")==0){
         fscanf(fin,"%i",&EUpMin);
      }else if(strcmp(temp,"EUPMAX")==0){
         fscanf(fin,"%i",&EUpMax);
      }else if(strcmp(temp,"EDELTAUPMIN")==0){
         fscanf(fin,"%i",&EDeltaUpMin);
      }else if(strcmp(temp,"EDELTAUPMAX")==0){
         fscanf(fin,"%i",&EDeltaUpMax);
      }else if(strcmp(temp,"TACUPMIN")==0){
         fscanf(fin,"%i",&TACUpMin);
      }else if(strcmp(temp,"TACUPMAX")==0){
         fscanf(fin,"%i",&TACUpMax);
      }else if(strcmp(temp,"EDOWNMIN")==0){
         fscanf(fin,"%i",&EDownMin);
      }else if(strcmp(temp,"EDOWNMAX")==0){
         fscanf(fin,"%i",&EDownMax);
      }else if(strcmp(temp,"EDELTADOWNMIN")==0){
         fscanf(fin,"%i",&EDeltaDownMin);
      }else if(strcmp(temp,"EDELTADOWNMAX")==0){
         fscanf(fin,"%i",&EDeltaDownMax);
      }else if(strcmp(temp,"TACDOWNMIN")==0){
         fscanf(fin,"%i",&TACDownMin);
      }else if(strcmp(temp,"TACDOWNMAX")==0){
         fscanf(fin,"%i",&TACDownMax);
      }else if(strcmp(temp,"END")==0){
         break;
      }else {
         cout<<"Could not read your input keyword. Aborting program."<<endl;
         return 0;
      }
   }
   return 1;
}

int NQR::ReadFitPara(char* filename){
   char temp[300];
   FILE *fin = fopen(filename,"r");
   while(!feof(fin)){
      fscanf(fin,"%s ",temp);
      if(strcmp(temp,"AMPLITUDE")==0){
         fscanf(fin,"%lf",&Amp);
      }else if(strcmp(temp,"BASELINE")==0){
         fscanf(fin,"%lf",&BaseL);
      }else if(strcmp(temp,"WIDTH")==0){
         fscanf(fin,"%lf",&Width);
      }else if(strcmp(temp,"RESONANCEFREQ")==0){
         fscanf(fin,"%lf",&ResonanceFreq);
      }else if(strcmp(temp,"END")==0){
         break;
      }else {
         cout<<"Could not read your input keyword. Aborting program."<<endl;
         return 0;
      }
   }
   return 1;
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
   Long64_t time_previous = 0, time_present = 0, time_next = 0, time_offset = 0;
   int TiD3_present = 0, TiD3_previous = 0, TiD3_perSecond = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if(jentry%500000==0){
         cout<<jentry<<" events have been analyzed"<<endl;
         //cout<<"\r"<<(double)jentry/nentries*100<<"% of events have been analyzed";
      }
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      bool FillTiD3_T = false;

      time_present = GetTime();
      if(time_present < time_previous - 100){
         time_offset = time_offset + time_previous + 1;
         time_previous = 0;
      }

      if(time_present + 1000 < time_next){
         time_next = 0;
         TiD3_previous = 0;
      }
      if(time_present > time_next){
         TiD3_present = GetTiD3();
         TiD3_perSecond = TiD3_present - TiD3_previous;
         TiD3_T.push_back(make_pair((time_present+time_offset)/1000, TiD3_perSecond) ); //TiD3 monitor, before cut
         FillTiD3_T = true;
         time_next = time_present + 1000;
         TiD3_previous = TiD3_present;
      }

      if(time_present - time_previous < TimeCut && TiD3_perSecond > TiD3Cut){ //cut on TiD3 and the time interval between two successive events
         time = time + time_present - time_previous;
         //cout<<jentry<<" "<<time_present<<" "<<time_previous<<endl;
      }else{
         time_previous = time_present;
         continue;
      }
      time_previous = time_present;
      if(FillTiD3_T){
         TiD3_T_cut.push_back(make_pair((time_offset+time_present)/1000, TiD3_perSecond) ); //TiD3 monitor, after cut
      }
      //if(time<6000){
      //   continue;
      //}
      if(FLAG==100){
         continue;
      }

      CalibGammaH();
      CalibGammaG();

      //if(Cut() == 0){
      //   continue;
      //}

      int freq2;
      if(RF_OFF_ON==1000){
         freq2 = FREQ2;
      }else{
         freq2 = FREQ;
      }

      // if (Cut(ientry) < 0) continue;
      bool GoUp = false, GoDown = false;
      if(TAC_Up>TACUpMin && TAC_Up<TACUpMax && E_Up>EUpMin && E_Up<EUpMax && E_deltaUp>EDeltaUpMin && E_deltaUp<EDeltaUpMax){
         GoUp = true;
      }
      if(TAC_Down>TACDownMin && TAC_Down<TACDownMax && E_Down>EDownMin && E_Down<EDownMax && E_deltaDown>EDeltaDownMin && E_deltaDown<EDeltaDownMax){
         GoDown = true;
      }
      if(GoUp && GoDown){
         continue;
      }
      if(GoUp){
         CtsUp[freq2]++;
      }
      if(GoDown){
         CtsDown[freq2]++;
      }
      h_GammaH_cal->Fill(E_GammaH_cal);
      h_GammaG_cal->Fill(E_GammaG_cal);
      h_EUp->Fill(E_Up);
      h_EDown->Fill(E_Down);
      freqset.insert(freq2);
   }
   cout<<endl;
}

void NQR::MakeNQR(){
   NumFreq = 0;

   cout<< freqset.size() <<" frequencies found:"<< endl;
   for(itfreqset=freqset.begin(); itfreqset!=freqset.end(); itfreqset++){
      int ffreq = *itfreqset;
      int fup = CtsUp[ffreq], fdown = CtsDown[ffreq];
      gFreq[NumFreq] = ffreq;
      gAsymm[NumFreq] = (double)(fup - fdown)/(fup + fdown);
      gFreqErr[NumFreq] = Mod;
      gAsymmErr[NumFreq] = sqrt(4.0*fup*fdown/pow(fup+fdown,3));
      NumFreq++;
      cout<<NumFreq<<" "<<ffreq<<" "<<fup<<" "<<fdown<<endl;
   }
   cout<<"Total Data taking time: "<<time/1000./60<<" min."<<endl;
   gNQR = new TGraphErrors(NumFreq,gFreq,gAsymm,gFreqErr,gAsymmErr);
   gNQR->SetMarkerStyle(20);
   gNQR->SetLineWidth(0);
   gNQR->SetMarkerSize(1);
   gNQR->GetXaxis()->SetTitle("Freq. [kHz]");
   gNQR->GetYaxis()->SetTitle("Asymm.");
   gNQR->SetTitle("NQR");
   gNQR->SetName("NQR");
   //g1->Draw("AP");

   gTiD3_T = new TGraph(TiD3_T.size());
   gTiD3_T_cut = new TGraph(TiD3_T_cut.size());
   for(int i=0; i<TiD3_T.size(); i++){
      gTiD3_T->SetPoint(i, TiD3_T[i].first, TiD3_T[i].second-10);
   }
   for(int i=0; i<TiD3_T_cut.size(); i++){
      gTiD3_T_cut->SetPoint(i, TiD3_T_cut[i].first, TiD3_T_cut[i].second);
   }
   gTiD3_T->SetTitle("TiD3");
   gTiD3_T->SetName("TiD3");
   gTiD3_T->SetMarkerStyle(20);
   gTiD3_T->SetMarkerColor(1);
   gTiD3_T->SetLineColor(1);
   gTiD3_T_cut->SetTitle("TiD3_cut");
   gTiD3_T_cut->SetName("TiD3_cut");
   gTiD3_T_cut->SetMarkerStyle(20);
   gTiD3_T_cut->SetMarkerColor(2);
   gTiD3_T_cut->SetLineColor(2);
}

void NQR::FitNQR(double fit_low, double fit_high){
   ReadFitPara("NMR_NQR_fit.in");
   TF1 *f1=new TF1("f1","[0]+[1]-[1]*pow(0.5/[3],2)*pow(sqrt(pow([2]-x+[3],2) + pow([4],2)) - sqrt(pow([2]-x-[3],2) + pow([4],2)),2)");
   f1->SetParName(0,"Baseline");
   f1->SetParName(1,"Amplitude");
   f1->SetParName(2,"ResonanceFreq");
   f1->SetParName(3,"Modulation");
   f1->SetParName(4,"Width");
   f1->SetParameter(0,BaseL);
   f1->SetParameter(1,Amp);
   f1->SetParameter(2,ResonanceFreq);
   f1->FixParameter(3,Mod);
   f1->SetParameter(4,Width); f1->SetParLimits(4,0,500);
   gNQR->Fit("f1","EM","D",fit_low,fit_high);
   double chi2 = f1->GetChisquare();
   double NDF = f1->GetNDF();
   cout<<"Chi2/NDF = "<<chi2/NDF<<endl;
   cout<<"Baseline = "<<f1->GetParameter(0)<<endl;
   cout<<"Amplitude = "<<f1->GetParameter(1)<<endl;
   cout<<"ResonanceFreq = "<<f1->GetParameter(2)<<endl;
   cout<<"Modulation = "<<f1->GetParameter(3)<<endl;
   cout<<"Width = "<<f1->GetParameter(4)<<endl;
}
