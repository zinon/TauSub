#ifndef _TAUOBJECT_PANTAU_H_
#define _TAUOBJECT_PANTAU_H_

// root includes
#include "TLorentzVector.h"

// c++ includes
#include <iostream>
#include <vector>


/**
* 
* Class describing a substructure based tau object using CellBased+PanTau
* 
*  USAGE:
*   when reading variables from the D3PD to build objects, do
* 
*       if(tau_pantau_CellBased_isPanTauCandidate == 1) {
*           // omitting the prefix tau_pantau_CellBased_ in the constructor for readability
*           TauObject_PanTau currentPanTauTau = TauObject_PanTau(RecoModePanTau,
*                                                                RecoModeCellBased,
*                                                                final_pt,
*                                                                final_eta,
*                                                                final_phi,
*                                                                final_m,
*                                                                ChargedEFOs_pt,
*                                                                ChargedEFOs_eta,
*                                                                ChargedEFOs_phi,
*                                                                ChargedEFOs_m,
*                                                                Pi0NeutEFOs_pt,
*                                                                Pi0NeutEFOs_eta,
*                                                                Pi0NeutEFOs_phi,
*                                                                Pi0NeutEFOs_m,
*                                                                NeutralEFOs_pt,
*                                                                NeutralEFOs_eta,
*                                                                NeutralEFOs_phi,
*                                                                NeutralEFOs_m);
*           myListOfPanTauTaus.push_back(currentPanTauTau);
*       }
* 
* 
* 
* If you also need the BDT values and BDT input variables, use this code:
* 
*    if(tau_pantau_CellBased_isPanTauCandidate == 1) {
*           TauObject_PanTau currentPanTauTau = TauObject_PanTau( ... )
* 
*           // omitting the prefix tau_pantau_CellBased_ for readability
*           currentPanTauTau.addBDTInformation( BDTValue_1p0n_vs_1p1n,
*                                               BDTValue_1p0n_vs_1p1n,
*                                               BDTValue_1p0n_vs_1p1n,
*                                               IDVars_Basic_NNeutralConsts,
*                                               IDVars_Charged_JetMoment_EtDRxTotalEt,
*                                               IDVars_Charged_StdDev_Et_WrtEtAllConsts,
*                                               IDVars_Combined_DeltaR1stNeutralTo1stCharged,
*                                               IDVars_Neutral_HLV_SumM,
*                                               IDVars_Neutral_PID_BDTValues_BDTSort_1,
*                                               IDVars_Neutral_PID_BDTValues_BDTSort_2,
*                                               IDVars_Neutral_Ratio_1stBDTEtOverEtAllConsts,
*                                               IDVars_Neutral_Ratio_EtOverEtAllConsts,
*                                               IDVars_Neutral_Shots_NPhotonsInSeed);
*           myListOfPanTauTaus.push_back(currentPanTauTau);
*     }
* 
* 
*/



class TauObject_PanTau {
	
	public:
		
		//! Constants
		static double DEFAULT_VALUE() {return -1111.;}
		
		//! Enumerations
		
		// Enum the decay modes
		enum DecayMode {
			decayMode_1p0n   = 0,
			decayMode_1p1n   = 1,
			decayMode_1pXn   = 2,
			decayMode_3p0n   = 3,
			decayMode_3pXn   = 4,
			decayMode_nModes = 5
		};
		
		//enum for BDT variables (for detailed studies)
		enum BDTVariableID {
			BDTVarID_Basic_NNeutralConsts = 0,
			BDTVarID_Charged_JetMoment_EtDRxTotalEt = 1,
			BDTVarID_Charged_StdDev_Et_WrtEtAllConsts = 2,
			BDTVarID_Combined_DeltaR1stNeutralTo1stCharged = 3,
			BDTVarID_Neutral_HLV_SumM = 4,
			BDTVarID_Neutral_PID_BDTValues_BDTSort_1 = 5,
			BDTVarID_Neutral_PID_BDTValues_BDTSort_2 = 6,
			BDTVarID_Neutral_Ratio_1stBDTEtOverEtAllConsts = 7,
			BDTVarID_Neutral_Ratio_EtOverEtAllConsts = 8,
			BDTVarID_Neutral_Shots_NPhotonsInSeed = 9,
			BDTVarID_nVariables = 10
		};
		
		
		//!Constructor
		// Only create a TauObject_PanTau, if tau_pantau_*_isPanTauCandidate == 1
		// Otherwise this class will contain useless & wrong information!
		
		//The arguments have to be the values extracted from the D3PD
		//The prefix tau_pantau_CellBased_ (or tau_pantau_eflowRec_) is omitted in the arguments list,
		//  i.e. the first argument should be 'tau_pantau_CellBased_RecoModePanTau', etc.
		TauObject_PanTau(int                 RecoModePanTau,    // reco mode
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
						 std::vector<double> NeutralEFOs_m);    // other neutrals: m values
		
		TauObject_PanTau(){};//ZZ
		~TauObject_PanTau(){};//ZZ
		
		//!Initialize function for the BDT related variables
		// Like in the constructor, the prefix 'tau_pantau_CellBased_' is omitted
		// NOTE: This function will only work for CellBased, because CellBased 
		// NOTE:   is the default & baseline algorithm to use PanTau with.
		void    addBDTInformation(double BDTValue_1p0n_vs_1p1n,
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
								  double IDVars_Neutral_Shots_NPhotonsInSeed);
								  
								  
								  //!Getter functions
								  
								  //basic information
								  DecayMode                   getDecayMode()    {return m_DecayMode;}
								  TLorentzVector              getMomentum()     {return m_Momentum;}
								  std::vector<TLorentzVector> getChargedPions() {return m_ChargedPions;}
								  std::vector<TLorentzVector> getNeutralPions() {return m_NeutralPions;}
								  
								  //detailed information (BDT values, BDT input variables)
								  double                      getBDTValue_1p0n_vs_1p1n() {return m_BDTValue_1p0n_vs_1p1n;}
								  double                      getBDTValue_1p1n_vs_1pXn() {return m_BDTValue_1p1n_vs_1pXn;}
								  double                      getBDTValue_3p0n_vs_3pXn() {return m_BDTValue_3p0n_vs_3pXn;}
								  double                      getBDTInputVariable(TauObject_PanTau::BDTVariableID BDTVarID);
								  
								  
	private:
		
		//! Member variables
		
		// basic information
		DecayMode                   m_DecayMode;
		TLorentzVector              m_Momentum;
		std::vector<TLorentzVector> m_ChargedPions;
		std::vector<TLorentzVector> m_NeutralPions;
		
		
		// Detailed information (BDT values, BDT input variables)
		double                      m_BDTValue_1p0n_vs_1p1n;
		double                      m_BDTValue_1p1n_vs_1pXn;
		double                      m_BDTValue_3p0n_vs_3pXn;
		std::vector<double>         m_BDTInputVariables;
		
		
		//! Helper functions
		
		//helper function to sort pts, etas, phis, ms from D3PD into TLorentzVector objects
		std::vector<TLorentzVector> helper_CreateMomentumList(std::vector<double> pts,
															  std::vector<double> etas,
															  std::vector<double> phis,
															  std::vector<double> ms);
															  
// 	private:
// 		ClassDef( TauObject_PanTau, 0 );
};


#endif


