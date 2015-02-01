#include <algorithm>

bool Has(const string &str, const string &sub);
TH1D *H(TFile *, const string &);
TCanvas *C();
TCanvas *C(double w, double h);
TH1D *G(const string &);
string GetStringFromInt(int);
void Resolution(TFile *f);
void Pt(TFile *f);
void PtResolutionTauRecVsPanTau(TFile *f, const string &info);

TLatex *DrawAlgo(double x, double y);
TLatex *DrawAtlas(double x, double y);
TLatex *DrawMC(double x, double y);
TLatex *DrawInfo(double x, double y, const string &s);


TGraphAsymmErrors *GetPtResGraph(TFile *f,  const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v);
TGraphAsymmErrors *GetPtResGraphPanTau(TFile *f,  const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v);
TGraphAsymmErrors *GetPtResGraphRecTau(TFile *f,  const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v);
TGraphAsymmErrors *GetPtResGraphMain(TFile *f,  const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v, const string&Algo);

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

double const arrPt[] = {0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 250, 350, 500, 750, 1000};

int const NPt = NELEMS(arrPt);
//================================================================================
void Efficiencies(){

  string dir = "../results/V58/";

  string fn; string info;

  fn = "tau4mom.root"; info = "";
 

  TFile *f = new TFile((dir+fn).c_str());
  if(!f || f->IsZombie() ){cerr<<"unable to open file "<<fn<<endl; return;}


  //PtResolution(f, info);
  ////Pt(f);
  TrueDecayModeEff(f);
  //TrueTrackEff(f);
  // PtResolutionTauRecVsPanTau(f, info);
}
//================================================================================
void TrueTrackEff(TFile *f){

  string res = "reso_std";
  double ptRange_i = 3;
  double ptRange_f = 12;
  bool kSetYaxisAuto = 0;
  bool kSetYaxisManual = 1;

  double maxYmanual = 1;
  double minYmanual = 0.92;

  TGraphAsymmErrors *g1p0n = new TGraphAsymmErrors();
  TGraphAsymmErrors *g1p1n = new TGraphAsymmErrors();


  for(int i = ptRange_i; i <= ptRange_f; i++){

    TH1D * h1p0n  =GetRef(res);
    TH1D * h1p1n  =GetRef(res);

    TH1D * h1p0n_0 = H(f, ("tau_pan_1p0n_"+PT(i)+"true_1p0n_matched_trk_parent_0_"+res).c_str() );
    TH1D * h1p0n_1 = H(f, ("tau_pan_1p0n_"+PT(i)+"true_1p0n_matched_trk_parent_1_"+res).c_str() );

    TH1D * h1p1n_0 = H(f, ("tau_pan_1p1n_"+PT(i)+"true_1p1n_matched_trk_parent_0_"+res).c_str() );
    TH1D * h1p1n_1 = H(f, ("tau_pan_1p1n_"+PT(i)+"true_1p1n_matched_trk_parent_1_"+res).c_str() );

    if(h1p0n_0) h1p0n->Add(h1p0n_0);
    if(h1p0n_1) h1p0n->Add(h1p0n_1);

    if(h1p1n_0) h1p1n->Add(h1p1n_0);
    if(h1p1n_1) h1p1n->Add(h1p1n_1);

    if(h1p0n && h1p0n_1) EffBayes(i, g1p0n, h1p0n, h1p0n_1, arrPt[i], arrPt[i+1]);
    if(h1p1n && h1p1n_1) EffBayes(i, g1p1n, h1p1n, h1p1n_1, arrPt[i], arrPt[i+1]);

  }

  if(!g1p0n->GetN() ){ cout<<"graphs points g0 "<<g1p0n->GetN()<<" - stop"<<endl; return;}
  if(!g1p1n->GetN() ){ cout<<"graphs points g1 "<<g1p1n->GetN()<<" - stop "<<endl; return;}

  TGraphAsymmErrors *g1p0n_p = NoErrorBars(g1p0n);
  TGraphAsymmErrors *g1p1n_p = NoErrorBars(g1p1n);

  Color_t c0 = 41;
  Color_t c1 = kViolet - 9;

  g1p0n->SetFillColor(c0); g1p0n->SetLineColor(c0-2);
  g1p1n->SetFillColor(c1); g1p1n->SetLineColor(c1-2);

  g1p0n->SetMarkerStyle(20);
  g1p1n->SetMarkerStyle(24);  // g1p1n->SetFillStyle(3003);


  g1p0n_p->SetMarkerStyle(20);
  g1p1n_p->SetMarkerStyle(24);

  TCanvas *c = C();
  c->cd();
  TH1D *hb = new TH1D("hb", "", NPt-1, arrPt);
  hb->GetXaxis()->SetTitle("visible true tau p_{T} [GeV]");
  hb->GetYaxis()->SetTitle("track efficiency");
  hb->GetYaxis()->SetTitleOffset( hb->GetYaxis()->GetTitleOffset() *1.55 );
  double maxY1 = GetMaxBinCont(g1p0n_p);
  double minY1 = GetMinBinCont(g1p0n_p);
  double maxY2 = GetMaxBinCont(g1p1n_p);
  double minY2 = GetMinBinCont(g1p1n_p);
  double maxY = std::max(maxY1, maxY2);
  double minY = std::min(minY1, minY2);
  cout<<"max Y "<<maxY<<endl;
  cout<<"min Y "<<minY<<endl;

  if(kSetYaxisAuto){ hb->SetMaximum( maxY * 1.1 ); hb->SetMinimum( minY * 0.8 ); }
  else if (kSetYaxisManual){ hb->SetMaximum( maxYmanual ); hb->SetMinimum( minYmanual ); }
  else { hb->SetMinimum( 0 );  hb->SetMaximum( 1 ); }

  hb->GetXaxis()->SetRangeUser( arrPt[ptRange_i-1], arrPt[ptRange_f] );
  hb->Draw();
  g1p0n->Draw("S E2 Z");
  g1p1n->Draw("S E2 Z");
  if(g1p0n_p) g1p0n_p->Draw("PS");
  if(g1p1n_p) g1p1n_p->Draw("PS");

  TLegend *l = L(0.15, 0.5, 0.4, 0.7);
  l->SetHeader("track from real tau");
  l->AddEntry(g1p0n, "1p0n-1p0n Decay Mode", "pf");
  l->AddEntry(g1p1n, "1p1n-1p1n Decay Mode", "pf");
  //l->AddEntry(g0, "otherwise", "pf");
  l->Draw();

}
//================================================================================
void TrueDecayModeEff(TFile *f){

  string res;
  string mode;

  int ptRange_i; int ptRange_f;

  bool kBayesDivide = 1;

  bool kOneMode = 0;

  bool kSetYaxisRange = 1;

  bool kIncludeOther = 0;

  mode = "1p0n";
  //mode = "1p1n";
  //mode = "1pXn";

  ptRange_i = 3; ptRange_f = 15;

  //res = "reso_std";
  res = "reso_rel";

  TGraphAsymmErrors *g = new TGraphAsymmErrors();
  TGraphAsymmErrors *r = new TGraphAsymmErrors();

  //tau_pan_1p_true_1p_reso_rel
  //tau_pan_1p_20_25_true_1p_reso_re
  //tau_pan_1p0n_20_25_true_1p0n_reso_rel

  // one mode
  for(int i = ptRange_i; i <= ptRange_f; i++){

    if(kOneMode){
      TH1D * h  =GetRef(res);
      TH1D * t  =GetRef(res);
      TH1D * z  =GetRef(res);

      TH1D * h0 = H(f, ("tau_pan_1p0n_"+PT(i)+"true_"+mode+"_"+res).c_str() );
      TH1D * h1 = H(f, ("tau_pan_1p1n_"+PT(i)+"true_"+mode+"_"+res).c_str() );
      TH1D * h2 = H(f, ("tau_pan_1pXn_"+PT(i)+"true_"+mode+"_"+res).c_str() );
      TH1D * h3 = H(f, ("tau_pan_3p0n_"+PT(i)+"true_"+mode+"_"+res).c_str() );
      TH1D * h4 = H(f, ("tau_pan_3pXn_"+PT(i)+"true_"+mode+"_"+res).c_str() );
      TH1D * h5 = H(f, ("tau_pan_other_"+PT(i)+"true_"+mode+"_"+res).c_str() );

      if(h0) h->Add(h0);
      if(h1) h->Add(h1);
      if(h2) h->Add(h2);
      if(h3) h->Add(h3);
      if(h4) h->Add(h4);
      if(kIncludeOther) if(h5) h->Add(h5);

      if(mode!="1p0n") if(h0) t->Add(h0);
      if(mode!="1p1n") if(h1) t->Add(h1);
      if(mode!="1pXn") if(h2) t->Add(h2);
      if(mode!="3p0n") if(h3) t->Add(h3);
      if(mode!="3pXn") if(h4) t->Add(h4);
      if(kIncludeOther) if(mode!="other") if(h5) t->Add(h5);

      if(mode=="1p0n") z->Add(h0);
      if(mode=="1p1n") z->Add(h1);
      if(mode=="1pXn") z->Add(h2);
      if(mode=="3p0n") z->Add(h3);
      if(mode=="3pXn") z->Add(h4);
      if(kIncludeOther)if(mode=="other") z->Add(h5);

      if(h && z) if( kBayesDivide ) EffBayes(i, g, h, z, arrPt[i], arrPt[i+1]); else Eff(i, g, h, z, arrPt[i], arrPt[i+1]);
      if(h && t) if( kBayesDivide ) EffBayes(i, r, h, t, arrPt[i], arrPt[i+1]); else Eff(i, r, h, t, arrPt[i], arrPt[i+1]);

    }else{
      //tau_pan_1p0n_20_25_true_1p0n_reso_rel
      //tau_pan_1p1n_90_100_true_1pnX_reso_rel:
      cout<<"all 1p modes "<<endl;

      TH1D * h00 = H(f, ("tau_pan_1p0n_"+PT(i)+"true_1p0n_"+res).c_str() );
      TH1D * h01 = H(f, ("tau_pan_1p1n_"+PT(i)+"true_1p1n_"+res).c_str() );
      TH1D * h02 = H(f, ("tau_pan_1pXn_"+PT(i)+"true_1pXn_"+res).c_str() );

      TH1D * h1 = H(f, ("tau_pan_1p1n_"+PT(i)+"true_1p0n_"+res).c_str() );
      TH1D * h2 = H(f, ("tau_pan_1pXn_"+PT(i)+"true_1p0n_"+res).c_str() );
      TH1D * h3 = H(f, ("tau_pan_3p0n_"+PT(i)+"true_1p0n_"+res).c_str() );
      TH1D * h4 = H(f, ("tau_pan_3pXn_"+PT(i)+"true_1p0n_"+res).c_str() );
      TH1D * h5 = H(f, ("tau_pan_other_"+PT(i)+"true_1p0n_"+res).c_str() );

      TH1D * u1 = H(f, ("tau_pan_1p0n_"+PT(i)+"true_1p1n_"+res).c_str() );
      TH1D * u2 = H(f, ("tau_pan_1pXn_"+PT(i)+"true_1p1n_"+res).c_str() );
      TH1D * u3 = H(f, ("tau_pan_3p0n_"+PT(i)+"true_1p1n_"+res).c_str() );
      TH1D * u4 = H(f, ("tau_pan_3pXn_"+PT(i)+"true_1p1n_"+res).c_str() );
      TH1D * u5 = H(f, ("tau_pan_other_"+PT(i)+"true_1p1n_"+res).c_str() );

      TH1D * q1 = H(f, ("tau_pan_1p0n_"+PT(i)+"true_1pXn_"+res).c_str() );
      TH1D * q2 = H(f, ("tau_pan_1p1n_"+PT(i)+"true_1pXn_"+res).c_str() );
      TH1D * q3 = H(f, ("tau_pan_3p0n_"+PT(i)+"true_1pXn_"+res).c_str() );
      TH1D * q4 = H(f, ("tau_pan_3pXn_"+PT(i)+"true_1pXn_"+res).c_str() );
      TH1D * q5 = H(f, ("tau_pan_other_"+PT(i)+"true_1pXn_"+res).c_str() );

      TH1D * t  =GetRef(res);
      if(h00) t->Add(h00);
      if(h01) t->Add(h01);
      if(h02) t->Add(h02);

      TH1D * e  =GetRef(res);
      if(h1) e->Add(h1);
      if(h2) e->Add(h2);
      if(h3) e->Add(h3);
      if(h4) e->Add(h4);
      if(kIncludeOther) if(h5) e->Add(h5);

      if(u1) e->Add(u1);
      if(u2) e->Add(u2);
      if(u3) e->Add(u3);
      if(u4) e->Add(u4);
      if(kIncludeOther) if(u5) e->Add(u5);

      if(q1) e->Add(q1);
      if(q2) e->Add(q2);
      if(q3) e->Add(q3);
      if(q4) e->Add(q4);
      if(kIncludeOther) if(q5) e->Add(q5);

      TH1D * w  =GetRef(res);
      if(t) w->Add(t);
      if(e) w->Add(e);

      if(t && w)  if( kBayesDivide ) EffBayes(i, g, w, t, arrPt[i], arrPt[i+1]); else Eff(i, g, w, t, arrPt[i], arrPt[i+1]);
      if(t && e)  if( kBayesDivide ) EffBayes(i, r, w, e, arrPt[i], arrPt[i+1]); else Eff(i, r, w, e, arrPt[i], arrPt[i+1]);

    }
  }

  cout<<"graphs points g "<<g->GetN()<<endl;
  cout<<"graphs points r "<<r->GetN()<<endl;

  TGraphAsymmErrors *gp = NoErrorBars(g);
  TGraphAsymmErrors *rp = NoErrorBars(r);

  Color_t cg = 41;
  Color_t cr = kViolet - 9;

  g->SetFillColor(cg); g->SetLineColor(cg-2);
  r->SetFillColor(cr); r->SetLineColor(cr-2);

  g->SetMarkerStyle(20);
  r->SetMarkerStyle(24);

  gp->SetMarkerStyle(20);
  rp->SetMarkerStyle(24);

  TCanvas *c = C();
  c->cd();
  TH1D *hb = new TH1D("hb", "", NPt-1, arrPt);
  hb->GetXaxis()->SetTitle("visible true tau p_{T} [GeV]");
  hb->GetYaxis()->SetTitle("(mis)classification efficiency");
  hb->GetYaxis()->SetTitleOffset( hb->GetYaxis()->GetTitleOffset() *1.4 );
  double maxY1 = GetMaxBinCont(gp);
  double minY1 = GetMinBinCont(gp);
  double maxY2 = GetMaxBinCont(rp);
  double minY2 = GetMinBinCont(rp);
  double maxY = std::max(maxY1, maxY2);
  double minY = std::min(minY1, minY2);
  cout<<"max Y "<<maxY<<endl;
  cout<<"min Y "<<minY<<endl;

  if(kSetYaxisRange){ hb->SetMaximum( maxY * 1.1 ); hb->SetMinimum( minY * 0.8 ); } else { hb->SetMinimum( 0 );  hb->SetMaximum( 1 ); }

  hb->GetXaxis()->SetRangeUser( arrPt[ptRange_i-1], arrPt[ptRange_f] );
  hb->Draw();
  g->Draw("S E2 Z");
  r->Draw("S E2 Z");
  if(gp) gp->Draw("PS");
  if(rp) rp->Draw("PS");

  TLegend *l = L(0.15, 0.5, 0.4, 0.7);
  if(kOneMode)
    l->SetHeader( ("True Decay Mode " + mode).c_str());
  else
    l->SetHeader("All 1p True Decay Modes");
  l->AddEntry(g, "classiffied", "pf");
  l->AddEntry(r, "misclassiffied", "pf");
  l->Draw();


  DrawAtlas(0.175, 0.9)->Draw();
  DrawAlgo(0.65, 0.9)->Draw();
  DrawMC(0.65, 0.84)->Draw();

  //  DrawInfo(0.6, 0.9, info)->Draw();

}
//================================================================================
//================================================================================
void PtResolutionTauRecVsPanTau(TFile *f, const string &info){

  bool kNorm = 1;
  int ResType = 3; //0: RMS,  1: RMS/Mean,   2: RMS/Mean modified in +-3sigma around Mean,   3: RMS modified in +-3sigma around Mean
  string rmode; string tmode; string res; string lat;
  double minY = 0.05;
  double maxY = 0.25;
  double minX = 10;
  double maxX = 110;
  double bin_minX = 3;
  double bin_maxX = 13;


  rmode = "1p0n"; tmode = "1p0n"; lat = rmode + " - " + tmode;

  //res = "reso_std";
  res = "reso_rel";

  //1p0n - 1p0n
  /*  vector<double> v1;
  TGraphAsymmErrors *g1 = GetPtResGraph(f, "1p0n", "1p0n", res, ResType, v1);
  TGraphAsymmErrors *g1n =  CopyG(g1);
  RemoveZeroPoint(g1); RemoveZeroPoint(g1n); NoErrorBars(g1n);
  g1->SetLineColor(kOrange); g1->SetMarkerColor(kOrange); g1n->SetLineColor(kOrange); g1n->SetLineStyle(7); g1->SetMarkerStyle(25);
  */

  //1p - 1p or 3p - 3p
  vector<double> v2;
  //  TGraphAsymmErrors *g2 = GetPtResGraph(f, "1p", "1p", res, ResType, v2);
  TGraphAsymmErrors *g2 = GetPtResGraph(f, "3p", "3p", res, ResType, v2);
  TGraphAsymmErrors *g2n =  CopyG(g2);
  RemoveZeroPoint(g2); RemoveZeroPoint(g2n); NoErrorBars(g2n);
  g2->SetLineColor(kAzure); g2->SetMarkerColor(kAzure); 
  g2n->SetLineColor(kAzure-2); g2n->SetLineStyle(7); g2->SetMarkerStyle(20); g2n->SetLineWidth(2);

  //1p0n - 1p0n
  /*vector<double> v3;
  TGraphAsymmErrors *g3 = GetPtResGraphRecTau(f, "1p0n", "1p0n", res, ResType, v3);
  TGraphAsymmErrors *g3n =  CopyG(g3);
  RemoveZeroPoint(g3); RemoveZeroPoint(g3n); NoErrorBars(g3n);
  g3->SetLineColor(kMagenta); g3->SetMarkerColor(kMagenta-2); g3n->SetLineColor(kMagenta-2); g3n->SetLineStyle(7); g3->SetMarkerStyle(23);
  */

  //1p - 1p or 3p - 3p
  vector<double> v4;
  //  TGraphAsymmErrors *g4 = GetPtResGraphRecTau(f, "1p", "1p", res, ResType, v4);
  TGraphAsymmErrors *g4 = GetPtResGraphRecTau(f, "3p", "3p", res, ResType, v4);
  TGraphAsymmErrors *g4n =  CopyG(g4);
  RemoveZeroPoint(g4); RemoveZeroPoint(g4n); NoErrorBars(g4n);
  g4n->SetLineColor(kGray); g4n->SetLineStyle(7); g4n->SetLineWidth(2);
  g4->SetMarkerStyle(24); 

  //draw
  TCanvas *c = C(900, 600);
  c->cd();
  TH1D *hb = new TH1D("hb", "", NPt-1, arrPt);
  hb->Draw();
  hb->SetMinimum(minY); hb->SetMaximum(maxY); 
  //hb->GetXaxis()->SetRangeUser(minX, maxX);
  hb->GetXaxis()->SetRange(bin_minX, bin_maxX);
  if(res=="reso_std"){ hb->GetXaxis()->SetTitle("p_{T}^{vis-true} [GeV]"); hb->GetYaxis()->SetTitle("#sigma[ p_{T}^{reco}/p_{T}^{vis-true} ]"); }
  if(res=="reso_rel"){ hb->GetXaxis()->SetTitle("p_{T}^{vis-true} [GeV]"); hb->GetYaxis()->SetTitle("#sigma[ (p_{T}^{reco} - p_{T}^{vis-true})/p_{T}^{vis-true} ]"); }
  hb->GetYaxis()->SetTitleOffset( hb->GetYaxis()->GetTitleOffset() *1.6 );

  //g1n->Draw("L S");  g1->Draw("P Z");
  g2n->Draw("L S");  g2->Draw("P Z");
  //g3n->Draw("L S");  g3->Draw("P Z");
  g4n->Draw("L S");  g4->Draw("P Z");

  TLatex *tex = new TLatex(0.1, 0.7, lat.c_str() ); tex->SetNDC(); tex->SetTextFont(44); tex->Draw();

  TLegend *leg = L(0.7, 0.35, 0.95, 0.95);
  leg->SetHeader("Decay Mode");
  //leg->AddEntry(g1, "1p0n - 1p0n PanTau", "p");
  //  leg->AddEntry(g2, "1p - 1p PanTau", "p");
  leg->AddEntry(g2, "3p - 3p PanTau", "p");
  //leg->AddEntry(g3, "1p0n - 1p0n tauRec", "p");
  // leg->AddEntry(g4, "1p - 1p tauRec", "p");
  leg->AddEntry(g4, "3p - 3p tauRec", "p");
  leg->Draw();
  //c->Modified();

  DrawAtlas(0.175, 0.9)->Draw();
  DrawAlgo(0.175, 0.84)->Draw();
  DrawMC(0.175, 0.78)->Draw();

  DrawInfo(0.5, 0.9, info)->Draw();

}
void PtResolution(TFile *f, const string &info){

  bool kNorm = 1;
  int ResType = 3; //0: RMS,  1: RMS/Mean,   2: RMS/Mean modified in +-3sigma around Mean,   3: RMS modified in +-3sigma around Mean
  string rmode; string tmode; string res; string lat;
  double minY = 0.05;
  double maxY = 0.17;
  double minX = 10;
  double maxX = 110;


  rmode = "1p0n"; tmode = "1p0n"; lat = rmode + " - " + tmode;

  //res = "reso_std";
  res = "reso_rel";

  //1p0n - 1p0n
  vector<double> v1;
  TGraphAsymmErrors *g1 = GetPtResGraph(f, "1p0n", "1p0n", res, ResType, v1);
  TGraphAsymmErrors *g1n =  CopyG(g1);
  RemoveZeroPoint(g1); RemoveZeroPoint(g1n); NoErrorBars(g1n);
  g1->SetLineColor(kOrange); g1->SetMarkerColor(kOrange); 
  g1n->SetLineColor(kOrange); g1n->SetLineStyle(7); g1->SetMarkerStyle(25); g1n->SetLineWidth(2);


  //1p1n - 1p1n
  vector<double> v2;
  TGraphAsymmErrors *g2 = GetPtResGraph(f, "1p1n", "1p1n", res, ResType, v2);
  TGraphAsymmErrors *g2n =  CopyG(g2);
  RemoveZeroPoint(g2); RemoveZeroPoint(g2n); NoErrorBars(g2n);
  g2->SetLineColor(kAzure); g2->SetMarkerColor(kAzure); 
  g2n->SetLineColor(kAzure-2); g2n->SetLineStyle(7); g2->SetMarkerStyle(20); g2n->SetLineWidth(2);

  //1pXn - 1pXn
  vector<double> v3;
  TGraphAsymmErrors *g3 = GetPtResGraph(f, "1pXn", "1pXn", res, ResType, v3);
  TGraphAsymmErrors *g3n =  CopyG(g3);
  RemoveZeroPoint(g3); RemoveZeroPoint(g3n); NoErrorBars(g3n);
  g3->SetLineColor(kMagenta); g3->SetMarkerColor(kMagenta-2); g3n->SetLineColor(kMagenta-2); g3n->SetLineStyle(7); g3->SetMarkerStyle(23);
  g3n->SetLineWidth(2);

  //1p - 1p
  vector<double> v4;
  TGraphAsymmErrors *g4 = GetPtResGraph(f, "1p", "1p", res, ResType, v4);
  TGraphAsymmErrors *g4n =  CopyG(g4);
  RemoveZeroPoint(g4); RemoveZeroPoint(g4n); NoErrorBars(g4n);
  g4n->SetLineColor(kGray); g4n->SetLineStyle(7); g4->SetMarkerStyle(24); g4n->SetLineWidth(2);

  //draw
  TCanvas *c = C(900, 600);
  c->cd();
  TH1D *hb = new TH1D("hb", "", NPt-1, arrPt);
  hb->Draw();
  hb->SetMinimum(minY); hb->SetMaximum(maxY); hb->GetXaxis()->SetRangeUser(minX, maxX);
  if(res=="reso_std"){ hb->GetXaxis()->SetTitle("p_{T}^{vis-true} [GeV]"); hb->GetYaxis()->SetTitle("#sigma[ p_{T}^{reco}/p_{T}^{vis-true} ]"); }
  if(res=="reso_rel"){ hb->GetXaxis()->SetTitle("p_{T}^{vis-true} [GeV]"); hb->GetYaxis()->SetTitle("#sigma[ (p_{T}^{reco} - p_{T}^{vis-true})/p_{T}^{vis-true} ]"); }
  hb->GetYaxis()->SetTitleOffset( hb->GetYaxis()->GetTitleOffset() *1.6 );

  g1n->Draw("L S");  g1->Draw("P Z");
  g2n->Draw("L S");  g2->Draw("P Z");
  g3n->Draw("L S");  g3->Draw("P Z");
  g4n->Draw("L S");  g4->Draw("P Z");

  TLatex *tex = new TLatex(0.1, 0.7, lat.c_str() ); tex->SetNDC(); tex->SetTextFont(44); tex->Draw();

  TLegend *leg = L(0.7, 0.35, 0.95, 0.95);
  leg->SetHeader("Decay Mode");
  leg->AddEntry(g4, "1p - 1p", "p");
  leg->AddEntry(g1, "1p0n - 1p0n", "p");
  leg->AddEntry(g2, "1p1n - 1p1n", "p");
  leg->AddEntry(g3, "1pXn - 1pXn", "p");
  leg->Draw();
  //c->Modified();

  DrawAtlas(0.175, 0.9)->Draw();
  DrawAlgo(0.175, 0.84)->Draw();
  DrawMC(0.175, 0.78)->Draw();

  DrawInfo(0.6, 0.9, info)->Draw();

  

  //pts
  return;
  double ym = *max_element(v.begin(), v.end());

  TCanvas *cc = C();
  cc->cd();
  TH1D *href = GetRef(res);
  href->Draw();

  gPad->SetLogy();

  if(!kNorm) href->SetMaximum(ym*1.1);
  TLegend *l = L(0.7, 0.35, 0.95, 0.95);
  l->SetHeader("p_{T} bin [GeV]");
  int lw=2;
  vector<double> vv;

  if(h0 && k0){ h0->Draw("same"); h0->SetLineColor(1);  h0->SetLineWidth(lw); if(kNorm) N(vv, h0); l->AddEntry(h0, PT(0).c_str()); }
  if(h1 && k1){ h1->Draw("same"); h1->SetLineColor(1);  h1->SetLineWidth(lw); if(kNorm)  N(vv, h1); l->AddEntry(h1, PT(1).c_str()); }
  if(h2 && k2){ h2->Draw("same"); h2->SetLineColor(1);  h2->SetLineWidth(lw); if(kNorm) N(vv, h2); l->AddEntry(h2, PT(2).c_str()); }
  if(h3 && k3){ h3->Draw("same"); h3->SetLineColor(kBlack);   h3->SetLineWidth(lw); if(kNorm) N(vv, h3); l->AddEntry(h3, PT(3).c_str()); }
  if(h4 && k4){ h4->Draw("same"); h4->SetLineColor(kRed);     h4->SetLineWidth(lw); if(kNorm) N(vv, h4); l->AddEntry(h4, PT(4).c_str()); }
  if(h5 && k5){ h5->Draw("same"); h5->SetLineColor(kGreen);   h5->SetLineWidth(lw); if(kNorm) N(vv, h5); l->AddEntry(h5, PT(5).c_str()); }
  if(h6 && k6){ h6->Draw("same"); h6->SetLineColor(kYellow);  h6->SetLineWidth(lw); if(kNorm) N(vv, h6); l->AddEntry(h6, PT(6).c_str()); }
  if(h7 && k7){ h7->Draw("same"); h7->SetLineColor(kAzure);   h7->SetLineWidth(lw); h7->SetLineStyle(7); if(kNorm) N(vv, h7); l->AddEntry(h7, PT(7).c_str()); }
  if(h8 && k8){ h8->Draw("same"); h8->SetLineColor(kMagenta); h8->SetLineWidth(lw); if(kNorm) N(vv, h8); l->AddEntry(h8, PT(8).c_str()); }
  if(h9 && k9){ h9->Draw("same"); h9->SetLineColor(kBlue);        h9->SetLineWidth(lw); if(kNorm) N(vv, h9); l->AddEntry(h9, PT(9).c_str()); }
  if(h10 && k10){ h10->Draw("same"); h10->SetLineColor(kGray+2);  h10->SetLineWidth(lw); if(kNorm) N(vv, h10); l->AddEntry(h10, PT(10).c_str()); }
  if(h11 && k11){ h11->Draw("same"); h11->SetLineColor(kCyan);    h11->SetLineWidth(lw);  if(kNorm) N(vv, h11); l->AddEntry(h11, PT(11).c_str()); }
  if(h12 && k12){ h12->Draw("same"); h12->SetLineColor(kViolet);  h12->SetLineWidth(lw);   if(kNorm) N(vv, h12); l->AddEntry(h12, PT(12).c_str()); }
  if(h13 && k13){ h13->Draw("same"); h13->SetLineColor(kSpring);  h13->SetLineWidth(lw);  h13->SetLineStyle(7);  if(kNorm) N(vv, h13); l->AddEntry(h13, PT(13).c_str()); }

  if(kNorm){
    double Ym = *max_element(vv.begin(), vv.end());
    href->SetMaximum(Ym*1.1);
  }

  l->Draw();



}

