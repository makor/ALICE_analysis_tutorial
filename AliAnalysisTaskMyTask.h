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
  void IsConvertedPhotonDaughterIsPhysPrimaryCheck(
      AliAODMCParticle* posDaughter, AliAODMCParticle* negDaughter);
  void Sigma0Descendancy(AliAODMCParticle* Daughter);
  void Sigma0Descendancy2(AliAODMCParticle* Daughter2);
  void Sigma0DescendancyAll(AliAODMCParticle* DaughterAll);
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
  TH1F* fHistNoSigma0Phi;                   //!
  TH1F* fHistNoSigma0Theta;                 //!
  TH1F* fHistNoSigma0Eta;                   //!
  TH1F* fHistNoSigma0Pt;                    //!
  TH1F* fHistNoSigma0P;                     //!
  TH1F* fHistNoSigma0E;                     //!
  TH1F* fHistNoSigma0Mass2;                 //!
  TH1F* fHistNoSigma0Tv;                    //!
  TH1F* fHistNoSigma0OneOverPt;             //!
  TH1F* fHist2Sigma0E;                      //!
  TH1F* fHist2Sigma0Pt;                     //!
  TH1F* fHist2Sigma0Eta;                    //!
  TH1F* fHist2Sigma0Theta;                  //!
  TH1F* fHist2Sigma0Mass2;                  //!
  TH1F* fHist2Sigma0Tv;                     //!
  TH1F* fHist2Sigma0P;                      //!
  TH1F* fHist2Sigma0Phi;                    //!
  TH1F* fHist2Sigma0OneOverPt;              //!
  TH1F* fHist2NoSigma0E;                    //!
  TH1F* fHist2NoSigma0Pt;                   //!
  TH1F* fHist2NoSigma0Eta;                  //!
  TH1F* fHist2NoSigma0Theta;                //!
  TH1F* fHist2NoSigma0Mass2;                //!
  TH1F* fHist2NoSigma0Tv;                   //!
  TH1F* fHist2NoSigma0P;                    //!
  TH1F* fHist2NoSigma0Phi;                  //!
  TH1F* fHist2NoSigma0OneOverPt;            //!
  TH1F* fHistAllSigma0E;                    //!
  TH1F* fHistAllSigma0Pt;                   //!
  TH1F* fHistAllSigma0Eta;                  //!
  TH1F* fHistAllSigma0Theta;                //!
  TH1F* fHistAllSigma0Mass2;                //!
  TH1F* fHistAllSigma0Tv;                   //!
  TH1F* fHistAllSigma0P;                    //!
  TH1F* fHistAllSigma0Phi;                  //!
  TH1F* fHistAllSigma0OneOverPt;            //!
  TH1F* fHistAllNoSigma0E;                  //!
  TH1F* fHistAllNoSigma0Pt;                 //!
  TH1F* fHistAllNoSigma0Eta;                //!
  TH1F* fHistAllNoSigma0Theta;              //!
  TH1F* fHistAllNoSigma0Mass2;              //!
  TH1F* fHistAllNoSigma0Tv;                 //!
  TH1F* fHistAllNoSigma0P;                  //!
  TH1F* fHistAllNoSigma0Phi;                //!
  TH1F* fHistAllNoSigma0OneOverPt;          //!
  TH1F* fHistReconstrmcPhotonPt;            //!
  TH1F* fHistV0K0ShortInvMass;              //!
  TH1F* fHistReconstrmcPhotonPtIsPhysPrim;  //!
  TH1F* fHistAllPhotonsConvPrim;            //!
  TH2F* fHistSigma0PhiVsPt;                 //!
  TH2F* fHistNoSigma0PhiVsPt;               //!
  TH2F* fHist2Sigma0PhiVsPt;                //!
  TH2F* fHist2NoSigma0PhiVsPt;              //!
  TH2F* fHistAllSigma0PhiVsPt;              //!
  TH2F* fHistAllNoSigma0PhiVsPt;            //!
  TH2F* fHistSigma0ThetaVsPt;               //!
  TH2F* fHistNoSigma0ThetaVsPt;             //!
  TH2F* fHist2Sigma0ThetaVsPt;              //!
  TH2F* fHist2NoSigma0ThetaVsPt;            //!
  TH2F* fHistAllSigma0ThetaVsPt;            //!
  TH2F* fHistAllNoSigma0ThetaVsPt;          //!
  TH2F* fHistSigma0EtaVsPt;                 //!
  TH2F* fHistNoSigma0EtaVsPt;               //!
  TH2F* fHist2Sigma0EtaVsPt;                //!
  TH2F* fHist2NoSigma0EtaVsPt;              //!
  TH2F* fHistAllSigma0EtaVsPt;              //!
  TH2F* fHistAllNoSigma0EtaVsPt;            //!
  TH2F* fHistSigma0EVsPt;                   //!
  TH2F* fHistNoSigma0EVsPt;                 //!
  TH2F* fHist2Sigma0EVsPt;                  //!
  TH2F* fHist2NoSigma0EVsPt;                //!
  TH2F* fHistAllSigma0EVsPt;                //!
  TH2F* fHistAllNoSigma0EVsPt;              //!
  TH2F* fHistSigma0TvVsPt;                  //!
  TH2F* fHistNoSigma0TvVsPt;                //!
  TH2F* fHist2Sigma0TvVsPt;                 //!
  TH2F* fHist2NoSigma0TvVsPt;               //!
  TH2F* fHistAllSigma0TvVsPt;               //!
  TH2F* fHistAllNoSigma0TvVsPt;             //!
  TH2F* fHistClsDistrPosTr;                 //!
  TH2F* fHistClsDistrNegTr;                 //!
  TH2F* fHistPDGsOfMothToPhotons;           //!
  TH2F* fHist2PDGsOfMothToPhotons;          //!
  TH2F* fHistAllPDGsOfMothToPhotons;        //!
  AliConvEventCuts* fEventCuts;             //!
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
