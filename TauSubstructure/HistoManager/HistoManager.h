#ifndef _HISTOMANAGER_
#define _HISTOMANAGER_

#include <iostream>
#include <string>
#include <map>

#include "TH1.h"
#include "TH2.h"

#include "TROOT.h"

class HistoManager {

 public:
  HistoManager();
  ~HistoManager();

 public:
  // name, title, xtitle, ytitle, bins, range 1d
  void AddHisto(const std::string &, const std::string &, const std::string &, const std::string &, int, double, double );

  // name, title, xtitle, ytitle, bins, range 2d
  void AddHisto(const std::string &, const std::string &, const std::string &, const std::string &, int, double, double, int, double, double );

  void AddCutflow(const std::string  &name, int n);

  void FillHisto(const std::string &, double); // x
  void FillHistoW(const std::string &, double, double); //x, w

  void FillHisto(const std::string &, double, double); // x, y
  void FillHistoW(const std::string &, double, double, double); //x, y, w

  void UpdateCutflow(const string&, int);

  void WriteHistos();

  void WeightHistos(double);

  void SetGlobalWeight(double x){ m_global_weight = x; }

 private:
  map<string, TH1 *> m_hmap;
  map<string, TH2 *> m_hmap2;
  map<string, TH1 *> m_hmapCut;

  typedef map<string, TH1 *>::iterator Itr1;
  typedef map<string, TH2 *>::iterator Itr2;

  double m_global_weight;
};

#endif
