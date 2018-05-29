#if !defined(__CINT__) || defined(__CLING__)
#include "AliAODInputHandler.h"
#include "AliAnalysisAlien.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskMyTask.h"
#endif
void runAnalysis(Bool_t IsMC = kTRUE) {
  // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
  Bool_t local = kFALSE;
  // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
  Bool_t gridTest = kTRUE;

// since we will compile a class, tell root where to look for headers
#if !defined(__CINT__) || defined(__CLING__)
  gInterpreter->ProcessLine(".include $ROOTSYS/include");
  gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
  gROOT->ProcessLine(".include $ROOTSYS/include");
  gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif

  // create the analysis manager
  AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
  AliAODInputHandler *aodH = new AliAODInputHandler();
  mgr->SetInputEventHandler(aodH);

// compile the class and load the add task macro
// here we have to differentiate between using the just-in-time compiler
// from root6, or the interpreter of root5
#if !defined(__CINT__) || defined(__CLING__)
  if (IsMC) {
    AliAnalysisTaskPIDResponse *pidResponse =
        reinterpret_cast<AliAnalysisTaskPIDResponse *>(
            gInterpreter->ExecuteMacro("$ALICE_ROOT/ANALYSIS/macros/"
                                       "AddTaskPIDResponse.C (kTRUE, kTRUE, "
                                       "kTRUE, \"1\")"));
  } else {
    AliAnalysisTaskPIDResponse *pidResponse =
        reinterpret_cast<AliAnalysisTaskPIDResponse *>(
            gInterpreter->ExecuteMacro(
                "$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C"));
  }
  gInterpreter->LoadMacro("AliAnalysisTaskMyTask.cxx++g");
  AliAnalysisTaskMyTask *task = reinterpret_cast<AliAnalysisTaskMyTask *>(
      gInterpreter->ExecuteMacro(Form("AddMyTask.C (\"name\", %i)", IsMC)));
#else
  // gROOT->LoadMacro("/home/mkor/alice/AliRoot/ANALYSIS/macros/AddTaskPIDResponse.C");
  // AddTaskPIDResponse();
  gROOT->LoadMacro("AliAnalysisTaskMyTask.cxx++g");
  gROOT->LoadMacro("AddMyTask.C");
  AliAnalysisTaskMyTask *task = AddMyTask("name", IsMC);
#endif

  if (!mgr->InitAnalysis()) return;
  mgr->SetDebugLevel(2);
  mgr->PrintStatus();
  mgr->SetUseProgressBar(1, 25);

  if (local) {
    // if you want to run locally, we need to define some input
    TChain *chain = new TChain("aodTree");
    // add a few files to the chain (change this so that your local files are
    // added)
    if(IsMC)
    {chain->Add("~/Downloads/MC-259888-121.root");}
    else {
        chain->Add("~/Downloads/AliAOD.root");
        // chain->Add("~/Downloads/full.root");
    }


    // start the analysis locally, reading the events from the tchain
    mgr->StartAnalysis("local", chain);
  } else {
    // if we want to run on grid, we create and configure the plugin
    AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
    // also specify the include (header) paths on grid
    alienHandler->AddIncludePath(
        "-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include "
        "-I$ALICE_PHYSICS/include");
    // make sure your source files get copied to grid
    alienHandler->SetAdditionalLibs(
        "AliAnalysisTaskMyTask.cxx AliAnalysisTaskMyTask.h");
    alienHandler->SetAnalysisSource("AliAnalysisTaskMyTask.cxx");
    // select the aliphysics version. all other packages
    // are LOADED AUTOMATICALLY!
    alienHandler->SetAliPhysicsVersion("vAN-20180330-1");
    // set the Alien API version
    alienHandler->SetAPIVersion("V1.1x");

    // Use Gamma satellites for the photons
    alienHandler->SetFriendChainName("AliAODGammaConversion.root",
                                     "libPWGGAGammaConv.so");
    // select the input data
    if (IsMC) {
      alienHandler->SetGridDataDir("/alice/sim/2017/LHC17d20a2");
      alienHandler->SetDataPattern("/*/AliAOD.root");
    } else {
      alienHandler->SetRunPrefix("000");
      alienHandler->SetGridDataDir("/alice/data/2016/LHC16l");
      alienHandler->SetDataPattern("pass2/AOD/*/AliAOD.root");
    }

    // runnumber
    Int_t runlist[] = {
        259888, 259868, 259867, 259866, 259860, 259842, 259841, 259822, 259789,
        259788, 259781, 259756, 259752, 259751, 259750, 259748, 259747, 259713,
        259711, 259705, 259704, 259703, 259700, 259697, 259668, 259650, 259649,
        259477, 259473, 259396, 259395, 259394, 259389, 259388, 259382, 259378,
        259342, 259341, 259340, 259339, 259336, 259334, 259307, 259305, 259303,
        259302, 259274, 259273, 259272, 259271, 259270, 259269, 259264, 259263,
        259261, 259257, 259204, 259164, 259162, 259118, 259117, 259099, 259096,
        259091, 259090, 259088, 258964, 258962, 258923, 258919};
    for (Int_t i = 0; i < sizeof(runlist); i++) {
      if (i == sizeof(runlist) / sizeof(runlist[1])) break;
      alienHandler->AddRunNumber(runlist[i]);
    }
    // number of files per subjob
    alienHandler->SetNrunsPerMaster(5);
    alienHandler->SetSplitMaxInputFileNumber(20);
    alienHandler->SetExecutable("myTask.sh");
    // specify how many seconds your job may take
    alienHandler->SetTTL(30000);
    alienHandler->SetJDLName("myTask.jdl");

    alienHandler->SetOutputToRunNo(kTRUE);
    alienHandler->SetKeepLogs(kTRUE);
    // merging: run with kTRUE to merge on grid
    // after re-running the jobs in SetRunMode("terminate")
    // (see below) mode, set SetMergeViaJDL(kFALSE)
    // to collect final results
    alienHandler->SetMaxMergeStages(1);
    alienHandler->SetMergeViaJDL(kTRUE);    //normal run
    //alienHandler->SetMergeViaJDL(kFALSE);   //merging run 2.step

    // define the output folders
    alienHandler->SetGridWorkingDir("myWorkingDir7"); //Change Number every run on fullgrid
    alienHandler->SetGridOutputDir("output");

    // connect the alien plugin to the manager
    mgr->SetGridHandler(alienHandler);
    if (gridTest) {
      // speficy on how many files you want to run
      alienHandler->SetNtestFiles(1);
      // and launch the analysis
      alienHandler->SetRunMode("test");
      mgr->StartAnalysis("grid");
    } else {
      // else launch the full grid analysis
      alienHandler->SetRunMode("full");     //normal run
      //alienHandler->SetRunMode("terminate");  // merging run 1.step
      mgr->StartAnalysis("grid");
    }
  }
}
