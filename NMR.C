#define NMR_cxx
#include <iostream>
#include <fstream>
#include "NMR.h"
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TText.h>
#include <TString.h>
#include <TRandom3.h>
#include <TLegend.h>
#include <sstream>
#include <algorithm>
#include <vector>

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
      }else if(strcmp(temp,"II2")==0){
         fscanf(fin,"%d",&II2);
      }else if(strcmp(temp,"IFFIELD")==0){
         fscanf(fin,"%d",&IfField);
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

void NMR::Analysis(int MergeLow, int MergeHigh, int MergeFreq)
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

   //create a new tree (in a new root file) for the gamma-ray analysis
   TFile* hfile=new TFile("figure/Tree_Gamma.root","RECREATE");
   double E[2], T[2];
   int ch[2];
   TTree *tree = new TTree("tree","A tree for gamma ray");
   tree->Branch("E",&E,"E[2]/D");
   tree->Branch("T",&T,"T[2]/D");
   tree->Branch("ch",&ch,"ch[2]/I");

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
      if(FLAG==100 || (IfField==1&&FIELD==0)){
         time_previous = time_present;
         continue;
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

      field_each_event = FIELD + FIELD2/10.0;
      ntotal++;
      FieldAvgHP = FieldAvgHP + field_each_event;

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
      if(freq>MergeLow && freq<MergeHigh){
         freq = MergeFreq;
      }
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
      h_GammaH_cal_notime->Fill(E_GammaH_cal);
      h_GammaAll_notime->Fill(E_GammaH_cal);
      if(TAC_Delta_gH>500 && TAC_Delta_gH<10000){
         h_GammaH_cal->Fill(E_GammaH_cal);
         h_GammaAll->Fill(E_GammaH_cal);
      }
      h_GammaG_cal_notime->Fill(E_GammaG_cal);
      h_GammaAll_notime->Fill(E_GammaG_cal);
      if(TAC_Delta_gG>500 && TAC_Delta_gG<10000){
         h_GammaG_cal->Fill(E_GammaG_cal);
         h_GammaAll->Fill(E_GammaG_cal);
      }
      if(TAC_Delta_gH>500 && TAC_Delta_gH<10000 && TAC_Delta_gG>500 && TAC_Delta_gG<10000){
         h_GG_Matrix->Fill(E_GammaH_cal,E_GammaG_cal);
      }
      E[0]=E_GammaH_cal;
      T[0]=TAC_Delta_gH;
      ch[0]=0;
      E[1]=E_GammaG_cal;
      T[1]=TAC_Delta_gG-1500;
      ch[1]=1;
      tree->Fill();
      h_EUp->Fill(E_Up);
      h_EDown->Fill(E_Down);
      freqset.insert(freq);
   }
   FieldAvgHP = FieldAvgHP/ntotal;
   FieldAvgCenterBefore = CalFieldCenterBefore(FieldAvgHP);
   FieldAvgCenterAfter = CalFieldCenterAfter(FieldAvgHP);
   FieldAvgCenter = CalFieldCenter(FieldAvgHP);
   cout<<"Both beta UP and DOWN were fired for "<<count<<" times."<<endl;
   hfile->Write();
}

