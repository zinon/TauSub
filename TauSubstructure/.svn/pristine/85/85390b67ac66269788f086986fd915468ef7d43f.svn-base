#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPad.h"
#include "TColor.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TLine.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
#include <sys/stat.h>

using namespace std;

bool ToDraw(TH1D *h);
vector<double> GetFracVec(vector<TH1D*> &vhist, bool kFirstIsRef, bool kNormHistos);
bool StrHas(const string &str, const string &sub);
TFile *File(TString s);
vector<TH1D*> GetHistoVec(TFile *f, vector<string>&v);
TH1D *Histo(TFile *f, const string &s);
TH2D *Histo2(TFile *f, const string &s);
TH1D *EmptyHisto(const string &s);
double Fraction(TH1 *h, TH1 *g);
double Percentage(TH1 *h, TH1 *g);
void Norm2Area(TH1 *h);
void Norm2Factor(TH1 *h, double x);
TCanvas *Canvas();
string  char2str(char *c);
string num2str(double x);
string int2str(int n);
void SetHistoStyles(vector<TH1D*> &v);
Color_t Color(int i);
TLegend *Legend(vector<TH1D*> &vh, vector<double> &vf, vector<string> &vt);
void PlotHistos(TCanvas *c, vector<TH1D*> &vhist, vector<double> &vfrac, vector<string> &vtitles, const string &histoType, string dir, string name, bool kLog, string info);
void Plot(TString file, vector<string> &histos, vector<string> &titles, string outDir, string outName, string info);
TLatex *Atlas();
TLatex *Algo();
TLatex *MC();
TLatex *Info(const string &s);
void FindRegionSigma(TH1D *h, double &xl, double &xr, int ns);
void MakeOutputDir(string outDir, string outName);
TH1D *OverflowHisto(TH1D *h, const string &s);

bool kEPS = true;
bool kPNG = false;
double y_top_level = 0.94;
double x_legend_right = 0.43;
double x_logo_left = 0.58;
double x_mc_left = 0.62;
double x_algo_left = 0.69;
double x_info_left = 0.69;
double rel_leg_font_size = 1.2;
bool kShowOverflow = true;

//===================================================================================
//top-level function

void Plot(TString file, vector<string> &vhistos, vector<string> &vtitles, string outDir, string outName, string info){

  MakeOutputDir(outDir, outName);
  TFile *f = File(file);
  vector<TH1D*> vhist = GetHistoVec(f, vhistos); 
  if(!vhist.size()){ cerr<<"empty hist vector.... "<<endl; return;} else { cout<<"common - histo vec size "<<vhist.size()<<endl;}
  vector<double> vfrac = GetFracVec(vhist, true, true); //use first histo as reference? also normalize the input histograms?
  TCanvas *c = Canvas();
  PlotHistos(c, vhist, vfrac, vtitles, "rel_res", outDir, outName, true, info); // ylog?
}
//===================================================================================
void MakeOutputDir(string outDir, string outName){

  if(outName.size()){}

  string outputdir =  "./results/"+outDir+"/";
  struct stat dst;
  int dstatus = stat(outputdir.c_str(),&dst);
  if( dstatus ){
    cout<<"\ncreating directory "<<outputdir<<endl;
    system( ("mkdir -p "+outputdir).c_str() );
  }

}
//===================================================================================
void PlotHistos(TCanvas *c, vector<TH1D*> &vhist, vector<double> &vfrac, vector<string> &vtitles, const string &histoType, string dir, string name, bool kLog, string info){

  //string outFile = "results/" + dir + "/" + name;
  string outFile = dir + "/" + name;


  SetHistoStyles(vhist);

  double orders_of_magn = 3;

  TH1D* h = EmptyHisto(histoType);
  double maxY(0);   double tmaxY(0);

  c->cd();
  h->Draw("HIST");

  for(vector<TH1D*>::iterator itr = vhist.begin(); itr != vhist.end(); itr++){
    if(ToDraw(*itr) ) (*itr)->Draw("HIST same");
    tmaxY = (*itr)->GetBinContent( (*itr)->GetMaximumBin() );
    maxY = tmaxY > maxY ? tmaxY : maxY; 

  }

  if(kLog){
    gPad->SetLogy();
    h->SetMaximum( 1. );
  }else{
    h->SetMaximum( maxY * 1.5);
  }
  
  h->SetMinimum( maxY * pow( 10, -orders_of_magn ) );

  h->GetXaxis()->SetNdivisions(515);

  h->GetXaxis()->SetTitleOffset( h->GetXaxis()->GetTitleOffset() * 1.1 );

  h->GetYaxis()->SetTitle("normalized to unit area");
  
  h->GetYaxis()->SetTitleOffset(   h->GetYaxis()->GetTitleOffset()*1.2 );

  Legend(vhist, vfrac, vtitles)->Draw();

  Atlas()->Draw();
  
  Algo()->Draw();

  MC()->Draw();

  Info(info)->Draw();

  double xl(0); double xr(0);

  FindRegionSigma(vhist[0], xl, xr, 1);


  double ymaxLine = vhist[0]->GetBinContent( vhist[0]->GetMaximumBin() ) *1.1; 

  TLine *l = new TLine(xl, ymaxLine, xr, ymaxLine);
  //  l->SetLineColor(kGray);
  l->Draw();

  TLine *ll = new TLine(xl, ymaxLine*.95, xl, ymaxLine*1.05);
  //  ll->SetLineColor(kGray);
  ll->Draw();

  TLine *lr = new TLine(xr, ymaxLine*.95, xr, ymaxLine*1.05);
  //  lr->SetLineColor(kGray);
  lr->Draw();


  TLatex *tt = new TLatex( xl+(xr-xl)/2. , ymaxLine*1.1, "#font[42]{68%}");
  tt->SetTextSize( tt->GetTextSize() * 0.5);
  tt->SetTextAlign(21);
  //  tt->SetTextColor(kGray);
  tt->Draw();
  


  gPad->RedrawAxis();

  if(kPNG) c->SaveAs( (outFile+".png").c_str());

  if(kEPS) c->SaveAs( (outFile+".eps").c_str());
  
}

