#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TPad.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TLatex.h"

TH1D *H(TFile *, const string &);
TH1D *G(const string &);
string GetStringFromInt(int);
void N(TH1 *);
void NF(TH1 *, double);
double F(TH1 *, TH1 *);
double FP(TH1 *, TH1 *);
string  char2str(char *);
string NumString(double);
TCanvas *C();
TLegend *L(double x1, double y1, double x2, double y2);
TLatex *T(double x, double y, const string &);
void R(TH1D*h0);
bool Has(const string &str, const string &sub);
void P1(TFile*, const string &etaRange, const string &plotName);
void P2(TFile*, const string &etaRange, const string &plotName);
void P3(TFile*, const string &etaRange, const string &plotName);
void P4(TFile*, const string &etaRange, const string &plotName);
void P5(TFile*, const string &etaRange, const string &plotName);
void P6(TFile*, const string &etaRange, const string &plotName);
void P7(TFile*, const string &etaRange, const string &plotName);
void P8(TFile*, const string &etaRange, const string &plotName);
void P9(TFile*, const string &etaRange, const string &plotName);
void P10(TFile*, const string &etaRange, const string &plotName);
void P11(TFile*, const string &etaRange, const string &plotName);
void P12(TFile*, const string &etaRange, const string &plotName);
void P13(TFile*, const string &etaRange, const string &plotName);
void P14(TFile*, const string &etaRange, const string &plotName);
void P15(TFile*, const string &etaRange, const string &plotName);
void P16(TFile*, const string &etaRange, const string &plotName);
void P17(TFile*, const string &etaRange, const string &plotName);
void P18(TFile*, const string &etaRange, const string &plotName);
void P19(TFile*, const string &etaRange, const string &plotName);
void P19(TFile*, const string &etaRange, const string &plotName);
void P20(TFile*, const string &etaRange, const string &plotName);

void Save(TCanvas *, int, const string&);
void Loop(const string &fname, const string &etaRange, const string &plotName);

bool kStack = true;

double legx0 = 0.12;
double legy0 = 0.5;
double legx1 = 0.37;
double legy1= 0.93;
double label_x = kStack ? 0.65 : 0.65;
double label_y = 0.9;
double label_dy = 0.05;
int histo_lw = 2;
string outputformat = "png";
string dir = "plots/plots_23_06/";
string mc = "Pythia8 AU2CTEQ6L1 Z#rightarrow#tau^{+}#tau^{-}";
bool SaveHistos = true;


struct mpair_t {
  string file;
  string eta;
  string plot;

};

void Resolutions(){

  string dire = "../results/";

  vector<mpair_t> v;  mpair_t p;

  p.file="user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.BDTn.v38.140623213538.merge/user.zenon.016941._00025.merge.tau4mom.root"; p.eta = "#eta inclusive"; p.plot = "eta_incl";
  //p.file="user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.EtaIncl.v4.140303154010.merge/tau4mom.root"; p.eta = "#eta inclusive"; p.plot = "eta_incl";
  v.push_back(p);

  p.file="user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.Eta00_03.v4.140303155504.merge/user.zenon.015214._00025.merge.tau4mom.root"; p.eta = "0.0<|#eta|<0.3"; p.plot = "eta_00_03";
  // v.push_back(p);

  p.file="user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.Eta03_08.v4.140303155624.merge/user.zenon.015216._00020.merge.tau4mom.root"; p.eta = "0.3<|#eta|<0.8"; p.plot = "eta_03_08";
  //v.push_back(p);

  p.file="user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.Eta08_12.v4.140303155739.merge/user.zenon.015218._00025.merge.tau4mom.root"; p.eta = "0.8<|#eta|<1.2"; p.plot = "eta_08_12";
  //v.push_back(p);

  p.file="user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.Eta12_21.v4.140303160001.merge/user.zenon.015220._00025.merge.tau4mom.root"; p.eta = "1.2<|#eta|<2.1"; p.plot = "eta_12_21";
  //v.push_back(p);

  p.file="user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.Eta21_25.v4.140303160235.merge/user.zenon.015222._00020.merge.tau4mom.root"; p.eta = "2.1<|#eta|<2.5"; p.plot = "eta_21_25";
  //v.push_back(p);

  for(vector<mpair_t>::iterator i = v.begin(); i!= v.end(); i++)
    Loop( dire+i->file, i->eta, i->plot);

}

