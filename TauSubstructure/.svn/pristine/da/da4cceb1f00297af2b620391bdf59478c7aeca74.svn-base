// Jan 2015, back to action!

#include "TauMain.h"

const double TauMain::arrBDT[] = {0.0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};

const int TauMain::arrPt[] = {0, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200, 250, 350, 500, 750, 1000};

const double TauMain::arrEta[] = {0, 0.3, 0.8, 1.0, 1.2, 1.6, 2.1, 2.5};

const int TauMain::arrKaonCharged[] = {
  321, 10321, 100321, 200321, 9000321, 323, 10323, 20323, 100323, 9000323, 30323, 325, 9000325, 10325, 20325, 100325, 9010325, 327, 9010327, 329, 9000329
};

const int TauMain::arrKaonNeutral[] = {
  130, 310, 311, 10311, 100311, 200311, 9000311, 313, 10313, 20313, 100313, 9000313, 30313, 315, 9000315, 10315, 20315, 100315, 9010315, 317, 9010317, 319, 9000319
};

///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
TauMain::TauMain(TTree *t)
  : TauSubstructureViewer(t), //let TauSubstructureViewer take care of Init and other standard stuff
    m_do_taurec(true),
    m_opt_max_ntrks(12),
    m_opt_max_reco_tau_abs_eta(-123),
    m_opt_min_reco_tau_pt(-123),
    m_opt_min_true_vis_tau_pt(-123),
    m_opt_match_to_vis_true_tau(false),
    m_opt_reco_tau_eta_l(-1),
    m_opt_reco_tau_eta_r(-1),
    m_opt_reco_tau_pt_l(-1),
    m_opt_reco_tau_pt_r(-1),
    m_opt_pan_tau_trk_reco_trk_match_max_dR(0.01),
    m_opt_pan_tau_trk_reco_trk_match_max_rel_frac_pT(0.01),
    m_opt_pan_tau_trk_reco_trk_match_closest_dR(false),
    m_opt_reco_tau_vis_true_max_dR(0.2),
    m_opt_reco_tau_pan_tau_max_dR(0.2),
    m_opt_tau_parent_pdg_id(23),
    m_opt_build_vis_true_tau("auto"),
    m_opt_build_vis_true_tau_method("subtraction"), //-
    m_opt_JetBDTSig("none"),
    m_opt_vis_true_tau_match_use_Assoc_index(false),
    m_opt_UseOfficialTruthMatching(false),
    m_opt_WeightHistos(false),
    m_opt_compatibility_ratio_cut("nocut"),
    m_mc(0),
    m_nentries(0),
    m_File(0),
    m_OutFileName("tau4mom")
{

  TH1::AddDirectory(kFALSE);//sets a global switch disabling the reference, see: http://root.cern.ch/root/html/TH1.html or http://root.cern.ch/drupal/content/saving-histograms-disk

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
TauMain::~TauMain(){

  //if(GetOptWeightHistos()) WeightHistos();

  SaveAndClose();
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::LoadSetup(){

  m_File = new TFile( (m_OutFileName+".root").c_str(), "recreate");

  m_DecayModes.push_back("1p0n");  m_DecayModes.push_back("1p1n");  m_DecayModes.push_back("1pXn");
  m_DecayModes.push_back("3p0n");  m_DecayModes.push_back("3pXn");  m_DecayModes.push_back("other");

  cout<<"TauMain::LoadSetup - study tauRec " <<(GetOptStudyTauRec()?"YES":"NO")<<endl;
  cout<<"TauMain::LoadSetup - option max n tracks = " << GetOptMaxNtrks()<<endl;
  if( GetOptMaxRecoTauAbsEta() > 0) {cout<<"TauMain::LoadSetup - option max reco |eta| = " << GetOptMaxRecoTauAbsEta()<<endl; }
  if( GetOptMinRecoTauPt() > 0) {cout<<"TauMain::LoadSetup - option min reco pt = " << GetOptMinRecoTauPt()<<endl; }
  if( GetOptMinTrueVisTauPt() > 0) {cout<<"TauMain::LoadSetup - option min true vis pt = " << GetOptMinTrueVisTauPt()<<endl; }
  if( GetOptMatchToVisTrueTau() ) {cout<<"TauMain::LoadSetup - option match reco to visible true tau"<<endl;}
  if( GetOptVisTrueTauMatchUseAssocIndex() ) { cout<<"TauMain::LoadSetup - option vis true tau matching done with Assoc index"<<endl; }
  if( GetOptRecoTauAbsEtaL() > 0 ){ cout<<"TauMain::LoadSetup - option reco tau min abs eta"<<endl; }
  if( GetOptRecoTauAbsEtaR() > 0){ cout<<"TauMain::LoadSetup - option reco tau max abs eta"<<endl; }
  if( GetOptTauJetBDTSig() != "none" ) { cout<<"TauMain::LoadSetup - option tau JetBDTSig '"<<GetOptTauJetBDTSig()<<"'"<<endl; }
  if(GetOptUseOfficialTruthMatching() ){ cout<<"TauMain::LoadSetup - option TruthTrackMatchingTool is enabled "<<endl; }
  cout<<"TauMain::LoadSetup - option reco tau - tau true parent PDG ID "<<GetOptTauParentPDGID()<<endl;
  cout<<"TauMain::LoadSetup - option tau track - pan tau track - reco track matching maximum dR "<<GetOptPanTauTrkRecoTrkMatchMaxDR()<<endl;
  cout<<"TauMain::LoadSetup - option tau track - pan tau track - reco track matching maximum relative pT fraction " <<GetOptPanTauTrkRecoTrkMatchMaxRelFracPt()*100<<"% "<<endl;
  if(GetOptPanTauTrkRecoTrkMatchClosestDR())  cout<<"TauMain::LoadSetup - option pan tau tau track - reco track matching maximum based on closest dR "<<endl;
  cout<<"TauMain::LoadSetup - option reco tau - vis true tau max dR "<<GetOptRecoTauVisTrueTauMatchMaxDR()<<endl;
  cout<<"TauMain::LoadSetup - option reco tau - build vis true tau '" << GetOptBuildVisTauTrue()<<"'"<<endl;
  if(GetOptBuildVisTauTrue() != "auto") cout<<"TauMain::LoadSetup - option reco tau - build vis true tau '" <<GetOptBuildVisTauTrueMethod()<<"'"<<endl;     //-
  cout<<"TauMain::LoadSetup - option reco tau - pan tau max dR "<<GetOptRecoTauPanTauMaxDR()<<endl;
  if(GetOptWeightHistos()) cout<<"TauMain::LoadSetup - applying global weight on histograms "<<endl;
  cout<<"TauMain::LoadSetup - option resolution vs truth pt  : '" <<GetOptCompatibilityRatioCut()<<"'"<<endl;

  vector<int> v (arrPt, arrPt + sizeof(arrPt) / sizeof(arrPt[0]) );
  m_vec_pt_bins = v;
  cout<<"TauMain::LoadSetup - pt bins ";
  for( vector<int>::iterator it = m_vec_pt_bins.begin(); it != m_vec_pt_bins.end(); it++){
    cout<<*it<<":";
  }
  cout<<endl;

  vector<double> vB (arrBDT, arrBDT + sizeof(arrBDT) / sizeof(arrBDT[0]) );
  m_vec_bdt_bins = vB;
  cout<<"TauMain::LoadSetup - bdt bins ";
  for( vector<double>::iterator it = m_vec_bdt_bins.begin(); it != m_vec_bdt_bins.end(); it++){
    cout<<*it<<":";
  }
  cout<<endl;

  vector<double> ve (arrEta, arrEta + sizeof(arrEta) / sizeof(arrEta[0]) );
  m_vec_eta_bins = ve;
  cout<<"TauMain::LoadSetup - eta bins ";
  for( vector<double>::iterator it = m_vec_eta_bins.begin(); it != m_vec_eta_bins.end(); it++){
    cout<<*it<<":";
  }
  cout<<endl;


  vector<int> v1 (arrKaonCharged, arrKaonCharged + sizeof(arrKaonCharged) / sizeof(arrKaonCharged[0]) );
  m_charged_kaons_pdgid = v1;

  vector<int> v2 (arrKaonNeutral, arrKaonNeutral + sizeof(arrKaonNeutral) / sizeof(arrKaonNeutral[0]) );
  m_neutral_kaons_pdgid = v2;

  //xsecs:  crossSection_mean (nano barn)  X GenFiltEff_mean X k-factor
  m_xsec[147818] = 0.87767 * 1 * 1;

  m_xsec[170201] = 0.037396 * 1 * 1; //Zprime250tautau

  m_xsec[170202] = 0.0028237 * 1 * 1; //Zprime500tautau

  m_xsec[170203] = 0.00053747 * 1 * 1; //Zprime750tautau

  m_xsec[170204] = 0.00014839 * 1 * 1; //Zprime1000tautau

  m_xsec[170205] = 0.000049671 * 1 * 1; //Zprime1250tautau

  //nevents:
  m_Nevt[147818] = 7502984;

  m_Nevt[170201] = 200000;

  m_Nevt[170202] = 200500;

  m_Nevt[170203] = 200499;

  m_Nevt[170204] = 200500;

  m_Nevt[170205] = 200500;


}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::WeightHistos(){

  cout<<"TauMain::WeightHistos - mc channel number "<<m_mc<<endl;

  double w = 1. / m_Nevt[m_mc] / m_xsec[m_mc];

  m_HM.WeightHistos(w);

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::SaveAndClose(){

  cout<<"TauMain::SaveAndClose() - saving histograms ..."<<endl;

  m_File->cd();

  //m_File->Write(0,TObject::kOverwrite);
  m_HM.WriteHistos();

  m_File->Write();
  //file->Save();
  //file->ls();
  m_File->Close();

  if( gSystem->GetFromPipe(("ls " + m_OutFileName+".root").c_str()) == m_OutFileName+".root" )
    cout<<"TauMain::SaveAndClose() - root file stored succesfully..."<<endl;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::Looper(){

  if(!fChain) { cerr<<"TauMain::Looper - Null chain. Exiting..."<<endl; return;}

  m_nentries = fChain->GetEntries();

  if(!m_nentries) { cerr<<"TauMain::Looper - No entries. Exiting..."<<endl; return;}

  cout<<"TauMain::Looper - entries "<<m_nentries<<endl;

  ///book histos
  BookHistos();

  ///loop over entries
  for(int jentry = 0; jentry < m_nentries; jentry++){
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    ///load branches
    LoadBranches(ientry);

    //weights
    m_mc = mc_channel_number;
    double gw = ( (*mcevt_weight)[0][0] ) * (m_xsec[m_mc]);

    if(GetOptWeightHistos()) m_HM.SetGlobalWeight( gw );

    if(!jentry) cout<<"TauMain::Looper - Global MC weight "<<gw<<" ("<<( (*mcevt_weight)[0][0] )<<" x "<< (m_xsec[m_mc])<<") is applied..."<<endl;

    //particle mother
    if(!jentry){
      if(m_mc == 147818)
        SetOptTauParentPDGID(23);
      else if(170201 <= m_mc  && m_mc <= 170205 )
        SetOptTauParentPDGID(32);
      else{
        cout<<"TauMain::Looper - Parent PDGID unknown for MC "<<m_mc<<" Exiting..."<<endl; return;
      }
    }

    ///actual analysis code
    Analyze();
  }
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::Analyze(){

  /*
    CreatePanTauList(); //list of pan tau onjects (cell-based for the moment)

    CreateRecoTauList(); //list of reco taus

    CreateTrueVisTauList(); //list of visible truth taus

    AssociateRecoToVisTrue(); // link reco taus to truth taus

    AssociatePanToVisTrue(); //this creates a list of HyperTau's, ie. PanTaus with visible truth matched tau information

    AssociateHyperToReco();// link reco taus to hyper (pan) taus

    AssociateHyperTauTracksToTruthTracks(); // assign truth info to the pantau tracks
  */



  //build objects
  CreateRecoTauList(); //list of reco taus

  CreateTrueVisTauList(); //list of visible truth taus

  AssociateRecoToVisTrue(); // link reco taus to truth taus

  CreateHyperTau(); // combines PanTau + VisTrue + RecTau

  AssociateHyperTauTracksToTruthTracks(); // assign truth info to the pantau tracks



  //all about tau rec
  if( GetOptStudyTauRec() ){
    for(SuperTauVecItr itr = m_TauList_RecoTau.begin(); itr != m_TauList_RecoTau.end(); itr++){

      m_HM.UpdateCutflow("taurec", 1 );

      //vis truth matching
      if(GetOptMatchToVisTrueTau()) if( !itr->IsTrue() ) continue;
      m_HM.UpdateCutflow("taurec", 2 );

      int obs_nTrk = itr->GetInfo("nTrk");

      double obs_pt = itr->GetKin("pt");
      double ref_pt = itr->GetTrueVis().GetKin("truevis", "pt");

      double obs_eta = itr->GetKin("eta");

      int ref_nTrk = itr->GetTrueVis().GetInfo("nProng");

      string obs_nTrk_str = GetNprongStr(obs_nTrk);
      string ref_nTrk_str = GetNprongStr(ref_nTrk);

      double RelReso =  RelRes(obs_pt, ref_pt);
      double StdReso = StdRes(obs_pt, ref_pt);

      string pt_range = GetPtRangeStr(ref_pt);

      //selection cuts
      if( GetOptMinRecoTauPt() > 0 ) if( obs_pt < GetOptMinRecoTauPt() ) continue; // pT threshold for reco taus
      m_HM.UpdateCutflow("taurec", 3 );

      if( GetOptMaxRecoTauAbsEta() > 0 ) if( fabs(obs_eta) > GetOptMaxRecoTauAbsEta() ) continue; // eta for reco taus
      m_HM.UpdateCutflow("taurec", 4 );

      if( GetOptMinTrueVisTauPt() > 0 ) if( ref_pt < GetOptMinTrueVisTauPt() ) continue; // pT threshold for true vis taus
      m_HM.UpdateCutflow("taurec", 5 );

      if( GetOptTauJetBDTSig().compare("none") ){//BDT
        bool kJetBDTSig = itr->Get_JetBDTSig( GetOptTauJetBDTSig() );
        if(!kJetBDTSig) continue;
      }
      m_HM.UpdateCutflow("taurec", 6 );

      if(obs_nTrk > GetOptMaxNtrks() ) continue; //don't care for higher-multiplicity taus
      m_HM.UpdateCutflow("taurec", 7 );

      if( obs_nTrk == 0) continue; //discard events with no tracks
      m_HM.UpdateCutflow("taurec", 8 );

      if( GetOptRecoTauPtL() > 0 ) if( obs_pt < GetOptRecoTauPtL() ) continue; // pT window
      if( GetOptRecoTauPtR() > 0 ) if( obs_pt > GetOptRecoTauPtR() ) continue;
      m_HM.UpdateCutflow("taurec", 9 );

      if( GetOptRecoTauAbsEtaL() > 0 ) if( fabs(obs_eta) < GetOptRecoTauAbsEtaL() ) continue; // eta cut
      if( GetOptRecoTauAbsEtaR() > 0 ) if( fabs(obs_eta) > GetOptRecoTauAbsEtaR() ) continue;
      m_HM.UpdateCutflow("taurec", 10 );


      //plots
      m_HM.FillHisto( "tau_rec_incl_pt", obs_pt );

      m_HM.FillHisto( "tau_rec_incl_reso_rel", RelReso );
      m_HM.FillHisto( "tau_rec_incl_reso_log", Log10Res(obs_pt, ref_pt) );

      m_HM.FillHisto( "tau_rec_incl_"+pt_range+"_reso_rel", RelReso );
      m_HM.FillHisto( "tau_rec_incl_"+pt_range+"_reso_std", StdReso );

      m_HM.FillHisto( "tau_rec_"+obs_nTrk_str+"_reso_rel", RelReso );
      m_HM.FillHisto( "tau_rec_"+obs_nTrk_str+"_reso_std", StdReso );

      m_HM.FillHisto( "tau_rec_"+obs_nTrk_str+"_"+pt_range+"_reso_rel", RelReso );
      m_HM.FillHisto( "tau_rec_"+obs_nTrk_str+"_"+pt_range+"_reso_std", StdReso );

      m_HM.FillHisto( "tau_rec_"+obs_nTrk_str+"_"+pt_range+"_true_"+ref_nTrk_str+"_reso_rel", RelReso );
      m_HM.FillHisto( "tau_rec_"+obs_nTrk_str+"_"+pt_range+"_true_"+ref_nTrk_str+"_reso_std", StdReso );

      m_HM.FillHisto( "tau_rec_vs_true_nTrk", ref_nTrk, obs_nTrk );
      m_HM.FillHisto( "tau_rec_incl_reso_rel_vs_Nvtx", GetNvtx(), RelReso );

    }
  }

  if(m_TauList_RecoTau.size()) m_HM.FillHisto( "tau_rec_lead_pt",  m_TauList_RecoTau.front().GetKin("pt"));


  //all about pan tau
  bool ditau_evt(false);
  double ditau_vis_true_dR(1e3);
  double ditau_reco_dR(1e3);
  if(m_TauList_HyperTau.size() > 1){
    if(m_TauList_HyperTau[0].IsTrue() && m_TauList_HyperTau[1].IsTrue() ){
      ditau_evt = true;
      ditau_vis_true_dR = DeltaR(m_TauList_HyperTau[0].GetTrueVisHLV(), m_TauList_HyperTau[1].GetTrueVisHLV());
      ditau_reco_dR = DeltaR(m_TauList_HyperTau[0].GetPanHLV(), m_TauList_HyperTau[1].GetPanHLV());
    }
  }


  for(HyperTauVecItr itr = m_TauList_HyperTau.begin(); itr != m_TauList_HyperTau.end(); itr++){
    m_HM.UpdateCutflow("pantau", 1 );
    //vis truth matching
    if(GetOptMatchToVisTrueTau()) if( !itr->IsTrue() ) continue; // matched to true visible tau

    double obs_pt = itr->GetPanHLV().Pt()/1000.; //observed pT
    double obs_eta = itr->GetPanHLV().Eta(); //observed eta
    double ref_pt = itr->GetTrueVisHLV().Pt(); //reference pT

    double obs_e = itr->GetPanHLV().E()/1000.;
    double obs_taurec_pt = itr->GetRecoHLV().Pt(); //observed reco pT
    double obs_taurec_et = itr->GetRecoHLV().Et(); //observed reco eT
    double obs_taurec_p = itr->GetRecoHLV().P(); //observed reco e or p
    double obs_taurec_eta = itr->GetRecoHLV().Eta(); //observed reco eta

    double ref_e = itr->GetTrueVisHLV().E();
    double ref_eta = itr->GetTrueVisHLV().Eta();
    double ref_phi = itr->GetTrueVisHLV().Phi();

    TLV vec_pan_hlv_ChargedPions = itr->GetPanTau().getChargedPions();
    int obs_nTrk = vec_pan_hlv_ChargedPions.size();

    m_HM.FillHisto( "tau_pan_incl_no_cut_pt", obs_pt );

    //selection cuts
    if( GetOptMinRecoTauPt() > 0 ) if( obs_pt < GetOptMinRecoTauPt() ) continue; // pT threshold for reco taus
    m_HM.UpdateCutflow("pantau", 2 );

    if( GetOptMaxRecoTauAbsEta() > 0 ) if( fabs(obs_eta) > GetOptMaxRecoTauAbsEta() ) continue; // eta for reco taus
    m_HM.UpdateCutflow("pantau", 3 );

    if( GetOptMinTrueVisTauPt() > 0 ) if( ref_pt < GetOptMinTrueVisTauPt() ) continue; // pT threshold for true vis taus
    m_HM.UpdateCutflow("pantau", 4 );

    if( GetOptTauJetBDTSig().compare("none") ){//BDT
      bool kJetBDTSig = itr->GetRecoTau().Get_JetBDTSig( GetOptTauJetBDTSig() );
      if(!kJetBDTSig) continue;
    }
    m_HM.UpdateCutflow("pantau", 5 );

    if(obs_nTrk > GetOptMaxNtrks() ) continue; //don't care for higher-multiplicity taus
    m_HM.UpdateCutflow("pantau", 6 );

    if( obs_nTrk == 0) continue; //discard events with no tracks
    m_HM.UpdateCutflow("pantau", 7 );

    if( GetOptRecoTauPtL() > 0 ) if( obs_pt < GetOptRecoTauPtL() ) continue; // pT window
    if( GetOptRecoTauPtR() > 0 ) if( obs_pt > GetOptRecoTauPtR() ) continue;
    m_HM.UpdateCutflow("pantau", 8 );

    if( GetOptRecoTauAbsEtaL() > 0 ) if( fabs(obs_eta) < GetOptRecoTauAbsEtaL() ) continue; // eta cut
    if( GetOptRecoTauAbsEtaR() > 0 ) if( fabs(obs_eta) > GetOptRecoTauAbsEtaR() ) continue;
    m_HM.UpdateCutflow("pantau", 9 );

    if( obs_nTrk != (int)itr->GetRecoTau().GetInfo("nTrk") ) {
      cerr<<"TauMain::Loop - n track disagreement tau rec "<<itr->GetRecoTau().GetInfo("nTrk")<<" vs tau sub "<<obs_nTrk<<". Skipping the event ..."<<endl;
      continue;
    }
    m_HM.UpdateCutflow("pantau", 10 );

    //gather observables needed for the resolution studies
    string pt_range = GetPtRangeStr(ref_pt);//Use ref_pt to define the pT binning - not the observed pT
    string eta_range = GetEtaRangeStr(ref_eta);//Use ref_eta to define the eta binning - not the observed eta

    double ref_bdt_score = itr->GetRecoTau().Get_JetBDTSigScore();
    string bdt_range = GetBDTRangeStr(ref_bdt_score); //define the BDT binning
    string bdt_pt_bin =
      ref_pt < 20. ? "1" :
      ref_pt < 40. ? "2" :
      ref_pt < 80. ? "3" :
      "4";

    int ref_nTrk = itr->GetTrueVis().GetInfo("nProng");
    string obs_nTrk_str = GetNprongStr(obs_nTrk);
    string ref_nTrk_str = GetNprongStr(ref_nTrk);

    TLV vec_pan_hlv_NeutralPions = itr->GetPanTau().getNeutralPions();
    int obs_nPi0 = vec_pan_hlv_NeutralPions.size();
    int ref_nPi0 = itr->GetTrueVis().GetInfo("nPi0");
    string obs_nNeutral_str = GetNneutralStr(obs_nPi0);
    string ref_nNeutral_str = GetNneutralStr(ref_nPi0);

    int ref_decay_mode = GetDecayModeTrue(ref_nTrk, ref_nPi0);
    string ref_decay_mode_str = GetDecayModeStr(ref_decay_mode);

    TauObject_PanTau::DecayMode obs_decay_mode = itr->GetPanTau().getDecayMode();
    string obs_decay_mode_str = GetDecayModeStr(obs_decay_mode);

    //resolution definitions
    double RelReso = RelRes(obs_pt, ref_pt);
    double StdReso = StdRes(obs_pt, ref_pt);
    double DetEneReso = DetEneRes(obs_e, ref_e);
    //double DetPtReso = DetPtRes(obs_pt, ref_pt);
    double Log10Reso = Log10Res(obs_pt, ref_pt);

    double taurec_RelReso = RelRes(obs_taurec_pt, ref_pt);

    //tracks and origins
    vector<SmartTrack> strack_vec = itr->GetSmartTracks(); // tracks associated to the reco tau
    vector<double>  vec_obs_matched_trk_truth_prob;
    vector<int>  vec_obs_matched_trk_truth_parent;
    vector<string> vec_obs_matched_trk_truth_origin;
    for(vector<SmartTrack>::iterator sTrk = strack_vec.begin(); sTrk < strack_vec.end(); sTrk++ ){
      if( /*sTrk->Get_tau_track_matched_reco() &&*/ sTrk->Get_tau_track_matched_truth() ){
        vec_obs_matched_trk_truth_prob.push_back( sTrk->Get_tau_track_matched_reco_probability() );
        vec_obs_matched_trk_truth_parent.push_back( sTrk->Get_tau_track_matched_truth_parent_pdgId() );
        vec_obs_matched_trk_truth_origin.push_back( sTrk->Get_tau_track_matched_truth_Origin() );
      }else{
        //cout<<"track not matched"<<endl;
        vec_obs_matched_trk_truth_prob.push_back( 0 );
        vec_obs_matched_trk_truth_parent.push_back( 0 );
        vec_obs_matched_trk_truth_origin.push_back( "Other" );
      }
    }

    //track pt
    double rec_track_0_p(0);
    double rec_track_0_pT(0);
    double rec_track_0_d0(0);
    double rec_track_0_z0(0);
    double rec_track_0_z0SinTheta(0);
    //double rec_track_0_theta(0);
    int rec_track_0_nSCTHits(-1);
    int rec_track_0_nPixHits(-1);
    int rec_track_0_idx(-1);
    //int rec_track_0_q(0);
    double rec_track_0_qoverpt(0);
    double rec_track_0_err_qoverpt(0);
    double rec_track_0_qoverp(0);
    double rec_track_0_err_qoverp(0);
    double rec_track_0_sigma_qoverp_over_qoverp(0);
    if(strack_vec.size()){
      if(strack_vec.front().Get_tau_track_matched_reco()){
        rec_track_0_p = strack_vec.front().Get_tau_track_matched_reco_tlv().P();
        rec_track_0_pT = strack_vec.front().Get_tau_track_matched_reco_tlv().Pt();
        rec_track_0_idx = (int)strack_vec.front().Get_tau_track_matched_reco_index();
        rec_track_0_d0 = trk_d0_wrtPV->at(rec_track_0_idx);
        rec_track_0_z0 = trk_z0_wrtPV->at(rec_track_0_idx);
        rec_track_0_z0SinTheta = trk_z0_wrtPV->at(rec_track_0_idx) * sin( trk_theta->at(rec_track_0_idx) );
        rec_track_0_nSCTHits = trk_nSCTHits->at(rec_track_0_idx);
        rec_track_0_nPixHits = trk_nPixHits->at(rec_track_0_idx);

        //rec_track_0_q = trk_qoverp->at(rec_track_0_idx) > 0 ? +1 : -1;

        rec_track_0_qoverpt =  trk_qoverp->at(rec_track_0_idx) / std::sin(trk_theta->at(rec_track_0_idx)) * 1e3 ; // from 1/MeV to 1/GeV
        rec_track_0_err_qoverpt = std::fabs(trk_qoverp->at(rec_track_0_idx)) * 1e3  / std::sin(trk_theta->at(rec_track_0_idx)) * // from 1/MeV to 1/GeV
          std::sqrt( std::pow(trk_err_qoverp_wrtBS->at(rec_track_0_idx) / trk_qoverp->at(rec_track_0_idx),2) + // sqrt() is dimensionless
                     std::pow(trk_theta_err_wrtBL->at(rec_track_0_idx) / std::tan(trk_theta->at(rec_track_0_idx)), 2) ); // --//--

        rec_track_0_qoverp = trk_qoverp->at(rec_track_0_idx) * 1e3;
        rec_track_0_err_qoverp = trk_err_qoverp_wrtBS->at(rec_track_0_idx) * 1e3;

        rec_track_0_sigma_qoverp_over_qoverp = trk_err_qoverp_wrtBS->at(rec_track_0_idx) / trk_qoverp->at(rec_track_0_idx);

        /*cout<<"xcheck trk pT "<<trk_pt->at(rec_track_0_idx) * 1e-3
          <<", ltv trk pT "<<rec_track_0_pT
          <<", 1/pT " << 1/(trk_pt->at(rec_track_0_idx) * 1e-3)
          <<", tlv 1/pT "<<1/ rec_track_0_pT
          <<", 1/(p.sinTheta) "<<rec_track_0_qoverpt
          <<", err_qoverp "<< rec_track_0_err_qoverp
          <<", err_qoverpt "<< rec_track_0_err_qoverpt
          <<endl;*/

        //cout<<" 1/p "<< 1/rec_track_0_p << " |q/p| "<<fabs(trk_qoverp->at(rec_track_0_idx) * 1e3)<<" sigma/(1/p) "<<rec_track_0_sigma_qoverp_over_qoverp<<endl;

        //cout<<rec_track_0_idx<<" pT="<<rec_track_0_pT<<" d0="<<rec_track_0_d0<<" z0="<<rec_track_0_z0<<" SCT="<<rec_track_0_nSCTHits<<" PIX="<<rec_track_0_nPixHits<<endl;
      }
    }

    double obs_track_0_qoverp;

    bool reco_trk_0_matched_truth_PI = strack_vec.size() ?
      strack_vec.at(0).Get_tau_track_matched_reco() && strack_vec.at(0).Get_tau_track_matched_truth() && strack_vec.at(0).Get_tau_track_matched_truth_Origin() == "PI" : false;

    if(reco_trk_0_matched_truth_PI ){

      //xcheck
      if( DeltaR( strack_vec.at(0).Get_tau_track_matched_reco_tlv(), strack_vec.at(0).Get_tau_track_matched_truth_tlv() ) > 0.1 )
        cerr<<"Reco track pt, eta  "<<strack_vec.at(0).Get_tau_track_matched_reco_tlv().Pt()<<", "<<strack_vec.at(0).Get_tau_track_matched_reco_tlv().Eta()
            <<" not matched to truth "<<strack_vec.at(0).Get_tau_track_matched_truth_tlv().Pt()<<", "<<strack_vec.at(0).Get_tau_track_matched_truth_tlv().Eta()
            <<" from "<<strack_vec.at(0).Get_tau_track_matched_truth_Origin()
            <<endl;

      obs_track_0_qoverp = ( strack_vec.at(0).Get_tau_track_matched_truth_Q()) / (strack_vec.at(0).Get_tau_track_matched_truth_tlv().P());

    }


    bool kRecoTrkQuality = fabs(rec_track_0_d0) < 0.25 && fabs(rec_track_0_z0SinTheta) < 0.25 && rec_track_0_nPixHits >= 3 && rec_track_0_nSCTHits >= 7;

    double pan_track_0_pT = vec_pan_hlv_ChargedPions.size() ? vec_pan_hlv_ChargedPions[0].Pt()/1000. : 0;
    double pan_track_0_Eta = vec_pan_hlv_ChargedPions.size() ? fabs( vec_pan_hlv_ChargedPions[0].Eta() ) : -1234;

    bool kPanLeadTrkmatchedReco = strack_vec.size() ?  strack_vec.front().Get_tau_track_matched_reco() : false;
    bool kPanLeadTrkMatchedTruth = strack_vec.size() ? strack_vec.front().Get_tau_track_matched_truth() &&  fabs(strack_vec.front().Get_tau_track_matched_truth_parent_pdgId())==15 : false;

    double lead_recoTrk_panTrk_dR = kPanLeadTrkMatchedTruth ? DeltaR( strack_vec.front().Get_tau_track_matched_reco_tlv(), vec_pan_hlv_ChargedPions.front() ) : -1;
    double lead_recoTrk_panTrk_res = fabs( RelRes( pan_track_0_pT, rec_track_0_pT ) );
    double lead_recoTrk_over_panTrk = pan_track_0_pT / rec_track_0_pT;


    double rec_track_0_pT_over_rec_tau_pT = rec_track_0_pT / obs_taurec_pt;
    double rec_track_0_pT_over_pan_tau_pT = rec_track_0_pT / obs_pt;

    double pan_track_0_pT_over_rec_tau_pT = pan_track_0_pT / obs_taurec_pt;
    double pan_track_0_pT_over_pan_tau_pT = pan_track_0_pT / obs_pt;

    double pan_track_0_matched_truth_pT =  kPanLeadTrkMatchedTruth ? strack_vec.front().Get_tau_track_matched_truth_tlv().Pt() : 0;
    double pan_track_0_matched_truth_Eta =  kPanLeadTrkMatchedTruth ? strack_vec.front().Get_tau_track_matched_truth_tlv().Eta() : 0;
    double pan_track_0_matched_truth_dR =  kPanLeadTrkMatchedTruth ? DeltaR( strack_vec.front().Get_tau_track_matched_truth_tlv(), strack_vec.front().Get_tau_track_matched_reco_tlv() ) : -1;

    double pan_track_0_matched_truth_RelReso = RelRes(pan_track_0_pT, pan_track_0_matched_truth_pT);

    //trk compatibility
    double ResoRelComp;
    bool kTrkTauRecComp = pan_track_0_pT_over_rec_tau_pT > 0.5 && pan_track_0_pT_over_rec_tau_pT < 5;
    if( kTrkTauRecComp ){
      ResoRelComp = RelReso;
    }else{
      ResoRelComp = taurec_RelReso;
    }

    //event selection cut on compatibility
    if(GetOptCompatibilityRatioCut() != "nocut"){
      if(GetOptCompatibilityRatioCut() == "r1p0n_CRcut")
        if(obs_decay_mode_str == "1p0n")
          if(!kTrkTauRecComp) continue;//discard event
    }
    m_HM.UpdateCutflow("pantau", 11 );

    //trk compatibility weighted
    double sigma_et = 0;
    double sigma_qoverpt = rec_track_0_err_qoverpt;
    double sigma_et_over_pt = obs_taurec_et / rec_track_0_pT * std::sqrt( std::pow(sigma_et/obs_taurec_et, 2) + std::pow(rec_track_0_pT * sigma_qoverpt, 2) ); //sigma(et/pt)
    double tau_rec_et_over_pan_track_0_pT_minus_1 = (obs_taurec_et / rec_track_0_pT - 1.0); // R(et/pt)
    double tau_rec_et_over_pan_track_0_pT_minus_1_weighted  = (obs_taurec_et / rec_track_0_pT - 1.0) / sigma_et_over_pt; // R / sigma(et/pt)

    /*
      cout<<"  et "<<obs_taurec_et<<", pt "<<rec_track_0_pT
      <<", sigma et "<<sigma_et
      <<", sigma_qoverpt "<<sigma_qoverpt
      <<", sigma_et_over_pt  "<<sigma_et_over_pt
      <<", R  "<<tau_rec_et_over_pan_track_0_pT_minus_1
      <<", R/sigma_et_over_pt "<<tau_rec_et_over_pan_track_0_pT_minus_1_weighted
      <<endl;
    */

    double tau_rec_sigma_over_p = SigmaOverP( obs_taurec_p, obs_taurec_eta, obs_nTrk);
    double tau_rec_sigma_p = obs_taurec_p * SigmaOverP( obs_taurec_p, obs_taurec_eta, obs_nTrk);

    double sigma_e_over_p = obs_taurec_p / rec_track_0_p * std::sqrt( std::pow(tau_rec_sigma_over_p, 2) + std::pow(rec_track_0_sigma_qoverp_over_qoverp, 2) ); //sigma(e/p)

    double tau_rec_e_over_pan_track_0_p_minus_1 = (obs_taurec_p / rec_track_0_p - 1.0); // R(e/p)
    double tau_rec_e_over_pan_track_0_p_minus_1_weighted  = (obs_taurec_p / rec_track_0_p - 1.0) / sigma_e_over_p; // R / sigma(et/pt)

    double R_trk0_calo = tau_rec_e_over_pan_track_0_p_minus_1;
    double R_trk0_calo_w = tau_rec_e_over_pan_track_0_p_minus_1_weighted;

    /*cout<<"  tau p "<<obs_taurec_p<<" eta "<<obs_taurec_eta<<" Ntrk "<<obs_nTrk<<" Sigma/E "<<tau_rec_sigma_over_p<<endl;
      cout<<"  sigma(e/p) "<<sigma_e_over_p
      <<" R "<<tau_rec_e_over_pan_track_0_p_minus_1
      <<" R/sigma_e_over_p "<<tau_rec_e_over_pan_track_0_p_minus_1_weighted
      <<endl;*/

    //cout<<"rec vs truth p: "<<1/rec_track_0_qoverp<<"  "<<1/obs_track_0_qoverp<<endl;

    //pulls
    double pull_ene = (obs_taurec_p - ref_e) / tau_rec_sigma_p;
    double pull_qoverp = ( std::fabs(rec_track_0_qoverp) - std::fabs(obs_track_0_qoverp) )/rec_track_0_err_qoverp;

    //matching probability - minimum value for 3p cases
    double min_obs_matched_trk_truth_prob = vec_obs_matched_trk_truth_prob.size() ?
      *min_element(vec_obs_matched_trk_truth_prob.begin(), vec_obs_matched_trk_truth_prob.end()) : 0;

    string obs_matched_trk_truth_prob_str = min_obs_matched_trk_truth_prob > 0.9 ?
      "high" : min_obs_matched_trk_truth_prob > 0.8 ? "medium" : "low" ;

    //track parent
    int count_obs_matched_trk_truth_parent_tau = count (vec_obs_matched_trk_truth_parent.begin(), vec_obs_matched_trk_truth_parent.end(), 15);
    string obs_matched_trk_truth_parent_tau_str = GetStringFromInt( count_obs_matched_trk_truth_parent_tau );

    //track origin  - only the 1st track at the moment
    string obs_matched_trk_truth_orig_str = vec_obs_matched_trk_truth_origin.size() ?
      vec_obs_matched_trk_truth_origin[0] : "Other"; //optimized only for 1p - will do for all tracks later

    string obs_matched_trk_truth_orig_xPI_str = GetStringFromInt( count( vec_obs_matched_trk_truth_origin.begin(), vec_obs_matched_trk_truth_origin.end(), "PI") );

    //kaon decays
    string ref_truth_kaon_decay_str =  itr->GetTruthKaonDecay() ? "1" : "0";
    string ref_truth_charged_kaon_decay_str =  itr->GetTruthChargedKaonDecay() ? "1" : "0";
    string ref_truth_neutral_kaon_decay_str =  itr->GetTruthNeutralKaonDecay() ? "1" : "0";


    //distances
    double dR_Rec_TrueVis = DeltaR(itr->GetRecoHLV(), itr->GetTrueVisHLV());
    double dR_Pan_TrueVis = DeltaR(itr->GetPanHLV(), itr->GetTrueVisHLV());

    //leading track
    bool kTauTrackMatchedTruth(false);
    bool kTauTrackMatchedReco(false);
    double TauTrackMatchedRecoTruth_DR(-1234);
    double TauTrackMatchedRecoTruth_Deta(-1234);
    double TauTrackMatchedRecoTruth_DpT(-1234);
    double TauTrackMatchedRecoTruth_DpTres(-1234);
    int TauTrackMatchedReco_Q(-1234);
    int TauTrackMatchedTruth_Q(-1234);
    TLorentzVector v4TauTrackMatchedReco(0,0,0,0);
    TLorentzVector v4TauTrackMatchedTruth(0,0,0,0);
    if( strack_vec.size() ){

      kTauTrackMatchedReco = strack_vec.at(0).Get_tau_track_matched_reco();
      if(kTauTrackMatchedReco){
        v4TauTrackMatchedReco = strack_vec.at(0).Get_tau_track_matched_reco_tlv();
        TauTrackMatchedReco_Q = strack_vec.at(0).Get_tau_track_matched_reco_Q();
      }

      kTauTrackMatchedTruth = strack_vec.at(0).Get_tau_track_matched_truth();
      if(kTauTrackMatchedTruth){
        v4TauTrackMatchedTruth = strack_vec.at(0).Get_tau_track_matched_truth_tlv();
        TauTrackMatchedTruth_Q = strack_vec.at(0).Get_tau_track_matched_truth_Q();
      }
      if(kTauTrackMatchedReco && kTauTrackMatchedTruth){
        if( !strack_vec.at(0).Get_tau_track_matched_truth_is_spurious() ){
          TauTrackMatchedRecoTruth_DR = DeltaR(v4TauTrackMatchedReco, v4TauTrackMatchedTruth);
          TauTrackMatchedRecoTruth_Deta = DeltaEta(v4TauTrackMatchedReco, v4TauTrackMatchedTruth);
        }
        TauTrackMatchedRecoTruth_DpT = DeltaPt(v4TauTrackMatchedReco, v4TauTrackMatchedTruth);
        TauTrackMatchedRecoTruth_DpTres = RelRes(v4TauTrackMatchedReco.Pt(), v4TauTrackMatchedTruth.Pt());
      }
    }

    if(ref_decay_mode_str == obs_decay_mode_str && ref_decay_mode_str == "1p0n"){

      if(false) if(RelReso < -0.25  && !itr->GetRecoTau().Get_JetBDTSig("tight")){
          cout<<"\n"<<obs_decay_mode_str<<endl
              <<"Res="<<RelReso<<endl
              <<"pTrec="<<itr->GetRecoHLV().Pt()<<endl
              <<"pTpan="<<itr->GetPanHLV().Pt()/1000.<<endl
              <<"pTvis="<<itr->GetTrueVisHLV().Pt()<<endl
              <<"max BDT="<<itr->GetRecoTau().Get_Max_JetBDTSig()<<endl
              <<"dR(rec, vis)="<<dR_Rec_TrueVis<<endl
              <<"dR(pan, vis)="<<dR_Pan_TrueVis<<endl
              <<"dR(trk reco, trk truth)="<<TauTrackMatchedRecoTruth_DR<<endl
              <<"pt(trk true)="<<v4TauTrackMatchedTruth.Pt()<<endl
              <<"pt(trk rec)="<<v4TauTrackMatchedReco.Pt()<<endl
              <<"pt(trk lead Pan)="<< ( vec_pan_hlv_ChargedPions.size() ? vec_pan_hlv_ChargedPions[0].Pt()/1000. : -1)<<endl
              <<"RelRes(trk rec, trk true)="<<TauTrackMatchedRecoTruth_DpTres<<endl
              <<"orig="<<obs_matched_trk_truth_orig_str
              <<endl;
          int _idx(-1); double _minDr(-1);
          bool matched = GetMatchedMCtauIndex( itr->GetTrueVisHLV(), _idx, _minDr );
          if(matched){
            cout<<"minDr(vis tau, mc tau)="<<_minDr<<endl;
            cout<<"Dr(vis tau, rec tau)="<<DeltaR(itr->GetRecoHLV(), itr->GetTrueVisHLV())<<endl;
            if(ditau_evt) cout<<"Dr(ditau)="<<ditau_vis_true_dR<<endl;
            PrintDecay( _idx );
          }
        }

      m_HM.FillHisto( "test_r1p0n_t1p0n_trkRecoTrue_tauRecoVisTrue_dRes", TauTrackMatchedRecoTruth_DpTres);

      if(RelReso < -0.25) m_HM.FillHisto( "test_r1p0n_t1p0n_lt_m025_rel_res_use_tauRec", RelRes(obs_taurec_pt, ref_pt) );
      if(RelReso > +0.25) m_HM.FillHisto( "test_r1p0n_t1p0n_gt_p025_rel_res_use_tauRec", RelRes(obs_taurec_pt, ref_pt) );
      m_HM.FillHisto( "test_r1p0n_t1p0n_rel_res_use_tauRec", RelRes(obs_taurec_pt, ref_pt) );

      m_HM.FillHisto( "test_r1p0n_t1p0n_rel_res_tauRec_vs_PanTau", RelRes(obs_pt, ref_pt), RelRes(obs_taurec_pt, ref_pt) );

      m_HM.FillHisto( "test_r1p0n_t1p0n_rel_res_vs_TruthMatchedDR", RelRes(obs_pt, ref_pt), itr->GetMatchedTruthDR() );
      m_HM.FillHisto( "test_t1p0n_t10n_visTrue_ditau_DR", ditau_vis_true_dR);
    }else{
      m_HM.FillHisto( "test_not_t1p0n_t10n_visTrue_ditau_DR", ditau_vis_true_dR);
    }


    if(ditau_evt){
      if(ref_nTrk_str == "1p"){
        if(ref_decay_mode_str == "1p0n"){
          m_HM.FillHisto( "test_t1p0n_visTrue_ditau_DR", ditau_vis_true_dR);
        }else{
          m_HM.FillHisto( "test_t1pwithn_visTrue_ditau_DR", ditau_vis_true_dR);
        }
      }
    }

    //plotting

    if(GetOptStudyTauRec()) m_HM.FillHisto( "tau_rec_visTrue_dR", dR_Rec_TrueVis);
    m_HM.FillHisto( "tau_pan_visTrue_dR", dR_Pan_TrueVis);

    m_HM.FillHisto( "tau_pan_incl_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_incl_reso_det", DetEneReso );
    m_HM.FillHisto( "tau_pan_incl_reso_log", Log10Reso );
    m_HM.FillHisto( "tau_pan_incl_reso_std", StdReso );
    m_HM.FillHisto( "tau_pan_incl_"+pt_range+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_incl_"+pt_range+"_reso_std", StdReso );

    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_reso_log", Log10Reso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_reso_std", StdReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_"+pt_range+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_"+pt_range+"_reso_std", StdReso );

    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_reso_std", StdReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_"+pt_range+"_true_"+ref_decay_mode_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_"+pt_range+"_true_"+ref_decay_mode_str+"_reso_std", StdReso );

    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_reso_std", StdReso );
    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_"+pt_range+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_"+pt_range+"_reso_std", StdReso );

    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_true_"+ref_nNeutral_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_true_"+ref_nNeutral_str+"_reso_std", StdReso );
    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_"+pt_range+"_true_"+ref_nNeutral_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_"+pt_range+"_true_"+ref_nNeutral_str+"_reso_std", StdReso );

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_reso_std", StdReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_reso_std", StdReso );

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_reso_std", StdReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_true_"+ref_nTrk_str+"_reso_rel", RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_true_"+ref_nTrk_str+"_reso_std", StdReso );

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_matched_trk_score_"+obs_matched_trk_truth_prob_str+"_reso_rel", RelReso );

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_parent_"+obs_matched_trk_truth_parent_tau_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_parent_"+obs_matched_trk_truth_parent_tau_str+"_reso_std", StdReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_true_"+ref_nTrk_str+"_matched_trk_parent_"+obs_matched_trk_truth_parent_tau_str+"_reso_std", StdReso);

    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_matched_trk_parent_"+obs_matched_trk_truth_parent_tau_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_matched_trk_parent_"+obs_matched_trk_truth_parent_tau_str+"_reso_std", StdReso);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_"+pt_range+"_true_"+ref_decay_mode_str+"_matched_trk_parent_"+obs_matched_trk_truth_parent_tau_str+"_reso_std", StdReso);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_"+pt_range+"_true_"+ref_decay_mode_str+"_matched_trk_parent_"+obs_matched_trk_truth_parent_tau_str+"_reso_rel", RelReso);

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_reso_rel", RelReso);

    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_std", StdReso);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_"+pt_range+"_true_"+ref_decay_mode_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_"+pt_range+"_true_"+ref_decay_mode_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_std", StdReso);

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_std", StdReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_std", StdReso);

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_std", StdReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_true_"+ref_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_"+pt_range+"_true_"+ref_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_std", StdReso);

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_matched_trk_orig_xPI"+obs_matched_trk_truth_orig_xPI_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_orig_xPI"+obs_matched_trk_truth_orig_xPI_str+"_reso_rel", RelReso);

    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_matched_trk_orig_xPI"+obs_matched_trk_truth_orig_xPI_str+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_matched_trk_orig_xPI"+obs_matched_trk_truth_orig_xPI_str+"_reso_rel", RelReso);


    // 2D
    m_HM.FillHisto( "tau_pan_incl_reso_rel_vs_pt_true", ref_pt, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_reso_rel_vs_pt_true", ref_pt, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_reso_rel_vs_eta_true", ref_eta, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_reso_rel_vs_phi_true", ref_phi, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_pt_true", ref_pt, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_eta_true", ref_eta, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_phi_true", ref_phi, RelReso );

    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_reso_rel_vs_pt_true", ref_pt, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_reso_rel_vs_pt_true", ref_pt, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_reso_rel_vs_eta_true", ref_eta, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_reso_rel_vs_phi_true", ref_phi, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_pt_true", ref_pt, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_eta_true", ref_eta, RelReso );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_phi_true", ref_phi, RelReso );

    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_reso_rel_vs_pt_tau_rec_reso_rel",  RelReso, taurec_RelReso );

    m_HM.FillHisto( "tau_pan_incl_pt_reco_vs_pt_true", ref_pt, obs_pt);

    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_pt_reco_vs_pt_true", ref_pt, obs_pt );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_pt_reco_vs_pt_true", ref_pt, obs_pt );

    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_pt_reco_vs_pt_true", ref_pt, obs_pt);
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+obs_decay_mode_str+"_pt_reco_vs_pt_true", ref_pt, obs_pt );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+obs_decay_mode_str+"_matched_trk_orig_"+obs_matched_trk_truth_orig_str+"_pt_reco_vs_pt_true", ref_pt, obs_pt );

    m_HM.FillHisto( "tau_pan_incl_reso_rel_vs_Nvtx", GetNvtx(), RelReso );


    //pi masses
    for(TLVItr it = vec_pan_hlv_NeutralPions.begin(); it != vec_pan_hlv_NeutralPions.end(); it++ ) m_HM.FillHisto( "tau_pan_incl_pi0_m", it->M());
    for(TLVItr it = vec_pan_hlv_ChargedPions.begin(); it != vec_pan_hlv_ChargedPions.end(); it++ ) m_HM.FillHisto( "tau_pan_incl_piC_m", it->M());

    //tracks
    m_HM.FillHisto( "tau_pan_vs_true_nTrk", ref_nTrk, obs_nTrk );

    m_HM.FillHisto( "tau_pan_vs_true_nPi0", ref_nPi0, obs_nPi0 );

    m_HM.FillHisto( "tau_pan_vs_true_dec", ref_decay_mode, obs_decay_mode );

    //eta - pt
    m_HM.FillHisto( "tau_pan_incl_eta", obs_eta );
    m_HM.FillHisto( "tau_pan_incl_pt", obs_pt );
    m_HM.FillHisto( "tau_pan_"+pt_range+"_pt", obs_pt );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_eta", obs_eta );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_pt", obs_pt );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_eta", obs_eta );
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_pt", obs_pt );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_eta", obs_eta );
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_true_"+ref_nTrk_str+"_pt", obs_pt );
    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_true_"+ref_nNeutral_str+"_eta", obs_eta );
    m_HM.FillHisto( "tau_pan_"+obs_nNeutral_str+"_true_"+ref_nNeutral_str+"_pt", obs_pt );

    //BDT
    m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_BDT_"+bdt_range+"_pTbin"+bdt_pt_bin+"_reso_rel", RelReso);
    m_HM.FillHisto( "tau_pan_"+obs_nTrk_str+"_BDT_"+bdt_range+"_pTbin"+bdt_pt_bin+"_reso_rel", RelReso);

    // matched reco-truth track
    if(kTauTrackMatchedTruth){
      m_HM.FillHisto( "tau_pan_TauTrack_RecoTruth_DR", TauTrackMatchedRecoTruth_DR);
      m_HM.FillHisto( "tau_pan_TauTrack_RecoTruth_Deta", TauTrackMatchedRecoTruth_Deta);
      m_HM.FillHisto( "tau_pan_TauTrack_RecoTruth_DpT", TauTrackMatchedRecoTruth_DpT);
      m_HM.FillHisto( "tau_pan_TauTrack_RecoTruth_DpTres", TauTrackMatchedRecoTruth_DpTres);
      m_HM.FillHisto( "tau_pan_TauTrack_RecoQ_vs_TruthQ", TauTrackMatchedTruth_Q, TauTrackMatchedReco_Q);

      m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_TauTrack_RecoTruth_DR", TauTrackMatchedRecoTruth_DR);
      m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_TauTrack_RecoTruth_Deta", TauTrackMatchedRecoTruth_Deta);
      m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_TauTrack_RecoTruth_DpT", TauTrackMatchedRecoTruth_DpT);
      m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_TauTrack_RecoTruth_DpTres", TauTrackMatchedRecoTruth_DpTres);
      m_HM.FillHisto( "tau_pan_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_TauTrack_RecoQ_vs_TruthQ", TauTrackMatchedTruth_Q, TauTrackMatchedReco_Q);
    }
    //decay mode classification
    m_HM.FillHistoW( "tau_pan_decay_mode_classification", ref_decay_mode, (int)obs_decay_mode, 1);
    m_HM.FillHistoW( "tau_pan_"+pt_range+"_decay_mode_classification", ref_decay_mode, (int)obs_decay_mode, 1);

    //trk-tau compatibility
    if(kPanLeadTrkmatchedReco){
      m_HM.FillHisto( "test_lead_recoTrk_over_panTrk", lead_recoTrk_over_panTrk );
      m_HM.FillHisto( "test_lead_recoTrk_panTrk_dR", lead_recoTrk_panTrk_dR);
      m_HM.FillHisto( "test_lead_recoTrk_panTrk_res", lead_recoTrk_panTrk_res);
      m_HM.FillHisto( "test_lead_recoTrk_d0", rec_track_0_d0);
      m_HM.FillHisto( "test_lead_recoTrk_z0", rec_track_0_z0);
      m_HM.FillHisto( "test_lead_recoTrk_z0SinTheta", rec_track_0_z0SinTheta);
      m_HM.FillHisto( "test_lead_recoTrk_nSCTHits", rec_track_0_nSCTHits);
      m_HM.FillHisto( "test_lead_recoTrk_nPixHits", rec_track_0_nPixHits);
    }

    m_HM.FillHisto( "test_incl_rec_track_0_pT_over_rec_tau_pT", rec_track_0_pT_over_rec_tau_pT );
    m_HM.FillHisto( "test_incl_rec_track_0_pT_over_pan_tau_pT", rec_track_0_pT_over_pan_tau_pT );
    m_HM.FillHisto( "test_incl_pan_track_0_pT_over_rec_tau_pT", pan_track_0_pT_over_rec_tau_pT );
    m_HM.FillHisto( "test_incl_pan_track_0_pT_over_pan_tau_pT", pan_track_0_pT_over_pan_tau_pT );
    m_HM.FillHisto( "test_incl_rec_track_0_pT_over_rec_tau_pT_vs_tau_rec_reso_rel", taurec_RelReso, rec_track_0_pT_over_rec_tau_pT );
    m_HM.FillHisto( "test_incl_rec_track_0_pT_over_rec_tau_pT_vs_tau_pan_reso_rel", RelReso, rec_track_0_pT_over_rec_tau_pT );

    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_rec_track_0_pT_over_rec_tau_pT", rec_track_0_pT_over_rec_tau_pT );
    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_rec_track_0_pT_over_pan_tau_pT", rec_track_0_pT_over_pan_tau_pT );
    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_pT_over_rec_tau_pT", pan_track_0_pT_over_rec_tau_pT );
    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_pT_over_pan_tau_pT", pan_track_0_pT_over_pan_tau_pT );

    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_matched_trk_parent_"+obs_matched_trk_truth_parent_tau_str+"_pan_track_0_pT_over_rec_tau_pT",
                    pan_track_0_pT_over_rec_tau_pT);

    m_HM.FillHisto( "test_incl_tau_pan_compatible_trk_pT_reso_rel", ResoRelComp);

    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_tau_pan_compatible_trk_pT_reso_rel", ResoRelComp);
    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_tau_pan_compatible_trk_pT_reso_rel", ResoRelComp);

    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_tau_pan_compatible_trk_pT_reso_rel_vs_pt_true", ref_pt, ResoRelComp);
    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_tau_pan_compatible_trk_pT_reso_rel_vs_pt_true", ref_pt, ResoRelComp);

    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_tau_pan_compatible_trk_pT_reso_rel", ResoRelComp);
    m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_tau_pan_compatible_trk_pT_reso_rel", ResoRelComp);

    if(kTrkTauRecComp){
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_compatible_trk_pT_PanTau_only_pass_reso_rel", RelReso);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_compatible_trk_pT_PanTau_only_pass_reso_rel", RelReso);

      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_compatible_trk_pT_tauRec_only_pass_reso_rel", taurec_RelReso);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_compatible_trk_pT_tauRec_only_pass_reso_rel", taurec_RelReso);
    }else{
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_compatible_trk_pT_PanTau_only_fail_reso_rel", RelReso);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_compatible_trk_pT_PanTau_only_fail_reso_rel", RelReso);

      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_compatible_trk_pT_tauRec_only_fail_reso_rel", taurec_RelReso);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_compatible_trk_pT_tauRec_only_fail_reso_rel", taurec_RelReso);
    }

    if(kPanLeadTrkMatchedTruth){
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel",
                      pan_track_0_matched_truth_RelReso);

      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_pT",
                      pan_track_0_matched_truth_RelReso, pan_track_0_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_pT",
                      pan_track_0_matched_truth_RelReso, pan_track_0_matched_truth_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_dR",
                      pan_track_0_matched_truth_RelReso, pan_track_0_matched_truth_dR);

      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_Eta",
                      pan_track_0_matched_truth_RelReso, pan_track_0_Eta);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_Eta",
                      pan_track_0_matched_truth_RelReso, pan_track_0_matched_truth_Eta);

      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT",
                      pan_track_0_matched_truth_RelReso, pan_track_0_pT_over_rec_tau_pT);


      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT",
                      RelReso, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT",
                      RelReso, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT",
                      RelReso, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT",
                      RelReso, pan_track_0_pT_over_rec_tau_pT);

      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT",
                      obs_pt, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT",
                      obs_pt, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT",
                      obs_pt, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT",
                      obs_pt, pan_track_0_pT_over_rec_tau_pT);

      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT",
                      obs_taurec_pt, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT",
                      obs_taurec_pt, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT",
                      obs_taurec_pt, pan_track_0_pT_over_rec_tau_pT);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT",
                      obs_taurec_pt, pan_track_0_pT_over_rec_tau_pT);

      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel",
                      pan_track_0_matched_truth_RelReso, RelReso);
      //+ kaons info
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel",
                      pan_track_0_matched_truth_RelReso, RelReso);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel",
                      pan_track_0_matched_truth_RelReso, RelReso);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel",
                      pan_track_0_matched_truth_RelReso, RelReso);

      // + trk origin info
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_pan_track_0_matched_truth_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_reso_rel", pan_track_0_matched_truth_RelReso, RelReso);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_pan_track_0_matched_truth_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_reso_rel", pan_track_0_matched_truth_RelReso, RelReso);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_pan_track_0_matched_truth_trk_orig_"+obs_matched_trk_truth_orig_str+"_reso_rel_vs_reso_rel", pan_track_0_matched_truth_RelReso, RelReso);

    }

    if(kRecoTrkQuality){
      m_HM.FillHisto( "test_trk_quality_"+obs_decay_mode_str+"_true_"+ref_decay_mode_str+"_reso_rel", RelReso );
      if(kPanLeadTrkMatchedTruth){
        m_HM.FillHisto( "test_trk_quality_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel",
                        pan_track_0_matched_truth_RelReso);

        m_HM.FillHisto( "test_trk_quality_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_pT",
                        pan_track_0_matched_truth_RelReso, pan_track_0_pT);

        m_HM.FillHisto( "test_trk_quality_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_pT",
                        pan_track_0_matched_truth_RelReso, pan_track_0_matched_truth_pT);

      }
    }


    //weighted trk compatibility

    //tau->Draw("TMath::Power(trk_pt[0], 2)*trk_err_qoverp_wrtBS[0]*1e-3:trk_pt[0]*1e-3", "trk_pt[0]>5 * 1e3 && trk_pt[0] < 50 * 1e3", "box")
    //tau->Draw("trk_qoverp[0]*1e3:trk_err_qoverp_wrtBS[0]*1e3", "trk_pt[0]>10 * 1e3 && trk_pt[0] < 50 * 1e3", "box")

    m_HM.FillHisto( "test_rec_track_0_qoverp_vs_err_qoverp",   rec_track_0_err_qoverp,  rec_track_0_qoverp );
    m_HM.FillHisto( "test_rec_track_0_qoverpt_vs_err_qoverpt", rec_track_0_err_qoverpt, rec_track_0_qoverpt);

    //m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_rec_track_0_qoverp_vs_err_qoverp", rec_track_0_qoverp, rec_track_0_err_qoverp );
    //m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_rec_track_0_qoverpt_vs_err_qoverpt", rec_track_0_qoverpt, rec_track_0_err_qoverpt);

    if(kPanLeadTrkMatchedTruth){


      //pulls
      m_HM.FillHisto( "test_rec_track_0_pull_energy", pull_ene);
      m_HM.FillHisto( "test_rec_track_0_pull_qoverp", pull_qoverp);

      m_HM.FillHisto( "test_rec_track_0_"+pt_range+"_pull_energy", pull_ene);
      m_HM.FillHisto( "test_rec_track_0_"+pt_range+"_pull_qoverp", pull_qoverp);

      m_HM.FillHisto( "test_rec_track_0_"+eta_range+"_pull_energy", pull_ene);
      m_HM.FillHisto( "test_rec_track_0_"+eta_range+"_pull_qoverp", pull_qoverp);

      //general raw
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_reso_rel_vs_R_trk0_calo",
                      RelReso, R_trk0_calo);

      //general weighted
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_reso_rel_vs_R_trk0_calo_w",
                      RelReso, R_trk0_calo_w);

      //+kaons info raw
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_reso_rel_vs_R_trk0_calo",
                      RelReso, R_trk0_calo);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_reso_rel_vs_R_trk0_calo",
                      RelReso, R_trk0_calo);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_reso_rel_vs_R_trk0_calo",
                      RelReso, R_trk0_calo);

      //+kaons info weighted
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_reso_rel_vs_R_trk0_calo_w",
                      RelReso, R_trk0_calo_w);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_reso_rel_vs_R_trk0_calo_w",
                      RelReso, R_trk0_calo_w);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_reso_rel_vs_R_trk0_calo_w",
                      RelReso, R_trk0_calo_w);

      //+trk origin info raw
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_trk_0_orig_"+obs_matched_trk_truth_orig_str
                      +"_reso_rel_vs_R_trk0_calo", RelReso, R_trk0_calo);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_trk_0_orig_"+obs_matched_trk_truth_orig_str
                      +"_reso_rel_vs_R_trk0_calo", RelReso, R_trk0_calo);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_trk_0_orig_"+obs_matched_trk_truth_orig_str
                      +"_reso_rel_vs_R_trk0_calo", RelReso, R_trk0_calo);

      //+trk origin info weighted
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_kaon_decay_"+ref_truth_kaon_decay_str+"_trk_0_orig_"+obs_matched_trk_truth_orig_str
                      +"_reso_rel_vs_R_trk0_calo_w", RelReso, R_trk0_calo_w);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_charged_kaon_decay_"+ref_truth_charged_kaon_decay_str+"_trk_0_orig_"+obs_matched_trk_truth_orig_str
                      +"_reso_rel_vs_R_trk0_calo_w", RelReso, R_trk0_calo_w);
      m_HM.FillHisto( "test_r"+obs_decay_mode_str+"_t"+ref_decay_mode_str+"_neutral_kaon_decay_"+ref_truth_neutral_kaon_decay_str+"_trk_0_orig_"+obs_matched_trk_truth_orig_str
                      +"_reso_rel_vs_R_trk0_calo_w", RelReso, R_trk0_calo_w);


    }



  }//loop over hyper-taus



}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::BookHistos(){

  m_HM.AddCutflow( "taurec", 20);
  m_HM.AddCutflow( "pantau", 20);

  if( GetOptStudyTauRec() ) BookTemplate("rec");
  BookTemplate("pan");
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::BookTemplate(const std::string &algo ){

  //common: limits, axis titles, etc
  string t_res_rel = "(p_{T}^{reco} - p_{T}^{true})/p_{T}^{true}"; int n_res_rel = 101; double l_res_rel = -1.01; double r_res_rel = 1.01;
  string t_res_det = "(E^{reco} - E^{true})/#sqrt{E^{true}}"; int n_res_det = 201; double l_res_det = -2.01; double r_res_det = 2.01;
  string t_res_std = "p_{T}^{reco}/p_{T}^{true}"; int n_res_std = 300; double l_res_std = 0; double r_res_std = 3;
  string t_res_log = "log_{10}[E_{T}^{reco}/E_{T}^{true}]";int n_res_log = 101; double l_res_log = -1.01; double r_res_log = 1.01;
  string t_vtx = "Nvtx"; int n_vtx = 51; double l_vtx = -0.5; double r_vtx = 50.5;
  string t_pi0 = "N #pi^{0}"; int n_pi0 = 7; double l_pi0 = -0.5; double r_pi0 = 6.5;
  string t_pi0_m = "#pi^{0} mass [MeV]"; string t_piC_m = "#pi^{#pm} mass [MeV]"; int n_pi_m = 200; double l_pi_m = 0; double r_pi_m = 200;
  string t_dec = "decay mode"; int n_dec = 7; double l_dec = -1.5; double r_dec = 5.5;
  string t_trk = "N tracks"; int n_trk = 7; double l_trk = -0.5; double r_trk = 6.5;
  static const string arrN[] = {"0n", "1n", "Xn"}; vector<string> vec_neutrals (arrN, arrN + sizeof(arrN) / sizeof(arrN[0]) );
  static const string arrP[] = {"low", "medium", "high"}; vector<string> vec_prob (arrP, arrP + sizeof(arrP) / sizeof(arrP[0]) );
  static const string arrOr[] = {"PI", "UE", "PU", "PC", "FK", "UC", "MM", "Other"}; vector<string> vec_orig (arrOr, arrOr + sizeof(arrOr) / sizeof(arrOr[0]) );
  int min_prong = 1; int max_prong = GetOptMaxNtrks();
  int min_parent = 0; int max_parent = GetOptMaxNtrks();
  string t_eta_true = "#eta_{true}"; string t_eta_reco = "#eta_{reco}"; int n_eta = 102; double l_eta = -2.55; double r_eta = 2.55;
  string t_pt_true = "p_{T}^{true} [GeV]";   string t_pt_reco = "p_{T}^{reco} [GeV]"; int n_pt = 200; double l_pt = 0; double r_pt = 200;
  string t_phi_true = "#phi_{true} [rad]";   string t_phi_reco = "#phi_{reco} [rad]"; int n_phi = 64; double l_phi = -PI; double r_phi = PI;
  string t_dr = "#DeltaR";  int n_dr = 50; int l_dr = 0; int r_dr = 0.5;
  string t_deta = "#Delta#eta"; int n_deta = 50; double l_deta = 0; double r_deta = 0.5;
  string t_dpt = "#Deltap_T"; int n_dpt = 200; double l_dpt = -5; double r_dpt = 5;
  string t_Q_true = "Q_{true}"; string t_Q_reco = "Q_{reco}"; int n_Q = 4; double l_Q = -2; double r_Q = 2;
  string t_R = "R_{trk}^{calo}/#sigma(E/p)"; string t_R_raw = "R_{trk}^{calo}"; int n_R = 200; double l_R = -10; double r_R = 10;

  //distances
  m_HM.AddHisto( "tau_"+algo+"_visTrue_dR", "", "#Delta_{}R", "", 100, 0, 1);

  //inclusive distributions
  m_HM.AddHisto("tau_"+algo+"_lead_pt", "", "pT [GeV]", "", 500, 0, 500);
  m_HM.AddHisto("tau_"+algo+"_incl_pt", "", "pT [GeV]", "", 500, 0, 500);
  m_HM.AddHisto("tau_"+algo+"_incl_no_cut_pt", "", "pT [GeV]", "", 500, 0, 500);

  //inclusive resolution - incl stands for inclusive decay modes
  m_HM.AddHisto("tau_"+algo+"_incl_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
  m_HM.AddHisto("tau_"+algo+"_incl_reso_det", "", t_res_det, "", n_res_det, l_res_det, r_res_det);
  m_HM.AddHisto("tau_"+algo+"_incl_reso_log", "", t_res_log, "", n_res_log, l_res_log, r_res_log);
  m_HM.AddHisto("tau_"+algo+"_incl_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
  //pt intervals
  for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
    m_HM.AddHisto("tau_"+algo+"_incl_"+HpTrange(ipt)+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto("tau_"+algo+"_incl_"+HpTrange(ipt)+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
  }
  //2d
  m_HM.AddHisto("tau_"+algo+"_incl_reso_rel_vs_pt_true", "", t_pt_true, t_res_rel, n_pt, l_pt, r_pt, n_res_rel, l_res_rel, r_res_rel);
  m_HM.AddHisto("tau_"+algo+"_incl_pt_reco_vs_pt_true", "", t_pt_true, t_pt_reco, n_pt, l_pt, r_pt, n_pt, l_pt, r_pt);

  //resolution for decay modes
  for(DecayModesItr it = m_DecayModes.begin(); it != m_DecayModes.end(); it++) {
    //1d pt inclusive
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_reso_log", "", t_res_log, "", n_res_log, l_res_log, r_res_log);
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);

    //2d pt inclusive
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_reso_rel_vs_pt_true", "", t_pt_true, t_res_rel, n_pt, l_pt, r_pt, n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_pt_reco_vs_pt_true", "", t_pt_true, t_pt_reco, n_pt, l_pt, r_pt, n_pt, l_pt, r_pt);

    //pt intervals
    for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
    }//pt

    //bdt intervals
    for(int ibdt = 0; ibdt < (int)m_vec_bdt_bins.size() -1; ibdt++){
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_BDT_"+HBDTrange(ibdt)+"_pTbin1_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_BDT_"+HBDTrange(ibdt)+"_pTbin2_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_BDT_"+HBDTrange(ibdt)+"_pTbin3_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_BDT_"+HBDTrange(ibdt)+"_pTbin4_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    }//bdt


    //track origin - number of PI tracks
    for(int iPI = 0; iPI <= GetOptMaxNtrks(); iPI++)
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_matched_trk_orig_xPI"+Int2Str(iPI)+"_reso_rel",  "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);


    //true decay modes
    for(DecayModesItr itr = m_DecayModes.begin(); itr != m_DecayModes.end(); itr++){
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
      //pt intervals
      for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_true_"+*itr+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_true_"+*itr+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
      }//pt

      //parents
      for(int parent = min_parent; parent <=max_parent; parent++){
        //pt inclusive
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_parent_"+GetStringFromInt(parent)+"_reso_rel", "",
                      t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_parent_"+GetStringFromInt(parent)+"_reso_std", "",
                      t_res_std, "", n_res_std, l_res_std, r_res_std);
        //pt intervals
        for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
          m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_true_"+*itr+"_matched_trk_parent_"+GetStringFromInt(parent)+"_reso_rel", "",
                        t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
          m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_true_"+*itr+"_matched_trk_parent_"+GetStringFromInt(parent)+"_reso_std", "",
                        t_res_std, "", n_res_std, l_res_std, r_res_std);

        }//pt
      }//parents

      //kaon decays
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_kaon_decay_0_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_kaon_decay_1_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

      //track origin - number of PI tracks
      for(int iPI = 0; iPI <= GetOptMaxNtrks(); iPI++)
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_orig_xPI"+Int2Str(iPI)+"_reso_rel",  "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

      //track origins
      for(vector<string>::iterator iT = vec_orig.begin(); iT != vec_orig.end(); iT++){
        //pt inclusive
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_orig_"+*iT+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_orig_"+*iT+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);

        //pt intervals
        for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
          m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_true_"+*itr+"_matched_trk_orig_"+*iT+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
          m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_true_"+*itr+"_matched_trk_orig_"+*iT+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
        }//pt
      }//origins

    }// true decay modes
  }// reco decay modes DONE

  //resolution for prongs
  for(int iprong = min_prong; iprong <= max_prong; iprong++){

    //pt inclusive
    m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
    //pt intervals
    for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
    }//pt

    //bdt intervals
    for(int ibdt = 0; ibdt < (int)m_vec_bdt_bins.size() -1; ibdt++){
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_BDT_"+HBDTrange(ibdt)+"_pTbin1_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_BDT_"+HBDTrange(ibdt)+"_pTbin2_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_BDT_"+HBDTrange(ibdt)+"_pTbin3_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_BDT_"+HBDTrange(ibdt)+"_pTbin4_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    }//bdt

    //track origins
    for(vector<string>::iterator iT = vec_orig.begin(); iT != vec_orig.end(); iT++){
      //pt inclusive
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_matched_trk_orig_"+*iT+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_matched_trk_orig_"+*iT+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
      //pt intervals
      for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_matched_trk_orig_"+*iT+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_matched_trk_orig_"+*iT+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
      }//pt
    }//origins

  }//prongs DONE

  //also true prongs
  for(int iprong = min_prong; iprong <= max_prong; iprong++){

    //track origin - number of PI tracks
    for(int iPI = 0; iPI <= GetOptMaxNtrks(); iPI++)
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_matched_trk_orig_xPI"+Int2Str(iPI)+"_reso_rel",  "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

    for(int jprong = min_prong; jprong <= max_prong; jprong++){

      //track origin - number of PI tracks
      for(int iPI = 0; iPI <= GetOptMaxNtrks(); iPI++)
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_xPI"+Int2Str(iPI)+"_reso_rel",  "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);


      //pt incl
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
      //pt intervals
      for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_true_"+GetNprongStr(jprong)+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_true_"+GetNprongStr(jprong)+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
      }//pt

      //parents
      for(int parent = min_parent; parent <=max_parent; parent++){
        //pt inclusive
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_parent_"+GetStringFromInt(parent)+"_reso_rel", "",
                      t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_parent_"+GetStringFromInt(parent)+"_reso_std", "",
                      t_res_std, "", n_res_std, l_res_std, r_res_std);
        //pt intervals
        for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
          m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_true_"+GetNprongStr(jprong)+"_matched_trk_parent_"+GetStringFromInt(parent)+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
        }//pt
      }//parents

      //kaon decays
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_kaon_decay_0_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_kaon_decay_1_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

      //track origins
      for(vector<string>::iterator iT = vec_orig.begin(); iT != vec_orig.end(); iT++){
        //pt inclusive
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_"+*iT+"_reso_rel", "",
                      t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_"+*iT+"_reso_std", "",
                      t_res_std, "", n_res_std, l_res_std, r_res_std);
        //pt intervals
        for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
          m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_"+*iT+"_reso_rel", "",
                        t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
          m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_"+HpTrange(ipt)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_"+*iT+"_reso_std", "",
                        t_res_std, "", n_res_std, l_res_std, r_res_std);
        }//pt
      }//origins

    }//prongs
  }//prongs DONE

  //track matching scores
  for(int iprong = min_prong; iprong <= max_prong; iprong++)
    for(vector<string>::const_iterator it = vec_prob.begin(); it != vec_prob.end(); it++)
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_matched_trk_score_"+*it+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

  //resolution for neutrals
  for(vector<string>::const_iterator it = vec_neutrals.begin(); it != vec_neutrals.end(); it++){
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
    //pt intervals
    for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
    }//
  }//neutrals DONE

  //also for truth
  for(vector<string>::const_iterator it = vec_neutrals.begin(); it != vec_neutrals.end(); it++){
    for(vector<string>::const_iterator itr = vec_neutrals.begin(); itr != vec_neutrals.end(); itr++){
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
      //pt intervals
      for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_true_"+*itr+"_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_"+HpTrange(ipt)+"_true_"+*itr+"_reso_std", "", t_res_std, "", n_res_std, l_res_std, r_res_std);
      }//pt
    }
  }//neutrals + truth DONE

  //2D resolution
  for(DecayModesItr it = m_DecayModes.begin(); it != m_DecayModes.end(); it++) {
    for(DecayModesItr itr = m_DecayModes.begin(); itr != m_DecayModes.end(); itr++) {
      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_reso_rel_vs_pt_true",  "",  t_pt_true, t_res_rel, n_pt, l_pt, r_pt, n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_reso_rel_vs_eta_true", "",  t_eta_true, t_res_rel, n_eta, l_eta, r_eta, n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_reso_rel_vs_phi_true",  "",  t_phi_true, t_res_rel, n_phi, l_phi, r_phi, n_res_rel, l_res_rel, r_res_rel);

      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_pt_reco_vs_pt_true", "", t_pt_true, t_pt_reco, n_pt, l_pt, r_pt, n_pt, l_pt, r_pt );

      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_reso_rel_vs_pt_tau_rec_reso_rel",  "",  t_res_rel, t_res_rel,
                     n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);

      for(vector<string>::iterator iT = vec_orig.begin(); iT != vec_orig.end(); iT++){
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_orig_"+*iT+"_reso_rel_vs_pt_true",  "",  t_pt_true, t_res_rel, n_pt, l_pt, r_pt, n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_orig_"+*iT+"_reso_rel_vs_eta_true", "",  t_eta_true, t_res_rel, n_eta, l_eta, r_eta, n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_orig_"+*iT+"_reso_rel_vs_phi_true",  "",  t_phi_true, t_res_rel, n_phi, l_phi, r_phi, n_res_rel, l_res_rel, r_res_rel);

        m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_matched_trk_orig_"+*iT+"_pt_reco_vs_pt_true", "", t_pt_true, t_pt_reco, n_pt, l_pt, r_pt, n_pt, l_pt, r_pt );
      }

    }
  }
  for(int iprong = min_prong; iprong <= max_prong; iprong++){
    for(int jprong = min_prong; jprong <= max_prong; jprong++){
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_reso_rel_vs_pt_true","", t_pt_true, t_res_rel, n_pt, l_pt, r_pt, n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_reso_rel_vs_eta_true","", t_eta_true, t_res_rel, n_eta, l_eta, r_eta, n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_reso_rel_vs_phi_true","", t_phi_true, t_res_rel, n_phi, l_phi, r_phi, n_res_rel, l_res_rel, r_res_rel);

      m_HM.AddHisto( "tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_pt_reco_vs_pt_true", "", t_pt_true, t_pt_reco, n_pt, l_pt, r_pt, n_pt, l_pt, r_pt );

      for(vector<string>::iterator iT = vec_orig.begin(); iT != vec_orig.end(); iT++){
        m_HM.AddHisto( "tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_"+*iT+"_reso_rel_vs_pt_true",  "",
                       t_pt_true, t_res_rel, n_pt, l_pt, r_pt, n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto( "tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_"+*iT+"_reso_rel_vs_eta_true", "",
                       t_eta_true, t_res_rel, n_eta, l_eta, r_eta, n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto( "tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_"+*iT+"_reso_rel_vs_phi_true",  "",
                       t_phi_true, t_res_rel, n_phi, l_phi, r_phi, n_res_rel, l_res_rel, r_res_rel);

        m_HM.AddHisto( "tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_matched_trk_orig_"+*iT+"_pt_reco_vs_pt_true", "",
                       t_pt_true, t_pt_reco, n_pt, l_pt, r_pt, n_pt, l_pt, r_pt );
      }

    }
  }

  //resolutions for vertices
  m_HM.AddHisto("tau_"+algo+"_incl_reso_rel_vs_Nvtx", "", t_vtx, t_res_rel, n_vtx, l_vtx, r_vtx, n_res_rel, l_res_rel, r_res_rel);

  //pi mass spectrum
  m_HM.AddHisto("tau_"+algo+"_incl_pi0_m", "", t_pi0_m, "", n_pi_m, l_pi_m, r_pi_m);
  m_HM.AddHisto("tau_"+algo+"_incl_piC_m", "", t_piC_m, "", n_pi_m, l_pi_m, r_pi_m);

  //tracks
  m_HM.AddHisto("tau_"+algo+"_vs_true_nTrk", "", "true "+t_trk, "reco "+t_trk, n_trk, l_trk, r_trk, n_trk, l_trk, r_trk); //reco can be rec, pan, etc
  m_HM.AddHisto("tau_"+algo+"_vs_true_nPi0", "", "true "+t_pi0, "reco "+t_pi0, n_pi0, l_pi0, r_pi0, n_pi0, l_pi0, r_pi0);
  m_HM.AddHisto("tau_"+algo+"_vs_true_dec", "", "true "+t_dec, "reco "+t_dec, n_dec, l_dec, r_dec, n_dec, l_dec, r_dec);

  //eta - pT distributions
  m_HM.AddHisto("tau_"+algo+"_incl_eta", "", t_eta_reco, "", n_eta, l_eta, r_eta);
  m_HM.AddHisto("tau_"+algo+"_incl_pt", "", t_pt_reco, "", n_pt, l_pt, r_pt);

  //pt intervals
  for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
    m_HM.AddHisto("tau_"+algo+"_"+HpTrange(ipt)+"_pt", "", t_pt_reco, "", n_pt, l_pt, r_pt);
  }//

  for(DecayModesItr it = m_DecayModes.begin(); it != m_DecayModes.end(); it++) {
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_eta", "", t_eta_reco, "", n_eta, l_eta, r_eta);
    m_HM.AddHisto("tau_"+algo+"_"+*it+"_pt", "", t_pt_reco, "", n_pt, l_pt, r_pt);
    for(DecayModesItr itr = m_DecayModes.begin(); itr != m_DecayModes.end(); itr++){
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_eta", "", t_eta_reco, "", n_eta, l_eta, r_eta);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_pt", "", t_pt_reco, "", n_pt, l_pt, r_pt);
    }
  }

  for(int iprong = min_prong; iprong <= max_prong; iprong++){
    for(int jprong = min_prong; jprong <= max_prong; jprong++){
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_eta", "", t_eta_reco, "", n_eta, l_eta, r_eta);
      m_HM.AddHisto("tau_"+algo+"_"+GetNprongStr(iprong)+"_true_"+GetNprongStr(jprong)+"_pt", "", t_pt_reco, "", n_pt, l_pt, r_pt);
    }
  }

  for(vector<string>::const_iterator it = vec_neutrals.begin(); it != vec_neutrals.end(); it++){
    for(vector<string>::const_iterator itr = vec_neutrals.begin(); itr != vec_neutrals.end(); itr++){
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_eta", "", t_eta_reco, "", n_eta, l_eta, r_eta);
      m_HM.AddHisto("tau_"+algo+"_"+*it+"_true_"+*itr+"_pt", "", t_pt_reco, "", n_pt, l_pt, r_pt);
    }
  }

  //matched reco - truth track
  for(DecayModesItr it = m_DecayModes.begin(); it != m_DecayModes.end(); it++) {
    for(DecayModesItr itr = m_DecayModes.begin(); itr != m_DecayModes.end(); itr++) {
      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_TauTrack_RecoTruth_DR", "", t_dr, "", n_dr, l_dr, r_dr);
      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_TauTrack_RecoTruth_Deta", "", t_deta, "", n_deta, l_deta, r_deta);
      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_TauTrack_RecoTruth_DpT", "",  t_dpt, "", n_dpt, l_dpt, r_dpt);
      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_TauTrack_RecoTruth_DpTres", "",  t_res_rel, "",  n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "tau_"+algo+"_"+*it+"_true_"+*itr+"_TauTrack_RecoQ_vs_TruthQ", "",  t_Q_true, t_Q_reco, n_Q, l_Q, r_Q, n_Q, l_Q, r_Q);
    }
  }
  m_HM.AddHisto( "tau_"+algo+"_TauTrack_RecoTruth_DR", "", t_dr, "", n_dr, l_dr, r_dr);
  m_HM.AddHisto( "tau_"+algo+"_TauTrack_RecoTruth_Deta", "", t_deta, "", n_deta, l_deta, r_deta);
  m_HM.AddHisto( "tau_"+algo+"_TauTrack_RecoTruth_DpT", "",  t_dpt, "", n_dpt, l_dpt, r_dpt);
  m_HM.AddHisto( "tau_"+algo+"_TauTrack_RecoTruth_DpTres", "",  t_res_rel, "",  n_res_rel, l_res_rel, r_res_rel);
  m_HM.AddHisto( "tau_"+algo+"_TauTrack_RecoQ_vs_TruthQ", "",  t_Q_true, t_Q_reco, n_Q, l_Q, r_Q, n_Q, l_Q, r_Q);

  //classification rates
  m_HM.AddHisto( "tau_"+algo+"_decay_mode_classification", "", "True Decay Mode", "Reco Decay Mode", 8, 0, 8, 8, 0, 8);
  for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
    m_HM.AddHisto("tau_"+algo+"_"+HpTrange(ipt)+"_decay_mode_classification", "", "True Decay Mode", "Reco Decay Mode", 8, 0, 8, 8, 0, 8);
  }//


  //control / cross-check plots
  m_HM.AddHisto( "test_dPtOverPt_visTrueTau_auto_manual", "", "pt (manual-auto)/auto", "", 200, -0.1, 0.1 );
  m_HM.AddHisto( "test_dPtOverPt_visTrueTau_auto_manual_vs_visTrueReco_dR", "", "pt (manual-auto)/auto", "dR", 400, -0.2, 0.2, 200, 0, 0.2);//-
  m_HM.AddHisto( "test_r1p0n_t1p0n_trkRecoTrue_tauRecoVisTrue_dRes", "", "res ", "", 200, -0.5, 0.5 );
  m_HM.AddHisto( "test_r1p0n_t1p0n_lt_m025_rel_res_use_tauRec", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
  m_HM.AddHisto( "test_r1p0n_t1p0n_gt_p025_rel_res_use_tauRec", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
  m_HM.AddHisto( "test_r1p0n_t1p0n_rel_res_use_tauRec", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
  m_HM.AddHisto( "test_r1p0n_t1p0n_rel_res_tauRec_vs_PanTau", "", "PanTau resolution", "TauRec resolution", n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);
  m_HM.AddHisto( "test_r1p0n_t1p0n_rel_res_vs_TruthMatchedDR", "", "PanTau resolution", "DR(reco,vis-true)", n_res_rel, l_res_rel, r_res_rel, 200, 0, 0.2);
  m_HM.AddHisto( "test_t1p0n_visTrue_ditau_DR", "", "dR", "", 600, 0, 6);
  m_HM.AddHisto( "test_t1pwithn_visTrue_ditau_DR", "", "dR", "", 600, 0, 6);
  m_HM.AddHisto( "test_t1p0n_t10n_visTrue_ditau_DR", "", "dR", "", 600, 0, 6);
  m_HM.AddHisto( "test_not_t1p0n_t10n_visTrue_ditau_DR", "", "dR", "", 600, 0, 6);

  ///trk-tau compatibility
  m_HM.AddHisto( "test_lead_recoTrk_over_panTrk", "", "trk pTreco/ trk pTpan", "", 200, 0, 10);
  m_HM.AddHisto( "test_lead_recoTrk_panTrk_res", "", "Res(trk pTreco, trk pTpan)", "", 200, 0, 10);
  m_HM.AddHisto( "test_lead_recoTrk_panTrk_dR", "", "dR(trk reco, trk pan tau)", "", 200, 0, 0.05);
  m_HM.AddHisto( "test_lead_recoTrk_d0", "", "d0", "", 2000, -10, 10);
  m_HM.AddHisto( "test_lead_recoTrk_z0", "", "z0", "", 2000, -100, 100);
  m_HM.AddHisto( "test_lead_recoTrk_z0SinTheta", "", "z0SinTheta", "", 2000, -10, 10);
  m_HM.AddHisto( "test_lead_recoTrk_nSCTHits", "", "# SCT Hits", "", 50, 0, 50);
  m_HM.AddHisto( "test_lead_recoTrk_nPixHits", "", "# Pixel Hits", "", 50, 0, 50);

  m_HM.AddHisto( "test_incl_rec_track_0_pT_over_rec_tau_pT", "", "pT rec track / pT tauRec", "", 200, 0, 10 );
  m_HM.AddHisto( "test_incl_rec_track_0_pT_over_pan_tau_pT", "", "pT rec track / pT PanTau", "", 200, 0, 10 );
  m_HM.AddHisto( "test_incl_pan_track_0_pT_over_rec_tau_pT", "", "pT pan track / pT tauRec", "", 200, 0, 10 );
  m_HM.AddHisto( "test_incl_pan_track_0_pT_over_pan_tau_pT", "", "pT pan track / pT PanTau", "", 200, 0, 10 );

  m_HM.AddHisto( "test_incl_rec_track_0_pT_over_rec_tau_pT_vs_tau_rec_reso_rel", "tauRec", t_res_rel, "pT track / pT tauRec", n_res_rel, l_res_rel, r_res_rel, 200, 0, 10);
  m_HM.AddHisto( "test_incl_rec_track_0_pT_over_rec_tau_pT_vs_tau_pan_reso_rel", "PanTau", t_res_rel, "pT track / pT tauRec", n_res_rel, l_res_rel, r_res_rel, 200, 0, 10);

  m_HM.AddHisto( "test_incl_tau_pan_compatible_trk_pT_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
  for(DecayModesItr it = m_DecayModes.begin(); it != m_DecayModes.end(); it++) {
    m_HM.AddHisto( "test_r"+*it+"_tau_pan_compatible_trk_pT_reso_rel", "PanTau", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto( "test_r"+*it+"_tau_pan_compatible_trk_pT_reso_rel_vs_pt_true", "",  t_pt_true, t_res_rel, n_pt, l_pt, r_pt, n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto( "test_r"+*it+"_kaon_decay_0_tau_pan_compatible_trk_pT_reso_rel", "PanTau", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto( "test_r"+*it+"_kaon_decay_1_tau_pan_compatible_trk_pT_reso_rel", "PanTau", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

    m_HM.AddHisto( "test_r"+*it+"_compatible_trk_pT_PanTau_only_pass_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto( "test_r"+*it+"_compatible_trk_pT_PanTau_only_fail_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto( "test_r"+*it+"_compatible_trk_pT_tauRec_only_pass_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
    m_HM.AddHisto( "test_r"+*it+"_compatible_trk_pT_tauRec_only_fail_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

    for(DecayModesItr itr = m_DecayModes.begin(); itr != m_DecayModes.end(); itr++){
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_tau_pan_compatible_trk_pT_reso_rel", "PanTau", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_tau_pan_compatible_trk_pT_reso_rel_vs_pt_true", "",  t_pt_true, t_res_rel, n_pt, l_pt, r_pt, n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_0_tau_pan_compatible_trk_pT_reso_rel", "PanTau", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_1_tau_pan_compatible_trk_pT_reso_rel", "PanTau", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_compatible_trk_pT_PanTau_only_pass_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_compatible_trk_pT_PanTau_only_fail_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_compatible_trk_pT_tauRec_only_pass_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_compatible_trk_pT_tauRec_only_fail_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_rec_track_0_pT_over_rec_tau_pT", "", "pT rec track / pT tauRec", "", 200, 0, 10 );
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_rec_track_0_pT_over_pan_tau_pT", "", "pT rec track / pT PanTau", "",  200, 0, 10 );
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_pT_over_rec_tau_pT", "", "pT pan track / pT tauRec", "",  200, 0, 10 );
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_pT_over_pan_tau_pT", "", "pT pan track / pT PanTau", "",  200, 0, 10 );

      for(int parent = min_parent; parent <=max_parent; parent++){
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_matched_trk_parent_"+GetStringFromInt(parent)+"_pan_track_0_pT_over_rec_tau_pT", "", "pT pan track / pT tauRec", "",  200, 0, 10);
      }

      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel", "",  t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_pT", "PanTau", "trk resolution", "pan track pT [GeV]",
                     n_res_rel, l_res_rel, r_res_rel, 200, 0, 200);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_Eta", "PanTau", "trk resolution", "pan track #eta",
                     n_res_rel, l_res_rel, r_res_rel, 25, 0, 2.5);

      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_pT", "PanTau", "trk resolution", "truth trk pT [GeV]",
                     n_res_rel, l_res_rel, r_res_rel, 200, 0, 200);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_Eta", "PanTau", "trk resolution", "truth trk #eta",
                     n_res_rel, l_res_rel, r_res_rel, 25, 0, 2.5);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_dR", "PanTau", "trk resolution", "dR(truth trk, reco trk)",
                     n_res_rel, l_res_rel, r_res_rel, 100, 0, 0.1);

      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", "", "trk resolution", "pT pan track / pT tauRec",
                     n_res_rel, l_res_rel, r_res_rel, 200, 0, 10);
      //
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", "", "PanTau resolution", "pT pan track / pT tauRec",
                     n_res_rel, l_res_rel, r_res_rel, 200, 0, 10);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", "", "PanTau pT [GeV]", "pT pan track / pT tauRec",
                     200, 0, 200, 200, 0, 10);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", "", "tauRec pT [GeV]", "pT pan track / pT tauRec",
                     200, 0, 200, 200, 0, 10);
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel", "", "trk resolution", "PanTau resolution",
                     n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);

      for(int ik = 0; ik <=1; ik++){
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", "", "PanTau resolution", "pT pan track / pT tauRec",
                       n_res_rel, l_res_rel, r_res_rel, 200, 0, 10);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", "", "PanTau resolution", "pT pan track / pT tauRec",
                       n_res_rel, l_res_rel, r_res_rel, 200, 0, 10);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_pan_track_0_pT_over_rec_tau_pT", "", "PanTau resolution", "pT pan track / pT tauRec",
                       n_res_rel, l_res_rel, r_res_rel, 200, 0, 10);

        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", "", "PanTau pT [GeV]", "pT pan track / pT tauRec",
                       200, 0, 200, 200, 0, 10);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", "", "PanTau pT [GeV]", "pT pan track / pT tauRec",
                       200, 0, 200, 200, 0, 10);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_pan_pT_vs_pan_track_0_pT_over_rec_tau_pT", "", "PanTau pT [GeV]", "pT pan track / pT tauRec",
                       200, 0, 200, 200, 0, 10);

        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", "", "tauRec pT [GeV]", "pT pan track / pT tauRec",
                       200, 0, 200, 200, 0, 10);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", "", "tauRec pT [GeV]", "pT pan track / pT tauRec",
                       200, 0, 200, 200, 0, 10);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_tau_rec_pT_vs_pan_track_0_pT_over_rec_tau_pT", "", "tauRec pT [GeV]", "pT pan track / pT tauRec",
                       200, 0, 200, 200, 0, 10);

        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel", "", "trk resolution", "PanTau resolution",
                       n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel", "", "trk resolution", "PanTau resolution",
                       n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_pan_track_0_matched_truth_reso_rel_vs_reso_rel", "", "trk resolution", "PanTau resolution",
                       n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);

        //with track origins
        for(vector<string>::iterator iT = vec_orig.begin(); iT != vec_orig.end(); iT++){
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_pan_track_0_matched_truth_trk_orig_"+*iT+"_reso_rel_vs_reso_rel", "",
                         "trk resolution", "PanTau resolution", n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_pan_track_0_matched_truth_trk_orig_"+*iT+"_reso_rel_vs_reso_rel", "",
                         "trk resolution", "PanTau resolution", n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_pan_track_0_matched_truth_trk_orig_"+*iT+"_reso_rel_vs_reso_rel", "",
                         "trk resolution", "PanTau resolution", n_res_rel, l_res_rel, r_res_rel, n_res_rel, l_res_rel, r_res_rel);
        }

      }


      m_HM.AddHisto( "test_trk_quality_"+*it+"_true_"+*itr+"_reso_rel", "",  t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);

      m_HM.AddHisto( "test_trk_quality_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel", "", "trk resolution", "", n_res_rel, l_res_rel, r_res_rel);

      m_HM.AddHisto( "test_trk_quality_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_pT", "PanTau", "trk resolution", "pan track pT [GeV]",
                     n_res_rel, l_res_rel, r_res_rel, 200, 0, 200);


      m_HM.AddHisto( "test_trk_quality_r"+*it+"_t"+*itr+"_pan_track_0_matched_truth_reso_rel_vs_pan_track_0_matched_truth_pT", "PanTau", "trk resolution", "truth track pT [GeV]",
                     n_res_rel, l_res_rel, r_res_rel, 200, 0, 200);

    }
  }

  //and for tracks
  /* for(int iprong = min_prong; iprong <= max_prong; iprong++){
     for(int jprong = min_prong; jprong <= max_prong; jprong++){

     }
     }
  */

  // = = = weighted track compatibility = = =

  m_HM.AddHisto("test_rec_track_0_qoverp_vs_err_qoverp", "1/p", "#sigma(#frac{q}{p})  [GeV^{-1}]", "#frac{q}{p}  [GeV^{-1}]", 100, 0, 0.01, 200, -0.1, 0.1);
  m_HM.AddHisto("test_rec_track_0_qoverpt_vs_err_qoverpt", "1/pT", "#sigma(#frac{q}{pT})  [GeV^{-1}]", "#frac{q}{pT} [GeV^{-1}]  [GeV^{-1}]", 100, 0, 0.01, 200, -0.1, 0.1);

  //pulls
  m_HM.AddHisto( "test_rec_track_0_pull_energy", "", "", "(E^{reco}-E^{truth})/#Delta{}E^{reco}", 61, -3.05, 3.05);
  m_HM.AddHisto( "test_rec_track_0_pull_qoverp", "", "", "(|q/p|^{reco}-|q/p|^{truth})/#Delta{}|q/p|^{reco}", 61, -3.05, 3.05);

  for(int ipt = 0; ipt < (int)m_vec_pt_bins.size() -1; ipt++){
    m_HM.AddHisto( "test_rec_track_0_"+HpTrange(ipt)+"_pull_energy", "", "", "(E^{reco}-E^{truth})/#Delta{}E^{reco}", 61, -3.05, 3.05);
    m_HM.AddHisto( "test_rec_track_0_"+HpTrange(ipt)+"_pull_qoverp", "", "", "(|q/p|^{reco}-|q/p|^{truth})/#Delta{}|q/p|^{reco}", 61, -3.05, 3.05);
  }

  for(int iEta = 0; iEta < (int)m_vec_eta_bins.size() -1; iEta++){
    m_HM.AddHisto( "test_rec_track_0_"+Hetarange(iEta)+"_pull_energy", "", "", "(E^{reco}-E^{truth})/#Delta{}E^{reco}", 61, -3.05, 3.05);
    m_HM.AddHisto( "test_rec_track_0_"+Hetarange(iEta)+"_pull_qoverp", "", "", "(|q/p|^{reco}-|q/p|^{truth})/#Delta{}|q/p|^{reco}", 61, -3.05, 3.05);
  }

  // R vs resolution
  for(DecayModesItr it = m_DecayModes.begin(); it != m_DecayModes.end(); it++) {
    for(DecayModesItr itr = m_DecayModes.begin(); itr != m_DecayModes.end(); itr++) {

      //raw
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_reso_rel_vs_R_trk0_calo",
                     "", t_res_rel, t_R_raw, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
      //weighted
      m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_reso_rel_vs_R_trk0_calo_w",
                     "", t_res_rel, t_R, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);

      //+kaons info
      for(int ik = 0; ik <=1; ik++){
        //raw
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_R_trk0_calo",
                       "", t_res_rel, t_R_raw, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_R_trk0_calo",
                       "", t_res_rel, t_R_raw, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_R_trk0_calo",
                       "", t_res_rel, t_R_raw, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);

        //weighted
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_R_trk0_calo_w",
                       "", t_res_rel, t_R, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_R_trk0_calo_w",
                       "", t_res_rel, t_R, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
        m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_reso_rel_vs_R_trk0_calo_w",
                       "", t_res_rel, t_R, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);

        //+trk origin info
        for(vector<string>::iterator iT = vec_orig.begin(); iT != vec_orig.end(); iT++){
          //raw
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_trk_0_orig_"+*iT+"_reso_rel_vs_R_trk0_calo",
                         "", t_res_rel, t_R_raw, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_trk_0_orig_"+*iT+"_reso_rel_vs_R_trk0_calo",
                         "", t_res_rel, t_R_raw, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_trk_0_orig_"+*iT+"_reso_rel_vs_R_trk0_calo",
                         "", t_res_rel, t_R_raw, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);

          //weighted
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_kaon_decay_"+Int2Str(ik)+"_trk_0_orig_"+*iT+"_reso_rel_vs_R_trk0_calo_w",
                         "", t_res_rel, t_R, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_charged_kaon_decay_"+Int2Str(ik)+"_trk_0_orig_"+*iT+"_reso_rel_vs_R_trk0_calo_w",
                         "", t_res_rel, t_R, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);
          m_HM.AddHisto( "test_r"+*it+"_t"+*itr+"_neutral_kaon_decay_"+Int2Str(ik)+"_trk_0_orig_"+*iT+"_reso_rel_vs_R_trk0_calo_w",
                         "", t_res_rel, t_R, n_res_rel, l_res_rel, r_res_rel, n_R, l_R, r_R);

        }//origin
      }//kaons
    }//decay mode
  }//decay mode

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::CreatePanTauList(){

  CleanListOfPanTauTaus();

  for(int i=0; i < (int)tau_pantau_CellBased_isPanTauCandidate->size(); i++)
    if( tau_pantau_CellBased_isPanTauCandidate->at(i) == 1){
      TauObject_PanTau currentPanTauTau = TauObject_PanTau(tau_pantau_CellBased_RecoModePanTau->at(i),
                                                           tau_pantau_CellBased_RecoModeCellBased->at(i),
                                                           tau_pantau_CellBased_final_pt->at(i),
                                                           tau_pantau_CellBased_final_eta->at(i),
                                                           tau_pantau_CellBased_final_phi->at(i),
                                                           tau_pantau_CellBased_final_m->at(i),
                                                           tau_pantau_CellBased_ChargedEFOs_pt->at(i),
                                                           tau_pantau_CellBased_ChargedEFOs_eta->at(i),
                                                           tau_pantau_CellBased_ChargedEFOs_phi->at(i),
                                                           tau_pantau_CellBased_ChargedEFOs_m->at(i),
                                                           tau_pantau_CellBased_Pi0NeutEFOs_pt->at(i),
                                                           tau_pantau_CellBased_Pi0NeutEFOs_eta->at(i),
                                                           tau_pantau_CellBased_Pi0NeutEFOs_phi->at(i),
                                                           tau_pantau_CellBased_Pi0NeutEFOs_m->at(i),
                                                           tau_pantau_CellBased_NeutralEFOs_pt->at(i),
                                                           tau_pantau_CellBased_NeutralEFOs_eta->at(i),
                                                           tau_pantau_CellBased_NeutralEFOs_phi->at(i),
                                                           tau_pantau_CellBased_NeutralEFOs_m->at(i));

      m_TauList_PanTau.push_back(currentPanTauTau);
    }
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::AssociateRecoToVisTrue(){

  for(SuperTauVecItr it = m_TauList_TrueVisTau.begin(); it != m_TauList_TrueVisTau.end(); it++){ //true vis tau first to gain some cpu time
    for(SuperTauVecItr itr = m_TauList_RecoTau.begin(); itr != m_TauList_RecoTau.end(); itr++){
      double dR = DeltaR( it->hlv("truevis"), itr->hlv("reco") );
      if(dR < m_opt_reco_tau_vis_true_max_dR ){
        itr->Set_match_vis_tau(true);
        itr->Set_match_vis_tau_object( *it );
      }
    }
  }

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::AssociatePanToVisTrue(){

  CleanListOfHyperTaus();

  for(PanTauVecItr itr = m_TauList_PanTau.begin(); itr != m_TauList_PanTau.end(); itr++){
    double minDR(1e3);
    SuperTau matchedTrueVis;
    for(SuperTauVecItr it = m_TauList_TrueVisTau.begin(); it != m_TauList_TrueVisTau.end(); it++){
      double dR = DeltaR( it->hlv("truevis"), itr->getMomentum().Eta(), itr->getMomentum().Phi() );
      if( dR < minDR ){
        minDR = dR;
        matchedTrueVis = *it;
      }
    }//true vis tau list
    bool kMatch = (minDR < GetOptRecoTauVisTrueTauMatchMaxDR() );
    HyperTau htau( *itr, matchedTrueVis, kMatch);
    m_TauList_HyperTau.push_back(htau);
  }//pantau list

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::AssociateHyperToReco(){
  //  cout<<"\n";
  for(HyperTauVecItr itrHyp = m_TauList_HyperTau.begin(); itrHyp != m_TauList_HyperTau.end(); itrHyp++){
    //    int j(0); int im;
    SuperTau matchedReco;
    double minDR(1e3);
    for(SuperTauVecItr itrRec = m_TauList_RecoTau.begin(); itrRec != m_TauList_RecoTau.end(); itrRec++){
      double dR = DeltaR( itrHyp->GetPanHLV(), itrRec->hlv() );
      if(dR < GetOptRecoTauPanTauMaxDR() && dR < minDR ){
        minDR = dR;
        matchedReco = *itrRec;
        //      im = j;
        // cout<<j<<"/"<<m_TauList_RecoTau.size()<<" dR "<<dR<<" pT pan "<<itrHyp->GetPanHLV().Pt()/1000. <<" rec "<<itrRec->hlv().Pt() << endl;
      }//matched
      //j++;
    }//tauRec
    //    cout<<"matched "<<im<<endl;
    itrHyp->LinkReco(matchedReco);
  }//PanTau

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::CreateHyperTau(){

  //clean vector
  CleanListOfHyperTaus();

  //check size
  if(tau_n != (int)tau_pantau_CellBased_isPanTauCandidate->size() ) cerr<<"void TauMain::CreateHyperTau - tau_n and pantau n mismatch "<<endl;

  for(int i=0; i < (int)tau_pantau_CellBased_isPanTauCandidate->size(); i++){
    if( tau_pantau_CellBased_isPanTauCandidate->at(i) != 1) continue;

    //PanTau
    TauObject_PanTau currentPanTau = TauObject_PanTau(tau_pantau_CellBased_RecoModePanTau->at(i),
                                                      tau_pantau_CellBased_RecoModeCellBased->at(i),
                                                      tau_pantau_CellBased_final_pt->at(i),
                                                      tau_pantau_CellBased_final_eta->at(i),
                                                      tau_pantau_CellBased_final_phi->at(i),
                                                      tau_pantau_CellBased_final_m->at(i),
                                                      tau_pantau_CellBased_ChargedEFOs_pt->at(i),
                                                      tau_pantau_CellBased_ChargedEFOs_eta->at(i),
                                                      tau_pantau_CellBased_ChargedEFOs_phi->at(i),
                                                      tau_pantau_CellBased_ChargedEFOs_m->at(i),
                                                      tau_pantau_CellBased_Pi0NeutEFOs_pt->at(i),
                                                      tau_pantau_CellBased_Pi0NeutEFOs_eta->at(i),
                                                      tau_pantau_CellBased_Pi0NeutEFOs_phi->at(i),
                                                      tau_pantau_CellBased_Pi0NeutEFOs_m->at(i),
                                                      tau_pantau_CellBased_NeutralEFOs_pt->at(i),
                                                      tau_pantau_CellBased_NeutralEFOs_eta->at(i),
                                                      tau_pantau_CellBased_NeutralEFOs_phi->at(i),
                                                      tau_pantau_CellBased_NeutralEFOs_m->at(i));

    //VisTrueTau
    double minDR(1e3);
    bool kVisTrueMatch(false);
    SuperTau matchedTrueVis;

    if(GetOptVisTrueTauMatchUseAssocIndex()){ // match vis true tau to reco tau using the association index
      kVisTrueMatch = (*tau_trueTauAssoc_matched)[i];
      minDR = (*tau_trueTauAssoc_dr)[i];
      if( (*tau_trueTauAssoc_matched)[i] ){
        for(SuperTauVecItr it = m_TauList_TrueVisTau.begin(); it != m_TauList_TrueVisTau.end(); it++){
          if((*tau_trueTauAssoc_index)[i] == (int)it->GetInfo("index")){
            //cout<<(*trueTau_vis_Et)[ (*tau_trueTauAssoc_index)[i] ]/1000.  << " "<<currentPanTau.getMomentum().Pt()/1000.<<" "<<(*tau_pt)[i]/1000.<<endl;
            matchedTrueVis = *it;
            break;
          }
        }
      }

    }else{// match vis true tau to reco tau using the min distance DR
      for(SuperTauVecItr it = m_TauList_TrueVisTau.begin(); it != m_TauList_TrueVisTau.end(); it++){
        double dR = DeltaR( it->hlv("truevis"), currentPanTau.getMomentum().Eta(), currentPanTau.getMomentum().Phi() );
        if( dR < minDR ){
          minDR = dR;
          matchedTrueVis = *it;
        }
      }//true vis tau list
      kVisTrueMatch = (minDR < GetOptRecoTauVisTrueTauMatchMaxDR() );

    }

    //tau rec
    TLorentzVector v4RecTau;
    v4RecTau.SetPtEtaPhiM( (*tau_pt)[i]/1000., (*tau_eta)[i], (*tau_phi)[i], (*tau_m)[i]/1000. );
    SuperTau sRecTau;
    sRecTau.Set_hlv(v4RecTau);
    sRecTau.Set_index(i);
    sRecTau.Set_author( (*tau_author)[i] );
    sRecTau.Set_charge( (int)((*tau_charge)[i]) );
    sRecTau.Set_numTrack( (*tau_numTrack)[i] );
    sRecTau.Set_JetBDTSig( (*tau_JetBDTSigLoose)[i], (*tau_JetBDTSigMedium)[i], (*tau_JetBDTSigTight)[i]);
    sRecTau.Set_JetBDTSigScore( (*tau_BDTJetScore)[i] );
    //pions - Vince
    /* to fix
       TLorentzVector leadingRecPion;
       leadingRecPion.SetPtEtaPhiM(0,0,0,0);
       for(SuperTauVecItr it = m_TauList_TrueVisTau.begin(); it != m_TauList_TrueVisTau.end(); it++){
       TLV vec_NeutralPions = currentPanTau.getNeutralPions();
       if (vec_NeutralPions.size()!=0){
       for (int j=0;j<(int)vec_NeutralPions.size();j++){
       if (vec_NeutralPions[j].Pt()>leadingRecPion.Pt())leadingRecPion=vec_NeutralPions[j];
       }
       }
       }
       cout<<"leading Rec"<<endl;

       TLorentzVector leadingTruePion;
       leadingTruePion.SetPtEtaPhiM(0,0,0,0);
       for(SuperTauVecItr it = m_TauList_TrueVisTau.begin(); it != m_TauList_TrueVisTau.end(); it++){
       TLV vec_NeutralPions = currentPanTau.getNeutralPions();
       if (vec_NeutralPions.size()!=0){
       for (int j=0;j<(int)vec_NeutralPions.size();j++){
       if (vec_NeutralPions[j].Pt()>leadingTruePion.Pt())leadingTruePion=vec_NeutralPions[j];
       }
       }
       }
       cout<<"leading True"<<endl;
    */

    //keep tau in the list
    //HyperTau htau( currentPanTau, matchedTrueVis, kVisTrueMatch, sRecTau,leadingRecPion,leadingTruePion); // Vince - will be the default when fixed
    HyperTau htau( currentPanTau, matchedTrueVis, kVisTrueMatch, minDR, sRecTau);
    m_TauList_HyperTau.push_back(htau);

  }

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::AssociateHyperTauTracksToTruthTracks(){


  if(GetOptUseOfficialTruthMatching()  ){///M. Milesi's tool
    //initialize tool
    m_TruthTrackMatchingTool.Initialize(mc_pt,
                                        mc_eta,
                                        mc_phi,
                                        mc_m,
                                        mc_charge,
                                        mc_pdgId,
                                        mc_status,
                                        mc_barcode,
                                        mc_vx_barcode,
                                        mc_child_index,
                                        mc_parent_index,
                                        trk_pt,
                                        trk_eta,
                                        trk_phi,
                                        trk_mc_probability,
                                        trk_mc_barcode
                                        );

    for(HyperTauVecItr itr = m_TauList_HyperTau.begin(); itr != m_TauList_HyperTau.end(); itr++){
      TLV vec_pan_hlv_ChargedPions = itr->GetPanTau().getChargedPions();
      bool kTruthKaonDecay(false);
      bool kTruthChargedKaonDecay(false);
      bool kTruthNeutralKaonDecay(false);

      int rTauIndex = (int)itr->GetRecoTau().GetInfo("index");
      for(TLVItr it = vec_pan_hlv_ChargedPions.begin(); it != vec_pan_hlv_ChargedPions.end(); it++){

        SmartTrack strack;
        strack.SetTauParentPdgId( GetOptTauParentPDGID() );
        strack.SetTauTrackPtEtaPhi( it->Pt()/1000., it->Eta(), it->Phi() ); // set the charged pion pt(GeV), eta, phi - use to find the reco track + extra info

        m_TruthTrackMatchingTool.Classify( *it );
        //m_TruthTrackMatchingTool.Classify( &itr->GetPanHLV(), *it );
        //m_TruthTrackMatchingTool.PrintOutput();
        //int TauMatchStatus = m_TruthTrackMatchingTool.getTrackMatchStatus();
        //int TauType = m_TruthTrackMatchingTool.getTauType();
        int TrackMatchStatus = m_TruthTrackMatchingTool.getTrackMatchStatus();
        int TrackSpuriousType = m_TruthTrackMatchingTool.getTrackSpuriousType();
        int MCParticleMatchIndex = TrackMatchStatus ==1 ? m_TruthTrackMatchingTool.getMCParticleMatchIndex() : -1;
        //kTruthKaonDecayfloat DeltaRTruthPartner = m_TruthTrackMatchingTool.getDeltaRTruthPartner();
        //cout<<"type: "<<TrackSpuriousType<<" stat: "<<TrackMatchStatus<<endl;

        if(TrackMatchStatus==1){
          bool kChKaon(false); bool kNeuKaon(false);
          TruthKaonDecay(MCParticleMatchIndex, kChKaon, kNeuKaon);
          if(!kTruthChargedKaonDecay) kTruthChargedKaonDecay = kChKaon;
          if(!kTruthNeutralKaonDecay) kTruthNeutralKaonDecay = kNeuKaon;
        }
        vector<int>* dummyInt = 0;
        vector<float>* dummyFloat = 0;
        strack.UseExternalInformation(//truth matching tool results
                                      TrackMatchStatus,
                                      TrackSpuriousType,
                                      MCParticleMatchIndex,
                                      //matching options
                                      GetOptPanTauTrkRecoTrkMatchMaxDR(),
                                      GetOptPanTauTrkRecoTrkMatchMaxRelFracPt(),
                                      GetOptPanTauTrkRecoTrkMatchClosestDR(),
                                      //reco tracks
                                      trk_pt,
                                      trk_eta,
                                      trk_phi,
                                      trk_qoverp,
                                      trk_mc_barcode,
                                      trk_mc_probability,
                                      /*&tau_track_atTJVA_pt->at(rTauIndex),
                                        &tau_track_atTJVA_eta->at(rTauIndex),
                                        &tau_track_atTJVA_phi->at(rTauIndex),
                                        &tau_track_atTJVA_qoverp->at(rTauIndex),*/
                                      /*&tau_track_pt->at(rTauIndex),
                                        &tau_track_eta->at(rTauIndex),
                                        &tau_track_phi->at(rTauIndex),
                                        &tau_track_qoverp->at(rTauIndex),
                                        dummyInt,
                                        dummyFloat,*/
                                      //mc true particle
                                      mc_barcode,
                                      mc_pdgId,
                                      mc_parent_index,
                                      mc_child_index,
                                      mc_pt,
                                      mc_eta,
                                      mc_phi,
                                      mc_m,
                                      mc_charge);

        itr->AddSmartTrack(strack);
      }//charged pions - tracks

      kTruthKaonDecay = kTruthChargedKaonDecay || kTruthNeutralKaonDecay;

      itr->SetTruthKaonDecay(kTruthKaonDecay);
      itr->SetTruthChargedKaonDecay(kTruthChargedKaonDecay);
      itr->SetTruthNeutralKaonDecay(kTruthNeutralKaonDecay);

    }//hyper tau


  }else{// MANUAL

    for(HyperTauVecItr itr = m_TauList_HyperTau.begin(); itr != m_TauList_HyperTau.end(); itr++){
      TLV vec_pan_hlv_ChargedPions = itr->GetPanTau().getChargedPions();

      for(TLVItr it = vec_pan_hlv_ChargedPions.begin(); it != vec_pan_hlv_ChargedPions.end(); it++){
        SmartTrack strack;
        strack.SetTauParentPdgId( GetOptTauParentPDGID() );
        strack.SetTauTrackPtEtaPhi( it->Pt()/1000., it->Eta(), it->Phi() ); // charged pion kinematics in GeV
        strack.MatchTrackToTruth_MaxDR_MaxRelFracPt_TRK_Pt_Eta_Phi_QoP_TRKMC_Bc_Prob_MC_Bc_PdgId_parentIdx_childIdx_Pt_Eta_Phi_Eta_Q(
                                                                                                                                     GetOptPanTauTrkRecoTrkMatchMaxDR(),
                                                                                                                                     GetOptPanTauTrkRecoTrkMatchMaxRelFracPt(),
                                                                                                                                     GetOptPanTauTrkRecoTrkMatchClosestDR(),
                                                                                                                                     trk_pt,
                                                                                                                                     trk_eta,
                                                                                                                                     trk_phi,
                                                                                                                                     trk_qoverp,
                                                                                                                                     trk_mc_barcode,
                                                                                                                                     trk_mc_probability,
                                                                                                                                     mc_barcode,
                                                                                                                                     mc_pdgId,
                                                                                                                                     mc_parent_index,
                                                                                                                                     mc_child_index,
                                                                                                                                     mc_pt,
                                                                                                                                     mc_eta,
                                                                                                                                     mc_phi,
                                                                                                                                     mc_m,
                                                                                                                                     mc_charge);

        itr->AddSmartTrack(strack);
      }//charged pions - tracks
    }//hyper tau

  }//own or official tool for matching


}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::CreateTrueTauList(){

  //empty

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::CreateTrueVisTauList(){

  CleanListOfTrueVisTaus(); // empty vector

  if( GetOptBuildVisTauTrue() == "auto") CreateTrueVisTauListAuto();
  else if( GetOptBuildVisTauTrue() == "manual") CreateTrueVisTauListManual();
  else cerr<<"TauMain::CreateTrueVisTauList - don't know what to do with "<< GetOptBuildVisTauTrue() <<endl;

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::CreateTrueVisTauListAuto(){
  //method using branch info

  for(int itau = 0; itau < trueTau_n; itau++ ){
    TLorentzVector ptau;
    ptau.SetPtEtaPhiM( (*trueTau_vis_Et)[itau]/1000., (*trueTau_vis_eta)[itau], (*trueTau_vis_phi)[itau], (*trueTau_vis_m)[itau]/1000. );
    SuperTau stau;
    stau.Set_hlv("truevis", ptau);
    stau.Set_index(itau);
    stau.Set_charge( (int)((*tau_charge)[itau]) );
    stau.Set_nProng( (*trueTau_nProng)[itau] );
    stau.Set_nPi0( (*trueTau_nPi0)[itau] );

    //bool kLepDec = MC_TauLeptonicDecay((*trueTau_vis_eta)[itau], (*trueTau_vis_phi)[itau]); // not needed for visible true taus
    m_TauList_TrueVisTau.push_back(stau);
  }

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
bool TauMain::GetMatchedMCtauIndex(const TLorentzVector &v, int &Index, double &Dr){

  int index(-1);
  double dR(1e3);
  bool matched(false);
  for (int truthindex=0; truthindex<mc_n; truthindex++){
    int n_children=mc_child_index->at(truthindex).size();
    if( abs(mc_pdgId->at(truthindex)) == 15 && n_children > 1 )  { //skip taus with no/1 child only
      int lastTauIndex = LastTauIndex(truthindex);
      int nPi0; int nPiC;
      bool mode = CountVisDecayProducts(lastTauIndex, nPi0, nPiC);
      if (mode){//avoids leptonic decays!
        double tmpDR = DeltaR(v, (*mc_eta)[lastTauIndex],(*mc_phi)[lastTauIndex] );
        if( tmpDR < dR){
          dR = tmpDR;
          index = lastTauIndex;
          matched = true;
        }//min distance
      }//hadronic decays
    }//tau decays
  }//loop over true

  Index = index;
  Dr = dR;

  return matched;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::CreateTrueVisTauListManual(){
  //ref:  https://twiki.cern.ch/twiki/pub/AtlasProtected/TauRecommendationsSummerConf2012/calcTauVisibleSum.py.txt
  //manual way to detect tau's visible products

  for (int truthindex=0; truthindex<mc_n; truthindex++){

    int n_children=mc_child_index->at(truthindex).size();

    if( abs(mc_pdgId->at(truthindex)) == 15 && n_children > 1 )  { //skip taus with no/1 child only
      int lastTauIndex = LastTauIndex(truthindex);
      int nPi0; int nPiC; // number of neutral and charged tracks
      bool mode = CountVisDecayProducts(lastTauIndex, nPi0, nPiC);
      if (mode){//avoids leptonic decays!
        //-
        TLorentzVector visVector;
        if(GetOptBuildVisTauTrueMethod() == "subtraction")
          visVector = MakeVisVectorBySubtraction(lastTauIndex);
        else if(GetOptBuildVisTauTrueMethod() == "addition")
          visVector = MakeVisVectorByAddition(lastTauIndex);

        SuperTau stau;
        stau.Set_hlv("truevis", visVector);
        stau.Set_mc_index( lastTauIndex );
        stau.Set_charge( nPiC );
        stau.Set_nProng( nPiC );
        stau.Set_nPi0( nPi0 );

        m_TauList_TrueVisTau.push_back(stau);

      }//leptonveto
    }//if taus with kids
  }//loop over truth particles

  //PRINTOUT compare "auto" to "manual" vis true tau
  //cout<<endl;
  /*for(SuperTauVecItr i = m_TauList_TrueVisTau.begin(); i != m_TauList_TrueVisTau.end(); i++ ){

    for(int itau = 0; itau < trueTau_n; itau++ ){//true taus in tree

    TLorentzVector ptau;
    ptau.SetPtEtaPhiM( (*trueTau_vis_Et)[itau]/1000., (*trueTau_vis_eta)[itau], (*trueTau_vis_phi)[itau], (*trueTau_vis_m)[itau]/1000. );

    double DR = DeltaR( i->hlv("truevis"), ptau ); //-
    double dpt = i->GetKin("truevis","pt") - ptau.Pt();
    double pTdiff = (i->GetKin("truevis","pt") -  ptau.Pt())/ ptau.Pt(); //-

    if( DR > 0.2 ) continue; // matched vis true tau's

    if( fabs(pTdiff) > 0.05 && ptau.Pt() > 10. ){
    cout<<"tree vis pt="<<ptau.Pt()<<endl;
    cout<<"manu vis pt="<<i->GetKin("truevis","pt")<<" nP="<<i->GetInfo("nProng")<<" nN="<<i->GetInfo("nPi0")<<endl;
    cout<<"RelDpt(manu-tree)="<<pTdiff<<" dR="<<DR<<" dProng="<<i->GetInfo("nProng") - (*trueTau_nProng)[itau] <<" dNeutral="<<i->GetInfo("nPi0") - (*trueTau_nPi0)[itau] <<endl;
    PrintDecay( (int)i->GetInfo("mcindex") );
    cout<<"-----"<<endl;
    }

    m_HM.FillHisto( "test_dPtOverPt_visTrueTau_auto_manual", pTdiff);
    m_HM.FillHisto( "test_dPtOverPt_visTrueTau_auto_manual_vs_visTrueReco_dR", pTdiff, DR); //-
    }//loop on true taus in tree

    }//loop over stored vis true tau
  */


}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
int TauMain::LastTauIndex(int truthindex){

  int n_children=mc_child_index->at(truthindex).size();
  if( abs(mc_pdgId->at(truthindex)) == 15 && n_children > 1 ){
    for (int childindex = 0; childindex < n_children; childindex++){
      int idx = (*mc_child_index)[truthindex][childindex];
      int pdgid = std::fabs( (*mc_pdgId)[idx] );
      if(pdgid==15){
        int nextTau = LastTauIndex(idx);
        return nextTau;
      }
    }//child loop
  }//if
  return truthindex;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::PrintDecay(int Index){

  cout<<(*mc_pdgId)[Index]<<" -> ";

  int n_children=mc_child_index->at(Index).size();
  for (int childindex = 0; childindex < n_children; childindex++){
    int idx = (*mc_child_index)[Index][childindex];
    int pdgid = (*mc_pdgId)[idx];
    int status=(*mc_status)[idx];
    int barcode=(*mc_barcode)[idx];
    int vxbarcode=(*mc_vx_barcode)[idx];
    bool goodDaughter = IsGoodDaughter(status, barcode, vxbarcode);
    cout<<"\t"<<pdgid<<" mc pt,eta,phi="<<(*mc_pt)[idx]/1000.<<","<<(*mc_eta)[idx]<<","<<(*mc_phi)[idx]
        <<" st="<<status<<" gD="<<goodDaughter
        <<" dR="<<DeltaR((*mc_eta)[Index], (*mc_phi)[Index], (*mc_eta)[idx],(*mc_phi)[idx])
        <<endl;

  }//children
  cout<<endl;

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
TLorentzVector TauMain::MakeVisVectorByAddition(int lastTauIndex){

  TLorentzVector visVector;

  //cout<<""<<(*mc_pdgId)[lastTauIndex]<<": ";

  int n_children=mc_child_index->at(lastTauIndex).size();
  for (int childindex = 0; childindex < n_children; childindex++){
    int idx = (*mc_child_index)[lastTauIndex][childindex];
    int pdgid = std::fabs( (*mc_pdgId)[idx] );
    int status=(*mc_status)[idx];
    int barcode=(*mc_barcode)[idx];
    int vxbarcode=(*mc_vx_barcode)[idx];
    bool goodDaughter = IsGoodDaughter(status, barcode, vxbarcode);
    //cout<<pdgid<<"("<<goodDaughter<<", "<<status<<") ";
    if (goodDaughter){
      if (pdgid!=12 && pdgid!=14 && pdgid!=16){ //no neutrinos
        TLorentzVector p;//component
        p.SetPtEtaPhiM((*mc_pt)[idx]/1000.,(*mc_eta)[idx],(*mc_phi)[idx],(*mc_m)[idx]/1000.);
        visVector+=p;
      }
    }//good daughter
  }//children
  //cout<<"("<<n_children<<" childr)\n";

  return visVector;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
TLorentzVector TauMain::MakeVisVectorBySubtraction(int lastTauIndex){

  TLorentzVector invVector;
  TLorentzVector mamVector;
  mamVector.SetPtEtaPhiM((*mc_pt)[lastTauIndex]/1000.,(*mc_eta)[lastTauIndex],(*mc_phi)[lastTauIndex],(*mc_m)[lastTauIndex]/1000.);

  //cout<<"\n"<<(*mc_pdgId)[lastTauIndex]<<": ";

  int n_children=mc_child_index->at(lastTauIndex).size();
  for (int childindex = 0; childindex < n_children; childindex++){
    int idx = (*mc_child_index)[lastTauIndex][childindex];
    int pdgid = std::fabs( (*mc_pdgId)[idx] );
    int status=(*mc_status)[idx];
    int barcode=(*mc_barcode)[idx];
    int vxbarcode=(*mc_vx_barcode)[idx];
    bool goodDaughter = IsGoodDaughter(status, barcode, vxbarcode);
    if (goodDaughter){
      if( pdgid ==16){ // tau neutrinos!
        //cout<<pdgid<<"("<<goodDaughter<<", "<<status<<") ";
        TLorentzVector p;//component
        p.SetPtEtaPhiM((*mc_pt)[idx]/1000.,(*mc_eta)[idx],(*mc_phi)[idx],(*mc_m)[idx]/1000.);
        invVector+=p;
      }
    }//good daughter
  }//children

  TLorentzVector visVector = mamVector - invVector;

  //cout<<"pT mam "<<mamVector.Pt() <<"  pT inv "<<invVector.Pt()<<" pT vis "<<visVector.Pt()<<endl;

  return visVector;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
bool TauMain::IsGoodDaughter(int status, int barcode, int vxbarcode){
  // accept all stat==2 daughters
  if(status==2) return true;
  //for AlpgenJimmy (accept daughters with 190 < stat < 200 )
  if( ( status < 200 ) && ( status > 190 )) return true;
  // accept daughters with status code 1,1001,2001,... and 1002,2002,... etc if barcode is not too high
  if( (( status%1000 == 1) || (status%1000 == 2 && status > 1000) || (status==2 && vxbarcode < -200000)) && (barcode < 200000) ) return true ;

  return false ;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
bool TauMain::CountVisDecayProducts(int truthindex, int &nNeutral, int &nCharged){

  int n_children=mc_child_index->at(truthindex).size();
  int npi0=0;
  int npi=0;
  int ninv=0;
  int nph=0;
  if( abs(mc_pdgId->at(truthindex))==15 && n_children>1)  {
    for (int childindex=0; childindex<n_children; childindex++){
      int idx = (*mc_child_index)[truthindex][childindex];
      int pdgid = std::fabs( (*mc_pdgId)[idx] );
      int status=(*mc_status)[idx];
      int barcode=(*mc_barcode)[idx];
      int vxbarcode=(*mc_vx_barcode)[idx];
      bool goodDaughter = IsGoodDaughter(status, barcode, vxbarcode);
      if(!goodDaughter) continue;

      if(pdgid == 15 || pdgid == 13 || pdgid == 11) return false;//lepton
      else if (pdgid==111 || pdgid== 311 || pdgid==221 || pdgid==223 || pdgid==130 || pdgid==310 || pdgid==313) npi0++;//number of neutral mesons
      else if (pdgid==211 || pdgid==321 || pdgid==323) npi++;//number of charged mesons
      else if (pdgid==12 || pdgid==14 || pdgid==16) ninv++;//number of neutrinos
      else if (pdgid==22) nph++;//number of photons
      else{cout<<"TauMain::CountVisDecayProducts - decay particle "<<pdgid<<" escaped !"<<endl; }

    }//child loop
  }//if

  if(!ninv) { cerr<<"TauMain::CountVisDecayProducts - no neutrino found "<<endl; return false; }

  nNeutral = npi0;
  nCharged = npi;

  return true;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::TruthKaonDecay(const int truthindex, bool &kChargedKaon, bool &kNeutralKaon){

  int j = truthindex;

  if( j > (int)mc_pt->size() && j >0 ){ cout<<"TruthKaonDecay: index "<<j<<" cannot be larger than "<<mc_pt->size()<<endl; return;}

  //now find parent of particle
  int parentPdg(0); //pdg
  int parentIdx(0); //index
  for(unsigned int m=0; m < mc_parent_index->at(j).size(); m++) {
    parentIdx = mc_parent_index->at(j).at(m);
    parentPdg = parentIdx <  (int)mc_pt->size() ? mc_pdgId->at( parentIdx ) : 0;
    if( fabs(parentPdg) == 15) break; //once found, stop looking for parents
  }

  if(!parentIdx){ cout<<"TruthKaonDecay - no parent index"<<endl; return;}

  //loop over paretn decays
  int n_children=mc_child_index->at(parentIdx).size();
  bool kCKaon(false);
  bool kNKaon(false);

  if( abs(mc_pdgId->at(parentIdx)) == 15 && n_children > 1)  {
    for (int childindex = 0; childindex < n_children; childindex++){
      int idx = (*mc_child_index)[parentIdx][childindex];
      int pdgid = std::fabs( (*mc_pdgId)[idx] );
      int status=(*mc_status)[idx];
      int barcode=(*mc_barcode)[idx];
      int vxbarcode=(*mc_vx_barcode)[idx];
      bool goodDaughter = IsGoodDaughter(status, barcode, vxbarcode);
      if(!goodDaughter) continue;

      if(!kCKaon) kCKaon = KaonIsCharged( pdgid );
      if(!kNKaon) kNKaon = KaonIsNeutral( pdgid );

      /*if(//charged
        pdgid == 321 || // Kaon +-
        pdgid == 323 || // Kaon* +-
        pdgid == 325 || // Kaon2* +-
        pdgid == 327 || // Kaon3* +-
        pdgid == 329 || // Kaon4* +-
        //neutrals
        pdgid == 130 || //kaon 0 long
        pdgid == 310 || //kaon 0 short
        pdgid == 311 || //kaon 0
        pdgid == 313 || // Kaon* 0
        pdgid == 315 || // Kaon2* 0
        pdgid == 317 || // Kaon3* 0
        pdgid == 319    // Kaon4* 0
        )
        {
        //    cout<<"TruthKaonDecay - Kaon found "<<(*mc_pdgId)[idx]<<endl;
        return true;//kaon found - ciao ciao
        }*/

    }//child loop
  }//if

  kChargedKaon = kCKaon;
  kNeutralKaon = kNKaon;

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
bool TauMain::KaonIsCharged(const int i){

  return ( find( m_charged_kaons_pdgid.begin(), m_charged_kaons_pdgid.end(), i) != m_charged_kaons_pdgid.end() );
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
bool TauMain::KaonIsNeutral(const int i){

  return ( find( m_neutral_kaons_pdgid.begin(), m_neutral_kaons_pdgid.end(), i) != m_neutral_kaons_pdgid.end() );
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::CreateRecoTauList(){

  CleanListOfRecoTaus();

  for(int itau = 0; itau < tau_n; itau++ ){

    TLorentzVector ptau;
    ptau.SetPtEtaPhiM( (*tau_pt)[itau]/1000., (*tau_eta)[itau], (*tau_phi)[itau], (*tau_m)[itau]/1000. );

    SuperTau stau;
    stau.Set_hlv(ptau);
    stau.Set_index(itau);
    stau.Set_author( (*tau_author)[itau] );
    stau.Set_charge( (int)((*tau_charge)[itau]) );
    stau.Set_numTrack( (*tau_numTrack)[itau] );
    stau.Set_JetBDTSig( (*tau_JetBDTSigLoose)[itau], (*tau_JetBDTSigMedium)[itau], (*tau_JetBDTSigTight)[itau]);
    stau.Set_JetBDTSigScore( (*tau_BDTJetScore)[itau] );

    m_TauList_RecoTau.push_back(stau);
  }

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
int TauMain::GetDecayModeTrue(int ntrk, int npi0){

  //     Tau -> 1 Charged Pion,  0 Neutral Pions (1p0n) = 0
  //     Tau -> 1 Charged Pion,  1 Neutral Pion  (1p1n) = 1
  //     Tau -> 1 Charged Pion, >1 Neutral Pion  (1pXn) = 2

  //     Tau -> 3 Charged Pion,  0 Neutral Pions (3p0n) = 3
  //     Tau -> 3 Charged Pion, >0 Neutral Pions (3pXn) = 4

  if( ntrk == 1){
    if(npi0 == 0) return 0;
    else if (npi0 == 1) return 1;
    else return 2;
  }else if( ntrk ==3){
    if(npi0 == 0) return 3;
    else return 4;
  }else{
    //this case is not classified
  }

  return 5;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
string TauMain::GetDecayModeStr(int type){

  if(type == 0 ) return "1p0n";
  else if(type == 1 ) return "1p1n";
  else if(type == 2 ) return "1pXn";
  else if(type == 3 ) return "3p0n";
  else if(type == 4 ) return "3pXn";
  else if(type == 5 ) return "other";
  else { cerr<<"TauMain::GetDecayModeStr - unknown decay mode "<<type<<endl;}

  return "unclassified";
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
string TauMain::GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
string TauMain::GetStringFromDouble(double x){

  char aa[50];
  sprintf(aa,"%.2f", x);

  //std::ostringstream stm; stm << n;
  //string s = stm.str();

  string s(aa);

  TString S(s);
  S.ReplaceAll(".", "p");

  return S.Data();
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
string TauMain::GetNprongStr(int n){

  return GetStringFromInt(n)+"p";

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
string TauMain::GetNneutralStr(int n){

  if(n == 0 || n == 1) return GetStringFromInt(n)+"n";

  return "Xn";
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
bool TauMain::MC_TauLeptonicDecay(double eta, double phi){

  for(int i = 0; i < mc_n; i++){

    if(fabs( mc_pdgId->at(i)) != 15) continue; //consider only decaying taus in the particle history
    if(mc_child_index->at(i).size()<2) continue; //skip taus with no/1 child only

    //detect taus which have a tau as child or leptonic taus
    for (int j = 0; j < (int)mc_child_index->at(i).size(); j++ ){
      int idx = (*mc_child_index)[i][j];
      int pdgid = std::fabs( (*mc_pdgId)[idx] );
      if( pdgid ==15 || pdgid == 13 || pdgid == 11){
        double child_eta = (*mc_eta)[idx];
        double child_phi = (*mc_phi)[idx];
        double dR = DeltaR(eta, phi, child_eta, child_phi);
        //cout<<pdgid<<"  dr "<<dR<<endl;
        if(  dR < 0.2 ) // matches
          return true;
      }
    }//loop over children

  }//loop over mc

  return false;

}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
int TauMain::GetNvtx() const {

  return vxp_n;
}
///_-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-__-'`'-_
void TauMain::LoadBranches(int j){

  ///event variables
  b_RunNumber->GetEntry(j);
  b_EventNumber->GetEntry(j);
  b_lbn->GetEntry(j);
  b_mc_channel_number->GetEntry(j);
  b_mcevt_weight->GetEntry(j);

  //vertex
  b_vxp_n->GetEntry(j);

  //mc stuff
  b_mc_n->GetEntry(j);
  b_mc_pdgId->GetEntry(j);
  b_mc_child_index->GetEntry(j);
  b_mc_eta->GetEntry(j);
  b_mc_phi->GetEntry(j);
  b_mc_pt->GetEntry(j);
  b_mc_m->GetEntry(j);
  b_mc_charge->GetEntry(j);
  b_mc_barcode->GetEntry(j);
  b_mc_parent_index->GetEntry(j);
  b_mc_status->GetEntry(j);
  b_mc_vx_barcode->GetEntry(j);

  //tracks
  b_trk_eta->GetEntry(j);
  b_trk_phi->GetEntry(j);
  b_trk_pt->GetEntry(j);
  b_trk_mc_barcode->GetEntry(j);
  b_trk_mc_probability->GetEntry(j);
  b_trk_nSCTHits->GetEntry(j);
  b_trk_nPixHits->GetEntry(j);
  b_trk_z0_wrtPV->GetEntry(j);
  b_trk_d0_wrtPV->GetEntry(j);
  b_trk_theta ->GetEntry(j);
  b_trk_qoverp->GetEntry(j);
  b_trk_err_qoverp_wrtBS->GetEntry(j);
  b_trk_theta_err_wrtBL->GetEntry(j);

  //tau tracks
  b_tau_track_n->GetEntry(j);
  //  b_tau_track_d0->GetEntry(j);
  //  b_tau_track_z0->GetEntry(j);
  //  b_tau_track_theta->GetEntry(j);
  //  b_tau_track_qoverp->GetEntry(j);
  b_tau_track_pt->GetEntry(j);
  b_tau_track_eta->GetEntry(j);
  b_tau_track_phi->GetEntry(j);
  b_tau_track_qoverp->GetEntry(j);

  //tau track at TJVA
  b_tau_track_atTJVA_pt->GetEntry(j);
  b_tau_track_atTJVA_eta->GetEntry(j);
  b_tau_track_atTJVA_phi->GetEntry(j);
  b_tau_track_atTJVA_qoverp->GetEntry(j);


  ///regular reco taus
  b_trueTau_vis_phi->GetEntry(j);
  b_tau_pt->GetEntry(j);
  b_tau_eta->GetEntry(j);
  b_tau_phi->GetEntry(j);
  b_tau_m->GetEntry(j);
  b_tau_n->GetEntry(j);
  b_tau_author->GetEntry(j);
  b_tau_charge->GetEntry(j);
  b_tau_numTrack->GetEntry(j);
  b_tau_JetBDTSigLoose->GetEntry(j);
  b_tau_JetBDTSigMedium->GetEntry(j);
  b_tau_JetBDTSigTight->GetEntry(j);
  b_tau_BDTJetScore->GetEntry(j);

  b_tau_trueTauAssoc_dr->GetEntry(j);
  b_tau_trueTauAssoc_index->GetEntry(j);
  b_tau_trueTauAssoc_matched->GetEntry(j);

  b_trueTau_tauAssoc_index->GetEntry(j);

  ///true taus
  b_trueTau_n->GetEntry(j);
  b_trueTau_pt->GetEntry(j);
  b_trueTau_m->GetEntry(j);
  b_trueTau_eta->GetEntry(j);
  b_trueTau_phi->GetEntry(j);
  b_trueTau_vis_m->GetEntry(j);
  b_trueTau_vis_Et->GetEntry(j);
  b_trueTau_vis_eta->GetEntry(j);
  b_trueTau_vis_phi->GetEntry(j);
  b_trueTau_nProng->GetEntry(j);
  b_trueTau_nPi0->GetEntry(j);
  b_trueTau_charge->GetEntry(j);

  ///tau_pantau_CellBased_
  b_tau_pantau_CellBased_isPanTauCandidate->GetEntry(j);
  b_tau_pantau_CellBased_RecoModeCellBased->GetEntry(j);
  b_tau_pantau_CellBased_RecoModePanTau->GetEntry(j);
  b_tau_pantau_CellBased_BDTValue_1p0n_vs_1p1n->GetEntry(j);
  b_tau_pantau_CellBased_BDTValue_1p1n_vs_1pXn->GetEntry(j);
  b_tau_pantau_CellBased_BDTValue_3p0n_vs_3pXn->GetEntry(j);
  b_tau_pantau_CellBased_proto_pt->GetEntry(j);
  b_tau_pantau_CellBased_proto_eta->GetEntry(j);
  b_tau_pantau_CellBased_proto_phi->GetEntry(j);
  b_tau_pantau_CellBased_proto_m->GetEntry(j);
  b_tau_pantau_CellBased_final_pt->GetEntry(j);
  b_tau_pantau_CellBased_final_eta->GetEntry(j);
  b_tau_pantau_CellBased_final_phi->GetEntry(j);
  b_tau_pantau_CellBased_final_m->GetEntry(j);
  b_tau_pantau_CellBased_ChargedEFOs_pt->GetEntry(j);
  b_tau_pantau_CellBased_ChargedEFOs_eta->GetEntry(j);
  b_tau_pantau_CellBased_ChargedEFOs_phi->GetEntry(j);
  b_tau_pantau_CellBased_ChargedEFOs_m->GetEntry(j);
  b_tau_pantau_CellBased_NeutralEFOs_pt->GetEntry(j);
  b_tau_pantau_CellBased_NeutralEFOs_eta->GetEntry(j);
  b_tau_pantau_CellBased_NeutralEFOs_phi->GetEntry(j);
  b_tau_pantau_CellBased_NeutralEFOs_m->GetEntry(j);
  b_tau_pantau_CellBased_Pi0NeutEFOs_pt->GetEntry(j);
  b_tau_pantau_CellBased_Pi0NeutEFOs_eta->GetEntry(j);
  b_tau_pantau_CellBased_Pi0NeutEFOs_phi->GetEntry(j);
  b_tau_pantau_CellBased_Pi0NeutEFOs_m->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Basic_NNeutralConsts->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Charged_JetMoment_EtDRxTotalEt->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Charged_StdDev_Et_WrtEtAllConsts->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Neutral_HLV_SumM->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Neutral_PID_BDTValues_BDTSort_1->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Neutral_PID_BDTValues_BDTSort_2->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Neutral_Ratio_1stBDTEtOverEtAllConsts->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Neutral_Ratio_EtOverEtAllConsts->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Neutral_Shots_NPhotonsInSeed->GetEntry(j);
  b_tau_pantau_CellBased_IDVars_Combined_DeltaR1stNeutralTo1stCharged->GetEntry(j);


}


string TauMain::GetPtRangeStr(double x){

  for(int i = 0;  i < (int)m_vec_pt_bins.size()-1;  i++){
    if( x < m_vec_pt_bins.at(i+1) ) return GetStringFromInt(m_vec_pt_bins.at(i)) + "_" + GetStringFromInt(m_vec_pt_bins.at(i+1));
  }
  cerr<<"TauMain::GetPtRangeStr - "<<x<<" not in range..."<<endl;
  return "other";
}

string TauMain::GetEtaRangeStr(double x){

  for(int i = 0;  i < (int)m_vec_eta_bins.size()-1;  i++){
    if( x < m_vec_eta_bins.at(i+1) ) return GetStringFromDouble(m_vec_eta_bins.at(i)) + "_" + GetStringFromDouble(m_vec_eta_bins.at(i+1));
  }

  cerr<<"TauMain::GetEtaRangeStr - "<<x<<" not in range..."<<endl;
  return "other";
}

string TauMain::GetBDTRangeStr(double x){

  for(int i = 0;  i < (int)m_vec_bdt_bins.size()-1;  i++){
    if( x < m_vec_bdt_bins.at(i+1) ) return GetStringFromDouble(m_vec_bdt_bins.at(i)) + "_" + GetStringFromDouble(m_vec_bdt_bins.at(i+1));
  }

  cerr<<"TauMain::GetBDTRangeStr - "<<x<<" not in range..."<<endl;
  return "other";
}

string TauMain::HpTrange(unsigned int i){
  if(i < m_vec_pt_bins.size() ) return GetStringFromInt( m_vec_pt_bins.at(i) ) + "_" + GetStringFromInt( m_vec_pt_bins.at(i+1) );
  else cerr<<"TauMain::HpTrange - bin index "<<i<<" can't be greater than vector's size "<<m_vec_pt_bins.size()<<endl;

  return "";
}

string TauMain::Hetarange(unsigned int i){
  if(i < m_vec_eta_bins.size() ) return GetStringFromDouble( m_vec_eta_bins.at(i) ) + "_" + GetStringFromDouble( m_vec_eta_bins.at(i+1) );
  else cerr<<"TauMain::Hetsrange - bin index "<<i<<" can't be greater than vector's size "<<m_vec_eta_bins.size()<<endl;

  return "";
}

string TauMain::HBDTrange(unsigned int i){
  if(i < m_vec_bdt_bins.size() ) return GetStringFromDouble( m_vec_bdt_bins.at(i) ) + "_" + GetStringFromDouble( m_vec_bdt_bins.at(i+1) );
  else cerr<<"TauMain::HBDTrange - bin index "<<i<<" can't be greater than vector's size "<<m_vec_bdt_bins.size()<<endl;

  return "";
}

double TauMain::SigmaOverP(double _p, double _eta, double _N){

  //ref: https://cds.cern.ch/record/1544036/files/ATLAS-CONF-2013-044.pdf
  //Table 1 page 5

  double eta = std::fabs(_eta);
  double a(0); double b(0);

  if(_N==1){

    if( eta < 0.3) {a = 0.71; b = 0.02; }
    else if( eta < 0.8) {a = 0.73; b = 0.02; }
    else if( eta < 1.3) {a = 0.87; b = 0.04; }
    else if( eta < 1.6) {a = 1.09; b = 0.07; }
    else {a = 1.10; b = 0.01; }

  } else if(_N>1){

    if( eta < 0.3) {a = 0.85; b = 0.01; }
    else if( eta < 0.8) {a = 0.79; b = 0.03; }
    else if( eta < 1.3) {a = 1.02; b = 0.04; }
    else if( eta < 1.6) {a = 1.24; b = 0.06; }
    else {a = 1.27; b = 0.01; }

  } else{

    cerr<<"TauMain::SigmaOverP - unable to calculate resolution for p "<<_p<<", eta "<<_eta<<" and Ntrk "<<_N<<endl;

  }

  return std::sqrt( a*a/_p + b*b);

}
