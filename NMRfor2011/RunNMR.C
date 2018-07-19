{
   gROOT->ProcessLine(".L NMR.C+");
   TChain *AutoTree = new TChain ("AutoTree");
   /******* NMR Runs ********/
   ////34Al, NMR, Mod = 7 kHz
   //AutoTree->Add("root-files/run157.root");
   //AutoTree->Add("root-files/run158.root");

   ////34Al, NMR, Mod = 4 kHz, different steps
   //AutoTree->Add("root-files/run164.root");

   ////34Al, NMR, Mod = 7 kHz, different steps
   //AutoTree->Add("root-files/run166.root");
   //AutoTree->Add("root-files/run167.root");

   /******* NQR Runs ********/
   //34Al, NQR, Mod = 350 kHz
   AutoTree->Add("root-files/run160.root");
   AutoTree->Add("root-files/run161.root");
   AutoTree->Add("root-files/run162.root");
   AutoTree->Add("root-files/run163.root");
   AutoTree->Add("root-files/run168.root");
   AutoTree->Add("root-files/run169.root");
   AutoTree->Add("root-files/run170.root");
   AutoTree->Add("root-files/run171.root");
   AutoTree->Add("root-files/run172.root");
   AutoTree->Add("root-files/run173.root");
   AutoTree->Add("root-files/run174.root");
   AutoTree->Add("root-files/run175.root");
   AutoTree->Add("root-files/run176.root");
   AutoTree->Add("root-files/run177.root");
   AutoTree->Add("root-files/run178.root");

   NMR *t = new NMR("",AutoTree);

   ////for normal analysis
   //t->ReadPara("NMR_NQR.in");
   //t->Analysis();
   //t->MakeSpec();
   //t->PlotSpec();

   ////for bootstrapping
   //char pngname[128];
   //char filename1[128];
   //char filename2[128];
   //char filename3[128];
   //sprintf(filename1,"figure//34gAl_NQR_Mod350_bootstrap/centroid.txt");
   //sprintf(filename2,"figure//34gAl_NQR_Mod350_bootstrap/amplitude.txt");
   //sprintf(filename3,"figure//34gAl_NQR_Mod350_bootstrap/asymm.txt");
   //FILE *result1 = fopen(filename1,"w");
   //FILE *result2 = fopen(filename2,"w");
   //FILE *result3 = fopen(filename3,"w");
   //const int dim = 8;
   //const int NumOfTimes = 4000;
   //fprintf(result3, "%d %d", NumOfTimes, dim);
   //int freq[dim] = {250, 750, 1250, 1750, 2250, 2750, 3250, 4400};
   //for(int i=0; i<dim; i++){
   //   fprintf(result3, " %d", freq[i]);
   //}
   //fprintf(result3, "\n");
   //for(int i = 0; i<NumOfTimes; i++){
   //   t->ReadPara("NMR_NQR.in");
   //   t->ReadFitPara("NMR_NQR_fit.in");
   //   t->Bootstrapping();
   //   t->MakeSpec();
   //   t->PlotSpec();
   //   t->FitSpec(0,0,4500);
   //   cout<<"************** i = "<<i<<": centroid = "<<t->FitCent<<" ***************"<<endl;
   //   sprintf(pngname,"figure//34gAl_NQR_Mod350_bootstrap/%04d.png",i+1);
   //   c2->SaveAs(pngname);
   //   fprintf(result1, "%d %.1f %d\n", i+1, t->FitCent, t->MaxAsymmFreq);
   //   fprintf(result2, "%d %.1f %.1f\n", i+1, t->FitAmp*(-1e3), t->FitAmpError*1e3);
   //   int NumFreq = t->NumFreq;
   //   fprintf(result3, "%d", i+1);
   //   for(int j=0; j<NumFreq; j++){
   //      fprintf(result3, " %f %f", t->VecAsymm[j], t->VecAsymmError[j]);
   //   }
   //   fprintf(result3, "\n");
   //}
   //fclose(result1);
   //fclose(result2);
   //fclose(result3);

   //for reading existing asymm file and redoing the fits
   char pngname[128];
   char filename1[128];
   char filename2[128];
   sprintf(filename1,"figure//34gAl_NQR_Mod350_bootstrap/2nd_trial_27March2017/centroid.txt");
   sprintf(filename2,"figure//34gAl_NQR_Mod350_bootstrap/2nd_trial_27March2017/amplitude.txt");
   FILE *result1 = fopen(filename1,"w");
   FILE *result2 = fopen(filename2,"w");
   int dim, NumOfLines;
   int *freq;
   double **VecAsymm, **VecAsymmError;
   ReadAsymmFile("figure/34gAl_NQR_Mod350_bootstrap/2nd_trial_27March2017/asymm.txt",NumOfLines, dim, freq, VecAsymm, VecAsymmError);
   for(int i = 0; i<NumOfLines; i++){
      t->ReadPara("NMR_NQR.in");
      t->ReadFitPara("NMR_NQR_fit.in");
      t->MakeSpec(dim, freq, VecAsymm[i], VecAsymmError[i]);
      t->PlotSpec();
      t->FitSpec(0,0,4500);
      cout<<"************** i = "<<i<<": centroid = "<<t->FitCent<<" ***************"<<endl;
      sprintf(pngname,"figure//34gAl_NQR_Mod350_bootstrap/2nd_trial_27March2017/%04d.png",i+1);
      c2->SaveAs(pngname);
      fprintf(result1, "%d %.1f %d\n", i+1, t->FitCent, t->MaxAsymmFreq);
      fprintf(result2, "%d %.1f %.1f\n", i+1, t->FitAmp*(-1e3), t->FitAmpError*1e3);
   }
   fclose(result1);
   fclose(result2);
}
