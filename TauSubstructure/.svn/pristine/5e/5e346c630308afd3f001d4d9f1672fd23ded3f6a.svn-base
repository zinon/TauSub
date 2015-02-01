{

  gSystem->AddIncludePath( " -I./");
  
  gSystem->AddIncludePath( " -IHistoManager/");
  gSystem->Load( "HistoManager/HistoManager_cxx.so" );

  gSystem->AddIncludePath( " -ITauSubstructureViewer/");
  gSystem->Load( "TauSubstructureViewer/TauSubstructureViewer_C.so" );

  gSystem->AddIncludePath( " -ISuperTau/");
  gSystem->Load( "SuperTau/SuperTau_cpp.so" );
  
  gSystem->AddIncludePath( " -ISmartTrack/");
  gSystem->Load( "SmartTrack/SmartTrack_cpp.so" );

  gSystem->AddIncludePath( " -ITauObject_PanTau/");
  gSystem->Load( "TauObject_PanTau/TauObject_PanTau_cxx.so" );

  gSystem->AddIncludePath( " -ITruthTrackMatchingTool-00-00-02/TruthTrackMatchingTool/TruthTrackMatchingTool/");
  gSystem->Load( "TruthTrackMatchingTool-00-00-02/TruthTrackMatchingTool/standalone/libTruthTrackMatchingTool.so");
  
  gSystem->CompileMacro( "TauMain.cxx", "gk" );
 
  //  gROOT->ProcessLine(".L +");
  gROOT->ProcessLine(".q");

}