TGraphAsymmErrors *GetPtResGraph(TFile *f,  const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v){
  return GetPtResGraphMain(f, recmode, truemode, res, ResType, v, "pan");
}
TGraphAsymmErrors *GetPtResGraphPanTau(TFile *f,  const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v){
  return GetPtResGraphMain(f, recmode, truemode, res, ResType, v, "pan");
}
TGraphAsymmErrors *GetPtResGraphRecTau(TFile *f,  const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v){
  return GetPtResGraphMain(f, recmode, truemode, res, ResType, v, "rec");
}
TGraphAsymmErrors *GetPtResGraphMain(TFile *f,  const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v, const string&Algo){

  string tmode; string rmode;

  if(!recmode.size()) return 0;
  if(recmode.size()) rmode = Algo+"_"+recmode+"_";
  if(tmode.size()) tmode = "true_"+truemode+"_";

  bool k0(0), k1(0), k2(0), k3(1), k4(1), k5(1), k6(1), k7(1), k8(1), k9(1), k10(1), k11(1), k12(0), k13(0);

  TGraphAsymmErrors *g = new TGraphAsymmErrors();

  //tau_pan_1p_20_25_true_1p_reso_rel
  TH1D * h0 = J(f, v, ("tau_" + rmode + PT(0) + tmode + res).c_str());
  TH1D * h1 = J(f, v ,("tau_" + rmode + PT(1) + tmode + res).c_str());
  TH1D * h2 = J(f, v, ("tau_" + rmode + PT(2) + tmode + res).c_str());
  TH1D * h3 = J(f, v, ("tau_" + rmode + PT(3) + tmode + res).c_str());
  TH1D * h4 = J(f, v, ("tau_" + rmode + PT(4) + tmode + res).c_str());
  TH1D * h5 = J(f, v, ("tau_" + rmode + PT(5) + tmode + res).c_str());
  TH1D * h6 = J(f, v, ("tau_" + rmode + PT(6) + tmode + res).c_str());
  TH1D * h7 = J(f, v, ("tau_" + rmode + PT(7) + tmode + res).c_str());
  TH1D * h8 = J(f, v, ("tau_" + rmode + PT(8) + tmode + res).c_str());
  TH1D * h9 = J(f, v, ("tau_" + rmode + PT(9) + tmode + res).c_str());
  TH1D *h10 = J(f, v, ("tau_" + rmode + PT(10)+ tmode + res).c_str());
  TH1D *h11 = J(f, v, ("tau_" + rmode + PT(11)+ tmode + res).c_str());
  TH1D *h12 = J(f, v, ("tau_" + rmode + PT(12)+ tmode + res).c_str());
  TH1D *h13 = J(f, v, ("tau_" + rmode + PT(13)+ tmode + res).c_str());
  
  int i(1); 
  if(k0) if(h0) SetP(i++,ResType, g, h0, arrPt[0], arrPt[1]);
  if(k1) if(h1) SetP(i++,ResType, g, h1, arrPt[1], arrPt[2]);
  if(k2) if(h2) SetP(i++,ResType, g, h2, arrPt[2], arrPt[3]);
  if(k3) if(h3) SetP(i++,ResType, g, h3, arrPt[3], arrPt[4]);
  if(k4) if(h4) SetP(i++,ResType, g, h4, arrPt[4], arrPt[5]);
  if(k5) if(h5) SetP(i++,ResType, g, h5, arrPt[5], arrPt[6]);
  if(k6) if(h6) SetP(i++,ResType, g, h6, arrPt[6], arrPt[7]);
  if(k7) if(h7) SetP(i++,ResType, g, h7, arrPt[7], arrPt[8]);
  if(k8) if(h8) SetP(i++,ResType, g, h8, arrPt[8], arrPt[9]);
  if(k9) if(h9) SetP(i++,ResType, g, h9, arrPt[9], arrPt[10]);
  if(k10) if(h10) SetP(i++,ResType, g, h10, arrPt[10], arrPt[11]);
  if(k11) if(h11) SetP(i++,ResType, g, h11, arrPt[11], arrPt[12]);
  if(k12) if(h12) SetP(i++,ResType, g, h12, arrPt[12], arrPt[13]);
  if(k13) if(h13) SetP(i++,ResType, g, h13, arrPt[13], arrPt[14]);

  return g;
}

