#include "SuperTau.h"

//ClassImp(SuperTau); 

///<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
SuperTau::SuperTau() :
    m_reco_hlv(0,0,0,0), 
    m_true_hlv(0,0,0,0),
    m_truevis_hlv(0,0,0,0),
    m_tau_index(-1),
    m_mc_index(-1),
    m_tau_charge(0),
    m_tau_author(0),
    m_tau_numTrack(0),
    m_tau_nProng(0),
    m_tau_nPi0(0),
    m_tau_match_vis_tau(false),
    m_tau_JetBDTSigLoose(false),
    m_tau_JetBDTSigMedium(false),
    m_tau_JetBDTSigTight(false)

{
  
}
///<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
SuperTau::~SuperTau()
{
}
///<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

///<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

