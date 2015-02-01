
//NOTE: You may have to change the path depending on you setup!
#include "TauObject_PanTau.h"

// ClassImp( TauObject_PanTau );


std::vector<TLorentzVector> TauObject_PanTau::helper_CreateMomentumList(std::vector<double> pts,
                                                                        std::vector<double> etas,
                                                                        std::vector<double> phis,
                                                                        std::vector<double> ms) {
  std::vector<TLorentzVector> resultHLVList = std::vector<TLorentzVector>(0);
  unsigned int nObjects = pts.size();
  for(unsigned int iPFO=0; iPFO<nObjects; iPFO++) {
    TLorentzVector curMom;
    curMom.SetPtEtaPhiM(pts.at(iPFO), etas.at(iPFO), phis.at(iPFO), ms.at(iPFO));
    resultHLVList.push_back(curMom);
  }
  return resultHLVList;
}



TauObject_PanTau::TauObject_PanTau(int                 RecoModePanTau,    // reco mode
                                   int                 RecoModeSubAlg,    // i.e. use RecoModeCellBased for CellBased variables
                                   double              final_pt,          // tau 4-vector: pt
                                   double              final_eta,         // tau 4-vector: eta
                                   double              final_phi,         // tau 4-vector: phi
                                   double              final_m,           // tau 4-vector: m
                                   std::vector<double> ChargedEFOs_pt,    // charged pions: pt values
                                   std::vector<double> ChargedEFOs_eta,   // charged pions: eta values
                                   std::vector<double> ChargedEFOs_phi,   // charged pions: phi values
                                   std::vector<double> ChargedEFOs_m,     // charged pions: m values
                                   std::vector<double> Pi0NeutEFOs_pt,    // neutral pions: pt values
                                   std::vector<double> Pi0NeutEFOs_eta,   // neutral pions: eta values
                                   std::vector<double> Pi0NeutEFOs_phi,   // neutral pions: phi values
                                   std::vector<double> Pi0NeutEFOs_m,     // neutral pions: m values
                                   std::vector<double> NeutralEFOs_pt,    // other neutrals: pt values
                                   std::vector<double> NeutralEFOs_eta,   // other neutrals: eta values
                                   std::vector<double> NeutralEFOs_phi,   // other neutrals: phi values
                                   std::vector<double> NeutralEFOs_m)     // other neutrals: m values
{
  // Fill BDT variables with default values until they are set
  m_BDTInputVariables = std::vector<double>(0);
  unsigned int nBDTVars = TauObject_PanTau::BDTVarID_nVariables;
  for(unsigned int iBDTVar=0; iBDTVar<nBDTVars; iBDTVar++) m_BDTInputVariables.push_back(TauObject_PanTau::DEFAULT_VALUE());

  //Set BDT values to default values
  m_BDTValue_1p0n_vs_1p1n = TauObject_PanTau::DEFAULT_VALUE();
  m_BDTValue_1p0n_vs_1p1n = TauObject_PanTau::DEFAULT_VALUE();
  m_BDTValue_1p0n_vs_1p1n = TauObject_PanTau::DEFAULT_VALUE();

  // Tau Decay Mode
  m_DecayMode = (TauObject_PanTau::DecayMode)RecoModePanTau;

  // Tau 4-vector
  m_Momentum.SetPtEtaPhiM(final_pt, final_eta, final_phi, final_m);

  //Charged Pions
  m_ChargedPions = helper_CreateMomentumList(ChargedEFOs_pt, ChargedEFOs_eta, ChargedEFOs_phi, ChargedEFOs_m);

  //Neutral pions
  //This is based on the relation between CellBased and PanTau decay mode.
  //How this information is stored in the D3PD/xAOD will change in the future.
  //Atm, this is still a bit awkward to extract, but here it goes:
  m_NeutralPions = std::vector<TLorentzVector>(0);
  std::vector<TLorentzVector> list_Pi0Neuts = helper_CreateMomentumList(Pi0NeutEFOs_pt, Pi0NeutEFOs_eta, Pi0NeutEFOs_phi, Pi0NeutEFOs_m);
  std::vector<TLorentzVector> list_Neutrals = helper_CreateMomentumList(NeutralEFOs_pt, NeutralEFOs_eta, NeutralEFOs_phi, NeutralEFOs_m);

  TauObject_PanTau::DecayMode mode_SubAlg = (TauObject_PanTau::DecayMode)RecoModeSubAlg;
  TauObject_PanTau::DecayMode mode_PanTau = (TauObject_PanTau::DecayMode)RecoModePanTau;


  //deal with cases in which the mode is not changed
  if(mode_SubAlg == mode_PanTau) {
    if(mode_PanTau == TauObject_PanTau::decayMode_3pXn) {
      //if mode is 3pXn, only use the first pi0neutral
      m_NeutralPions.push_back(list_Pi0Neuts.at(0));

    } else {
      //if pantau mode is not 3pXn, use all suggested pi0neutrals
      for(unsigned int iPi0=0; iPi0<list_Pi0Neuts.size(); iPi0++) {
        m_NeutralPions.push_back(list_Pi0Neuts.at(iPi0));
      }//end loop pi0
    }
  }//end if modes are equal


  //deal with cases in which pantau changes the decay mode
  // -> choose the correct neutrals from pi0neutrals and neutrals
  if(mode_SubAlg != mode_PanTau) {

    //1p0n -> 1p1n: Use neutral with highest BDT score as pi0
    if(mode_SubAlg == TauObject_PanTau::decayMode_1p0n && mode_PanTau == TauObject_PanTau::decayMode_1p1n) {
      m_NeutralPions.push_back(list_Neutrals.at(0));
    }

    //1p1n -> 1p0n: Do not use any neutrals
    if(mode_SubAlg == TauObject_PanTau::decayMode_1p1n && mode_PanTau == TauObject_PanTau::decayMode_1p0n) {
      m_NeutralPions.clear(); //just to be safe...
    }

    //1p1n -> 1pXn: Use second neutral as pi0 (if existant - it's not existant if cellbased found >2 shots in the pi0neutral
    if(mode_SubAlg == TauObject_PanTau::decayMode_1p1n && mode_PanTau == TauObject_PanTau::decayMode_1pXn) {
      m_NeutralPions.push_back(list_Pi0Neuts.at(0));
      if(list_Neutrals.size() > 1) {
        m_NeutralPions.push_back(list_Neutrals.at(1));
      }
    }

    //1pXn -> 1p1n: merge the two pi0 from CellBased into one pi0
    if(mode_SubAlg == TauObject_PanTau::decayMode_1pXn && mode_PanTau == TauObject_PanTau::decayMode_1p1n) {
      TLorentzVector subAlg_Pi0_A = TLorentzVector();
      TLorentzVector subAlg_Pi0_B = TLorentzVector();
      TLorentzVector hlv_Pi0_A    = TLorentzVector();
      TLorentzVector hlv_Pi0_B    = TLorentzVector();
      if(list_Pi0Neuts.size() > 0) {
        subAlg_Pi0_A = list_Pi0Neuts.at(0);
        hlv_Pi0_A.SetPtEtaPhiM(subAlg_Pi0_A.Pt(), subAlg_Pi0_A.Eta(), subAlg_Pi0_A.Phi(), 0.);
      }
      if(list_Pi0Neuts.size() > 1) {
        subAlg_Pi0_B = list_Pi0Neuts.at(1);
        hlv_Pi0_B.SetPtEtaPhiM(subAlg_Pi0_B.Pt(), subAlg_Pi0_B.Eta(), subAlg_Pi0_B.Phi(), 0.);
      }
      TLorentzVector hlv_SumPi0 = hlv_Pi0_A + hlv_Pi0_B;
      m_NeutralPions.push_back(hlv_SumPi0);
    }

    //3p0n -> 3pXn: Use neutral with highest BDT score as pi0
    if(mode_SubAlg == TauObject_PanTau::decayMode_3p0n && mode_PanTau == TauObject_PanTau::decayMode_3pXn) {
      m_NeutralPions.push_back(list_Neutrals.at(0));
    }

    //3pXn -> 3p0n: Do not use any neutrals
    if(mode_SubAlg == TauObject_PanTau::decayMode_3pXn && mode_PanTau == TauObject_PanTau::decayMode_3p0n) {
      m_NeutralPions.clear(); //just to be safe...
    }

  }//end if modes are not equal

}//end constructor



