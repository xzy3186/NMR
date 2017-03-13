{
   TGraph *calib1=new TGraph(11);

   calib1->SetPoint(0, 463.935, 121.78 );
   calib1->SetPoint(1, 930.60,  244.7  );
   calib1->SetPoint(2, 1307.72, 344.28 );
   calib1->SetPoint(3, 2957.34, 778.9  );
   calib1->SetPoint(4, 3659.11, 964.08 );
   calib1->SetPoint(5, 4120.32, 1085.87);
   calib1->SetPoint(6, 4219.40, 1112.07);
   calib1->SetPoint(7, 5340.21, 1408.01);
   calib1->SetPoint(8, 9905.94, 2614.05);
   calib1->SetPoint(9, 12600.8, 3327.1);//from 34Si
   calib1->SetPoint(10, 16116.2, 4257.0);//from 34Si

   TGraph *calib2=new TGraph(3);
   calib2->SetPoint(0, 2796.03, 121.78 );
   calib2->SetPoint(1, 5599.37, 244.7  );
   calib2->SetPoint(2, 7865.35, 344.28 );
   //
   //calib->SetPointError(0,   1, 0.0);
   //calib->SetPointError(1,   1, 0.0);
   //calib->SetPointError(2,   1, 0.0);
   //calib->SetPointError(3,   1, 0.0);
   //calib->SetPointError(4,   1, 0.0);
   //calib->SetPointError(5,   1, 0.0);
   //calib->SetPointError(6,   1, 0.0);
   //calib->SetPointError(7,   1, 0.0);
   //calib->SetPointError(7,   1, 0.0);

   TF1 *ff1 = new TF1("ff1","pol2",0,3800);
   ff1->SetParameter(0,-1);
   ff1->SetParameter(1,0.23);
   TF1 *ff2 = new TF1("ff2","pol2",3400,16500);
   ff2->SetParameter(0,-1);
   ff2->SetParameter(1,0.23);

   TF1 *ff3 = new TF1("ff3","pol1",0,16000);
   ff2->SetParameter(0,-1);
   ff2->SetParameter(1,0.023);

   TCanvas* c1 = new TCanvas("c1","c1",0,0,800,600);
   c1->Divide(1,2);
   c1->cd(1);
   calib1->SetMarkerStyle(8);
   calib1->Draw("ap");
   calib1->Fit("ff1","R");
   cout << "chi2/NDF = " << ff1->GetChisquare()/ff1->GetNDF() <<endl;;
   cout << "p0 = " << ff1->GetParameter(0) << ", p1 = " << ff1->GetParameter(1) << ", p2 = " << ff1->GetParameter(2) <<endl;
   cout << ff1->Eval(3000)<<endl;
   calib1->Fit("ff2","R+");
   cout << "chi2/NDF = " << ff2->GetChisquare()/ff2->GetNDF() <<endl;;
   cout << "p0 = " << ff2->GetParameter(0) << ", p1 = " << ff2->GetParameter(1) << ", p2 = " << ff2->GetParameter(2) <<endl;
   cout << ff2->Eval(3000)<<endl;
   c1->cd(2);
   calib2->SetMarkerStyle(8);
   calib2->Draw("ap");
   calib2->Fit("ff3","R");
   cout << "chi2/NDF = " << ff3->GetChisquare()/ff3->GetNDF() <<endl;;
   cout << "p0 = " << ff3->GetParameter(0) << ", p1 = " << ff3->GetParameter(1) <<endl;
}
