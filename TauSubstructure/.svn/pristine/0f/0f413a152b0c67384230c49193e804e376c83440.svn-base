{



  //gSystem->AddIncludePath( (" -I"+path+"SimpleTau/").c_str() );
  //gSystem->Load( (path+"SimpleTau/SimpleTau_cpp.so").c_str() );

  gSystem->AddIncludePath( " -I./");
  
  gSystem->AddIncludePath( " -IHistoManager/");
  gSystem->Exec("root -q -b -l CompileHistoManager.C");
  gSystem->Load( "HistoManager/HistoManager_cxx.so" );

  gSystem->AddIncludePath( " -ITauSubstructureViewer/");
  gSystem->Exec("root -q -b -l CompileTauSubstructureViewer.C");
  gSystem->Load( "TauSubstructureViewer/TauSubstructureViewer_C.so" );

  gSystem->AddIncludePath( " -ISmartTrack/");
  gSystem->Exec("root -q -b -l CompileSmartTrack.C");
  gSystem->Load( "SmartTrack/SmartTrack_cpp.so" );

  gSystem->AddIncludePath( " -ISuperTau/");
  gSystem->Exec("root -q -b -l CompileSuperTau.C");
  gSystem->Load( "SuperTau/SuperTau_cpp.so" );
  
  gSystem->AddIncludePath( " -ITauObject_PanTau/");
  gSystem->Exec("root -q -b -l CompileTauObject_PanTau.C");
  gSystem->Load( "TauObject_PanTau/TauObject_PanTau_cxx.so" );

  gSystem->AddIncludePath( " -ITruthTrackMatchingTool-00-00-02/TruthTrackMatchingTool/TruthTrackMatchingTool/");
  gSystem->Exec("source ./CompileTruthTrackMatchingTool.sh");
  gSystem->Load( "TruthTrackMatchingTool-00-00-02/TruthTrackMatchingTool/standalone/libTruthTrackMatchingTool.so");

  gSystem->CompileMacro( "TauMain.cxx", "gk" );
 
  //  gROOT->ProcessLine(".L TaTauSubstructureViewer/uTriggerLogistics.C+");

  gROOT->ProcessLine(".q");

}
