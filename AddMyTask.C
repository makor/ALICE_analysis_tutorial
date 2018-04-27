
#if !defined(__CINT__) || defined(__CLING__)
#include <TList.h>
#include <TString.h>
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskMyTask.h"
#endif

AliAnalysisTaskMyTask* AddMyTask(TString name = "name", Bool_t IsMC = kFALSE) {
  // get the manager via the static access member. since it's static, you don't
  // need
  // an instance of the class to call the function
  AliAnalysisManager* mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    return 0x0;
  }
  // get the input event handler, again via a static method.
  // this handler is part of the managing system and feeds events
  // to your task
  if (!mgr->GetInputEventHandler()) {
    return 0x0;
  }
  // by default, a file is open for writing. here, we get the filename
  TString fileName = AliAnalysisManager::GetCommonFileName();
  fileName += ":MyTask";  // create a subfolder in the file

  //=========  Set Cutnumber for V0Reader ================================
  TString cutnumberPhoton = "00200008400020002282000000";
  TString cutnumberEvent = "00000003";
  TString periodNameV0Reader = "";
  Bool_t enableV0findingEffi = kFALSE;
  Bool_t runLightOutput = kFALSE;
  TString cutnumberAODBranch = "00000003_06000008400100001000000000";

  //========= Add V0 Reader to  ANALYSIS manager if not yet existent =====
  TString V0ReaderName =
      Form("V0ReaderV1_%s_%s", cutnumberEvent.Data(), cutnumberPhoton.Data());
  AliConvEventCuts *fEventCuts = nullptr;

  if (!(AliV0ReaderV1 *)mgr->GetTask(V0ReaderName.Data())) {
    AliV0ReaderV1 *fV0ReaderV1 = new AliV0ReaderV1(V0ReaderName.Data());
    if (periodNameV0Reader.CompareTo("") != 0)
      fV0ReaderV1->SetPeriodName(periodNameV0Reader);
    fV0ReaderV1->SetUseOwnXYZCalculation(kTRUE);
    fV0ReaderV1->SetCreateAODs(kFALSE);  // AOD Output
    fV0ReaderV1->SetUseAODConversionPhoton(kTRUE);
    fV0ReaderV1->SetProduceV0FindingEfficiency(enableV0findingEffi);

    if (!mgr) {
      Error("AddTask_V0ReaderV1", "No analysis manager found.");
      return nullptr;
    }

    if (cutnumberEvent != "") {
      fEventCuts =
          new AliConvEventCuts(cutnumberEvent.Data(), cutnumberEvent.Data());
      fEventCuts->SetPreSelectionCutFlag(kTRUE);
      fEventCuts->SetV0ReaderName(V0ReaderName);
      if (periodNameV0Reader.CompareTo("") != 0)
        fEventCuts->SetPeriodEnum(periodNameV0Reader);
      fV0ReaderV1->SetEventCuts(fEventCuts);
    }

    // Set AnalysisCut Number
    AliConversionPhotonCuts *fCuts = NULL;
    if (cutnumberPhoton != "") {
      fCuts = new AliConversionPhotonCuts(cutnumberPhoton.Data(),
                                          cutnumberPhoton.Data());
      fCuts->SetPreSelectionCutFlag(kTRUE);
      fCuts->SetIsHeavyIon(kFALSE);
      fCuts->SetV0ReaderName(V0ReaderName);
      fCuts->SetLightOutput(runLightOutput);
      if (fCuts->InitializeCutsFromCutString(cutnumberPhoton.Data())) {
        fV0ReaderV1->SetConversionCuts(fCuts);
        fCuts->SetFillCutHistograms("", kTRUE);
      }
    }

    if (mgr->GetCommonInputContainer()->IsA() == AliAODInputHandler::Class()) {
      fV0ReaderV1->SetDeltaAODBranchName(
          Form("GammaConv_%s_gamma", cutnumberAODBranch.Data()));
    }

    fV0ReaderV1->Init();

    AliLog::SetGlobalLogLevel(AliLog::kFatal);

    // connect input V0Reader
    mgr->AddTask(fV0ReaderV1);
    mgr->ConnectInput(fV0ReaderV1, 0, mgr->GetCommonInputContainer());
  }

  // now we create an instance of your task
  AliAnalysisTaskMyTask* task = new AliAnalysisTaskMyTask(name.Data());
  if (!task) return 0x0;
  task->SelectCollisionCandidates(AliVEvent::kINT7); // select minimum bias trigger
  task->SetV0ReaderName(V0ReaderName.Data());
  task->SetIsMC(IsMC);
  // add your task to the manager
  mgr->AddTask(task);
  // your task needs input: here we connect the manager to your task
  mgr->ConnectInput(task, 0, mgr->GetCommonInputContainer());
  // same for the output
  mgr->ConnectOutput(task, 1,
                     mgr->CreateContainer("MyOutputContainer", TList::Class(),
                                          AliAnalysisManager::kOutputContainer,
                                          fileName.Data()));
  // in the end, this macro returns a pointer to your task. this will be
  // convenient later on
  // when you will run your analysis in an analysis train on grid
  return task;
}
