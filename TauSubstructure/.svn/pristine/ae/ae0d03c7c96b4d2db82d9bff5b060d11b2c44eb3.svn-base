
#include <string>
#include <vector>



void Plot_TrkCalo_pulls(){

  TFile *f = TFile::Open("../results/V61/tau4mom.root");

  string var; string yTitle; string versus; double fitx;

  //=================================================
  fitx = 3; 

  //versus = "eta";
  versus = "pt";
 
  //var = "qoverp"; yTitle = "#frac{|q/p|^{reco} - |q/p|^{truth}}{#sigma_{|q/p|}}    [#times #sigma]";
  var = "energy"; yTitle = "#frac{E^{reco} - E^{truth}}{#sigma_{E}}   [#times #sigma]";
  //=================================================

  string xTitle;
  std::vector<std::string> v;
  std::vector<std::string> V;
  if(versus == "eta"){
    v.push_back(("test_rec_track_0_0p00_0p30_pull_"+var).c_str()); V.push_back("0.0-0.3");
    v.push_back(("test_rec_track_0_0p30_0p80_pull_"+var).c_str()); V.push_back("0.3-0.8");
    v.push_back(("test_rec_track_0_0p80_1p00_pull_"+var).c_str()); V.push_back("0.8-1.0");
    v.push_back(("test_rec_track_0_1p00_1p20_pull_"+var).c_str()); V.push_back("1.0-1.2");
    v.push_back(("test_rec_track_0_1p20_1p60_pull_"+var).c_str()); V.push_back("1.2-1.6");
    v.push_back(("test_rec_track_0_1p60_2p10_pull_"+var).c_str()); V.push_back("1.6-2.1");
    v.push_back(("test_rec_track_0_2p10_2p50_pull_"+var).c_str()); V.push_back("2.1-2.5");
    xTitle = "|#eta|";
  }else if(versus == "pt"){
    v.push_back(("test_rec_track_0_15_20_pull_"+var).c_str()); V.push_back("15-20");
    v.push_back(("test_rec_track_0_20_25_pull_"+var).c_str()); V.push_back("20-25");
    v.push_back(("test_rec_track_0_25_30_pull_"+var).c_str()); V.push_back("25-30");
    v.push_back(("test_rec_track_0_30_40_pull_"+var).c_str()); V.push_back("30-40");
    v.push_back(("test_rec_track_0_40_50_pull_"+var).c_str()); V.push_back("40-50");
    v.push_back(("test_rec_track_0_50_60_pull_"+var).c_str()); V.push_back("50-60");
    v.push_back(("test_rec_track_0_60_70_pull_"+var).c_str()); V.push_back("60-70");
    v.push_back(("test_rec_track_0_70_80_pull_"+var).c_str()); V.push_back("70-80");
    v.push_back(("test_rec_track_0_80_90_pull_"+var).c_str()); V.push_back("70-90");
    v.push_back(("test_rec_track_0_90_100_pull_"+var).c_str()); V.push_back("90-100");
    v.push_back(("test_rec_track_0_100_120_pull_"+var).c_str()); V.push_back("100-120");
    v.push_back(("test_rec_track_0_120_150_pull_"+var).c_str()); V.push_back("120-150");
    v.push_back(("test_rec_track_0_150_200_pull_"+var).c_str()); V.push_back("150-200");
    xTitle = "p_{T} [GeV]";
  }else{
    cout<<"unknown variable "<<versus<<endl;
  }

  const int n = v.size();

  double y[n];  double dy[n];

  TF1 *fit = new TF1("fit", "gaus", -fitx, fitx);

  TCanvas *c1 = new TCanvas("c1", "", 50, 50, 1200, 600);
  if(n<=8) c1->Divide(4,2);
  else if(n<=16) c1->Divide(4,4);
  else{}

  TGraphAsymmErrors  *gr = new TGraphAsymmErrors(n);

  int i(1);
  for(vector<std::string>::iterator it = v.begin(); it != v.end(); it++){
    c1->cd(i);

    TH1D *h = (TH1D*)f->Get( (*it).c_str() );
    if(!h){cerr<<"can't get "<<*it<<endl; break;}


    h->GetYaxis()->SetTitle("");

    h->Fit(fit, "R");
    double par[3];
    fit->GetParameters(par);
    cout<<*it<<" mean= "<<par[1]<<" sigma= "<<par[2]<<endl;

    //y[i] = par[1];  dy[i] = par[2];

    gr->SetPoint(i, i, par[1]);
    gr->SetPointError(i, 0, 0, par[2], par[2]);

    i++;
  }


  gr->RemovePoint(0);

  c1->Update();

  TCanvas *c2 = new TCanvas("c2", "", 50, 50, 900, 300);
  c2->cd();

  c2->SetBottomMargin(   c2->GetBottomMargin( ) * 1.5);
  c2->SetRightMargin(   c2->GetRightMargin( ) * 0.3);

  TH1D *hnull = new TH1D("hnull", "", n+1, 0, n+1);

  hnull->Draw();

  hnull->GetYaxis()->SetTitle(yTitle.c_str());
  hnull->GetXaxis()->SetTitle(xTitle.c_str());
  hnull->GetYaxis()->SetLabelSize(   hnull->GetYaxis()->GetLabelSize() *1.3);
  hnull->GetYaxis()->SetTitleSize(   hnull->GetYaxis()->GetTitleSize() *1.75);
  hnull->GetXaxis()->SetTitleSize(   hnull->GetXaxis()->GetTitleSize() *1.75);
  hnull->GetYaxis()->SetTitleOffset(   hnull->GetYaxis()->GetTitleOffset() * 0.54);
  hnull->GetXaxis()->SetTitleOffset(   hnull->GetXaxis()->GetTitleOffset() * 1.1);

  hnull->GetXaxis()->SetLabelSize(0);

  gStyle->SetOptStat(0);

  hnull->SetMaximum(3);
  hnull->SetMinimum(-3);
  hnull->GetXaxis()->SetRangeUser(0, n+1);

  gr->SetLineWidth(3);
  gr->SetMarkerStyle(21);





  TBox *b2 = new TBox(0, -2, n+1, 2);
  b2->SetFillColor(kGreen-7);
  b2->Draw();

  TBox *b1 = new TBox(0, -1, n+1, 1);
  b1->SetFillColor(kYellow-7);
  b1->Draw();

  TLine *l = new TLine(0, 0, n+1, 0);
  l->SetLineColor(kOrange);
  l->SetLineStyle(7);
  l->Draw();

  gPad->SetTickx(1);  gPad->SetTicky(1);

  gPad->RedrawAxis();

  gr->Draw("PZ");

  i=1;
  for(vector<std::string>::iterator it = V.begin(); it != V.end(); it++){
    TLatex *lat = new TLatex(i++ - 0.25, -3.5, (*it).c_str() );
    lat->SetTextFont(42);
    lat->SetTextAlign(11);
    lat->Draw( );
  }





}
