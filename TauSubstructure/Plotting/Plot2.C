void NormalizeUnitArea(TH1 *);

void Plot2(){

  bool kStop = false;
  int i = 0;

  do{
    cout<<i<<"."<<endl;
    if(i==0) Diff("tau_pan_1p0n_reso_rel", "tau_pan_1p0n_reso_rel", "PanTau 1p0n", "PanTau 1p0n");

    else if(i==1) Same(1, "tau_pan_incl_reso_rel", "tau_rec_incl_reso_rel", "PanTau", "RecTau");
    else if(i==2) Same(2, "tau_pan_incl_reso_rel", "tau_rec_incl_reso_rel", "PanTau", "RecTau");

    else if(i==3) Same(1, "tau_pan_1p0n_reso_rel", "tau_pan_1p1n_reso_rel", "tau_pan_1pXn_reso_rel", "PanTau 1p0n", "PanTau 1p1n", "PanTau 1pXn");
    else if(i==4) Same(2, "tau_pan_1p0n_reso_rel", "tau_pan_1p1n_reso_rel", "tau_pan_1pXn_reso_rel", "PanTau 1p0n", "PanTau 1p1n", "PanTau 1pXn");

    else if(i==5) Same(1, "tau_pan_3p0n_reso_rel", "tau_pan_3pXn_reso_rel", "PanTau 3p0n", "PanTau 3pXn");
    else if(i==6) Same(2, "tau_pan_3p0n_reso_rel", "tau_pan_3pXn_reso_rel", "PanTau 3p0n", "PanTau 3pXn");

    else if(i==7) Same(1, "tau_pan_0n_true_0n_reso_rel", "tau_pan_0n_true_1n_reso_rel", "tau_pan_0n_true_Xn_reso_rel", "PanTau 0n - true 0n", "PanTau 0n - true 1n", "PanTau 0n - true Xn");
    else if(i==8) Same(2, "tau_pan_0n_true_0n_reso_rel", "tau_pan_0n_true_1n_reso_rel", "tau_pan_0n_true_Xn_reso_rel", "PanTau 0n - true 0n", "PanTau 0n - true 1n", "PanTau 0n - true Xn");

    else if(i==9) Same(1, "tau_pan_1n_true_0n_reso_rel", "tau_pan_1n_true_1n_reso_rel", "tau_pan_1n_true_Xn_reso_rel", "PanTau 1n - true 0n", "PanTau 1n - true 1n", "PanTau 1n - true Xn");
    else if(i==10) Same(2, "tau_pan_1n_true_0n_reso_rel", "tau_pan_1n_true_1n_reso_rel", "tau_pan_1n_true_Xn_reso_rel", "PanTau 1n - true 0n", "PanTau 1n - true 1n", "PanTau 1n - true Xn");

    else if(i==11) Same(1, "tau_pan_Xn_true_0n_reso_rel", "tau_pan_Xn_true_1n_reso_rel", "tau_pan_Xn_true_Xn_reso_rel", "PanTau Xn - true 0n", "PanTau Xn - true 1n", "PanTau Xn - true Xn");
    else if(i==12) Same(2, "tau_pan_Xn_true_0n_reso_rel", "tau_pan_Xn_true_1n_reso_rel", "tau_pan_Xn_true_Xn_reso_rel", "PanTau Xn - true 0n", "PanTau Xn - true 1n", "PanTau Xn - true Xn");

    else if(i==13) Diff("tau_pan_0n_true_0n_reso_rel", "tau_pan_0n_true_0n_reso_rel", "PanTau 0n", "PanTau 0n");
    else if(i==14) Diff("tau_pan_1n_true_1n_reso_rel", "tau_pan_1n_true_1n_reso_rel", "PanTau 1n", "PanTau 1n");
    else if(i==15) Diff("tau_pan_Xn_true_Xn_reso_rel", "tau_pan_Xn_true_Xn_reso_rel", "PanTau Xn", "PanTau Xn");

    else if(i==16) Same(1, "tau_pan_0n_true_0n_reso_rel", "tau_pan_1n_true_0n_reso_rel", "tau_pan_Xn_true_0n_reso_rel", "PanTau 0n - true 0n", "PanTau 1n - true 0n", "PanTau Xn - true 0n");
    else if(i==17) Same(2, "tau_pan_0n_true_0n_reso_rel", "tau_pan_1n_true_0n_reso_rel", "tau_pan_Xn_true_0n_reso_rel", "PanTau 0n - true 0n", "PanTau 1n - true 0n", "PanTau Xn - true 0n");

    else if(i==18) Same(1, "tau_pan_0n_true_0n_reso_rel", "tau_pan_1n_true_1n_reso_rel", "tau_pan_Xn_true_Xn_reso_rel", "PanTau 0n - true 0n", "PanTau 1n - true 1n", "PanTau Xn - true Xn");
    else if(i==19) Same(2, "tau_pan_0n_true_0n_reso_rel", "tau_pan_1n_true_1n_reso_rel", "tau_pan_Xn_true_Xn_reso_rel", "PanTau 0n - true 0n", "PanTau 1n - true 1n", "PanTau Xn - true Xn");

    else if(i==20) Same(1, "tau_pan_1p_true_1p_reso_rel", "tau_pan_1p_true_3p_reso_rel", "tau_pan_1p_true_5p_reso_rel", "PanTau 1p - true 1p", "PanTau 1p - true 3p", "PanTau 1p - true 5p");
    else if(i==21) Same(2, "tau_pan_1p_true_1p_reso_rel", "tau_pan_1p_true_3p_reso_rel", "tau_pan_1p_true_5p_reso_rel", "PanTau 1p - true 1p", "PanTau 1p - true 3p", "PanTau 1p - true 5p");

    else if(i==22) Same(1, "tau_pan_2p_true_1p_reso_rel", "tau_pan_2p_true_3p_reso_rel", "tau_pan_2p_true_5p_reso_rel", "PanTau 2p - true 1p", "PanTau 2p - true 3p", "PanTau 2p - true 5p");
    else if(i==23) Same(2, "tau_pan_2p_true_1p_reso_rel", "tau_pan_2p_true_3p_reso_rel", "tau_pan_2p_true_5p_reso_rel", "PanTau 2p - true 1p", "PanTau 2p - true 3p", "PanTau 2p - true 5p");

    else if(i==24) Same(1, "tau_pan_3p_true_1p_reso_rel", "tau_pan_3p_true_3p_reso_rel", "tau_pan_3p_true_5p_reso_rel", "PanTau 3p - true 1p", "PanTau 3p - true 3p", "PanTau 3p - true 5p");
    else if(i==25) Same(2, "tau_pan_3p_true_1p_reso_rel", "tau_pan_3p_true_3p_reso_rel", "tau_pan_3p_true_5p_reso_rel", "PanTau 3p - true 1p", "PanTau 3p - true 3p", "PanTau 3p - true 5p");

    else if(i==26) Same(1, "tau_pan_5p_true_1p_reso_rel", "tau_pan_5p_true_3p_reso_rel", "tau_pan_5p_true_5p_reso_rel", "PanTau 5p - true 1p", "PanTau 5p - true 3p", "PanTau 5p - true 5p");
    else if(i==27) Same(2, "tau_pan_5p_true_1p_reso_rel", "tau_pan_5p_true_3p_reso_rel", "tau_pan_5p_true_5p_reso_rel", "PanTau 5p - true 1p", "PanTau 5p - true 3p", "PanTau 5p - true 5p");

    else if(i==28) Same(1, "tau_pan_1p_true_1p_reso_rel", "tau_pan_3p_true_3p_reso_rel", "PanTau 1p - true 1p", "PanTau 3p - true 3p");
    else if(i==29) Same(2, "tau_pan_1p_true_1p_reso_rel", "tau_pan_3p_true_3p_reso_rel", "PanTau 1p - true 1p", "PanTau 3p - true 3p");

    else if(i==30) Same(1, "tau_pan_0n_true_0n_reso_rel", "tau_pan_1p_true_1p_reso_rel", "tau_pan_3p_true_3p_reso_rel", "PanTau 0n - true 0n", "PanTau 1p - true 1p", "PanTau 3p - true 3p");
    else if(i==31) Same(2, "tau_pan_0n_true_0n_reso_rel", "tau_pan_1p_true_1p_reso_rel", "tau_pan_3p_true_3p_reso_rel", "PanTau 0n - true 0n", "PanTau 1p - true 1p", "PanTau 3p - true 3p");

    else if(i==32) Same(1, "tau_pan_1p0n_true_1p0n_reso_rel", "tau_pan_1p0n_true_1p1n_reso_rel", "tau_pan_1p0n_true_1pXn_reso_rel", "PanTau 1p0n - true 1p0n", "PanTau 1p0n - true 1p1n", "PanTau 1p0n - true 1p3X");
    else if(i==33) Same(2, "tau_pan_1p0n_true_1p0n_reso_rel", "tau_pan_1p0n_true_1p1n_reso_rel", "tau_pan_1p0n_true_1pXn_reso_rel", "PanTau 1p0n - true 1p0n", "PanTau 1p0n - true 1p1n", "PanTau 1p0n - true 1p3X");

    else if(i==34) Same(1, "tau_pan_1p0n_true_1p0n_reso_rel", "tau_pan_1p0n_true_3p0n_reso_rel",  "PanTau 1p0n - true 1p0n", "PanTau 1p0n - true 3p0n");
    else if(i==35) Same(2, "tau_pan_1p0n_true_1p0n_reso_rel", "tau_pan_1p0n_true_3p0n_reso_rel",  "PanTau 1p0n - true 1p0n", "PanTau 1p0n - true 3p0n");

    else if(i==36) Same(1, "tau_pan_3p0n_true_3p0n_reso_rel", "tau_pan_3p0n_true_3pXn_reso_rel",  "PanTau 3p0n - true 3p0n", "PanTau 3p0n - true 3pXn" );
    else if(i==37) Same(2, "tau_pan_3p0n_true_3p0n_reso_rel", "tau_pan_3p0n_true_3pXn_reso_rel",  "PanTau 3p0n - true 3p0n", "PanTau 3p0n - true 3pXn" );

    else if(i==38) Same(1, "tau_pan_other_true_1p0n_reso_rel", "tau_pan_other_true_1p1n_reso_rel", "tau_pan_other_true_1pXn_reso_rel",  "PanTau other - true 1p0n", "PanTau other - true 1p1n", "PanTau other - true 1pXn" );
    else if(i==39) Same(2, "tau_pan_other_true_1p0n_reso_rel", "tau_pan_other_true_1p1n_reso_rel", "tau_pan_other_true_1pXn_reso_rel",  "PanTau other - true 1p0n", "PanTau other - true 1p1n", "PanTau other - true 1pXn" );

    else if(i==40) Same(1, "tau_pan_other_true_3p0n_reso_rel", "tau_pan_other_true_3pXn_reso_rel",  "PanTau other - true 3p0n", "PanTau other - true 3pXn");
    else if(i==41) Same(2, "tau_pan_other_true_3p0n_reso_rel", "tau_pan_other_true_3pXn_reso_rel",  "PanTau other - true 3p0n", "PanTau other - true 3pXn");

    else if(i==42) Same(1, "tau_pan_1p_matched_trk_score_low_reso_rel", "tau_pan_1p_matched_trk_score_medium_reso_rel", "tau_pan_1p_matched_trk_score_high_reso_rel",  "PanTau 1p - low", "PanTau 1p - medium", "PanTau 1p - high" );
    else if(i==43) Same(2, "tau_pan_1p_matched_trk_score_low_reso_rel", "tau_pan_1p_matched_trk_score_medium_reso_rel", "tau_pan_1p_matched_trk_score_high_reso_rel",  "PanTau 1p - low", "PanTau 1p - medium", "PanTau 1p - high" );

    else if(i==44) Same(1, "tau_pan_3p_matched_trk_score_low_reso_rel", "tau_pan_3p_matched_trk_score_medium_reso_rel", "tau_pan_3p_matched_trk_score_high_reso_rel",  "PanTau 3p - low", "PanTau 3p - medium", "PanTau 3p - high" );
    else if(i==45) Same(2, "tau_pan_3p_matched_trk_score_low_reso_rel", "tau_pan_3p_matched_trk_score_medium_reso_rel", "tau_pan_3p_matched_trk_score_high_reso_rel",  "PanTau 3p - low", "PanTau 3p - medium", "PanTau 3p - high" );

    else  kStop = true;

    i++;
  } while(!kStop);

  cout<<"\n"<<i<<" plots created "<<endl;
}

