#include "HistoManager.h"

HistoManager::HistoManager() : m_global_weight(1)
{
  m_hmap.clear();

}

HistoManager::~HistoManager(){

}
void HistoManager::AddCutflow(const std::string  &name, int n){

  m_hmapCut[name] = new TH1D( name.c_str(), "", n, -0.5, n-0.5);

}

void HistoManager::AddHisto(const std::string  &name, const std::string &title, const std::string  &xtitle, const std::string  &ytitle, int n, double x0, double x1){
  // name, title, xtitle, ytitle, bins, range

  m_hmap[name] = new TH1D( name.c_str(), title.c_str(), n, x0, x1);
  if( xtitle.size() ) m_hmap[name]->GetXaxis()->SetTitle(xtitle.c_str());
  if( ytitle.size() ) m_hmap[name]->GetYaxis()->SetTitle(ytitle.c_str());
}

void HistoManager::AddHisto(const std::string  &name, const std::string &title, const std::string  &xtitle, const std::string  &ytitle, int nx, double x0, double x1, int ny, double y0, double y1){
  // name, title, xtitle, ytitle, bins, range 2d

  m_hmap2[name] = new TH2D( name.c_str(), title.c_str(), nx, x0, x1, ny, y0, y1);
  if( xtitle.size() ) m_hmap2[name]->GetXaxis()->SetTitle(xtitle.c_str());
  if( ytitle.size() ) m_hmap2[name]->GetYaxis()->SetTitle(ytitle.c_str());
}

void HistoManager::FillHisto(const std::string   &name, double x){

  FillHistoW(name, x, 1. * m_global_weight);

}

void HistoManager::FillHistoW(const std::string   &name, double x, double w){

  if ( m_hmap.find(name) == m_hmap.end() ) {
    cerr<< "HistoManager::FillHistoW - key "<<name << " not found "<<endl;
  } else {
    m_hmap[name]->Fill(x, w);
  }

}

void HistoManager::FillHisto(const std::string   &name, double x, double y){

  FillHistoW(name, x, y, 1. * m_global_weight );

}

void HistoManager::FillHistoW(const std::string   &name, double x, double y, double w){

  if ( m_hmap2.find(name) == m_hmap2.end() ) {
    cerr<< "HistoManager::FillHistoW - key "<<name << " not found "<<endl;
  } else {
    m_hmap2[name]->Fill(x, y, w);
  }

}

void HistoManager::UpdateCutflow(const std::string   &name, int entry){

  if ( m_hmapCut.find(name) == m_hmapCut.end() ) {
    cerr<< "HistoManager::UpdateCutflow - key "<<name << " not found "<<endl;
  } else {
    m_hmapCut[name]->Fill(entry, 1);
  }

}

void HistoManager::WriteHistos(){
  
  int i(0);

  if (m_hmap.size() ){
    for( Itr1 it = m_hmap.begin(); it != m_hmap.end(); it++){
      if( it->second->GetEntries() > 0 ){ (*it).second->Write(); i++; }
    }
    cout<<"     HistoManager::WriteHistos() - "<<i<<" 1d histograms stored."<<endl;
  }else{
    cout<<"     HistoManager::WriteHistos() - no 1d histograms stored."<<endl;
  }

  i = 0;
  if (m_hmap2.size() ){
    for( Itr2 it = m_hmap2.begin(); it != m_hmap2.end(); it++){
      if( it->second->GetEntries() > 0 ){ (*it).second->Write(); i++;}
    }
    cout<<"     HistoManager::WriteHistos() - "<<i<<" 2d histograms stored."<<endl;
  }else{
    cout<<"     HistoManager::WriteHistos() - no 2d histograms stored."<<endl;
  }

  i = 0;
  if (m_hmapCut.size() ){
    for( Itr1 it = m_hmapCut.begin(); it != m_hmapCut.end(); it++){
      if( it->second->GetEntries() > 0 ){ (*it).second->Write(); i++;}
    }
    cout<<"     HistoManager::WriteHistos() - "<<i<<"cutflow histograms stored."<<endl;
  }else{
    cout<<"     HistoManager::WriteHistos() - no cutflow histograms stored."<<endl;
  }

}

void HistoManager::WeightHistos(double w){
  
  cout<<"     HistoManager::WriteHistos() - scaling using weight "<<w<<endl;

  int i(0);

  if (m_hmap.size() ){
    for( Itr1 it = m_hmap.begin(); it != m_hmap.end(); it++){
      if( it->second->GetEntries() ){ (*it).second->Scale(w); i++; }
    }
    cout<<"     HistoManager::WriteHistos() - "<<i<<" 1d histograms scaled."<<endl;
  }else{
    cout<<"     HistoManager::WriteHistos() - no 1d histograms scaled."<<endl;
  }

  i = 0;
  if (m_hmap2.size() ){
    for( Itr2 it = m_hmap2.begin(); it != m_hmap2.end(); it++){
      if( it->second->GetEntries() ){ (*it).second->Scale(w); i++;}
    }
    cout<<"     HistoManager::WriteHistos() - "<<i<<" 2d histograms scaled."<<endl;
  }else{
    cout<<"     HistoManager::WriteHistos() - no 2d histograms scaled."<<endl;
  }

}