//================================================================================
void Pt(TFile *f){

  cout<<"retrieving histograms..."<<endl;
  vector<double> vy;
  TH1D *h0 = J(f, vy, "tau_pan_5_10_pt");
  TH1D *h1 = J(f, vy,"tau_pan_10_15_pt");
  TH1D *h2 = J(f, vy, "tau_pan_15_20_pt");
  TH1D *h3 = J(f, vy, "tau_pan_20_25_pt");
  TH1D *h4 = J(f, vy, "tau_pan_25_30_pt");
  TH1D *h5 = J(f, vy, "tau_pan_30_40_pt");
  TH1D *h6 = J(f, vy, "tau_pan_40_50_pt");
  TH1D *h7 = J(f, vy, "tau_pan_50_60_pt");
  TH1D *h8 = J(f, vy, "tau_pan_60_70_pt");
  TH1D *h9 = J(f, vy, "tau_pan_70_80_pt");
  TH1D *h10 = J(f, vy, "tau_pan_80_90_pt");
  TH1D *h11 = J(f, vy, "tau_pan_90_100_pt");
  TH1D *h12 = J(f, vy, "tau_pan_100_120_pt");
  TH1D *h13 = J(f, vy, "tau_pan_120_150_pt");

  //std::sort(vy.begin(), vy.end());  double ym = vy[0];
  double ym = *max_element(vy.begin(), vy.end());

  TCanvas *cc = C();
  cc->cd();
  h0->Draw(); h0->SetLineColor(42);
  h0->SetMaximum(ym);
  h1->Draw("same"); h1->SetLineColor(1);
  h2->Draw("same"); h2->SetLineColor(2);
  h3->Draw("same"); h3->SetLineColor(3);
  h4->Draw("same"); h4->SetLineColor(4);
  h5->Draw("same"); h5->SetLineColor(5);
  h6->Draw("same"); h6->SetLineColor(6);
  h7->Draw("same"); h7->SetLineColor(7);
  h8->Draw("same"); h8->SetLineColor(8);
  h9->Draw("same"); h9->SetLineColor(9);
  h10->Draw("same"); h10->SetLineColor(32);
  h11->Draw("same"); h11->SetLineColor(11);
  h12->Draw("same"); h12->SetLineColor(12);
  h13->Draw("same"); h13->SetLineColor(13);


}
//================================================================================
TH1D *GetRef(const string &s){

  static int i(1);
  string name = "histo"+GetStringFromInt(i++);
  //cout<<"empty histo "<<name<<endl;

  string t_res_rel = "(p_{T}^{reco} - p_{T}^{true})/p_{T}^{true}"; int n_res_rel = 101; double l_res_rel = -1.01; double r_res_rel = 1.01;
  string t_res_det = "(E^{reco} - E^{true})/#sqrt{E^{true}}"; int n_res_det = 201; double l_res_det = -2.01; double r_res_det = 2.01;
  string t_res_std = "p_{T}^{reco}/p_{T}^{true}"; int n_res_std = 300; double l_res_std = 0; double r_res_std = 3;
  string t_res_log = "log_{10}[E_{T}^{reco}/E_{T}^{true}]";int n_res_log = 101; double l_res_log = -1.01; double r_res_log = 1.01;
  int n_eta = 102; double l_eta = -2.55; double r_eta = 2.55;

  TH1D *h;

  if(s=="reso_rel"){ h =  new TH1D(name.c_str(),"", n_res_rel, l_res_rel, r_res_rel);  h->GetXaxis()->SetTitle(t_res_rel.c_str()); }
  else if(s=="reso_std"){ h = new TH1D(name.c_str(),"", n_res_std, l_res_std, r_res_std);    h->GetXaxis()->SetTitle(t_res_std.c_str()); }
  else if(s=="eta"){ h = new TH1D(name.c_str(),"", n_eta, l_eta, r_eta);     h->GetXaxis()->SetTitle("#eta");}
  else cerr<<"GetRef - "<<s<<" not found "<<endl;


  return h;

}
//================================================================================
void Eff(int i, TGraphAsymmErrors *g, TH1D *hm, TH1D *hd, double x1, double x2){

  double x = (x1+x2)/2.;
  double dx1 = fabs(x-x1);
  double dx2 = fabs(x-x2);

  double dm; double dd;
  double m = hm->IntegralAndError(-1,-1, dm, "");
  double d = hd->IntegralAndError(-1,-1, dd, "");

  if(!m) return;
  if(!d) return;

  double y = d/m;
  double dy = y * sqrt( pow(dm/m, 2) + pow(dd/d, 2) );

  g->SetPoint(i, x, y);
  g->SetPointError(i, dx1, dx2, dy, dy);

}
//================================================================================
void EffBayes(int i, TGraphAsymmErrors *g, TH1D *hm, TH1D *hd, double x1, double x2){

  double x = (x1+x2)/2.;
  double dx1 = fabs(x-x1);
  double dx2 = fabs(x-x2);

  double dm; double dd;
  double m = hm->IntegralAndError(-1,-1, dm, "");
  double d = hd->IntegralAndError(-1,-1, dd, "");

  if(!m) return; if(!d) return;

  TH1D *hm = new TH1D( ("hm_"+GetStringFromInt(x-dx1)+"_"+GetStringFromInt(x+dx2)).c_str(), "", 1, x-dx1, x+dx2);
  TH1D *hd = new TH1D( ("hd_"+GetStringFromInt(x-dx1)+"_"+GetStringFromInt(x+dx2)).c_str(), "", 1, x-dx1, x+dx2);

  hm->SetBinContent(1, m); hm->SetBinError(1, dm);
  hd->SetBinContent(1, d); hd->SetBinError(1, dd);

  cout<<"hm "<<hm->GetBinContent(1)<<" "<<hm->GetBinLowEdge(1)<<" - "<<hm->GetBinLowEdge(1)+hm->GetBinWidth(1)<<endl;
  TGraphAsymmErrors *gn = new TGraphAsymmErrors(hd, hm,"cl=0.683 b(1,1) mode");
  //gn->Divide(hd, hm,"cl=0.683 b(1,1) mode");

  double gx; double gy;
  gn->GetPoint(0, gx, gy);

  cout<<i<<". "<<gn->GetN()<<" "<<x-dx1<<" "<<x+dx2<<" "<<gx<<" "<<d<<"/"<<m<<" = "<<gy<<" dxlow "<<gn->GetErrorXlow(0)<<" dylow "<<gn->GetErrorYlow(0)<<endl;

  //g = gn;
  /*
    double y = d/m;
    double dy = y * sqrt( pow(dm/m, 2) + pow(dd/d, 2) );

    g->SetPoint(i, x, y);
    g->SetPointError(i, dx1, dx2, dy, dy);
  */

  g->SetPoint(i, gx, gy);
  g->SetPointEXlow( i, gn->GetErrorXlow(0) );
  g->SetPointEXhigh( i, gn->GetErrorXhigh(0) );
  g->SetPointEYlow( i, gn->GetErrorYlow(0) );
  g->SetPointEYhigh( i, gn->GetErrorYhigh(0) );

  double _gx; double _gy;
  g->GetPoint(0, _gx, _gy);
  //cout<<i<<" xcheck "<<_gx<<"  "<<_gy<<endl;

  delete hm; delete hd; delete gn;
}
//================================================================================
void SetP(int bin, int type, TGraphAsymmErrors *g, TH1D *h, double x1, double x2){

  Set(bin, type, g, h, x1, x2);
}
//================================================================================
void Set(int bin = -1, int type, TGraphAsymmErrors *g, TH1D *h, double x1, double x2){

  if(type == 0 )
    Set0(bin, g, h, x1, x2);
  else if(type == 1 )
    Set1(bin, g, h, x1, x2);
  else if(type == 2 )
    Set2(bin, g, h, x1, x2);
  else if(type == 3 )
    Set3(bin, g, h, x1, x2);
  else
    cerr<<"Set - nothing to do "<<endl;
}
//================================================================================
void Set0(int j, TGraphAsymmErrors *g, TH1D *h, double x1, double x2){

  int bin;

  static int i(1);

  double x = (x1+x2)/2.;
  double dx1 = fabs(x-x1);
  double dx2 = fabs(x-x2);
  double enu = h->GetRMS();
  double y = enu;
  double denu = h->GetRMSError();
  double dy = y * sqrt( pow(denu/enu, 2) );
  double Dy = dy;///2.;

  if(j < 0 ) bin = i; else bin = j; 
  
  cout<<"Bin "<<bin<<"  pT "<<x1<<"-"<<x2<<"  StdDev "<<y<<" +- "<<Dy<<endl;

  g->SetPoint(bin, x, y);
  g->SetPointError(bin, dx1, dx2, dy, Dy);

  i++;
}
//================================================================================
void Set1(int j, TGraphAsymmErrors *g, TH1D *h, double x1, double x2){

  int bin;
  static int i(1);

  double x = (x1+x2)/2.;
  double dx1 = fabs(x-x1);
  double dx2 = fabs(x-x2);
  double enu = h->GetRMS();
  double den = h->GetMean();
  double y = enu/den;
  double denu = h->GetRMSError();
  double dden = h->GetMeanError();
  double dy = y * sqrt( pow(denu/enu, 2) + pow(dden/den, 2) );
  double Dy = dy;///2.;

  if(j < 0 ) bin = i; else bin = j; 

  cout<<"Bin "<<bin<<"  pT "<<x1<<"-"<<x2<<"  RMS/Mean "<<y<<" +- "<<Dy<<endl;

  g->SetPoint(bin, x, y);
  g->SetPointError(bin, dx1, dx2, Dy, Dy);

  i++;
}
//================================================================================
void Set2(int j, TGraphAsymmErrors *g, TH1D *H, double x1, double x2){

  int bin;
  static int i(1);

  TH1D *h = H->Clone( TString::Itoa(i, 10) );

  const int n = h->GetNbinsX();
  double rms = h->GetRMS();
  double mean = h->GetMean();

  //reset range around mean and recalculate RMS

  //1. find bin for Mean
  int bin_mean(-1);
  for(int jk = 0; jk < n; jk++ ){
    double xl = h->GetBinLowEdge(jk);
    double xr = xl + h->GetBinWidth(jk);
    if( mean >= xl && mean <= xr ){
      bin_mean = jk;
      break;
    }
  }


  double RMS_l = mean - 3 * rms;
  double RMS_r = mean + 3 * rms;

  //2. find bins with 3 x RMS left and right
  int bin_mean3rms_l(-1);
  int bin_mean3rms_r(-1);
  for(int jk = 0; jk < n; jk++ ){
    double xl = h->GetBinLowEdge(jk);
    double xr = xl + h->GetBinWidth(jk);
    if( RMS_l >= xl && RMS_l <= xr )  bin_mean3rms_l = jk;
    if( RMS_r >= xl && RMS_r <= xr )  bin_mean3rms_r = jk;
  }

  //3. set new range and calculate rms & mean
  h->GetXaxis()->SetRange(bin_mean3rms_l, bin_mean3rms_r);

  double new_rms = h->GetRMS();
  double new_mean = h->GetMean();

  // cout<<"Bin "<<i<<"Mean " << mean <<" Bin "<<bin_mean<<" / "<< n <<" RMS "<<rms<<" <>-3s "<<RMS_l<<" bin "<< bin_mean3rms_l <<" <>+3s "<<RMS_r
  //     <<" bin "<<bin_mean3rms_r<<" ("
  //     <<(bin_mean3rms_r-bin_mean3rms_l)/(float)n*100<<" %)"<<endl;
  // cout<<"\tMean "<<new_mean<<" rms "<<new_rms<<endl;

  //set points now
  double x = (x1+x2)/2.;
  double dx1 = fabs(x-x1);
  double dx2 = fabs(x-x2);
  double y = new_rms/new_mean;
  double drms = h->GetRMSError();
  double dmean = h->GetMeanError();
  double dy = y * sqrt( pow(dmean/new_mean, 2) + pow(drms/new_rms, 2) );
  double Dy = dy;///2.;

  if(j < 0 ) bin = i; else bin = j;

  cout<<"\t Bin "<<bin<<"  pT "<<x1<<"-"<<x2<<"  RMS/Mean(pm 3sigma) "<<y<<" +- "<<Dy<<endl;

  g->SetPoint(bin, x, y);
  g->SetPointError(bin, dx1, dx2, Dy, Dy);

  i++;
}
//================================================================================
void Set3(int j, TGraphAsymmErrors *g, TH1D *H, double x1, double x2){

  int bin;

  static int i(1);

  TH1D *h = H->Clone( TString::Itoa(i, 10) );

  const int n = h->GetNbinsX();
  double rms = h->GetRMS();
  double mean = h->GetMean();

  //reset range around mean and recalculate RMS

  //1. find bin for Mean
  int bin_mean(-1);
  for(int jk = 0; jk < n; jk++ ){
    double xl = h->GetBinLowEdge(jk);
    double xr = xl + h->GetBinWidth(jk);
    if( mean >= xl && mean <= xr ){
      bin_mean = jk;
      break;
    }
  }


  double RMS_l = mean - 3 * rms;
  double RMS_r = mean + 3 * rms;

  //2. find bins with 3 x RMS left and right
  int bin_mean3rms_l(-1);
  int bin_mean3rms_r(-1);
  for(int jk = 0; jk < n; jk++ ){
    double xl = h->GetBinLowEdge(jk);
    double xr = xl + h->GetBinWidth(jk);
    if( RMS_l >= xl && RMS_l <= xr )  bin_mean3rms_l = jk;
    if( RMS_r >= xl && RMS_r <= xr )  bin_mean3rms_r = jk;
  }

  //3. set new range and calculate rms & mean
  h->GetXaxis()->SetRange(bin_mean3rms_l, bin_mean3rms_r);

  double new_rms = h->GetRMS();
  double new_mean = h->GetMean();

  // cout<<"Bin "<<i<<"Mean " << mean <<" Bin "<<bin_mean<<" / "<< n <<" RMS "<<rms<<" <>-3s "<<RMS_l<<" bin "<< bin_mean3rms_l <<" <>+3s "<<RMS_r
  //     <<" bin "<<bin_mean3rms_r<<" ("
  //     <<(bin_mean3rms_r-bin_mean3rms_l)/(float)n*100<<" %)"<<endl;
  // cout<<"\tMean "<<new_mean<<" rms "<<new_rms<<endl;

  //set points now
  double x = (x1+x2)/2.;
  double dx1 = fabs(x-x1);
  double dx2 = fabs(x-x2);
  double y = new_rms;
  double drms = h->GetRMSError();
  double Dy = drms;

  if(j < 0 ) bin = i; else bin = j;

  cout<<"\t Bin "<<bin<<"  pT "<<x1<<"-"<<x2<<"  RMS(pm 3sigma) "<<y<<" +- "<<Dy<<endl;
  
  g->SetPoint(bin, x, y);
  g->SetPointError(bin, dx1, dx2, Dy, Dy);

  i++;
}
//---------------------------------------------------------------------------------------------------------------
TH1D *H(TFile *f, const string &s){

  TH1D *h = (TH1D*)f->Get( s.c_str() );

  if(!h){
    cerr<<s<<": unable to obtain it from file, returning an empty histo "<<endl;
    return GetRef(s);
  }else {
    cout<<s<<": OK"<<endl;
  }

  return h;
}
//---------------------------------------------------------------------------------------------------------------
TH1D *J(TFile *f, vector<double> &v, const string &s){

  TH1D *h = (TH1D*)f->Get( s.c_str() );

  if(!h){
    cerr<<s<<": unable to obtain it from file, returning an empty histo "<<endl;
    return GetRef(s);
  }else {
    cout<<s<<": OK"<<endl;
  }

  if(h){
    int n = h->GetMaximumBin();
    v.push_back(  h->GetBinContent(n) );
  }

  return h;
}
//---------------------------------------------------------------------------------------------------------------
TCanvas *C(){

  return C(950, 800);

}

