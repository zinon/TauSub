
void NormalizeMaxBin(TH1 *);

TCanvas *GetCanvas();

void Graphics(const string &folder, const string &name, TH1*h);
void Graphics(const string &folder, const string &name, TH1*h, TH1*g);



void Plot(){

  bool kOverlay = false; 
  string over1="tau_pan_incl_reso_rel"; string over2="tau_rec_incl_reso_rel";
  //string over1="tau_pan_incl_reso_log"; string over2="tau_rec_incl_reso_log";

  bool kMulti = true;

  string outputdir = "plots/5_2_2014/";

  string folder = "results/user.zenon.TauPi0Rec_D3PD.147818.Pythia8_AU2CTEQ6L1_Ztautau.recon.ESD.e1176_s1479_s1470_r3553_tid00999076_00.v06-00.v2.140204165017/";
  string file = "tau4mom.root";

  TFile *f = new TFile((folder+file).c_str(), "read");

  if(!f) { cout<<"file not found, exiting..."<<endl; return;}



  //TH1D *h = f->Get("tau_pan_incl_reso_log"); NormalizeMaxBin(h); TCanvas *c = GetCanvas(); c->cd(); h->Draw(); return;
  //TH2D *h = f->Get("tau_pan_1p0n_pt_reco_vs_pt_true");  TCanvas *c = GetCanvas(); c->cd(); h->SetMarkerColor(kAzure); h->SetMarkerSize(0.5); h->Draw(); return;

  if(kOverlay){
    TCanvas *c = GetCanvas(); c->cd();
    TH1D *h1 = f->Get(over1.c_str()); NormalizeMaxBin(h1);
    TH1D *h2 = f->Get(over2.c_str()); NormalizeMaxBin(h2); h2->SetLineColor(kMagenta);
    const char *hname1 = h1->GetName(); string hname1_str(hname1);
    const char *hname2 = h2->GetName(); string hname2_str(hname2);
    string hname = hname1_str +"_vs_"+hname2_str;
    Graphics(outputdir, hname, h1, h2);
  }

  if(kMulti){
    TIter next(f->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next())) {
      const char* cname = key->GetClassName();
      string cname_str(cname);

      TClass *cl = gROOT->GetClass(cname);
      if (cl->InheritsFrom("TH1") && cname_str == "TH1D" ){
        TH1 *h1 = (TH1*)key->ReadObj();
        const char *hname = h1->GetName();
        string hname_str(hname);
        cout<<"TH1 : "<<hname_str<<" "<<endl;
        NormalizeUnitArea(h1);
        Graphics(outputdir, hname_str, h1);

      } else if (cl->InheritsFrom("TH2") && cname_str == "TH2D"){
        TH2 *h2 = (TH2*)key->ReadObj();
        const char *hname = h2->GetName();
        string hname_str(hname);
        cout<<"TH2 : "<<hname_str<<" "<<endl;
        h2->SetMarkerColor(kAzure); h2->SetMarkerSize(0.5);
        Graphics(outputdir, hname_str, h2);

      }else{
        //
      }
    }
  }//

}

void Graphics(const string &folder, const string &name, TH1*h){

  Graphics(folder, name, h, 0);
}
void Graphics(const string &folder, const string &name, TH1*h, TH1*g){

  TCanvas *c = GetCanvas(); c->cd();
  h->Draw();
  if(g) g->Draw("same");
  c->SaveAs( (folder+name+".eps").c_str() );
  delete c;
}

TCanvas *GetCanvas(){


  TCanvas *c = new TCanvas("c", "",10,50,700,500);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetRightMargin(0.025);
  c->SetTopMargin(0.04);
  c->SetFrameBorderMode(0);
  c->SetFrameBorderMode(0);


  return c;

}

void NormalizeMaxBin(TH1 *h){

  h->Scale( 1./h->GetBinContent(h->GetMaximumBin()) );
}

void NormalizeUnitArea(TH1 *h){

  h->Scale( 1./h->Integral() );
}
