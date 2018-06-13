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
      fHistReconstrmcPhotonPtCutPt(nullptr),
      fHistReconstrmcPhotonPtNoDetCut(nullptr),
      fHistArmenterosPodolandskiV0mcPhotons(nullptr),
      fHistV0PhotonCandPt(nullptr),
      fHistV0Pt(nullptr),
      fHistmcDaug1Pt(nullptr),
      fHistDetAccmcDaug1Pt(nullptr),
      fHistmcDaug2Pt(nullptr),
      fHistDetAccmcDaug2Pt(nullptr),
      fHistAllPhotons(nullptr),
      fHistArmenterosPodolandskiArmCut(nullptr),
      fHistV0mcPhotonPtandArmCut(nullptr),
      fHistV0mcPhotonPtCut(nullptr),
      fHistArmenterosPodolandskiV0mcPhotonsCut(nullptr),
      fHistReconstrmcPhotonPtMoCh(nullptr),
      fEventCuts(nullptr),
      fHistKindOfCand(nullptr),
      FillMCHistograms(nullptr),
      fHistAllPhotons2(nullptr),
      fHistKindOfPrim(nullptr) {
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
      fHistReconstrmcPhotonPtCutPt(nullptr),
      fHistReconstrmcPhotonPtNoDetCut(nullptr),
      fHistArmenterosPodolandskiV0mcPhotons(nullptr),
      fHistV0PhotonCandPt(nullptr),
      fHistV0Pt(nullptr),
      fHistmcDaug1Pt(nullptr),
      fHistDetAccmcDaug1Pt(nullptr),
      fHistmcDaug2Pt(nullptr),
      fHistDetAccmcDaug2Pt(nullptr),
      fHistAllPhotons(nullptr),
      fHistArmenterosPodolandskiArmCut(nullptr),
      fHistV0mcPhotonPtandArmCut(nullptr),
      fHistV0mcPhotonPtCut(nullptr),
      fHistArmenterosPodolandskiV0mcPhotonsCut(nullptr),
      fHistReconstrmcPhotonPtMoCh(nullptr),
      fEventCuts(nullptr),
      fHistKindOfCand(nullptr),
      FillMCHistograms(nullptr),
      fHistAllPhotons2(nullptr),
      fHistKindOfPrim(nullptr) {
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

  fHistReconstrmcPhotonPtMoCh = new TH1F(
      "fHistReconstrmcPhotonPtMoCh", "fHistReconstrmcPhotonPtMoCh", 200, 0, 10);
  fHistReconstrmcPhotonPtMoCh->SetTitle(
      "fHistReconstrmcPhotonPtMoCh;momentum p;counts N");
  fOutputList->Add(fHistReconstrmcPhotonPtMoCh);

  // fFillMCHistograms = new TH1F(
  //            "fFillMCHistograms", "fFillMCHistograms", 200, 0, 10);
  //        fFillMCHistograms->SetTitle(
  //            "fFillMCHistograms;momentum p;counts N");
  //        fOutputList->Add(fFillMCHistograms);

  fHistV0PhotonCandPt =
      new TH1F("fHistV0PhotonCandPt", "fHistV0PhotonCandPt", 200, 0, 10);
  fHistV0PhotonCandPt->SetTitle("fHistV0PhotonCandPt;momentum p;counts N");
  fOutputList->Add(fHistV0PhotonCandPt);

  fHistV0mcPhotonPtCut =
      new TH1F("fHistV0mcPhotonPtCut", "fHistV0mcPhotonPtCut", 200, 0, 10);
  fHistV0mcPhotonPtCut->SetTitle("fHistV0mcPhotonPtCut;momentum p;counts N");
  fOutputList->Add(fHistV0mcPhotonPtCut);

  fHistArmenterosPodolandskiV0mcPhotonsCut = new TH2F(
      "fHistArmenterosPodolandskiV0mcPhotonsCut",
      " ; #alpha; #it{q}_{T} p#pi [GeV/#it{c}]", 500, -1, 1, 500, 0, farmQtCut);
  fOutputList->Add(fHistArmenterosPodolandskiV0mcPhotonsCut);

  fHistmcDaug2Pt = new TH1F("fHistmcDaug2Pt", "fHistmcDaug2Pt", 200, 0, 10);
  fHistmcDaug2Pt->SetTitle("fHistmcDaug2Pt;momentum p;counts N");
  fOutputList->Add(fHistmcDaug2Pt);

  fHistDetAccmcDaug2Pt =
      new TH1F("fHistDetAccmcDaug2Pt", "fHistDetAccmcDaug2Pt", 200, 0, 10);
  fHistDetAccmcDaug2Pt->SetTitle("fHistDetAccmcDaug2Pt;momentum p;counts N");
  fOutputList->Add(fHistDetAccmcDaug2Pt);

  fHistmcDaug1Pt = new TH1F("fHistmcDaug1Pt", "fHistmcDaug1Pt", 200, 0, 10);
  fHistmcDaug1Pt->SetTitle("fHistmcDaug1Pt;momentum p;counts N");
  fOutputList->Add(fHistmcDaug1Pt);

  fHistDetAccmcDaug1Pt =
      new TH1F("fHistDetAccmcDaug1Pt", "fHistDetAccmcDaug1Pt", 200, 0, 10);
  fHistDetAccmcDaug1Pt->SetTitle("fHistDetAccmcDaug1Pt;momentum p;counts N");
  fOutputList->Add(fHistDetAccmcDaug1Pt);

  fHistV0Pt = new TH1F("fHistV0Pt", "fHistV0Pt", 200, 0, 10);
  fHistV0Pt->SetTitle(
      "Pt Distribution of accepted V0s;transverse momentum Pt;counts N");
  fOutputList->Add(fHistV0Pt);

  fHistReconstrmcPhotonPtCutPt =
      new TH1F("fHistReconstrmcPhotonPtCutPt", "fHistReconstrmcPhotonPtCutPt",
               200, 0, 10);
  fHistReconstrmcPhotonPtCutPt->SetTitle(
      "Pt Distribution of accepted V0s;transverse momentum Pt;counts N");
  fOutputList->Add(fHistReconstrmcPhotonPtCutPt);

  fHistReconstrmcPhotonPtNoDetCut =
      new TH1F("fHistReconstrmcPhotonPtNoDetCut",
               "fHistReconstrmcPhotonPtNoDetCut", 200, 0, 10);
  fHistReconstrmcPhotonPtNoDetCut->SetTitle(
      "Pt Distribution of accepted V0s;transverse momentum Pt;counts N");
  fOutputList->Add(fHistReconstrmcPhotonPtNoDetCut);

  fHistReconstrmcPhotonPt = new TH1F("fHistReconstrmcPhotonPt",
                                     "fHistReconstrmcPhotonPt", 200, 0, 10);
  fHistReconstrmcPhotonPt->SetTitle(
      "Pt Distribution of accepted V0s;transverse momentum Pt;counts N");
  fOutputList->Add(fHistReconstrmcPhotonPt);

  fHistV0mcPhotonPtandArmCut = new TH1F(
      "fHistV0mcPhotonPtandArmCut", "fHistV0mcPhotonPtandArmCut", 200, 0, 10);
  fHistV0mcPhotonPtandArmCut->SetTitle(
      "MCTrueV0Photons;transverse momentum pt;counts N");
  fOutputList->Add(fHistV0mcPhotonPtandArmCut);

  fHistClsDistrPosTr = new TH2F("fHistClsDistrPosTr", "fHistClsDistrPosTr", 200,
                                0, 1.5, 200, 0, 200);
  fHistClsDistrPosTr->SetTitle("Cluster-Distribution;pt;Clusters");
  fOutputList->Add(fHistClsDistrPosTr);

  fHistClsDistrNegTr = new TH2F("fHistClsDistrNegTr", "fHistClsDistrNegTr", 200,
                                0, 1.5, 200, 0, 200);
  fHistClsDistrNegTr->SetTitle("Cluster-Distribution;pt;Clusters");
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
  fHistKindOfPrim->GetXaxis()->SetBinLabel(21, "|Eta| < 0.8");
  fHistKindOfPrim->GetXaxis()->SetBinLabel(22, "Pt > 0.1 MeV");
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
  fHistKindOfCand->GetXaxis()->SetBinLabel(21, "|Eta| < 0.8");
  fHistKindOfCand->GetXaxis()->SetBinLabel(22, "Pt > 0.1 MeV");
  fHistKindOfCand->GetXaxis()->SetBinLabel(23, "Findable Cluster Ratio > 80%");
  fHistKindOfCand->GetXaxis()->SetBinLabel(24, "ArmQt < 0.3");
  fHistKindOfCand->GetXaxis()->SetBinLabel(25, "Daughters Exit");
  fOutputList->Add(fHistKindOfCand);

  fHistV0LambdaInvMass =
      new TH1F("fHistV0LambdaInvMass", "fHistV0LambdaInvMass", 200, 0, 1.5);
  fHistV0LambdaInvMass->SetTitle(
      "Invariantmass-Distribution Lambda;m*m;Counts");
  fOutputList->Add(fHistV0LambdaInvMass);

  fHistV0AntiLambdaInvMass = new TH1F("fHistV0AntiLambdaInvMass",
                                      "fHistV0AntiLambdaInvMass", 200, 0, 1.5);
  fHistV0AntiLambdaInvMass->SetTitle(
      "Invariantmass-Distribution AntiLambda;m*m;Counts");
  fOutputList->Add(fHistV0AntiLambdaInvMass);

  fHistV0K0ShortInvMass =
      new TH1F("fHistV0K0ShortInvMass", "fHistV0K0ShortInvMass", 200, 0, 1.5);
  fHistV0K0ShortInvMass->SetTitle(
      "Invariantmass-Distribution K0Short;m*m;Counts");
  fOutputList->Add(fHistV0K0ShortInvMass);

  fHistPhotonPt = new TH1F("fHistPhotonPt",
                           "; #it{p}_{T} (GeV/#it{c}); Entries", 100, 0, 10);
  fOutputList->Add(fHistPhotonPt);

  fHistAllPhotons = new TH1F("fHistAllPhotons",
                             "; #it{p}_{T} (GeV/#it{c}); Entries", 100, 0, 10);
  fOutputList->Add(fHistAllPhotons);

  fHistAllPhotons2 = new TH1F("fHistAllPhotons2",
                              "; #it{p}_{T} (GeV/#it{c}); Entries", 100, 0, 10);
  fOutputList->Add(fHistAllPhotons2);

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

  // Get all Photons

  AliMCEvent *fMC = nullptr;
  if (fIsMC) {
    AliAODInputHandler *eventHandler = dynamic_cast<AliAODInputHandler *>(
        AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());

    fMC = eventHandler->MCEvent();

    for (int iPart = 1; iPart < (fMC->GetNumberOfTracks()); iPart++) {
      AliAODMCParticle *particle = (AliAODMCParticle *)fMC->GetTrack(iPart);
      fHistKindOfPrim->Fill(10);
      if (!particle) continue;
      fHistKindOfPrim->Fill(11);
      if (!(particle->IsPhysicalPrimary())) continue;
      fHistKindOfPrim->Fill(12);
      if (std::abs(particle->Eta()) > fEtaCut) continue;
      fHistKindOfPrim->Fill(13);
      if (particle->E() < fECut) continue;
      fHistKindOfPrim->Fill(14);
      if (particle->GetPdgCode() != 22) continue;
      fHistKindOfPrim->Fill(15);
      AliAODMCParticle *firstDaughter = static_cast<AliAODMCParticle *>(
          fMC->GetTrack(particle->GetFirstDaughter()));
      AliAODMCParticle *lastDaughter = static_cast<AliAODMCParticle *>(
          fMC->GetTrack(particle->GetLastDaughter()));
      if (!firstDaughter) continue;
      if (!lastDaughter) continue;
      fHistKindOfPrim->Fill(16);
      if (firstDaughter->Eta() > fEtaCut) continue;
      if (lastDaughter->Eta() > fEtaCut) continue;
      fHistKindOfPrim->Fill(17);
      if (firstDaughter->Pt() < fpTCut) continue;
      if (lastDaughter->Pt() < fpTCut) continue;
      fHistKindOfPrim->Fill(18);
      fHistAllPhotons->Fill(particle->Pt());
    }
  }

  if (!fAOD) return;

  // Event cuts - check whether the event is good for analysis
  if (!fEventCuts2.AcceptEvent(fAOD)) {
    PostData(1, fOutputList);
    return;
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

        if (!IsConvertedPhoton(posDaughter, negDaughter, fMCEvent)) continue;

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
    if (fIsMC && fMC)
      mcParticle =
          static_cast<AliMCParticle *>(fMC->GetTrack(track->GetLabel()));
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
      // Not Same Mother == Combinatorial Bck
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
