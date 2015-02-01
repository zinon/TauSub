/*

.L Plot_Resolution.C+

Plot_Resolution("../results/V58/tau4mom.root", 1, "", "Jet-Sig BDT medium")
Plot_Resolution("../results/V59/tau4mom.root", 1, "", "No Jet-Sig BDT")

Plot_Resolution("../results/V58/tau4mom.root", 12, "", "Jet-Sig BDT medium")
Plot_Resolution("../results/V59/tau4mom.root", 12, "", "No Jet-Sig BDT")

Plot_Resolution("../results/V58/tau4mom.root", 4, "", "Jet-Sig BDT medium")
Plot_Resolution("../results/V59/tau4mom.root", 4, "", "No Jet-Sig BDT")

Plot_Resolution("../results/V58/tau4mom.root", 7, "", "Jet-Sig BDT medium")
Plot_Resolution("../results/V59/tau4mom.root", 7, "", "No Jet-Sig BDT")

Plot_Resolution("../results/V58/tau4mom.root", 19, "", "Jet-Sig BDT medium")
Plot_Resolution("../results/V75/tau4mom.root", 19, "", "No Jet-Sig BDT")
*/


#include "common.C"

vector<string> v; //histo names
vector<string> w; //histo legend titles - 1st is the header
string out;

void Plot_Resolution(TString file, string dir, string info);
void Plot_Resolution(TString file, int i, string dir, string info);

void Plot_Resolution(TString file, string dir, string info){

  for (int i = 0; i <= 15; i++)
    Plot_Resolution(file, i, dir, info);

}


