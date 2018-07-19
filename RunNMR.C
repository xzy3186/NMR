{
   gROOT->ProcessLine(".L NMR.C+");
   TChain *AutoTree = new TChain ("AutoTree");
   /******* NMR Runs ********/
   ////32Al, NMR, Mod = 3 kHz
   //AutoTree->Add("root-files/r0092.root");
   //AutoTree->Add("root-files/r0093.root");
   //AutoTree->Add("root-files/r0095.root");

   ////32Al, NMR, Mod = 3 kHz, different steps
   //AutoTree->Add("root-files/r0096.root");

   ////32Al, NMR, Mod = 6 kHz
   //AutoTree->Add("root-files/r0087.root");
   //AutoTree->Add("root-files/r0088.root");
   //AutoTree->Add("root-files/r0089.root");
   //AutoTree->Add("root-files/r0090.root");
   //AutoTree->Add("root-files/r0091.root");

   ////32Al, NMR, Mod = 8 kHz
   //AutoTree->Add("root-files/r0081.root");
   //AutoTree->Add("root-files/r0082.root");
   //AutoTree->Add("root-files/r0083.root");
   //AutoTree->Add("root-files/r0084.root");
   //AutoTree->Add("root-files/r0085.root");

   ////32Al, NMR, Mod = 8 kHz, different steps
   //AutoTree->Add("root-files/r0150.root");

   ////32Al, NMR, Mod = 8 kHz, different steps
   //AutoTree->Add("root-files/r0151.root");

   ////32Al, NMR, Mod = 8 kHz, different steps
   //AutoTree->Add("root-files/r0152.root");

   ////32Al, NMR, Mod = 15 kHz
   //AutoTree->Add("root-files/r0154.root");

   ////32Al, NMR, Mod = 45 kHz
   //AutoTree->Add("root-files/r0097.root");

   ////32Al, NMR, Mod = 45 kHz, different RF power
   //AutoTree->Add("root-files/r0099.root");

   ////32Al, NMR, Mod = 45 kHz, different steps
   //AutoTree->Add("root-files/r0100.root");
   //AutoTree->Add("root-files/r0101.root");

   ////34gAl, NMR, Mod = 10 kHz
   //AutoTree->Add("root-files/r0145.root");

   ////34gAl, NMR, Mod = 10 kHz, different steps
   //AutoTree->Add("root-files/r0146.root");
   //AutoTree->Add("root-files/r0147.root");

   ////34gAl, NMR, Mod = 45 kHz
   //AutoTree->Add("root-files/r0148.root");
   //AutoTree->Add("root-files/r0149.root");

   //34mAl, NMR, Mod = 45 kHz
   AutoTree->Add("root-files/r0125.root");
   AutoTree->Add("root-files/r0127.root");
   AutoTree->Add("root-files/r0128.root");
   AutoTree->Add("root-files/r0129.root");
   AutoTree->Add("root-files/r0130.root");

   //34Al, NMR, Mod = 45 kHz, different RF power
   AutoTree->Add("root-files/r0131.root");
   AutoTree->Add("root-files/r0132.root");

   //34Al, NMR, Mod = 45 kHz, different RF power and off-rf frequency
   AutoTree->Add("root-files/r0157.root");
   AutoTree->Add("root-files/r0158.root");
   AutoTree->Add("root-files/r0159.root");
   AutoTree->Add("root-files/r0160.root");
   AutoTree->Add("root-files/r0164.root");
   AutoTree->Add("root-files/r0165.root");
   AutoTree->Add("root-files/r0166.root");
   AutoTree->Add("root-files/r0169.root");
   AutoTree->Add("root-files/r0170.root");
   AutoTree->Add("root-files/r0171.root");
   AutoTree->Add("root-files/r0172.root");
   AutoTree->Add("root-files/r0173.root");
   AutoTree->Add("root-files/r0175.root");
   AutoTree->Add("root-files/r0176.root");
   AutoTree->Add("root-files/r0177.root");

   ////34mAl, NMR, Mod = 45 kHz, different freq
   //AutoTree->Add("root-files/r0139.root");
   //AutoTree->Add("root-files/r0141.root");
   //AutoTree->Add("root-files/r0142.root");
   //AutoTree->Add("root-files/r0143.root");

   ////34mAl, NMR, Mod = 45 kHz, different freq
   //AutoTree->Add("root-files/r0122.root");
   //AutoTree->Add("root-files/r0124.root");


   ////34mAl, NMR, Mod = 15 kHz
   //AutoTree->Add("root-files/r0179.root");
   //AutoTree->Add("root-files/r0180.root");
   //AutoTree->Add("root-files/r0181.root");
   //AutoTree->Add("root-files/r0182.root");
   //AutoTree->Add("root-files/r0183.root");
   //AutoTree->Add("root-files/r0184.root");
   //AutoTree->Add("root-files/r0185.root");
   //AutoTree->Add("root-files/r0186.root");
   //AutoTree->Add("root-files/r0187.root");

   ////34mAl, NMR, Mod = 6 kHz
   //AutoTree->Add("root-files/r0133.root");
   //AutoTree->Add("root-files/r0135.root");
   //AutoTree->Add("root-files/r0136.root");
   //AutoTree->Add("root-files/r0137.root");
   //AutoTree->Add("root-files/r0138.root");

   /******* NQR Runs ********/
   ////32Al, NQR, Mod = 60 kHz
   //AutoTree->Add("root-files/r0102.root");

   ////32Al, NQR, Mod = 60 kHz, different steps
   //AutoTree->Add("root-files/r0155.root");
   //AutoTree->Add("root-files/r0156.root");

   ////32Al, NQR, Mod = 40 kHz
   //AutoTree->Add("root-files/r0103.root");
   //AutoTree->Add("root-files/r0105.root");
   //AutoTree->Add("root-files/r0107.root");

   ////32Al, NQR, Mod = 40 kHz, different Larmor frequency, no FIELD information
   //AutoTree->Add("root-files/r0108.root");

   ////34mAl, NQR, Mod = 60 kHz
   //AutoTree->Add("root-files/r0193.root");
   //AutoTree->Add("root-files/r0194.root");
   //AutoTree->Add("root-files/r0195.root");
   //AutoTree->Add("root-files/r0197.root");
   //AutoTree->Add("root-files/r0199.root");
   //AutoTree->Add("root-files/r0200.root");
   //AutoTree->Add("root-files/r0203.root");
   //AutoTree->Add("root-files/r0204.root");
   //AutoTree->Add("root-files/r0205.root");
   //AutoTree->Add("root-files/r0206.root");
   //AutoTree->Add("root-files/r0207.root");
   //AutoTree->Add("root-files/r0208.root");
   //AutoTree->Add("root-files/r0209.root");
   //AutoTree->Add("root-files/r0210.root");

   ////34mAl, NQR, Mod = 60 kHz, different Larmor frequency
   //AutoTree->Add("root-files/r0162.root");
   //AutoTree->Add("root-files/r0163.root");


   ////for normal analysis
   //NMR *t = new NMR("t1",AutoTree);

   //t->ReadPara("NMR_NQR.in");
   //t->ReadFitPara("NMR_NQR_fit.in");
   ////for NMR
   ////t->Analysis(2890,3000,2400);//frequencies between arg1 and arg2 will be combined as frequency arg3.
   //t->Analysis(2290,3000,2700);//frequencies between arg1 and arg2 will be combined as frequency arg3.
   ////t->Analysis(0,1000,1800);//frequencies between arg1 and arg2 will be combined as frequency arg3.
   ////special for presentation.
   ////t->Analysis(1800,2000,2100);//frequencies between arg1 and arg2 will be combined as frequency arg3.

   ////for NQR
   ////t->Analysis(3200,4000,3200);//frequencies between arg1 and arg2 will be combined as frequency arg3.
   //t->MakeSpec();

   //for 3 points
   NMR *t = new NMR("t1",AutoTree);
   t->ReadPara("NMR_NQR.in");
   t->ReadFitPara("NMR_NQR_fit.in");
   int dim, NumOfLines;
   int *freq;
   double **VecAsymm, **VecAsymmError;
   ReadAsymmFile("figure/34Al-NMR-6points-asymm.txt",NumOfLines, dim, freq, VecAsymm, VecAsymmError);
   t->MakeSpec(dim, freq, VecAsymm[0], VecAsymmError[0]);
   /*************************************************************************/

   t->PlotSpec();
   t->FitSpec(-1, 1800, 2800, 1800, 2800, 0, "c1");

   ////for bootstrapping
   //NMR *t = new NMR("t1",AutoTree);
   //char pngname[128];
   //char filename1[128];
   //char filename2[128];
   //char filename3[128];
   //sprintf(filename1,"figure//34mAl_NMR_Mod15_bootstrap/centroid.txt");
   //sprintf(filename2,"figure//34mAl_NMR_Mod15_bootstrap/amplitude.txt");
   //sprintf(filename3,"figure//34mAl_NMR_Mod15_bootstrap/asymm.txt");
   //FILE *result1 = fopen(filename1,"w");
   //FILE *result2 = fopen(filename2,"w");
   //FILE *result3 = fopen(filename3,"w");
   //for(int i = 0; i<4000; i++){
   //   t->ReadPara("NMR_NQR.in");
   //   t->ReadFitPara("NMR_NQR_fit.in");
   //   t->Bootstrapping(3000,4000,3000);
   //   t->MakeSpec();
   //   t->PlotSpec();
   //   t->FitSpec(0,1900,2350,1800,2400);
   //   cout<<"************** i = "<<i<<": centroid = "<<t->FitCent<<" ***************"<<endl;
   //   sprintf(pngname,"figure//34mAl_NMR_Mod15_bootstrap/%04d.png",i+1);
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

   ////for reading existing asymm file and redoing the fits
   //char pngname[128];
   //char filename1[128];
   //char filename2[128];
   //sprintf(filename1,"figure/34mAl_NMR_Mod15_bootstrap/test/centroid.txt");
   //sprintf(filename2,"figure/34mAl_NMR_Mod15_bootstrap/test/amplitude.txt");
   //FILE *result1 = fopen(filename1,"w");
   //FILE *result2 = fopen(filename2,"w");
   //int dim, NumOfLines;
   //int *freq;
   //double **VecAsymm, **VecAsymmError;
   //ReadAsymmFile("figure/34mAl_NMR_Mod15_bootstrap/test/asymm.txt",NumOfLines, dim, freq, VecAsymm, VecAsymmError);
   //for(int i = 0; i<NumOfLines; i++){
   //   t->ReadPara("NMR_NQR.in");
   //   t->ReadFitPara("NMR_NQR_fit.in");
   //   t->MakeSpec(dim, freq, VecAsymm[i], VecAsymmError[i]);
   //   t->PlotSpec();
   //   t->FitSpec(0,0,4500);
   //   cout<<"************** i = "<<i<<": centroid = "<<t->FitCent<<" ***************"<<endl;
   //   sprintf(pngname,"figure//34mAl_NMR_Mod15_bootstrap/test/%04d.png",i+1);
   //   c2->SaveAs(pngname);
   //   fprintf(result1, "%d %.1f %d\n", i+1, t->FitCent, t->MaxAsymmFreq);
   //   fprintf(result2, "%d %.1f %.1f\n", i+1, t->FitAmp*(-1e3), t->FitAmpError*1e3);
   //}
   //fclose(result1);
   //fclose(result2);
}
