
#include <iostream>
#include <string>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TSystem.h"
#include "TROOT.h"

using namespace std;

bool RunGrid(string  inputfile);

string rmSpaces(const string &str);

string GetStringFromInt(int n);


int main(){

  if( RunGrid() ) cout<<"RunGrid: Done!"<<endl;

  return 0;
}

bool RunGrid(string  inputfile){

  cout<<"RungGrid: ROOT "<<gSystem->Exec("which root")<<endl;

  string argStr;
  ifstream ifs(inputfile.c_str());
  getline(ifs,argStr);

  std::vector<std::string> fileList;

  for(size_t i=0,n; i <= argStr.length(); i=n+1){


    n = argStr.find_first_of(',',i);
    if(n == string::npos)
      n = argStr.length();

    string tmp = argStr.substr(i,n-i);
    if (tmp.empty()) continue;

    cout<<"RunGrid: adding file "<<tmp<<endl;
    fileList.push_back(tmp);

  }
  int nfiles = fileList.size();

  cout<<"RunGrid: Files added "<<nfiles<<endl;

  TChain * chain = new TChain("tau");
  if(!chain){cerr<<"RunGrid: Bad chain"<<endl; return false;}

  if(chain->IsZombie()) {cerr<<"RunGrid: Zombie chain"<<endl; return false;}

  if(!nfiles) {cout<<"RunGrid: No files - "<<endl; return true;}

  for (int iFile=0; iFile<fileList.size(); ++iFile) {
    cout << "RunGrid: Opening file ... " << fileList[iFile].c_str() << endl;
    chain->Add(fileList[iFile].c_str());
    //chain->AddFile(fileList[iFile].c_str());
  }

  int nEntries=chain->GetEntries();
  if(!nEntries){cerr<<"RunGrid: No chain entries"<<endl; return false;}

  TTree* tree = (TTree*)chain;
  if(!tree){cerr<<"RunGrid: Bad tree"<<endl; return false;}

  cout<<"RunGrid: Loading libraries ..."<<endl;

  //gSystem->Exec("ls ./*.so;");
  vector<string> v_libraries;
  v_libraries.push_back("HistoManager/HistoManager_cxx.so");
  v_libraries.push_back("TauSubstructureViewer/TauSubstructureViewer_C.so");
  v_libraries.push_back("TauObject_PanTau/TauObject_PanTau_cxx.so");
  v_libraries.push_back("SuperTau/SuperTau_cpp.so");
  v_libraries.push_back("SmartTrack/SmartTrack_cpp.so");
  v_libraries.push_back("TruthTrackMatchingTool-00-00-02/TruthTrackMatchingTool/standalone/libTruthTrackMatchingTool.so");
  v_libraries.push_back("TauMain_cxx.so");

  ///load libraries
  for(vector<string>::iterator ilib = v_libraries.begin(); ilib != v_libraries.end(); ilib++){
    string com = "ls "+(*ilib);
    TString pipe = gSystem->GetFromPipe( com.c_str() );
    if( pipe.IsNull() ){
      cerr<<"RunGrid: Lib "<<*ilib<<" does not exist. Bye bye..."<<endl; return false;
    }else{
      int loaded = gSystem->Load( (*ilib).c_str() );
      if( loaded < 0 ){ //http://root.cern.ch/root/html/TSystem.html#TSystem:Load
        cerr<<"RunGrid: Fail to load library : "<<*ilib<<". Exiting ..."<<endl; return false;
      }else{
        cout<<"RunGrid: Library : "<<*ilib<<" loaded"<<endl;
      }
    }
  }

  cout<<"RunGrid: calling main class ..."<<endl;
  double etaL; double etaR; double ptL; double ptR;

  //etaL = 0.0; etaR = 0.3;
  //etaL = 0.3; etaR = 0.8;
  //etaL = 0.8; etaR = 1.2;
  //etaL = 1.2; etaR = 2.1;
  etaL = 2.1; etaR = 2.55;

  ptL = 20; ptR = 30;

  MemInfo_t memInfo;
  ProcInfo_t procInfo;

  gSystem->GetProcInfo(&procInfo);
  gSystem->GetMemInfo(&memInfo);
  cout << " MEM BEGINNING " << endl;
  cout << " Mem Total = " << memInfo.fMemTotal << endl; 
  cout << " Mem Used = " << memInfo.fMemUsed << endl; 
  cout << " Mem Swapped = " << memInfo.fSwapUsed << endl; 
  cout << " Resident Memory = " << procInfo.fMemResident << endl; 
  cout << " Virtual Memory = " << procInfo.fMemVirtual << endl; 
  Int_t memRes0=procInfo.fMemResident; 
  Int_t memVirt0=procInfo.fMemVirtual; 



  TauMain fun(tree);
  fun.SetOptStudyTauRec(true);
  fun.SetOptMatchToVisTrueTau();
  fun.SetOptMaxRecoTauAbsEta(2.5);
  fun.SetOptMinRecoTauPt(15);
  fun.SetOptMaxNtrks(5);
  //fun.SetOptMinTrueVisTauPt(10);
  //fun.SetOptRecoTauAbsEtaRange(etaL, etaR);
  //fun.SetOptRecoTauPtRange(ptL, ptR);
  fun.SetOptTauParentPDGID(23);
  fun.SetOptPanTauTrkRecoTrkMatchMaxDR(0.01);
  fun.SetOptPanTauTrkRecoTrkMatchMaxRelFracPt(0.01);
  fun.SetOptPanTauTrkRecoTrkMatchClosestDR(true);
  fun.SetOptRecoTauVisTrueTauMatchMaxDR(0.2);
  fun.SetOptRecoTauPanTauMaxDR(0.2);
  //fun.SetOptBuildVisTauTrue("manual"); // calculation: "auto" (tree, default, fast), "manual" (via mc navigation)
  //fun.SetOptBuildVisTauTrueMethod("subtraction"); // when manual: "addition" (visible products), "subtraction" (neutrino)
  fun.SetOptTauJetBDTSig("none"); //none loose medium tight
  fun.SetOptVisTrueTauMatchUseAssocIndex(false);
  fun.SetOptUseOfficialTruthMatching(true);
  fun.SetOptWeightHistos(true);
  fun.SetOptCompatibilityRatioCut("r1p0n_CRcut"); // nocut, r1p0n_CRcut (cut on compatibility ratio), Rcut (cut on R ratio), RWcut (cut on weighted R ratio)
  fun.LoadSetup();
  fun.Looper();
  cout<<"RunGrid: main class finished..."<<endl;



  gSystem->GetProcInfo(&procInfo);
  gSystem->GetMemInfo(&memInfo);
  Int_t memRes1=procInfo.fMemResident; 
  Int_t memVirt1=procInfo.fMemVirtual; 

  cout << " Resident Memory DIFF = " << memRes1-memRes0<< endl; 
  cout << " Virtual Memory DIFF = " << memVirt1-memVirt0 << endl; 
  
  cout << " MEM END " << endl;
  cout << " Mem Total = " << memInfo.fMemTotal << endl; 
  cout << " Mem Used = " << memInfo.fMemUsed << endl; 
  cout << " Mem Swapped = " << memInfo.fSwapUsed << endl; 
  cout << " Resident Memory = " << procInfo.fMemResident << endl; 
  cout << " Virtual Memory = " << procInfo.fMemVirtual << endl; 


  return true;
}

string GetStringFromInt(int n){ std::ostringstream stm; stm << n; return stm.str(); }

string rmSpaces(const string &str){
  string temp;
  for (unsigned int i = 0; i < str.length(); i++)
    if (str[i] != ' ') temp += str[i];

  return temp;
}
