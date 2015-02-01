
#include "SmartTrack.h"

SmartTrack::SmartTrack() :

  m_tau_parent_pdg_id(23),

  m_tau_track_matched_reco(false),
  m_tau_track_matched_reco_tlv(0,0,0,0),
  m_tau_track_matched_reco_index(0),
  m_tau_track_matched_reco_barcode(0),
  m_tau_track_matched_reco_probability(0),
  m_tau_track_matched_reco_Q(0),

  m_tau_track_matched_truth(false),
  m_tau_track_matched_truth_pdgId(0),
  m_tau_track_matched_truth_tlv(0,0,0,0),
  m_tau_track_matched_truth_Q(0),
  m_tau_track_matched_truth_dR(0),
  m_tau_track_matched_truth_barcode(0),
  m_tau_track_matched_truth_from_PI(false),
  m_tau_track_matched_truth_from_PU(false),
  m_tau_track_matched_truth_from_PC(false),
  m_tau_track_matched_truth_from_UE(false),
  m_tau_track_matched_truth_from_FK(false),
  m_tau_track_matched_truth_from_UC(false),
  m_tau_track_matched_truth_from_MM(false),
  m_tau_track_matched_truth_spurious(false),

  m_tau_track_matched_truth_from_tau_from_parent(false),
  m_tau_track_matched_truth_parent_pdgId(0),
  m_tau_track_matched_truth_parent_barcode(0),
  m_tau_track_matched_truth_grandparent_pdgId(0),
  m_tau_track_matched_truth_grandparent_barcode(0),

  m_tau_track_eta(-123),
  m_tau_track_phi(-123),
  m_tau_track_pt(-123)
{


}

SmartTrack::~SmartTrack(){

}


void SmartTrack::SetTauTrackPtEtaPhi(double x, double y, double z){

  m_tau_track_pt = x;
  m_tau_track_eta = y;
  m_tau_track_phi = z;

}

void SmartTrack::MatchTo_RecoTrack_Pt_Eta_Phi(vector<float> *pt, vector<float> *eta, vector<float> *phi){

  if(!pt || !eta || !phi) { cerr<<"SmartTrack::RecoTracksPtEtaPhi - null pt/eta/phi pointer "<<endl; return;}

  if(m_tau_track_pt < 0){ cerr<<"SmartTrack::RecoTracksPtEtaPhi - tau track not set "<<endl; return;}

  for(int i=0; i< (int)pt->size(); i++){
    if( DeltaR(m_tau_track_eta, m_tau_track_phi, eta->at(i), phi->at(i) ) < 0.01 && AbsRelFracObsRef(m_tau_track_pt, pt->at(i)) < 0.05 ){
      //cout<<"\tmatched "<<pt->at(i)<<endl;
      m_tau_track_matched_reco = true;
    }
  }

}