void Loop(const string &fileName, const string &etaRange, const string &plotName){

  TFile *f = new TFile(fileName.c_str());
  if(!f){cerr<<"unable to open file "<<fileName<<endl; return;}

  // P1(f, etaRange, plotName);
  // P2(f, etaRange, plotName);
  // P3(f, etaRange, plotName);
  // P4(f, etaRange, plotName);
  // P5(f, etaRange, plotName);
  // P6(f, etaRange, plotName);
  // P7(f, etaRange, plotName);
  // P8(f, etaRange, plotName);
  // P9(f, etaRange, plotName);
  // P10(f, etaRange, plotName);
  // P11(f, etaRange, plotName);
  // P12(f, etaRange, plotName);
  // P13(f, etaRange, plotName);
  // P14(f, etaRange, plotName);
  // P15(f, etaRange, plotName);
  // P16(f, etaRange, plotName);
  // P17(f, etaRange, plotName);
  // P18(f, etaRange, plotName);
  //P19(f, etaRange, plotName);
  P20(f, etaRange, plotName);

  delete f;
}
//===============================================================================================================
void P1(TFile *f, const string &etaRange, const string &plotName){

  TH1D *g1 = H(f, "tau_pan_3p_reso_rel");
  TH1D *g2 = H(f, "tau_pan_3p0n_reso_rel");
  TH1D *g3 = H(f, "tau_pan_3pXn_reso_rel");


  TH1D *gs_a;
  TH1D *gs_b;
  string fs_a;
  string fs_b;
  if(g2){
    double f_1_2 = F(g2, g1);
    double fp_1_2 = FP(g2, g1);
    fs_a = NumString(fp_1_2);
    NF(g2, f_1_2);

    gs_a = G("rel_res");
    gs_a->Add(g2);
    gs_a->SetFillColor(kBlue-7);
    gs_a->SetLineColor(kBlue-7);

    //gs_b = new TH1D(*g2);
    gs_b = G("rel_res");
    gs_b->Add(g2);
    if(g3){
      double f_1_3 = F(g3, g1);
      double fp_1_3 = FP(g3, g1);
      fs_b = NumString(fp_1_3);
      NF(g3, f_1_3);

      gs_b->Add(g3);
      gs_b->SetFillColor(kYellow-6);
      gs_b->SetLineColor(kYellow-6);
    }
  }

  N(g1);

  TCanvas *c = C();
  //draw
  c->cd();

  R(g1);

  g1->Draw();

  if(gs_b) gs_b->Draw("same");

  if(gs_a) gs_a->Draw("same");

  g1->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(g1,"3p","l");
  leg->AddEntry(gs_a, ("3p0n  " + fs_a + "%").c_str(),"f");
  leg->AddEntry(gs_b, ("3pXn  " + fs_b + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 1, plotName);

  delete g1; delete g2; delete g3; delete gs_a; delete gs_b;
  delete leg; delete l; delete t; delete c;
}
//===============================================================================================================
void P2(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_3p_true_3p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_3p0n_true_3p0n_reso_rel");
  TH1D *h2 = H(f, "tau_pan_3p0n_true_3pXn_reso_rel");
  TH1D *h3 = H(f, "tau_pan_3p0n_true_other_reso_rel");//not included

  TH1D *h4 = H(f, "tau_pan_3pXn_true_3p0n_reso_rel");
  TH1D *h5 = H(f, "tau_pan_3pXn_true_3pXn_reso_rel");
  TH1D *h6 = H(f, "tau_pan_3pXn_true_other_reso_rel"); //not included

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);
  double f5 = F(h5, h0); double fp5 = FP(h5, h0); string fs5 = NumString(fp5); NF(h5, f5);
  double f6 = F(h6, h0); double fp6 = FP(h6, h0); string fs6 = NumString(fp6); NF(h6, f6);

  //cout<<f1<<endl<<f2<<endl<<f3<<endl<<f4<<endl<<f5<<endl<<f6<<endl; cout<<"tot "<<f1+f2+f3+f4+f5+f6<<endl;
  cout<<f1<<endl<<f2<<endl<<f4<<endl<<f5<<endl; cout<<"tot "<<f1+f2+f4+f5<<endl;


  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");
  TH1D *s4 = G("rel_res");
  TH1D *s5 = G("rel_res");
  TH1D *s6 = G("rel_res");

  /* s1->Add(h1);
     s2->Add(h1); s2->Add(h2);
     s3->Add(h1); s3->Add(h2); s3->Add(h3);
     s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);
     s5->Add(h1); s5->Add(h2); s5->Add(h3); s5->Add(h4); s5->Add(h5);
     s6->Add(h1); s6->Add(h2); s6->Add(h3); s6->Add(h4); s6->Add(h5); s6->Add(h6); */

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s4->Add(h1); s4->Add(h2); s4->Add(h4);
  s5->Add(h1); s5->Add(h2); s5->Add(h4); s5->Add(h5);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;
  Color_t c3 = kRed-3;
  Color_t c4 = kGreen-6;
  Color_t c5 = kYellow-6;
  Color_t c6 = kCyan-6;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);
  s5->SetFillColor(c5); s5->SetLineColor(c5);
  s6->SetFillColor(c6); s6->SetLineColor(c6);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  //  if(s6) s6->Draw("same");
  if(s5) s5->Draw("same");
  if(s4) s4->Draw("same");
  //if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"3p-3p","l");
  //leg->AddEntry(s6, ("3pXn-Other " + fs6 + "%").c_str(),"f");
  leg->AddEntry(s5, ("#bf{3pXn-3pXn} " + fs5 + "%").c_str(),"f");
  leg->AddEntry(s4, ("3pXn-3p0n " + fs4 + "%").c_str(),"f");
  //leg->AddEntry(s3, ("3p0n-Other " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("3p0n-3pXn " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{3p0n-3p0n} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 2, plotName);

  delete h0; delete h1; delete h2; delete h3; delete h4; delete h5; delete h6;
  delete s1; delete s2; delete s3; delete s4; delete s5; delete s6;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P3(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_1p_true_1p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p0n_true_1p0n_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p0n_true_1p1n_reso_rel");
  TH1D *h3 = H(f, "tau_pan_1p0n_true_1pXn_reso_rel");

  TH1D *h4 = H(f, "tau_pan_1p1n_true_1p0n_reso_rel");
  TH1D *h5 = H(f, "tau_pan_1p1n_true_1p1n_reso_rel");
  TH1D *h6 = H(f, "tau_pan_1p1n_true_1pXn_reso_rel");

  TH1D *h7 = H(f, "tau_pan_1pXn_true_1p0n_reso_rel");
  TH1D *h8 = H(f, "tau_pan_1pXn_true_1p1n_reso_rel");
  TH1D *h9 = H(f, "tau_pan_1pXn_true_1pXn_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);
  double f5 = F(h5, h0); double fp5 = FP(h5, h0); string fs5 = NumString(fp5); NF(h5, f5);
  double f6 = F(h6, h0); double fp6 = FP(h6, h0); string fs6 = NumString(fp6); NF(h6, f6);
  double f7 = F(h7, h0); double fp7 = FP(h7, h0); string fs7 = NumString(fp7); NF(h7, f7);
  double f8 = F(h8, h0); double fp8 = FP(h8, h0); string fs8 = NumString(fp8); NF(h8, f8);
  double f9 = F(h9, h0); double fp9 = FP(h9, h0); string fs9 = NumString(fp9); NF(h9, f9);

  cout<<f1<<endl<<f2<<endl<<f3<<endl<<f4<<endl<<f5<<endl<<f6<<endl<<f7<<endl<<f8<<endl<<f9<<endl;
  cout<<"tot "<<f1+f2+f3+f4+f5+f6+f7+f8+f9<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");
  TH1D *s4 = G("rel_res");
  TH1D *s5 = G("rel_res");
  TH1D *s6 = G("rel_res");
  TH1D *s7 = G("rel_res");
  TH1D *s8 = G("rel_res");
  TH1D *s9 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);
  s5->Add(h1); s5->Add(h2); s5->Add(h3); s5->Add(h4); s5->Add(h5);
  s6->Add(h1); s6->Add(h2); s6->Add(h3); s6->Add(h4); s6->Add(h5); s6->Add(h6);
  s7->Add(h1); s7->Add(h2); s7->Add(h3); s7->Add(h4); s7->Add(h5); s7->Add(h6); s7->Add(h7);
  s8->Add(h1); s8->Add(h2); s8->Add(h3); s8->Add(h4); s8->Add(h5); s8->Add(h6); s8->Add(h7); s8->Add(h8);
  s9->Add(h1); s9->Add(h2); s9->Add(h3); s9->Add(h4); s9->Add(h5); s9->Add(h6); s9->Add(h7); s9->Add(h8); s9->Add(h9);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;
  Color_t c3 = kRed-3;
  Color_t c4 = kCyan-6;
  Color_t c5 = kYellow-6;
  Color_t c6 = kGreen-6;
  Color_t c7 = kOrange+10;
  Color_t c8 = kGray;
  Color_t c9 = kViolet;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);
  s5->SetFillColor(c5); s5->SetLineColor(c5);
  s6->SetFillColor(c6); s6->SetLineColor(c6);
  s7->SetFillColor(c7); s7->SetLineColor(c7);
  s8->SetFillColor(c8); s8->SetLineColor(c8);
  s9->SetFillColor(c9); s9->SetLineColor(c9);

  h1->SetLineColor(c1); h1->SetLineWidth(histo_lw);
  h2->SetLineColor(c2); h2->SetLineWidth(histo_lw);
  h3->SetLineColor(c3); h3->SetLineWidth(histo_lw);
  h4->SetLineColor(c4); h4->SetLineWidth(histo_lw);
  h5->SetLineColor(c5); h5->SetLineWidth(histo_lw);
  h6->SetLineColor(c6); h6->SetLineWidth(histo_lw);
  h7->SetLineColor(c7); h7->SetLineWidth(histo_lw);
  h8->SetLineColor(c8); h8->SetLineWidth(histo_lw);
  h9->SetLineColor(c9); h9->SetLineWidth(histo_lw);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();


  if(kStack){
    if(s9) s9->Draw("same");
    if(s8) s8->Draw("same");
    if(s7) s7->Draw("same");
    if(s6) s6->Draw("same");
    if(s5) s5->Draw("same");
    if(s4) s4->Draw("same");
    if(s3) s3->Draw("same");
    if(s2) s2->Draw("same");
    if(s1) s1->Draw("same");
    h0->Draw("same");
    h0->SetMinimum(1e-5);
    gPad->SetLogy();

  }else{
    h9->Draw("same");
    h8->Draw("same");
    h7->Draw("same");
    h6->Draw("same");
    h5->Draw("same");
    h4->Draw("same");
    h3->Draw("same");
    h2->Draw("same");
    h1->Draw("same");
  }




  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1p-1p","l");
  leg->AddEntry(s9, ("#bf{1pXn-1pXn} " + fs9 + "%").c_str(),"f");
  leg->AddEntry(s8, ("1pXn-1p1n " + fs8 + "%").c_str(),"f");
  leg->AddEntry(s7, ("1pXn-1p0n " + fs7 + "%").c_str(),"f");
  leg->AddEntry(s6, ("1p1n-1pXn " + fs6 + "%").c_str(),"f");
  leg->AddEntry(s5, ("#bf{1p1n-1p1n} " + fs5 + "%").c_str(),"f");
  leg->AddEntry(s4, ("1p1n-1p0n " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("1p0n-1pXn " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("1p0n-1p1n " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{1p0n-1p0n} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 3, plotName);

  return;

  if(SaveHistos){
    string rname = dir + plotName+".root";
    cout<<rname<<endl;
    TFile *fn = new TFile(rname.c_str(), "recreate");
    fn->cd();
    s1->Write();
    s2->Write();
    s3->Write();
    s4->Write();
    s5->Write();
    s6->Write();
    s7->Write();
    s8->Write();
    s9->Write();
    fn->Close();
  }


  delete h0; delete h1; delete h2; delete h3; delete h4; delete h5; delete h6; delete h7; delete h8; delete h9;
  delete s1; delete s2; delete s3; delete s4; delete s5; delete s6; delete s7; delete s8; delete s9;
  delete c; delete leg; delete l; delete t;



}
//====================================================================================================
void P4(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_1p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p_true_1p_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p_true_3p_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);

  cout<<f1<<endl<<f2<<endl;
  cout<<"tot "<<f1+f2<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1p","l");
  leg->AddEntry(s2, ("1p-3p " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{1p-1p} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 4, plotName);

  delete h0; delete h1; delete h2;
  delete s1; delete s2;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P5(TFile *f, const string &etaRange, const string &plotName){


  TH1D *h0 = H(f, "tau_pan_3p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_3p_true_3p_reso_rel");
  TH1D *h2 = H(f, "tau_pan_3p_true_1p_reso_rel");
  TH1D *h3 = H(f, "tau_pan_3p_true_5p_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);

  cout<<f1<<endl<<f2<<endl<<f3<<endl;
  cout<<"tot "<<f1+f2+f3<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;
  Color_t c3 = kYellow-2;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"3p","l");
  leg->AddEntry(s3, ("3p-5p " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("3p-1p " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{3p-3p} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 5, plotName);

  delete h0; delete h1; delete h2; delete h3;
  delete s1; delete s2; delete s3;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P6(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_0n_reso_rel");

  TH1D *h1 = H(f, "tau_pan_0n_true_0n_reso_rel");
  TH1D *h2 = H(f, "tau_pan_0n_true_1n_reso_rel");
  TH1D *h3 = H(f, "tau_pan_0n_true_Xn_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);

  cout<<f1<<endl<<f2<<endl<<f3<<endl;
  cout<<"tot "<<f1+f2+f3<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;
  Color_t c3 = kGreen-3;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"0n","l");
  leg->AddEntry(s3, ("0n-Xn " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("0n-1n " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{0n-0n} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 6, plotName);

  delete h0; delete h1; delete h2; delete h3;
  delete s1; delete s2; delete s3;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P7(TFile *f, const string &etaRange, const string &plotName){


  TH1D *h0 = H(f, "tau_pan_1n_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1n_true_1n_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1n_true_0n_reso_rel");
  TH1D *h3 = H(f, "tau_pan_1n_true_Xn_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);

  cout<<f1<<endl<<f2<<endl<<f3<<endl;
  cout<<"tot "<<f1+f2+f3<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;
  Color_t c3 = kMagenta-8;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1n","l");
  leg->AddEntry(s3, ("1n-Xn " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("1n-0n " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{1n-1n} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 7, plotName);

  delete h0; delete h1; delete h2; delete h3;
  delete s1; delete s2; delete s3;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P8(TFile *f, const string &etaRange, const string &plotName){


  TH1D *h0 = H(f, "tau_pan_Xn_reso_rel");

  TH1D *h1 = H(f, "tau_pan_Xn_true_Xn_reso_rel");
  TH1D *h2 = H(f, "tau_pan_Xn_true_1n_reso_rel");
  TH1D *h3 = H(f, "tau_pan_Xn_true_0n_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);

  cout<<f1<<endl<<f2<<endl<<f3<<endl;
  cout<<"tot "<<f1+f2+f3<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");


  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;
  Color_t c3 = kMagenta-8;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"Xn","l");
  leg->AddEntry(s3, ("Xn-0n " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("Xn-1n " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{Xn-Xn} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 8, plotName);

  delete h0; delete h1; delete h2; delete h3;
  delete s1; delete s2; delete s3;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P9(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_3p_true_3p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_3p_true_3p_matched_trk_parent_0_reso_rel");
  TH1D *h2 = H(f, "tau_pan_3p_true_3p_matched_trk_parent_1_reso_rel");
  TH1D *h3 = H(f, "tau_pan_3p_true_3p_matched_trk_parent_2_reso_rel");
  TH1D *h4 = H(f, "tau_pan_3p_true_3p_matched_trk_parent_3_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);

  cout<<f1<<" "<<f2<<" "<<f3<<" "<<f4<<endl;
  cout<<"tot "<<f1+f2+f3+f4<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");
  TH1D *s4 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);

  Color_t c1 = kViolet-8;
  Color_t c2 = kYellow-8;
  Color_t c3 = kGreen-8;
  Color_t c4 = kOrange-9;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s4) s4->Draw("same");
  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"3p-3p","l");
  leg->AddEntry(s4, ("#bf{3 tracks from real parent} " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("2 tracks from real parent " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("1 track  from real parent " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("0 tracks from real parent " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 9, plotName);

  delete h0; delete h1; delete h2; delete h3; delete h4;
  delete s1; delete s2; delete s3; delete s4;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P10(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_3p_true_1p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_3p_true_1p_matched_trk_parent_0_reso_rel");
  TH1D *h2 = H(f, "tau_pan_3p_true_1p_matched_trk_parent_1_reso_rel");
  TH1D *h3 = H(f, "tau_pan_3p_true_1p_matched_trk_parent_2_reso_rel");
  TH1D *h4 = H(f, "tau_pan_3p_true_1p_matched_trk_parent_3_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);

  cout<<f1<<" "<<f2<<" "<<f3<<" "<<f4<<endl;
  cout<<"tot "<<f1+f2+f3+f4<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");
  TH1D *s4 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);

  Color_t c1 = kViolet-8;
  Color_t c2 = kYellow-8;
  Color_t c3 = kGreen-8;
  Color_t c4 = kOrange-9;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s4) s4->Draw("same");
  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"3p-1p","l");
  leg->AddEntry(s4, ("#bf{3 tracks from real parent} " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("2 tracks from real parent " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("1 track  from real parent " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("0 tracks from real parent " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 10, plotName);

  delete h0; delete h1; delete h2; delete h3; delete h4;
  delete s1; delete s2; delete s3; delete s4;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P11(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_1p_true_1p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p_true_1p_matched_trk_parent_0_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p_true_1p_matched_trk_parent_1_reso_rel");
  TH1D *h3 = H(f, "tau_pan_1p_true_1p_matched_trk_parent_2_reso_rel");
  TH1D *h4 = H(f, "tau_pan_1p_true_1p_matched_trk_parent_3_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);

  cout<<f1<<" "<<f2<<" "<<f3<<" "<<f4<<endl;
  double tot = f1+f2+f3+f4;
  cout<<"tot "<<tot<<endl;
  if(tot>1) cout<<"WARNING : Sum of franctions is not 1"<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");
  TH1D *s4 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);

  Color_t c1 = kViolet-8;
  Color_t c2 = kYellow-8;
  Color_t c3 = kGreen-8;
  Color_t c4 = kOrange-9;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s4) s4->Draw("same");
  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1p-1p","l");
  leg->AddEntry(s4, ("3 tracks from real parent " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("2 tracks from real parent " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("#bf{1 track  from real parent} " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("0 tracks from real parent " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 11, plotName);

  delete h0; delete h1; delete h2; delete h3; delete h4;
  delete s1; delete s2; delete s3; delete s4;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P12(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_1p_true_3p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p_true_3p_matched_trk_parent_0_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p_true_3p_matched_trk_parent_1_reso_rel");
  TH1D *h3 = H(f, "tau_pan_1p_true_3p_matched_trk_parent_2_reso_rel");
  TH1D *h4 = H(f, "tau_pan_1p_true_3p_matched_trk_parent_3_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);

  cout<<f1<<" "<<f2<<" "<<f3<<" "<<f4<<endl;
  double tot = f1+f2+f3+f4;
  cout<<"tot "<<tot<<endl;
  if(tot>1) cout<<"WARNING : Sum of franctions is not 1"<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");
  TH1D *s4 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);

  Color_t c1 = kViolet-8;
  Color_t c2 = kYellow-8;
  Color_t c3 = kGreen-8;
  Color_t c4 = kOrange-9;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s4) s4->Draw("same");
  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1p-3p","l");
  leg->AddEntry(s4, ("3 tracks from real parent " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("2 tracks from real parent " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("#bf{1 track  from real parent} " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("0 tracks from real parent " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 12, plotName);

  delete h0; delete h1; delete h2; delete h3; delete h4;
  delete s1; delete s2; delete s3; delete s4;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P13(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h1 = H(f, "tau_pan_1p0n_true_1p0n_eta");
  TH1D *h2 = H(f, "tau_pan_1p0n_true_1p1n_eta");
  TH1D *h3 = H(f, "tau_pan_1p0n_true_1pXn_eta");

  TH1D *h4 = H(f, "tau_pan_1p1n_true_1p0n_eta");
  TH1D *h5 = H(f, "tau_pan_1p1n_true_1p1n_eta");
  TH1D *h6 = H(f, "tau_pan_1p1n_true_1pXn_eta");

  TH1D *h7 = H(f, "tau_pan_1pXn_true_1p0n_eta");
  TH1D *h8 = H(f, "tau_pan_1pXn_true_1p1n_eta");
  TH1D *h9 = H(f, "tau_pan_1pXn_true_1pXn_eta");

  TH1D *h0 = G("eta"); //H(f, "tau_pan_1p_true_1p_eta");
  h0->Add(h1);   h0->Add(h2);   h0->Add(h3);   h0->Add(h4);   h0->Add(h5);   h0->Add(h6);   h0->Add(h7);   h0->Add(h8);   h0->Add(h9);

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);
  double f5 = F(h5, h0); double fp5 = FP(h5, h0); string fs5 = NumString(fp5); NF(h5, f5);
  double f6 = F(h6, h0); double fp6 = FP(h6, h0); string fs6 = NumString(fp6); NF(h6, f6);
  double f7 = F(h7, h0); double fp7 = FP(h7, h0); string fs7 = NumString(fp7); NF(h7, f7);
  double f8 = F(h8, h0); double fp8 = FP(h8, h0); string fs8 = NumString(fp8); NF(h8, f8);
  double f9 = F(h9, h0); double fp9 = FP(h9, h0); string fs9 = NumString(fp9); NF(h9, f9);

  cout<<f1<<endl<<f2<<endl<<f3<<endl<<f4<<endl<<f5<<endl<<f6<<endl<<f7<<endl<<f8<<endl<<f9<<endl;
  cout<<"tot "<<f1+f2+f3+f4+f5+f6+f7+f8+f9<<endl;

  string var = "eta";
  TH1D *s1 = G(var);
  TH1D *s2 = G(var);
  TH1D *s3 = G(var);
  TH1D *s4 = G(var);
  TH1D *s5 = G(var);
  TH1D *s6 = G(var);
  TH1D *s7 = G(var);
  TH1D *s8 = G(var);
  TH1D *s9 = G(var);

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);
  s5->Add(h1); s5->Add(h2); s5->Add(h3); s5->Add(h4); s5->Add(h5);
  s6->Add(h1); s6->Add(h2); s6->Add(h3); s6->Add(h4); s6->Add(h5); s6->Add(h6);
  s7->Add(h1); s7->Add(h2); s7->Add(h3); s7->Add(h4); s7->Add(h5); s7->Add(h6); s7->Add(h7);
  s8->Add(h1); s8->Add(h2); s8->Add(h3); s8->Add(h4); s8->Add(h5); s8->Add(h6); s8->Add(h7); s8->Add(h8);
  s9->Add(h1); s9->Add(h2); s9->Add(h3); s9->Add(h4); s9->Add(h5); s9->Add(h6); s9->Add(h7); s9->Add(h8); s9->Add(h9);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;
  Color_t c3 = kRed-3;
  Color_t c4 = kCyan-6;
  Color_t c5 = kYellow-6;
  Color_t c6 = kGreen-6;
  Color_t c7 = kOrange+10;
  Color_t c8 = kGray;
  Color_t c9 = kViolet;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);
  s5->SetFillColor(c5); s5->SetLineColor(c5);
  s6->SetFillColor(c6); s6->SetLineColor(c6);
  s7->SetFillColor(c7); s7->SetLineColor(c7);
  s8->SetFillColor(c8); s8->SetLineColor(c8);
  s9->SetFillColor(c9); s9->SetLineColor(c9);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  h0->GetXaxis()->SetTitle("#eta_{reco}");
  R(h0);

  h0->Draw();

  if(s9) s9->Draw("same");
  if(s8) s8->Draw("same");
  if(s7) s7->Draw("same");
  if(s6) s6->Draw("same");
  if(s5) s5->Draw("same");
  if(s4) s4->Draw("same");
  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");

  if(s1) s1->Draw("same");

  h0->Draw("same");

  h0->SetMaximum( h0->GetMaximum()*2 );

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1p-1p","l");
  leg->AddEntry(s9, ("#bf{1pXn-1pXn} " + fs9 + "%").c_str(),"f");
  leg->AddEntry(s8, ("1pXn-1p1n " + fs8 + "%").c_str(),"f");
  leg->AddEntry(s7, ("1pXn-1p0n " + fs7 + "%").c_str(),"f");
  leg->AddEntry(s6, ("1p1n-1pXn " + fs6 + "%").c_str(),"f");
  leg->AddEntry(s5, ("#bf{1p1n-1p1n} " + fs5 + "%").c_str(),"f");
  leg->AddEntry(s4, ("1p1n-1p0n " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("1p0n-1pXn " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("1p0n-1p1n " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{1p0n-1p0n} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 13, plotName);

  delete h0; delete h1; delete h2; delete h3; delete h4; delete h5; delete h6; delete h7; delete h8; delete h9;
  delete s1; delete s2; delete s3; delete s4; delete s5; delete s6; delete s7; delete s8; delete s9;
  delete c; delete leg; delete l; delete t;

}
//====================================================================================================
void P14(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h1 = H(f, "tau_pan_3p0n_true_3p0n_eta");
  TH1D *h2 = H(f, "tau_pan_3p0n_true_3pXn_eta");
  TH1D *h3 = H(f, "tau_pan_3pXn_true_3p0n_eta");
  TH1D *h4 = H(f, "tau_pan_3pXn_true_3pXn_eta");

  TH1D *h0 = G("eta"); //H(f, "tau_pan_3p_true_3p_eta");
  h0->Add(h1);   h0->Add(h2);   h0->Add(h3);   h0->Add(h4);

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);

  cout<<f1<<endl<<f2<<endl<<f3<<endl<<f4<<endl;
  cout<<"tot "<<f1+f2+f3+f4<<endl;

  string var = "eta";
  TH1D *s1 = G(var);
  TH1D *s2 = G(var);
  TH1D *s3 = G(var);
  TH1D *s4 = G(var);

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;
  Color_t c3 = kRed-3;
  Color_t c4 = kCyan-6;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  h0->GetXaxis()->SetTitle("#eta_{reco}");

  R(h0);

  h0->Draw();

  if(s4) s4->Draw("same");
  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  h0->SetMaximum( h0->GetMaximum()*2 );

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"3p-3p","l");
  leg->AddEntry(s4, ("#bf{3pXn-3pXn} " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("3pXn-3p0n " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("3p0n-3pXn " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("#bf{3p0n-3p0n} " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 14, plotName);

  delete h0; delete h1; delete h2; delete h3; delete h4;
  delete s1; delete s2; delete s3; delete s4;
  delete c; delete leg; delete l; delete t;
}
//===========================================================================================
void P15(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_1p_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p_matched_trk_score_high_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p_matched_trk_score_medium_reso_rel");
  TH1D *h3 = H(f, "tau_pan_1p_matched_trk_score_low_reso_rel");


  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);

  cout<<f1<<" "<<f2<<" "<<f3<<endl;
  double tot = f1+f2+f3;
  cout<<"tot "<<tot<<endl;
  if(tot>1 ) cout<<"WARNING : Sum of franctions is not 1"<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);

  Color_t c1 = kViolet-8;
  Color_t c2 = kOrange+1;
  Color_t c3 = kGreen-8;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s3) s3->Draw("same");
  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau - Track matching probability");
  leg->AddEntry(h0,"1p","l");
  leg->AddEntry(s3, ("low " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("medium (score>80%) " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("high (score>90%) " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 15, plotName);

  delete h0; delete h1; delete h2; delete h3;
  delete s1; delete s2; delete s3;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P16(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_1p0n_true_1p0n_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p0n_true_1p0n_matched_trk_parent_1_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p0n_true_1p0n_matched_trk_parent_0_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);

  cout<<f1<<endl<<f2<<endl;
  cout<<"tot "<<f1+f2<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1p0n-1p0n","l");

  leg->AddEntry(s2, ("otherwise " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("track from tau " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 16, plotName);

  delete h0; delete h1; delete h2;
  delete s1; delete s2;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P17(TFile *f, const string &etaRange, const string &plotName){

  //TH1D *h0 = H(f, "tau_pan_1p0n_true_1p0n_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p0n_15_20_true_1p0n_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p0n_20_25_true_1p0n_reso_rel");
  TH1D *h3 = H(f, "tau_pan_1p0n_25_30_true_1p0n_reso_rel");
  TH1D *h4 = H(f, "tau_pan_1p0n_30_40_true_1p0n_reso_rel");
  TH1D *h5 = H(f, "tau_pan_1p0n_40_50_true_1p0n_reso_rel");
  TH1D *h6 = H(f, "tau_pan_1p0n_50_60_true_1p0n_reso_rel");
  TH1D *h7 = H(f, "tau_pan_1p0n_60_70_true_1p0n_reso_rel");
  TH1D *h8 = H(f, "tau_pan_1p0n_70_80_true_1p0n_reso_rel");
  TH1D *h9 = H(f, "tau_pan_1p0n_80_100_true_1p0n_reso_rel");

  TH1D *h0 = G("rel_res");
  h0->Add(h1);
  h0->Add(h2);
  h0->Add(h3);
  h0->Add(h4);
  h0->Add(h5);
  h0->Add(h6);
  h0->Add(h7);
  h0->Add(h8);
  h0->Add(h9);

  if(!h0 || !h0->Integral()) {cout<<"empty reference histo "<<endl; return;}

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);
  double f5 = F(h5, h0); double fp5 = FP(h5, h0); string fs5 = NumString(fp5); NF(h5, f5);
  double f6 = F(h6, h0); double fp6 = FP(h6, h0); string fs6 = NumString(fp6); NF(h6, f6);
  double f7 = F(h7, h0); double fp7 = FP(h7, h0); string fs7 = NumString(fp7); NF(h7, f7);
  double f8 = F(h8, h0); double fp8 = FP(h8, h0); string fs8 = NumString(fp8); NF(h8, f8);
  double f9 = F(h9, h0); double fp9 = FP(h9, h0); string fs9 = NumString(fp9); NF(h9, f9);

  cout<<f1<<endl<<f2<<endl<<f3<<endl<<f4<<endl<<f5<<endl<<f6<<endl<<f7<<endl<<f8<<endl<<f9<<endl;
  cout<<"tot "<<f1+f2+f3+f4+f5+f6+f7+f8+f9<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");
  TH1D *s4 = G("rel_res");
  TH1D *s5 = G("rel_res");
  TH1D *s6 = G("rel_res");
  TH1D *s7 = G("rel_res");
  TH1D *s8 = G("rel_res");
  TH1D *s9 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);
  s5->Add(h1); s5->Add(h2); s5->Add(h3); s5->Add(h4); s5->Add(h5);
  s6->Add(h1); s6->Add(h2); s6->Add(h3); s6->Add(h4); s6->Add(h5); s6->Add(h6);
  s7->Add(h1); s7->Add(h2); s7->Add(h3); s7->Add(h4); s7->Add(h5); s7->Add(h6); s7->Add(h7);
  s8->Add(h1); s8->Add(h2); s8->Add(h3); s8->Add(h4); s8->Add(h5); s8->Add(h6); s8->Add(h7); s8->Add(h8);
  s9->Add(h1); s9->Add(h2); s9->Add(h3); s9->Add(h4); s9->Add(h5); s9->Add(h6); s9->Add(h7); s9->Add(h8); s9->Add(h9);

  Color_t c1 = kMagenta;
  Color_t c2 = kBlue;
  Color_t c3 = kRed;
  Color_t c4 = kAzure-2;
  Color_t c5 = kYellow-6;
  Color_t c6 = kGreen;
  Color_t c7 = kOrange;
  Color_t c8 = kGray+2;
  Color_t c9 = kCyan;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);
  s5->SetFillColor(c5); s5->SetLineColor(c5);
  s6->SetFillColor(c6); s6->SetLineColor(c6);
  s7->SetFillColor(c7); s7->SetLineColor(c7);
  s8->SetFillColor(c8); s8->SetLineColor(c8);
  s9->SetFillColor(c9); s9->SetLineColor(c9);

  h1->SetLineColor(c1); h1->SetLineWidth(histo_lw);
  h2->SetLineColor(c2); h2->SetLineWidth(histo_lw);
  h3->SetLineColor(c3); h3->SetLineWidth(histo_lw);
  h4->SetLineColor(c4); h4->SetLineWidth(histo_lw);
  h5->SetLineColor(c5); h5->SetLineWidth(histo_lw);
  h6->SetLineColor(c6); h6->SetLineWidth(histo_lw);
  h7->SetLineColor(c7); h7->SetLineWidth(histo_lw);
  h8->SetLineColor(c8); h8->SetLineWidth(histo_lw);
  h9->SetLineColor(c9); h9->SetLineWidth(histo_lw);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();

  if(kStack){
    if(s9) s9->Draw("same");
    if(s8) s8->Draw("same");
    if(s7) s7->Draw("same");
    if(s6) s6->Draw("same");
    if(s5) s5->Draw("same");
    if(s4) s4->Draw("same");
    if(s3) s3->Draw("same");
    if(s2) s2->Draw("same");
    if(s1) s1->Draw("same");
    h0->Draw("same");

    gPad->SetLogy();

  }else{

    h1->Draw("same"); //h1->Rebin(3);
    h2->Draw("same"); //h2->Rebin(3);
    h3->Draw("same"); //h3->Rebin(3);
    //h4->Draw("same"); h4->Rebin(3);
    h5->Draw("same"); //h5->Rebin(3);
    //h6->Draw("same"); h6->Rebin(3);
    h7->Draw("same"); //h7->Rebin(3);
    h8->Draw("same"); //h8->Rebin(3);
    //h9->Draw("same"); //h9->Rebin(3);

    gPad->SetLogy();
  }




  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("1p0n-1p0n");
  //leg->AddEntry(h0,"","l");
  leg->AddEntry(s9, ("80-100 " + fs9 + "%").c_str(),"f");
  leg->AddEntry(s8, ("70-80 " + fs8 + "%").c_str(),"f");
  leg->AddEntry(s7, ("60-70 " + fs7 + "%").c_str(),"f");
  leg->AddEntry(s6, ("50-60 " + fs6 + "%").c_str(),"f");
  leg->AddEntry(s5, ("40-50 " + fs5 + "%").c_str(),"f");
  leg->AddEntry(s4, ("30-40 " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("25-30 " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("20-25 " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("15-20 " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 17, plotName);

  return;

  if(SaveHistos){
    string rname = dir + plotName+".root";
    cout<<rname<<endl;
    TFile *fn = new TFile(rname.c_str(), "recreate");
    fn->cd();
    s1->Write();
    s2->Write();
    s3->Write();
    s4->Write();
    s5->Write();
    s6->Write();
    s7->Write();
    s8->Write();
    s9->Write();
    fn->Close();
  }


  delete h0; delete h1; delete h2; delete h3; delete h4; delete h5; delete h6; delete h7; delete h8; delete h9;
  delete s1; delete s2; delete s3; delete s4; delete s5; delete s6; delete s7; delete s8; delete s9;
  delete c; delete leg; delete l; delete t;



}
//====================================================================================================
void P18(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_1p1n_true_1p1n_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p1n_true_1p1n_matched_trk_parent_1_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p1n_true_1p1n_matched_trk_parent_0_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);

  cout<<f1<<endl<<f2<<endl;
  cout<<"tot "<<f1+f2<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);

  N(h0);

  TCanvas *c = C();
  //draw

  c->cd();

  R(h0);

  h0->Draw();

  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1p1n-1p1n","l");

  leg->AddEntry(s2, ("otherwise " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("track from tau " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 18, plotName);

  delete h0; delete h1; delete h2;
  delete s1; delete s2;
  delete c; delete leg; delete l; delete t;
}
//====================================================================================================
void P19(TFile *f, const string &etaRange, const string &plotName){

  //TH1D *h0 = H(f, "tau_pan_1p0n_true_1p0n_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p1n_15_20_true_1p1n_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p1n_20_25_true_1p1n_reso_rel");
  TH1D *h3 = H(f, "tau_pan_1p1n_25_30_true_1p1n_reso_rel");
  TH1D *h4 = H(f, "tau_pan_1p1n_30_40_true_1p1n_reso_rel");
  TH1D *h5 = H(f, "tau_pan_1p1n_40_50_true_1p1n_reso_rel");
  TH1D *h6 = H(f, "tau_pan_1p1n_50_60_true_1p1n_reso_rel");
  TH1D *h7 = H(f, "tau_pan_1p1n_60_70_true_1p1n_reso_rel");
  TH1D *h8 = H(f, "tau_pan_1p1n_70_80_true_1p1n_reso_rel");
  TH1D *h9 = H(f, "tau_pan_1p1n_80_100_true_1p1n_reso_rel");

  TH1D *h0 = G("rel_res");
  h0->Add(h1);
  h0->Add(h2);
  h0->Add(h3);
  h0->Add(h4);
  h0->Add(h5);
  h0->Add(h6);
  h0->Add(h7);
  h0->Add(h8);
  h0->Add(h9);


  h0->GetXaxis()->SetTitle( h1->GetXaxis()->GetTitle() );

  if(!h0 || !h0->Integral()) {cout<<"empty reference histo "<<endl; return;}

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);
  double f3 = F(h3, h0); double fp3 = FP(h3, h0); string fs3 = NumString(fp3); NF(h3, f3);
  double f4 = F(h4, h0); double fp4 = FP(h4, h0); string fs4 = NumString(fp4); NF(h4, f4);
  double f5 = F(h5, h0); double fp5 = FP(h5, h0); string fs5 = NumString(fp5); NF(h5, f5);
  double f6 = F(h6, h0); double fp6 = FP(h6, h0); string fs6 = NumString(fp6); NF(h6, f6);
  double f7 = F(h7, h0); double fp7 = FP(h7, h0); string fs7 = NumString(fp7); NF(h7, f7);
  double f8 = F(h8, h0); double fp8 = FP(h8, h0); string fs8 = NumString(fp8); NF(h8, f8);
  double f9 = F(h9, h0); double fp9 = FP(h9, h0); string fs9 = NumString(fp9); NF(h9, f9);

  cout<<f1<<endl<<f2<<endl<<f3<<endl<<f4<<endl<<f5<<endl<<f6<<endl<<f7<<endl<<f8<<endl<<f9<<endl;
  cout<<"tot "<<f1+f2+f3+f4+f5+f6+f7+f8+f9<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");
  TH1D *s3 = G("rel_res");
  TH1D *s4 = G("rel_res");
  TH1D *s5 = G("rel_res");
  TH1D *s6 = G("rel_res");
  TH1D *s7 = G("rel_res");
  TH1D *s8 = G("rel_res");
  TH1D *s9 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);
  s3->Add(h1); s3->Add(h2); s3->Add(h3);
  s4->Add(h1); s4->Add(h2); s4->Add(h3); s4->Add(h4);
  s5->Add(h1); s5->Add(h2); s5->Add(h3); s5->Add(h4); s5->Add(h5);
  s6->Add(h1); s6->Add(h2); s6->Add(h3); s6->Add(h4); s6->Add(h5); s6->Add(h6);
  s7->Add(h1); s7->Add(h2); s7->Add(h3); s7->Add(h4); s7->Add(h5); s7->Add(h6); s7->Add(h7);
  s8->Add(h1); s8->Add(h2); s8->Add(h3); s8->Add(h4); s8->Add(h5); s8->Add(h6); s8->Add(h7); s8->Add(h8);
  s9->Add(h1); s9->Add(h2); s9->Add(h3); s9->Add(h4); s9->Add(h5); s9->Add(h6); s9->Add(h7); s9->Add(h8); s9->Add(h9);

  Color_t c1 = kMagenta;
  Color_t c2 = kBlue;
  Color_t c3 = kRed;
  Color_t c4 = kAzure-2;
  Color_t c5 = kYellow-6;
  Color_t c6 = kGreen;
  Color_t c7 = kOrange;
  Color_t c8 = kGray+2;
  Color_t c9 = kCyan;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);
  s3->SetFillColor(c3); s3->SetLineColor(c3);
  s4->SetFillColor(c4); s4->SetLineColor(c4);
  s5->SetFillColor(c5); s5->SetLineColor(c5);
  s6->SetFillColor(c6); s6->SetLineColor(c6);
  s7->SetFillColor(c7); s7->SetLineColor(c7);
  s8->SetFillColor(c8); s8->SetLineColor(c8);
  s9->SetFillColor(c9); s9->SetLineColor(c9);

  h1->SetLineColor(c1); h1->SetLineWidth(histo_lw);
  h2->SetLineColor(c2); h2->SetLineWidth(histo_lw);
  h3->SetLineColor(c3); h3->SetLineWidth(histo_lw);
  h4->SetLineColor(c4); h4->SetLineWidth(histo_lw);
  h5->SetLineColor(c5); h5->SetLineWidth(histo_lw);
  h6->SetLineColor(c6); h6->SetLineWidth(histo_lw);
  h7->SetLineColor(c7); h7->SetLineWidth(histo_lw);
  h8->SetLineColor(c8); h8->SetLineWidth(histo_lw);
  h9->SetLineColor(c9); h9->SetLineWidth(histo_lw);

  N(h0);

  TCanvas *c = C();
  //draw
  c->cd();

  R(h0);

  h0->Draw();


  if(kStack){
    if(s9) s9->Draw("same");
    if(s8) s8->Draw("same");
    if(s7) s7->Draw("same");
    if(s6) s6->Draw("same");
    if(s5) s5->Draw("same");
    if(s4) s4->Draw("same");
    if(s3) s3->Draw("same");
    if(s2) s2->Draw("same");
    if(s1) s1->Draw("same");
    h0->Draw("same");

    gPad->SetLogy();

  }else{

    h1->Draw("same"); //h1->Rebin(3);
    h2->Draw("same"); //h2->Rebin(3);
    h3->Draw("same"); //h3->Rebin(3);
    //h4->Draw("same"); h4->Rebin(3);
    h5->Draw("same"); //h5->Rebin(3);
    //h6->Draw("same"); h6->Rebin(3);
    h7->Draw("same"); //h7->Rebin(3);
    h8->Draw("same"); //h8->Rebin(3);
    //h9->Draw("same"); //h9->Rebin(3);

    gPad->SetLogy();
  }




  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("1p1n-1p1n");
  //leg->AddEntry(h0,"","l");
  leg->AddEntry(s9, ("80-100 " + fs9 + "%").c_str(),"f");
  leg->AddEntry(s8, ("70-80 " + fs8 + "%").c_str(),"f");
  leg->AddEntry(s7, ("60-70 " + fs7 + "%").c_str(),"f");
  leg->AddEntry(s6, ("50-60 " + fs6 + "%").c_str(),"f");
  leg->AddEntry(s5, ("40-50 " + fs5 + "%").c_str(),"f");
  leg->AddEntry(s4, ("30-40 " + fs4 + "%").c_str(),"f");
  leg->AddEntry(s3, ("25-30 " + fs3 + "%").c_str(),"f");
  leg->AddEntry(s2, ("20-25 " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("15-20 " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 19, plotName);

  return;

  if(SaveHistos){
    string rname = dir + plotName+".root";
    cout<<rname<<endl;
    TFile *fn = new TFile(rname.c_str(), "recreate");
    fn->cd();
    s1->Write();
    s2->Write();
    s3->Write();
    s4->Write();
    s5->Write();
    s6->Write();
    s7->Write();
    s8->Write();
    s9->Write();
    fn->Close();
  }


  delete h0; delete h1; delete h2; delete h3; delete h4; delete h5; delete h6; delete h7; delete h8; delete h9;
  delete s1; delete s2; delete s3; delete s4; delete s5; delete s6; delete s7; delete s8; delete s9;
  delete c; delete leg; delete l; delete t;



}
//====================================================================================================
void P20(TFile *f, const string &etaRange, const string &plotName){

  TH1D *h0 = H(f, "tau_pan_1p0n_true_1p0n_reso_rel");

  TH1D *h1 = H(f, "tau_pan_1p0n_true_1p0n_kaon_decay_0_reso_rel");
  TH1D *h2 = H(f, "tau_pan_1p0n_true_1p0n_kaon_decay_1_reso_rel");

  double f1 = F(h1, h0); double fp1 = FP(h1, h0); string fs1 = NumString(fp1); NF(h1, f1);
  double f2 = F(h2, h0); double fp2 = FP(h2, h0); string fs2 = NumString(fp2); NF(h2, f2);

  cout<<f1<<endl<<f2<<endl;
  cout<<"tot "<<f1+f2<<endl;

  TH1D *s1 = G("rel_res");
  TH1D *s2 = G("rel_res");

  s1->Add(h1);
  s2->Add(h1); s2->Add(h2);

  Color_t c1 = kMagenta+9;
  Color_t c2 = kBlue-4;

  s1->SetFillColor(c1); s1->SetLineColor(c1);
  s2->SetFillColor(c2); s2->SetLineColor(c2);

  N(h0);

  TCanvas *c = C();
  //draw

  c->cd();

  R(h0);

  h0->Draw();

  if(s2) s2->Draw("same");
  if(s1) s1->Draw("same");

  h0->Draw("same");

  gPad->SetLogy();

  //legend
  TLegend *leg = L( legx0, legy0, legx1, legy1);
  leg->SetHeader("PanTau-VisTrue");
  leg->AddEntry(h0,"1p0n-1p0n","l");

  leg->AddEntry(s2, ("Kaonic decays " + fs2 + "%").c_str(),"f");
  leg->AddEntry(s1, ("Kaon-free decays " + fs1 + "%").c_str(),"f");
  leg->Draw();

  TLatex *l = T(label_x, label_y, mc); l->Draw(); TLatex *t = T(label_x, label_y-label_dy, etaRange); t->Draw();

  gPad->RedrawAxis();

  Save(c, 20, plotName);

  delete h0; delete h1; delete h2;
  delete s1; delete s2;
  delete c; delete leg; delete l; delete t;
}

//===========================================================================================
//===========================================================================================
void Save(TCanvas *c, int i, const string &s){

  string name = dir + "P" + GetStringFromInt(i)+"_"+s;

  c->SaveAs( (name+"."+outputformat).c_str() );
  cout<<endl;
}

TH1D *H(TFile *f, const string &s){

  TH1D *h = (TH1D*)f->Get( s.c_str() );

  string type =
    Has(s, "reso_rel") ? "rel_res" :
    Has(s, "eta") ? "eta" :
    "";

  if(!h){cerr<<"unable to obtain "<<s<<" from file, returning empty histo of type "<<type<<endl; return G(type);}

  if(!h->GetEntries() ) {cerr<<"empty "<<s<<" from file, returning empty histo of type "<<type<<endl; return G(type);}

  return h;
}

TH1D *G(const string &s){
  static int i;
  string name = "histo"+GetStringFromInt(i++);
  //cout<<"empty histo "<<name<<endl;
  int n_res_rel = 101; double l_res_rel = -1.01; double r_res_rel = 1.01;
  if(s=="rel_res") return new TH1D(name.c_str(),"", n_res_rel, l_res_rel, r_res_rel);

  int n_eta = 102; double l_eta = -2.55; double r_eta = 2.55;
  if(s=="eta") return new TH1D(name.c_str(),"", n_eta, l_eta, r_eta);

  return NULL;
}

string GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }

void N(TH1 *h){

  h->Scale( 1./h->Integral() );
}

double F(TH1 *h, TH1 *g){

  //cout<<"divide "<<h->Integral()<<" / "<<g->Integral()<<endl;
  double base =  g->Integral();
  if(!base) {cerr<<"reference plot has zero area"<<endl; return 0;}
  return h->Integral() / base;
}

double FP(TH1 *h, TH1 *g){
  return F(h,g)*100;
}

void NF(TH1 *h, double x){

  h->Scale( x/h->Integral() );
}

string NumString(double x){

  char n[12];

  sprintf(n,"%.2f", x);


  return char2str(n);
}
string  char2str(char *c){ stringstream ss; string s;  ss << c; ss >> s; return s; }

TCanvas *C(){

  static int j;
  string name = "canvas"+GetStringFromInt(j++);

  TCanvas *c = kStack ? new TCanvas(name.c_str(), "", 10,50,800,600) :  new TCanvas(name.c_str(), "", 0,0, 900, 700);
  //c->Range(0,0,1,1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetRightMargin(0.025);
  c->SetLeftMargin(0.1);
  c->SetTopMargin(0.04);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  return c;
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

TLatex *T(double x, double y, const string &s){

  TLatex *t = new TLatex(x,y,s.c_str());
  t->SetTextSize( t->GetTextSize() * 0.6);
  t->SetTextFont(42);
  //t->SetTextAlign(32);
  t->SetNDC();
  return t;

}

void R(TH1D*h0){

  h0->SetYTitle("normalized to unit area");
  h0->GetYaxis()->SetTitleOffset( h0->GetYaxis()->GetTitleOffset() * 1.1 );
  //h0->GetXaxis()->SetTitleOffset(1.2);
  h0->GetXaxis()->SetLabelSize( h0->GetXaxis()->GetLabelSize() * 0.9 );
  h0->GetYaxis()->SetTickLength( h0->GetYaxis()->GetTickLength() * 0.5);
  h0->GetXaxis()->SetNdivisions(525);
  h0->SetLineColor(1);
  h0->SetLineStyle(1);
  h0->SetLineWidth(2);
}

bool Has(const string &str, const string &sub){

  std::size_t found = str.find(sub);

  if (found!=std::string::npos) return true;

  return false;
}
