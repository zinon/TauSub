#ifndef _TAUMAIN_
#define _TAUMAIN_

#include "HistoManager.h"
#include "SuperTau.h"
#include "SmartTrack.h"
#include "TauSubstructureViewer.h"
#include "TauObject_PanTau.h"
#include "TruthTrackMatchingTool.h"

#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TMath.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <map>

#define PI 3.14159265

using namespace std;

class HyperTau {

 public:

 HyperTau() : m_IsTrue(false) { m_stracks.clear(); };
 HyperTau( TauObject_PanTau &x, SuperTau &y, bool k) : 
  m_IsTrue(false), m_kaon_decay(false), m_charged_kaon_decay(false), m_neutral_kaon_decay(false), m_MatchedTruthDR(-1) { Set(x, y, k);  m_stracks.clear(); };

 HyperTau( TauObject_PanTau &x, SuperTau &y, bool k, SuperTau &z) : 
  m_IsTrue(false), m_kaon_decay(false), m_charged_kaon_decay(false), m_neutral_kaon_decay(false), m_MatchedTruthDR(-1) { Set(x, y, k, z);  m_stracks.clear(); };

 HyperTau( TauObject_PanTau &x, SuperTau &y, bool k, double r, SuperTau &z) : 
  m_IsTrue(false), m_kaon_decay(false), m_charged_kaon_decay(false), m_neutral_kaon_decay(false),  m_MatchedTruthDR(-1) { Set(x, y, k, r, z);  m_stracks.clear(); };

 HyperTau( TauObject_PanTau &x, SuperTau &y, bool k, double r, SuperTau &z, TLorentzVector p1, TLorentzVector p2) : 
  m_IsTrue(false), m_kaon_decay(false), m_charged_kaon_decay(false), m_neutral_kaon_decay(false),  m_MatchedTruthDR(-1) { Set(x, y, k, r, z, p1, p2);  m_stracks.clear(); };
  
  ~HyperTau(){};


  void Set(TauObject_PanTau &x, SuperTau &y, bool k){
    m_PanTau = x;
    m_TrueVisTau = y;
    m_IsTrue = k;
  }
  void Set(TauObject_PanTau &x, SuperTau &y, bool k, SuperTau &z){
    m_PanTau = x;
    m_TrueVisTau = y;
    m_IsTrue = k;
    m_RecoTau = z;
  }
  void Set(TauObject_PanTau &x, SuperTau &y, bool k, double minDR, SuperTau &z){
    m_PanTau = x;
    m_TrueVisTau = y;
    m_IsTrue = k;
    m_MatchedTruthDR = minDR;
    m_RecoTau = z;
  }
  void Set(TauObject_PanTau &x, SuperTau &y, bool k, double minDR, SuperTau &z, TLorentzVector p1, TLorentzVector p2){
    m_PanTau = x;
    m_TrueVisTau = y;
    m_IsTrue = k;
    m_MatchedTruthDR = minDR;
    m_RecoTau = z;
    m_p1 = p1;
    m_p2 = p2;
  }

  void SetTruthKaonDecay(bool b){ m_kaon_decay = b;}
  void SetTruthChargedKaonDecay(bool b){ m_charged_kaon_decay = b;}
  void SetTruthNeutralKaonDecay(bool b){ m_neutral_kaon_decay = b;}

  void LinkReco(SuperTau &r){
    m_RecoTau = r;
  }

  void AddSmartTrack(const SmartTrack &t){ m_stracks.push_back(t); }
  vector<SmartTrack> GetSmartTracks() const { return m_stracks; }
  SmartTrack &GetFirstSmartTrack()  { 
    if(!m_stracks.size()) {
      cerr<<"HyperTau: Empty tracks vector "<<endl;// return NULL;
    } 
    return m_stracks[0]; 
  }

  int GetNumSmartTracks() const { return m_stracks.size(); }
  TauObject_PanTau GetPanTau(){ return m_PanTau;}
  SuperTau GetTrueVis(){ return m_TrueVisTau;}
  bool IsTrue(){ return m_IsTrue; }
  double GetMatchedTruthDR(){ return m_MatchedTruthDR; }
  SuperTau GetRecoTau(){ return m_RecoTau;}
  TLorentzVector GetP1(){ return m_p1;}
  TLorentzVector GetP2(){ return m_p2;}
  TLorentzVector GetPanHLV(){return m_PanTau.getMomentum();}
  TLorentzVector GetTrueVisHLV(){ return m_IsTrue ? m_TrueVisTau.hlv("truevis") : TLorentzVector(0,0,0,0); }
  TLorentzVector GetRecoHLV(){return m_RecoTau.hlv();}
  bool GetTruthKaonDecay(){ return m_kaon_decay;}
  bool GetTruthChargedKaonDecay(){ return m_charged_kaon_decay;}
  bool GetTruthNeutralKaonDecay(){ return m_neutral_kaon_decay;}

