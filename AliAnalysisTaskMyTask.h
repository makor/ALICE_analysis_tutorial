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
  Bool_t IsConvertedPhoton(AliAODMCParticle* posDaughter,
                           AliAODMCParticle* negDaughter, AliMCEvent* fMCEvent);
  Bool_t IsConversionPrimaryAOD(AliVEvent* event,
                                AliAODMCParticle* AODMCParticle,
                                Double_t prodVtxX, Double_t prodVtxY,
                                Double_t prodVtxZ);
  void Sigma0Descendancy(AliAODMCParticle* posDaughter);
  void StoreGlobalTrackReference();
  void SetIsMC(Bool_t IsMC) { fIsMC = IsMC; };
  void SetV0ReaderName(TString name) { fV0ReaderName = name; }

  AliEventCuts fEventCuts2;

 private:
  AliAODEvent* fAOD;            //! input event
  AliMCEvent* fMCEvent;         //! input MC event
  AliV0ReaderV1* fV0Reader;     //! basic photon Selection Task
  TString fV0ReaderName;        //
  TClonesArray* fReaderGammas;  //!
  std::vector<AliAODTrack*> fGlobalTrackReference;  //!
  TList* fOutputList;                               //! output list
  AliPIDResponse* fPIDResponse;                     //!
  TH1F* fHistAllPhotons;                            //!
  TH1F* fHistV0mcPhotonPtandArmCut;                 //!
  TH1F* fHistmcDaug1Pt;                             //!

  TH1F* fHistmcDaug2Pt;  //!

  TH1F* fHistV0LambdaInvMass;      //!
  TH1F* fHistV0AntiLambdaInvMass;  //!
  TH1F* fHistV0PhotonCandPt;       //!

  TH2F* fHistArmenterosPodolandskiV0mcPhotonsCut;  //!
  TH2F* fHistArmenterosPodolandskiArmCut;          //!
  TH1F* fHistV0Pt;                                 //!
  TH1F* fHistKindOfCand;                           //!
  TH1F* fHistKindOfPrim;                           //!
  TH1F* fHistSigma0Phi;                            //!
  TH1F* fHistSigma0Theta;                          //!
  TH1F* fHistSigma0Eta;                            //!
  TH1F* fHistSigma0Pt;                             //!
  TH1F* fHistSigma0P;                              //!
  TH1F* fHistSigma0E;                              //!
  TH1F* fHistSigma0Mass2;                          //!
  TH1F* fHistSigma0Tv;                             //!
  TH1F* fHistSigma0OneOverPt;
  TH1F* fHistNoSigma0Phi;         //!
  TH1F* fHistNoSigma0Theta;       //!
  TH1F* fHistNoSigma0Eta;         //!
  TH1F* fHistNoSigma0Pt;          //!
  TH1F* fHistNoSigma0P;           //!
  TH1F* fHistNoSigma0E;           //!
  TH1F* fHistNoSigma0Mass2;       //!
  TH1F* fHistNoSigma0Tv;          //!
  TH1F* fHistNoSigma0OneOverPt;   //!
  TH1F* fHistReconstrmcPhotonPt;  //!
  TH1F* fHistV0K0ShortInvMass;    //!
  TH2F* fHistClsDistrPosTr;       //!
  TH2F* fHistClsDistrNegTr;       //!
  AliConvEventCuts* fEventCuts;   //!
  Bool_t fIsMC;
  const float fpTCut = 0.1;
  const float fECut = 0.001;
  const float fEtaCut = 0.8;
  const float farmQtCut = 0.03;
  const float fCluFindRatCut = 0.8;
  const float fSecProdBoundary = 1.0;
  TH1F* fHistPhotonPt;                          //!
  TH2F* fHistArmenterosPodolandski;             //!
  TH2F* fHistArmenterosPodolandskiV0mcPhotons;  //!

  AliAnalysisTaskMyTask(const AliAnalysisTaskMyTask&);  // not implemented
  AliAnalysisTaskMyTask& operator=(
      const AliAnalysisTaskMyTask&);  // not implemented

  ClassDef(AliAnalysisTaskMyTask, 1);
};

#endif
