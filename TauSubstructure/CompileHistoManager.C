{

  gSystem->AddIncludePath( " -IHistoManager/");
  //gSystem->CompileMacro( "HistoManager/HistoManager.cxx","gk" );

  gROOT->ProcessLine(".L HistoManager/HistoManager.cxx+"); 
  
  gROOT->ProcessLine(".q");
}
