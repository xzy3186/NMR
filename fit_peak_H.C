{
   TH1F *h1 = new TH1F("h1","h1",16000,0,16000);
   TH1F *h2 = new TH1F("h2","h2",16000,0,16000);
   TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);
   c1->Divide(1,2);

   c1->cd(1);
   AutoTree->Draw("E_GammaH_L>>h1");
   /********* 121.78 keV ***********/
   TF1 *ff1 = new TF1("ff1","gaus(0)+pol1(3)",440,500);
   ff1->SetParameter(0,h1->GetBinContent(464));
   ff1->SetParameter(1,464);
   ff1->SetParameter(2,3);
   h1->Fit("ff1","R");

   /********* 244.7 keV ***********/
   TF1 *ff2 = new TF1("ff2","gaus(0)+pol1(3)",890,960);
   ff2->SetParameter(0,h1->GetBinContent(930));
   ff2->SetParameter(1,930);
   ff2->SetParameter(2,3);
   h1->Fit("ff2","R+");

   /********* 344.28 keV **********/
   TF1 *ff3 = new TF1("ff3","gaus(0)+pol1(3)",1270,1340);
   ff3->SetParameter(0,h1->GetBinContent(1308));
   ff3->SetParameter(1,1308);
   ff3->SetParameter(2,3);
   h1->Fit("ff3","R+");

   /********* 778.9 keV ***********/
   TF1 *ff4 = new TF1("ff4","gaus(0)+pol1(3)",2900,3000);
   ff4->SetParameter(0,h1->GetBinContent(2956));
   ff4->SetParameter(1,2956);
   ff4->SetParameter(2,3);
   h1->Fit("ff4","R+");

   /********* 964.08 keV **********/
   TF1 *ff5 = new TF1("ff5","gaus(0)+pol1(3)",3600,3750);
   ff5->SetParameter(0,h1->GetBinContent(3658));
   ff5->SetParameter(1,3658);
   ff5->SetParameter(2,3);
   h1->Fit("ff5","R+");

   /*** 1085.87 and 1112.07 keV****/
   TF1 *ff6 = new TF1("ff6","gaus(0)+gaus(3)+gaus(6)+pol1(9)",4050,4250);
   ff6->SetParameter(0,h1->GetBinContent(4120));
   ff6->SetParameter(1,4120);
   ff6->SetParameter(2,3);
   ff6->SetParameter(3,h1->GetBinContent(4137));
   ff6->SetParameter(4,4137);
   ff6->SetParameter(5,3);
   ff6->SetParameter(6,h1->GetBinContent(4220));
   ff6->SetParameter(7,4220);
   ff6->SetParameter(8,3);
   h1->Fit("ff6","R+");

   /********* 1408.01 keV *********/
   TF1 *ff7 = new TF1("ff7","gaus(0)+pol1(3)",5280,5400);
   ff7->SetParameter(0,h1->GetBinContent(5340));
   ff7->SetParameter(1,5340);
   ff7->SetParameter(2,3);
   h1->Fit("ff7","R+");

   /********* 2614.5 keV **********/
   TF1 *ff8 = new TF1("ff8","gaus(0)+pol1(3)",9880,9930);
   ff8->SetParameter(0,h1->GetBinContent(9909));
   ff8->SetParameter(1,9909);
   ff8->SetParameter(2,3);
   h1->Fit("ff8","R+");

   c1->cd(2);
   AutoTree->Draw("E_GammaH_H>>h2");
   /********* 121.78 keV ***********/
   TF1 *ff11 = new TF1("ff11","gaus(0)+pol1(3)",2700,2900);
   ff11->SetParameter(0,h1->GetBinContent(2800));
   ff11->SetParameter(1,2800);
   ff11->SetParameter(2,20);
   h2->Fit("ff11","R");

   /********* 244.7 keV ***********/
   TF1 *ff12 = new TF1("ff12","gaus(0)+pol1(3)",5400,5800);
   ff12->SetParameter(0,h1->GetBinContent(5600));
   ff12->SetParameter(1,5600);
   ff12->SetParameter(2,20);
   h2->Fit("ff12","R+");

   /********* 344.28 keV **********/
   TF1 *ff13 = new TF1("ff13","gaus(0)+pol1(3)",7700,8100);
   ff13->SetParameter(0,h1->GetBinContent(7870));
   ff13->SetParameter(1,7870);
   ff13->SetParameter(2,20);
   h2->Fit("ff13","R+");

   cout<<"For low gain:"<<endl;
   cout<<ff1->GetParameter(1)<<ff1->GetParError(1)<<endl;
   cout<<ff2->GetParameter(1)<<ff2->GetParError(1)<<endl;
   cout<<ff3->GetParameter(1)<<ff3->GetParError(1)<<endl;
   cout<<ff4->GetParameter(1)<<ff4->GetParError(1)<<endl;
   cout<<ff5->GetParameter(1)<<ff5->GetParError(1)<<endl;
   cout<<ff6->GetParameter(1)<<ff6->GetParError(1)<<endl;
   cout<<ff6->GetParameter(7)<<ff6->GetParError(7)<<endl;
   cout<<ff7->GetParameter(1)<<ff7->GetParError(1)<<endl;
   cout<<ff8->GetParameter(1)<<ff8->GetParError(1)<<endl;
   cout<<"For high gain:"<<endl;
   cout<<ff11->GetParameter(1)<<ff11->GetParError(1)<<endl;
   cout<<ff12->GetParameter(1)<<ff12->GetParError(1)<<endl;
   cout<<ff13->GetParameter(1)<<ff13->GetParError(1)<<endl;
}
