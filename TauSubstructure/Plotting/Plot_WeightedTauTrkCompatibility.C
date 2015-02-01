
TH1D *H(TFile *f, const string & s, Color_t);
TH1D *H(TFile *f, const string & s, Color_t, Color_t);
TH1D *Harea(TFile *f, const string & s, Color_t t, double &n);
TH1D *Harea(TFile *f, const string & s, Color_t t, Color_t, double &n);
TH1D *Hnorm(TFile *f, const string & s, Color_t t, const  double n);
TH1D *Hnorm(TFile *f, const string & s, Color_t t, Color_t, const  double n);
TH2D *H2(TFile *f, const string & s, Color_t t);
void N(TH1D*h);
void N2(TH1D*h);
void N(TH1D*h, double w);
void Calc(TH2D *h, double y, double &s, double &ds);

void Plot_WeightedTauTrkCompatibility(TString filename){

  int nPlots = 1;
  TFile *f = TFile::Open(filename);

  for(int i = 0; i <= nPlots; i++)
    Run_WeightedTauTrkCompatibility(f, i);

}

void Plot_WeightedTauTrkCompatibility(TString filename, int c){

  TFile *f = TFile::Open(filename);
  Run_WeightedTauTrkCompatibility(f, c);
}

void Run_WeightedTauTrkCompatibility(TFile *f, int c){
  

  if(!f || f->IsZombie() ){cerr<<"unable to open file "<<endl; return;}

  string mode = "1p0n";

  double ylim = 7;

  if( c == 0){
    
    double y = 1.4;
    double yw = 5.5;
    
    TLine *l = new TLine(-1, y, 1, y);
    l->SetLineStyle(7);
    l->SetLineColor(2);
    l->SetLineWidth(2);

    TLine *lw = new TLine(-1, yw, 1, yw);
    lw->SetLineStyle(7);
    lw->SetLineColor(2);
    lw->SetLineWidth(2);


    //
    TCanvas *can1 = new TCanvas("can1","All", 20, 20, 500, 800);
    can1->Divide(1,2);

    can1->cd(1);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_reso_rel_vs_R_trk0_calo", kAzure);
    h->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");
    l->Draw();


    can1->cd(2);
    TH2D *g = H2(f, "test_r"+mode+"_t"+mode+"_reso_rel_vs_R_trk0_calo_w", kAzure);
    g->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    g->Draw("colz");
    lw->Draw();

    //--
    double s1, ds1; Calc(h, y, s1, ds1);
    cout<<"1. S("<<y<<")= "<<s1<<" pm "<<ds1<<endl;

    double sw1, dsw1; Calc(g, yw, sw1, dsw1);
    cout<<"   Sw("<<yw<<")= "<<sw1<<" pm "<<dsw1<<endl;

    cout<<"=> Sw/S "<<sw1/s1<<endl<<endl;
    //--

    //
    TCanvas *can2 = new TCanvas("can2", "Kaons", 40, 40, 500, 800);
    can2->Divide(1,2);

    can2->cd(1);
    TH2D *r = H2(f,"test_r"+mode+"_t"+mode+"_kaon_decay_1_reso_rel_vs_R_trk0_calo" , kAzure);
    r->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    r->Draw("colz");

    can2->cd(2);
    TH2D *k = H2(f,"test_r"+mode+"_t"+mode+"_kaon_decay_1_reso_rel_vs_R_trk0_calo_w" , kAzure);
    k->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    k->Draw("colz");


    //
    TCanvas *can3 = new TCanvas("can3","K^{0}", 60, 60, 500, 800);
    can3->Divide(1,2);

    can3->cd(1);
    TH2D *h = H2(f,"test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_reso_rel_vs_R_trk0_calo" , kAzure);
    h->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");
    l->Draw();

    can3->cd(2);
    TH2D *q = H2(f,"test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_reso_rel_vs_R_trk0_calo_w" , kAzure);
    q->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    q->Draw("colz");
    lw->Draw();

    //
    TCanvas *can4 = new TCanvas("can4","No K^{0}", 80, 80, 500, 800);
    can4->Divide(1,2);

    can4->cd(1);
    TH2D *b = H2(f,"test_r"+mode+"_t"+mode+"_neutral_kaon_decay_0_reso_rel_vs_R_trk0_calo" , kAzure);
    b->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    b->Draw("colz");
    l->Draw();

    can4->cd(2);
    TH2D *t = H2(f,"test_r"+mode+"_t"+mode+"_neutral_kaon_decay_0_reso_rel_vs_R_trk0_calo_w" , kAzure);
    t->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    t->Draw("colz");
    lw->Draw();

    //--
    double s4, ds4; Calc(b, y, s4, ds4);
    cout<<"4. S("<<y<<")= "<<s4<<" pm "<<ds4<<" <= non-K rejection"<<endl;

    double sw4, dsw4; Calc(t, yw, sw4, dsw4);
    cout<<"   Sw("<<yw<<")= "<<sw4<<" pm "<<dsw4<<" <= non-K rejection"<<endl;

    cout<<"=> Sw/S "<<sw4/s4<<endl;
    cout<<"=> 1-Sw "<<(1-sw4)<<" <= non-K keep "<<endl;
    cout<<"=> 1-S "<<(1-s4)<<" <= non-K keep"<<endl;
    cout<<"=> (1-Sw)/(1-S) "<<(1-sw4)/(1-s4)<<endl;
    //--


    //
    TCanvas *can5 = new TCanvas("can5", "Kaons - Trk Origin", 100, 100, 500, 800);
    can5->Divide(1,2);

    can5->cd(1);
    TH2D *e = H2(f,"test_r"+mode+"_t"+mode+"_kaon_decay_1_trk_0_orig_PI_reso_rel_vs_R_trk0_calo" , kAzure);
    e->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    e->Draw("colz");
    l->Draw();

    can5->cd(2);
    TH2D *p = H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_1_trk_0_orig_PI_reso_rel_vs_R_trk0_calo_w", kAzure);
    p->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    p->Draw("colz");
    lw->Draw();

    //
    TCanvas *can6 = new TCanvas("can6", "Neutral Kaons - Trk Origin", 100, 100, 500, 800);
    can6->Divide(1,2);

    can6->cd(1);
    TH2D *w = H2(f,"test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_trk_0_orig_PI_reso_rel_vs_R_trk0_calo" , kAzure);
    w->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    w->Draw("colz");
    l->Draw();

    can6->cd(2);
    TH2D *d = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_trk_0_orig_PI_reso_rel_vs_R_trk0_calo_w", kAzure);
    d->GetYaxis()->SetRangeUser(-ylim, ylim);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    d->Draw("colz");
    lw->Draw();

    //--
    double s6, ds6; Calc(w, y, s6, ds6);
    cout<<"6. S("<<y<<")= "<<s6<<" pm "<<ds6<<" <= kaon rejection"<<endl;

    double sw6, dsw6; Calc(d, yw, sw6, dsw6);
    cout<<"   Sw("<<yw<<")= "<<sw6<<" pm "<<dsw6<<" <= kaon rejection"<<endl;

    cout<<"=> Sw/S "<<sw6/s6<<endl;
    cout<<"=> 1-Sw "<<(1-sw6)<<endl;
    cout<<"=> 1-S "<<(1-s6)<<endl;
    cout<<"=> (1-Sw)/(1-S) "<<(1-sw6)/(1-s6)<<endl;

    //--

  }



  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
}