void SmartTrack::MatchTrackToTruth_MaxDR_MaxRelFracPt_TRK_Pt_Eta_Phi_QoP_TRKMC_Bc_Prob_MC_Bc_PdgId_parentIdx_childIdx_Pt_Eta_Phi_Eta_Q(
                                                                                                                                       double opt_tauTrk_mcTrk_match_maxdR,
                                                                                                                                       double opt_tauTrk_mcTrk_match_maxAbsRelFracPt,
                                                                                                                                       bool opt_pan_tau_trk_reco_trk_match_closest_Dr,// to be implemented
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
                                                                                                                                       ){

  if(m_tau_track_pt < 0){ cerr<<"SmartTrack::MatchTo_RecoTrack_... - tau track quantities are not set "<<endl; return;}

  //we do not define the tau track TLV with m=0

  //initialize
  m_tau_track_matched_reco = false;
  m_tau_track_matched_reco_tlv = TLorentzVector(0.,0.,0.,0.);
  m_tau_track_matched_reco_index = 0;
  m_tau_track_matched_reco_barcode = 0;
  m_tau_track_matched_reco_probability = 0;
  m_tau_track_matched_reco_Q = 0;

  m_tau_track_matched_truth = false;
  m_tau_track_matched_truth_pdgId = 0;
  m_tau_track_matched_truth_tlv = TLorentzVector(0.,0.,0.,0.);
  m_tau_track_matched_truth_Q = 0;
  m_tau_track_matched_truth_barcode = 0;
  m_tau_track_matched_truth_from_PI = false;
  m_tau_track_matched_truth_from_PU = false;
  m_tau_track_matched_truth_from_PC = false;
  m_tau_track_matched_truth_from_UE = false;

  m_tau_track_matched_truth_parent_pdgId = 0;
  m_tau_track_matched_truth_parent_barcode = 0;

  m_tau_track_matched_truth_grandparent_pdgId = 0;
  m_tau_track_matched_truth_grandparent_barcode = 0;

  //loop over reco tracks and find the associated ones
  TLorentzVector vRecTrk;     //reco trk TLV
  for(int i=0; i< (int)trk_pt->size(); i++){// ATTENTION: all trk_* should have running index i
    vRecTrk.SetPtEtaPhiM( (*trk_pt)[i]/1000., (*trk_eta)[i], (*trk_phi)[i], 0);
    if( DeltaR(m_tau_track_eta, m_tau_track_phi, vRecTrk )<opt_tauTrk_mcTrk_match_maxdR && AbsRelFracObsRef(m_tau_track_pt, vRecTrk.Pt())<opt_tauTrk_mcTrk_match_maxAbsRelFracPt){
      m_tau_track_matched_reco = true; //matched reco track
      m_tau_track_matched_reco_tlv = vRecTrk;
      m_tau_track_matched_reco_index = i;
      m_tau_track_matched_reco_barcode = trk_mc_barcode->at(i);
      m_tau_track_matched_reco_probability = trk_mc_probability->at(i);
      m_tau_track_matched_reco_Q = (trk_qoverp->at(i) > 0) ? +1 : -1;
      /*cout<<"SmartTrack::MatchTo_RecoTrack_ - tau trk - reco trk matched at i trk "<<i<<"/"<<trk_pt->size()<<endl; */
      break;
    }
  }//reco

  if(!m_tau_track_matched_reco) return; // no reason to continue

  //find particle and parent using Barcode
  TLorentzVector vMC;
  int mc_n = (int)mc_pt->size();
  for(int j = 0; j < mc_n; j++){ // ATTENTION: all mc_* should have running index j

    vMC.SetPtEtaPhiM( (*mc_pt)[j]/1000., (*mc_eta)[j], (*mc_phi)[j], (*mc_m)[j]/1000.);

    ////
    //cout<<"mc "<<j<<endl;
    //cout<<"pt "<<(*mc_pt)[j]/1000.<< " eta "<< (*mc_eta)[j]<<" phi "<< (*mc_phi)[j]<<" m "<< (*mc_m)[j]/1000.<<" q "<< (*mc_charge)[j]<<endl;
    //cout<<vMC.Pt()<<" "<<vMC.Eta()<<" "<<vMC.Phi()<<" "<<vMC.M()<<endl;
    //inf eta : tau->Scan("mc_pdgId: mc_pt/1000. : mc_eta : mc_phi", "EventNumber == 13543908")

    bool kBarcode =  ( m_tau_track_matched_reco_barcode == mc_barcode->at(j) );

    //it makes sense to do matching if bc <= 10,000 AND if matching via bc works
    double dr_RecTrk_McPart(0);
    if( (*mc_barcode)[j] <= 10000 /*&& kBarcode*/){
      //dr_RecTrk_McPart = DeltaR(vRecTrk, vMC); // in conjuction with bc
      dr_RecTrk_McPart = DeltaR( (*mc_eta)[j], (*mc_phi)[j], vRecTrk );// to avoid: Warning in <TVector3::PseudoRapidity>: transvers momentum = 0! return +/- 10e10
    }

    /*double dr_RecTrk_McPart_10k(0);
      if( (*mc_barcode)[j] <= 10000 ){
      dr_RecTrk_McPart_10k = DeltaR( (*mc_eta)[j], (*mc_phi)[j], vRecTrk )
      }*/


    //reco track - mc particle matching via barcode - the standard way //http://indico.cern.ch/event/a055665/material/0/0?contribId=s1t2
    if( kBarcode ){ // mc BC = rec BC

      //now find parent
      int parentPdg(0); //pdg
      int parentIdx(0); //index
      int parentBc(0); //barcode
      for(unsigned int m=0; m < mc_parent_index->at(j).size(); m++) {
        parentIdx = mc_parent_index->at(j).at(m);
        parentPdg = parentIdx < mc_n ? mc_pdgId->at( parentIdx ) : 0;
        parentBc = mc_barcode->at(m);
        if( fabs(parentPdg) == 15) break; //once found, stop looking for parents
      }

      //grandparent
      int gparentPdg(0); //pdg
      int gparentIdx(0); //index
      int gparentBc(0); //barcode
      for(int jj = 0; jj < mc_n; jj++){
        if( mc_pdgId->at(jj) == parentPdg && jj == parentIdx ){
          for(unsigned int mm=0; mm < mc_parent_index->at(jj).size(); mm++) {
            gparentIdx = mc_parent_index->at(jj).at(mm);
            gparentPdg = parentIdx < mc_n ? mc_pdgId->at( gparentIdx ) : 0;
            gparentBc = mc_barcode->at(mm);
            if( fabs(parentPdg) == m_tau_parent_pdg_id ) break; // tau's parent found - save time now
          }
        }
      }
      //decay chain

      bool kChain = ( fabs(parentPdg) == 15 && fabs(gparentPdg) == m_tau_parent_pdg_id);// track <--- tau (15) <--- parent, eg Z(23)

      //matched particle
      m_tau_track_matched_truth = true;
      m_tau_track_matched_truth_pdgId = mc_pdgId->at(j);
      m_tau_track_matched_truth_tlv = vMC;
      m_tau_track_matched_truth_Q = mc_charge->at(j);
      m_tau_track_matched_truth_dR = dr_RecTrk_McPart;
      m_tau_track_matched_truth_barcode = mc_barcode->at(j);
      if( (mc_barcode->at(j) <= 10000) ){
        if(kChain)
          m_tau_track_matched_truth_from_PI = true;
        else
          m_tau_track_matched_truth_from_UE = true;
      }else if  (mc_barcode->at(j) > 10000 && mc_barcode->at(j) <= 200000){
        m_tau_track_matched_truth_from_PU = true;
      }else if (mc_barcode->at(j) >= 200000){
        m_tau_track_matched_truth_from_PC = true;
      } else{
        cout<<"SmartTrack::MatchTrack... -  unknown barcode "<<mc_barcode->at(j)<<endl;
      }


      //matched parent
      m_tau_track_matched_truth_parent_pdgId = parentPdg;
      m_tau_track_matched_truth_parent_barcode = parentBc;

      //matched grandparent
      m_tau_track_matched_truth_grandparent_pdgId = gparentPdg;
      m_tau_track_matched_truth_grandparent_barcode = gparentBc;


      /* cout<<"SmartTrack::MatchTo_RecoTrack "<<endl;
         cout<<"\t matched prob "<< m_tau_track_matched_reco_probability <<endl;
         cout<<"\t trk-part DR "<< dr_RecTrk_McPart <<endl;
         cout<<"\t trk q "<< m_tau_track_matched_reco_Q <<endl;
         cout<<"\t part q "<<m_tau_track_matched_truth_Q<<endl;
         cout<<"\t part id "<<m_tau_track_matched_truth_pdgId<<endl;
         cout<<"\t part bc "<< m_tau_track_matched_truth_barcode<<endl;
         cout<<"\t parent id "<<m_tau_track_matched_truth_parent_pdgId<<endl;
         cout<<"\t parent bc "<<m_tau_track_matched_truth_parent_barcode<<endl;
         cout<<"\t gparent id "<<m_tau_track_matched_truth_grandparent_pdgId<<endl;
         cout<<"\t gparent bc "<<m_tau_track_matched_truth_grandparent_barcode<<endl;
      */

      break; //any reason to continue?

    }else if( dr_RecTrk_McPart >0 && dr_RecTrk_McPart < 0.05) { //barcodes do not match  but dR does -> spurious track, underlying event most likely

      //find parent
      int parentPdg(0); //pdg
      int parentIdx(0); //index
      int parentBc(0); //barcode
      for(unsigned int m=0; m < mc_parent_index->at(j).size(); m++) {
        parentIdx = mc_parent_index->at(j).at(m);
        parentPdg = parentIdx < mc_n ? mc_pdgId->at( parentIdx ) : 0;
        parentBc = mc_barcode->at(m);
        if( fabs(parentPdg) == 15) break; //once found, stop looking for parents
      }

      //matched particle
      m_tau_track_matched_truth = true;
      m_tau_track_matched_truth_pdgId = mc_pdgId->at(j);
      m_tau_track_matched_truth_tlv = vMC;
      m_tau_track_matched_truth_Q = mc_charge->at(j);
      m_tau_track_matched_truth_dR = dr_RecTrk_McPart;
      m_tau_track_matched_truth_barcode = mc_barcode->at(j);

      //matched parent
      m_tau_track_matched_truth_parent_pdgId = parentPdg;
      m_tau_track_matched_truth_parent_barcode = parentBc;

      m_tau_track_matched_truth_from_UE = true;

      //cout<<"BC FAILED - DR OK parent "<< parentPdg<<"  dr "<< dr_RecTrk_McPart <<endl;

    }else{
    }//enough with the barcode

  }//loop mc with index j


  //find matched particle and parent using DR
  //loop over mc
  /*  cout<<"SmartTrack::MatchTo_RecoTrack_ - searching for parent again "<<endl;
      for(int ij = 0; ij < mc_n; ij++){ // ATTENTION: all mc_* should have running index ij in this
      if( fabs( mc_pdgid->at(ij)) == 15){ //tau
      for (int jc = 0; jc < (int)mc_childIdx->at(ij).size(); jc++ ){
      int childIdx = (*mc_childIdx)[ij][jc];
      int childPdgid = std::fabs( (*mc_pdgId)[childIdx] );
      int childBc = (*mc_bc)[childIdx];
      TLorentzVector vTauChild;
      vTauChild.SetPtEtaPhiM( (*mc_pt)[childIdx]/1000., (*mc_eta)[childIdx], (*mc_phi)[childIdx], (*mc_m)[childIdx]/1000.);
      double dr_trk_tau_child = DeltaR( vRecTrk, vTauChild);
      cout<<"tau child "<<jc<<" id "<<childPdgid<<" dr "<<dr_trk_tau_child<<" bc "<<childBc<<" trk bc "<<tmp_reco_trk_barcode<<endl;
      }//loop over children
      }//is a tau
      }//loop on mc
  */



}

