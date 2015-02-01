#ifndef _SUPERTAU_
#define _SUPERTAU_

#include <iostream>
#include <cmath>

#include "TROOT.h"
#include "TLorentzVector.h"

using namespace std;

class TLorentzVector;

class SuperTau {

  SuperTau *self; // self-class container

 public:
  SuperTau();
  virtual ~SuperTau();

  void Set_index(int i ){ m_tau_index = i; }
  void Set_mc_index(int i ){ m_mc_index = i; }
  void Set_hlv( const TLorentzVector &lv){ Set_hlv("reco", lv); }
  void Set_hlv( const std::string &type, const TLorentzVector &lv){
    if(type == "reco")
      m_reco_hlv = lv;
    else if(type == "true")
      m_true_hlv = lv;
    else if(type == "truevis")
      m_truevis_hlv = lv;
    else{
      cerr<<"Unable to set hlv '"<<type<<"'"<<endl;
    }
  }
  void Set_charge(int q){ m_tau_charge = q;}
  void Set_author(int a){ m_tau_author = a; }
  void Set_numTrack(int n){ m_tau_numTrack = n; }
  void Set_nProng(int n){ m_tau_nProng = n; }
  void Set_nPi0(int n){ m_tau_nPi0 = n; }
  void Set_match_vis_tau(bool b){ m_tau_match_vis_tau = b; }
  void Set_match_vis_tau_object(SuperTau &tau){ self = &tau; }
  void Set_JetBDTSig(bool l, bool m, bool t){ m_tau_JetBDTSigLoose = l; m_tau_JetBDTSigMedium = m; m_tau_JetBDTSigTight = t; }
  void Set_JetBDTSigScore(double x){m_tau_JetBDTSigScore = x;}

 public:
  TLorentzVector hlv() const {
    return  hlv("reco");
  }
  TLorentzVector hlv(const std::string &type) const {
    if(type == "reco") return  m_reco_hlv;
    else if(type == "true") return  m_true_hlv;
    else if(type == "truevis") return  m_truevis_hlv;
    else{ cerr<<"Unknown hlv type, returning empty vector"<<endl; }

    return TLorentzVector(0,0,0,0);
  }

  double GetKin( const std::string &var){
    return GetKin("reco", var);
  }

  double GetKin(const std::string &type, const std::string &var){
    if(var=="pt") return hlv(type).Pt();
    else if(var=="eta") return hlv(type).Eta();
    else if(var=="phi") return hlv(type).Phi();
    else if(var=="et") return hlv(type).Et();
    else if(var=="p") return hlv(type).P();
    else if(var=="m") return hlv(type).M();
    else if(var=="y") return hlv(type).Rapidity();
    else { cerr<<"SuperTau::GetKin - unknown variable '"<<var<<"'"<<endl;}

    return 0;
  }

  double GetInfo(const std::string &var) const {
    if(var=="q")   return m_tau_charge;
    else if(var=="nTrk") return m_tau_numTrack;
    else if(var=="nProng") return m_tau_nProng;
    else if(var=="nPi0") return m_tau_nPi0;
    else if(var=="author") return m_tau_author;
    else if(var=="index") return m_tau_index;
    else if(var=="mcindex") return m_mc_index;
    else if(var=="truth") return m_tau_match_vis_tau;
    else if(var=="bdtscore") return m_tau_JetBDTSigScore;
    else { cerr<<"SuperTau::GetInfo - unknown variable "<<var<<endl;}

    return 0;
  }
  
  double Get_JetBDTSigScore(){ return m_tau_JetBDTSigScore;}

  bool Get_JetBDTSig(const string &type){
    if(type == "loose") 
      return m_tau_JetBDTSigLoose;
    else if(type == "medium") 
      return m_tau_JetBDTSigMedium;
    else if(type == "tight") 
      return m_tau_JetBDTSigTight;
    else{
      cerr<<"SuperTau::Get_JetBDTSig - "<<type<<" unknown"<<endl;
    }

    return false;
  }

  string Get_Max_JetBDTSig(){
    if(Get_JetBDTSig("tight")) return "tight";
    if(Get_JetBDTSig("medium")) return "medium";
    if(Get_JetBDTSig("loose")) return "loose";

    return "none";
  }
  
  SuperTau GetTrueVis(){ return *self; }

  double IsTrue(){ return m_tau_match_vis_tau;}

 private:
  TLorentzVector m_reco_hlv;
  TLorentzVector m_true_hlv;
  TLorentzVector m_truevis_hlv;

  double m_tau_JetBDTSigScore;
  int m_tau_index;
  int m_mc_index;
  int m_tau_charge;
  int m_tau_author;
  int m_tau_numTrack;
  int m_tau_nProng;
  int m_tau_nPi0;
  bool m_tau_match_vis_tau;
  bool m_tau_JetBDTSigLoose; 
  bool m_tau_JetBDTSigMedium; 
  bool m_tau_JetBDTSigTight;


 public:
  ClassDef(SuperTau, 0)

};

//class HyperTau : SuperTau {};
#endif