TCanvas *C(double w, double h){

  static int j;
  string name = "canvas"+GetStringFromInt(j++);

  TCanvas *c =  new TCanvas(name.c_str(), "", 20,20, w, h);
  //c->Range(0,0,1,1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetRightMargin(0.025);
  c->SetLeftMargin(0.12);
  c->SetTopMargin(0.04);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  return c;
}

TH1D *G(const string &s){
  static int i;
  string name = "histo"+GetStringFromInt(i++);
  int n_pt = 200; double l_pt = 0; double r_pt = 200;

  if(s=="pt") return new TH1D(name.c_str(),"", n_pt, l_pt, r_pt);

  return NULL;
}

bool Has(const string &str, const string &sub){

  std::size_t found = str.find(sub);

  if (found!=std::string::npos) return true;

  return false;
}

string GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }


void N(vector<double> &v, TH1 *h){

  h->Scale( 1./h->Integral() );

  if(h){
    int n = h->GetMaximumBin();
    v.push_back(  h->GetBinContent(n) );
  }

}

TLegend *L(double x1, double y1, double x2, double y2){

  TLegend *leg = new TLegend(x1,y1,x2,y2, NULL,"brNDC");
  leg->SetBorderSize(1);
  leg->SetLineColor(15);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(19);
  leg->SetFillStyle(3004);

  return leg;
}

