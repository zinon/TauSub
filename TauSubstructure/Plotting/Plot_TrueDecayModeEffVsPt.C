#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TString.h"
#include "TColor.h"

using namespace std;

TLatex *DrawAtlas(double x, double y);
TLatex *DrawAlgo(double x, double y);
TLatex *DrawInfo(double x, double y, const string &s);
TLatex *DrawMC(double x, double y);
TH1D *H(TFile *f, const string &s);
void EffBayes(int i, TGraphAsymmErrors *g, TH1D *hm, TH1D *hd, double x1, double x2);
TH1D *GetRef(const string &s);
double GetMaxBinCont(TGraphAsymmErrors *g);
double GetMinBinCont(TGraphAsymmErrors *g);
TGraphAsymmErrors *NoErrorBars(TGraphAsymmErrors *g);
string GetStringFromInt(int);
string PT(int i);
string pt(int i);
TCanvas *C();
TCanvas *C(double w, double h);
TLegend *L(double x1, double y1, double x2, double y2);

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

double const arrPt[] = {0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 250, 350, 500, 750, 1000};

int const NPt = NELEMS(arrPt);


void Plot_TrueDecayModeEffVsPt(){

  string dir; string fn; string info;string res; string mode; int ptRange_i; int ptRange_f; string tmode; bool do1p; bool do3p;

  dir = "../results/V58/";

  fn = "tau4mom.root";

  //info = "";
  info = "BDT Jet/Sig medium";


  TFile *f = new TFile((dir+fn).c_str());
  if(!f || f->IsZombie() ){cerr<<"unable to open file "<<fn<<endl; return;}

  do1p = 0;

  do3p = 1;

  if(do1p) tmode = "1p"; else tmode = "3p";

  bool kBayesDivide = 1;

  bool kOneMode = 0;

  bool kSetYaxisRange = 1;

  bool kIncludeOther = 0; //Other decay mode in the eff calculation

  mode = "1p0n";
  //mode = "1p1n";
  //mode = "1pXn";

  ptRange_i = 3; ptRange_f = 15;

  //res = "reso_std";
  res = "reso_rel";

  TGraphAsymmErrors *g = new TGraphAsymmErrors();
  TGraphAsymmErrors *r = new TGraphAsymmErrors();

  for(int i = ptRange_i; i <= ptRange_f; i++){

    if(kOneMode){
      TH1D * h  = GetRef(res);
      TH1D * t  = GetRef(res);
      TH1D * z  = GetRef(res);

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

      if(do1p){
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

      }//1p
      if(do3p){
        cout<<"all 3p modes "<<endl;

        TH1D * h00 = H(f, ("tau_pan_3p0n_"+PT(i)+"true_3p0n_"+res).c_str() );
        TH1D * h01 = H(f, ("tau_pan_3pXn_"+PT(i)+"true_3pXn_"+res).c_str() );
	//        TH1D * h02 = H(f, ("tau_pan_1pXn_"+PT(i)+"true_1pXn_"+res).c_str() );

        TH1D * h1 = H(f, ("tau_pan_1p0n_"+PT(i)+"true_3p0n_"+res).c_str() );
        TH1D * h2 = H(f, ("tau_pan_1p1n_"+PT(i)+"true_3p0n_"+res).c_str() );
        TH1D * h3 = H(f, ("tau_pan_1pXn_"+PT(i)+"true_3p0n_"+res).c_str() );
        TH1D * h4 = H(f, ("tau_pan_3pXn_"+PT(i)+"true_3p0n_"+res).c_str() );
        TH1D * h5 = H(f, ("tau_pan_other_"+PT(i)+"true_3p0n_"+res).c_str() );

        TH1D * u1 = H(f, ("tau_pan_1p0n_"+PT(i)+"true_3pXn_"+res).c_str() );
        TH1D * u2 = H(f, ("tau_pan_1p1n_"+PT(i)+"true_3pXn_"+res).c_str() );
        TH1D * u3 = H(f, ("tau_pan_1pXn_"+PT(i)+"true_3pXn_"+res).c_str() );
        TH1D * u4 = H(f, ("tau_pan_3p0n_"+PT(i)+"true_3pXn_"+res).c_str() );
        TH1D * u5 = H(f, ("tau_pan_other_"+PT(i)+"true_3pXn_"+res).c_str() );

        TH1D * t  =GetRef(res);
        if(h00) t->Add(h00);
        if(h01) t->Add(h01);
        //if(h02) t->Add(h02);

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

        /*if(q1) e->Add(q1);
        if(q2) e->Add(q2);
        if(q3) e->Add(q3);
        if(q4) e->Add(q4);
        if(kIncludeOther) if(q5) e->Add(q5);
	*/

        TH1D * w  =GetRef(res);
        if(t) w->Add(t);
        if(e) w->Add(e);

        if(t && w)  if( kBayesDivide ) EffBayes(i, g, w, t, arrPt[i], arrPt[i+1]); else Eff(i, g, w, t, arrPt[i], arrPt[i+1]);
        if(t && e)  if( kBayesDivide ) EffBayes(i, r, w, e, arrPt[i], arrPt[i+1]); else Eff(i, r, w, e, arrPt[i], arrPt[i+1]);

      }//3p

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
    l->SetHeader( ("All "+tmode+" True Decay Modes").c_str() );
  l->AddEntry(g, "classiffied", "pf");
  l->AddEntry(r, "misclassiffied", "pf");
  l->Draw();


  DrawAtlas(0.175, 0.9)->Draw();
  DrawAlgo(0.6, 0.9)->Draw();

  DrawMC(0.15, 0.44)->Draw();
  if(info.size()) DrawInfo(0.15, 0.38, info)->Draw();


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

  TLatex *t = new TLatex( x,y, "#color[12]{#font[42]{MC12 Pythia8} #font[52]{Z^{0}, Z' #rightarrow #tau^{+}#tau^{-}}}");
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

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

void EffBayes(int i, TGraphAsymmErrors *g, TH1D *hm, TH1D *hd, double x1, double x2){

  //cout<<i<<". Bayes Divide "<<endl;

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

double GetMaxBinCont(TGraphAsymmErrors *g){
  int n = g->GetN();
  double Y(0); double y; double x;
  for(int i = 1; i<= n; i++){
    g->GetPoint(i, x, y);
    if( y > Y) Y = y;
  }

  return Y;
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

string PT(int i){

  return GetStringFromInt( arrPt[i] ) + "_" + GetStringFromInt( arrPt[i+1]) + "_";

}

string pt(int i){

  return GetStringFromInt( arrPt[i] ) + "-" + GetStringFromInt( arrPt[i+1]);

}

string GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }

TCanvas *C(){

  return C(1000, 600);

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

double GetMinBinCont(TGraphAsymmErrors *g){
  int n = g->GetN();
  double Y(1e6); double y; double x;
  for(int i = 1; i<= n; i++){
    g->GetPoint(i, x, y);
    if( y < Y && y > 1e-4 ) Y = y;
  }

  return Y;
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