void NMR::MakeSpec(int dim, int* vecFreq, double* vecAsymm, double* vecAsymmError){

   cout<< dim <<" frequencies found:"<< endl;
   gSpec = new TGraphErrors(dim);
   double MaxAsymm = 0;
   if(Amp>0){
      MaxAsymm = -1;
   }else if(Amp<0){
      MaxAsymm = 1;
   }
   for(int i=0; i<dim; i++){
      int ffreq = vecFreq[i];
      double gAsymm = vecAsymm[i];
      double gAsymmErr = vecAsymmError[i];
      cout<<i<<", "<<ffreq<<", "<<gAsymm<<", "<<gAsymmErr<<endl;
      //for NQR spectrum, plot Delta rather than Q_nu
      double Delta=0;
      if(NMRorNQR == 1){
         Delta = 3.0/(2*II2*(II2-1))*ffreq;
      }else{
         Delta = ffreq;
      }
      gSpec->SetPoint(i, Delta, gAsymm);
      double ModDelta;
      if(NMRorNQR == 1){
         ModDelta = 3.0/(2*II2*(II2-1))*Mod;
      }else{
         ModDelta = Mod;
      }
      gSpec->SetPointError(i, ModDelta, gAsymmErr);
      VecAsymm.push_back(gAsymm);
      VecAsymmError.push_back(gAsymmErr);
      if(Amp>0){
         if(gAsymm > MaxAsymm){
            MaxAsymmFreq = ffreq;
            MaxAsymm = gAsymm;
         }
      }else if(Amp<0){
         if(gAsymm < MaxAsymm){
            MaxAsymmFreq = ffreq;
            MaxAsymm = gAsymm;
         }
      }
   }
   gSpec->SetMarkerStyle(20);
   gSpec->SetMarkerSize(1);
   gSpec->GetXaxis()->SetNdivisions(208);
   gSpec->GetYaxis()->SetNdivisions(408);
   //gSpec->SetLineWidth(0);
   //gSpec->GetXaxis()->SetTitle("Freq. [kHz]");
   //gSpec->GetYaxis()->SetTitle("Asymm.");
   if(NMRorNQR==0){
      gSpec->SetTitle("NMR");
      gSpec->SetTitle("");
      gSpec->SetName("NMR");
   }else if(NMRorNQR==1){
      gSpec->SetTitle("NQR");
      gSpec->SetTitle("");
      gSpec->SetName("NQR");
   }else{
      return;
   }
}

