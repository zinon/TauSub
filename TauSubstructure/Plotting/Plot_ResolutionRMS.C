/*



 */
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

void Plot_ResolutionRMS();
TGraphAsymmErrors *GetPtResGraph(int, TFile *f,  const string&Algo, const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v);
bool SetGraphStyle(int , TGraphAsymmErrors *g, TGraphAsymmErrors *gn, Color_t co, int ms);
TCanvas *C();
TCanvas *C(double w, double h);
TGraphAsymmErrors *NoErrorBars(TGraphAsymmErrors *g);
void RemoveZeroPoint(TGraphAsymmErrors *g);
void RemoveEmptyPoints(TGraphAsymmErrors *g);
TLegend *L(double x1, double y1, double x2, double y2);
string RANGE(int i);
TLatex *DrawAlgo(double x, double y);
TLatex *DrawAtlas(double x, double y);
TLatex *DrawMC1(double x, double y);
TLatex *DrawMC2(double x, double y);
TLatex *DrawInfo(double x, double y, const string &s);
TGraphAsymmErrors *CopyG(int, TGraphAsymmErrors *g);
TH1D *J(TFile *f, vector<double> &v, const string &s);
void SetP(int bin, int type, TGraphAsymmErrors *g, TH1D *h, double x1, double x2);
void Set(int bin, int type, TGraphAsymmErrors *g, TH1D *h, double x1, double x2);
void Set0(int j, TGraphAsymmErrors *g, TH1D *h, double x1, double x2);
void Set1(int j, TGraphAsymmErrors *g, TH1D *h, double x1, double x2);
void Set2(int j, TGraphAsymmErrors *g, TH1D *H, double x1, double x2);
void Set3(int j, TGraphAsymmErrors *g, const TH1D *H, const double x1, const double x2);
TH1D *GetRef(const string &s);
string GetStringFromInt(int n);
string GetStringFromDouble(double x);

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))


bool kC = 0;
bool kEPS = 0;
bool kPNG = 1;
double maxY = 0.25;
double bin_minX = 3;
double bin_maxX = 15;
bool isBDT = false;
double minYtoBeRemoved = 0;

bool K0(1), K1(1), K2(1), K3(1), K4(1), K5(1), K6(1), K7(1), K8(1), K9(1), K10(1), K11(1), K12(1), K13(1), K14(1), K15(1), K16(1);

double const arrayVAR[] = {0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 250, 350, 500, 750, 1000}; int const Narray = NELEMS(arrayVAR); K0 = 0; K1 = 0; K2 = 0; minYtoBeRemoved = 1e-6;

//const double arrayVAR[] = {0.0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0}; int const Narray = NELEMS(arrayVAR); isBDT = true; bin_minX = 0; bin_maxX = 6; maxY = 0.45; minYtoBeRemoved = 1e-2;
string BDTpTbin = "4";

bool verbose = 1;