bool ToDraw(TH1D *h){

  return h->GetEntries() > 0;
}

void FindRegionSigma(TH1D *h, double &xl, double &xr, int ns){

  double s = ns == 1 ? 0.6826 :
    ns == 2 ? 0.9545 : 
    ns == 3 ? 0.9973 :
    ns == 4 ? 0.9999 : 1;

  int imax = h->GetMaximumBin();
  
  double area(0);
  int i(0); int j; int k;
  while(area < s){
    j = imax -i;
    k = imax +i;
    area = h->Integral( j, k, "" );
    i++;
  }

  xl  = h->GetBinLowEdge(j);
  xr  = h->GetBinLowEdge(k) +  h->GetBinWidth(k);

  cout<<ns <<" sigma between "<<xl<<" and "<<xr<<", "<<i<<" bins away from bin "<<imax<<endl;
}
TLatex *Atlas(){

  TLatex *t = new TLatex( x_logo_left, y_top_level - 0.04, "#color[12]{#font[72]{ATLAS} #font[42]{Work in Progress}}");
  t->SetTextSize( t->GetTextSize() * 0.75);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLatex *Algo(){

  TLatex *t = new TLatex( x_algo_left, y_top_level -0.14, "#color[36]{#font[42]{PanTau} + #font[52]{Cell-Based}}");
  t->SetTextSize( t->GetTextSize() * 0.6);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLatex *MC(){

  TLatex *t = new TLatex( x_mc_left, y_top_level - 0.09, "#color[12]{#font[42]{MC12 Pythia8} #font[52]{Z^{0}, Z' #rightarrow #tau^{+}#tau^{-}}}");
  t->SetTextSize( t->GetTextSize() * 0.6);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLatex *Info(const string &s){

  TString text = "#font[42]{"+s+"}";
  TLatex *t = new TLatex( x_info_left, y_top_level - 0.20, text );
  t->SetTextSize( t->GetTextSize() * 0.65);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLegend *Legend(vector<TH1D*> &vh, vector<double> &vf, vector<string> &vt){

  int Total(0);
  for(int i = 0; i < (int)vh.size(); i++ ){
    if(ToDraw(vh[i]) ) Total++;
  }


  double dy = Total*0.0525;

  double legx0 = 0.125;
  double legx1 = x_legend_right;

  double legy1=  y_top_level;
  double legy0 = legy1 - dy;

  string header = "#font[22]{"+vt[0]+"}";

  TLegend *leg = new TLegend( legx0, legy0, legx1, legy1, NULL,"brNDC");
  leg->SetBorderSize(1);
  leg->SetLineColor(15);
  leg->SetLineStyle(1);
  leg->SetLineWidth(1);
  leg->SetFillColor(19);
  leg->SetFillStyle(3004);
  leg->SetTextSize( leg->GetTextSize()*rel_leg_font_size );

  leg->SetHeader(header.c_str());

  for(int i = 0; i < (int)vh.size(); i++ ){
    if(ToDraw(vh[i]) ) leg->AddEntry( vh[i], (vt[i+1] + "  " +num2str(vf[i]*100) + "%").c_str() , "l");
  }
  
  return leg;
}

void SetHistoStyles(vector<TH1D*> &v){

  for(int i = 0; i < (int)v.size(); i++ ){
    v[i]->SetLineColor( Color(i) );
    v[i]->SetLineStyle(1);
    v[i]->SetLineWidth(2);
    
  }

}

Color_t Color(int i){
  
  Color_t c(kBlack);
  if( i == 0) c = kBlack;
  else if( i == 1) c = kRed;//
  else if( i == 2) c = kBlue;
  else if( i == 3) c = kMagenta;//
  else if( i == 4) c = kGreen;
  else if( i == 5) c = kOrange;//
  else if( i == 6) c = kViolet;
  else if( i == 7) c = kYellow;//
  else if( i == 8) c = kAzure-8;
  else if( i == 9) c = kGray;//
  else if( i == 10) c = kOrange+3;
  else if( i == 11) c = kGreen+3;
  else {cout<<"Color - no color for "<<i<<endl;}

  return c;
}

std::vector<double> GetFracVec(std::vector<TH1D*> &vhist, bool kFirstIsRef, bool kNormHistos){

  //to do : if first is not the ref - then make a sum to create a ref AND push it first in the vector!

  if(kNormHistos){}

  vector<double> v;
  double frac;
  //double frac_percentage;
  if(kFirstIsRef){
    v.push_back(1);

    for(int i = 1; i < (int)vhist.size(); i++){
      frac = Fraction( vhist[i], vhist[0] ); cout<<i<<". "<<frac<<endl;
      Norm2Factor( vhist[i], frac );
      v.push_back(frac);
    }
    Norm2Area( vhist[0] );
  }


  double sum_of_elems =std::accumulate(v.begin()+1, v.end(), 0.);
  
  cout<<"Sum Frac_i = "<<sum_of_elems<<endl;

 
  return v;
}

bool StrHas(const string &str, const string &sub){

  std::size_t found = str.find(sub);

  if (found!=std::string::npos) return true;

  return false;
}

TFile *File(TString s){
  
  if(!s.Length()) s = "thisfile.root";

  return TFile::Open(s);

}

vector<TH1D*> GetHistoVec(TFile *f, vector<string>&v){

  vector<TH1D*> vH;
  for(vector<string>::iterator i = v.begin(); i != v.end(); i++){
    vH.push_back( Histo(f, *i) );
  }
  
  return vH; 
}

TH2D *Histo2(TFile *f, const string &s){

   return (TH2D*)f->Get( s.c_str() );

}

TH1D *Histo(TFile *f, const string &s){

  TH1D *h = (TH1D*)f->Get( s.c_str() );

  string type =
    StrHas(s, "reso_rel") ? "rel_res" :
    StrHas(s, "eta") ? "eta" :
    "";

  if(!h){cerr<<"unable to obtain "<<s<<" from file, returning empty histo of type "<<type<<endl; return EmptyHisto(type);}

  if(!h->GetEntries() ) {cerr<<"empty "<<s<<" from file, returning empty histo of type "<<type<<endl; return EmptyHisto(type);}

  if(kShowOverflow) return OverflowHisto(h, type);
		      
  return h;
}

TH1D *OverflowHisto(TH1D *h, const string &s){
  
  TH1D *hn = EmptyHisto(s);
  int j(1);
  for(int i = 1; i <= h->GetNbinsX() + 1; i++){//+1 : include overflow
    hn->SetBinContent(j, h->GetBinContent(i) );
    hn->SetBinError(j, h->GetBinError(i) );
    j++;
  }

  return hn;

}

TH1D *EmptyHisto(const string &s){

  static int i;
  string name = "histo"+int2str(i++);


  if(s=="rel_res"){ 
    string t_res_rel = "(p_{T}^{reco} - p_{T}^{true})/p_{T}^{true}"; int n_res_rel = 101; double l_res_rel = -1.01; double r_res_rel = 1.01;
    if(kShowOverflow){
      double bw = (r_res_rel - l_res_rel)/n_res_rel;
      n_res_rel +=1;
      r_res_rel += bw;
    }
    //cout<<"empty histo "<<n_res_rel<<" "<<l_res_rel<<" "<<r_res_rel<<endl;

    TH1D*h = new TH1D(name.c_str(),"", n_res_rel, l_res_rel, r_res_rel);
    h->GetXaxis()->SetTitle( t_res_rel.c_str() );
    return h;
  } 

  int n_eta = 102; double l_eta = -2.55; double r_eta = 2.55;
  if(s=="eta") return new TH1D(name.c_str(),"", n_eta, l_eta, r_eta);

  cerr<<"Unknown type of empty histo "<<s<<endl;

  return NULL;
}


double Fraction(TH1 *h, TH1 *g){
  double ref =  g->Integral();
  if(!ref) {cerr<<"reference plot has zero area"<<endl; return 0;}
  return h->Integral() / ref;
}

double Percentage(TH1 *h, TH1 *g){
  return Fraction(h,g)*100;
}

void Norm2Area(TH1 *h){

  h->Scale( 1./h->Integral() );
}

void Norm2Factor(TH1 *h, double x){

  h->Scale( x/h->Integral() );
}

string int2str(int n){ 
  std::ostringstream stm; stm << n; 
  return stm.str(); 
}

string num2str(double x){

  char n[12];

  sprintf(n,"%.2f", x);


  return char2str(n);
}

string  char2str(char *c){
  stringstream ss; string s;  ss << c; ss >> s; 
  return s; 
}

TCanvas *Canvas(){

  static int j;
  string name = "canvas"+int2str(j++);
  TCanvas *c =  new TCanvas(name.c_str(), "", 20, 20, 900, 800);
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
  c->SetTopMargin(0.025);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  return c;
}

