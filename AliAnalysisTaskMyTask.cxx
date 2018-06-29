/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/* AliAnaysisTaskMyTask
 *
 * empty task which can serve as a starting point for building an analysis
 * as an example, one histogram is filled
 */

#include "AliAnalysisTask.h"
#include <iostream>
#include "AliAODEvent.h"
#include "AliAODInputHandler.h"
#include "AliAODMCParticle.h"
#include "AliAODTrack.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskMyTask.h"
#include "AliConversionPhotonBase.h"
#include "AliMCParticle.h"
#include "TChain.h"
#include "TH1F.h"
#include "TList.h"

class AliAnalysisTaskMyTask;  // your analysis class

using namespace std;  // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskMyTask)  // classimp: necessary for root

    AliAnalysisTaskMyTask::AliAnalysisTaskMyTask()
    : AliAnalysisTaskSE(),
      fAOD(nullptr),
      fMCEvent(nullptr),
      fV0Reader(nullptr),
      fV0ReaderName("NoInit"),
      fReaderGammas(nullptr),
      fGlobalTrackReference(),
      fOutputList(nullptr),
      fPIDResponse(nullptr),
      fIsMC(kFALSE),
      fHistPhotonPt(nullptr),
      fHistArmenterosPodolandski(nullptr),
      fHistClsDistrPosTr(nullptr),
      fHistClsDistrNegTr(nullptr),
      fHistV0LambdaInvMass(nullptr),
      fHistV0AntiLambdaInvMass(nullptr),
      fHistV0K0ShortInvMass(nullptr),
      fHistReconstrmcPhotonPt(nullptr),
      fHistArmenterosPodolandskiV0mcPhotons(nullptr),
      fHistV0PhotonCandPt(nullptr),
      fHistV0Pt(nullptr),
      fHistmcDaug1Pt(nullptr),
      fHistmcDaug2Pt(nullptr),
      fHistAllPhotons(nullptr),
      fHistArmenterosPodolandskiArmCut(nullptr),
      fHistV0mcPhotonPtandArmCut(nullptr),
      fHistArmenterosPodolandskiV0mcPhotonsCut(nullptr),
      fEventCuts(nullptr),
      fHistKindOfPrim(nullptr),
      fHistKindOfCand(nullptr),
      fHistSigma0E(nullptr),
      fHistSigma0Pt(nullptr),
      fHistSigma0Eta(nullptr),
      fHistSigma0Theta(nullptr),
      fHistSigma0Mass2(nullptr),
      fHistSigma0Tv(nullptr),
      fHistSigma0P(nullptr),
      fHistSigma0Phi(nullptr),
      fHistSigma0OneOverPt(nullptr),
      fHistNoSigma0E(nullptr),
      fHistNoSigma0Pt(nullptr),
      fHistNoSigma0Eta(nullptr),
      fHistNoSigma0Theta(nullptr),
      fHistNoSigma0Mass2(nullptr),
      fHistNoSigma0Tv(nullptr),
      fHistNoSigma0P(nullptr),
      fHistNoSigma0Phi(nullptr),
      fHistNoSigma0OneOverPt(nullptr),
      fHist2Sigma0E(nullptr),
      fHist2Sigma0Pt(nullptr),
      fHist2Sigma0Eta(nullptr),
      fHist2Sigma0Theta(nullptr),
      fHist2Sigma0Mass2(nullptr),
      fHist2Sigma0Tv(nullptr),
      fHist2Sigma0P(nullptr),
      fHist2Sigma0Phi(nullptr),
      fHist2Sigma0OneOverPt(nullptr),
      fHist2NoSigma0E(nullptr),
      fHist2NoSigma0Pt(nullptr),
      fHist2NoSigma0Eta(nullptr),
      fHist2NoSigma0Theta(nullptr),
      fHist2NoSigma0Mass2(nullptr),
      fHist2NoSigma0Tv(nullptr),
      fHist2NoSigma0P(nullptr),
      fHist2NoSigma0Phi(nullptr),
      fHist2NoSigma0OneOverPt(nullptr),
      fHistAllSigma0E(nullptr),
      fHistAllSigma0Pt(nullptr),
      fHistAllSigma0Eta(nullptr),
      fHistAllSigma0Theta(nullptr),
      fHistAllSigma0Mass2(nullptr),
      fHistAllSigma0Tv(nullptr),
      fHistAllSigma0P(nullptr),
      fHistAllSigma0Phi(nullptr),
      fHistAllSigma0OneOverPt(nullptr),
      fHistAllNoSigma0E(nullptr),
      fHistAllNoSigma0Pt(nullptr),
      fHistAllNoSigma0Eta(nullptr),
      fHistAllNoSigma0Theta(nullptr),
      fHistAllNoSigma0Mass2(nullptr),
      fHistAllNoSigma0Tv(nullptr),
      fHistAllNoSigma0P(nullptr),
      fHistAllNoSigma0Phi(nullptr),
      fHistAllNoSigma0OneOverPt(nullptr),
      fHistSigma0PhiVsPt(nullptr),
      fHistNoSigma0PhiVsPt(nullptr),
      fHist2Sigma0PhiVsPt(nullptr),
      fHist2NoSigma0PhiVsPt(nullptr),
      fHistAllSigma0PhiVsPt(nullptr),
      fHistAllNoSigma0PhiVsPt(nullptr),
      fHistSigma0ThetaVsPt(nullptr),
      fHistNoSigma0ThetaVsPt(nullptr),
      fHist2Sigma0ThetaVsPt(nullptr),
      fHist2NoSigma0ThetaVsPt(nullptr),
      fHistAllSigma0ThetaVsPt(nullptr),
      fHistAllNoSigma0ThetaVsPt(nullptr),
      fHistSigma0EtaVsPt(nullptr),
      fHistNoSigma0EtaVsPt(nullptr),
      fHist2Sigma0EtaVsPt(nullptr),
      fHist2NoSigma0EtaVsPt(nullptr),
      fHistAllSigma0EtaVsPt(nullptr),
      fHistAllNoSigma0EtaVsPt(nullptr),
      fHistSigma0EVsPt(nullptr),
      fHistNoSigma0EVsPt(nullptr),
      fHist2Sigma0EVsPt(nullptr),
      fHist2NoSigma0EVsPt(nullptr),
      fHistAllSigma0EVsPt(nullptr),
      fHistAllNoSigma0EVsPt(nullptr),
      fHistSigma0TvVsPt(nullptr),
      fHistNoSigma0TvVsPt(nullptr),
      fHist2Sigma0TvVsPt(nullptr),
      fHist2NoSigma0TvVsPt(nullptr),
      fHistAllSigma0TvVsPt(nullptr),
      fHistAllNoSigma0TvVsPt(nullptr),
      fHistPDGsOfMothToPhotons(nullptr),
      fHist2PDGsOfMothToPhotons(nullptr),
      fHistAllPDGsOfMothToPhotons(nullptr),
      fHistReconstrmcPhotonPtIsPhysPrim(nullptr),
      fHistAllPhotonsConvPrim(nullptr) {
  // default constructor, don't allocate memory here!
  // this is used by root for IO purposes, it needs to remain empty
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::AliAnalysisTaskMyTask(const char *name)
    : AliAnalysisTaskSE(name),
      fAOD(nullptr),
      fMCEvent(nullptr),
      fV0Reader(nullptr),
      fV0ReaderName("NoInit"),
      fReaderGammas(nullptr),
      fGlobalTrackReference(),
      fOutputList(nullptr),
      fPIDResponse(nullptr),
      fIsMC(kFALSE),
      fHistPhotonPt(nullptr),
      fHistArmenterosPodolandski(nullptr),
      fHistClsDistrPosTr(nullptr),
      fHistClsDistrNegTr(nullptr),
      fHistV0LambdaInvMass(nullptr),
      fHistV0AntiLambdaInvMass(nullptr),
      fHistV0K0ShortInvMass(nullptr),
      fHistReconstrmcPhotonPt(nullptr),
      fHistSigma0Mass2(nullptr),
      fHistSigma0Tv(nullptr),
      fHistArmenterosPodolandskiV0mcPhotons(nullptr),
      fHistV0PhotonCandPt(nullptr),
      fHistV0Pt(nullptr),
      fHistmcDaug1Pt(nullptr),
      fHistSigma0Theta(nullptr),
      fHistmcDaug2Pt(nullptr),
      fHistSigma0Eta(nullptr),
      fHistAllPhotons(nullptr),
      fHistArmenterosPodolandskiArmCut(nullptr),
      fHistV0mcPhotonPtandArmCut(nullptr),
      fHistSigma0Pt(nullptr),
      fHistArmenterosPodolandskiV0mcPhotonsCut(nullptr),
      fHistSigma0E(nullptr),
      fEventCuts(nullptr),
      fHistKindOfCand(nullptr),
      fHistSigma0P(nullptr),
      fHistSigma0Phi(nullptr),
      fHistKindOfPrim(nullptr),
      fHistSigma0OneOverPt(nullptr),
      fHistNoSigma0E(nullptr),
      fHistNoSigma0Pt(nullptr),
      fHistNoSigma0Eta(nullptr),
      fHistNoSigma0Theta(nullptr),
      fHistNoSigma0Mass2(nullptr),
      fHistNoSigma0Tv(nullptr),
      fHistNoSigma0P(nullptr),
      fHistNoSigma0Phi(nullptr),
      fHistNoSigma0OneOverPt(nullptr),
      fHist2Sigma0E(nullptr),
      fHist2Sigma0Pt(nullptr),
      fHist2Sigma0Eta(nullptr),
      fHist2Sigma0Theta(nullptr),
      fHist2Sigma0Mass2(nullptr),
      fHist2Sigma0Tv(nullptr),
      fHist2Sigma0P(nullptr),
      fHist2Sigma0Phi(nullptr),
      fHist2Sigma0OneOverPt(nullptr),
      fHist2NoSigma0E(nullptr),
      fHist2NoSigma0Pt(nullptr),
      fHist2NoSigma0Eta(nullptr),
      fHist2NoSigma0Theta(nullptr),
      fHist2NoSigma0Mass2(nullptr),
      fHist2NoSigma0Tv(nullptr),
      fHist2NoSigma0P(nullptr),
      fHist2NoSigma0Phi(nullptr),
      fHist2NoSigma0OneOverPt(nullptr),
      fHistAllSigma0E(nullptr),
      fHistAllSigma0Pt(nullptr),
      fHistAllSigma0Eta(nullptr),
      fHistAllSigma0Theta(nullptr),
      fHistAllSigma0Mass2(nullptr),
      fHistAllSigma0Tv(nullptr),
      fHistAllSigma0P(nullptr),
      fHistAllSigma0Phi(nullptr),
      fHistAllSigma0OneOverPt(nullptr),
      fHistAllNoSigma0E(nullptr),
      fHistAllNoSigma0Pt(nullptr),
      fHistAllNoSigma0Eta(nullptr),
      fHistAllNoSigma0Theta(nullptr),
      fHistAllNoSigma0Mass2(nullptr),
      fHistAllNoSigma0Tv(nullptr),
      fHistAllNoSigma0P(nullptr),
      fHistAllNoSigma0Phi(nullptr),
      fHistAllNoSigma0OneOverPt(nullptr),
      fHistSigma0PhiVsPt(nullptr),
      fHistNoSigma0PhiVsPt(nullptr),
      fHist2Sigma0PhiVsPt(nullptr),
      fHist2NoSigma0PhiVsPt(nullptr),
      fHistAllSigma0PhiVsPt(nullptr),
      fHistAllNoSigma0PhiVsPt(nullptr),
      fHistSigma0ThetaVsPt(nullptr),
      fHistNoSigma0ThetaVsPt(nullptr),
      fHist2Sigma0ThetaVsPt(nullptr),
      fHist2NoSigma0ThetaVsPt(nullptr),
      fHistAllSigma0ThetaVsPt(nullptr),
      fHistAllNoSigma0ThetaVsPt(nullptr),
      fHistSigma0EtaVsPt(nullptr),
      fHistNoSigma0EtaVsPt(nullptr),
      fHist2Sigma0EtaVsPt(nullptr),
      fHist2NoSigma0EtaVsPt(nullptr),
      fHistAllSigma0EtaVsPt(nullptr),
      fHistAllNoSigma0EtaVsPt(nullptr),
      fHistSigma0EVsPt(nullptr),
      fHistNoSigma0EVsPt(nullptr),
      fHist2Sigma0EVsPt(nullptr),
      fHist2NoSigma0EVsPt(nullptr),
      fHistAllSigma0EVsPt(nullptr),
      fHistAllNoSigma0EVsPt(nullptr),
      fHistSigma0TvVsPt(nullptr),
      fHistNoSigma0TvVsPt(nullptr),
      fHist2Sigma0TvVsPt(nullptr),
      fHist2NoSigma0TvVsPt(nullptr),
      fHistAllSigma0TvVsPt(nullptr),
      fHistAllNoSigma0TvVsPt(nullptr),
      fHistPDGsOfMothToPhotons(nullptr),
      fHist2PDGsOfMothToPhotons(nullptr),
      fHistAllPDGsOfMothToPhotons(nullptr),
      fHistReconstrmcPhotonPtIsPhysPrim(nullptr),
      fHistAllPhotonsConvPrim(nullptr) {
  // constructor
  DefineInput(0, TChain::Class());  // define the input of the analysis: in this
                                    // case we take a 'chain' of events
  // this chain is created by the analysis manager, so no need to worry about
  // it,
  // it does its work automatically
  DefineOutput(1, TList::Class());  // define the ouptut of the analysis: in
                                    // this case it's a list of histograms
  // you can add more output objects by calling DefineOutput(2,
  // classname::Class())
  // if you add more output objects, make sure to call PostData for all of them,
  // and to
  // make changes to your AddTask macro!
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::~AliAnalysisTaskMyTask() {
  // destructor
  if (fOutputList) {
    delete fOutputList;  // at the end of your task, it is deleted from memory
                         // by calling this function
  }
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserCreateOutputObjects() {
  // create output objects
  //
  // this function is called ONCE at the start of your analysis (RUNTIME)
  // here you create the histograms that you want to use
  //
  // the histograms are in this case added to a tlist, this list is in the end
  // saved
  // to an output file
  //
  fOutputList =
      new TList();  // this is a list which will contain all of your histograms
  // at the end of the analysis, the contents of this list are written
  // to the output file
  fOutputList->SetOwner(kTRUE);  // memory stuff: the list is owner of all
                                 // objects it contains and will delete them
                                 // if requested (dont worry about this now)

  fEventCuts2.AddQAplotsToList(fOutputList);
  // Lableing of the
  // Graph ("Title; X
  // Var; Y Var")
  // don't forget to add it to the list! the list
  // will be written to file, so if you want
  // your histogram in the output file, add it to the list!

  fHistSigma0E = new TH1F("Sigma0E", "Sigma0E", 500, 0, 10);
  fHistSigma0E->SetTitle("Sigma0E;Energy #it{E} [GeV];Counts #it{N}");
  fOutputList->Add(fHistSigma0E);

  fHistNoSigma0E = new TH1F("NoSigma0E", "NoSigma0E", 500, 0, 10);
  fHistNoSigma0E->SetTitle("NoSigma0E;Energy #it{E} [GeV];Counts #it{N}");
  fOutputList->Add(fHistNoSigma0E);

  fHist2Sigma0E = new TH1F("2Sigma0E", "2Sigma0E", 500, 0, 10);
  fHist2Sigma0E->SetTitle("2Sigma0E;Energy #it{E} [GeV];Counts #it{N}");
  fOutputList->Add(fHist2Sigma0E);

  fHist2NoSigma0E = new TH1F("2NoSigma0E", "2NoSigma0E", 500, 0, 10);
  fHist2NoSigma0E->SetTitle("2NoSigma0E;Energy #it{E} [GeV];Counts #it{N}");
  fOutputList->Add(fHist2NoSigma0E);

  fHistAllSigma0E = new TH1F("AllSigma0E", "AllSigma0E", 500, 0, 10);
  fHistAllSigma0E->SetTitle("AllSigma0E;Energy #it{E} [GeV];Counts #it{N}");
  fOutputList->Add(fHistAllSigma0E);

  fHistAllNoSigma0E = new TH1F("AllNoSigma0E", "AllNoSigma0E", 500, 0, 10);
  fHistAllNoSigma0E->SetTitle("AllNoSigma0E;Energy #it{E} [GeV];Counts #it{N}");
  fOutputList->Add(fHistAllNoSigma0E);

  fHistSigma0P = new TH1F("Sigma0P", "Sigma0P", 500, 0, 10);
  fHistSigma0P->SetTitle("Sigma0P;momentum #it{p} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistSigma0P);

  fHistNoSigma0P = new TH1F("NoSigma0P", "NoSigma0P", 500, 0, 10);
  fHistNoSigma0P->SetTitle(
      "NoSigma0P;momentum #it{p} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistNoSigma0P);

  fHist2Sigma0P = new TH1F("2Sigma0P", "2Sigma0P", 500, 0, 10);
  fHist2Sigma0P->SetTitle(
      "2Sigma0P;momentum #it{p} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHist2Sigma0P);

  fHist2NoSigma0P = new TH1F("2NoSigma0P", "2NoSigma0P", 500, 0, 10);
  fHist2NoSigma0P->SetTitle(
      "2NoSigma0P;momentum #it{p} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHist2NoSigma0P);

  fHistAllSigma0P = new TH1F("AllSigma0P", "AllSigma0P", 500, 0, 10);
  fHistAllSigma0P->SetTitle(
      "AllSigma0P;momentum #it{p} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistAllSigma0P);

  fHistAllNoSigma0P = new TH1F("AllNoSigma0P", "AllNoSigma0P", 500, 0, 10);
  fHistAllNoSigma0P->SetTitle(
      "AllNoSigma0P;momentum #it{p} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistAllNoSigma0P);

  fHistSigma0Pt = new TH1F("Sigma0Pt", "Sigma0Pt", 500, 0, 10);
  fHistSigma0Pt->SetTitle(
      "Sigma0Pt;transverse momentum #it{p}_{T} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistSigma0Pt);

  fHistNoSigma0Pt = new TH1F("NoSigma0Pt", "NoSigma0Pt", 500, 0, 10);
  fHistNoSigma0Pt->SetTitle(
      "NoSigma0Pt;transverse momentum #it{p}_{T} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistNoSigma0Pt);

  fHist2Sigma0Pt = new TH1F("2Sigma0Pt", "2Sigma0Pt", 500, 0, 10);
  fHist2Sigma0Pt->SetTitle(
      "2Sigma0Pt;transverse momentum #it{p}_{T} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHist2Sigma0Pt);

  fHist2NoSigma0Pt = new TH1F("2NoSigma0Pt", "2NoSigma0Pt", 500, 0, 10);
  fHist2NoSigma0Pt->SetTitle(
      "2NoSigma0Pt;transverse momentum #it{p}_{T} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHist2NoSigma0Pt);

  fHistAllSigma0Pt = new TH1F("AllSigma0Pt", "AllSigma0Pt", 500, 0, 10);
  fHistAllSigma0Pt->SetTitle(
      "AllSigma0Pt;transverse momentum #it{p}_{T} [GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistAllSigma0Pt);

  fHistAllNoSigma0Pt = new TH1F("AllNoSigma0Pt", "AllNoSigma0Pt", 500, 0, 10);
  fHistAllNoSigma0Pt->SetTitle(
      "AllNoSigma0Pt;transverse momentum #it{p}_{T} [GeV/#it{c}];Counts "
      "#it{N}");
  fOutputList->Add(fHistAllNoSigma0Pt);

  fHistSigma0OneOverPt =
      new TH1F("Sigma0OneOverPt", "Sigma0OneOverPt", 500, 0, 20);
  fHistSigma0OneOverPt->SetTitle(
      "Sigma0OneOverPt;transverse momentum 1/ #it{p}_{T} [#it{c}/GeV];Counts "
      "#it{N}");
  fOutputList->Add(fHistSigma0OneOverPt);

  fHistNoSigma0OneOverPt =
      new TH1F("NoSigma0OneOverPt", "NoSigma0OneOverPt", 500, 0, 20);
  fHistNoSigma0OneOverPt->SetTitle(
      "NoSigma0OneOverPt;transverse momentum 1/ #it{p}_{T} [#it{c}/GeV];Counts "
      "#it{N}");
  fOutputList->Add(fHistNoSigma0OneOverPt);

  fHist2Sigma0OneOverPt =
      new TH1F("2Sigma0OneOverPt", "2Sigma0OneOverPt", 500, 0, 20);
  fHist2Sigma0OneOverPt->SetTitle(
      "2Sigma0OneOverPt;transverse momentum 1/ #it{p}_{T} [#it{c}/GeV];Counts "
      "#it{N}");
  fOutputList->Add(fHist2Sigma0OneOverPt);

  fHist2NoSigma0OneOverPt =
      new TH1F("2NoSigma0OneOverPt", "2NoSigma0OneOverPt", 500, 0, 20);
  fHist2NoSigma0OneOverPt->SetTitle(
      "2NoSigma0OneOverPt;transverse momentum 1/ #it{p}_{T} "
      "[#it{c}/GeV];Counts #it{N}");
  fOutputList->Add(fHist2NoSigma0OneOverPt);

  fHistAllSigma0OneOverPt =
      new TH1F("AllSigma0OneOverPt", "AllSigma0OneOverPt", 500, 0, 20);
  fHistAllSigma0OneOverPt->SetTitle(
      "AllSigma0OneOverPt;transverse momentum 1/ #it{p}_{T} "
      "[#it{c}/GeV];Counts #it{N}");
  fOutputList->Add(fHistAllSigma0OneOverPt);

  fHistAllNoSigma0OneOverPt =
      new TH1F("AllNoSigma0OneOverPt", "AllNoSigma0OneOverPt", 500, 0, 20);
  fHistAllNoSigma0OneOverPt->SetTitle(
      "AllNoSigma0OneOverPt;transverse momentum 1/ #it{p}_{T} "
      "[#it{c}/GeV];Counts #it{N}");
  fOutputList->Add(fHistAllNoSigma0OneOverPt);

  fHistSigma0Eta = new TH1F("Sigma0Eta", "Sigma0Eta", 500, 0, 6);
  fHistSigma0Eta->SetTitle("Sigma0Eta;Pseudorapidity #eta ;Counts #it{N}");
  fOutputList->Add(fHistSigma0Eta);

  fHistNoSigma0Eta = new TH1F("NoSigma0Eta", "Sigma0Eta", 500, 0, 6);
  fHistNoSigma0Eta->SetTitle("NoSigma0Eta;Pseudorapidity #eta ;Counts #it{N}");
  fOutputList->Add(fHistNoSigma0Eta);

  fHist2Sigma0Eta = new TH1F("2Sigma0Eta", "2Sigma0Eta", 500, 0, 6);
  fHist2Sigma0Eta->SetTitle("2Sigma0Eta;Pseudorapidity #eta ;Counts #it{N}");
  fOutputList->Add(fHist2Sigma0Eta);

  fHist2NoSigma0Eta = new TH1F("2NoSigma0Eta", "2NoSigma0Eta", 500, 0, 6);
  fHist2NoSigma0Eta->SetTitle(
      "2NoSigma0Eta;Pseudorapidity #eta ;Counts #it{N}");
  fOutputList->Add(fHist2NoSigma0Eta);

  fHistAllSigma0Eta = new TH1F("AllSigma0Eta", "AllSigma0Eta", 500, 0, 6);
  fHistAllSigma0Eta->SetTitle(
      "AllSigma0Eta;Pseudorapidity #eta ;Counts #it{N}");
  fOutputList->Add(fHistAllSigma0Eta);

  fHistAllNoSigma0Eta = new TH1F("AllNoSigma0Eta", "AllNoSigma0Eta", 500, 0, 6);
  fHistAllNoSigma0Eta->SetTitle(
      "AllNoSigma0Eta;Pseudorapidity #eta ;Counts #it{N}");
  fOutputList->Add(fHistAllNoSigma0Eta);

  fHistSigma0Theta = new TH1F("Sigma0Theta", "Sigma0Theta", 500, 0, 3.2);
  fHistSigma0Theta->SetTitle("Sigma0Theta;Polar angle #theta ;Counts #it{N}");
  fOutputList->Add(fHistSigma0Theta);

  fHistNoSigma0Theta = new TH1F("NoSigma0Theta", "NoSigma0Theta", 500, 0, 3.2);
  fHistNoSigma0Theta->SetTitle(
      "NoSigma0Theta;Polar angle #theta ;Counts #it{N}");
  fOutputList->Add(fHistNoSigma0Theta);

  fHist2Sigma0Theta = new TH1F("2Sigma0Theta", "2Sigma0Theta", 500, 0, 3.2);
  fHist2Sigma0Theta->SetTitle("2Sigma0Theta;Polar angle #theta ;Counts #it{N}");
  fOutputList->Add(fHist2Sigma0Theta);

  fHist2NoSigma0Theta =
      new TH1F("2NoSigma0Theta", "2NoSigma0Theta", 500, 0, 3.2);
  fHist2NoSigma0Theta->SetTitle(
      "2NoSigma0Theta;Polar angle #theta ;Counts #it{N}");
  fOutputList->Add(fHist2NoSigma0Theta);

  fHistAllSigma0Theta =
      new TH1F("AllSigma0Theta", "AllSigma0Theta", 500, 0, 3.2);
  fHistAllSigma0Theta->SetTitle(
      "AllSigma0Theta;Polar angle #theta ;Counts #it{N}");
  fOutputList->Add(fHistAllSigma0Theta);

  fHistAllNoSigma0Theta =
      new TH1F("AllNoSigma0Theta", "AllNoSigma0Theta", 500, 0, 3.2);
  fHistAllNoSigma0Theta->SetTitle(
      "AllNoSigma0Theta;Polar angle #theta ;Counts #it{N}");
  fOutputList->Add(fHistAllNoSigma0Theta);

  fHistSigma0Mass2 = new TH1F("Sigma0Mass2", "Sigma0Mass2", 500, 0, 10);
  fHistSigma0Mass2->SetTitle(
      "Mass distribution of accepted Sigma0 candidates;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHistSigma0Mass2);

  fHistNoSigma0Mass2 = new TH1F("NoSigma0Mass2", "NoSigma0Mass2", 500, 0, 10);
  fHistNoSigma0Mass2->SetTitle(
      "Mass distribution of accepted NoSigma0 candidates;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHistNoSigma0Mass2);

  fHist2Sigma0Mass2 = new TH1F("2Sigma0Mass2", "2Sigma0Mass2", 500, 0, 10);
  fHist2Sigma0Mass2->SetTitle(
      "Mass distribution of accepted Sigma0 candidates;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHist2Sigma0Mass2);

  fHist2NoSigma0Mass2 =
      new TH1F("2NoSigma0Mass2", "2NoSigma0Mass2", 500, 0, 10);
  fHist2NoSigma0Mass2->SetTitle(
      "Mass distribution of accepted NoSigma0 candidates;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHist2NoSigma0Mass2);

  fHistAllSigma0Mass2 =
      new TH1F("AllSigma0Mass2", "AllSigma0Mass2", 500, 0, 10);
  fHistAllSigma0Mass2->SetTitle(
      "Mass distribution of accepted Sigma0 candidates;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHistAllSigma0Mass2);

  fHistAllNoSigma0Mass2 =
      new TH1F("AllNoSigma0Mass2", "AllNoSigma0Mass2", 500, 0, 10);
  fHistAllNoSigma0Mass2->SetTitle(
      "Mass distribution of accepted NoSigma0 candidates;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHistAllNoSigma0Mass2);

  fHistSigma0Tv = new TH1F("Sigma0Tv", "Sigma0Tv", 500, 0, 1);
  fHistSigma0Tv->SetTitle(
      "Distribution of T coordinate of prod.vertex;Time #it{t} [?s];Counts "
      "#it{N}");
  fOutputList->Add(fHistSigma0Tv);

  fHistNoSigma0Tv = new TH1F("NoSigma0Tv", "NoSigma0Tv", 500, 0, 1);
  fHistNoSigma0Tv->SetTitle(
      "Distribution of T coordinate of prod.vertex;Time #it{t} [?s];Counts "
      "#it{N}");
  fOutputList->Add(fHistNoSigma0Tv);

  fHist2Sigma0Tv = new TH1F("2Sigma0Tv", "2Sigma0Tv", 500, 0, 1);
  fHist2Sigma0Tv->SetTitle(
      "Distribution of T coordinate of prod.vertex;Time #it{t} [?s];Counts "
      "#it{N}");
  fOutputList->Add(fHist2Sigma0Tv);

  fHist2NoSigma0Tv = new TH1F("2NoSigma0Tv", "2NoSigma0Tv", 500, 0, 1);
  fHist2NoSigma0Tv->SetTitle(
      "Distribution of T coordinate of prod.vertex;Time #it{t} [?s];Counts "
      "#it{N}");
  fOutputList->Add(fHist2NoSigma0Tv);

  fHistAllSigma0Tv = new TH1F("AllSigma0Tv", "AllSigma0Tv", 500, 0, 1);
  fHistAllSigma0Tv->SetTitle(
      "Distribution of T coordinate of prod.vertex;Time #it{t} [?s];Counts "
      "#it{N}");
  fOutputList->Add(fHistAllSigma0Tv);

  fHistAllNoSigma0Tv = new TH1F("AllNoSigma0Tv", "AllNoSigma0Tv", 500, 0, 1);
  fHistAllNoSigma0Tv->SetTitle(
      "Distribution of T coordinate of prod.vertex;Time #it{t} [?s];Counts "
      "#it{N}");
  fOutputList->Add(fHistAllNoSigma0Tv);

  fHistSigma0Phi =
      new TH1F("Sigma0Phi", ";Azimuthal angle #phi ; Entries", 500, 0, 6.3);
  fOutputList->Add(fHistSigma0Phi);

  fHistNoSigma0Phi = new TH1F(
      "NoSigma0Phi", ";Azimuthal angle #phi ; Counts #it{N}", 500, 0, 6.3);
  fOutputList->Add(fHistNoSigma0Phi);

  fHist2Sigma0Phi = new TH1F(
      "2Sigma0Phi", ";Azimuthal angle #phi ; Counts #it{N}", 500, 0, 6.3);
  fOutputList->Add(fHist2Sigma0Phi);

  fHist2NoSigma0Phi = new TH1F(
      "2NoSigma0Phi", ";Azimuthal angle #phi ; Counts #it{N}", 500, 0, 6.3);
  fOutputList->Add(fHist2NoSigma0Phi);

  fHistAllSigma0Phi = new TH1F(
      "AllSigma0Phi", ";Azimuthal angle #phi ; Counts #it{N}", 500, 0, 6.3);
  fOutputList->Add(fHistAllSigma0Phi);

  fHistAllNoSigma0Phi = new TH1F(
      "AllNoSigma0Phi", ";Azimuthal angle #phi ; Counts #it{N}", 500, 0, 6.3);
  fOutputList->Add(fHistAllNoSigma0Phi);

  fHistSigma0PhiVsPt =
      new TH2F("Sigma0PhiVsPt", "Sigma0PhiVsPt", 500, 0, 10, 500, 0, 6.3);
  fHistSigma0PhiVsPt->SetTitle(
      "Sigma0PhiVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Azimuthal "
      "angle #phi");
  fOutputList->Add(fHistSigma0PhiVsPt);

  fHistNoSigma0PhiVsPt =
      new TH2F("NoSigma0PhiVsPt", "NoSigma0PhiVsPt", 500, 0, 10, 500, 0, 6.3);
  fHistNoSigma0PhiVsPt->SetTitle(
      "NoSigma0PhiVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Azimuthal "
      "angle #phi");
  fOutputList->Add(fHistNoSigma0PhiVsPt);

  fHist2Sigma0PhiVsPt =
      new TH2F("2Sigma0PhiVsPt", "2Sigma0PhiVsPt", 500, 0, 10, 500, 0, 6.3);
  fHist2Sigma0PhiVsPt->SetTitle(
      "2Sigma0PhiVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Azimuthal "
      "angle #phi");
  fOutputList->Add(fHist2Sigma0PhiVsPt);

  fHist2NoSigma0PhiVsPt =
      new TH2F("2NoSigma0PhiVsPt", "2NoSigma0PhiVsPt", 500, 0, 10, 500, 0, 6.3);
  fHist2NoSigma0PhiVsPt->SetTitle(
      "2NoSigma0PhiVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Azimuthal "
      "angle #phi");
  fOutputList->Add(fHist2NoSigma0PhiVsPt);

  fHistAllSigma0PhiVsPt =
      new TH2F("AllSigma0PhiVsPt", "AllSigma0PhiVsPt", 500, 0, 10, 500, 0, 6.3);
  fHistAllSigma0PhiVsPt->SetTitle(
      "AllSigma0PhiVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Azimuthal "
      "angle #phi");
  fOutputList->Add(fHistAllSigma0PhiVsPt);

  fHistAllNoSigma0PhiVsPt = new TH2F("AllNoSigma0PhiVsPt", "AllNoSigma0PhiVsPt",
                                     500, 0, 10, 500, 0, 6.3);
  fHistAllNoSigma0PhiVsPt->SetTitle(
      "AllNoSigma0PhiVsPt;transverse momentum  #it{p}_{T} "
      "[GeV/#it{c}];Azimuthal angle #phi");
  fOutputList->Add(fHistAllNoSigma0PhiVsPt);

  fHistSigma0ThetaVsPt =
      new TH2F("Sigma0ThetaVsPt", "Sigma0ThetaVsPt", 500, 0, 10, 500, 0, 3.2);
  fHistSigma0ThetaVsPt->SetTitle(
      "Sigma0ThetaVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Polar "
      "angle #theta");
  fOutputList->Add(fHistSigma0ThetaVsPt);

  fHistNoSigma0ThetaVsPt = new TH2F("NoSigma0ThetaVsPt", "NoSigma0ThetaVsPt",
                                    500, 0, 10, 500, 0, 3.2);
  fHistNoSigma0ThetaVsPt->SetTitle(
      "NoSigma0ThetaVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Polar "
      "angle #theta");
  fOutputList->Add(fHistNoSigma0ThetaVsPt);

  fHist2Sigma0ThetaVsPt =
      new TH2F("2Sigma0ThetaVsPt", "2Sigma0ThetaVsPt", 500, 0, 10, 500, 0, 3.2);
  fHist2Sigma0ThetaVsPt->SetTitle(
      "2Sigma0ThetaVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Polar "
      "angle #theta");
  fOutputList->Add(fHist2Sigma0ThetaVsPt);

  fHist2NoSigma0ThetaVsPt = new TH2F("2NoSigma0ThetaVsPt", "2NoSigma0ThetaVsPt",
                                     500, 0, 10, 500, 0, 3.2);
  fHist2NoSigma0ThetaVsPt->SetTitle(
      "2NoSigma0ThetaVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Polar "
      "angle #theta");
  fOutputList->Add(fHist2NoSigma0ThetaVsPt);

  fHistAllSigma0ThetaVsPt = new TH2F("AllSigma0ThetaVsPt", "AllSigma0ThetaVsPt",
                                     500, 0, 10, 500, 0, 3.2);
  fHistAllSigma0ThetaVsPt->SetTitle(
      "AllSigma0ThetaVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Polar "
      "angle #theta");
  fOutputList->Add(fHistAllSigma0ThetaVsPt);

  fHistAllNoSigma0ThetaVsPt = new TH2F(
      "AllNoSigma0ThetaVsPt", "AllNoSigma0ThetaVsPt", 500, 0, 10, 500, 0, 3.2);
  fHistAllNoSigma0ThetaVsPt->SetTitle(
      "AllNoSigma0ThetaVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Polar "
      "angle #theta");
  fOutputList->Add(fHistAllNoSigma0ThetaVsPt);

  fHistSigma0EtaVsPt =
      new TH2F("Sigma0EtaVsPt", "Sigma0EtaVsPt", 500, 0, 10, 500, 0, 6);
  fHistSigma0EtaVsPt->SetTitle(
      "Sigma0EtaVsPt;transverse momentum  #it{p}_{T} "
      "[GeV/#it{c}];Pseudorapidity #eta");
  fOutputList->Add(fHistSigma0EtaVsPt);

  fHistNoSigma0EtaVsPt =
      new TH2F("NoSigma0EtaVsPt", "NoSigma0EtaVsPt", 500, 0, 10, 500, 0, 6);
  fHistNoSigma0EtaVsPt->SetTitle(
      "NoSigma0EtaVsPt;transverse momentum  #it{p}_{T} "
      "[GeV/#it{c}];Pseudorapidity #eta");
  fOutputList->Add(fHistNoSigma0EtaVsPt);

  fHist2Sigma0EtaVsPt =
      new TH2F("2Sigma0EtaVsPt", "2Sigma0EtaVsPt", 500, 0, 10, 500, 0, 6);
  fHist2Sigma0EtaVsPt->SetTitle(
      "2Sigma0EtaVsPt;transverse momentum  #it{p}_{T} "
      "[GeV/#it{c}];Pseudorapidity #eta");
  fOutputList->Add(fHist2Sigma0EtaVsPt);

  fHist2NoSigma0EtaVsPt =
      new TH2F("2NoSigma0EtaVsPt", "2NoSigma0EtaVsPt", 500, 0, 10, 500, 0, 6);
  fHist2NoSigma0EtaVsPt->SetTitle(
      "2NoSigma0EtaVsPt;transverse momentum  #it{p}_{T} "
      "[GeV/#it{c}];Pseudorapidity #eta");
  fOutputList->Add(fHist2NoSigma0EtaVsPt);

  fHistAllSigma0EtaVsPt =
      new TH2F("AllSigma0EtaVsPt", "AllSigma0EtaVsPt", 500, 0, 10, 500, 0, 6);
  fHistAllSigma0EtaVsPt->SetTitle(
      "AllSigma0EtaVsPt;transverse momentum  #it{p}_{T} "
      "[GeV/#it{c}];Pseudorapidity #eta");
  fOutputList->Add(fHistAllSigma0EtaVsPt);

  fHistAllNoSigma0EtaVsPt = new TH2F("AllNoSigma0EtaVsPt", "AllNoSigma0EtaVsPt",
                                     500, 0, 10, 500, 0, 6);
  fHistAllNoSigma0EtaVsPt->SetTitle(
      "AllNoSigma0EtaVsPt;transverse momentum  #it{p}_{T} "
      "[GeV/#it{c}];Pseudorapidity #eta");
  fOutputList->Add(fHistAllNoSigma0EtaVsPt);

  fHistSigma0EVsPt =
      new TH2F("Sigma0EVsPt", "Sigma0EVsPt", 500, 0, 10, 500, 0, 1);
  fHistSigma0EVsPt->SetTitle(
      "Sigma0EVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Energy #it{E} "
      "[GeV]");
  fOutputList->Add(fHistSigma0EVsPt);

  fHistNoSigma0EVsPt =
      new TH2F("NoSigma0EVsPt", "NoSigma0EVsPt", 500, 0, 10, 500, 0, 1);
  fHistNoSigma0EVsPt->SetTitle(
      "NoSigma0EVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Energy "
      "#it{E} [GeV]");
  fOutputList->Add(fHistNoSigma0EVsPt);

  fHist2Sigma0EVsPt =
      new TH2F("2Sigma0EVsPt", "2Sigma0EVsPt", 500, 0, 10, 500, 0, 1);
  fHist2Sigma0EVsPt->SetTitle(
      "2Sigma0EVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Energy #it{E} "
      "[GeV]");
  fOutputList->Add(fHist2Sigma0EVsPt);

  fHist2NoSigma0EVsPt =
      new TH2F("2NoSigma0EVsPt", "2NoSigma0EVsPt", 500, 0, 10, 500, 0, 1);
  fHist2NoSigma0EVsPt->SetTitle(
      "2NoSigma0EVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Energy "
      "#it{E} [GeV]");
  fOutputList->Add(fHist2NoSigma0EVsPt);

  fHistAllSigma0EVsPt =
      new TH2F("AllSigma0EVsPt", "AllSigma0EVsPt", 500, 0, 10, 500, 0, 1);
  fHistAllSigma0EVsPt->SetTitle(
      "AllSigma0EVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Energy "
      "#it{E} [GeV]");
  fOutputList->Add(fHistAllSigma0EVsPt);

  fHistAllNoSigma0EVsPt =
      new TH2F("AllNoSigma0EVsPt", "AllNoSigma0EVsPt", 500, 0, 10, 500, 0, 1);
  fHistAllNoSigma0EVsPt->SetTitle(
      "AllNoSigma0EVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Energy "
      "#it{E} [GeV]");
  fOutputList->Add(fHistAllNoSigma0EVsPt);

  fHistSigma0TvVsPt =
      new TH2F("Sigma0TvVsPt", "Sigma0TvVsPt", 500, 0, 10, 500, 0, 1);
  fHistSigma0TvVsPt->SetTitle(
      "Sigma0TvVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Time coord. "
      "of prod.vertex #it{t} [?s]");
  fOutputList->Add(fHistSigma0TvVsPt);

  fHistNoSigma0TvVsPt =
      new TH2F("NoSigma0TvVsPt", "NoSigma0TvVsPt", 500, 0, 10, 500, 0, 1);
  fHistNoSigma0TvVsPt->SetTitle(
      "NoSigma0TvVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Time coord. "
      "of prod.vertex #it{t} [?s]");
  fOutputList->Add(fHistNoSigma0TvVsPt);

  fHist2Sigma0TvVsPt =
      new TH2F("2Sigma0TvVsPt", "2Sigma0TvVsPt", 500, 0, 10, 500, 0, 1);
  fHist2Sigma0TvVsPt->SetTitle(
      "2Sigma0TvVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Time coord. "
      "of prod.vertex #it{t} [?s]");
  fOutputList->Add(fHist2Sigma0TvVsPt);

  fHist2NoSigma0TvVsPt =
      new TH2F("2NoSigma0TvVsPt", "2NoSigma0TvVsPt", 500, 0, 10, 500, 0, 1);
  fHist2NoSigma0TvVsPt->SetTitle(
      "2NoSigma0TvVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Time "
      "coord. of prod.vertex #it{t} [?s]");
  fOutputList->Add(fHist2NoSigma0TvVsPt);

  fHistAllSigma0TvVsPt =
      new TH2F("AllSigma0TvVsPt", "AllSigma0TvVsPt", 500, 0, 10, 500, 0, 1);
  fHistAllSigma0TvVsPt->SetTitle(
      "AllSigma0TvVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Time "
      "coord. of prod.vertex #it{t} [?s]");
  fOutputList->Add(fHistAllSigma0TvVsPt);

  fHistAllNoSigma0TvVsPt =
      new TH2F("AllNoSigma0TvVsPt", "AllNoSigma0TvVsPt", 500, 0, 10, 500, 0, 1);
  fHistAllNoSigma0TvVsPt->SetTitle(
      "AllNoSigma0TvVsPt;transverse momentum  #it{p}_{T} [GeV/#it{c}];Time "
      "coord. of prod.vertex #it{t} [?s]");
  fOutputList->Add(fHistAllNoSigma0TvVsPt);

  fHistReconstrmcPhotonPt = new TH1F("fHistReconstrmcPhotonPt",
                                     "fHistReconstrmcPhotonPt", 500, 0, 10);
  fHistReconstrmcPhotonPt->SetTitle(
      "Pt Distribution of accepted V0s;transverse momentum #it{p}_{T} "
      "[GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistReconstrmcPhotonPt);

  fHistV0mcPhotonPtandArmCut = new TH1F(
      "fHistV0mcPhotonPtandArmCut", "fHistV0mcPhotonPtandArmCut", 500, 0, 10);
  fHistV0mcPhotonPtandArmCut->SetTitle(
      "MCTrueV0Photons;transverse momentum #it{p}_{T} [GeV/#it{c}];Counts "
      "#it{N}");
  fOutputList->Add(fHistV0mcPhotonPtandArmCut);

  fHistClsDistrPosTr = new TH2F("fHistClsDistrPosTr", "fHistClsDistrPosTr", 500,
                                0, 1.5, 500, 0, 200);
  fHistClsDistrPosTr->SetTitle(
      "Cluster-Distribution;#it{p}_{T} [GeV/#it{c}];Number of Clusters");
  fOutputList->Add(fHistClsDistrPosTr);

  fHistClsDistrNegTr = new TH2F("fHistClsDistrNegTr", "fHistClsDistrNegTr", 500,
                                0, 1.5, 500, 0, 200);
  fHistClsDistrNegTr->SetTitle(
      "Cluster-Distribution;#it{p}_{T} [GeV/#it{c}];Number of Clusters");
  fOutputList->Add(fHistClsDistrNegTr);

  fHistKindOfPrim = new TH1F("fHistKindOfPrim", "Entries", 25, 0, 25);
  fHistKindOfPrim->GetXaxis()->SetBinLabel(1, "All MCs");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(2, "Mothers exist");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(3, "Different Mothers");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(4, "Electron Combinatorial");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(5, "Direct Electron Combinatorial");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(6, "Pion Combinatorics");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(7, "Pion, Proton Combinatorics");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(8, "Pion, Electron Combinatorics");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(9, "Kaon Combinatorics");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(10, "Same Mother");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(
      11, "Combinatorics From Hadronic Decays");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(12, "Pi0 Dalitz");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(13, "Eta Dalitz");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(14, "Primary Photons");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(15, "Secondary Photons");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(16, "Something Else");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(17, "Something Else");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(18, "Something Else");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(19, "SomeThing ELse");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(20, "Tracks Exit");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(21, "|#eta| < 0.8");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(22, "#it{p}_{T} > 0.1 MeV");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(23, "Findable Cluster Ratio > 80%");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(24, "ArmQt < 0.3");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(25, "Daughters Exit");
  fOutputList->Add(fHistKindOfPrim);

  fHistKindOfCand = new TH1F("fHistKindOfCand", "Entries", 25, 0, 25);
  fHistKindOfCand->GetXaxis()->SetBinLabel(1, "All MCs");
  fHistKindOfCand->GetXaxis()->SetBinLabel(2, "Mothers exist");
  fHistKindOfCand->GetXaxis()->SetBinLabel(3, "Different Mothers");
  fHistKindOfCand->GetXaxis()->SetBinLabel(4, "Electron Combinatorial");
  fHistKindOfCand->GetXaxis()->SetBinLabel(5, "Direct Electron Combinatorial");
  fHistKindOfCand->GetXaxis()->SetBinLabel(6, "Pion Combinatorics");
  fHistKindOfCand->GetXaxis()->SetBinLabel(7, "Pion, Proton Combinatorics");
  fHistKindOfCand->GetXaxis()->SetBinLabel(8, "Pion, Electron Combinatorics");
  fHistKindOfCand->GetXaxis()->SetBinLabel(9, "Kaon Combinatorics");
  fHistKindOfCand->GetXaxis()->SetBinLabel(10, "Same Mother");
  fHistKindOfCand->GetXaxis()->SetBinLabel(
      11, "Combinatorics From Hadronic Decays");
  fHistKindOfCand->GetXaxis()->SetBinLabel(12, "Pi0 Dalitz");
  fHistKindOfCand->GetXaxis()->SetBinLabel(13, "Eta Dalitz");
  fHistKindOfCand->GetXaxis()->SetBinLabel(14, "Primary Photons");
  fHistKindOfCand->GetXaxis()->SetBinLabel(15, "Secondary Photons");
  fHistKindOfCand->GetXaxis()->SetBinLabel(16, "Something Else");
  fHistKindOfCand->GetXaxis()->SetBinLabel(17, "Something Else");
  fHistKindOfCand->GetXaxis()->SetBinLabel(18, "Something Else");
  fHistKindOfCand->GetXaxis()->SetBinLabel(19, "SomeThing ELse");
  fHistKindOfCand->GetXaxis()->SetBinLabel(20, "Tracks Exit");
  fHistKindOfCand->GetXaxis()->SetBinLabel(21, "|#eta| < 0.8");
  fHistKindOfCand->GetXaxis()->SetBinLabel(22, "#it{p}_{T} > 0.1 MeV");
  fHistKindOfCand->GetXaxis()->SetBinLabel(23, "Findable Cluster Ratio > 80%");
  fHistKindOfCand->GetXaxis()->SetBinLabel(24, "ArmQt < 0.3");
  fHistKindOfCand->GetXaxis()->SetBinLabel(25, "Daughters Exit");
  fOutputList->Add(fHistKindOfCand);

  fHistV0LambdaInvMass =
      new TH1F("fHistV0LambdaInvMass", "fHistV0LambdaInvMass", 500, 0, 1.5);
  fHistV0LambdaInvMass->SetTitle(
      "Invariantmass-Distribution Lambda;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHistV0LambdaInvMass);

  fHistV0AntiLambdaInvMass = new TH1F("fHistV0AntiLambdaInvMass",
                                      "fHistV0AntiLambdaInvMass", 500, 0, 1.5);
  fHistV0AntiLambdaInvMass->SetTitle(
      "Invariantmass-Distribution AntiLambda;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHistV0AntiLambdaInvMass);

  fHistV0K0ShortInvMass =
      new TH1F("fHistV0K0ShortInvMass", "fHistV0K0ShortInvMass", 500, 0, 1.5);
  fHistV0K0ShortInvMass->SetTitle(
      "Invariantmass-Distribution K0Short;invariant mass #it{m} "
      "[GeV/#it{c}^{2}];Counts #it{N}");
  fOutputList->Add(fHistV0K0ShortInvMass);

  fHistPhotonPt = new TH1F(
      "fHistPhotonPt", "; #it{p}_{T} (GeV/#it{c}); Counts #it{N}", 500, 0, 10);
  fOutputList->Add(fHistPhotonPt);

  fHistAllPhotons = new TH1F(
      "AllPhotons", "; #it{p}_{T} (GeV/#it{c}); Counts #it{N}", 500, 0, 10);
  fOutputList->Add(fHistAllPhotons);

  fHistAllPhotonsConvPrim =
      new TH1F("AllPhotonsConvPrim", "; #it{p}_{T} (GeV/#it{c}); Counts #it{N}",
               500, 0, 10);
  fOutputList->Add(fHistAllPhotonsConvPrim);

  fHistArmenterosPodolandski = new TH2F(
      "fHistArmenterosPodolandski", " ; #alpha; #it{q}_{T} p#pi [GeV/#it{c}]",
      500, -1, 1, 500, 0, 0.4);
  fOutputList->Add(fHistArmenterosPodolandski);

  fHistArmenterosPodolandskiV0mcPhotons = new TH2F(
      "fHistArmenterosPodolandskiV0mcPhotons",
      " ; #alpha; #it{q}_{T} p#pi [GeV/#it{c}]", 500, -1, 1, 500, 0, 0.2);
  fOutputList->Add(fHistArmenterosPodolandskiV0mcPhotons);

  fHistArmenterosPodolandskiArmCut = new TH2F(
      "fHistArmenterosPodolandskiArmCut",
      " ; #alpha; #it{q}_{T} p#pi [GeV/#it{c}]", 500, -1, 1, 500, 0, farmQtCut);
  fOutputList->Add(fHistArmenterosPodolandskiArmCut);

  fHistV0PhotonCandPt =
      new TH1F("fHistV0PhotonCandPt", "fHistV0PhotonCandPt", 500, 0, 10);
  fHistV0PhotonCandPt->SetTitle(
      "fHistV0PhotonCandPt;transverse momentum #it{q}_{T} [GeV/#it{c}];Counts "
      "#it{N}");
  fOutputList->Add(fHistV0PhotonCandPt);

  fHistArmenterosPodolandskiV0mcPhotonsCut = new TH2F(
      "fHistArmenterosPodolandskiV0mcPhotonsCut",
      " ; #alpha; #it{q}_{T} p#pi [GeV/#it{c}]", 500, -1, 1, 500, 0, farmQtCut);
  fOutputList->Add(fHistArmenterosPodolandskiV0mcPhotonsCut);

  fHistmcDaug2Pt = new TH1F("fHistmcDaug2Pt", "fHistmcDaug2Pt", 500, 0, 10);
  fHistmcDaug2Pt->SetTitle(
      "fHistmcDaug2Pt;transverse momentum #it{q}_{T} [GeV/#it{c}];Counts "
      "#it{N}");
  fOutputList->Add(fHistmcDaug2Pt);

  fHistmcDaug1Pt = new TH1F("fHistmcDaug1Pt", "fHistmcDaug1Pt", 500, 0, 10);
  fHistmcDaug1Pt->SetTitle(
      "fHistmcDaug1Pt;transverse momentum #it{q}_{T} [GeV/#it{c}];Counts "
      "#it{N}");
  fOutputList->Add(fHistmcDaug1Pt);

  fHistV0Pt = new TH1F("fHistV0Pt", "fHistV0Pt", 500, 0, 10);
  fHistV0Pt->SetTitle(
      "Pt Distribution of accepted V0s;transverse momentum #it{q}_{T} "
      "[GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistV0Pt);

  fHistPDGsOfMothToPhotons =
      new TH2F("PDGsOfMothToPhotons", "PDGsOfMothToPhotons", 8000, -4000, 4000,
               500, 0, 10);
  fHistPDGsOfMothToPhotons->SetTitle(
      "PDGsOfMothToPhotons;PDG-Code "
      "; transverse momentum  #it{p}_{T} [GeV/#it{c}]");
  fOutputList->Add(fHistPDGsOfMothToPhotons);

  fHist2PDGsOfMothToPhotons =
      new TH2F("2PDGsOfMothToPhotons", "2PDGsOfMothToPhotons", 8000, -4000,
               4000, 500, 0, 10);
  fHist2PDGsOfMothToPhotons->SetTitle(
      "2PDGsOfMothToPhotons;PDG-Code "
      "; transverse momentum  #it{p}_{T} [GeV/#it{c}]");
  fOutputList->Add(fHist2PDGsOfMothToPhotons);

  fHistAllPDGsOfMothToPhotons =
      new TH2F("AllPDGsOfMothToPhotons", "AllPDGsOfMothToPhotons", 8000, -4000,
               4000, 500, 0, 10);
  fHistAllPDGsOfMothToPhotons->SetTitle(
      "AllPDGsOfMothToPhotons;PDG-Code "
      "; transverse momentum  #it{p}_{T} [GeV/#it{c}]");
  fOutputList->Add(fHistAllPDGsOfMothToPhotons);

  fHistReconstrmcPhotonPtIsPhysPrim =
      new TH1F("ReconstrmcPhotonPtIsPhysPrim", "ReconstrmcPhotonPtIsPhysPrim",
               500, 0, 10);
  fHistReconstrmcPhotonPtIsPhysPrim->SetTitle(
      "ReconstrmcPhotonPtIsPhysPrim;transverse momentum #it{p}_{T} "
      "[GeV/#it{c}];Counts #it{N}");
  fOutputList->Add(fHistReconstrmcPhotonPtIsPhysPrim);

  PostData(1, fOutputList);  // postdata will notify the analysis manager of
                             // changes / updates to the
  // fOutputList object. the manager will in the end take care of writing your
  // output to file
  // so it needs to know what's in the output
}
//_____________________________________________________________________________
void AliAnalysisTaskMyTask::UserExec(Option_t *) {
  // user exec
  // this function is called once for each event
  // the manager will take care of reading the events from file, and with the
  // static function InputEvent() you
  // have access to the current event.
  // once you return from the UserExec function, the manager will retrieve the
  // next event from the chain
  fAOD = dynamic_cast<AliAODEvent *>(
      InputEvent());  // get an event (called fAOD) from the input file
  // there's another event format (ESD) which works in a similar way
  // but is more cpu/memory unfriendly. for now, we'll stick with aod's

  if (!fAOD) return;

  // Event cuts - check whether the event is good for analysis
  if (!fEventCuts2.AcceptEvent(fAOD)) {
    PostData(1, fOutputList);
    return;
  }

  // Get all Photons

  if (fIsMC) {
    AliAODInputHandler *eventHandler = dynamic_cast<AliAODInputHandler *>(
        AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());

    fMCEvent = eventHandler->MCEvent();

    for (int iPart = 1; iPart < (fMCEvent->GetNumberOfTracks()); iPart++) {
      AliAODMCParticle *particle =
          (AliAODMCParticle *)fMCEvent->GetTrack(iPart);
      fHistKindOfPrim->Fill(10);
      if (!particle) continue;
      fHistKindOfPrim->Fill(11);
      if (std::abs(particle->Eta()) > fEtaCut) continue;
      fHistKindOfPrim->Fill(13);
      if (particle->E() < fECut) continue;
      fHistKindOfPrim->Fill(14);
      if (particle->GetPdgCode() != 22) continue;
      fHistKindOfPrim->Fill(15);
      AliAODMCParticle *firstDaughter = static_cast<AliAODMCParticle *>(
          fMCEvent->GetTrack(particle->GetFirstDaughter()));
      AliAODMCParticle *lastDaughter = static_cast<AliAODMCParticle *>(
          fMCEvent->GetTrack(particle->GetLastDaughter()));
      if (!firstDaughter) continue;
      if (!lastDaughter) continue;
      fHistKindOfPrim->Fill(16);
      if (firstDaughter->Eta() > fEtaCut) continue;
      if (lastDaughter->Eta() > fEtaCut) continue;
      fHistKindOfPrim->Fill(17);
      if (firstDaughter->Pt() < fpTCut) continue;
      if (lastDaughter->Pt() < fpTCut) continue;
      fHistKindOfPrim->Fill(18);
      const AliVVertex *primVtxMC = fMCEvent->GetPrimaryVertex();
      Double_t mcProdVtxX = primVtxMC->GetX();
      Double_t mcProdVtxY = primVtxMC->GetY();
      Double_t mcProdVtxZ = primVtxMC->GetZ();
      Bool_t fIsConvPrim = IsConversionPrimaryAOD(fAOD, particle, mcProdVtxX,
                                                  mcProdVtxY, mcProdVtxZ);
      if (fIsConvPrim) {
        fHistAllPhotonsConvPrim->Fill(particle->Pt());
      };
      if (!(particle->IsPhysicalPrimary())) continue;
      fHistKindOfPrim->Fill(12);
      fHistAllPhotons->Fill(particle->Pt());
      Sigma0DescendancyAll(firstDaughter);
    }
  }

  // Keep track of the global tracks
  StoreGlobalTrackReference();

  AliAnalysisManager *man = AliAnalysisManager::GetAnalysisManager();
  fV0Reader = (AliV0ReaderV1 *)man->GetTask(fV0ReaderName.Data());
  if (!fV0Reader) {
    std::cout << "Error: No V0 Reader " << fV0ReaderName.Data() << "\n";
    return;
  }

  // Get the reconstructed photons
  fReaderGammas = fV0Reader->GetReconstructedGammas();

  for (int iGamma = 0; iGamma < fReaderGammas->GetEntriesFast(); ++iGamma) {
    auto *PhotonCandidate =
        dynamic_cast<AliAODConversionPhoton *>(fReaderGammas->At(iGamma));

    if (!PhotonCandidate) continue;

    fHistPhotonPt->Fill(PhotonCandidate->GetPhotonPt());

    if (fIsMC) {
      AliAODInputHandler *eventHandler = dynamic_cast<AliAODInputHandler *>(
          AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
      fMCEvent = eventHandler->MCEvent();

      if (fMCEvent) {
        // 			cout << "generating MC stack"<< endl;

        AliAODMCParticle *posDaughter = static_cast<AliAODMCParticle *>(
            fMCEvent->GetTrack(PhotonCandidate->GetMCLabelPositive()));
        AliAODMCParticle *negDaughter = static_cast<AliAODMCParticle *>(
            fMCEvent->GetTrack(PhotonCandidate->GetMCLabelNegative()));

        if (posDaughter == NULL || negDaughter == NULL) continue;
        fHistKindOfCand->Fill(23);
        IsConvertedPhotonDaughterIsPhysPrimaryCheck(posDaughter, negDaughter);
        if (!IsConvertedPhoton(posDaughter, negDaughter, fMCEvent)) continue;
        Sigma0Descendancy(posDaughter);
        fHistReconstrmcPhotonPt->Fill(PhotonCandidate->Pt());
      }
    }
  }

  for (auto v0obj : *(fAOD->GetV0s())) {
    auto *v0 = static_cast<AliAODv0 *>(v0obj);
    if (!v0) continue;
    // Cuts to the V0 selection in order to avoid false pairing
    if (v0->GetNProngs() > 2) continue;
    if (v0->GetNDaughters() > 2) continue;
    if (v0->GetCharge() != 0) continue;
    if (v0->GetOnFlyStatus()) continue;  // offline v0
    // Get the coordinates of the primary vertex
    Double_t xPV = fAOD->GetPrimaryVertex()->GetX();
    Double_t yPV = fAOD->GetPrimaryVertex()->GetY();
    Double_t zPV = fAOD->GetPrimaryVertex()->GetZ();
    Double_t PV[3] = {xPV, yPV, zPV};
    // Calculate decay vertex variables:
    const float point = v0->CosPointingAngle(PV);
    const float dcaV0Dau = v0->DcaV0Daughters();
    // Cut on angle between V0 vector and direct connection to primary vertex
    if (point < 0.99) continue;
    // DCA of the daughter tracks at the decay vertex
    if (dcaV0Dau > 1.5) continue;
    const float transverseRadius = v0->DecayLengthXY(PV);
    if (transverseRadius < 5.) continue;
    AliAODTrack *posTrack =
        static_cast<AliAODTrack *>(fGlobalTrackReference[v0->GetPosID()]);
    AliAODTrack *negTrack =
        static_cast<AliAODTrack *>(fGlobalTrackReference[v0->GetNegID()]);
    if (!posTrack || !negTrack) continue;
    fHistKindOfCand->Fill(19);
    // 				cout << "not the same mother" << endl;
    if (negTrack->Eta() > fEtaCut) continue;
    if (posTrack->Eta() > fEtaCut) continue;
    fHistKindOfCand->Fill(20);
    if (negTrack->Pt() < fpTCut) continue;
    if (posTrack->Pt() < fpTCut) continue;
    fHistKindOfCand->Fill(21);
    const float pnCls = posTrack->GetTPCNcls();
    const short pnFindable = posTrack->GetTPCNclsF();
    const float pratioFindable = pnCls / static_cast<float>(pnFindable);
    if (pratioFindable < fCluFindRatCut) continue;
    const float nnCls = negTrack->GetTPCNcls();
    const short nnFindable = negTrack->GetTPCNclsF();
    const float nratioFindable = nnCls / static_cast<float>(nnFindable);
    if (nratioFindable < fCluFindRatCut) continue;
    fHistKindOfCand->Fill(22);
    fHistClsDistrPosTr->Fill(posTrack->Pt(), pnCls);
    fHistClsDistrNegTr->Fill(negTrack->Pt(), nnCls);
    fHistV0LambdaInvMass->Fill(v0->MassLambda());
    fHistV0AntiLambdaInvMass->Fill(v0->MassAntiLambda());
    fHistV0K0ShortInvMass->Fill(v0->MassK0Short());
    const float v0pt = v0->Pt();
    fHistV0Pt->Fill(v0pt);
    const float armAlpha = v0->AlphaV0();
    const float armQt = v0->PtArmV0();
    fHistArmenterosPodolandski->Fill(armAlpha, armQt);
    // PtArmV0-Cut in order to select Gammas
    if (armQt > farmQtCut) continue;
    fHistKindOfCand->Fill(23);
    fHistArmenterosPodolandskiArmCut->Fill(armAlpha, armQt);
    fHistV0PhotonCandPt->Fill(v0pt);

    // MC-Particles with check if MC-Particle is Photon
    if (fIsMC) {
      AliAODInputHandler *eventHandler = dynamic_cast<AliAODInputHandler *>(
          AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
      fMCEvent = eventHandler->MCEvent();
      TClonesArray *mcarray = dynamic_cast<TClonesArray *>(
          fAOD->FindListObject(AliAODMCParticle::StdBranchName()));
      if (!mcarray) continue;
      int daugh[2] = {11, 11};  // we check whether the v0 is a photon, i.e. the
                                // daughters should be electrons
      int label = v0->MatchToMC(22, mcarray, 2, daugh);  // do the check
      if (label < 0)
        continue;  // no mc info assigned to this track - don’t use it
      AliAODMCParticle *mcParticle =
          static_cast<AliAODMCParticle *>(fMCEvent->GetTrack(label));
      if (!mcParticle) continue;
      // Check if daughters lie in acceptance
      AliAODMCParticle *mcDaug1 = static_cast<AliAODMCParticle *>(
          fMCEvent->GetTrack(mcParticle->GetDaughterLabel(0)));
      AliAODMCParticle *mcDaug2 = static_cast<AliAODMCParticle *>(
          fMCEvent->GetTrack(mcParticle->GetDaughterLabel(1)));
      if (!mcDaug1) continue;
      if (!mcDaug2) continue;
      fHistKindOfCand->Fill(24);
      if (!IsConvertedPhoton(mcDaug1, mcDaug2, fMCEvent)) continue;
      Sigma0Descendancy2(mcDaug1);
      const float mcDaug1Pt = mcDaug1->Pt();
      const float mcDaug2Pt = mcDaug2->Pt();
      fHistmcDaug1Pt->Fill(mcDaug1Pt);
      fHistmcDaug2Pt->Fill(mcDaug2Pt);
      fHistV0mcPhotonPtandArmCut->Fill(v0pt);
      fHistArmenterosPodolandskiV0mcPhotonsCut->Fill(armAlpha, armQt);
    }
  }

  Int_t iTracks(fAOD->GetNumberOfTracks());  // see how many tracks there are
                                             // in the event
  for (Int_t i(0); i < iTracks; i++) {       // loop over all these tracks
    AliAODTrack *track = static_cast<AliAODTrack *>(
        fAOD->GetTrack(i));  // get a track (type AliAODTrack) from the event
    if (!track || !track->TestFilterBit(1))
      continue;  // if we failed, skip this track
    AliMCParticle *mcParticle = nullptr;
    if (fIsMC && fMCEvent)
      mcParticle =
          static_cast<AliMCParticle *>(fMCEvent->GetTrack(track->GetLabel()));
    if (fIsMC && !mcParticle) continue;
    AliAnalysisManager *man = AliAnalysisManager::GetAnalysisManager();
    if (man) {
      AliInputEventHandler *inputHandler =
          (AliInputEventHandler *)(man->GetInputEventHandler());
      if (inputHandler) fPIDResponse = inputHandler->GetPIDResponse();
    }
  }

  // continue until all the tracks are processed
  PostData(1, fOutputList);  // stream the results the analysis of this event to
  // the output manager which will take care of writing
  // it to a file
}

float AliAnalysisTaskMyTask::GetBeta(AliAODTrack *track) {
  float beta = -999;
  double integratedTimes[9] = {-1.0, -1.0, -1.0, -1.0, -1.0,
                               -1.0, -1.0, -1.0, -1.0};
  track->GetIntegratedTimes(integratedTimes);
  const float c = 2.99792457999999984e-02;
  float p = track->P();
  float l = integratedTimes[0] * c;
  float trackT0 = fPIDResponse->GetTOFResponse().GetStartTime(p);
  float timeTOF = track->GetTOFsignal() - trackT0;
  if (timeTOF > 0) {
    beta = l / timeTOF / c;
  }
  return beta;
}

// Neue Funktion! zur Photonen erkennen die Konversion unterlaufen haben

Bool_t AliAnalysisTaskMyTask::IsConvertedPhoton(AliAODMCParticle *posDaughter,
                                                AliAODMCParticle *negDaughter,
                                                AliMCEvent *fMCEvent) {
  // Gravierender Unterschied zw. ESDs und AODs, wichtig fuer die Ueberpruefung,
  // ob e- und e+ aus Conversion (ID = 5) stammen!
  // AOD:
  // std::cout << "posDaughter ProcessCode"<<posDaughter->GetMCProcessCode()<<
  // "\n";
  // std::cout << "negDaughter ProcessCode"<<negDaughter->GetMCProcessCode()<<
  // "\n";
  // ESD:
  // std::cout << "posDaughter GetUniqueID"<<posDaughter->GetUniqueID()<< "\n";
  // std::cout << "posDaughter GetUniqueID"<<posDaughter->GetUniqueID()<< "\n";

  const AliVVertex *primVtxMC = fMCEvent->GetPrimaryVertex();
  Double_t mcProdVtxX = primVtxMC->GetX();
  Double_t mcProdVtxY = primVtxMC->GetY();
  Double_t mcProdVtxZ = primVtxMC->GetZ();

  auto *mcNegMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(negDaughter->GetMother()));
  auto *mcPosMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(posDaughter->GetMother()));
  fHistKindOfCand->Fill(0);
  Int_t pdgCodeNeg = negDaughter->PdgCode();
  Int_t pdgCodePos = posDaughter->PdgCode();
  if (!(mcPosMother == NULL || mcNegMother == NULL)) {
    fHistKindOfCand->Fill(1);
    if (posDaughter == NULL || negDaughter == NULL) {
      fHistKindOfCand->Fill(24);  // garbage
      // 				cout << "one of the daughters not
      // available"
      // <<
      // endl;
      return false;
    } else if (mcPosMother != mcNegMother ||
               (mcPosMother == mcNegMother && posDaughter->GetMother() == -1)) {
      // Not Same Mother == Combinatorial bkrg
      fHistKindOfCand->Fill(2);
      // 				cout << "not the same mother" << endl;
      if (TMath::Abs(pdgCodePos) == 11 && TMath::Abs(pdgCodeNeg) == 11) {
        fHistKindOfCand->Fill(3);  // Electron Combinatorial
        return false;
      }
      if (TMath::Abs(pdgCodePos) == 11 && TMath::Abs(pdgCodeNeg) == 11 &&
          (mcPosMother == mcNegMother && posDaughter->GetMother() == -1)) {
        fHistKindOfCand->Fill(4);  // direct Electron Combinatorial
        return false;
      }
      if (TMath::Abs(pdgCodePos) == 211 && TMath::Abs(pdgCodeNeg) == 211) {
        fHistKindOfCand->Fill(5);  // Pion Combinatorial
        return false;
      }
      if ((TMath::Abs(pdgCodePos) == 211 && TMath::Abs(pdgCodeNeg) == 2212) ||
          (TMath::Abs(pdgCodePos) == 2212 && TMath::Abs(pdgCodeNeg) == 211)) {
        fHistKindOfCand->Fill(6);  // Pion, Proton Combinatorics
        return false;
      }
      if ((TMath::Abs(pdgCodePos) == 211 && TMath::Abs(pdgCodeNeg) == 11) ||
          (TMath::Abs(pdgCodePos) == 11 && TMath::Abs(pdgCodeNeg) == 211)) {
        fHistKindOfCand->Fill(7);  // Pion, Electron Combinatorics
        return false;
      }
      if (TMath::Abs(pdgCodePos) == 321 || TMath::Abs(pdgCodeNeg) == 321) {
        fHistKindOfCand->Fill(8);  // Kaon combinatorics
        return false;
      }

    } else {
      fHistKindOfCand->Fill(9);
      // 				cout << "same mother" << endl;
      Int_t pdgCode = mcPosMother->GetPdgCode();
      // 				cout << "PDG code: " << pdgCode << endl;
      if (TMath::Abs(pdgCodePos) != 11 || TMath::Abs(pdgCodeNeg) != 11) {
        fHistKindOfCand->Fill(10);  // combinatorics from hadronic decays
        return false;
      } else if (!(pdgCodeNeg == pdgCodePos)) {
        Bool_t gammaIsPrimary = IsConversionPrimaryAOD(
            fAOD, mcPosMother, mcProdVtxX, mcProdVtxY, mcProdVtxZ);
        if (pdgCode == 111) {
          fHistKindOfCand->Fill(11);  // pi0 Dalitz
          return false;
        } else if (pdgCode == 221) {
          fHistKindOfCand->Fill(12);  // eta Dalitz
          return false;
        } else if (!(negDaughter->GetMCProcessCode() != 5 ||
                     posDaughter->GetMCProcessCode() != 5)) {
          if (pdgCode == 22 && gammaIsPrimary) {
            fHistKindOfCand->Fill(13);  // primary photons
            return true;
          } else if (pdgCode == 22) {
            fHistKindOfCand->Fill(14);  // secondary photons
            return false;
          }
        } else {
          fHistKindOfCand->Fill(15);  // garbage
          return false;
        }
      } else {
        fHistKindOfCand->Fill(16);  // garbage
        return false;
      }
      fHistKindOfCand->Fill(11);
      return false;
    }
    fHistKindOfCand->Fill(12);
    return false;
  }
  return false;
}

//_________________________________________________________________________
void AliAnalysisTaskMyTask::IsConvertedPhotonDaughterIsPhysPrimaryCheck(
    AliAODMCParticle *posDaughter, AliAODMCParticle *negDaughter) {
  auto *mcNegMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(negDaughter->GetMother()));
  auto *mcPosMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(posDaughter->GetMother()));

  Int_t pdgCodeNeg = negDaughter->PdgCode();
  Int_t pdgCodePos = posDaughter->PdgCode();

  if (!(mcPosMother == NULL || mcNegMother == NULL)) {
    if (posDaughter == NULL || negDaughter == NULL) {
      // garbage
      // 				cout << "one of the daughters not
      // available"
      // <<
      // endl;
    } else if (mcPosMother != mcNegMother ||
               (mcPosMother == mcNegMother && posDaughter->GetMother() == -1)) {
      // Not Same Mother == Combinatorial bkrg
      // 				cout << "not the same mother" << endl;
    } else {
      // 				cout << "same mother" << endl;
      Int_t pdgCode = mcPosMother->GetPdgCode();
      // 				cout << "PDG code: " << pdgCode << endl;
      if (TMath::Abs(pdgCodePos) != 11 || TMath::Abs(pdgCodeNeg) != 11) {
        // combinatorics from hadronic decays
      } else if (!(pdgCodeNeg == pdgCodePos)) {
        if (!(negDaughter->GetMCProcessCode() != 5 ||
              posDaughter->GetMCProcessCode() != 5)) {
          Bool_t fIsPrimary = mcPosMother->IsPhysicalPrimary();
          if (pdgCode == 22 && fIsPrimary) {
            // primary photons
            fHistReconstrmcPhotonPtIsPhysPrim->Fill(mcPosMother->Pt());
          } else if (pdgCode == 22) {
            // photons without vertex correlation, and checking for cascades
          }
        } else {
          // garbage

        }
      } else {
        // garbage
      }


    }

  }

}

//_________________________________________________________________________

Bool_t AliAnalysisTaskMyTask::IsConversionPrimaryAOD(
    AliVEvent *event, AliAODMCParticle *AODMCParticle, Double_t prodVtxX,
    Double_t prodVtxY, Double_t prodVtxZ) {
  TClonesArray *AODMCTrackArray = dynamic_cast<TClonesArray *>(
      fAOD->FindListObject(AliAODMCParticle::StdBranchName()));
  fHistKindOfPrim->Fill(1);
  if (AODMCTrackArray == NULL) return kFALSE;
  fHistKindOfPrim->Fill(2);
  AliAODMCParticle *currentParticle = AODMCParticle;
  if (TMath::Abs(currentParticle->GetPdgCode()) == 11) {
    if (currentParticle->GetMother() != -1) {
      AliAODMCParticle *particleMother = static_cast<AliAODMCParticle *>(
          AODMCTrackArray->At(currentParticle->GetMother()));
      if (particleMother) {
        if (TMath::Abs(particleMother->GetPdgCode()) == 22)
          currentParticle = particleMother;
      }
    }
  }
  if (currentParticle->GetMother() > -1) {
    Double_t deltaX = currentParticle->Xv() - prodVtxX;
    Double_t deltaY = currentParticle->Yv() - prodVtxY;
    Double_t deltaZ = currentParticle->Zv() - prodVtxZ;

    // Double_t realRadius2D = TMath::Sqrt(deltaX*deltaX+deltaY*deltaY);
    Double_t realRadius3D =
        TMath::Sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

    Bool_t dalitzCand = kFALSE;

    AliAODMCParticle *firstmother = static_cast<AliAODMCParticle *>(
        AODMCTrackArray->At(currentParticle->GetMother()));
    if (!firstmother) return kFALSE;
    fHistKindOfPrim->Fill(3);
    Int_t pdgCodeFirstMother = firstmother->GetPdgCode();
    Bool_t intDecay = kFALSE;
    if (pdgCodeFirstMother == 111 || pdgCodeFirstMother == 221)
      intDecay = kTRUE;
    if (intDecay && TMath::Abs(currentParticle->GetPdgCode()) == 11) {
      dalitzCand = kTRUE;
      //       cout << "dalitz candidate found" << endl;
    }

    Long_t source = currentParticle->GetMother();
    Bool_t foundExcludedPart = kFALSE;
    Bool_t foundShower = kFALSE;
    Int_t pdgCodeMotherPrev = 0;
    Int_t pdgCodeMotherPPrevMother = 0;
    Int_t depth = 0;
    if (dalitzCand || realRadius3D < fSecProdBoundary) {
      //       if (currentParticle->GetPdgCode() == 22){
      //         cout << endl << endl << "new particle: " << eventpos <<endl;
      //         cout << currentParticle->GetPdgCode() << "\t" <<
      //         currentParticle->R() << "\t" << realRadius2D << "\t" <<
      //         realRadius3D << endl;
      //       }
      while (depth < 20) {
        AliAODMCParticle *mother =
            static_cast<AliAODMCParticle *>(AODMCTrackArray->At(source));
        source = mother->GetMother();
        //         if (currentParticle->GetPdgCode() == 22)cout <<
        //         "eventposition: "<< source << endl;
        Int_t pdgCodeMother = mother->GetPdgCode();
        //         if (currentParticle->GetPdgCode() == 22)cout << "Previous
        //         mothers: " << pdgCodeMother << "\t"<< pdgCodeMotherPrev<<
        //         "\t" << pdgCodeMotherPPrevMother << endl;
        if (pdgCodeMother == pdgCodeMotherPrev &&
            pdgCodeMother == pdgCodeMotherPPrevMother)
          depth = 20;
        if (TMath::Abs(pdgCodeMother) == 11 &&
            TMath::Abs(pdgCodeMotherPrev) == 22 &&
            TMath::Abs(pdgCodeMotherPPrevMother) == 11) {
          foundShower = kTRUE;
          depth = 20;
        }
        if (TMath::Abs(pdgCodeMother) == 22 &&
            TMath::Abs(pdgCodeMotherPrev) == 11 &&
            TMath::Abs(pdgCodeMotherPPrevMother) == 22) {
          foundShower = kTRUE;
          depth = 20;
        }

        // particles to be excluded:
        // K0s      - 310
        // K0l      - 130
        // K+/-     - 321
        // Lambda   - 3122
        // Sigma0   - 3212
        // Sigma+/- - 3222, 3112
        // Cascades - 3322, 3312
        if (TMath::Abs(pdgCodeMother) == 310 ||
            TMath::Abs(pdgCodeMother) == 130 ||
            TMath::Abs(pdgCodeMother) == 321 ||
            TMath::Abs(pdgCodeMother) == 3122 ||
            TMath::Abs(pdgCodeMother) == 3212 ||
            TMath::Abs(pdgCodeMother) == 3222 ||
            TMath::Abs(pdgCodeMother) == 3112 ||
            TMath::Abs(pdgCodeMother) == 3322 ||
            TMath::Abs(pdgCodeMother) == 3312) {
          foundExcludedPart = kTRUE;
        }
        //      if (currentParticle->GetPdgCode() == 22)cout <<
        //      mother->GetPdgCode() << "\t" <<  source << "\t" <<
        //      foundExcludedPart<< endl;
        pdgCodeMotherPPrevMother = pdgCodeMotherPrev;
        pdgCodeMotherPrev = pdgCodeMother;
        if (source == -1) depth = 20;

        //      if (currentParticle->GetPdgCode() == 22)cout << depth << endl;
        depth++;
      }
    }
    if (foundExcludedPart) {
      //      if (currentParticle->GetPdgCode() == 22)cout << "This is
      //      definitely a secondary, manually excluded" << endl;
      fHistKindOfPrim->Fill(4);
      return kFALSE;
    } else if (dalitzCand && realRadius3D < fSecProdBoundary) {
      //      if (currentParticle->GetPdgCode() == 22)cout << "This was a decay
      //      via a virtual photon" << endl;
      fHistKindOfPrim->Fill(5);
      return kTRUE;
    } else if (foundShower) {
      //      if (currentParticle->GetPdgCode() == 22)cout << "This is a shower"
      //      << endl;
      fHistKindOfPrim->Fill(6);
      return kFALSE;
    } else if (realRadius3D >= fSecProdBoundary) {
      //      cout << "This is a secondary, too large production radius" <<
      //      endl;
      fHistKindOfPrim->Fill(7);
      return kFALSE;
    }
  }
  fHistKindOfPrim->Fill(8);
  return kTRUE;
}

//_________________________________________________________________________
void AliAnalysisTaskMyTask::Sigma0Descendancy(AliAODMCParticle *Daughter) {
  auto *mcPosMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(Daughter->GetMother()));
  auto *mcGrandMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(mcPosMother->GetMother()));
  if (!mcGrandMother) {
  } else {
    Int_t pdgCode = mcGrandMother->PdgCode();
    const float mcPosMotherPt = mcPosMother->Pt();
    fHistPDGsOfMothToPhotons->Fill(pdgCode, mcGrandMother->Pt());
    if (pdgCode != 3212) {
      fHistNoSigma0Phi->Fill(mcPosMother->Phi());
      fHistNoSigma0Theta->Fill(mcPosMother->Theta());
      fHistNoSigma0Eta->Fill(mcPosMother->Eta());
      fHistNoSigma0Pt->Fill(mcPosMotherPt);
      fHistNoSigma0P->Fill(mcPosMother->P());
      fHistNoSigma0E->Fill(mcPosMother->E());
      fHistNoSigma0Mass2->Fill(mcPosMother->GetCalcMass());
      fHistNoSigma0Tv->Fill(mcPosMother->Tv());
      fHistNoSigma0OneOverPt->Fill(mcPosMother->OneOverPt());
      fHistNoSigma0PhiVsPt->Fill(mcPosMotherPt, mcPosMother->Phi());
      fHistNoSigma0ThetaVsPt->Fill(mcPosMotherPt, mcPosMother->Theta());
      fHistNoSigma0EtaVsPt->Fill(mcPosMotherPt, mcPosMother->Eta());
      fHistNoSigma0EVsPt->Fill(mcPosMotherPt, mcPosMother->E());
      fHistNoSigma0TvVsPt->Fill(mcPosMotherPt, mcPosMother->Tv());
    } else {
      fHistSigma0Phi->Fill(mcPosMother->Phi());
      fHistSigma0Theta->Fill(mcPosMother->Theta());
      fHistSigma0Eta->Fill(mcPosMother->Eta());
      fHistSigma0Pt->Fill(mcPosMotherPt);
      fHistSigma0P->Fill(mcPosMother->P());
      fHistSigma0E->Fill(mcPosMother->E());
      fHistSigma0Mass2->Fill(mcPosMother->GetCalcMass());
      fHistSigma0Tv->Fill(mcPosMother->Tv());
      fHistSigma0OneOverPt->Fill(mcPosMother->OneOverPt());
      fHistSigma0PhiVsPt->Fill(mcPosMotherPt, mcPosMother->Phi());
      fHistSigma0ThetaVsPt->Fill(mcPosMotherPt, mcPosMother->Theta());
      fHistSigma0EtaVsPt->Fill(mcPosMotherPt, mcPosMother->Eta());
      fHistSigma0EVsPt->Fill(mcPosMotherPt, mcPosMother->E());
      fHistSigma0TvVsPt->Fill(mcPosMotherPt, mcPosMother->Tv());
    }
  }
}

//_________________________________________________________________________
void AliAnalysisTaskMyTask::Sigma0Descendancy2(AliAODMCParticle *Daughter2) {
  auto *mcPosMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(Daughter2->GetMother()));
  auto *mcGrandMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(mcPosMother->GetMother()));
  if (!mcGrandMother) {
  } else {
    Int_t pdgCode = mcGrandMother->PdgCode();
    const float mcPosMotherPt = mcPosMother->Pt();
    fHist2PDGsOfMothToPhotons->Fill(pdgCode, mcGrandMother->Pt());
    if (pdgCode != 3212) {
      fHist2NoSigma0Phi->Fill(mcPosMother->Phi());
      fHist2NoSigma0Theta->Fill(mcPosMother->Theta());
      fHist2NoSigma0Eta->Fill(mcPosMother->Eta());
      fHist2NoSigma0Pt->Fill(mcPosMotherPt);
      fHist2NoSigma0P->Fill(mcPosMother->P());
      fHist2NoSigma0E->Fill(mcPosMother->E());
      fHist2NoSigma0Mass2->Fill(mcPosMother->GetCalcMass());
      fHist2NoSigma0Tv->Fill(mcPosMother->Tv());
      fHist2NoSigma0OneOverPt->Fill(mcPosMother->OneOverPt());
      fHist2NoSigma0PhiVsPt->Fill(mcPosMotherPt, mcPosMother->Phi());
      fHist2NoSigma0ThetaVsPt->Fill(mcPosMotherPt, mcPosMother->Theta());
      fHist2NoSigma0EtaVsPt->Fill(mcPosMotherPt, mcPosMother->Eta());
      fHist2NoSigma0EVsPt->Fill(mcPosMotherPt, mcPosMother->E());
      fHist2NoSigma0TvVsPt->Fill(mcPosMotherPt, mcPosMother->Tv());
    } else {
      fHist2Sigma0Phi->Fill(mcPosMother->Phi());
      fHist2Sigma0Theta->Fill(mcPosMother->Theta());
      fHist2Sigma0Eta->Fill(mcPosMother->Eta());
      fHist2Sigma0Pt->Fill(mcPosMotherPt);
      fHist2Sigma0P->Fill(mcPosMother->P());
      fHist2Sigma0E->Fill(mcPosMother->E());
      fHist2Sigma0Mass2->Fill(mcPosMother->GetCalcMass());
      fHist2Sigma0Tv->Fill(mcPosMother->Tv());
      fHist2Sigma0OneOverPt->Fill(mcPosMother->OneOverPt());
      fHist2Sigma0PhiVsPt->Fill(mcPosMotherPt, mcPosMother->Phi());
      fHist2Sigma0ThetaVsPt->Fill(mcPosMotherPt, mcPosMother->Theta());
      fHist2Sigma0EtaVsPt->Fill(mcPosMotherPt, mcPosMother->Eta());
      fHist2Sigma0EVsPt->Fill(mcPosMotherPt, mcPosMother->E());
      fHist2Sigma0TvVsPt->Fill(mcPosMotherPt, mcPosMother->Tv());
    }
  }
}

//_________________________________________________________________________
void AliAnalysisTaskMyTask::Sigma0DescendancyAll(
    AliAODMCParticle *DaughterAll) {
  auto *mcPosMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(DaughterAll->GetMother()));
  if (!mcPosMother) return;
  auto *mcGrandMother = static_cast<AliAODMCParticle *>(
      fMCEvent->GetTrack(mcPosMother->GetMother()));
  if (!mcGrandMother) {
  } else {
    Int_t pdgCode = mcGrandMother->PdgCode();
    const float mcPosMotherPt = mcPosMother->Pt();
    fHistAllPDGsOfMothToPhotons->Fill(pdgCode, mcGrandMother->Pt());
    if (pdgCode != 3212) {
      fHistAllNoSigma0Phi->Fill(mcPosMother->Phi());
      fHistAllNoSigma0Theta->Fill(mcPosMother->Theta());
      fHistAllNoSigma0Eta->Fill(mcPosMother->Eta());
      fHistAllNoSigma0Pt->Fill(mcPosMotherPt);
      fHistAllNoSigma0P->Fill(mcPosMother->P());
      fHistAllNoSigma0E->Fill(mcPosMother->E());
      fHistAllNoSigma0Mass2->Fill(mcPosMother->GetCalcMass());
      fHistAllNoSigma0Tv->Fill(mcPosMother->Tv());
      fHistAllNoSigma0OneOverPt->Fill(mcPosMother->OneOverPt());
      fHistAllNoSigma0PhiVsPt->Fill(mcPosMotherPt, mcPosMother->Phi());
      fHistAllNoSigma0ThetaVsPt->Fill(mcPosMotherPt, mcPosMother->Theta());
      fHistAllNoSigma0EtaVsPt->Fill(mcPosMotherPt, mcPosMother->Eta());
      fHistAllNoSigma0EVsPt->Fill(mcPosMotherPt, mcPosMother->E());
      fHistAllNoSigma0TvVsPt->Fill(mcPosMotherPt, mcPosMother->Tv());
    } else {
      fHistAllSigma0Phi->Fill(mcPosMother->Phi());
      fHistAllSigma0Theta->Fill(mcPosMother->Theta());
      fHistAllSigma0Eta->Fill(mcPosMother->Eta());
      fHistAllSigma0Pt->Fill(mcPosMotherPt);
      fHistAllSigma0P->Fill(mcPosMother->P());
      fHistAllSigma0E->Fill(mcPosMother->E());
      fHistAllSigma0Mass2->Fill(mcPosMother->GetCalcMass());
      fHistAllSigma0Tv->Fill(mcPosMother->Tv());
      fHistAllSigma0OneOverPt->Fill(mcPosMother->OneOverPt());
      fHistAllSigma0PhiVsPt->Fill(mcPosMotherPt, mcPosMother->Phi());
      fHistAllSigma0ThetaVsPt->Fill(mcPosMotherPt, mcPosMother->Theta());
      fHistAllSigma0EtaVsPt->Fill(mcPosMotherPt, mcPosMother->Eta());
      fHistAllSigma0EVsPt->Fill(mcPosMotherPt, mcPosMother->E());
      fHistAllSigma0TvVsPt->Fill(mcPosMotherPt, mcPosMother->Tv());
    }
  }
}

//____________________________________________________________________________________________________
void AliAnalysisTaskMyTask::StoreGlobalTrackReference() {
  // This method was inherited form H. Beck & O. Arnold analysis
  // Stores the pointer to the global track
  // Modified to work with vectors

  fGlobalTrackReference.clear();
  fGlobalTrackReference.resize(1000);
  AliAODEvent *aodEvent = static_cast<AliAODEvent *>(fInputEvent);
  for (int iTrack = 0; iTrack < aodEvent->GetNumberOfTracks(); ++iTrack) {
    AliAODTrack *track = static_cast<AliAODTrack *>(aodEvent->GetTrack(iTrack));
    if (!track) continue;

    // Check that the id is positive
    if (track->GetID() < 0) continue;

    // Check id is not too big for buffer
    if (track->GetID() >= static_cast<int>(fGlobalTrackReference.size()))
      fGlobalTrackReference.resize(track->GetID() + 1);

    // Warn if we overwrite a track
    auto *trackRef = fGlobalTrackReference[track->GetID()];
    if (trackRef) {
      // Seems like there are FilterMap 0 tracks
      // that have zero TPCNcls, don't store these!
      if ((!track->GetFilterMap()) && (!track->GetTPCNcls())) continue;

      // Imagine the other way around, the zero map zero clusters track
      // is stored and the good one wants to be added. We ommit the warning
      // and just overwrite the 'bad' track
      if (fGlobalTrackReference[track->GetID()]->GetFilterMap() ||
          fGlobalTrackReference[track->GetID()]->GetTPCNcls()) {
        // If we come here, there's a problem
        std::cout << "Warning! global track info already there! ";
        std::cout << "TPCNcls track1 "
                  << (fGlobalTrackReference[track->GetID()])->GetTPCNcls()
                  << " track2 " << track->GetTPCNcls();
        std::cout << " FilterMap track1 "
                  << (fGlobalTrackReference[track->GetID()])->GetFilterMap()
                  << " track 2" << track->GetFilterMap() << "\n";
        fGlobalTrackReference[track->GetID()] = nullptr;
      }
    }  // Two tracks same id

    // Assign the pointer
    (fGlobalTrackReference.at(track->GetID())) = track;
  }
}

//_____________________________________________________________________________
void AliAnalysisTaskMyTask::Terminate(Option_t *) {
  // terminate
  // called at the END of the analysis (when all events are processed)
}
//_____________________________________________________________________________