int xmsz = 2;// times x marker size
//================================================================================
void Plot_ResolutionRMS(){
  string dir; 
  string fn = "tau4mom.root";
  string info(""); string fname("resolution_vs");
  string rmode; string tmode; string res; string lat; double minY;
  string fdir = "/home/zenon/TauSubstructureSupNote/COM/trunk/figs/resolution/";
  string pdir = "results/resolution_curves/Nov10/";
  string cdir = pdir;
  string BDTpTbin_str = BDTpTbin == "1" ? "pT<20GeV" : 
    BDTpTbin == "2" ? "20<pT<40 GeV" : 
    BDTpTbin == "3" ? "40<pT<80 GeV" : 
    BDTpTbin == "4" ? "pT>80 GeV" : 
    "don't know";
  string BDTpTbin_fstr = BDTpTbin == "1" ? "pT_20GeV" : 
    BDTpTbin == "2" ? "20_pT_40GeV" : 
    BDTpTbin == "3" ? "40_pT_80GeV" : 
    BDTpTbin == "4" ? "pT_80_GeV" : 
    "don't know";

  if(isBDT){
    fname+="_BDTscore_ptBin_"+BDTpTbin_fstr;
  }
  else fname+="_truth_pT";
 
  res = "reso_rel"; // "reso_std" "reso_rel";

  dir = "../results/V75/"; info = "No Jet/Sig BDT"; fname+="_BDTnone";
  //dir = "../results/V76/"; info = "Jet/Sig BDT medium"; fname+="_BDTmedium";
  //dir = "../results/V77/"; info = "No Jet/Sig BDT"; fname+="_BDTnone_r1p0nCompatRatio";

  bool kOverlay = 0;
  string overlayF = cdir + "resolution_vs_truth_pT_BDTnone_r1p0nCompatRatio_method_RMS_PanTau_r1p_r3p.root";
  string overlayG = "g5"; 
  string overlayFlag = "_no_yes_r1p0n_compRatio_";
  string tlegG = "with r1p0n R cut";
  Color_t colG = kRed;
  TGraphAsymmErrors *gover;
  if(kOverlay){
    TFile *fo = TFile::Open(overlayF.c_str());
    if(!fo){cerr<<"Cannot open "<<overlayF<<endl; return;}
    gover = (TGraphAsymmErrors *)fo->Get(overlayG.c_str());
    if(!gover){cerr<<"Cannot retrieve "<<overlayG<<" from "<<overlayF<<endl; return;}
    kC= 0; //do not store
    fname+="_overlay_"+overlayFlag;
    maxY = 0.3;
  }

  TFile *f = new TFile((dir+fn).c_str());  if(!f || f->IsZombie() ){cerr<<"unable to open file "<<fn<<endl; return;}

  bool withTauRec = 1; 
  bool kNorm = 1;
  int ResType = 0; //0: RMS,  1: RMS/Mean,   2: RMS/Mean modified in +-3sigma around Mean,   3: RMS modified in +-3sigma around Mean
  
  if(ResType == 0) fname+="_method_RMS"; else if(ResType == 3) fname+="_method_3sigmaRMS";


  string algo0; string rmode0; string tmode0; string tleg0;  Color_t col0; int ms0; vector<double> v0; bool show0;
  string algo1; string rmode1; string tmode1; string tleg1;  Color_t col1; int ms1; vector<double> v1; bool show1;
  string algo2; string rmode2; string tmode2; string tleg2;  Color_t col2; int ms2; vector<double> v2; bool show2;
  string algo3; string rmode3; string tmode3; string tleg3;  Color_t col3; int ms3; vector<double> v3; bool show3;
  string algo4; string rmode4; string tmode4; string tleg4;  Color_t col4; int ms4; vector<double> v4; bool show4;
  string algo5; string rmode5; string tmode5; string tleg5;  Color_t col5; int ms5; vector<double> v5; bool show5;
  string algo6; string rmode6; string tmode6; string tleg6;  Color_t col6; int ms6; vector<double> v6; bool show6;
  string algo7; string rmode7; string tmode7; string tleg7;  Color_t col7; int ms7; vector<double> v7; bool show7;
  string algo8; string rmode8; string tmode8; string tleg8;  Color_t col8; int ms8; vector<double> v8; bool show8;

  if(withTauRec){
    minY = 0.05;

    show0 = 0; algo0 = "rec"; rmode0 = "1p"; tmode0 = ""; tleg0 = "#font[62]{r}1p tauRec"; col0 = kGreen; ms0 = 20;
    show1 = 0; algo1 = "rec"; rmode1 = "3p"; tmode1 = ""; tleg1 = "#font[62]{r}3p tauRec"; col1 = kRed; ms1 = 20;
    show2 = 1; algo2 = "rec"; rmode2 = "1p"; tmode2 = "1p"; tleg2 = "#font[62]{r}1p - #font[62]{t}1p tauRec"; col2 = kGreen; ms2 = 20;
    show3 = 1; algo3 = "rec"; rmode3 = "3p"; tmode3 = "3p"; tleg3 = "#font[62]{r}3p - #font[62]{t}3p tauRec"; col3 = kRed; ms3 = 20;

    show4 = 1; algo4 = "pan"; rmode4 = "1p"; tmode4 = ""; tleg4 = "#font[62]{r}1p PanTau+CellBased"; col4 = kBlack; ms4 = 24;
    show5 = 1; algo5 = "pan"; rmode5 = "3p"; tmode5 = ""; tleg5 = "#font[62]{r}3p PanTau+CellBased"; col5 = kMagenta; ms5 = 24;
    show6 = 0; algo6 = "pan"; rmode6 = "1p"; tmode6 = "1p"; tleg6 = "#font[62]{r}1p - #font[62]{t}1p PanTau+CellBased"; col6 = kBlack; ms6 = 24;
    show7 = 0; algo7 = "pan"; rmode7 = "3p"; tmode7 = "3p"; tleg7 = "#font[62]{r}3p - #font[62]{t}3p PanTau+CellBased"; col7 = kMagenta; ms7 = 24;

    fname+="_tauRec";
    if(show0) fname+="_r1p";
    if(show1) fname+="_r3p";
    if(show2) fname+="_r1pt1p";
    if(show3) fname+="_r3pt3p";

    fname+="_PanTau";
    if(show4) fname+="_r1p";
    if(show5) fname+="_r3p";
    if(show6) fname+="_r1pt1p";
    if(show7) fname+="_r3pt3p";

  }else{

    minY = 0.02;

    show0 = 1; algo0 = "pan"; rmode0 = "1p0n"; tmode0 = ""; tleg0 = "#font[62]{r}1p0n PanTau+CellBased"; col0 = kRed; ms0 = 20;
    show1 = 1; algo1 = "pan"; rmode1 = "1p1n"; tmode1 = ""; tleg1 = "#font[62]{r}1p1n PanTau+CellBased"; col1 = kGray; ms1 = 20;
    show2 = 1; algo2 = "pan"; rmode2 = "1pXn"; tmode2 = ""; tleg2 = "#font[62]{r}1pXn PanTau+CellBased"; col2 = kOrange; ms2 = 20;
    show3 = 1; algo3 = "pan"; rmode3 = "3p0n"; tmode3 = ""; tleg3 = "#font[62]{r}3p0n PanTau+CellBased"; col3 = kAzure; ms3 = 24;
    show4 = 1; algo4 = "pan"; rmode4 = "3pXn"; tmode4 = ""; tleg4 = "#font[62]{r}3pXn PanTau+CellBased"; col4 = kMagenta; ms4 = 24;

    show5 = 0; algo5 = "pan"; rmode5 = "1p"; tmode5 = ""; tleg5 = "#font[62]{r}1p PanTau+CellBased"; col5 = kGreen; ms5 = 20;
    show6 = 0; algo6 = "pan"; rmode6 = "3p"; tmode6 = ""; tleg6 = "#font[62]{r}3p PanTau+CellBased"; col6 = kBlack; ms6 = 24;

    show7 = 0; algo7 = "pan"; rmode7 = "1p"; tmode7 = "1p"; tleg7 = " #font[62]{r}1p - #font[62]{t}1p PanTau+CellBased"; col7 = kViolet; ms7 = 24;
    show8 = 0; algo8 = "pan"; rmode8 = "1p"; tmode8 = "3p"; tleg8 = " #font[62]{r}1p - #font[62]{t}3p PanTau+CellBased"; col8 = kGreen; ms8 = 24;

    fname+="_PanTau";
    if(show0) fname+="_r1p0n";
    if(show1) fname+="_r1p1n";
    if(show2) fname+="_r1pXn";
    if(show3) fname+="_r3p0n";
    if(show4) fname+="_r3pXn";
    if(show5) fname+="_r1p";
    if(show6) fname+="_r3p";
    if(show7) fname+="_r1pt1p";
    if(show8) fname+="_r1pt3p";

  }



  TGraphAsymmErrors *g0 = show0 ? GetPtResGraph(0, f, algo0, rmode0, tmode0, res, ResType, v0) : 0;
  TGraphAsymmErrors *g0n =  show0 ? CopyG(0, g0) : 0;
  bool k0 = SetGraphStyle(0, g0, g0n, col0, ms0);

  TGraphAsymmErrors *g1 = show1 ?GetPtResGraph(1, f, algo1, rmode1, tmode1, res, ResType, v1) : 0;
  TGraphAsymmErrors *g1n =  show1 ? CopyG(1, g1) : 0;
  bool k1 = SetGraphStyle(1, g1, g1n, col1, ms1);

  TGraphAsymmErrors *g2 = show2 ?GetPtResGraph(2, f, algo2, rmode2, tmode2, res, ResType, v2) : 0;
  TGraphAsymmErrors *g2n =  show2 ?CopyG(2, g2) : 0;
  bool k2 = SetGraphStyle(2, g2, g2n, col2, ms2);

  TGraphAsymmErrors *g3 = show3 ? GetPtResGraph(3, f, algo3, rmode3, tmode3, res, ResType, v3) : 0;
  TGraphAsymmErrors *g3n =  show3 ? CopyG(3, g3):0;
  bool k3 = SetGraphStyle(3, g3, g3n, col3, ms3);

  TGraphAsymmErrors *g4 = show4 ? GetPtResGraph(4, f, algo4, rmode4, tmode4, res, ResType, v4) : 0;
  TGraphAsymmErrors *g4n =  show4 ? CopyG(4, g4):0;
  bool k4 = SetGraphStyle(4, g4, g4n, col4, ms4);

  TGraphAsymmErrors *g5 =  show5 ? GetPtResGraph(5, f, algo5, rmode5, tmode5, res, ResType, v5) : 0; 
  TGraphAsymmErrors *g5n =  show5 ? CopyG(5, g5) : 0;
  bool k5 = SetGraphStyle(5, g5, g5n, col5, ms5);

  TGraphAsymmErrors *g6 = show6 ? GetPtResGraph(6, f, algo6, rmode6, tmode6, res, ResType, v6) : 0;
  TGraphAsymmErrors *g6n =  show6 ? CopyG(6, g6) : 0;
  bool k6 = SetGraphStyle(6, g6, g6n, col6, ms6);

  TGraphAsymmErrors *g7 = show7 ?GetPtResGraph(7, f, algo7, rmode7, tmode7, res, ResType, v7) : 0;
  TGraphAsymmErrors *g7n =  show7 ?CopyG(7, g7) : 0;
  bool k7 = SetGraphStyle(7, g7, g7n, col7, ms7);

  TGraphAsymmErrors *g8 = show8 ?GetPtResGraph(8, f, algo8, rmode8, tmode8, res, ResType, v8) : 0;
  TGraphAsymmErrors *g8n =  show8 ?CopyG(8, g8) : 0;
  bool k8 = SetGraphStyle(8, g8, g8n, col8, ms8);

  TCanvas *c = C(1000, 600);
  c->cd();
  TH1D *hb = new TH1D("hb", "", Narray-1, arrayVAR);
  hb->Draw();
  hb->SetMinimum(minY);
  hb->SetMaximum(maxY);
  //hb->GetXaxis()->SetRangeUser(minX, maxX);
  hb->GetXaxis()->SetRange(bin_minX, bin_maxX);
  if(res=="reso_std"){ hb->GetYaxis()->SetTitle("#sigma[ p_{T}^{reco}/p_{T}^{vis-true} ]"); }
  if(res=="reso_rel"){ hb->GetYaxis()->SetTitle("#sigma[ (p_{T}^{reco} - p_{T}^{vis-true})/p_{T}^{vis-true} ]"); }

  if(isBDT)
    hb->GetXaxis()->SetTitle("Jet/Tau BDT score");
  else
     hb->GetXaxis()->SetTitle("p_{T}^{vis-true} [GeV]");

  hb->GetYaxis()->SetTitleOffset( hb->GetYaxis()->GetTitleOffset() *1.3 );
  hb->GetXaxis()->SetTitleOffset( hb->GetXaxis()->GetTitleOffset() *1.1 );

  hb->GetYaxis()->SetTitleSize( hb->GetYaxis()->GetTitleSize() *1.2 );

  if(show0) if(k0){
      cout<<"plotting graph 0"<<endl;
      g0n->Draw("L S Z");
      g0->Draw("P Z");
    }

  if(show1) if(k1){
      cout<<"plotting graph 1"<<endl;
      g1n->Draw("L Z S");
      g1->Draw("P Z");
    }

  if(show2) if(k2){
      cout<<"plotting graph 2"<<endl;
      g2n->Draw("L Z S");
      g2->Draw("P Z");
    }

  if(show3) if(k3){
      cout<<"plotting graph 3"<<endl;
      g3n->Draw("L Z S");
      g3->Draw("P Z");
    }

  if(show4) if(k4){
      cout<<"plotting graph 4"<<endl;
      g4n->Draw("L Z S");
      g4->Draw("P Z");
    }

  if(show5) if(k5){
      cout<<"plotting graph 5"<<endl;
      g5n->Draw("L Z S");
      g5->Draw("P Z");
    }

  if(show6) if(k6){
      cout<<"plotting graph 6"<<endl;
      g6n->Draw("L Z S");
      g6->Draw("P Z");
    }

  if(show7) if(k7){
      cout<<"plotting graph 7"<<endl;
      g7n->Draw("L Z S");
      g7->Draw("P Z");
    }

  if(show8) if(k8){
      cout<<"plotting graph 8"<<endl;
      g8n->Draw("L Z S");
      g8->Draw("P Z");
    }

  if(kOverlay){
    gover->SetLineColor(colG);
    gover->SetMarkerColor(colG);
    gover->Draw("p z"); 
  }

  TLatex *tex = new TLatex(0.1, 0.7, lat.c_str() ); tex->SetNDC(); tex->SetTextFont(44); tex->Draw();

  TLegend *leg = L(0.65, 0.6, 0.94, 0.93);
  leg->SetHeader("Decay Mode");
  if(show0) if(k0) leg->AddEntry(g0n, tleg0.c_str(), "lp");
  if(show1) if(k1) leg->AddEntry(g1n, tleg1.c_str(), "lp");
  if(show2) if(k2) leg->AddEntry(g2n, tleg2.c_str(), "lp");
  if(show3) if(k3) leg->AddEntry(g3n, tleg3.c_str(), "lp");
  if(show4) if(k4) leg->AddEntry(g4n, tleg4.c_str(), "lp");
  if(show5) if(k5) leg->AddEntry(g5n, tleg5.c_str(), "lp");
  if(show6) if(k6) leg->AddEntry(g6n, tleg6.c_str(), "lp");
  if(show7) if(k7) leg->AddEntry(g7n, tleg7.c_str(), "lp");
  if(show8) if(k8) leg->AddEntry(g8n, tleg8.c_str(), "lp");

  leg->Draw();

  if(kOverlay) leg->AddEntry(gover, tlegG.c_str(), "lp");

  double xl = 0.2;
  DrawAtlas(xl, 0.9)->Draw();
  //DrawAlgo(xl, 0.84)->Draw();
  DrawMC1(xl, 0.84)->Draw();
  DrawMC2(xl, 0.78)->Draw();

  if(isBDT) info = "#splitline{"+info+"}{"+BDTpTbin_str+"}";
 
  DrawInfo(0.47, 0.9, info)->Draw();

  string eps =fname+".eps";
  string png =fname+".png";
  string root =fname+".root";

  string outC = pdir + root;
  string outeps = fdir + eps;
  string outpng = pdir + png;
 
  if(kC){
    cout<<"saving "<<outC<<" ..."<<endl; 
    TFile fc(outC.c_str(), "recreate"); 
    fc.cd(); 
    if(show0){ g0->Write("g0"); if(k0) g0n->Write("g0n"); }
    if(show1){ g1->Write("g1"); if(k1) g1n->Write("g1n"); }
    if(show2){ g2->Write("g2"); if(k2) g2n->Write("g2n"); }
    if(show3){ g3->Write("g3"); if(k3) g3n->Write("g3n"); }
    if(show4){ g4->Write("g4"); if(k4) g4n->Write("g4n"); }
    if(show5){ g5->Write("g5"); if(k5) g5n->Write("g5n"); }
    if(show6){ g6->Write("g6"); if(k6) g6n->Write("g6n"); }
    if(show7){ g7->Write("g7"); if(k7) g7n->Write("g7n"); }
    if(show8){ g8->Write("g8"); if(k8) g8n->Write("g8n"); }

    fc.Close();
  }
  if(kEPS){cout<<"saving "<<outeps<<" ..."<<endl; c->SaveAs(outeps.c_str()); }
  if(kPNG){cout<<"saving "<<outpng<<" ..."<<endl; c->SaveAs(outpng.c_str());}

}
//================================================================================
TLatex *DrawAtlas(double x, double y){

  TLatex *t = new TLatex(x,y, "#color[12]{#font[72]{ATLAS} #font[42]{Work in Progress}}");
  t->SetTextSize( t->GetTextSize() * 0.8);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}
