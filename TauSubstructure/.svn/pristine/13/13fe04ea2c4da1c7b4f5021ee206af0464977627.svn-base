
void OverlayEtaRegions(){

  TFile *f0 = new TFile("plots/plots_05_03/eta_incl.root");
  TFile *f1 = new TFile("plots/plots_05_03/eta_00_03.root");
  TFile *f2 = new TFile("plots/plots_05_03/eta_03_08.root");
  //plots/plots_05_03/eta_08_12.root
  //plots/plots_05_03/eta_12_21.root
  //plots/plots_05_03/eta_21_25.root

  TH1D *h1 = f1->Get("histo9"); h1->SetFillColor(0);
  TH1D *h2 = f1->Get("histo10"); h2->SetFillColor(0);
  TH1D *h3 = f1->Get("histo11"); h3->SetFillColor(0);

  TH1D *g1 = f2->Get("histo18"); g1->SetFillColor(0); g1->SetLineStyle(7);
  TH1D *g2 = f2->Get("histo19"); g2->SetFillColor(0); g2->SetLineStyle(7);
  TH1D *g3 = f2->Get("histo20"); g3->SetFillColor(0); g3->SetLineStyle(7);

  
  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");

  g1->Draw("same");
  g2->Draw("same");  
  g3->Draw("same");  

  gPad->SetLogy();

}
