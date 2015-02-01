{
  gSystem->AddIncludePath( " -I./");
  gSystem->AddIncludePath( " -ITauObject_PanTau/");
  gSystem->CompileMacro( "TauObject_PanTau/TauObject_PanTau.cxx","gk" );
 
  gROOT->ProcessLine(".q");

}
