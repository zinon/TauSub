
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

void Plot_TauTrkCompatibility(TString filename){

  int nPlots = 10;
  TFile *f = TFile::Open(filename);

  for(int i = 0; i <= nPlots, i++)
    Run_TauTrkCompatibility(f, i);

}

void Plot_TauTrkCompatibility(TString filename, int c){

  TFile *f = TFile::Open(filename);
  Run_TauTrkCompatibility(f, c);
}

void Run_TauTrkCompatibility(TFile *f, int c){
  

  if(!f || f->IsZombie() ){cerr<<"unable to open file "<<endl; return;}

  string mode = "1p0n";

  //compare PanTau with PanTau-tauRec with track-calo consistency 
  if( c == -1){ 

    double surf(0);
    TH1D *h0 = Harea(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel", 1, kGray, surf);
    h0->Draw();

    Hnorm(f, "tau_pan_"+mode+"_true_"+mode+"_kaon_decay_0_reso_rel", kGreen-2, 0, surf)->Draw("same");
    Hnorm(f, "tau_pan_"+mode+"_true_"+mode+"_kaon_decay_1_reso_rel", kRed, 0, surf)->Draw("same");
    //    Hnorm(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_reso_rel", kOrange, 0, surf)->Draw("same");
    //Hnorm(f, "tau_pan_"+mode+"_true_"+mode+"_charged_kaon_decay_1_reso_rel", kOrange, 0, surf)->Draw("same");

    h0->SetMinimum(1e-6);

    gPad->SetTicks(1,1);
    gPad->SetLogy();
  }

  //check if the leading PanTau track is identified with a reco track 
  if(c == 0){    
    H(f, "test_lead_recoTrk_over_panTrk", 1)->Draw();
    gPad->SetLogy();
   }

  //compare PanTau with PanTau-tauRec with track-calo consistency 
  if( c == 1){ 

    double surf(0);
    Harea(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel", 1, kGray, surf)->Draw();
    

    double area(0);
    Harea(f, "test_r"+mode+"_t"+mode+"_tau_pan_compatible_trk_pT_reso_rel", kMagenta, kMagenta-10, area)->Draw("same");
    Hnorm(f, "test_r"+mode+"_t"+mode+"_kaon_decay_0_tau_pan_compatible_trk_pT_reso_rel", kGreen, kGreen -10, area)->Draw("same");
    Hnorm(f, "test_r"+mode+"_t"+mode+"_kaon_decay_1_tau_pan_compatible_trk_pT_reso_rel", kRed, area)->Draw("same");

    Hnorm(f, "tau_pan_"+mode+"_true_"+mode+"_kaon_decay_0_reso_rel", kBlue, 0, surf)->Draw("same");

    gPad->SetLogy();
  }

  //compare PanTau with PanTau-tauRec with track-calo consistency  - inclusive 1p0n
  if( c == 2){ 

    double surf(0);
    TH1D *h0 = Harea(f, "tau_pan_"+mode+"_reso_rel", kBlack, kGray, surf);
    h0->Draw();

    double area(0);
    Harea(f, "test_r"+mode+"_tau_pan_compatible_trk_pT_reso_rel", kBlue, kBlue-8, area)->Draw("same");
    Hnorm(f, "test_r"+mode+"_kaon_decay_0_tau_pan_compatible_trk_pT_reso_rel", kGreen -2, area)->Draw("same");
    Hnorm(f, "test_r"+mode+"_kaon_decay_1_tau_pan_compatible_trk_pT_reso_rel", kRed, area)->Draw("same");

    //Hnorm(f, "tau_pan_"+mode+"_true_"+mode+"_kaon_decay_0_reso_rel", kBlue, 0, surf)->Draw("same");

    h0->SetMinimum(1e-6);

    gPad->SetLogy();
  }

  //1d plot: reco-truth track resolution
  if( c == 3){
    H(f, "test_r"+mode+"_t"+mode+"_pan_track_0_matched_truth_reso_rel", kAzure)->Draw("");
    //H(f, "tau_pan_"+mode+"_true_"+mode+"_TauTrack_RecoTruth_DpTres", kOrange)->Draw("same");
    gPad->SetLogy();
  }

  //2d plot: reco-truth track resolution vs truth pT, eta, dR
  if( c == 4){
    TCanvas *can = new TCanvas("can","", 20, 20, 1500, 500);
    can->Divide(3,1);
    can->cd(1);
    H2(f, "test_r"+mode+"_t"+mode+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_pT", kAzure)->Draw("colz");
    gStyle->SetNumberContours(999);

    can->cd(2);
    H2(f, "test_r"+mode+"_t"+mode+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_Eta", kAzure)->Draw("");
    gStyle->SetNumberContours(999);
 
    can->cd(3);
    H2(f, "test_r"+mode+"_t"+mode+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_dR", kAzure)->Draw("");
    gStyle->SetNumberContours(999);

  }

  //1d plot:  resolution PanTau vs PanTau with track quality
  if( c == 5){
    //H(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel", 1)->Draw();
    //H(f, "test_trk_quality_"+mode+"_true_"+mode+"_reso_rel", kOrange)->Draw("same");

    H(f, "test_r"+mode+"_t"+mode+"_pan_track_0_matched_truth_reso_rel", kAzure)->Draw("same");
    H(f, "test_trk_quality_r"+mode+"_t"+mode+"_pan_track_0_matched_truth_reso_rel", kOrange)->Draw("same");

    gPad->SetLogy();
  }

  //2d plot: reco-truth track resolution vs PanTau resolution
  if( c == 6){//#
    TCanvas *can = new TCanvas("can","", 20, 20, 1550, 750);
    can->Divide(5,2);

    can->cd(1);
    H2(f, "test_r"+mode+"_t"+mode+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

    //
    can->cd(2);
    H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_0_pan_track_0_matched_truth_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

    can->cd(3);
    H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_1_pan_track_0_matched_truth_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

    can->cd(4);
    H2(f, "test_r"+mode+"_t"+mode+"_charged_kaon_decay_1_pan_track_0_matched_truth_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

    can->cd(5);
    H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_pan_track_0_matched_truth_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

    //
    string source = "PI";
    //
    can->cd(7);
    H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_0_pan_track_0_matched_truth_trk_orig_"+source+"_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

    can->cd(8);
    H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_1_pan_track_0_matched_truth_trk_orig_"+source+"_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

    can->cd(9);
    H2(f, "test_r"+mode+"_t"+mode+"_charged_kaon_decay_1_pan_track_0_matched_truth_trk_orig_"+source+"_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

    can->cd(10);
    H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_pan_track_0_matched_truth_trk_orig_"+source+"_reso_rel_vs_reso_rel", kAzure)->Draw("colz");

  }

  //2d plot : PanTau+tauRec trk compatibility vs pT true vis
  if( c == 7){
    TCanvas *can = new TCanvas("can","", 20, 20, 1000, 500);
    can->Divide(2,1);
    can->cd(1);
    H2(f, "test_r"+mode+"_t"+mode+"_tau_pan_compatible_trk_pT_reso_rel_vs_pt_true", kAzure)->Draw("colz");
    can->cd(2);
    H2(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel_vs_pt_true", kAzure)->Draw("colz");
  }

  //1d plot: reco-truth dR
  if( c == 8){
    H(f, "tau_pan_"+mode+"_true_"+mode+"_TauTrack_RecoTruth_DR", kAzure)->Draw("");
    gPad->SetLogy();
  }

  //1d plot: reco-truth track resolution
  if( c == 9){
    H(f, "test_r"+mode+"_t"+mode+"_pan_track_0_pT_over_rec_tau_pT", kBlack)->Draw();
    H(f, "test_r"+mode+"_t"+mode+"_pan_track_0_pT_over_pan_tau_pT", kGray)->Draw("same");

    H(f, "test_r"+mode+"_t"+mode+"_matched_trk_parent_1_pan_track_0_pT_over_rec_tau_pT", kOrange)->Draw("same");
    //    H(f, "test_r"+mode+"_t"+mode+"_matched_trk_parent_0_pan_track_0_pT_over_rec_tau_pT", kGreen)->Draw("same");

    gPad->SetLogy();
  }

  //1d plot: PanTau resolution for track origin
  if( c == 10){
    H(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel", kBlack)->Draw("");
    H(f, "tau_pan_"+mode+"_true_"+mode+"_matched_trk_parent_1_reso_rel", kAzure+2)->Draw("same");
    H(f, "tau_pan_"+mode+"_true_"+mode+"_matched_trk_parent_0_reso_rel", kOrange)->Draw("same");
    gPad->SetLogy();
  }

  //1d plot: PanTau trk/ rec trk ratio for track origin
  if( c == 11){
    H(f, "test_r"+mode+"_t"+mode+"_pan_track_0_pT_over_rec_tau_pT", 1)->Draw("same");
    H(f, "test_r"+mode+"_t"+mode+"_matched_trk_parent_1_pan_track_0_pT_over_rec_tau_pT", kOrange)->Draw("same");
    // H(f, "test_r"+mode+"_t"+mode+"_matched_trk_parent_0_pan_track_0_pT_over_rec_tau_pT", kOrange)->Draw("same");
    gPad->SetLogy();
  }
  //1d plot: reco-truth track resolution Vs pT trk reco / pT tau rec
  if( c == 12){
    H2(f, "test_r"+mode+"_t"+mode+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure)->Draw("");
  }

  //2d plot: PanTau resolution Vs pT trk reco / pT tau rec
  if( c == 13){
    TCanvas *can = new TCanvas("can","", 20, 20, 1500, 500);
    can->Divide(3,1);

    can->cd(1);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");

    TLine *l = new TLine(-1, 0.5, 1, 0.5);
    l->SetLineStyle(7);
    l->SetLineColor(2);
    l->SetLineWidth(2);
    l->Draw();

    TLine *l7 = new TLine(-1, 0.7, 1, 0.7);
    l7->SetLineStyle(7);
    l7->SetLineColor(kOrange);
    l7->SetLineWidth(2);
    l7->Draw();

    TLine *lt = new TLine(-1, 5, 1, 5);
    lt->SetLineStyle(7);
    lt->SetLineColor(1);
    lt->SetLineWidth(2);
    lt->Draw();

    can->cd(2);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_1_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");
    l->Draw();

    can->cd(3);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_0_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");
    l->Draw();
  }

  //2d plot: PanTau resolution Vs pT trk reco / pT tau rec  - disentagle kaon decays 
  if( c == 14){
    TCanvas *can = new TCanvas("can","", 20, 20, 1000, 850);
    can->Divide(2,2);

    TLine *l = new TLine(-1, 0.5, 1, 0.5);
    l->SetLineStyle(7);
    l->SetLineColor(2);
    l->SetLineWidth(2);

    TLine *l7 = new TLine(-1, 0.7, 1, 0.7);
    l7->SetLineStyle(7);
    l7->SetLineColor(kOrange);
    l7->SetLineWidth(2);

    TLine *lt = new TLine(-1, 5, 1, 5);
    lt->SetLineStyle(7);
    lt->SetLineColor(1);
    lt->SetLineWidth(2);


    can->cd(1);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_charged_kaon_decay_1_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    h->Draw("colz");
    l->Draw(); l7->Draw();

    can->cd(2);
    TH2D *hh = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    hh->GetYaxis()->SetRangeUser(0,6);
    hh->Draw("colz");
    l->Draw(); l7->Draw();

    can->cd(3);
    TH2D *h3 = H2(f, "test_r"+mode+"_t"+mode+"_charged_kaon_decay_0_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h3->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    h3->Draw("colz");
    l->Draw(); l7->Draw();

    can->cd(4);
    TH2D *h4 = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_0_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h4->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    h4->Draw("colz");
    l->Draw(); l7->Draw();

  }

  //2d plot: PanTau pT Vs pT trk reco / pT tau rec
  if( c == 15){
    TCanvas *can = new TCanvas("can","", 20, 20, 1500, 800);
    can->Divide(3,2);

    can->cd(1);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");

    TLine *l = new TLine(0, 0.5, 200, 0.5);
    l->SetLineStyle(7);
    l->SetLineColor(2);
    l->SetLineWidth(2);
    l->Draw();

    can->cd(2);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_1_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");

    l->Draw();

    can->cd(3);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_0_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");

    l->Draw();

    can->cd(5);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_charged_kaon_decay_1_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");

    l->Draw();

    can->cd(6);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");

    l->Draw();


  }


  //2d plot: PanTau pT Vs pT trk reco / pT tau rec
  if( c == 16){
    TCanvas *can = new TCanvas("can","", 20, 20, 1500, 800);
    can->Divide(3,2);

    can->cd(1);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");

    TLine *l = new TLine(0, 0.5, 200, 0.5);
    l->SetLineStyle(7);
    l->SetLineColor(2);
    l->SetLineWidth(2);
    l->Draw();

    can->cd(2);
   TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_1_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");
    l->Draw();

    can->cd(3);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_kaon_decay_0_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");
    l->Draw();

    can->cd(5);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_charged_kaon_decay_1_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");
    l->Draw();

    can->cd(6);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_0_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    gStyle->SetNumberContours(999);
    h->Draw("colz");
    l->Draw();

  }


  //1d resolution - kaons
  if(c == 17){

    double area(0);
    Harea(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel", kBlack, kGray, area)->Draw("");

    Hnorm(f, "tau_pan_"+mode+"_true_"+mode+"_kaon_decay_1_reso_rel", kGreen, kGreen -10, area)->Draw("same");
    gPad->SetGrid(1,1);
    gPad->SetLogy();

    Hnorm(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_PanTau_only_fail_reso_rel", kRed, 0,  area)->Draw("same");
    Hnorm(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_PanTau_only_pass_reso_rel", kAzure, 0,  area)->Draw("same");
    
  }



  //1d tauRec and PanTau resolution plots for passing and failing the consistency requirement
  if( c == 18){
    TCanvas *can = new TCanvas("can","", 20, 20, 1000, 500);
    can->Divide(2,1);
    can->cd(1);
    H(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel", 1)->Draw();
    H(f, "test_r"+mode+"_t"+mode+"_tau_pan_compatible_trk_pT_reso_rel", kRed)->Draw("same");
    H(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_PanTau_only_pass_reso_rel", kAzure)->Draw("same");
    H(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_PanTau_only_fail_reso_rel", kOrange)->Draw("same");
    gPad->SetLogy();

    can->cd(2);
    H(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel", 1)->Draw();
    H(f, "test_r"+mode+"_t"+mode+"_tau_pan_compatible_trk_pT_reso_rel", kRed)->Draw("same");
    H(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_tauRec_only_pass_reso_rel", kAzure)->Draw("same");
    H(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_tauRec_only_fail_reso_rel", kOrange)->Draw("same");

    gPad->SetLogy();
  }

  //1d same as above but more clear: pass and fail refer to the trk-tau consistency requirement
  if( c == 19){
     H(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel", 1)->Draw();

     H(f, "test_r"+mode+"_t"+mode+"_tau_pan_compatible_trk_pT_reso_rel", kRed)->Draw("same");

     H(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_PanTau_only_pass_reso_rel", kAzure)->Draw("same");
     H(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_PanTau_only_fail_reso_rel", kOrange)->Draw("same");

     // H(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_tauRec_only_pass_reso_rel", kViolet)->Draw("same");
     H(f, "test_r"+mode+"_t"+mode+"_compatible_trk_pT_tauRec_only_fail_reso_rel", kGreen)->Draw("same");

     gPad->SetLogy();
  }

  //2d: PanTau res vs true vis pT
  if(c == 20){
    H(f, "tau_pan_"+mode+"_true_"+mode+"_reso_rel_vs_pt_true", kAzure-2)->Draw("colz");

  }


  //2d plot: PanTau resolution Vs pT trk reco / pT tau rec  - disentagle kaon NEUTRAL decays 
  if( c == 21){
    TCanvas *can = new TCanvas("can","", 20, 20, 1450, 550);
    can->Divide(3,1);

    TLine *l = new TLine(-1, 0.5, 1, 0.5);
    l->SetLineStyle(7);
    l->SetLineColor(2);
    l->SetLineWidth(2);

    TLine *l7 = new TLine(-1, 0.7, 1, 0.7);
    l7->SetLineStyle(7);
    l7->SetLineColor(kOrange);
    l7->SetLineWidth(2);

    TLine *lt = new TLine(-1, 5, 1, 5);
    lt->SetLineStyle(7);
    lt->SetLineColor(1);
    lt->SetLineWidth(2);


    can->cd(1);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    h->SetTitle( ("r"+mode+"_t"+mode+" : all decays").c_str() );
    h->Draw("colz");
    l->Draw(); l7->Draw();

    can->cd(2);
    TH2D *hh = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    hh->GetYaxis()->SetRangeUser(0,6);
    hh->Draw("colz");
    hh->SetTitle( ("r"+mode+"_t"+mode+" : with neutral Kaons").c_str() );
    gPad->SetGrid(1,1);
    l->Draw(); l7->Draw();

    can->cd(3);
    TH2D *h4 = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_0_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h4->GetYaxis()->SetRangeUser(0,6);
    h4->SetTitle( ("r"+mode+"_t"+mode+" : without neutral Kaons").c_str() );
    gPad->SetGrid(1,1);
    h4->Draw("colz");
    l->Draw(); l7->Draw();

  }

  //2d plot: PanTau resolution Vs pT trk reco / pT tau rec  - disentagle kaon decays 
  if( c == 22){
    TCanvas *can = new TCanvas("can","", 20, 20, 1400, 550);
    can->Divide(3,1);

    TLine *l = new TLine(-1, 0.5, 1, 0.5);
    l->SetLineStyle(7);
    l->SetLineColor(2);
    l->SetLineWidth(2);

    TLine *l7 = new TLine(-1, 0.7, 1, 0.7);
    l7->SetLineStyle(7);
    l7->SetLineColor(kOrange);
    l7->SetLineWidth(2);

    TLine *lt = new TLine(-1, 5, 1, 5);
    lt->SetLineStyle(7);
    lt->SetLineColor(1);
    lt->SetLineWidth(2);


    can->cd(1);
    TH2D *h = H2(f, "test_r"+mode+"_t"+mode+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    h->Draw("colz");
    l->Draw(); l7->Draw();

    can->cd(2);
    TH2D *hh = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_1_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    hh->GetYaxis()->SetRangeUser(0,6);
    hh->Draw("colz");
    l->Draw(); l7->Draw();

    can->cd(3);
    TH2D *h4 = H2(f, "test_r"+mode+"_t"+mode+"_neutral_kaon_decay_0_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", kAzure);
    h4->GetYaxis()->SetRangeUser(0,6);
    gPad->SetGrid(1,1);
    h4->Draw("colz");
    l->Draw(); l7->Draw();



  }

  if(c == 101){

    Fraction(f, "test_r"+mode+"_t"+mode+"_tau_pan_compatible_trk_pT_reso_rel", "test_r"+mode+"_t"+mode+"_compatible_trk_pT_PanTau_only_pass_reso_rel");
    Fraction(f, "test_r"+mode+"_t"+mode+"_tau_pan_compatible_trk_pT_reso_rel", "test_r"+mode+"_t"+mode+"_compatible_trk_pT_PanTau_only_fail_reso_rel");


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
