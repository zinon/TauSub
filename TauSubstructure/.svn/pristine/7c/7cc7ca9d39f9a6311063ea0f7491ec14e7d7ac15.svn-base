#!/usr/bin/python

import os, shutil
from time import gmtime, strftime

def Typical():
  return """
void TauSubstructureViewer::Loop()
{
}
"""
def User():
  return """
void TauSubstructureViewer::Analyze(int ievent){

}
"""

def Main():
  return """
void TauSubstructureViewer::LoadBranches(int jentry){


}

void TauSubstructureViewer::Loop()
{
  if(!fChain) { cerr<<"TauSubstructureViewer::Loop - Null chain. Exiting..."<<endl; return;}

  int nentries = fChain->GetEntries();

  if(!nentries) { cerr<<"TauSubstructureViewer::Loop - No entries. Exiting..."<<endl; return;}

  cout<<"TauSubstructureViewer::Loop - entries "<<nentries<<endl;

  for(int jentry = 0; jentry < nentries; jentry++){
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    //load branches
    LoadBranches(ientry);

    //actual analysis code
    Analyze(jentry);
  }

}
"""

def Other():
  return """
Bool_t TauSubstructureViewer::Notify()
{
   return kTRUE;
}

void TauSubstructureViewer::Show(Long64_t entry)
{
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t TauSubstructureViewer::Cut(Long64_t entry)
{
   return 1;
}

Int_t TauSubstructureViewer::GetEntry(Long64_t entry)
{
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t TauSubstructureViewer::LoadTree(Long64_t entry)
{
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

TauSubstructureViewer::~TauSubstructureViewer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

TauSubstructureViewer::TauSubstructureViewer(TTree *tree)
{
   Init(tree);
}

"""

def More():
  return """
  virtual void Analyze(int ievent);
  void LoadBranches(int jentry);
  //user-def
"""
#-------------------------------------------------------

now = strftime("_%Y_%m_%d_%H_%M_%S", gmtime())
directory = "TauSubstructureViewer"
project = "TauSubstructureViewer"

if not os.path.exists(directory):
  os.makedirs(directory)
else:
  shutil.move(directory, directory+now)
  os.makedirs(directory)


finC = open(os.path.join ( "MakeClass", project+".C"), "r") #http://www.tutorialspoint.com/python/python_files_io.htm
finH = open(os.path.join ( "MakeClass", project+".h"), "r")

foutC = open( os.path.join ( directory, project+".C"), "w" )
foutH = open( os.path.join ( directory, project+".h"), "w" )

#with open(finC) as f:
linesC = finC.readlines()
linesH = finH.readlines()



start = False
for iline in linesH:
  if "#ifndef" in iline:
    start = True
  if start: 
    if iline and not "#include" in iline:
      if "class TauSubstructureViewer" in iline:
        foutH.write("#include \"Headers.h\"\n")
        foutH.write(iline)
      elif "};" in iline:
        #foutH.write( More() )
        foutH.write(iline)
      else:
        foutH.write(iline)
  if  "#endif" in iline:
    foutH.write("")
    break

foutC.write( "#include \"TauSubstructureViewer.h\"\n\n"  )

#foutC.write( User() )

#foutC.write( Main() )

foutC.write( Typical() )

foutC.write( Other() )


start = False
for iline in linesH:
  if (project+"::Init") in iline:
    start = True
  if start: 
    if iline:
      foutC.write(iline)
    if  "}" in iline:
      foutC.write("\n")
      break


  
foutC.close()
foutH.close()
