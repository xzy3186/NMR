{
   TH1F *h1 = new TH1F("h1","h1",16000,0,16000);
   TH1F *h2 = new TH1F("h2","h2",16000,0,16000);
   TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);
   c1->Divide(1,2);

   c1->cd(1);
   AutoTree->Draw("E_GammaG_L>>h1");
   /********* 121.78 keV ***********/
   TF1 *ff1 = new TF1("ff1","gaus(0)+pol1(3)",375,415);
   ff1->SetParameter(0,h1->GetBinContent(395));
   ff1->SetParameter(1,395);
   ff1->SetParameter(2,3);
   h1->Fit("ff1","R");

   /********* 244.7 keV ***********/
   TF1 *ff2 = new TF1("ff2","gaus(0)+pol1(3)",800,840);
   ff2->SetParameter(0,h1->GetBinContent(820));
   ff2->SetParameter(1,820);
   ff2->SetParameter(2,3);
   h1->Fit("ff2","R+");

   /********* 344.28 keV **********/
   TF1 *ff3 = new TF1("ff3","gaus(0)+pol1(3)",1135,1175);
   ff3->SetParameter(0,h1->GetBinContent(1155));
   ff3->SetParameter(1,1155);
   ff3->SetParameter(2,3);
   h1->Fit("ff3","R+");

   /********* 778.9 keV ***********/
   TF1 *ff4 = new TF1("ff4","gaus(0)+pol1(3)",2605,2645);
   ff4->SetParameter(0,h1->GetBinContent(2625));
   ff4->SetParameter(1,2625);
   ff4->SetParameter(2,3);
   h1->Fit("ff4","R+");

   /********* 964.08 keV **********/
   TF1 *ff5 = new TF1("ff5","gaus(0)+pol1(3)",3230,3270);
   ff5->SetParameter(0,h1->GetBinContent(3250));
   ff5->SetParameter(1,3250);
   ff5->SetParameter(2,3);
   h1->Fit("ff5","R+");

   /*** 1085.87 and 1112.07 keV****/
   TF1 *ff6 = new TF1("ff6","gaus(0)+gaus(3)+gaus(6)+pol1(9)",3640,3770);
   ff6->SetParameter(0,h1->GetBinContent(3660));
   ff6->SetParameter(1,3660);
   ff6->SetParameter(2,3);
   ff6->SetParameter(3,h1->GetBinContent(3675));
   ff6->SetParameter(4,3675);
   ff6->SetParameter(5,3);
   ff6->SetParameter(6,h1->GetBinContent(3750));
   ff6->SetParameter(7,3750);
   ff6->SetParameter(8,3);
   h1->Fit("ff6","R+");

   /********* 1408.01 keV *********/
   TF1 *ff7 = new TF1("ff7","gaus(0)+pol1(3)",4725,4765);
   ff7->SetParameter(0,h1->GetBinContent(4745));
   ff7->SetParameter(1,4745);
   ff7->SetParameter(2,3);
   h1->Fit("ff7","R+");

   /********* 2614.5 keV **********/
   TF1 *ff8 = new TF1("ff8","gaus(0)+pol1(3)",8785,8825);
   ff8->SetParameter(0,h1->GetBinContent(8805));
   ff8->SetParameter(1,8805);
   ff8->SetParameter(2,3);
   h1->Fit("ff8","R+");

   c1->cd(2);
   AutoTree->Draw("E_GammaG_H>>h2");
   /********* 121.78 keV ***********/
   TF1 *ff11 = new TF1("ff11","gaus(0)+pol1(3)",2610,3010);
   ff11->SetParameter(0,h1->GetBinContent(2810));
   ff11->SetParameter(1,2810);
   ff11->SetParameter(2,20);
   h2->Fit("ff11","R");

   /********* 244.7 keV ***********/
   TF1 *ff12 = new TF1("ff12","gaus(0)+pol1(3)",5440,5840);
   ff12->SetParameter(0,h1->GetBinContent(5640));
   ff12->SetParameter(1,5640);
   ff12->SetParameter(2,20);
   h2->Fit("ff12","R+");

   /********* 344.28 keV **********/
   TF1 *ff13 = new TF1("ff13","gaus(0)+pol1(3)",7730,8130);
   ff13->SetParameter(0,h1->GetBinContent(7930));
   ff13->SetParameter(1,7930);
   ff13->SetParameter(2,20);
   h2->Fit("ff13","R+");

   cout<<"For low gain:"<<endl;
   cout<<ff1->GetParameter(1)<<endl;
   cout<<ff2->GetParameter(1)<<endl;
   cout<<ff3->GetParameter(1)<<endl;
   cout<<ff4->GetParameter(1)<<endl;
   cout<<ff5->GetParameter(1)<<endl;
   cout<<ff6->GetParameter(1)<<endl;
   cout<<ff6->GetParameter(7)<<endl;
   cout<<ff7->GetParameter(1)<<endl;
   cout<<ff8->GetParameter(1)<<endl;
   cout<<"For high gain:"<<endl;
   cout<<ff11->GetParameter(1)<<endl;
   cout<<ff12->GetParameter(1)<<endl;
   cout<<ff13->GetParameter(1)<<endl;
}
