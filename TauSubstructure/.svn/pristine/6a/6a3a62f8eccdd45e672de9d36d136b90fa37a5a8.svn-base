#include "common.C"

#include "TColor.h"


void Plot_PurityMatrix(TString s, TString ptRange, TString info);
void Plot_PurityMatrixLoop(TString s);
void PrintContent(TH2D*h);
void RowNorm(TH2D *h);
void SetLabels(TH2D *h);
void Fractions(TH2D *h, double &fall, double &f1p, double &f3p, double&f13);
void PrintFractions(TH2D*h, const string &s);
void DrawDiagFrac(const string &s, double f, double x, double y );
TLatex *DrawAlgo(double x, double y);
TLatex *DrawAtlas(double x, double y);
TLatex *DrawMC(double x, double y);
TLatex *DrawMatrix(double x, double y);
string HpTrange(unsigned int i, vector<int> &m_vec_pt_bins);
string GetStringFromInt(int n);

void Plot_PurityMatrixLoop(TString s){

  //classification rates
  const int arrPt[] = {0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 100, 150, 500, 1000};
  vector<int>  m_vec_pt_bins   (arrPt, arrPt + sizeof(arrPt) / sizeof(arrPt[0]) );

  for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
    Plot_PurityMatrix(s, HpTrange(ipt, m_vec_pt_bins), "bin" );
  }


}


void Plot_PurityMatrix(TString s, TString ptRange, TString info){

  string dir = "results/";
  string ptRange_str = ptRange.Length() ? ptRange.Data() : "pTall"; 
  string name = "matrix_"+ptRange_str+"_"+info.Data();

  TFile *f = TFile::Open(s);

  
  TCanvas *c =  new TCanvas( ptRange, "", 20, 20, 700, 600);
  //c->Range(0,0,1,1);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  //c->SetTickx(1);
  //c->SetTicky(1);
  //c->SetRightMargin(0.025);
  //c->SetLeftMargin(0.1);
  c->SetTopMargin(0.025);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);

  c->cd();
  
  string hs;

  if(!ptRange.Length()) hs = "tau_pan_decay_mode_classification";
  else{ cout<<"pT range "<<ptRange<<endl; hs = "tau_pan_"+ptRange+"_decay_mode_classification";}

  TH2D *h = Histo2(f, hs);

  if(!h) return;

  int nd = 505;
  h->GetXaxis()->SetNdivisions(nd);
  h->GetYaxis()->SetNdivisions(nd);

  double rel_label_offset = 1.2;
  h->GetXaxis()->SetTitleOffset( h->GetXaxis()->GetTitleOffset( )*rel_label_offset );
  h->GetYaxis()->SetTitleOffset( h->GetYaxis()->GetTitleOffset( )*rel_label_offset );

  RowNorm(h);

  int nb=100;  
  /*
  const int Number = 3;
  double Red[Number]    = { 1.00, 0.00, 0.00};
  double Green[Number]  = { 0.00, 1.00, 0.00};
  double Blue[Number]   = { 1.00, 0.00, 1.00};
  double Length[Number] = { 0.00, 0.50, 1.00 };
  TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
  */  

  /*
  const int Number = 3;
  double Red[Number]    = { 0.80, 0.00, 0.00};
  double Green[Number]  = { 0.00, 0.00, 0.00};
  double Blue[Number]   = { 0.70, 0.00, 0.00};
  double Length[Number] = { 0.00, 0.95, 1.00 };
  TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
  */
  const int Number = 4;
  double Red[Number]    = { 1.00, 0.80, 0.00, 0.00};
  double Green[Number]  = { 0.00, 0.00, 0.00, 0.00};
  double Blue[Number]   = { 1.00, 0.70, 0.00, 0.00};
  double Length[Number] = { 0.00, 0.10, 0.95, 1.00 };
  TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);


  h->SetContour(nb);

  //gStyle->SetPalette(55);
  int maxB = h->GetMaximumBin();
  int minB = h->GetMinimumBin();
  double zmin = h->GetBinContent(minB);
  double zmax =  h->GetBinContent(maxB); zmax = (100 - zmax)/2. + zmax;
  //double zmin = 0;
  //double zmax = 1;
  h->GetZaxis()->SetRangeUser(zmin, zmax);
  //h->SetContour(2000);


  h->Draw("colz");

  PrintContent(h);

  SetLabels(h);

  PrintFractions(h, ptRange.Data());
  
  DrawAtlas(0.15, 0.92)->Draw();
  DrawMatrix(0.15, 0.85)->Draw();

  DrawAlgo(0.6, 0.92)->Draw();
  DrawMC(0.6, 0.85)->Draw();

  c->SaveAs( (dir + name + ".png").c_str() );

}