string PT(int i){

  return GetStringFromInt( arrPt[i] ) + "_" + GetStringFromInt( arrPt[i+1]) + "_";

}

string pt(int i){

  return GetStringFromInt( arrPt[i] ) + "-" + GetStringFromInt( arrPt[i+1]);

}


TGraphAsymmErrors *NoErrorBars(TGraphAsymmErrors *g){

  TGraphAsymmErrors *gn = new TGraphAsymmErrors();

  int n = g->GetN();
  double x,y;
  for(int i = 1; i<= n; i++){
    g->GetPoint(i, x, y);
    gn->SetPoint(i, x, y);
  }

  return  n ? gn : NULL;

}
void RemoveEmptyPoints(TGraphAsymmErrors *g){

  double _x; double _y;
  for(int i = 1; i<= g->GetN(); i++){
    g->GetPoint(i, _x, _y);
    if(!_y || _y < 1e-5) g->RemovePoint(i);
  }

}

void RemoveZeroPoint(TGraphAsymmErrors *g){
  if(g->GetN() ) g->RemovePoint(0);
}

TGraphAsymmErrors *CopyG(TGraphAsymmErrors *g){

  int n = g->GetN();
  cout<<"copying graph with "<<n<<" points..."<<endl;

  TGraphAsymmErrors *gn = new TGraphAsymmErrors();

  double x,y;
  for(int i = 1; i<= n; i++){
    g->GetPoint(i, x, y);
    gn->SetPoint(i, x, y);
    gn->SetPointEXlow(i, g->GetErrorXlow(i) );
    gn->SetPointEXhigh(i, g->GetErrorXhigh(i) );
    gn->SetPointEYlow(i, g->GetErrorYlow(i) );
    gn->SetPointEYhigh(i, g->GetErrorYhigh(i) );

  }

  //gn->Print("all");

  return  gn->GetN() ? gn : NULL;

}