//================================================================================
TLatex *DrawAlgo(double x, double y){

  TLatex *t = new TLatex( x,y, "#color[36]{#font[42]{PanTau} + #font[52]{Cell-Based}}");
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}
//================================================================================
TLatex *DrawInfo(double x, double y, const string &s){

  TString text = "#font[42]{"+s+"}";
  TLatex *t = new TLatex( x,y, text );
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}
//================================================================================
TLatex *DrawMC1(double x, double y){

  TLatex *t = new TLatex( x,y, "#color[12]{#font[42]{MC12 Pythia8}  #font[52]{Z^{0} #rightarrow #tau^{+}#tau^{-}}}");
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}
//================================================================================
TLatex *DrawMC2(double x, double y){

  TLatex *t = new TLatex( x,y, "#color[12]{#font[42]{MC12 Pythia8}  #font[52]{Z' #rightarrow #tau^{+}#tau^{-}}}");
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}
//================================================================================
bool SetGraphStyle(int i, TGraphAsymmErrors *g, TGraphAsymmErrors *gn, Color_t co, int ms){

  if( !g ){ cerr<<"SetGraphStyle - g null pointer for "<<i<<endl; return false; }
  if( !g->GetN()){ cerr<<"SetGraphStyle - g empty graph for "<<i<<endl; return false;}

  if( !gn ){ cerr<<"SetGraphStyle - gn null pointer for "<<i<<endl; return false; }
  if( !gn->GetN()){ cerr<<"SetGraphStyle - gn empty graph for "<<i<<endl; return false;}

  RemoveZeroPoint(g);
  RemoveZeroPoint(gn);
  NoErrorBars(gn);

  double x(0); double y(0);
 
  int n = g->GetN();
  for(i = 0; i < n ; i++){
    x = 0; y = 0;
    g->GetPoint(i, x, y);
    if(y< minYtoBeRemoved) {
      RemovePoint(g, i);
      RemovePoint(gn, i);
    }
  }

  g->SetLineColor(co);
  g->SetMarkerColor(co);
  g->SetMarkerStyle(ms);
  g->SetMarkerSize( g->GetMarkerSize() *xmsz);

  gn->SetLineColor(co);
  gn->SetLineStyle(7);
  gn->SetLineWidth(2);
  gn->SetMarkerStyle(ms);
  gn->SetMarkerColor(co);

  cout<<"N points g="<<g->GetN()<<" gn="<<gn->GetN()<<endl;

  return true;
}
//================================================================================
TGraphAsymmErrors *GetPtResGraph(int ic, TFile *f,  const string&Algo, const string &recmode, const string &truemode, const string &res, int ResType, vector<double> &v){

  cout<<"\nGetPtResGraph - case "<<ic<<" rec mode "<<recmode<<" true mode "<<truemode<<endl;

  string tmode; string rmode; string pTBin("");

  if(!recmode.size()) return 0;
  if(recmode.size()) rmode = Algo+"_"+recmode+"_";
  if(truemode.size()) tmode = "true_"+truemode+"_";

  if(isBDT) pTBin = "_pTbin"+BDTpTbin+"_";

  //templates:
  //  tau_pan_1p_BDT_0p70_0p80_pTbin5_reso_rel


  TGraphAsymmErrors *g = new TGraphAsymmErrors();

  //tau_pan_1p_20_25_true_1p_reso_rel
  TH1D * h0 = Narray>0 ? J(f, v, ("tau_" + rmode + RANGE(0) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h1 = Narray>1 ? J(f, v ,("tau_" + rmode + RANGE(1) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h2 = Narray>2 ? J(f, v, ("tau_" + rmode + RANGE(2) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h3 = Narray>3 ? J(f, v, ("tau_" + rmode + RANGE(3) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h4 = Narray>4 ? J(f, v, ("tau_" + rmode + RANGE(4) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h5 = Narray>5 ? J(f, v, ("tau_" + rmode + RANGE(5) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h6 = Narray>6 ? J(f, v, ("tau_" + rmode + RANGE(6) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h7 = Narray>7 ? J(f, v, ("tau_" + rmode + RANGE(7) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h8 = Narray>8 ? J(f, v, ("tau_" + rmode + RANGE(8) + pTBin + tmode + res).c_str()) : 0;
  TH1D * h9 = Narray>9 ? J(f, v, ("tau_" + rmode + RANGE(9) + pTBin + tmode + res).c_str()) : 0;
  TH1D *h10 = Narray>10 ? J(f, v, ("tau_" + rmode + RANGE(10)+ pTBin + tmode + res).c_str()) : 0;
  TH1D *h11 = Narray>11 ? J(f, v, ("tau_" + rmode + RANGE(11)+ pTBin + tmode + res).c_str()) : 0;
  TH1D *h12 = Narray>12 ? J(f, v, ("tau_" + rmode + RANGE(12)+ pTBin + tmode + res).c_str()) : 0;
  TH1D *h13 = Narray>13 ? J(f, v, ("tau_" + rmode + RANGE(13)+ pTBin + tmode + res).c_str()) : 0;
  TH1D *h14 = Narray>14 ? J(f, v, ("tau_" + rmode + RANGE(14)+ pTBin + tmode + res).c_str()) : 0;
  TH1D *h15 = Narray>15 ? J(f, v, ("tau_" + rmode + RANGE(15)+ pTBin + tmode + res).c_str()) : 0;
  TH1D *h16 = Narray>16 ? J(f, v, ("tau_" + rmode + RANGE(16)+ pTBin + tmode + res).c_str()) : 0;


  int i(1);
  if(K0) if(h0) SetP(i++,ResType, g, h0, arrayVAR[0], arrayVAR[1]);
  if(K1) if(h1) SetP(i++,ResType, g, h1, arrayVAR[1], arrayVAR[2]);
  if(K2) if(h2) SetP(i++,ResType, g, h2, arrayVAR[2], arrayVAR[3]);
  if(K3) if(h3) SetP(i++,ResType, g, h3, arrayVAR[3], arrayVAR[4]);
  if(K4) if(h4) SetP(i++,ResType, g, h4, arrayVAR[4], arrayVAR[5]);
  if(K5) if(h5) SetP(i++,ResType, g, h5, arrayVAR[5], arrayVAR[6]);
  if(K6) if(h6) SetP(i++,ResType, g, h6, arrayVAR[6], arrayVAR[7]);
  if(K7) if(h7) SetP(i++,ResType, g, h7, arrayVAR[7], arrayVAR[8]);
  if(K8) if(h8) SetP(i++,ResType, g, h8, arrayVAR[8], arrayVAR[9]);
  if(K9) if(h9) SetP(i++,ResType, g, h9, arrayVAR[9], arrayVAR[10]);
  if(K10) if(h10) SetP(i++,ResType, g, h10, arrayVAR[10], arrayVAR[11]);
  if(K11) if(h11) SetP(i++,ResType, g, h11, arrayVAR[11], arrayVAR[12]);
  if(K12) if(h12) SetP(i++,ResType, g, h12, arrayVAR[12], arrayVAR[13]);
  if(K13) if(h13) SetP(i++,ResType, g, h13, arrayVAR[13], arrayVAR[14]);
  if(K14) if(h14) SetP(i++,ResType, g, h14, arrayVAR[14], arrayVAR[15]);
  if(K15) if(h15) SetP(i++,ResType, g, h15, arrayVAR[15], arrayVAR[16]);
  if(K16) if(h16) SetP(i++,ResType, g, h16, arrayVAR[16], arrayVAR[17]);

  if(g) cout<<"GetPtResGraph - case "<<ic<<" OK! Integral:"<<g->Integral(0,-1)<<endl;

  cout<<ic<<" g pointer "<<g<<endl;

  return g;
}
//================================================================================
void SetP(int bin, int type, TGraphAsymmErrors *g, TH1D *h, double x1, double x2){

  Set(bin, type, g, h, x1, x2);
}
//================================================================================
void Set(int bin, int type, TGraphAsymmErrors *g, TH1D *h, double x1, double x2){

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
  if(verbose) cout<<"Set0 - Method RMS "<<endl;

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

  if(verbose) cout<<"Bin "<<bin<<"  pT "<<x1<<"-"<<x2<<"  StdDev "<<y<<" +- "<<Dy<<endl;

  g->SetPoint(bin, x, y);
  g->SetPointError(bin, dx1, dx2, dy, Dy);

  i++;
}
//================================================================================
void Set1(int j, TGraphAsymmErrors *g, TH1D *h, double x1, double x2){
  if(verbose) cout<<"Set1 - Method RMS/Mean "<<endl;
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

  if(verbose) cout<<"Bin "<<bin<<"  pT "<<x1<<"-"<<x2<<"  RMS/Mean "<<y<<" +- "<<Dy<<endl;

  g->SetPoint(bin, x, y);
  g->SetPointError(bin, dx1, dx2, Dy, Dy);

  i++;
}
//================================================================================
void Set2(int j, TGraphAsymmErrors *g, TH1D *H, double x1, double x2){
  if(verbose) cout<<"Set2 - Method RMS/Mean in 3sigma "<<endl;
  int bin;
  static int i(1);
  TString hcopy = TString::Itoa(i, 10);
  TH1D *h = (TH1D*)H->Clone( hcopy );

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

  if(verbose){
    cout<<"Bin "<<i<<"Mean " << mean <<" Bin "<<bin_mean<<" / "<< n <<" RMS "<<rms<<" <>-3s "<<RMS_l<<" bin "<< bin_mean3rms_l <<" <>+3s "<<RMS_r
        <<" bin "<<bin_mean3rms_r<<" ("
        <<(bin_mean3rms_r-bin_mean3rms_l)/(float)n*100<<" %)"<<endl;
    cout<<"\tMean "<<new_mean<<" rms "<<new_rms<<endl;
  }

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

  if(verbose) cout<<"\t Bin "<<bin<<"  pT "<<x1<<"-"<<x2<<"  RMS/Mean(pm 3sigma) "<<y<<" +- "<<Dy<<endl;

  g->SetPoint(bin, x, y);
  g->SetPointError(bin, dx1, dx2, Dy, Dy);

  i++;
}
//================================================================================
void Set3(int j, //static bin counter
          TGraphAsymmErrors *g, // output graph
          const TH1D *H, //input histogram
          const double x1, //bin lhs limit
          const double x2 //bin rhs limit
          ){

  if(verbose) cout<<"Set3 - Method RMS in 3sigma:  point "<<j<<endl;

  int bin;

  static int i(1);

  TH1D *h = (TH1D*)H->Clone( TString::Itoa(i, 10) );

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

  if(bin_mean == -1) {
    cerr<<"Set3 - bin mean not found "<<j<<endl;
  }

  double RMS_l = mean - 3 * rms;
  double RMS_r = mean + 3 * rms;

  if(verbose) cout<<" mean "<<mean<<" rms l "<<RMS_l<<"  rms r"<<RMS_r<<endl;

  //2. find bins with 3 x RMS left and right
  int bin_mean3rms_l(-1);
  int bin_mean3rms_r(-1);
  for(int jk = 0; jk < n; jk++ ){
    double xl = h->GetBinLowEdge(jk);
    double xr = xl + h->GetBinWidth(jk);
    if( RMS_l >= xl && RMS_l <= xr )  bin_mean3rms_l = jk;
    if( RMS_r >= xl && RMS_r <= xr )  bin_mean3rms_r = jk;
  }

  if(bin_mean3rms_l == -1) {
    cerr<<"Set3 - bin mean x 3rms left not found "<<j<<endl;
  }

  if(bin_mean3rms_r == -1) {
    cerr<<"Set3 - bin mean x 3rms right not found "<<j<<endl;
  }

  //3. set new range and recalculate rms & mean
  h->GetXaxis()->SetRange(bin_mean3rms_l, bin_mean3rms_r);

  double new_rms = h->GetRMS();
  double new_mean = h->GetMean();

  if(verbose){
    cout<<"Bin "<<i<<endl
        <<" Mean " << mean << " Bin mean " <<bin_mean<<" / "<< n<<endl
        <<" RMS "<<rms<<endl
        <<" -3s "<<RMS_l <<" bin "<< bin_mean3rms_l<<endl
        <<" +3s "<<RMS_r <<" bin "<< bin_mean3rms_r<<endl
        <<" ("<<(bin_mean3rms_r-bin_mean3rms_l)/(float)n*100<<" %)"<<endl;
    cout<<"\tNew Mean "<<new_mean<<" New Rms "<<new_rms<<endl;
  }

  //set points now
  double x = (x1+x2)/2.;
  double dx1 = fabs(x-x1);
  double dx2 = fabs(x-x2);
  double y = new_rms;
  double drms = h->GetRMSError();
  double Dy = drms;

  if(j < 0 ) bin = i; else bin = j;

  if(verbose) cout<<"\tBin "<<bin<<"  pT "<<x1<<" - "<<x2<<"  RMS(pm 3 sigma) "<<y<<" +- "<<Dy<<endl;

  g->SetPoint(bin, x, y);
  g->SetPointError(bin, dx1, dx2, Dy, Dy);

  i++;
}
//---------------------------------------------------------------------------------------------------------------
TH1D *J(TFile *f, vector<double> &v, const string &s){

  if(!f) {cerr<<"J: null pointer to file"<<endl; return 0;}

  TH1D *h = (TH1D*)f->Get( s.c_str() );

  if(!h){
    cerr<<s<<": unable to obtain it from file, returning an empty histo "<<endl;
    return GetRef(s);
  }else {
    cout<<s<<": OK , area "<<h->Integral()<<endl;
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
//---------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------
string GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }
//---------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------
void RemoveEmptyPoints(TGraphAsymmErrors *g){

  double _x; double _y;
  for(int i = 1; i<= g->GetN(); i++){
    g->GetPoint(i, _x, _y);
    if(!_y || _y < 1e-5) g->RemovePoint(i);
  }


}
//---------------------------------------------------------------------------------------------------------------
void RemoveZeroPoint(TGraphAsymmErrors *g){
  if(g->GetN() ) g->RemovePoint(0);
}
void RemovePoint(TGraphAsymmErrors *g, int i){
  if( i < g->GetN() ) g->RemovePoint(i);
}
//---------------------------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------------------------
string RANGE(int i){

  if(isBDT) return "BDT_"+GetStringFromDouble(arrayVAR[i]) + "_" + GetStringFromDouble(arrayVAR[i+1]);

  return GetStringFromInt( arrayVAR[i] ) + "_" + GetStringFromInt( arrayVAR[i+1]) + "_";

}
//---------------------------------------------------------------------------------------------------------------
string GetStringFromDouble(double x){

  char aa[50];
  sprintf(aa,"%.2f", x);

  //std::ostringstream stm; stm << n; 
  //string s = stm.str();

  string s(aa);

  TString S(s);
  S.ReplaceAll(".", "p");

  return S.Data();
}

//---------------------------------------------------------------------------------------------------------------
TGraphAsymmErrors *CopyG(int i, TGraphAsymmErrors *g) {

  if(!g) { cerr<<"CopyG - null pointer for "<<i<<endl; return NULL; }

  int n = g->GetN();

  cout<<"CopyG - copying graph "<<i<<" with "<<n<<" points..."<<endl;

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

  if(gn && gn->GetN()) cerr<<"CopyG - copy "<<i<<" is OK!"<<endl;

  return gn;

}
//---------------------------------------------------------------------------------------------------------------
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
