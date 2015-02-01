#ifndef _SMARTTRACK_
#define _SMARTTRACK_

#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TLorentzVector.h"

#define PI 3.14159265

using namespace std;

class SmartTrack {

 public:
  SmartTrack();
  virtual ~SmartTrack();

  void SetTauTrackPtEtaPhi(double, double, double);
  void MatchTo_RecoTrack_Pt_Eta_Phi(vector<float> *pt, vector<float> *eta, vector<float> *phi);
  void SetTauParentPdgId(int pdg){ m_tau_parent_pdg_id = pdg; }
  void MatchTrackToTruth_MaxDR_MaxRelFracPt_TRK_Pt_Eta_Phi_QoP_TRKMC_Bc_Prob_MC_Bc_PdgId_parentIdx_childIdx_Pt_Eta_Phi_Eta_Q(
                                                                                                                             double maxDR,
                                                                                                                             double maxRelFracPt,
															     bool matchBasedOnClosestDR,
                                                                                                                             vector<float> *trk_pt,
                                                                                                                             vector<float> *trk_eta,
                                                                                                                             vector<float> *trk_phi,
                                                                                                                             vector<float> *trk_qoverp,
                                                                                                                             vector<int> *trk_mc_barcode,
                                                                                                                             vector<float> *trk_mc_probability,
                                                                                                                             vector<int> *mc_barcode,
                                                                                                                             vector<int> *mc_pdgId,
                                                                                                                             vector<vector<int> > *mc_parent_index,
                                                                                                                             vector<vector<int> > *mc_child_index,
                                                                                                                             vector<float> *mc_pt,
                                                                                                                             vector<float> *mc_eta,
                                                                                                                             vector<float> *mc_phi,
                                                                                                                             vector<float> *mc_m,
                                                                                                                             vector<float> *mc_charge
                                                                                                                             );
  void UseExternalInformation(int TrackMatchStatus,
                              int TrackSpuriousType,
			      int MCParticleMatchIndex,
                              double maxDR,
                              double maxRelFracPt,
			      bool matchBasedOnClosestDR,
                              vector<float> *trk_pt,
                              vector<float> *trk_eta,
                              vector<float> *trk_phi,
                              vector<float> *trk_qoverp,
                              vector<int> *trk_mc_barcode,
                              vector<float> *trk_mc_probability,
                              vector<int> *mc_barcode,
                              vector<int> *mc_pdgId,
                              vector<vector<int> > *mc_parent_index,
                              vector<vector<int> > *mc_child_index,
                              vector<float> *mc_pt,
                              vector<float> *mc_eta,
                              vector<float> *mc_phi,
                              vector<float> *mc_m,
                              vector<float> *mc_charge
                              );
  double GetKin(const std::string&);

  // old - obsolete
  bool IsRecoTrack() const { return 0;}
  bool IsTruthTrack() const { return 0;}
  int  GetTruthPdgId() const { return 0;}
  double GetTruthMatchingScore() const { return 0;}
  bool IsTruthPrimaryParticle() const {  return 0;}
  int GetTruthTrackParent() const { return 0;}
  bool IsTruthTrackParentPrimaryParticle() const { return 0;}
  int GetTruthTrackParentBarcode() const { return 0;}
  TLorentzVector GetRecoTrackTLV() const { return  m_tau_track_matched_reco_tlv;}
  TLorentzVector GetTruthTrackTLV() const { return m_tau_track_matched_truth_tlv;}
  //

  //reco tracks
  bool Get_tau_track_matched_reco () const { return m_tau_track_matched_reco; }
  TLorentzVector Get_tau_track_matched_reco_tlv  () const { return m_tau_track_matched_reco_tlv; }
  int Get_tau_track_matched_reco_index () const { return m_tau_track_matched_reco_index; }
  int Get_tau_track_matched_reco_barcode () const { return m_tau_track_matched_reco_barcode; }
  double Get_tau_track_matched_reco_probability () const { return m_tau_track_matched_reco_probability; }
  int Get_tau_track_matched_reco_Q  () const { return m_tau_track_matched_reco_Q; }