void Diff(const string&hn1,const string&hn2, const string &t1, const string &t2){
  Draw(hn1, 1, t1, hn2, 2, t2, "", 0, "");
}


void Same(int ifile, const string&hn1,const string&hn2, const string &t1, const string &t2){
  Draw(hn1, ifile, t1, hn2, ifile, t2);
}

void Same(int ifile, const string&hn1,const string&hn2, const string&hn3, const string &t1, const string &t2, const string &t3){
  Draw(hn1, ifile, t1, hn2, ifile, t2, hn3, ifile, t3);
}


void Draw(const string&hn1,
          int nfile1,
          const string&t1,
          //
          const string &hn2,
          int nfile2,
          const string&t2
          ){
  Draw(hn1, nfile1, t1, hn2, nfile2, t2, "", 0, "");
}

void Draw(const std::string&hn1,
          int nfile1,
          const std::string&t1,
          //
          const std::string &hn2,
          int nfile2,
          const std::string&t2,
          //
          const std::string &hn3,
          int nfile3,
          const std::string&t3
          ){

  static int j;


  string ext = "eps";
  string outputdir = "plots/plots_17_2/";

  string fn1="results/user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.recon.ESD.e1176_s1479_s1470_r3553_tid00999076_00.v06-00.v3.noPtcut.140214152940/tau4mom.root";
  string fn2="results/user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.recon.ESD.e1176_s1479_s1470_r3553_tid00999076_00.v06-00.v3.RecoPt15.140214153249/tau4mom.root";


  string tag1 = "no p_{T} cut";
  string tag2 = "p_{T} > 15 GeV";
  string tag3;

  string head("");

  if(nfile1 == nfile2){

    if(nfile1 == 1){
      tag2 = tag1;
      head = tag1;
    }else{
      tag1 = tag2;
      head = tag2;
    }

  }

  if(nfile3 == 1) tag3  = tag1;
  else tag3 = tag2;

  // string tex1 = t1;
  //string tex2 = t2;

  string title1 = t1 + " / " + tag1;
  string title2 = t2 + " / " + tag2;
  string title3 = t3 + " / " + tag3;

  if(nfile1 == nfile2){
    title1 = t1;
    title2 = t2;
  }
  if(nfile2 == nfile3){
    title3 = t3;
  }

  bool kLogY = true;

  string filename1;
  string filename2;
  string filename3;

  if(nfile1 == 1) filename1 = fn1; else filename1 = fn2;
  if(nfile2 == 1) filename2 = fn1; else filename2 = fn2;
  if(nfile3 == 1) filename3 = fn1; else filename3 = fn2;

  TFile *f1 = nfile1 ? new TFile(filename1.c_str()) : NULL;
  TFile *f2 = nfile2 ? new TFile(filename2.c_str()) : NULL;
  TFile *f3 = nfile3 ? new TFile(filename3.c_str()) : NULL;

  if(nfile1) if(!f1) { cerr<<"No file 1 "<<endl return;} else{ cout<<"file 1 : "<<f1->GetName()<<endl; }
  if(nfile2) if(!f2) { cerr<<"No file 2 "<<endl return;} else{ cout<<"file 2 : "<<f2->GetName()<<endl; }
  if(nfile3) if(!f3) { cerr<<"No file 3 "<<endl; return;} else{ cout<<"file 3 : "<<f3->GetName()<<endl; }

  TH1D *h1 = (TH1D*)f1->Get(hn1.c_str());
  if(!h1) { cerr<<"No histo 1 "<<endl; return;}
  NormalizeMaxBin(h1);
  TH1D *h2 = (TH1D*)f2->Get(hn2.c_str());
  if(!h2) { cerr<<"No histo 2 "<<endl; return;}
  NormalizeMaxBin(h2);

  TH1D *h3 = nfile3 ? (TH1D*)f3->Get(hn3.c_str()) : NULL;
  if(nfile3) if(!h3) { cerr<<"No histo 3 "<<endl; return;}
  if(nfile3 && h3) NormalizeMaxBin(h3);



  TCanvas *c = new TCanvas("c", "",10,50,850,500);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetRightMargin(0.025);
  c->SetTopMargin(0.04);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  h1->Draw();
  h1->SetLineColor(kAzure-4);
  h2->Draw("same");
  h2->SetLineColor(kRed-4);
  if(nfile3 && h3){
    h3->Draw("same");
    h3->SetLineColor(kGreen-4);
  }

  double yfactor = kLogY ? 2 : 1.1;

  h1->SetMaximum( h1->GetMaximum() * 1.2);

  if(kLogY) gPad->SetLogy();

  TLegend *leg = new TLegend(0.1,0.65,0.45,0.92,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetLineColor(0);
  leg->SetLineStyle(0);
  leg->SetLineWidth(0);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1, title1.c_str(), "l");
  leg->AddEntry(h2, title2.c_str(), "l");
  if(nfile3 && h3) leg->AddEntry(h3, title3.c_str(), "l");
  if(head!="") leg->SetHeader(head.c_str());
  leg->Draw();

  string cname = outputdir + "c"+GetStringFromInt(j++) + ( nfile1 ? "_"+hn1 : "") +  ( nfile2 ? "_T_"+hn2 : "") +  ( nfile3 ? "_T_"+hn3 : "") + "."+ext;
  
  c->SaveAs(cname.c_str());
}
void NormalizeUnitArea(TH1 *h){

  h->Scale( 1./h->Integral() );
}

void NormalizeMaxBin(TH1 *h){

  h->Scale( 1./h->GetBinContent(h->GetMaximumBin()) );
}
 string GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }
