#include <string>
#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

using namespace std;

TLatex *DrawAlgo(double x, double y);
TLatex *DrawAtlas(double x, double y);
TLatex *DrawMC(double x, double y);
TLatex *DrawInfo(double x, double y, const string &s);

void Norm(TH1D*);
void Plot_PanTauVsTauRec(int ch){

  string dir = "../results/";
  string hn0; string hn1; string hn2; string hn3; 
  string header;
  string fn0; string fn1; string fn2; string fn3;
  string e0;   string e1; string e2; string e3;
  bool k0(false); bool k1(false); bool k2(false); bool k3(false);
  string info; double maxY1; double maxY3;

  double legx0 = 0.125;
  double legy0 = 0.7;
  double legx1 = 0.45;
  double legy1=  0.95;
  double xl = 0.52;

  double offset1 = 1.4;
  double offset3 = 1.3;

  string dest = "/home/zenon/TauSubstructureSupNote/COM/trunk/figs/resolution/";
  string outname;


  if(ch == 0){
    //fn0 = "../results/V59/tau4mom.root"; info = "no Jet-Sig BDT"; maxY1 = 0.2; maxY3 = 0.25; outname = "resolution_PanTauCellBased_tauRec_1p_3p_noJetSigBDT";
    fn0 = "../results/V58/tau4mom.root"; info = "Jet-Sig BDT medium"; maxY1 = 0.2; maxY3 = 0.4; outname = "resolution_PanTauCellBased_tauRec_1p_3p_JetSigBDTm";

    header = "p_{T}^{reco} > 15 GeV";
    /*    hn0 = "tau_pan_1p_true_1p_reso_rel"; e0 = "PanTau r1p-t1p";
    hn1 = "tau_pan_3p_true_3p_reso_rel"; e1 = "PanTau r3p-t3p";
    hn2 = "tau_rec_1p_true_1p_reso_rel"; e2 = "tauRec r1p-t1p";
    hn3 = "tau_rec_3p_true_3p_reso_rel"; e3 = "tauRec r3p-t3p";
    */
    hn0 = "tau_pan_1p_reso_rel"; e0 = "PanTau r1p";
    hn1 = "tau_pan_3p_reso_rel"; e1 = "PanTau r3p";
    hn2 = "tau_rec_1p_reso_rel"; e2 = "tauRec r1p";
    hn3 = "tau_rec_3p_reso_rel"; e3 = "tauRec r3p";

  }

  if(ch == 1){
    fn0 = "../results/V59/tau4mom.root"; info = "no Jet-Sig BDT";
    header = "p_{T}^{reco} > 15 GeV";
    hn0 = "tau_pan_incl_reso_rel"; e0 = "PanTau + Cell-based";
    hn1 = "tau_pan_incl_reso_rel"; e1 = "tauRec";

  }

  if(fn0.size()) {k0 = true; k1 = true; k2 = true; k3 = true;}

  TFile *f0 = k0 ? TFile::Open( (dir+fn0).c_str() ) : 0; if(!f0){ cout<<"Cannot get file 0"<<endl; return;}


  TH1D *h0 = (TH1D*)(k0 ? f0->Get( hn0.c_str() ) : 0); if(!h0){ cout<<"Cannot get histo 0"<<endl; return;}
  TH1D *h1 = (TH1D*)(k1 ? f0->Get( hn1.c_str() ) : 0); if(!h1){ cout<<"Cannot get histo 1"<<endl; return;}
  TH1D *h2 = (TH1D*)(k2 ? f0->Get( hn2.c_str() ) : 0); if(!h2){ cout<<"Cannot get histo 2"<<endl; return;}
  TH1D *h3 = (TH1D*)(k3 ? f0->Get( hn3.c_str() ) : 0); if(!h3){ cout<<"Cannot get histo 3"<<endl; return;}

  if(k0) cout<< h0->GetEntries() <<endl;
  if(k1) cout<< h1->GetEntries() <<endl;
  if(k2) cout<< h2->GetEntries() <<endl;
  if(k3) cout<< h3->GetEntries() <<endl;

  if(k0) Norm(h0);
  if(k1) Norm(h1);
  if(k2) Norm(h2);
  if(k3) Norm(h3);

  if(k0) {h0->SetLineWidth(2); h0->SetLineColor(kGreen);  }
  if(k1) {h1->SetLineWidth(2); h1->SetLineColor(kGreen); }
  if(k2) {h2->SetLineWidth(2); h2->SetLineColor(kBlack); h2->SetLineStyle(7); }
  if(k3) {h3->SetLineWidth(2); h3->SetLineColor(kBlack); h3->SetLineStyle(7); }


  TCanvas *c = new TCanvas("c", "", 20, 20, 1300, 600);
  c->Divide(2,1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetRightMargin(0.025);
  c->SetLeftMargin(0.1);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);
  c->cd();


  c->cd(1);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  gPad->SetTopMargin(0.015);
  if(k2) h2->Draw();
  if(k0) h0->Draw("same");
  h2->SetMaximum(maxY1);
  h2->GetYaxis()->SetTitle("normalized to unit area");
  h2->GetYaxis()->SetTitleOffset(   h2->GetYaxis()->GetTitleOffset()*offset1 );

  TLegend *leg = new TLegend( legx0, legy0, legx1, legy1, NULL,"brNDC");
  leg->SetBorderSize(1);
  leg->SetLineColor(15);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(19);
  leg->SetFillStyle(3004);
  if(!header.empty()) leg->SetHeader(header.c_str());
  if(k0) leg->AddEntry(h0, e0.c_str(), "l");
  if(k2) leg->AddEntry(h2, e2.c_str(), "l");
  leg->Draw();

  DrawAtlas(xl, 0.9)->Draw();
  DrawAlgo(xl, 0.84)->Draw();
  DrawMC(xl, 0.78)->Draw();
  DrawInfo(xl, 0.72, info)->Draw();

  //===========================================

  c->cd(2);
  gPad->SetTickx(1);
  gPad->SetTicky(1);
  gPad->SetTopMargin(0.015);

  if(k3) h3->Draw();
  if(k1) h1->Draw("same");
  h3->SetMaximum(maxY3);

  h3->GetYaxis()->SetTitle("normalized to unit area");
  h3->GetYaxis()->SetTitleOffset(   h2->GetYaxis()->GetTitleOffset()*offset3 );

  TLegend *leg0 = new TLegend( legx0, legy0, legx1, legy1, NULL,"brNDC");
  leg0->SetBorderSize(1);
  leg0->SetLineColor(15);
  leg0->SetLineStyle(1);
  leg0->SetLineWidth(1);
  leg0->SetFillColor(19);
  leg0->SetFillStyle(3004);
  if(!header.empty()) leg0->SetHeader(header.c_str());
  if(k1) leg0->AddEntry(h1, e1.c_str(), "l");
  if(k3) leg0->AddEntry(h3, e3.c_str(), "l");
  leg0->Draw();

  DrawAtlas(xl, 0.9)->Draw();
  DrawAlgo(xl, 0.84)->Draw();
  DrawMC(xl, 0.78)->Draw();
  DrawInfo(xl, 0.72, info)->Draw();

  //gPad->SetLogy();

  c->SaveAs( (dest+outname+".eps").c_str() );

}

void Norm(TH1D *h){

  double s = h->Integral();

  h->Scale(1./s);

}

TLatex *DrawAtlas(double x, double y){

  TLatex *t = new TLatex(x,y, "#color[12]{#font[72]{ATLAS} #font[42]{Work in Progress}}");
  t->SetTextSize( t->GetTextSize() * 0.7);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLatex *DrawAlgo(double x, double y){

  TLatex *t = new TLatex( x,y, "#color[36]{#font[42]{PanTau} + #font[52]{Cell-Based}}");
  t->SetTextSize( t->GetTextSize() * 0.65);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLatex *DrawInfo(double x, double y, const string &s){

  TString text = "#font[42]{"+s+"}";
  TLatex *t = new TLatex( x,y, text );
  t->SetTextSize( t->GetTextSize() * 0.65);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}


TLatex *DrawMC(double x, double y){

  TLatex *t = new TLatex( x,y, "#color[12]{#font[42]{MC12 Pythia8} #font[52]{Z^{0}, Z' #rightarrow #tau^{+}#tau^{-}}}");
  t->SetTextSize( t->GetTextSize() * 0.65);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