void SmartTrack::UseExternalInformation(//Truth matching tool information
					int TrackMatchStatus,
                                        int TrackSpuriousType,
                                        int MCParticleMatchIndex,
					//matching options
                                        double opt_tauTrk_mcTrk_match_maxdR,
                                        double opt_tauTrk_mcTrk_match_maxAbsRelFracPt,
                                        bool opt_pan_tau_trk_reco_trk_match_closest_Dr,
					//reco tracks
                                        vector<float> *trk_pt,
                                        vector<float> *trk_eta,
                                        vector<float> *trk_phi,
                                        vector<float> *trk_qoverp,
                                        vector<int> *trk_mc_barcode,
                                        vector<float> *trk_mc_probability,
					//mc true particles
                                        vector<int> *mc_barcode,
                                        vector<int> *mc_pdgId,
                                        vector<vector<int> > *mc_parent_index,
                                        vector<vector<int> > *mc_child_index,
                                        vector<float> *mc_pt,
                                        vector<float> *mc_eta,
                                        vector<float> *mc_phi,
                                        vector<float> *mc_m,
                                        vector<float> *mc_charge
                                        ){

  //initialize
  m_tau_track_matched_reco = false;
  m_tau_track_matched_reco_tlv = TLorentzVector(0.,0.,0.,0.);
  m_tau_track_matched_reco_index = 0;
  m_tau_track_matched_reco_barcode = 0;
  m_tau_track_matched_reco_probability = 0;
  m_tau_track_matched_reco_Q = 0;

  m_tau_track_matched_truth = false;
  m_tau_track_matched_truth_pdgId = 0;
  m_tau_track_matched_truth_tlv = TLorentzVector(0.,0.,0.,0.);
  m_tau_track_matched_truth_Q = 0;
  m_tau_track_matched_truth_barcode = 0;
  m_tau_track_matched_truth_from_PI = false;
  m_tau_track_matched_truth_from_PU = false;
  m_tau_track_matched_truth_from_PC = false;
  m_tau_track_matched_truth_from_UE = false;
  m_tau_track_matched_truth_from_FK = false;
  m_tau_track_matched_truth_from_UC = false;
  m_tau_track_matched_truth_from_MM = false;
  m_tau_track_matched_truth_spurious = false;

  m_tau_track_matched_truth_parent_pdgId = 0;
  m_tau_track_matched_truth_parent_barcode = 0;

  m_tau_track_matched_truth_grandparent_pdgId = 0;
  m_tau_track_matched_truth_grandparent_barcode = 0;


  /*
    TrackMatchStatus_t
    kTRACKMATCHSTATUS_UNCL             = 0, // Track is unclassified
    kTRACKMATCHSTATUS_TRUTH_MATCHED    = 1, // Track is truth matched
    kTRACKMATCHSTATUS_TRUTH_UNMATCHED  = 2, // Track is spurious
    kTRACKMATCHSTATUS_MULTIMATCHED     = 3, // Track is truth matched to more than 1 particle

    TrackSpuriousType_t
    kTRACKSPURIOUSTYPE_UNCL         = 0, // Track is unclassified
    kTRACKSPURIOUSTYPE_CONVERSION   = 1, // Track is from conversion
    kTRACKSPURIOUSTYPE_PILEUP       = 2, // Track is from pileup
    kTRACKSPURIOUSTYPE_UE           = 3, // Track is from underlying event
    kTRACKSPURIOUSTYPE_FAKE         = 4, // Track is a fake
    kTRACKNSPURIOUS_TYPES
  */

  //Track type info from external tool - set, before any 'continue'
  if(TrackMatchStatus != 0){
    m_tau_track_matched_truth = true;
    //m_tau_track_matched_reco = true;
  }
  if(TrackMatchStatus == 1) m_tau_track_matched_truth_from_PI = true;
  if(TrackMatchStatus == 2) {
    if(TrackSpuriousType == 0) m_tau_track_matched_truth_from_UC = true;
    if(TrackSpuriousType == 1) m_tau_track_matched_truth_from_PC = true;
    if(TrackSpuriousType == 2) m_tau_track_matched_truth_from_PU = true;
    if(TrackSpuriousType == 3) m_tau_track_matched_truth_from_UE = true;
    if(TrackSpuriousType == 4) m_tau_track_matched_truth_from_FK = true;
    m_tau_track_matched_truth_spurious = true;
  }
  if(TrackMatchStatus == 3) m_tau_track_matched_truth_from_MM = true;


  /*
    cout<<"\npi "<<m_tau_track_matched_truth_from_PI<<endl;
    cout<<"pu "<<m_tau_track_matched_truth_from_PU<<endl;
    cout<<"pc "<<m_tau_track_matched_truth_from_PC<<endl;
    cout<<"ue "<<m_tau_track_matched_truth_from_UE<<endl;
    cout<<"fk "<<m_tau_track_matched_truth_from_FK<<endl;
    cout<<"uc "<<m_tau_track_matched_truth_from_UC<<endl;
    cout<<"mm "<<m_tau_track_matched_truth_from_MM<<endl;
  */

  //more inofrmation on the matched mc track using tree variables
  //if(!m_tau_track_matched_truth) return; //no reason to build info for spurious tracks for which eta/phi vars are broken

  //loop over reco tracks and find the associated ones - before any 'continue'
  TLorentzVector vRecTrk(0,0,0,0);     //reco trk TLV - later use
  if(opt_pan_tau_trk_reco_trk_match_closest_Dr){ //match on closest DR first and then examine pT
    //
    double tmpRecTrkMinDR(1e3);
    int tmpRecTrkIndex(0);
    for(int i=0; i< (int)trk_pt->size(); i++){// ATTENTION: all trk_* should have running index i
      double dR =  DeltaR(m_tau_track_eta, m_tau_track_phi,  (*trk_eta)[i], (*trk_phi)[i]);
      if( dR < tmpRecTrkMinDR){
        tmpRecTrkMinDR = dR;
        tmpRecTrkIndex = i;
      }
    }
    if(  tmpRecTrkMinDR < opt_tauTrk_mcTrk_match_maxdR ){
      if(AbsRelFracObsRef( m_tau_track_pt, (*trk_pt)[tmpRecTrkIndex]/1000. ) > opt_tauTrk_mcTrk_match_maxAbsRelFracPt)
	cout<<"matched track to "<<m_tau_track_pt<<"  "<<(*trk_pt)[tmpRecTrkIndex]/1000.<<endl;//HERE
      if(AbsRelFracObsRef( m_tau_track_pt, (*trk_pt)[tmpRecTrkIndex]/1000. ) < opt_tauTrk_mcTrk_match_maxAbsRelFracPt){
        vRecTrk.SetPtEtaPhiM( (*trk_pt)[tmpRecTrkIndex]/1000., (*trk_eta)[tmpRecTrkIndex], (*trk_phi)[tmpRecTrkIndex], 0);
        m_tau_track_matched_reco = true; //matched reco track
        m_tau_track_matched_reco_tlv = vRecTrk;
	m_tau_track_matched_reco_index = tmpRecTrkIndex;
        if(trk_mc_barcode) m_tau_track_matched_reco_barcode = trk_mc_barcode->at(tmpRecTrkIndex);
        if(trk_mc_probability) m_tau_track_matched_reco_probability = trk_mc_probability->at(tmpRecTrkIndex);
        m_tau_track_matched_reco_Q = (trk_qoverp->at(tmpRecTrkIndex) > 0) ? +1 : -1;
	//m_tau_track_matched_reco_barcode =  tmpRecTrkIndex;
      }
    }
    //
  }else{ //simulaneous match on DR and pT
    //
    for(int i=0; i< (int)trk_pt->size(); i++){// ATTENTION: all trk_* should have running index i

      if( DeltaR(m_tau_track_eta, m_tau_track_phi, (*trk_eta)[i], (*trk_phi)[i] ) < opt_tauTrk_mcTrk_match_maxdR
          && AbsRelFracObsRef(m_tau_track_pt,  (*trk_pt)[i]/1000. ) < opt_tauTrk_mcTrk_match_maxAbsRelFracPt ){
	vRecTrk.SetPtEtaPhiM( (*trk_pt)[i]/1000., (*trk_eta)[i], (*trk_phi)[i], 0);
        m_tau_track_matched_reco = true; //matched reco track
        m_tau_track_matched_reco_tlv = vRecTrk;
	m_tau_track_matched_reco_index = i;
        if(trk_mc_barcode) m_tau_track_matched_reco_barcode = trk_mc_barcode->at(i);
        if(trk_mc_probability) m_tau_track_matched_reco_probability = trk_mc_probability->at(i);
        m_tau_track_matched_reco_Q = (trk_qoverp->at(i) > 0) ? +1 : -1;
	//m_tau_track_matched_reco_barcode =  i;
        break;
      }
    }
    //
  }

  //the MC matched particle index
  int j = MCParticleMatchIndex;

  if(j < 0 ){ /*probably a spurious track without index*/ return;}
  if(j >= (int)mc_pt->size() ){ cerr<<"SmartTrack::UseExternalInformation - matched mc index "<<j <<" out of range "<<mc_pt->size()<<endl; return;}

  //mc particle 4-mom
  TLorentzVector vMC; vMC.SetPtEtaPhiM( (*mc_pt)[j]/1000., (*mc_eta)[j], (*mc_phi)[j], (*mc_m)[j]/1000.);

  //mc length
  int mc_n = (int)mc_pt->size();

  //now find parent
  int parentPdg(0); //pdg
  int parentIdx(0); //index
  int parentBc(0); //barcode
  for(unsigned int m=0; m < mc_parent_index->at(j).size(); m++) {
    parentIdx = mc_parent_index->at(j).at(m);
    parentPdg = parentIdx < mc_n ? mc_pdgId->at( parentIdx ) : 0;
    parentBc = mc_barcode->at(m);
    if( fabs(parentPdg) == 15) break; //once found, stop looking for parents
  }

  //grandparent
  int gparentPdg(0); //pdg
  int gparentIdx(0); //index
  int gparentBc(0); //barcode
  for(int jj = 0; jj < mc_n; jj++){
    if( mc_pdgId->at(jj) == parentPdg && jj == parentIdx ){
      for(unsigned int mm=0; mm < mc_parent_index->at(jj).size(); mm++) {
        gparentIdx = mc_parent_index->at(jj).at(mm);
        gparentPdg = parentIdx < mc_n ? mc_pdgId->at( gparentIdx ) : 0;
        gparentBc = mc_barcode->at(mm);
        if( fabs(parentPdg) == m_tau_parent_pdg_id ) break; // tau's parent found - save time now
      }
    }
  }

  //decay chain
  bool kChain = ( fabs(parentPdg) == 15 && fabs(gparentPdg) == m_tau_parent_pdg_id);// track <--- tau (15) <--- parent, eg Z(23)

  //matched particle
  m_tau_track_matched_truth = true;
  m_tau_track_matched_truth_pdgId = mc_pdgId->at(j);
  m_tau_track_matched_truth_tlv = vMC;
  m_tau_track_matched_truth_Q = mc_charge->at(j);
  m_tau_track_matched_truth_barcode = mc_barcode->at(j);

  //parent and grandmother
  m_tau_track_matched_truth_from_tau_from_parent = kChain;

  m_tau_track_matched_truth_parent_pdgId = parentPdg;
  m_tau_track_matched_truth_parent_barcode = parentBc;

  m_tau_track_matched_truth_grandparent_pdgId = gparentPdg;
  m_tau_track_matched_truth_grandparent_barcode = gparentBc;


  //truth reco related
  if(!m_tau_track_matched_reco) return; // no reason to continue

  double dr_RecTrk_McPart(0);
  if( (*mc_barcode)[j] <= 10000 /*&& kBarcode*/){
    dr_RecTrk_McPart = DeltaR( (*mc_eta)[j], (*mc_phi)[j], vRecTrk );// to avoid: Warning in <TVector3::PseudoRapidity>: transvers momentum = 0! return +/- 10e10
  }
  m_tau_track_matched_truth_dR = dr_RecTrk_McPart;

}

string SmartTrack::Get_tau_track_matched_truth_Origin(){

  if( Get_tau_track_matched_truth_from_PI() ) return "PI";
  else if( Get_tau_track_matched_truth_from_PU() ) return "PU";
  else if( Get_tau_track_matched_truth_from_UE() ) return "UE";
  else if( Get_tau_track_matched_truth_from_PC() ) return "PC";
  else if( Get_tau_track_matched_truth_from_FK() ) return "FK";
  else if( Get_tau_track_matched_truth_from_UC() ) return "UC";
  else if( Get_tau_track_matched_truth_from_MM() ) return "MM";

  else {cout<<"SmartTrack::Get_tau_track_matched_truth_Origin() - unknown track origin"<<endl;}

  return "Other";
}

double SmartTrack::GetKin(const std::string&t){

  if(t=="eta") return m_tau_track_eta;
  else if(t=="phi") return m_tau_track_phi;
  else if(t=="pt") return m_tau_track_pt;
  else cerr<<"SmartTrack:Get - unknown variable "<<t<<endl;

  return -123;
}
