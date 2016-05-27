{
   gROOT->ProcessLine(".L NMR.C+");
   TChain *AutoTree = new TChain ("AutoTree");
   AutoTree->Add("DataFiles/r0125.root");
   AutoTree->Add("DataFiles/r0127.root");
   AutoTree->Add("DataFiles/r0128.root");
   AutoTree->Add("DataFiles/r0129.root");
   AutoTree->Add("DataFiles/r0130.root");
   AutoTree->Add("DataFiles/r0131.root");
   AutoTree->Add("DataFiles/r0132.root");
   NMR *t = new NMR("",AutoTree);
   t->ReadPara("NMR_NQR.in");
   t->Loop();
   t->MakeNMR();
   t->gNMR->Draw("AP");
}