 private:
  TauObject_PanTau m_PanTau;
  SuperTau m_TrueVisTau;
  bool m_IsTrue;
  bool m_kaon_decay;
  bool m_charged_kaon_decay;
  bool m_neutral_kaon_decay;
  double m_MatchedTruthDR;
  vector<SmartTrack> m_stracks;
  SuperTau m_RecoTau;
  TLorentzVector m_p1;
  TLorentzVector m_p2;
};

class TauMain : public TauSubstructureViewer {

 public:
  TauMain(TTree *);
  ~TauMain();

 public:
  void Looper();
  void Analyze();
  void BookHistos();
  void BookTemplate(const std::string &);
  void LoadBranches(int);
  void LoadSetup();

  //set jobs options
  void SetOutFileName(string &s){m_OutFileName = s;}
  void SetOptStudyTauRec(bool k){m_do_taurec = k;}
  void SetOptMaxNtrks(int i){ m_opt_max_ntrks = i;}
  void SetOptMaxRecoTauAbsEta(double x){ m_opt_max_reco_tau_abs_eta = x;}
  void SetOptMinRecoTauPt(double x){ m_opt_min_reco_tau_pt = x;}
  void SetOptMatchToVisTrueTau(){ m_opt_match_to_vis_true_tau = true;}
  void SetOptMinTrueVisTauPt(double x) { m_opt_min_true_vis_tau_pt = x; }
  void SetOptRecoTauPtRange(double x, double y){ m_opt_reco_tau_pt_l = x; m_opt_reco_tau_pt_r = y; }
  void SetOptRecoTauAbsEtaRange(double x, double y){ m_opt_reco_tau_eta_l = x; m_opt_reco_tau_eta_r = y; }
  void SetOptPanTauTrkRecoTrkMatchMaxDR(double x){ m_opt_pan_tau_trk_reco_trk_match_max_dR = x;}
  void SetOptPanTauTrkRecoTrkMatchMaxRelFracPt(double x){ m_opt_pan_tau_trk_reco_trk_match_max_rel_frac_pT = x; }
  void SetOptPanTauTrkRecoTrkMatchClosestDR(bool b){ m_opt_pan_tau_trk_reco_trk_match_closest_dR = b; }
  void SetOptRecoTauVisTrueTauMatchMaxDR(double x){ m_opt_reco_tau_vis_true_max_dR = x; }
  void SetOptRecoTauPanTauMaxDR(double x){ m_opt_reco_tau_pan_tau_max_dR = x;}
  void SetOptTauParentPDGID(int i){ m_opt_tau_parent_pdg_id = i; }
  void SetOptBuildVisTauTrue(const string & s){ m_opt_build_vis_true_tau = s; }
  void SetOptBuildVisTauTrueMethod(const string & s){ m_opt_build_vis_true_tau_method = s; } //-
  void SetOptTauJetBDTSig(const string &s){ m_opt_JetBDTSig = s; }
  void SetOptVisTrueTauMatchUseAssocIndex(bool b){ m_opt_vis_true_tau_match_use_Assoc_index = b;}
  void SetOptUseOfficialTruthMatching( bool b){ m_opt_UseOfficialTruthMatching = b; }
  void SetOptWeightHistos(bool b){ m_opt_WeightHistos = b; }
  void SetOptCompatibilityRatioCut(const string &s){ m_opt_compatibility_ratio_cut = s; }

 protected:

  //get job options
  bool GetOptStudyTauRec() const { return m_do_taurec;}
  double GetOptMaxRecoTauAbsEta() const { return m_opt_max_reco_tau_abs_eta;}
  double GetOptMinRecoTauPt() const { return m_opt_min_reco_tau_pt; }
  int GetOptMaxNtrks() const { return m_opt_max_ntrks;}
  bool GetOptMatchToVisTrueTau() const { return m_opt_match_to_vis_true_tau; }
  double GetOptMinTrueVisTauPt() const { return m_opt_min_true_vis_tau_pt; }
  double GetOptRecoTauAbsEtaL() const{ return m_opt_reco_tau_eta_l;}
  double GetOptRecoTauAbsEtaR() const{ return m_opt_reco_tau_eta_r;}
  double GetOptRecoTauPtL() const{ return m_opt_reco_tau_pt_l;}
  double GetOptRecoTauPtR() const{ return m_opt_reco_tau_pt_r;}
  double GetOptPanTauTrkRecoTrkMatchMaxDR() const { return m_opt_pan_tau_trk_reco_trk_match_max_dR;}
  double GetOptPanTauTrkRecoTrkMatchMaxRelFracPt() const { return m_opt_pan_tau_trk_reco_trk_match_max_rel_frac_pT; }
  bool GetOptPanTauTrkRecoTrkMatchClosestDR() const { return m_opt_pan_tau_trk_reco_trk_match_closest_dR; }
  double GetOptRecoTauVisTrueTauMatchMaxDR() const { return m_opt_reco_tau_vis_true_max_dR; }
  double GetOptRecoTauPanTauMaxDR() const { return m_opt_reco_tau_pan_tau_max_dR;}
  int GetOptTauParentPDGID() const { return m_opt_tau_parent_pdg_id; }
  string GetOptBuildVisTauTrue() const { return m_opt_build_vis_true_tau; }
  string GetOptBuildVisTauTrueMethod() const { return m_opt_build_vis_true_tau_method; } //-
  string GetOptTauJetBDTSig() const { return m_opt_JetBDTSig; }
  bool GetOptVisTrueTauMatchUseAssocIndex() const { return m_opt_vis_true_tau_match_use_Assoc_index;}
  bool GetOptUseOfficialTruthMatching() const { return m_opt_UseOfficialTruthMatching; }
  bool GetOptWeightHistos() const { return m_opt_WeightHistos; }
  string GetOptCompatibilityRatioCut() const { return m_opt_compatibility_ratio_cut; }
  
  //class methods
  void SaveAndClose();
  void WeightHistos();

  void CleanListOfPanTauTaus(){ m_TauList_PanTau.clear(); }
  void CreatePanTauList();

  void CleanListOfRecoTaus(){ m_TauList_RecoTau.clear(); }
  void CreateRecoTauList();

  void CleanListOfTrueTaus(){ m_TauList_TrueTau.clear(); }
  void CreateTrueTauList();

  void CleanListOfTrueVisTaus(){ m_TauList_TrueVisTau.clear(); }
  void CreateTrueVisTauList();

  void CleanListOfHyperTaus(){ m_TauList_HyperTau.clear(); }
  void AssociateRecoToVisTrue();

  void AssociatePanToVisTrue();
  void AssociateHyperTauTracksToTruthTracks();
  void AssociateHyperToReco();

  void CreateHyperTau(); // combines PanTau + VisTrue + RecTau

  int GetDecayModeTrue(int, int);
  string GetDecayModeStr(int);
  string GetNprongStr(int);
  string GetNneutralStr(int);
  bool MC_TauLeptonicDecay(double, double);
  int GetNvtx() const;
  string GetStringFromInt(int);
  string GetStringFromDouble(double);
  string Int2Str(int i){ return GetStringFromInt(i); };
  template <typename T> std::string ToString( const T & t){   ostringstream os; os << t; return os.str();}
  string GetPtRangeStr(double);  
  string HpTrange(unsigned int);
  string Hetarange(unsigned int);
  string GetEtaRangeStr(double x);
  string HBDTrange(unsigned int);
  string GetBDTRangeStr(double x);

  void CreateTrueVisTauListAuto();
  void CreateTrueVisTauListManual();
  int LastTauIndex(int truthindex);
  TLorentzVector MakeVisVectorByAddition(int lastTauIndex);
  TLorentzVector MakeVisVectorBySubtraction(int lastTauIndex);
  bool IsGoodDaughter(int status, int barcode, int vxbarcode);
  bool CountVisDecayProducts(int truthindex, int &nNeutral, int &nCharged);
  void PrintDecay(int Index);
  bool GetMatchedMCtauIndex(const TLorentzVector &, int &index, double &minDr);
  void TruthKaonDecay(const int truthindex, bool &, bool &);
  bool KaonIsCharged(const int i);
  bool KaonIsNeutral(const int i);

  double SigmaOverP(double _p, double _eta, double _N);

 private:

