{


  //gSystem->Exec("cd SimpleTau/; root -q -b -l CompileSimpleTau.C; ls; cd -");
  //gSystem->AddIncludePath( (" -I"+path+"SimpleTau/").c_str() );
  //gSystem->Load( (path+"SimpleTau/SimpleTau_cpp.so").c_str() );

  gSystem->AddIncludePath( " -I./");
  gSystem->CompileMacro( "TauSubstructureViewer/TauSubstructureViewer.C","gk" );
 
  //  gROOT->ProcessLine(".L TauTriggerLogistics.C+");
  gROOT->ProcessLine(".q");

}