void NMR::MakeSpec(){
   NumFreq = 0;

   cout<< freqset.size() <<" frequencies found:"<< endl;
   cout<<"id, Freq, CtsUp, CtsDown, Asymm, AsymmError"<<endl;
   gSpec = new TGraphErrors(freqset.size());
   double MaxAsymm = 0;
   if(Amp>0){
      MaxAsymm = -1;
   }else if(Amp<0){
      MaxAsymm = 1;
   }
   for(itfreqset=freqset.begin(); itfreqset!=freqset.end(); itfreqset++){
      int ffreq = *itfreqset;
      int fup = CtsUp[ffreq], fdown = CtsDown[ffreq];
      double gAsymm = (double)(fup - fdown)/(fup + fdown);
      double gAsymmErr = sqrt(4.0*fup*fdown/pow(fup+fdown,3));
      cout<<NumFreq<<", "<<ffreq<<", "<<fup<<", "<<fdown<<", "<<gAsymm<<", "<<gAsymmErr<<endl;
      //for NQR spectrum, plot Delta rather than Q_nu
      double Delta=0;
      if(NMRorNQR == 1){
         Delta = 3.0/(2*II2*(II2-1))*ffreq;
      }else{
         Delta = ffreq;
      }
      gSpec->SetPoint(NumFreq, Delta, gAsymm);
      double ModDelta;
      if(NMRorNQR == 1){
         ModDelta = 3.0/(2*II2*(II2-1))*Mod;
      }else{
         ModDelta = Mod;
      }
      gSpec->SetPointError(NumFreq, ModDelta, gAsymmErr);
      VecAsymm.push_back(gAsymm);
      VecAsymmError.push_back(gAsymmErr);
      if(Amp>0){
         if(gAsymm > MaxAsymm){
            MaxAsymmFreq = ffreq;
            MaxAsymm = gAsymm;
         }
      }else if(Amp<0){
         if(gAsymm < MaxAsymm){
            MaxAsymmFreq = ffreq;
            MaxAsymm = gAsymm;
         }
      }
      NumFreq++;
   }
   cout<<"Total Data taking time: "<<time/1000./60<<" min."<<endl;
   gSpec->SetMarkerStyle(20);
   gSpec->SetMarkerSize(1);
   gSpec->GetXaxis()->SetNdivisions(208);
   gSpec->GetYaxis()->SetNdivisions(408);
   //gSpec->SetLineWidth(0);
   //gSpec->GetXaxis()->SetTitle("Freq. [kHz]");
   //gSpec->GetYaxis()->SetTitle("Asymm.");
   if(NMRorNQR==0){
      gSpec->SetTitle("NMR");
      gSpec->SetTitle("");
      gSpec->SetName("NMR");
   }else if(NMRorNQR==1){
      gSpec->SetTitle("NQR");
      gSpec->SetTitle("");
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

void NMR::Bootstrapping(int MergeLow, int MergeHigh, int MergeFreq){

   if (fChain == 0) return;
   IfTiD3 = 0;

   Long64_t nentries = fChain->GetEntries();
   cout<<"total number of events = "<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   TRandom3 * rand = new TRandom3();
   rand->SetSeed(0);
   std::vector<Long64_t> randarray;//array to store random numbers
   std::vector<Long64_t>::iterator itrandarray; //the iterator of the array

   Long64_t nevents = nentries;//number of random sample is the same as the number of real events
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

      if(FLAG==100 || FIELD==0){
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
      //just for test, to sum RF-OFF freq at different position.
      if(freq>MergeLow && freq<MergeHigh){
         freq = MergeFreq;
      }
      ////just for 34mAl to remove the first data point with different baseline.
      //if(freq<1400){
      //   index++;
      //   continue;
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

void NMR::FitSpecCompare(double fit_low, double fit_high){
   ReadFitPara("NMR_NQR_fit.in");
   TF1 *f1, *f2, *f3, *f4, *f5;

   f1 = new TF1("f1",LineShapeMarieke,fit_low,fit_high,5);
   f2 = new TF1("f2",LineShapeRamp,fit_low,fit_high,5);
   f3 = new TF1("f3",LineShapeSine,fit_low,fit_high,5);
   f4 = new TF1("f4",LineShapeLorentz,fit_low,fit_high,5);
   f5 = new TF1("f5",LineShapeGaussian,fit_low,fit_high,5);

   f1->SetParameter(0,BaseL); f1->SetParLimits(0,BaseL_low,BaseL_high);
   f1->SetParameter(1,Amp); f1->SetParLimits(1,Amp_low,Amp_high);
   f1->SetParameter(2,Centroid); f1->SetParLimits(2,Centroid_low,Centroid_high);
   f1->SetParameter(3,Mod); f1->SetParLimits(3,Mod_low,Mod_high);
   f1->SetParameter(4,Width); f1->SetParLimits(4,Width_low,Width_high);
   f1->SetLineColor(1);

   f2->SetParameter(0,BaseL); f2->SetParLimits(0,BaseL_low,BaseL_high);
   f2->SetParameter(1,Amp); f2->SetParLimits(1,Amp_low,Amp_high);
   f2->SetParameter(2,Centroid); f2->SetParLimits(2,Centroid_low,Centroid_high);
   f2->SetParameter(3,Mod); f2->SetParLimits(3,Mod_low,Mod_high);
   f2->SetParameter(4,Width); f2->SetParLimits(4,Width_low,Width_high);
   f2->SetLineColor(2);

   f3->SetParameter(0,BaseL); f3->SetParLimits(0,BaseL_low,BaseL_high);
   f3->SetParameter(1,Amp); f3->SetParLimits(1,Amp_low,Amp_high);
   f3->SetParameter(2,Centroid); f3->SetParLimits(2,Centroid_low,Centroid_high);
   f3->SetParameter(3,Mod); f3->SetParLimits(3,Mod_low,Mod_high);
   f3->SetParameter(4,Width); f3->SetParLimits(4,Width_low,Width_high);
   f3->SetLineColor(4);

   f4->SetParameter(0,BaseL); f4->SetParLimits(0,BaseL_low,BaseL_high);
   f4->SetParameter(1,Amp); f4->SetParLimits(1,Amp_low,Amp_high);
   f4->SetParameter(2,Centroid); f4->SetParLimits(2,Centroid_low,Centroid_high);
   f4->FixParameter(3,0);
   f4->SetParameter(4,Width); f4->SetParLimits(4,Width_low,Width_high);
   f4->SetLineColor(6);

   f5->SetParameter(0,BaseL); f5->SetParLimits(0,BaseL_low,BaseL_high);
   f5->SetParameter(1,Amp); f5->SetParLimits(1,Amp_low,Amp_high);
   f5->SetParameter(2,Centroid); f5->SetParLimits(2,Centroid_low,Centroid_high);
   f5->FixParameter(3,0);
   f5->SetParameter(4,Width); f5->SetParLimits(4,Width_low,Width_high);
   f5->SetLineColor(7);

   gSpec->Fit("f1","EMR0","D");
   gSpec->Fit("f2","EMR0","D");
   gSpec->Fit("f3","EMR0","D");
   gSpec->Fit("f4","EMR0","D");
   gSpec->Fit("f5","EMR0","D");

   TCanvas *c2;
   if(gROOT->FindObject("c2")!=0){
      c2 = (TCanvas*) gROOT->FindObject("c2");
   }else{
      c2 = new TCanvas("c2","c2",0,0,800,500);
   }
   c2->cd();
   gSpec->Draw("AP");
   f1->Draw("same");
   f2->Draw("same");
   f3->Draw("same");
   f4->Draw("same");
   f5->Draw("same");

   TLegend *lg = new TLegend(0.55,0.55,0.9,0.9,"");
   lg->SetBorderSize(0);
   lg->SetFillColor(0);
   lg->SetFillStyle(0);
   lg->AddEntry(f1,"Lineshape A","L");
   lg->AddEntry(f2,"Lineshape B","L");
   lg->AddEntry(f3,"Lineshape C","L");
   lg->AddEntry(f4,"Lineshape D","L");
   lg->AddEntry(f5,"Lineshape E","L");
   lg->Draw();
}

void NMR::FitSpec(int type, double fit_low, double fit_high, double bin_low, double bin_high, int IfText, const char* canvas, int index_all, int index){
   ReadFitPara("NMR_NQR_fit.in");
   TF1 *f1;
   if(type == 0){
      f1 = new TF1("f1",LineShapeMarieke,fit_low,fit_high,5);
   }else if(type == 1){
      f1 = new TF1("f1",LineShapeRamp,fit_low,fit_high,5);
   }else if(type == 2){
      f1 = new TF1("f1",LineShapeSine,fit_low,fit_high,5);
   }else if(type == 3){
      f1 = new TF1("f1",LineShapeGaussian,fit_low,fit_high,5);
   }else{
      f1 = new TF1("f1",LineShapeLorentz,fit_low,fit_high,5);
   }

   f1->SetParName(0,"Baseline");
   f1->SetParName(1,"Amplitude");
   f1->SetParName(2,"Centroid");
   f1->SetParName(3,"Modulation");
   f1->SetParName(4,"Width");
   f1->SetParameter(0,BaseL); f1->SetParLimits(0,BaseL_low,BaseL_high);
   f1->SetParameter(1,Amp); f1->SetParLimits(1,Amp_low,Amp_high);
   f1->SetParameter(2,Centroid); f1->SetParLimits(2,Centroid_low,Centroid_high);
   if(type==0 || type==1 || type==2){
      //translate from modulation on Q_nu to modulation on Delta
      double ModDelta, ModDelta_low, ModDelta_high;
      if(NMRorNQR == 1){
         ModDelta = 3.0/(2*II2*(II2-1))*Mod;
         ModDelta_low = 3.0/(2*II2*(II2-1))*Mod_low;
         ModDelta_high = 3.0/(2*II2*(II2-1))*Mod_high;
      }else{
         ModDelta = Mod;
         ModDelta_low = Mod_low;
         ModDelta_high = Mod_high;
      }
      f1->SetParameter(3,ModDelta); f1->SetParLimits(3,ModDelta_low,ModDelta_high);
   }else{
      f1->FixParameter(3,0);
   }
   f1->SetParameter(4,Width); f1->SetParLimits(4,Width_low,Width_high);
   gSpec->Fit("f1","EMR0","D");
   double chi2 = f1->GetChisquare();
   double NDF = f1->GetNDF();
   cout<<"Chi2/NDF = "<<chi2/NDF<<endl;
   cout<<"BModseline = "<<f1->GetParameter(0)<<" +/- "<<f1->GetParError(0)<<endl;
   cout<<"Amplitude = "<<f1->GetParameter(1)<<" +/- "<<f1->GetParError(1)<<endl;
   cout<<"Centroid = "<<f1->GetParameter(2)<<" +/- "<<f1->GetParError(2)<<endl;
   cout<<"Modulation = "<<f1->GetParameter(3)<<" +/- "<<f1->GetParError(3)<<endl;
   cout<<"Width = "<<f1->GetParameter(4)<<" +/- "<<f1->GetParError(4)<<endl;
   FitCent = f1->GetParameter(2);
   FitCentError = f1->GetParError(2);
   FitAmp = f1->GetParameter(1);
   FitAmpError = f1->GetParError(1);

   //double bl = f1->GetParameter(0);
   //double bll = f1->GetParameter(0)-f1->GetParError(0);
   //double blh = f1->GetParameter(0)+f1->GetParError(0);
   TCanvas *c2;
   gStyle->SetPadBorderMode(0);
   if(gROOT->FindObject(canvas)!=0){
      c2 = (TCanvas*) gROOT->FindObject(canvas);
   }else{
      c2 = new TCanvas(canvas,canvas,0,0,600,400*index_all);
      c2->Divide(1,index_all,0,0);
   }
   c2->cd(index);
   c2->cd(index)->SetRightMargin(0.01);
   gSpec->GetXaxis()->SetLimits(bin_low, bin_high);
   gSpec->Draw("AP");
   f1->Draw("same");

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
   if(IfText == 1){
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
}

void NMR::DrawBaseLine(double bl, double ble, double bin_low, double bin_high, const char* canvas, int index_all, int index){
   //only draw the spectrum with baseline
   TF1 *f2, *f2_l, *f2_h;
   f2 = new TF1("f2","pol0",bin_low,bin_high);
   f2_l = new TF1("f2_l","pol0",bin_low,bin_high);
   f2_h = new TF1("f2_h","pol0",bin_low,bin_high);

   TCanvas *c2;
   gStyle->SetPadBorderMode(0);
   if(gROOT->FindObject(canvas)!=0){
      c2 = (TCanvas*) gROOT->FindObject(canvas);
   }else{
      c2 = new TCanvas(canvas,canvas,0,0,600,400*index_all);
      c2->Divide(1,index_all,0,0);
   }
   c2->cd(index);
   c2->cd(index)->SetRightMargin(0.01);
   gSpec->GetXaxis()->SetLimits(bin_low, bin_high);
   gSpec->Draw("AP");

   double bll = bl-ble;
   double blh = bl+ble;
   f2->SetParameter(0,bl);
   f2_l->SetParameter(0,bll);
   f2_l->SetLineStyle(2);
   f2_h->SetParameter(0,blh);
   f2_h->SetLineStyle(2);

   f2->Draw("same");
   f2_l->Draw("same");
   f2_h->Draw("same");
}


double gFactorNMR(double LarmorFreq, double LarmorFreqErr, double MagField, double MagFieldErr){//larmor freq. in the unit of kHz, MagField in the unit of Gauss;
   const double h_planck = 4.13566766e-12;//in the unit of eV*ms
   const double NuclMageton = 3.152451e-12;//in the unit of eV/gauss
   double gfn = LarmorFreq / MagField * h_planck / NuclMageton;
   double f1 = LarmorFreqErr/LarmorFreq;
   double f2 = MagFieldErr/MagField;
   double gfnerr = sqrt(f1*f1+f2*f2)*gfn;
   cout << "Error = "<<gfnerr<<endl;
   return gfn;
}

void A_Divided_by_B(double A, double Aerr, double B, double Berr){
   double C = A/B;
   double Cerr = sqrt(Aerr*Aerr/A/A+Berr*Berr/B/B)*C;
   cout<<"C = "<<C<<", error = "<<Cerr<<endl;
}

void QuadNQR(double nuQ, double nuQerror){//nuQ in kHz, Q in mb
   A_Divided_by_B(nuQ,nuQerror,16.39,0.11);
}

void A_Times_B(double A, double Aerr, double B, double Berr){
   double C = A*B;
   double Cerr = sqrt(Aerr*Aerr/A/A+Berr*Berr/B/B)*C;
   cout<<"C = "<<C<<", error = "<<Cerr<<endl;
}

int ReadDataPoint(const char* filename, vector<int> &IntArray, vector<float> &NumArray1, vector<float> &NumArray2){
   int index;
   float num1, num2;
   FILE *fin = fopen(filename,"r");
   int i = 0;
   IntArray.clear();
   NumArray1.clear();
   NumArray2.clear();
   while(fscanf(fin,"%d %f %f",&index,&num1,&num2)==3){
      IntArray.push_back(index);
      NumArray1.push_back(num1);
      NumArray2.push_back(num2);
      i++;
   }
   cout<<"total dim = "<<i<<endl;
   return i;
}

void PlotDataPoint(const char* filename, int type){ //type=0: normal mean value, type=1: weighted mean value
   vector<int> IndexArray;
   vector<float> NumArray, ErrorArray;
   int dim = ReadDataPoint(filename, IndexArray, NumArray, ErrorArray);
   TGraphErrors* gData = new TGraphErrors(dim);
   float Mean = 0, MeanError = 0, MeanDev = 0;
   float SumSigma = 0;
   for(int i=0; i<dim; i++){
      gData->SetPoint(i, IndexArray[i], NumArray[i]);
      gData->SetPointError(i, 0, ErrorArray[i]);
   }

   if(type == 0){
      for(int i=0; i<dim; i++){
         cout<<"i = "<<i<<", num = "<<NumArray[i]<<", error = "<<ErrorArray[i]<<endl;
         Mean = Mean + NumArray[i]/dim;
         MeanError = MeanError + ErrorArray[i]/dim;
      }
      for(int i=0; i<dim; i++){
         MeanDev = MeanDev + pow((NumArray[i]-Mean),2)/(dim-1);
      }
      MeanDev = sqrt(MeanDev);
   }else if(type == 1){
      MeanError = 100;
      for(int i=0; i<dim; i++){
         cout<<"i = "<<i<<", num = "<<NumArray[i]<<", error = "<<ErrorArray[i]<<endl;
         Mean = Mean + NumArray[i]/pow(ErrorArray[i],2);
         SumSigma = SumSigma + 1/pow(ErrorArray[i],2);
         if(ErrorArray[i]<MeanError){
            MeanError = ErrorArray[i];
         }
     }
      Mean = Mean/SumSigma;
      MeanError = sqrt(1/SumSigma);
      MeanDev = 0;
   }
   float TotalError = sqrt(MeanError*MeanError + MeanDev*MeanDev);
   cout<<"Mean = "<<Mean<<", MeanDev = "<<MeanDev<<", TotalError = "<<TotalError<<endl;

   TGraph* gMean = new TGraph(2);
   TGraph* gDev = new TGraph(4);
   TGraph* gError = new TGraph(4);

   float offset = 0.5*fabs(IndexArray[0]-IndexArray[1]);
   gMean->SetPoint(0, IndexArray[0]-offset, Mean);
   gMean->SetPoint(1, IndexArray[dim-1]+offset, Mean);
   gMean->SetLineWidth(3);

   gDev->SetPoint(0, IndexArray[0]-offset, Mean+MeanDev);
   gDev->SetPoint(1, IndexArray[dim-1]+offset, Mean+MeanDev);
   gDev->SetPoint(2, IndexArray[dim-1]+offset, Mean-MeanDev);
   gDev->SetPoint(3, IndexArray[0]-offset, Mean-MeanDev);
   gDev->SetFillStyle(1001);
   gDev->SetFillColor(12);

   gError->SetPoint(0, IndexArray[0]-offset, Mean+TotalError);
   gError->SetPoint(1, IndexArray[dim-1]+offset, Mean+TotalError);
   gError->SetPoint(2, IndexArray[dim-1]+offset, Mean-TotalError);
   gError->SetPoint(3, IndexArray[0]-offset, Mean-TotalError);
   gError->SetFillStyle(1001);
   gError->SetFillColor(16);

   gData->SetTitle("Centroid vs. Energy cut");
   gData->GetYaxis()->SetNdivisions(508);
   gData->GetYaxis()->SetTitle("Centroid (kHz)");
   gData->GetYaxis()->CenterTitle(true);
   gData->GetYaxis()->SetTitleOffset(1.2);
   gData->GetXaxis()->SetTickLength(-0.03);
   gData->GetXaxis()->SetLabelOffset(0.02);
   gData->GetXaxis()->SetTitleOffset(1.2);
   gData->GetXaxis()->SetNdivisions(508);
   gData->GetXaxis()->SetTitle("Energy cut (a.u.)");
   gData->GetXaxis()->CenterTitle(true);
   gData->SetMarkerStyle(21);
   gData->SetMarkerSize(1.3);
   gData->Draw("AP");
   gError->Draw("f");
   gDev->Draw("f");
   gMean->Draw("L");
   gData->Draw("P");
}

TH1F* PlotHistogram(const char* filename, int index, int numbin, int bin1, int bin2){
   vector<int> IndexArray;
   vector<float> NumArray1, NumArray2;
   int dim = ReadDataPoint(filename, IndexArray, NumArray1, NumArray2);
   TH1F* h1 = new TH1F("h1", "Centroid distribution", numbin, bin1, bin2);
   for(int i=0; i<dim; i++){
      if(index == 0){
         h1->Fill(NumArray1[i]);
      }else if(index == 1){
         h1->Fill(NumArray2[i]);
      }
   }
   h1->GetXaxis()->SetNdivisions(508);
   h1->GetXaxis()->SetTitle("Centroid (kHz)");
   h1->GetXaxis()->CenterTitle(true);
   h1->GetXaxis()->SetTickLength(-0.03);
   return h1;
}

void ReadAsymmFile(const char* filename, int& numOfLines, int& dim, int*& freq, double**& vecAsymm, double**& vecAsymmError){
   //here I need to change the address of the pointer so the argument is the
   //reference of the pointer
   numOfLines = 0;
   int NumOfLines, Dim;
   int * Freq;
   double ** VecAsymm;
   double ** VecAsymmError;
   ifstream in;
   in.open(filename);
   std::string line;
   std::getline(in, line);
   std::istringstream ss(line);
   ss >> NumOfLines >> Dim;
   Freq = new int[Dim];
   VecAsymm = new double* [NumOfLines];
   VecAsymmError = new double* [NumOfLines];
   for(int i=0; i<Dim; i++){
      ss >> Freq[i];
   }
   for(int i=0; i<NumOfLines; i++){
      VecAsymm [i] = new double [Dim];
      VecAsymmError[i] = new double [Dim];
   }
   while ( std::getline(in, line) ){
      int index;
      std::istringstream ss1(line);
      ss1 >> index;
      for(int i=0; i<Dim; i++){
         ss1 >> VecAsymm[index-1][i] >> VecAsymmError[index-1][i];
         cout << VecAsymm[index-1][i] <<", "<< VecAsymmError[index-1][i]<<endl;
      }
   }
   dim = Dim;
   numOfLines = NumOfLines;
   freq = Freq;
   vecAsymm = VecAsymm;
   vecAsymmError = VecAsymmError;
}