void PrintFractions(TH2D*h, const string &pT){


  double fall; double f1p; double f3p; double f1p3p;
  Fractions(h, fall, f1p, f3p, f1p3p);
  cout<<"Diagonal fractions "<<fall<<" "<<f1p<<" "<<f3p<<" "<<f1p3p<<endl;

  TLatex *tt = new TLatex( 6.25, 5.5, "#splitline{Diagonal}{fractions}");
  tt->SetTextSize( tt->GetTextSize()*0.6);
  tt->SetTextFont(42);
  tt->Draw();

  DrawDiagFrac("All", fall, 6.25, 4.5 );
  DrawDiagFrac("1p+3p", f1p3p, 6.25, 3.5 );
  DrawDiagFrac("1p", f1p, 6.25, 2.5 );
  DrawDiagFrac("3p", f3p, 6.25, 1.5 );


  cout<<"\ndouble f"<<pT<<"[4] = {"<<fall<<", "<<f1p3p<<", "<<f1p<<", "<<f3p<<"};"<<endl;;

}

void DrawDiagFrac(const string &s, double f, double x, double y ){

  double relSize = 0.55;
  char m[12];
  double perc = f*100;
  sprintf(m,"%.2f", perc);
  string bc_str = char2str(m);
  TLatex *tt = new TLatex( x, y, ("#font[62]{"+s+"}: "+bc_str+"%").c_str());
  tt->SetTextSize( tt->GetTextSize()*relSize);
  tt->SetTextFont(42);
  tt->Draw();

}

void Fractions(TH2D *h, double &fall, double &f1p, double &f3p, double &f1p3p){

  double sum1p(0);
  double sum3p(0);
  double sum1p3p(0);
  double sum(0);

  double diag1p(0);
  double diag3p(0);
  double diag1p3p(0);
  double diag(0);
  
  for(int iy = 1; iy <= h->GetNbinsY(); iy++){   
    for(int ix = 1; ix <= h->GetNbinsX(); ix++){
      
      double bc = h->GetBinContent(ix, iy);

      if( iy <=3 && ix <=3 ){ sum1p+=bc;  if(iy == ix) diag1p += bc; }
      if( (iy == 4 || iy ==5) &&  (ix == 4 || ix ==5)  ){ sum3p+= bc; if(iy == ix) diag3p += bc; } 
      if( iy <=5 && ix <=5 ){ sum1p3p+=bc;  if(iy == ix) diag1p3p += bc; }
      sum += h->GetBinContent(ix, iy); if(iy == ix) diag += bc; 
    }
  }

  fall = diag/sum;
  f1p = diag1p/sum1p;
  f3p = diag3p/sum3p;
  f1p3p = diag1p3p/sum1p3p;
}
void RowNorm(TH2D *h){

  for(int iy = 1; iy <= h->GetNbinsY(); iy++){

    double sum(0);
    for(int ix = 1; ix <= h->GetNbinsX(); ix++){
      sum+= h->GetBinContent(ix, iy);
    }

    for(int ix = 1; ix <= h->GetNbinsX(); ix++){
      double bc = h->GetBinContent(ix, iy);
      if(ix > 6 || iy > 6 ) h->SetBinContent(ix, iy, 0);
      else  h->SetBinContent(ix, iy, bc/sum*100);
    }

  }

}

void PrintContent(TH2D*h){


  for(int iy = 1; iy <= h->GetNbinsY(); iy++){   
    for(int ix = 1; ix <= h->GetNbinsX(); ix++){
      double bc = h->GetBinContent(ix, iy);
      if(bc>0){
	//cout<<ix<<" "<<iy<<" "<<bc<<endl;
	char mchar[12];
	double perc = bc;
        sprintf(mchar,"%.2f", perc);
        string bc_str = char2str(mchar);
        TLatex *tt = new TLatex( ix-0.85, iy-0.75, (bc_str+"%").c_str());
        tt->SetTextSize( tt->GetTextSize()*0.55);
        tt->SetTextFont(42);
        if( fabs(perc)>50 ) tt->SetTextColor(0);
        tt->Draw();
      }
    }
  }


}

