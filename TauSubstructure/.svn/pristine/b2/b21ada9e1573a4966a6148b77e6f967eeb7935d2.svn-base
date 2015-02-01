=================================================
Tau-substructure four-momentum resolution studies
=================================================

:authors: Zinonas Zinonos, ...
:contact: zenon@cern.ch, ...


------------
Introduction
------------

This code is designed to study the four-momentum resolution for taus using substructure information. The basic goal is to better understand and reduce the tails from the current substructure-based 4-momentum calculation. There is already a basic understanding as to the origin of the tails, and some ideas to reduce them. These are detailed in Peter's talk (linked on the Epic - https://its.cern.ch/jira/browse/ATLTAU-58 ). Datasets including the output of the new substructure algorithms have been produced in private production. Details of the samples can be found here: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TauSubstructureDatasets . Some details on the substructure reconstruction itself can be found here https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TauSubstructure , however, the details on the individual algorithms are still under construction. For now please contact the authors regarding accessing the substructure information from the D3PDs, and calculating the 4-momentum (just send one email including them all):

1. Cell-based: Benedict Winter

2. eflowRec: Mark Hodgkinson

3. PanTau: Christian Limbach

In order to build the 4-momentum from substructure components, a PanTau wrapper class is used https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/PanTau. This code basically produces resolution plots for different tau decay modes.
(eg. from our plot book). Just focus on ET resolution for now, and make the true, reco and true=reco mode plots.
The resolution in the different modes is examined and in order to identify large tails. The cause of the large tails is investigated aiming to come up with a method to reduce the tails.


-----
Setup
-----

The proper environent to built the package can be sourced::

	source setup.sh

This ensures that all shared libraries are compiled using the same ROOT version when running locally or on the Grid.

---------
Compiling
---------

To compile everything you need to call:

	root Compile.C

which simply links and compiles all individual classes, and creates the corresponding dynamic shared libraries.

To compile a specific class (when you modify something in the code) you have to run the script corresponding to that class::

	root CompileHistoManager.C  

or::

	root CompileSmartTrack.C  

or::

	root CompileSuperTau.C

or::

	root CompileTauMain.C  

or::

	root CompileTauObject_PanTau.C  

or::

	root CompileTauSubstructureViewer.C

Usually, changes occur in the 'TauMain' class and so runnning::

	root root CompileTauMain.C

is just sufficient.

------
Runing
------

To run on your local machine, you only need to source::

	source RunAnalysis.sh

which is responsible to create (if necessary) and wrap all dynamic shared libraries together, read the input datasets file 'inputfiles.txt' and launch the 'RunGrid.C' main script. The latter contains an instance of the 'TauMain' class with job options set. It's necessary to review all job options before submitting general jobs on the grid.


-----------------------
Defining new histograms
-----------------------

To book, fill and store a  histogram you don't need to do so much. The 'HistoManager' class is doing most of the job. 1D and 2D histograms can be easily declared in the 'TauMain.cxx' source file and in more specifically here::

	void TauMain::BookTemplate(const std::string &algo ){
	
	//..
	
	m_HM.AddHisto("tau_"+algo+"_incl_reso_rel", "", t_res_rel, "", n_res_rel, l_res_rel, r_res_rel);
	

and filled in the main event loop function::

	void TauMain::Looper(){
	
	if(!fChain) { cerr<<"TauMain::Looper - Null chain. Exiting..."<<endl; return;}
	//...
	//plotting
	m_HM.FillHisto( "tau_pan_incl_reso_rel", RelReso );

---------------------------
Submitting jobs to the grid
---------------------------

Create your grid proxy as usual::

	voms-proxy-init -voms atlas

and then setup prun::

	localSetupPandaClient --noAthenaCheck

The prun script reads a list of input datasets linked to the file "datasets" which can be updated as follows::

	. PrepareDatasets.sh > datasets

Datasets are listed in the textfile "datasets.grid.txt". Finally, to send jobs to the grid, you only need to run::

	. grid.sh

which runs succesfully under normal circumstances.

--------
Plotting
--------

Once you get your prun output succesfully downloaded in your working area, you need to change your directory to "Ploting". Link the merged root file to "thisfile.root". To produce generic and fast resolution plots, a good starting point is to use the super general plotting code::

	[].L Plot_Resolution.C+
	[]Plot_Resolution("<will pick up the thisfile.root if left empty>", <plot id integer number>, "<out put directory name>")

which will create and save a histogram in the directory specified in the function arguments shown above. More specific plotting details are included in the "common.C" code, which is the core program. Other plotting codes are also available.