void    TauObject_PanTau::addBDTInformation(double BDTValue_1p0n_vs_1p1n,
                                            double BDTValue_1p1n_vs_1pXn,
                                            double BDTValue_3p0n_vs_3pXn,
                                            double IDVars_Basic_NNeutralConsts,
                                            double IDVars_Charged_JetMoment_EtDRxTotalEt,
                                            double IDVars_Charged_StdDev_Et_WrtEtAllConsts,
                                            double IDVars_Combined_DeltaR1stNeutralTo1stCharged,
                                            double IDVars_Neutral_HLV_SumM,
                                            double IDVars_Neutral_PID_BDTValues_BDTSort_1,
                                            double IDVars_Neutral_PID_BDTValues_BDTSort_2,
                                            double IDVars_Neutral_Ratio_1stBDTEtOverEtAllConsts,
                                            double IDVars_Neutral_Ratio_EtOverEtAllConsts,
                                            double IDVars_Neutral_Shots_NPhotonsInSeed)
{
  m_BDTValue_1p0n_vs_1p1n = BDTValue_1p0n_vs_1p1n;
  m_BDTValue_1p1n_vs_1pXn = BDTValue_1p1n_vs_1pXn;
  m_BDTValue_3p0n_vs_3pXn = BDTValue_3p0n_vs_3pXn;
  m_BDTInputVariables.at(BDTVarID_Basic_NNeutralConsts)                   = IDVars_Basic_NNeutralConsts;
  m_BDTInputVariables.at(BDTVarID_Charged_JetMoment_EtDRxTotalEt)         = IDVars_Charged_JetMoment_EtDRxTotalEt;
  m_BDTInputVariables.at(BDTVarID_Charged_StdDev_Et_WrtEtAllConsts)       = IDVars_Charged_StdDev_Et_WrtEtAllConsts;
  m_BDTInputVariables.at(BDTVarID_Combined_DeltaR1stNeutralTo1stCharged)  = IDVars_Combined_DeltaR1stNeutralTo1stCharged;
  m_BDTInputVariables.at(BDTVarID_Neutral_HLV_SumM)                       = IDVars_Neutral_HLV_SumM;
  m_BDTInputVariables.at(BDTVarID_Neutral_PID_BDTValues_BDTSort_1)        = IDVars_Neutral_PID_BDTValues_BDTSort_1;
  m_BDTInputVariables.at(BDTVarID_Neutral_PID_BDTValues_BDTSort_2)        = IDVars_Neutral_PID_BDTValues_BDTSort_2;
  m_BDTInputVariables.at(BDTVarID_Neutral_Ratio_1stBDTEtOverEtAllConsts)  = IDVars_Neutral_Ratio_1stBDTEtOverEtAllConsts;
  m_BDTInputVariables.at(BDTVarID_Neutral_Ratio_EtOverEtAllConsts)        = IDVars_Neutral_Ratio_EtOverEtAllConsts;
  m_BDTInputVariables.at(BDTVarID_Neutral_Shots_NPhotonsInSeed)           = IDVars_Neutral_Shots_NPhotonsInSeed;
  return;
}



double                      TauObject_PanTau::getBDTInputVariable(TauObject_PanTau::BDTVariableID BDTVarID)
{
  unsigned int iBDTVarID = (unsigned int)BDTVarID;
  if(iBDTVarID > m_BDTInputVariables.size()) {
    std::cout << "WARNING (TauObject_PanTau) No BDT input variable with index " << iBDTVarID << "! Returning default value of " << DEFAULT_VALUE << std::endl;
    return TauObject_PanTau::DEFAULT_VALUE();
  }

  return m_BDTInputVariables.at(iBDTVarID);

}