void SetLabels(TH2D *h){
  h->GetYaxis()->SetLabelSize(0);
  h->GetXaxis()->SetLabelSize(0);
  double relsize = 0.85;
  double shift = 0.1;
  double gap = -0.2;
  double gapx = -0.4;
  int i;

  i = 0;
  TLatex *tp = new TLatex( i + shift, 0 + gapx, "1p0n");
  tp->SetTextSize( tp->GetTextSize()*relsize);
  tp->SetTextFont(42);
  tp->Draw("same");

  i = 1;
  TLatex *tq = new TLatex( i + shift, 0 + gapx, "1p1n");
  tq->SetTextSize( tq->GetTextSize()*relsize);
  tq->SetTextFont(42);
  tq->Draw("same");

  i = 2;
  TLatex *tqr = new TLatex( i + shift, 0 + gapx, "1pXn");
  tqr->SetTextSize( tqr->GetTextSize()*relsize);
  tqr->SetTextFont(42);
  tqr->Draw("same");

  i = 3;
  TLatex *tqra = new TLatex( i + shift, 0 + gapx, "3p0n");
  tqra->SetTextSize( tqra->GetTextSize()*relsize);
  tqra->SetTextFont(42);
  tqra->Draw("same");

  i = 4;
  TLatex *tqraS = new TLatex( i + shift, 0 + gapx, "3pXn");
  tqraS->SetTextSize( tqraS->GetTextSize()*relsize);
  tqraS->SetTextFont(42);
  tqraS->Draw("same");

  i = 5;
  TLatex *t5 = new TLatex( i + shift, 0 + gapx, "Other");
  t5->SetTextSize( t5->GetTextSize()*relsize);
  t5->SetTextFont(42);
  t5->Draw("same");

  i=0;
  TLatex *t1 = new TLatex( 0 + gap, i + shift, "1p0n");
  t1->SetTextSize( t1->GetTextSize()*relsize);
  t1->SetTextFont(42);
  t1->SetTextAngle(90);
  t1->Draw("same");


  i=1;
  TLatex *tw1 = new TLatex( 0 + gap, i + shift, "1p1n");
  tw1->SetTextSize( tw1->GetTextSize()*relsize);
  tw1->SetTextFont(42);
  tw1->SetTextAngle(90);
  tw1->Draw("same");

  i=2;
  TLatex *tw1b = new TLatex( 0 + gap, i + shift, "1pXn");
  tw1b->SetTextSize( tw1b->GetTextSize()*relsize);
  tw1b->SetTextFont(42);
  tw1b->SetTextAngle(90);
  tw1b->Draw("same");

  i=3;
  TLatex *to = new TLatex( 0 + gap, i + shift, "3p0n");
  to->SetTextSize( to->GetTextSize()*relsize);
  to->SetTextFont(42);
  to->SetTextAngle(90);
  to->Draw("same");

  i=4;
  TLatex *te = new TLatex( 0 + gap, i + shift, "3pXn");
  te->SetTextSize( te->GetTextSize()*relsize);
  te->SetTextFont(42);
  te->SetTextAngle(90);
  te->Draw("same");

  i=5;
  TLatex *te2 = new TLatex( 0 + gap, i + shift, "Other");
  te2->SetTextSize( te2->GetTextSize()*relsize);
  te2->SetTextFont(42);
  te2->SetTextAngle(90);
  te2->Draw("same");
  
}

TLatex *DrawAtlas(double x, double y){

  TLatex *t = new TLatex(x,y, "#color[12]{#font[72]{ATLAS} #font[42]{Work in Progress}}");
  t->SetTextSize( t->GetTextSize() * 0.75);
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

TLatex *DrawMC(double x, double y){

  TLatex *t = new TLatex( x,y, "#color[12]{#font[42]{MC12 Pythia8} #font[52]{Z^{0} #rightarrow #tau^{+}#tau^{-}}}");
  t->SetTextSize( t->GetTextSize() * 0.65);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

TLatex *DrawMatrix(double x, double y){

  TLatex *t = new TLatex( x,y, "#font[42]{Purity Matrix - row-nornalized}");
  t->SetTextSize( t->GetTextSize() * 0.65);
  t->SetTextAlign(11);
  t->SetNDC();
  return t;
}

string HpTrange(unsigned int i, vector<int> &m_vec_pt_bins){
  if(i < m_vec_pt_bins.size() ) return GetStringFromInt( m_vec_pt_bins.at(i) ) + "_" + GetStringFromInt( m_vec_pt_bins.at(i+1) );
  else cerr<<"TauMain::HpTrange - bin index "<<i<<" can't be greater than vector's size "<<m_vec_pt_bins.size()<<endl;

  return "";
}

string GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }

