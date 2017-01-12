#define NMR_cxx
#include "NMR.h"
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TText.h>
#include <TString.h>
#include <TRandom3.h>
#include <sstream>
#include <algorithm>

#include "lineshape.h"

int NMR::ReadPara(const char* filename){
   InitPara();
   char temp[300];
   FILE *fin = fopen(filename,"r");
   while(!feof(fin)){
      fscanf(fin,"%s ",temp);
      if(strcmp(temp,"NMR")==0){
         NMRorNQR = 0;
      }else if(strcmp(temp,"NQR")==0){
         NMRorNQR = 1;
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

int NMR::ReadFitPara(const char* filename){
   char temp[300];
   FILE *fin = fopen(filename,"r");
   while(!feof(fin)){
      fscanf(fin,"%s ",temp);
      if(strcmp(temp,"AMPLITUDE")==0){
         fscanf(fin,"%lf %lf %lf",&Amp,&Amp_low,&Amp_high);
      }else if(strcmp(temp,"BASELINE")==0){
         fscanf(fin,"%lf %lf %lf",&BaseL,&BaseL_low,&BaseL_high);
      }else if(strcmp(temp,"WIDTH")==0){
         fscanf(fin,"%lf %lf %lf",&Width,&Width_low,&Width_high);
      }else if(strcmp(temp,"MODULATION")==0){
         fscanf(fin,"%lf %lf %lf",&Mod,&Mod_low,&Mod_high);
      }else if(strcmp(temp,"CENTROID")==0){
         fscanf(fin,"%lf %lf %lf",&Centroid,&Centroid_low,&Centroid_high);
      }else if(strcmp(temp,"END")==0){
         break;
      }else {
         cout<<"Could not read your input keyword. Aborting program."<<endl;
         return 0;
      }
   }
   return 1;
}

void NMR::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L NMR.C
//      Root > NMR t
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
   IfTiD3 = 1;

   Long64_t nentries = fChain->GetEntries();
   cout<<"total number of events = "<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   Long64_t time_previous = 0, time_present = 0, time_next = 0, time_offset = 0;
   int TiD3_present = 0, TiD3_previous = 0, TiD3_perSecond = 0;
   int count = 0;

   FieldAvgHP = 0;
   double field_each_event;
   Long64_t ntotal = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if(jentry%500000==0){
         cout<<jentry<<" events have been analyzed"<<endl;
         //cout<<"\r"<<(double)count/nentries*100<<"% of events have been analyzed";
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
         //if(TiD3_perSecond>500){
         //   cout<<time_present<<", "<<time_previous<<", "<<TiD3_perSecond<<endl;
         //}
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
      if(FLAG==100 /*|| FIELD==0*/){
         continue;
      }

      field_each_event = FIELD + FIELD2/10.0;
      FieldAvgHP = FieldAvgHP + field_each_event;
      ntotal++;

      CalibGammaH();
      CalibGammaG();

      //if(Cut() == 0){
      //   continue;
      //}
      int freq;
      if(NMRorNQR==0){//NMR data
         freq = FREQ;
      }else if(NMRorNQR==1){//NRQ data
         if(RF_OFF_ON==1000){
            freq = FREQ2;
         }else{
            freq = FREQ;
         }
      }else{
         break;
      }

      // if (Cut(ientry) < 0) continue;
      bool GoUp = false, GoDown = false;
      if(TAC_Up>TACUpMin && TAC_Up<TACUpMax && E_Up>EUpMin && E_Up<EUpMax && E_deltaUp>EDeltaUpMin && E_deltaUp<EDeltaUpMax){
         GoUp = true;
      }
      if(TAC_Down>TACDownMin && TAC_Down<TACDownMax && E_Down>EDownMin && E_Down<EDownMax && E_deltaDown>EDeltaDownMin && E_deltaDown<EDeltaDownMax){
         GoDown = true;
      }
      //just for test, to sum RF-OFF freq at different position.
      if(NMRorNQR==1 && freq>1500){
         freq = 1500;
      }
      //if(NMRorNQR==0 && freq>2200 && freq<2800){
      //   freq = 2500;
      //}
      if(GoUp && GoDown){
         count++;
         continue;
      }

      if(GoUp){
         CtsUp[freq]++;
      }
      if(GoDown){
         CtsDown[freq]++;
      }
      h_GammaH_cal->Fill(E_GammaH_cal);
      h_GammaG_cal->Fill(E_GammaG_cal);
      h_EUp->Fill(E_Up);
      h_EDown->Fill(E_Down);
      freqset.insert(freq);
   }
   FieldAvgHP = FieldAvgHP/ntotal;
   FieldAvgCenterBefore = CalFieldCenterBefore(FieldAvgHP);
   FieldAvgCenterAfter = CalFieldCenterAfter(FieldAvgHP);
   FieldAvgCenter = CalFieldCenter(FieldAvgHP);
   cout<<"Both beta UP and DOWN were fired for "<<count<<" times."<<endl;
}

void NMR::MakeSpec(){
   NumFreq = 0;

   cout<< freqset.size() <<" frequencies found:"<< endl;
   cout<<"id, Freq, CtsUp, CtsDown, Asymm, AsymmError"<<endl;
   for(itfreqset=freqset.begin(); itfreqset!=freqset.end(); itfreqset++){
      int ffreq = *itfreqset;
      int fup = CtsUp[ffreq], fdown = CtsDown[ffreq];
      gFreq[NumFreq] = ffreq;
      gAsymm[NumFreq] = (double)(fup - fdown)/(fup + fdown);
      //gFreqErr[NumFreq] = Mod;
      gFreqErr[NumFreq] = 0;
      gAsymmErr[NumFreq] = sqrt(4.0*fup*fdown/pow(fup+fdown,3));
      cout<<NumFreq<<", "<<ffreq<<", "<<fup<<", "<<fdown<<", "<<gAsymm[NumFreq]<<", "<<gAsymmErr[NumFreq]<<endl;
      NumFreq++;
   }
   cout<<"Total Data taking time: "<<time/1000./60<<" min."<<endl;
   gSpec = new TGraphErrors(NumFreq,gFreq,gAsymm,gFreqErr,gAsymmErr);
   gSpec->SetMarkerStyle(20);
   gSpec->SetLineWidth(0);
   gSpec->SetMarkerSize(1);
   gSpec->GetXaxis()->SetTitle("Freq. [kHz]");
   gSpec->GetYaxis()->SetTitle("Asymm.");
   if(NMRorNQR==0){
      gSpec->SetTitle("NMR");
      gSpec->SetName("NMR");
   }else if(NMRorNQR==1){
      gSpec->SetTitle("NQR");
      gSpec->SetName("NQR");
   }else{
      return;
   }

   //g1->Draw("AP");

   gTiD3_T = new TGraph(TiD3_T.size());
   gTiD3_T_cut = new TGraph(TiD3_T_cut.size());
   for(int i=0; i<(int)TiD3_T.size(); i++){
      gTiD3_T->SetPoint(i, TiD3_T[i].first, TiD3_T[i].second-10);
   }
   for(int i=0; i<(int)TiD3_T_cut.size(); i++){
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

void NMR::PlotSpec(){
   TCanvas *c1;
   if(gROOT->FindObject("c1")!=0){
      c1 = (TCanvas*)gROOT->FindObject("c1");
   }else{
      c1 = new TCanvas("c1","c1",0,0,800,1000);
      c1->Divide(1,2);
   }
   c1->cd(1);
   gSpec->Draw("AP");
   if(IfTiD3 == 1){
      c1->cd(2);
      gTiD3_T->Draw("APL");
      gTiD3_T_cut->Draw("PL");
   }
}

void NMR::SaveSpec(){
   std::ostringstream file_png;
   string folder = "figure/";
   string _png = ".png";
   string Eup = "Eup";
   string Edown = "Edown";
   file_png << folder << Eup << EUpMin << Edown << EDownMin << _png;
   TCanvas *c2 = (TCanvas*)gROOT->FindObject("c2");
   string sfile_png = file_png.str();
   c2->SaveAs(sfile_png.c_str());
}


void SetLatex(TString &content, const char* parname, double para, double error, const char* unit = ""){
   content = parname;
   content += " = ";
   char tpara[200], terror[200]; //truncated value
   sprintf(tpara, "%.1f", para);
   sprintf(terror, "%.1f", error);
   content += tpara;
   if(error != 0){
      content += " +/- ";
      content += terror;
   }
   content += " ";
   content += unit;
   //cout<<"come here"<<endl;
}

void NMR::Bootstrapping(){

   if (fChain == 0) return;
   IfTiD3 = 0;

   Long64_t nentries = fChain->GetEntries();
   cout<<"total number of events = "<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   TRandom3 * rand = new TRandom3();
   rand->SetSeed(0);
   std::vector<Long64_t> randarray;//array to store random numbers
   std::vector<Long64_t>::iterator itrandarray; //the iterator of the array

   Long64_t nevents = nentries;
   for(Long64_t jjentry = 0; jjentry<nevents; jjentry++){
      Long64_t jentry = rand->Integer(nentries);
      randarray.push_back(jentry);
   }
   std::sort(randarray.begin(), randarray.end() );

   Long64_t index = 0;
   for(itrandarray=randarray.begin(); itrandarray!=randarray.end(); itrandarray++){
      if(index%500000==0){
         cout<<index<<" events picked up..."<<endl;
      }
      Long64_t jentry = (Long64_t)*itrandarray;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(FLAG==100 || FIELD ==0){
         index++;
         continue;
      }

      int freq;
      if(NMRorNQR==0){//NMR data
         freq = FREQ;
      }else if(NMRorNQR==1){//NRQ data
         if(RF_OFF_ON==1000){
            freq = FREQ2;
         }else{
            freq = FREQ;
         }
      }else{
         break;
      }

      // if (Cut(ientry) < 0) continue;
      bool GoUp = false, GoDown = false;
      if(TAC_Up>TACUpMin && TAC_Up<TACUpMax && E_Up>EUpMin && E_Up<EUpMax && E_deltaUp>EDeltaUpMin && E_deltaUp<EDeltaUpMax){
         GoUp = true;
      }
      if(TAC_Down>TACDownMin && TAC_Down<TACDownMax && E_Down>EDownMin && E_Down<EDownMax && E_deltaDown>EDeltaDownMin && E_deltaDown<EDeltaDownMax){
         GoDown = true;
      }
      ////just for test, to sum RF-OFF freq at different position.
      //if(freq>2260 && freq<2900){
      //   freq = 2500;
      //}

      if(GoUp){
         CtsUp[freq]++;
      }
      if(GoDown){
         CtsDown[freq]++;
      }
      freqset.insert(freq);
      index++;
   }
}

void NMR::FitSpec(int type, double fit_low, double fit_high){
   ReadFitPara("NMR_NQR_fit.in");
   TF1 *f1;
   if(type == 0){
      f1 = new TF1("f1",LineShapeMarieke,fit_low,fit_high,5);
   }else if(type == 1){
      f1 = new TF1("f1",LineShapeRamp,fit_low,fit_high,5);
   }else{
      f1 = new TF1("f1",LineShapeSine,fit_low,fit_high,5);
   }
   f1->SetParName(0,"Baseline");
   f1->SetParName(1,"Amplitude");
   f1->SetParName(2,"Centroid");
   f1->SetParName(3,"Modulation");
   f1->SetParName(4,"Width");
   f1->SetParameter(0,BaseL); f1->SetParLimits(0,BaseL_low,BaseL_high);
   f1->SetParameter(1,Amp); f1->SetParLimits(1,Amp_low,Amp_high);
   f1->SetParameter(2,Centroid); f1->SetParLimits(2,Centroid_low,Centroid_high);
   f1->SetParameter(3,Mod); f1->SetParLimits(3,Mod_low,Mod_high);
   f1->SetParameter(4,Width); f1->SetParLimits(4,Width_low,Width_high);
   gSpec->Fit("f1","EMR","D");
   double chi2 = f1->GetChisquare();
   double NDF = f1->GetNDF();
   cout<<"Chi2/NDF = "<<chi2/NDF<<endl;
   cout<<"Baseline = "<<f1->GetParameter(0)<<" +/- "<<f1->GetParError(0)<<endl;
   cout<<"Amplitude = "<<f1->GetParameter(1)<<" +/- "<<f1->GetParError(1)<<endl;
   cout<<"Centroid = "<<f1->GetParameter(2)<<" +/- "<<f1->GetParError(2)<<endl;
   cout<<"Modulation = "<<f1->GetParameter(3)<<" +/- "<<f1->GetParError(3)<<endl;
   cout<<"Width = "<<f1->GetParameter(4)<<" +/- "<<f1->GetParError(4)<<endl;

   if(gROOT->FindObject("c2")!=0){
      gROOT->FindObject("c2")->Delete();
   }
   TCanvas* c2 = new TCanvas("c2","c2",0,0,800,500);
   c2->cd();
   gSpec->Draw("AP");

   //plot the fitting result to figure
   TLatex text0;
   TString content0;
   text0.SetTextSize(0.03);
   text0.SetTextAlign(13);
   text0.SetNDC();

   double posx;
   if(NMRorNQR==0){
      posx = 0.15;
   }else if(NMRorNQR==1){
      posx = 0.55;
   }else{
      return;
   }
   SetLatex(content0,"E_Up_cut",EUpMin,0,"[ch]");
   text0.DrawLatex(posx,0.85,content0);
   SetLatex(content0,"E_Down_cut",EDownMin,0,"[ch]");
   text0.DrawLatex(posx,0.80,content0);
   SetLatex(content0,"Centroid",f1->GetParameter(2),f1->GetParError(2),"[kHz]");
   text0.DrawLatex(posx,0.75,content0);
   SetLatex(content0,"Width",f1->GetParameter(4),f1->GetParError(4),"[kHz]");
   text0.DrawLatex(posx,0.70,content0);
   SetLatex(content0,"Amplitude",f1->GetParameter(1)*1000,f1->GetParError(1)*1000,"[x10^{-3}]");
   text0.DrawLatex(posx,0.65,content0);
   SetLatex(content0,"Baseline",f1->GetParameter(0)*1000,f1->GetParError(0)*1000,"[x10^{-3}]");
   text0.DrawLatex(posx,0.60,content0);
}

double gFactorNMR(double LarmorFreq, double MagField){//larmor freq. in the unit of MHz, MagField in the unit of Gauss;
   const double h_planck = 4.13566766e-12;//in the unit of eV*us
   const double NuclMageton = 3.152451e-12;
   double gfn = LarmorFreq * h_planck / MagField / NuclMageton;
   return gfn;
}

void A_Divided_by_B(double A, double Aerr, double B, double Berr){
   double C = A/B;
   double Cerr = sqrt(Aerr*Aerr/A/A+Berr*Berr/B/B)*C;
   cout<<"C = "<<C<<", error = "<<Cerr<<endl;
}

void QuadNQR(double nuQ, double nuQerror){
   A_Divided_by_B(nuQ,nuQerror,16.39,0.11);
}

void A_Times_B(double A, double Aerr, double B, double Berr){
   double C = A*B;
   double Cerr = sqrt(Aerr*Aerr/A/A+Berr*Berr/B/B)*C;
   cout<<"C = "<<C<<", error = "<<Cerr<<endl;
}