  //job options variables
  bool m_do_taurec;
  int m_opt_max_ntrks;
  double m_opt_max_reco_tau_abs_eta;
  double m_opt_min_reco_tau_pt;
  double m_opt_min_true_vis_tau_pt;
  bool m_opt_match_to_vis_true_tau;
  double m_opt_reco_tau_eta_l;
  double m_opt_reco_tau_eta_r;
  double m_opt_reco_tau_pt_l;
  double m_opt_reco_tau_pt_r;
  double m_opt_pan_tau_trk_reco_trk_match_max_dR;
  double m_opt_pan_tau_trk_reco_trk_match_max_rel_frac_pT;
  double m_opt_pan_tau_trk_reco_trk_match_closest_dR;
  double m_opt_reco_tau_vis_true_max_dR;
  double m_opt_reco_tau_pan_tau_max_dR;
  int m_opt_tau_parent_pdg_id;
  string m_opt_build_vis_true_tau;
  string m_opt_build_vis_true_tau_method;//-
  string m_opt_JetBDTSig;
  bool m_opt_vis_true_tau_match_use_Assoc_index;
  bool m_opt_UseOfficialTruthMatching;
  bool m_opt_WeightHistos;
  string m_opt_compatibility_ratio_cut;

  //other variables
  int m_mc;
  int m_nentries;
  map<int,double> m_xsec;
  map<int,double> m_Nevt;
  TFile *m_File;
  string m_OutFileName;

  HistoManager m_HM;

  TruthTrackMatchingTool m_TruthTrackMatchingTool;

  static const double arrBDT[];
  vector<double> m_vec_bdt_bins;

  static const int arrPt[];
  vector<int> m_vec_pt_bins;

  static const double arrEta[];
  vector<double> m_vec_eta_bins;

  static const int arrKaonCharged[];
  vector<int>  m_charged_kaons_pdgid;
 
  static const int arrKaonNeutral[];
  vector<int>  m_neutral_kaons_pdgid;

  typedef vector<TLorentzVector> TLV;

  typedef vector<TLorentzVector>::iterator TLVItr;

  typedef vector<TauObject_PanTau> PanTauVec;
  typedef vector<TauObject_PanTau>::iterator PanTauVecItr;

  typedef vector<HyperTau> HyperTauVec;
  typedef vector<HyperTau>::iterator HyperTauVecItr;

  typedef vector<SuperTau> SuperTauVec;
  typedef vector<SuperTau>::iterator SuperTauVecItr;

  typedef vector<string> DecayModes;
  typedef vector<string>::iterator DecayModesItr;

  PanTauVec m_TauList_PanTau;
  HyperTauVec m_TauList_HyperTau;
  SuperTauVec m_TauList_RecoTau;
  SuperTauVec m_TauList_TrueTau;
  SuperTauVec m_TauList_TrueVisTau;

  DecayModes m_DecayModes;

  //to put in the ToolBox class
 public:
  double DeltaR(const TLorentzVector &p1, const TLorentzVector &p2){
    return DeltaR( p1.Eta(), p1.Phi(), p2.Eta(), p2.Phi() );
  }
  double DeltaEta(const TLorentzVector &p1, const TLorentzVector &p2){
    return DeltaEta( p1.Eta(), p2.Eta());
  }
  double DeltaPt(const TLorentzVector &p1, const TLorentzVector &p2){
    return p1.Pt() - p2.Pt();
  }
  double DeltaR(const TLorentzVector &p1, double eta, double phi){
    return DeltaR( p1.Eta(), p1.Phi(), eta, phi );
  }
  double DeltaR( double eta, double phi, const TLorentzVector &p1){
    return DeltaR( p1.Eta(), p1.Phi(), eta, phi );
  }
  double DeltaR(double eta1, double phi1, double eta2, double phi2){
    double dPhi = DeltaPhi(phi1, phi2);
    double dEta = DeltaEta(eta1, eta2);
    return std::sqrt( dPhi*dPhi + dEta*dEta );
  }
  double DeltaEta(const double eta1, const double eta2){
    return std::fabs( eta1 - eta2 );
  }

  double DeltaPhi(const double phi1, const double phi2){
    return PI - std::fabs( std::fabs( phi1 - phi2 ) - PI );
  }

  double RelRes(double obs, double ref ){ return (obs-ref)/ref; }
  double Log10Res(double obs, double ref){ return TMath::Log10(obs/ref); }
  double DetEneRes(double obs, double ref ){ return (obs-ref)/sqrt(ref); }
  double DetPtRes(double obs, double ref ){ return (obs-ref)/pow(ref,2); }
  double StdRes(double obs, double ref ){ return obs/ref; }

};

#endif