TH1D *H(TFile *f, const string & s, Color_t t){
  cout<<s<<": "<<endl;
  TH1D *h = (TH1D*)f->Get(s.c_str());
  cout<<"\tentries "<<h->GetEntries()<<endl;
  N(h);
  h->SetLineColor(t);

  return h;
}

TH1D *H(TFile *f, const string & s, Color_t t, Color_t g){
  cout<<s<<": "<<endl;
  TH1D *h = (TH1D*)f->Get(s.c_str());
  cout<<"\tentries "<<h->GetEntries()<<endl;
  N(h);
  h->SetLineColor(t);
  h->SetFillColor(g);
  return h;
}


TH1D *Harea(TFile *f, const string & s, Color_t t, double &n){
  cout<<s<<": "<<endl;
  TH1D *h = (TH1D*)f->Get(s.c_str());
  n = h->Integral();
  cout<<"\tintegral "<<n<<endl;
  N(h);
  h->SetLineColor(t);

  return h;
}

TH1D *Harea(TFile *f, const string & s, Color_t t, Color_t g,double &n){
  cout<<s<<": "<<endl;
  TH1D *h = (TH1D*)f->Get(s.c_str());
  n = h->Integral();
  cout<<"\tintegral "<<n<<endl;
  N(h);
  h->SetLineColor(t);
  h->SetFillColor(g);

  return h;
}


TH1D *Hnorm(TFile *f, const string & s, Color_t t, const double n){
  cout<<s<<": "<<endl;
  TH1D *h = (TH1D*)f->Get(s.c_str());
  double nh = h->Integral();
  cout<<"\tfraction "<<nh/n*100<<" %"<<endl;
  N(h, nh/n);
  h->SetLineColor(t);
  h->SetLineWidth(2);

  return h;
}

TH1D *Hnorm(TFile *f, const string & s, Color_t t, Color_t g, const double n){
  cout<<s<<": "<<endl;
  TH1D *h = (TH1D*)f->Get(s.c_str());
  double nh = h->Integral();
  cout<<"\tfraction "<<nh/n*100<<" %"<<endl;
  N(h, nh/n);
  h->SetLineColor(t);
  h->SetFillColor(g);
  h->SetLineWidth(2);

  return h;
}

TH2D *H2(TFile *f, const string & s, Color_t t){

  TH2D *h = (TH2D*)f->Get(s.c_str());
  cout<<"entries "<<h->GetEntries()<<endl;
  N2(h);
  h->SetMarkerColor(t);

  return h;
} 

void Fraction(TFile *f, const string&sh, const string &sg){

  TH1D *h = (TH1D*)f->Get(sh.c_str());
  TH1D *g = (TH1D*)f->Get(sg.c_str());

  //  cout<< g->Integral() <<endl;
  // cout<< h->Integral() <<endl;
  cout<< g->Integral() / h->Integral() * 100 <<" %"<<endl;
  
}


void N(TH1D*h){

  h->Scale( 1./ h->Integral() );
}

void N(TH1D*h, double w){

  h->Scale( 1./h->Integral() * w );
}



void N2(TH2D*h){

  h->Scale( 1./ h->Integral() );
}

void Calc(TH2D *h, double y, double &s, double &ds){

  double error;
  int nx = h->GetNbinsX();
  int ny = h->GetNbinsY();
  int bin = h->GetYaxis()->FindBin(y);

  double area = h->IntegralAndError(0, nx, bin, ny, error, "");

  double Error;
  double Area = h->IntegralAndError(0, nx, 0, ny, Error, "");


  cout<<"\n bin "<<bin<<" "<<area<<" / "<<Area<<" from "<<0<<" to "<<y<<endl;

  double s = area / Area;

  double ds = s * std::sqrt( std::pow( error/area, 2) +  std::pow( Error/Area, 2) /* - 2/(area*Area)*/ );


}



