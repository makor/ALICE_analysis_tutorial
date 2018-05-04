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
  AliV0ReaderV1* fV0Reader;     //! basic photon Selection Task
  TString fV0ReaderName;        //
  TClonesArray* fReaderGammas;  //!
  std::vector<AliAODTrack*> fGlobalTrackReference;  //!
  TList* fOutputList;                               //! output list
  TH1F* fHistPt;                                    //! dummy histogram
  TH1F* fHistPtvertexZ;                             //!
  TH1F* fHistPtcentrality;                          //!
  TH2F* fHistPt2D;                                  //!
  TH2F* fHistTPC;                                   //!
  TH2F* fHistTOF;                                   //!
  TH2F* fHistBeta;                                  //!
  AliPIDResponse* fPIDResponse;                     //!
  TH1F* fHistPionPt;                                //!
  TH1F* fHistPionPsdRap;                            //!
  TH1F* fHistPionAzi;                               //!
  TH1F* fHistSigSelectedProtonP;                    //!
  TH1F* fHist3SigSelectedProtonP;                   //!
  TH1F* fHistSigSelectedElectronP;                  //!
  TH1F* fHist3SigSelectedElectronP;                 //!
  TH1F* fHistSigSelectedPionP;                      //!
  TH1F* fHist3SigSelectedPionP;                     //!
  TH1F* fHistSigSelectedKaonP;                      //!
  TH1F* fHist3SigSelectedKaonP;                     //!
  TH1F* fHistV0mcPhotonPt;                          //!
  TH1F* fHistmcDaug1Pt;                             //!
  TH1F* fHist2mcDaug1Pt;                            //!
  TH1F* fHistmcDaug2Pt;                             //!
  TH1F* fHist2mcDaug2Pt;                            //!
  TH1F* fHistV0LambdaInvMass;                       //!
  TH1F* fHistV0AntiLambdaInvMass;                   //!
  TH1F* fHistmcDaugPt;                              //!
  TH1F* fHist2mcDaugPt;                             //!
  TH1F* fHist2V0mcPhotonPt;                         //!
  TH1F* fHist2ArmenterosPodolandskiV0mcPhotons;     //!
  TH1F* fHistV0Pt;                                  //!
  TH1F* fHistV0K0ShortInvMass;                      //!
  TH2F* fHistClsDistrPosTr;                         //!
  TH2F* fHistClsDistrNegTr;                         //!
  TH2F* fHistPTPCPion;                              //!
  TH2F* fHistPTOFPion;                              //!
  TH2F* fHistPTPCKaon;                              //!
  TH2F* fHistPTOFKaon;                              //!
  TH2F* fHistPTPC3SigKaon;                          //!
  TH2F* fHistPTOF3SigKaon;                          //!
  TH2F* fHistPTPCProton;                            //!
  TH2F* fHistPTOFProton;                            //!
  TH2F* fHistPTPCElectron;                          //!
  TH2F* fHistPTOFElectron;                          //!
  TH2F* fHistPTPCPion2;                             //!
  TH2F* fHistPTOFPion2;                             //!
  TH2F* fHistPBetaTOFPion;                          //!
  TH2F* fHistPBetaTPCPion;                          //!
  TH2F* fHistPBetaProton;                           //!
  TH2F* fHistPBetaElectron;                         //!
  TH2F* fHistPBetaKaon;                             //!
  TH2F* fHistPBetaPion;                             //!
  TH2F* fHistNSigTOFPion;                           //!
  TH2F* fHistNSigTPCPion;                           //!
  TH2F* fHistNSigTOFKaon;                           //!
  TH2F* fHistNSigTPCKaon;                           //!
  TH2F* fHistNSigTOFProton;                         //!
  TH2F* fHistNSigTPCProton;                         //!
  TH2F* fHistNSigTOFElectron;                       //!
  TH2F* fHistNSigTPCElectron;                       //!
  TH2F* fHistNSigAddProton;                         //!
  TH2F* fHistNSigAddElectron;                       //!
  TH2F* fHistNSigAddPion;                           //!
  TH2F* fHistNSigAddKaon;                           //!
  // TH2F*			TEST;
  Bool_t fIsMC;
  TH1F* fHistPKaon;  //!
  // TH1F*			fHistSum_PKaon;
  TH1F* fHistMCall;                  //!
  TH1F* fHistAllSpeciesKaon;         //!
  TH1F* fHistPureKaon;               //!
  TH1F* fHistAllPureKaon;            //!
  TH1F* fHistPhotonPt;               //!
  TH2F* fHistArmenterosPodolandski;  //!
  TH2F* fHistArmenterosPodolandskiV0mcPhotons;  //!

  AliAnalysisTaskMyTask(const AliAnalysisTaskMyTask&);  // not implemented
  AliAnalysisTaskMyTask& operator=(
      const AliAnalysisTaskMyTask&);  // not implemented

  ClassDef(AliAnalysisTaskMyTask, 1);
};

#endif