void Plot_Resolution(TString file, int i, string dir, string info){

  if(dir.empty()) dir = "/home/zenon/TauSubstructureSupNote/COM/trunk/figs/resolution";

  cout<<"Saving figures in "<<dir<<endl;


  v.clear(); w.clear();

  if(i==0) {
    w.push_back("PanTau");
    v.push_back("tau_pan_1p_reso_rel"); w.push_back("1p");
    v.push_back("tau_pan_1p0n_reso_rel"); w.push_back("1p0n");
    v.push_back("tau_pan_1p1n_reso_rel"); w.push_back("1p1n");
    v.push_back("tau_pan_1pXn_reso_rel"); w.push_back("1pXn");
    out = "tau_pan_1pNn_reso_rel";
  }

  if(i==1){
    w.push_back("PanTau - VisTrueTau");
    v.push_back("tau_pan_1p_true_1p_reso_rel"); w.push_back("1p-1p");
    v.push_back("tau_pan_1p0n_true_1p0n_reso_rel"); w.push_back("1p0n-1p0n");
    v.push_back("tau_pan_1p0n_true_1p1n_reso_rel"); w.push_back("1p0n-1p1n");
    v.push_back("tau_pan_1p0n_true_1pXn_reso_rel"); w.push_back("1p0n-1pXn");
    v.push_back("tau_pan_1p1n_true_1p0n_reso_rel"); w.push_back("1p1n-1p0n");
    v.push_back("tau_pan_1p1n_true_1p1n_reso_rel"); w.push_back("1p1n-1p1n");
    v.push_back("tau_pan_1p1n_true_1pXn_reso_rel"); w.push_back("1p1n-1pXn");
    v.push_back("tau_pan_1pXn_true_1p0n_reso_rel"); w.push_back("1pXn-1p0n");
    v.push_back("tau_pan_1pXn_true_1p1n_reso_rel"); w.push_back("1pXn-1p1n");
    v.push_back("tau_pan_1pXn_true_1pXn_reso_rel"); w.push_back("1pXn-1pXn");
    out = "tau_pan_1pNn_true_1pNn_reso_rel";
  }
    
  if(i==2){
    w.push_back("#splitline{PanTau 1p - VisTrueTau 1p}{pT[GeV]}");
    v.push_back("tau_pan_1p_true_1p_reso_rel"); w.push_back("inclusive");
    v.push_back("tau_pan_1p_5_10_true_1p_reso_rel"); w.push_back("5-10");
    v.push_back("tau_pan_1p_10_15_true_1p_reso_rel"); w.push_back("10-15");
    v.push_back("tau_pan_1p_15_20_true_1p_reso_rel"); w.push_back("15-20");
    v.push_back("tau_pan_1p_20_25_true_1p_reso_rel"); w.push_back("20-25");
    v.push_back("tau_pan_1p_25_30_true_1p_reso_rel"); w.push_back("25-30");
    v.push_back("tau_pan_1p_30_40_true_1p_reso_rel"); w.push_back("30-40");
    v.push_back("tau_pan_1p_40_50_true_1p_reso_rel"); w.push_back("40-50");
    v.push_back("tau_pan_1p_50_60_true_1p_reso_rel"); w.push_back("50-60");
    v.push_back("tau_pan_1p_60_70_true_1p_reso_rel"); w.push_back("60-70");
    v.push_back("tau_pan_1p_70_80_true_1p_reso_rel"); w.push_back("70-80");
    v.push_back("tau_pan_1p_80_90_true_1p_reso_rel"); w.push_back("80-90");
   v.push_back("tau_pan_1p_90_100_true_1p_reso_rel"); w.push_back("90-100");
    out = "tau_pan_1p_X_Y_true_1p_reso_rel";
  }

  if(i==3){
    w.push_back("#splitline{PanTau 1p0n-VisTrueTau 1p0n}{VisTrue p_{T}[GeV]}");
    v.push_back("tau_pan_1p0n_true_1p0n_reso_rel"); w.push_back("inclusive");
    v.push_back("tau_pan_1p0n_5_10_true_1p0n_reso_rel"); w.push_back("5-10");
    v.push_back("tau_pan_1p0n_10_15_true_1p0n_reso_rel"); w.push_back("10-15");
    v.push_back("tau_pan_1p0n_15_20_true_1p0n_reso_rel"); w.push_back("15-20");
    v.push_back("tau_pan_1p0n_20_25_true_1p0n_reso_rel"); w.push_back("20-25");
    v.push_back("tau_pan_1p0n_25_30_true_1p0n_reso_rel"); w.push_back("25-30");
    v.push_back("tau_pan_1p0n_30_40_true_1p0n_reso_rel"); w.push_back("30-40");
    v.push_back("tau_pan_1p0n_40_50_true_1p0n_reso_rel"); w.push_back("40-50");
    v.push_back("tau_pan_1p0n_50_60_true_1p0n_reso_rel"); w.push_back("50-60");
    v.push_back("tau_pan_1p0n_60_70_true_1p0n_reso_rel"); w.push_back("60-70");
    v.push_back("tau_pan_1p0n_70_80_true_1p0n_reso_rel"); w.push_back("70-80");
    v.push_back("tau_pan_1p0n_80_90_true_1p0n_reso_rel"); w.push_back("80-90");
    v.push_back("tau_pan_1p0n_90_100_true_1p0n_reso_rel"); w.push_back("90-100");
    out = "tau_pan_1p0n_X_Y_true_1p0n_reso_rel";
  }

  
  if(i==4){
    w.push_back("PanTau 1p0n - VisTrueTau 1p0n");
    v.push_back("tau_pan_1p0n_true_1p0n_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_1p0n_true_1p0n_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_1p0n_true_1p0n_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying Event");
    v.push_back("tau_pan_1p0n_true_1p0n_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_1p0n_true_1p0n_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Conversion");
    v.push_back("tau_pan_1p0n_true_1p0n_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_1p0n_true_1p0n_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-matched");
    v.push_back("tau_pan_1p0n_true_1p0n_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_1p0n_true_1p0n_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_1p0n_true_1p0n_matched_trk_orig_X_reso_rel";
  }
  
  if(i==5){
    w.push_back("#splitline{PanTau 1p1n -}{VisTrueTau 1p1n}");
    v.push_back("tau_pan_1p1n_true_1p1n_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_1p1n_true_1p1n_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_1p1n_true_1p1n_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying Event");
    v.push_back("tau_pan_1p1n_true_1p1n_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_1p1n_true_1p1n_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Conversion");
    v.push_back("tau_pan_1p1n_true_1p1n_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_1p1n_true_1p1n_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-matched");
    v.push_back("tau_pan_1p1n_true_1p1n_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_1p1n_true_1p1n_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_1p1n_true_1p1n_matched_trk_orig_X_reso_rel";
  }

  if(i==6){
    w.push_back("PanTau 1pXn - VisTrueTau 1pXn");
    v.push_back("tau_pan_1pXn_true_1pXn_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_1pXn_true_1pXn_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_1pXn_true_1pXn_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying Event");
    v.push_back("tau_pan_1pXn_true_1pXn_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_1pXn_true_1pXn_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Conversion");
    v.push_back("tau_pan_1pXn_true_1pXn_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_1pXn_true_1pXn_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-matched");
    v.push_back("tau_pan_1pXn_true_1pXn_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_1pXn_true_1pXn_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_1pXn_true_1pXn_matched_trk_orig_X_reso_rel";
  }

  if(i==7){
    w.push_back("PanTau 1p - VisTrueTau 1p");
    v.push_back("tau_pan_1p_true_1p_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_1p_true_1p_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_1p_true_1p_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying Event");
    v.push_back("tau_pan_1p_true_1p_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_1p_true_1p_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Conversion");
    v.push_back("tau_pan_1p_true_1p_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_1p_true_1p_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-matched");
    v.push_back("tau_pan_1p_true_1p_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_1p_true_1p_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_1p_true_1p_matched_trk_orig_X_reso_rel";
  }

  if(i==8){
    w.push_back("PanTau 3p - VisTrueTau 1p");
    v.push_back("tau_pan_3p_true_1p_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_3p_true_1p_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_3p_true_1p_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying Event");
    v.push_back("tau_pan_3p_true_1p_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_3p_true_1p_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Conversion");
    v.push_back("tau_pan_3p_true_1p_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_3p_true_1p_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-matched");
    v.push_back("tau_pan_3p_true_1p_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_3p_true_1p_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_3p_true_1p_matched_trk_orig_X_reso_rel";
  }

  if(i==9){
    w.push_back("PanTau 3p0n - VisTrueTau 1p0n");
    v.push_back("tau_pan_3p0n_true_1p0n_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_3p0n_true_1p0n_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_3p0n_true_1p0n_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying Event");
    v.push_back("tau_pan_3p0n_true_1p0n_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_3p0n_true_1p0n_matched_trk_orig_PC_reso_rel"); w.push_back("Photon conversion");
    v.push_back("tau_pan_3p0n_true_1p0n_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_3p0n_true_1p0n_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-matched");
    v.push_back("tau_pan_3p0n_true_1p0n_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_3p0n_true_1p0n_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_3p0n_true_1p0n_matched_trk_orig_X_reso_rel";
  }

  if(i==10){
    w.push_back("PanTau 3pXn - VisTrueTau 1pXn");
    v.push_back("tau_pan_3pXn_true_1pXn_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_3pXn_true_1pXn_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_3pXn_true_1pXn_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying-Event");
    v.push_back("tau_pan_3pXn_true_1pXn_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_3pXn_true_1pXn_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Convertion");
    v.push_back("tau_pan_3pXn_true_1pXn_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_3pXn_true_1pXn_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-Matched");
    v.push_back("tau_pan_3pXn_true_1pXn_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_3pXn_true_1pXn_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_3pXn_true_1pXn_matched_trk_orig_X_reso_rel";
  }

  if(i==11) {
    w.push_back("PanTau");
    v.push_back("tau_pan_3p_reso_rel"); w.push_back("3p");
    v.push_back("tau_pan_3p0n_reso_rel"); w.push_back("3p0n");
    v.push_back("tau_pan_3pXn_reso_rel"); w.push_back("3pXn");
    out = "tau_pan_3pNn_reso_rel";
  }

  if(i==12){
    w.push_back("PanTau - VisTrueTau");
    v.push_back("tau_pan_3p_true_3p_reso_rel"); w.push_back("3p-3p");
    v.push_back("tau_pan_3p0n_true_3p0n_reso_rel"); w.push_back("3p0n-3p0n");
    v.push_back("tau_pan_3p0n_true_3pXn_reso_rel"); w.push_back("3p0n-3pXn");
    v.push_back("tau_pan_3pXn_true_3p0n_reso_rel"); w.push_back("3pXn-3p0n");
    v.push_back("tau_pan_3pXn_true_3pXn_reso_rel"); w.push_back("3pXn-3pXn");
    out = "tau_pan_3pNn_true_3pNn_reso_rel";
  }
  
  if(i==13){
    w.push_back("PanTau 1pXn - VisTrueTau 1p1n");
    v.push_back("tau_pan_1pXn_true_1p1n_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_1pXn_true_1p1n_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_1pXn_true_1p1n_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying-Event");
    v.push_back("tau_pan_1pXn_true_1p1n_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_1pXn_true_1p1n_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Convertion");
    v.push_back("tau_pan_1pXn_true_1p1n_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_1pXn_true_1p1n_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-Matched");
    v.push_back("tau_pan_1pXn_true_1p1n_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_1pXn_true_1p1n_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_1pXn_true_1p1n_matched_trk_orig_X_reso_rel";
  }

  if(i==14) {
    w.push_back("PanTau");
    v.push_back("tau_pan_incl_reso_rel"); w.push_back("PanTau + Cell-based");
    v.push_back("tau_rec_incl_reso_rel"); w.push_back("tauRec");
    out = "tau_pantau_taurec_reso_rel";
  }

  if(i==15){
    w.push_back("PanTau 1p1n - VisTrueTau 1p0n");
    v.push_back("tau_pan_1p1n_true_1p0n_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_1p1n_true_1p0n_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_1p1n_true_1p0n_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying Event");
    v.push_back("tau_pan_1p1n_true_1p0n_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_1p1n_true_1p0n_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Conversion");
    v.push_back("tau_pan_1p1n_true_1p0n_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_1p1n_true_1p0n_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-matched");
    v.push_back("tau_pan_1p1n_true_1p0n_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_1p1n_true_1p0n_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_1p1n_true_1p0n_matched_trk_orig_X_reso_rel";
  }

  if(i==16){
    w.push_back("PanTau 3p - VisTrueTau 3p");
    v.push_back("tau_pan_3p_true_3p_reso_rel"); w.push_back("All");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_PI_reso_rel"); w.push_back("Primary");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_UE_reso_rel"); w.push_back("Underlying Event");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_PU_reso_rel"); w.push_back("Pile-Up");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_PC_reso_rel"); w.push_back("Photon Conversion");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_FK_reso_rel"); w.push_back("Fakes");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_MM_reso_rel"); w.push_back("Multi-matched");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_UC_reso_rel"); w.push_back("Unclassified");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_Other_reso_rel"); w.push_back("Other");
    out = "tau_pan_3p_true_3p_matched_trk_orig_X_reso_rel";
  }

  if(i==17){
    w.push_back("PanTau - VisTrueTau");
    v.push_back("tau_pan_3p_true_3p_reso_rel"); w.push_back("3pXn-3pXn");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_xPI3_reso_rel"); w.push_back("Primary: 3 tracks");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_xPI2_reso_rel"); w.push_back("Primary: 2 tracks");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_xPI1_reso_rel"); w.push_back("Primary: 1 tracks");
    v.push_back("tau_pan_3p_true_3p_matched_trk_orig_xPI0_reso_rel"); w.push_back("Primary: 0 tracks");
    out = "tau_pan_3p_true_3p_matched_trk_orig_xPIX_reso_rel";
  }

  if(i==18){
    w.push_back("PanTau - VisTrueTau");
    v.push_back("tau_pan_3p0n_true_3p0n_reso_rel"); w.push_back("3p0n-3p0n");
    v.push_back("tau_pan_3p0n_true_3p0n_matched_trk_orig_xPI3_reso_rel"); w.push_back("Primary: 3 tracks");
    v.push_back("tau_pan_3p0n_true_3p0n_matched_trk_orig_xPI2_reso_rel"); w.push_back("Primary: 2 tracks");
    v.push_back("tau_pan_3p0n_true_3p0n_matched_trk_orig_xPI1_reso_rel"); w.push_back("Primary: 1 tracks");
    v.push_back("tau_pan_3p0n_true_3p0n_matched_trk_orig_xPI0_reso_rel"); w.push_back("Primary: 0 tracks");
    out = "tau_pan_3p0n_true_3p0n_matched_trk_orig_xPIX_reso_rel";
  }

  if(i==19){
    w.push_back("PanTau - VisTrueTau");
    v.push_back("tau_pan_3pXn_true_3pXn_reso_rel"); w.push_back("3pXn-3pXn");
    v.push_back("tau_pan_3pXn_true_3pXn_matched_trk_orig_xPI3_reso_rel"); w.push_back("Primary: 3 tracks");
    v.push_back("tau_pan_3pXn_true_3pXn_matched_trk_orig_xPI2_reso_rel"); w.push_back("Primary: 2 tracks");
    v.push_back("tau_pan_3pXn_true_3pXn_matched_trk_orig_xPI1_reso_rel"); w.push_back("Primary: 1 tracks");
    v.push_back("tau_pan_3pXn_true_3pXn_matched_trk_orig_xPI0_reso_rel"); w.push_back("Primary: 0 tracks");
    out = "tau_pan_3pXn_true_3pXn_matched_trk_orig_xPIX_reso_rel";
  }

  if(i==20){
    w.push_back("#splitline{PanTau 1p - VisTrueTau 1p}{pT[GeV]}");
    v.push_back("tau_pan_1p_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("inclusive");
    v.push_back("tau_pan_1p_5_10_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("5-10");
    v.push_back("tau_pan_1p_10_15_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("10-15");
    v.push_back("tau_pan_1p_15_20_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("15-20");
    v.push_back("tau_pan_1p_20_25_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("20-25");
    v.push_back("tau_pan_1p_25_30_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("25-30");
    v.push_back("tau_pan_1p_30_40_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("30-40");
    v.push_back("tau_pan_1p_40_50_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("40-50");
    v.push_back("tau_pan_1p_50_60_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("50-60");
    v.push_back("tau_pan_1p_60_70_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("60-70");
    v.push_back("tau_pan_1p_70_80_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("70-80");
    v.push_back("tau_pan_1p_80_90_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("80-90");
    v.push_back("tau_pan_1p_90_100_true_1p_matched_trk_parent_0_reso_rel"); w.push_back("90-100");
    out = "tau_pan_1p_5_10_true_1p_matched_trk_parent_0_reso_rel";
  }

  string BDT;

  if ( info.find("medium") != string::npos)  BDT = "BDTm";
  else if ( info.find("loose") != string::npos)  BDT = "BDTl";
  else if ( info.find("tight") != string::npos)  BDT = "BDTt";
  else  BDT = "BDTn";

  out += "_"+BDT;

  Plot(file, v, w, dir, out, info);
}
