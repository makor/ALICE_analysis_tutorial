/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskMyTask_H
#define AliAnalysisTaskMyTask_H
#include <vector>
#include "AliAnalysisTaskSE.h"
#include "AliEventCuts.h"
#include "AliPIDResponse.h"
#include "AliV0ReaderV1.h"

class AliAnalysisTaskMyTask : public AliAnalysisTaskSE {
 public:
  AliAnalysisTaskMyTask();
  AliAnalysisTaskMyTask(const char* name);
  virtual ~AliAnalysisTaskMyTask();

  virtual void UserCreateOutputObjects();
  virtual void UserExec(Option_t* option);
  virtual void Terminate(Option_t* option);
  float GetBeta(AliAODTrack* track);
  void StoreGlobalTrackReference();
  void SetIsMC(Bool_t IsMC) { fIsMC = IsMC; };
  void SetV0ReaderName(TString name) { fV0ReaderName = name; }

  AliEventCuts fEventCuts;

 private:
  AliAODEvent* fAOD;            //! input event
  AliMCEvent* fMCEvent;         //! input MC event
  AliV0ReaderV1* fV0Reader;     //! basic photon Selection Task
  TString fV0ReaderName;        //
  TClonesArray* fReaderGammas;  //!
  std::vector<AliAODTrack*> fGlobalTrackReference;  //!
  TList* fOutputList;                               //! output list
  AliPIDResponse* fPIDResponse;                     //!
  TH1F* fHistPionPt;                                //!
  TH1F* fHistAllPhotons;                            //!
  TH1F* fHistV0mcPhotonPtandArmCut;                          //!
  TH1F* fHistmcDaug1Pt;                             //!
  TH1F* fHistDetAccmcDaug1Pt;                            //!
  TH1F* fHistmcDaug2Pt;                             //!
  TH1F* fHistDetAccmcDaug2Pt;                            //!
  TH1F* fHistV0LambdaInvMass;                       //!
  TH1F* fHistV0AntiLambdaInvMass;                   //!
  TH1F* fHistmcDaugPt;                              //!
  TH1F* fHist2mcDaugPt;                             //!
  TH1F* fHistV0PhotonCandPt;                            //!
  TH1F* fHistV0mcPhotonPtCut;                       //!
  TH2F* fHistArmenterosPodolandskiV0mcPhotonsCut;   //!
  TH1F* fHist2V0mcPhotonPt;                         //!
  TH2F* fHist2ArmenterosPodolandskiV0mcPhotons;     //!
  TH2F* fHistArmenterosPodolandskiArmCut;            //!
  TH1F* fHistV0Pt;                                  //!
  TH1F* fHistReconstrmcPhotonPt;                     //!
  TH1F* fHistV0K0ShortInvMass;                      //!
  TH2F* fHistClsDistrPosTr;                         //!
  TH2F* fHistClsDistrNegTr;                         //!
  Bool_t fIsMC;
  float fpTCut;
  TH1F* fHistPhotonPt;               //!
  TH2F* fHistArmenterosPodolandski;  //!
  TH2F* fHistArmenterosPodolandskiV0mcPhotons;  //!

  AliAnalysisTaskMyTask(const AliAnalysisTaskMyTask&);  // not implemented
  AliAnalysisTaskMyTask& operator=(
      const AliAnalysisTaskMyTask&);  // not implemented

  ClassDef(AliAnalysisTaskMyTask, 1);
};

#endif