  //truth charged particles
  bool Get_tau_track_matched_truth  () const { return m_tau_track_matched_truth; }
  int Get_tau_track_matched_truth_pdgId () const { return m_tau_track_matched_truth_pdgId; }
  TLorentzVector Get_tau_track_matched_truth_tlv () const { return m_tau_track_matched_truth_tlv; }
  int Get_tau_track_matched_truth_Q () const { return m_tau_track_matched_truth_Q; }
  double Get_tau_track_matched_truth_dR () const { return m_tau_track_matched_truth_dR; }
  int Get_tau_track_matched_truth_barcode () const { return m_tau_track_matched_truth_barcode; }
  bool Get_tau_track_matched_truth_from_PI () const { return m_tau_track_matched_truth_from_PI; }
  bool Get_tau_track_matched_truth_from_PU () const { return m_tau_track_matched_truth_from_PU; }
  bool Get_tau_track_matched_truth_from_PC () const { return m_tau_track_matched_truth_from_PC; }
  bool Get_tau_track_matched_truth_from_UE () const { return m_tau_track_matched_truth_from_UE; }
  bool Get_tau_track_matched_truth_from_FK () const { return m_tau_track_matched_truth_from_FK; }
  bool Get_tau_track_matched_truth_from_UC () const { return m_tau_track_matched_truth_from_UC; }
  bool Get_tau_track_matched_truth_from_MM () const { return m_tau_track_matched_truth_from_MM; }
  string Get_tau_track_matched_truth_Origin ();
  bool Get_tau_track_matched_truth_is_spurious() const { return m_tau_track_matched_truth_spurious;}

  bool Get_tau_track_matched_truth_from_tau_from_parent() const{ return m_tau_track_matched_truth_from_tau_from_parent; }
  
  int Get_tau_track_matched_truth_parent_pdgId () const { return m_tau_track_matched_truth_parent_pdgId; }
  int Get_tau_track_matched_truth_parent_barcode () const { return m_tau_track_matched_truth_parent_barcode; }

  int Get_tau_track_matched_truth_grandparent_pdgId () const { return m_tau_track_matched_truth_grandparent_pdgId; }
  int Get_tau_track_matched_truth_grandparent_barcode () const { return m_tau_track_matched_truth_grandparent_barcode; }

  //PanTau charged track
  double Get_tau_track_eta () const { return m_tau_track_eta; }
  double Get_tau_track_phi () const { return m_tau_track_phi; }
  double Get_tau_track_pt () const { return m_tau_track_pt; }

 private:

  int m_tau_parent_pdg_id;

  bool m_tau_track_matched_reco;
  TLorentzVector m_tau_track_matched_reco_tlv;
  int m_tau_track_matched_reco_index;
  int m_tau_track_matched_reco_barcode;
  double m_tau_track_matched_reco_probability;
  int m_tau_track_matched_reco_Q;

  bool m_tau_track_matched_truth;
  int m_tau_track_matched_truth_pdgId;
  TLorentzVector m_tau_track_matched_truth_tlv;
  int m_tau_track_matched_truth_Q;
  double m_tau_track_matched_truth_dR;
  int m_tau_track_matched_truth_barcode;
  bool m_tau_track_matched_truth_from_PI; // primary interaction
  bool m_tau_track_matched_truth_from_PU; // pile up
  bool m_tau_track_matched_truth_from_PC; // particle conversions
  bool m_tau_track_matched_truth_from_UE; // underlying event
  bool m_tau_track_matched_truth_from_FK; //fake
  bool m_tau_track_matched_truth_from_UC; //unclassified
  bool  m_tau_track_matched_truth_from_MM; //multimatched
  bool m_tau_track_matched_truth_spurious; //spurious

  bool m_tau_track_matched_truth_from_tau_from_parent;

  int m_tau_track_matched_truth_parent_pdgId;
  int m_tau_track_matched_truth_parent_barcode;

  int m_tau_track_matched_truth_grandparent_pdgId;
  int m_tau_track_matched_truth_grandparent_barcode;

  double m_tau_track_eta;
  double m_tau_track_phi;
  double m_tau_track_pt;


 protected:
  double DeltaR(TLorentzVector &v1, TLorentzVector &v2){
    return DeltaR( v1.Eta(), v1.Phi(), v2.Eta(), v2.Phi() );
  }
  double DeltaR(TLorentzVector &v1, double eta, double phi){
    return DeltaR( v1.Eta(), v1.Phi(), eta, phi );
  }
  double DeltaR(double eta, double phi, TLorentzVector &v1){
    return DeltaR( v1.Eta(), v1.Phi(), eta, phi );
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

  double AbsRelFracObsRef(double obs, double ref){ return std::fabs( (ref-obs)/ref );}

 public:
  ClassDef(SmartTrack, 0)

    };

#endif