double GetMinBinCont(TGraphAsymmErrors *g){
  int n = g->GetN();
  double Y(1e6); double y; double x;
  for(int i = 1; i<= n; i++){
    g->GetPoint(i, x, y);
    if( y < Y && y > 1e-4 ) Y = y;
  }

  return Y;
}

double GetMaxBinCont(TGraphAsymmErrors *g){
  int n = g->GetN();
  double Y(0); double y; double x;
  for(int i = 1; i<= n; i++){
    g->GetPoint(i, x, y);
    if( y > Y) Y = y;
  }

  return Y;
}

TLatex *DrawAtlas(double x, double y){

  TLatex *t = new TLatex(x,y, "#color[12]{#font[72]{ATLAS} #font[42]{Work in Progress}}");
  t->SetTextSize( t->GetTextSize() * 0.8);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLatex *DrawAlgo(double x, double y){

  TLatex *t = new TLatex( x,y, "#color[36]{#font[42]{PanTau} + #font[52]{Cell-Based}}");
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLatex *DrawInfo(double x, double y, const string &s){

  TString text = "#font[42]{"+s+"}";
  TLatex *t = new TLatex( x,y, text );
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}


TLatex *DrawMC(double x, double y){

  TLatex *t = new TLatex( x,y, "#color[12]{#font[42]{MC12 Pythia8} #font[52]{Z^{0} #rightarrow #tau^{+}#tau^{-}}}");
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

