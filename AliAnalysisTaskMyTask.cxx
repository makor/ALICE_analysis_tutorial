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
#include "AliAODTrack.h"
#include "AliAODInputHandler.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskMyTask.h"
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
      fV0Reader(nullptr),
      fV0ReaderName("NoInit"),
      fReaderGammas(nullptr),
      fGlobalTrackReference(),
      fOutputList(nullptr),
      fHistPTPCKaon(nullptr),
      fHistPTOFKaon(nullptr),
      fHistPTPCElectron(nullptr),
      fHistPTOFElectron(nullptr),
      fHistPBetaPion(nullptr),
      fHistNSigAddElectron(nullptr),
      fHistPt(nullptr),
      fHistPtvertexZ(nullptr),
      fHistPtcentrality(nullptr),
      fHistPt2D(nullptr),
      fPIDResponse(nullptr),
      fHistTPC(nullptr),
      fHistPionPt(nullptr),
      fHistPionPsdRap(nullptr),
      fHistPionAzi(nullptr),
      fHistPTPCPion(nullptr),
      fHistPTOFPion(nullptr),
      fHistPBetaTOFPion(nullptr),
      fHistPBetaTPCPion(nullptr),
      fHistNSigTOFPion(nullptr),
      fHistNSigTPCPion(nullptr),
      fHistNSigTOFKaon(nullptr),
      fHistNSigTPCKaon(nullptr),
      fHistNSigTOFProton(nullptr),
      fHistNSigTPCProton(nullptr),
      fHistNSigTOFElectron(nullptr),
      fHistNSigTPCElectron(nullptr),
      fHistNSigAddProton(nullptr),
      fHistSigSelectedProtonP(nullptr),
      fHist3SigSelectedProtonP(nullptr),
      fHistSigSelectedElectronP(nullptr),
      fHist3SigSelectedElectronP(nullptr),
      fHistNSigAddPion(nullptr),
      fHistSigSelectedPionP(nullptr),
      fHist3SigSelectedPionP(nullptr),
      fHistNSigAddKaon(nullptr),
      fHistSigSelectedKaonP(nullptr),
      fHist3SigSelectedKaonP(nullptr),
      fismc(kFALSE),
      fHistPBetaProton(nullptr),
      fHistPBetaElectron(nullptr),
      fHistPBetaKaon(nullptr),
      fHistPTPCPion2(nullptr),
      fHistPTOFPion2(nullptr),
      fHistPTPCProton(nullptr),
      fHistPTOFProton(nullptr),
      /*TEST(nullptr),*/ fHistPTOF3SigKaon(nullptr),
      fHistPTPC3SigKaon(nullptr),
      fHistPKaon(nullptr),
      /*fHistSum_PKaon(nullptr),*/ fHistTOF(nullptr),
      fHistBeta(nullptr),
      fHistMCall(nullptr),
      fHistAllSpeciesKaon(nullptr),
      fHistPureKaon(nullptr),
      fHistAllPureKaon(nullptr),
      fHistPhotonPt(nullptr),
      fHistArmenterosPodolandski(nullptr) {
  // default constructor, don't allocate memory here!
  // this is used by root for IO purposes, it needs to remain empty
}
//_____________________________________________________________________________
AliAnalysisTaskMyTask::AliAnalysisTaskMyTask(const char *name)
    : AliAnalysisTaskSE(name),
      fAOD(nullptr),
      fV0Reader(nullptr),
      fV0ReaderName("NoInit"),
      fReaderGammas(nullptr),
      fGlobalTrackReference(),
      fOutputList(nullptr),
      fHistPTPCKaon(nullptr),
      fHistPTOFKaon(nullptr),
      fHistPTPCElectron(nullptr),
      fHistPTOFElectron(nullptr),
      fHistPBetaPion(nullptr),
      fHistNSigAddElectron(nullptr),
      fHistPt(nullptr),
      fHistPtvertexZ(nullptr),
      fHistPtcentrality(nullptr),
      fHistPt2D(nullptr),
      fPIDResponse(nullptr),
      fHistTPC(nullptr),
      fHistPionPt(nullptr),
      fHistPionPsdRap(nullptr),
      fHistPionAzi(nullptr),
      fHistPTPCPion(nullptr),
      fHistPTOFPion(nullptr),
      fHistPBetaTOFPion(nullptr),
      fHistPBetaTPCPion(nullptr),
      fHistNSigTOFPion(nullptr),
      fHistNSigTPCPion(nullptr),
      fHistNSigTOFKaon(nullptr),
      fHistNSigTPCKaon(nullptr),
      fHistNSigTOFProton(nullptr),
      fHistNSigTPCProton(nullptr),
      fHistNSigTOFElectron(nullptr),
      fHistNSigTPCElectron(nullptr),
      fHistNSigAddProton(nullptr),
      fHistSigSelectedProtonP(nullptr),
      fHist3SigSelectedProtonP(nullptr),
      fHistSigSelectedElectronP(nullptr),
      fHist3SigSelectedElectronP(nullptr),
      fHistNSigAddPion(nullptr),
      fHistSigSelectedPionP(nullptr),
      fHist3SigSelectedPionP(nullptr),
      fHistNSigAddKaon(nullptr),
      fHistSigSelectedKaonP(nullptr),
      fHist3SigSelectedKaonP(nullptr),
      fismc(kFALSE),
      fHistPBetaProton(nullptr),
      fHistPBetaElectron(nullptr),
      fHistPBetaKaon(nullptr),
      fHistPTPCPion2(nullptr),
      fHistPTOFPion2(nullptr),
      fHistPTPCProton(nullptr),
      fHistPTOFProton(nullptr),
      /*TEST(nullptr),*/ fHistPTOF3SigKaon(nullptr),
      fHistPTPC3SigKaon(nullptr),
      fHistPKaon(nullptr),
      /*fHistSum_PKaon(nullptr),*/ fHistTOF(nullptr),
      fHistBeta(nullptr),
      fHistMCall(nullptr),
      fHistAllSpeciesKaon(nullptr),
      fHistPureKaon(nullptr),
      fHistAllPureKaon(nullptr),
      fHistPhotonPt(nullptr),
      fHistArmenterosPodolandski(nullptr)

{
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

  fEventCuts.AddQAplotsToList(fOutputList);

  // example of a histogram
  fHistPt =
      new TH1F("fHistPt", "fHistPt", 200, 0, 10);  // create your histogram
  fHistPt->SetTitle(
      "Transversemomentum;transversmomentum p;counts N");  // Lableing of the
                                                           // Graph ("Title; X
                                                           // Var; Y Var")
  fOutputList->Add(fHistPt);  // don't forget to add it to the list! the list
                              // will be written to file, so if you want
  // your histogram in the output file, add it to the list!
  fHistPtvertexZ = new TH1F("fHistPtvertexZ", "fHistPtvertexZ", 200, -10, 10);
  fHistPtvertexZ->SetTitle("Transversemomentum;transversmomentum p;counts N");
  fOutputList->Add(fHistPtvertexZ);

  // fHistPtcentrality = new TH1F("fHistPtcentrality", "fHistPtcentrality", 200,
  // 0, 10);
  // fOutputList->Add(fHistPtcentrality);

  // TEST = new TH2F("TEST", "TEST", 200, 0, 10, 200, 0, 10);
  // fOutputList->Add(TEST);

  fHistPKaon = new TH1F("fHistPKaon", "fHistPKaon", 200, 0, 10);
  fHistPKaon->SetTitle("Kaon momentum;momentum p;counts N");
  fOutputList->Add(fHistPKaon);

  fHistAllPureKaon =
      new TH1F("fHistAllPureKaon", "fHistAllPureKaon", 200, 0, 10);
  fHistAllPureKaon->SetTitle("TrueKaon momentum;momentum p;counts N");
  fOutputList->Add(fHistAllPureKaon);

  fHistPureKaon = new TH1F("fHistPureKaon", "fHistPureKaon", 200, 0, 10);
  fHistPureKaon->SetTitle("Only Kaon momentum;momentum p;counts N");
  fOutputList->Add(fHistPureKaon);

  fHistMCall = new TH1F("fHistMCall", "fHistMCall", 200, 0, 10);
  fHistMCall->SetTitle("Only Kaon momentum;momentum p;counts N");
  fOutputList->Add(fHistMCall);

  fHistAllSpeciesKaon =
      new TH1F("fHistAllSpeciesKaon", "fHistAllSpeciesKaon", 200, -321, 322);
  fHistAllSpeciesKaon->SetTitle("Particle species;PDG-Code;counts N");
  fOutputList->Add(fHistAllSpeciesKaon);

  fHistSigSelectedProtonP = new TH1F("fHistSigSelectedProtonP",
                                     "fHistSigSelectedProtonP", 200, 0, 10);
  fHistSigSelectedProtonP->SetTitle("3-Sig. Protonevents;momentum p;counts N");
  fOutputList->Add(fHistSigSelectedProtonP);

  fHist3SigSelectedProtonP = new TH1F("fHist3SigSelectedProtonP",
                                      "fHist3SigSelectedProtonP", 200, 0, 10);
  fHist3SigSelectedProtonP->SetTitle(
      "3-Sig.(combined) Protonevents;momentum p;counts N");
  fOutputList->Add(fHist3SigSelectedProtonP);

  fHistSigSelectedElectronP = new TH1F("fHistSigSelectedElectronP",
                                       "fHistSigSelectedElectronP", 200, 0, 10);
  fHistSigSelectedElectronP->SetTitle(
      "3-Sig. Electronevents;momentum p;counts N");
  fOutputList->Add(fHistSigSelectedElectronP);

  fHist3SigSelectedElectronP = new TH1F(
      "fHist3SigSelectedElectronP", "fHist3SigSelectedElectronP", 200, 0, 10);
  fHist3SigSelectedElectronP->SetTitle(
      "3-Sig.(combined) Electronevents;momentum p;counts N");
  fOutputList->Add(fHist3SigSelectedElectronP);

  fHistSigSelectedPionP =
      new TH1F("fHistSigSelectedPionP", "fHistSigSelectedPionP", 200, 0, 10);
  fHistSigSelectedPionP->SetTitle("3-Sig. Pionevents;momentum p;counts N");
  fOutputList->Add(fHistSigSelectedPionP);

  fHist3SigSelectedPionP =
      new TH1F("fHist3SigSelectedPionP", "fHist3SigSelectedPionP", 200, 0, 10);
  fHist3SigSelectedPionP->SetTitle(
      "3-Sig.(combined) Pionevents;momentum p;counts N");
  fOutputList->Add(fHist3SigSelectedPionP);

  fHistSigSelectedKaonP =
      new TH1F("fHistSigSelectedKaonP", "fHistSigSelectedKaonP", 200, 0, 10);
  fHistSigSelectedKaonP->SetTitle("3-Sig. Kaonevents;momentum p;counts N");
  fOutputList->Add(fHistSigSelectedKaonP);

  fHist3SigSelectedKaonP =
      new TH1F("fHist3SigSelectedKaonP", "fHist3SigSelectedKaonP", 200, 0, 10);
  fHist3SigSelectedKaonP->SetTitle(
      "3-Sig.(combined) Kaonevents;momentum p;counts N");
  fOutputList->Add(fHist3SigSelectedKaonP);

  fHistPt2D = new TH2F("fHistPt2D", "fHistPt2D", 200, 0, 10, 200, 0, 10);
  fHistPt2D->SetTitle("transverse momentum;transversemomentum pt;counts N");
  fOutputList->Add(fHistPt2D);

  fHistTPC = new TH2F("fHistTPC", "fHistTPC", 200, 0, 10, 200, 0, 500);
  fHistTPC->SetTitle("TPC signals;TPC signals;counts N");
  fOutputList->Add(fHistTPC);

  fHistTOF = new TH2F("fHistTOF", "fHistTOF", 200, 0, 10, 200, 0, 25000);
  fHistTOF->SetTitle("TOF signals;TOF signals;counts N");
  fOutputList->Add(fHistTOF);

  fHistBeta = new TH2F("fHistBeta", "fHistBeta", 200, 0, 10, 200, 0, 1);
  fHistBeta->SetTitle("$/Beta$ distribution;momentum p;Beta $/Beta$");
  fOutputList->Add(fHistBeta);

  fHistPTPCPion =
      new TH2F("fHistPTPCPion", "fHistPTPCPion", 200, 0, 10, 200, 0, 500);
  fHistPTPCPion->SetTitle("Pionsignal TPC and momentum;momentum p;TPC signals");
  fOutputList->Add(fHistPTPCPion);

  fHistPTOFPion =
      new TH2F("fHistPTOFPion", "fHistPTOFPion", 200, 0, 10, 200, 0, 25000);
  fHistPTOFPion->SetTitle("Pionsignal TOF and momentum;momentum p;TOF signals");
  fOutputList->Add(fHistPTOFPion);

  fHistPTPCProton =
      new TH2F("fHistPTPCProton", "fHistPTPCProton", 200, 0, 10, 200, 0, 500);
  fHistPTPCProton->SetTitle(
      "Protonsignal TPC and momentum;momentum p;TPC signals");
  fOutputList->Add(fHistPTPCProton);

  fHistPTOFProton =
      new TH2F("fHistPTOFProton", "fHistPTOFProton", 200, 0, 10, 200, 0, 25000);
  fHistPTOFProton->SetTitle(
      "Pionsignal TOF and momentum;momentum p;TOF signals");
  fOutputList->Add(fHistPTOFProton);

  fHistPTPCKaon =
      new TH2F("fHistPTPCKaon", "fHistPTPCKaon", 200, 0, 10, 200, 0, 500);
  fHistPTPCKaon->SetTitle("Kaonsignal TPC and momentum;momentum p;TPC signals");
  fOutputList->Add(fHistPTPCKaon);

  fHistPTOFKaon =
      new TH2F("fHistPTOFKaon", "fHistPTOFKaon", 200, 0, 10, 200, 0, 25000);
  fHistPTOFKaon->SetTitle("Kaonsignal TOF and momentum;momentum p;TOF signals");
  fOutputList->Add(fHistPTOFKaon);

  fHistPTPC3SigKaon = new TH2F("fHistPTPC3SigKaon", "fHistPTPC3SigKaon", 200, 0,
                               10, 200, 0, 500);
  fHistPTPC3SigKaon->SetTitle(
      "Kaonsignal within 3-Sig. TPC and momentum;momentum p;TPC signals");
  fOutputList->Add(fHistPTPC3SigKaon);

  fHistPTOF3SigKaon = new TH2F("fHistPTOF3SigKaon", "fHistPTOF3SigKaon", 200, 0,
                               10, 200, 0, 25000);
  fHistPTOF3SigKaon->SetTitle(
      "Kaonsignal within 3-Sig. TOF and momentum;momentum p;TOF signals");
  fOutputList->Add(fHistPTOF3SigKaon);

  fHistPTPCElectron = new TH2F("fHistPTPCElectron", "fHistPTPCElectron", 200, 0,
                               10, 200, 0, 500);
  fHistPTPCElectron->SetTitle(
      "Electronsignal TPC and momentum;momentum p;TPC signals");
  fOutputList->Add(fHistPTPCElectron);

  fHistPTOFElectron = new TH2F("fHistPTOFElectron", "fHistPTOFElectron", 200, 0,
                               10, 200, 0, 25000);
  fHistPTOFElectron->SetTitle(
      "Electronsignal TPC and momentum;momentum p;TPC signals");
  fOutputList->Add(fHistPTOFElectron);

  fHistPTPCPion2 =
      new TH2F("fHistPTPCPion2", "fHistPTPCPion2", 200, 0, 10, 200, 0, 500);
  fHistPTPCPion2->SetTitle(
      "Pionsignal TPC and momentum;momentum p;TPC signals");
  fOutputList->Add(fHistPTPCPion2);

  fHistPTOFPion2 =
      new TH2F("fHistPTOFPion2", "fHistPTOFPion2", 200, 0, 10, 200, 0, 25000);
  fHistPTOFPion2->SetTitle(
      "Pionsignal TOF and momentum;momentum p;TOF signals");
  fOutputList->Add(fHistPTOFPion2);

  fHistPBetaTPCPion = new TH2F("fHistPBetaTPCPion", "fHistPBetaTPCPion", 200, 0,
                               10, 200, 0, 1.1);
  fHistPBetaTPCPion->SetTitle(
      "Pionsignal TPC and momentum;momentum p;Beta $/Beta$");
  fOutputList->Add(fHistPBetaTPCPion);

  fHistPBetaTOFPion = new TH2F("fHistPBetaTOFPion", "fHistPBetaTOFPion", 200, 0,
                               10, 200, 0, 1.1);
  fHistPBetaTOFPion->SetTitle(
      "Pionsignal TOF and momentum;momentum p;Beta $/Beta$");
  fOutputList->Add(fHistPBetaTOFPion);

  fHistPBetaPion =
      new TH2F("fHistPBetaPion", "fHistPBetaPion", 200, 0, 10, 200, 0, 1.1);
  fHistPBetaPion->SetTitle(
      "Pionsignal Beta and momentum;momentum p;Beta $/Beta$");
  fOutputList->Add(fHistPBetaPion);

  fHistPBetaProton =
      new TH2F("fHistPBetaProton", "fHistPBetaProton", 200, 0, 10, 200, 0, 1.1);
  fHistPBetaProton->SetTitle(
      "Protonsignal Beta and momentum;momentum p;Beta $/Beta$");
  fOutputList->Add(fHistPBetaProton);

  fHistPBetaKaon =
      new TH2F("fHistPBetaKaon", "fHistPBetaKaon", 200, 0, 10, 200, 0, 1.1);
  fHistPBetaKaon->SetTitle(
      "Kaonsignal Beta and momentum;momentum p;Beta $/Beta$");
  fOutputList->Add(fHistPBetaKaon);

  fHistPBetaElectron = new TH2F("fHistPBetaElectron", "fHistPBetaElectron", 200,
                                0, 10, 200, 0, 1.1);
  fHistPBetaElectron->SetTitle(
      "Electronsignal Beta and momentum;momentum p;Beta $/Beta$");
  fOutputList->Add(fHistPBetaElectron);

  fHistPionPt = new TH1F("fHistPionPt", "fHistPionPt", 200, 0, 10);
  fHistPionPt->SetTitle(
      "Pion transversalmomentum;transversemomentum p;counts N");
  fOutputList->Add(fHistPtcentrality);

  fHistPionPsdRap = new TH1F("fHistPionPsdRap", "fHistPionPsdRap", 200, 0, 10);
  fHistPionPsdRap->SetTitle(
      "Pion Pseudorapidity;Pseudorapidity $/Eta$;counts N");
  fOutputList->Add(fHistPionPsdRap);

  fHistPionAzi = new TH1F("fHistPionAzi", "fHistPionAzi", 200, 0, 10);
  fHistPionAzi->SetTitle("Pion Azimuthal;Pseudorapidity $/Eta$;counts N");
  fOutputList->Add(fHistPionAzi);

  fHistNSigTOFPion = new TH2F("fHistNSigTOFPion", "fHistNSigTOFPion", 200, 0,
                              10, 200, -10, 10);
  fHistNSigTOFPion->SetTitle(
      "Electron Sig. distribution of TOF;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigTOFPion);

  fHistNSigTPCPion = new TH2F("fHistNSigTPCPion", "fHistNSigTPCPion", 200, 0,
                              10, 200, -10, 10);
  fHistNSigTPCPion->SetTitle(
      "Electron Sig. distribution of TPC;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigTPCPion);

  fHistNSigTOFKaon = new TH2F("fHistNSigTOFKaon", "fHistNSigTOFKaon", 200, 0,
                              10, 200, -10, 10);
  fHistNSigTOFKaon->SetTitle(
      "Kaon Sig. distribution of TOF;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigTOFKaon);

  fHistNSigTPCKaon = new TH2F("fHistNSigTPCKaon", "fHistNSigTPCKaon", 200, 0,
                              10, 200, -10, 10);
  fHistNSigTPCKaon->SetTitle(
      "Kaon Sig. distribution of TPC;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigTPCKaon);

  fHistNSigTOFProton = new TH2F("fHistNSigTOFProton", "fHistNSigTOFProton", 200,
                                0, 10, 200, -10, 10);
  fHistNSigTOFProton->SetTitle(
      "Proton Sig. distribution of TOF;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigTOFProton);

  fHistNSigTPCProton = new TH2F("fHistNSigTPCProton", "fHistNSigTPCProton", 200,
                                0, 10, 200, -10, 10);
  fHistNSigTPCProton->SetTitle(
      "Proton Sig. distribution of TPC;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigTPCProton);

  fHistNSigTOFElectron = new TH2F(
      "fHistNSigTOFElectron", "fHistNSigTOFElectron", 200, 0, 10, 200, -10, 10);
  fHistNSigTOFElectron->SetTitle(
      "Electron Sig. distribution of TOF;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigTOFElectron);

  fHistNSigTPCElectron = new TH2F(
      "fHistNSigTPCElectron", "fHistNSigTPCElectron", 200, 0, 10, 200, -10, 10);
  fHistNSigTPCElectron->SetTitle(
      "Electron Sig. distribution of TPC;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigTPCElectron);

  fHistNSigAddProton = new TH2F("fHistNSigAddProton", "fHistNSigAddProton", 200,
                                0, 10, 200, -10, 10);
  fHistNSigAddProton->SetTitle(
      "Proton Sig. (combined) distribution;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigAddProton);

  fHistNSigAddElectron = new TH2F(
      "fHistNSigAddElectron", "fHistNSigAddElectron", 200, 0, 10, 200, -10, 10);
  fHistNSigAddElectron->SetTitle(
      "Electron Sig. (combined) distribution;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigAddElectron);

  fHistNSigAddPion = new TH2F("fHistNSigAddPion", "fHistNSigAddPion", 200, 0,
                              10, 200, -10, 10);
  fHistNSigAddPion->SetTitle(
      "Pion Sig. (combined) distribution;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigAddPion);

  fHistNSigAddKaon = new TH2F("fHistNSigAddKaon", "fHistNSigAddKaon", 200, 0,
                              10, 200, -10, 10);
  fHistNSigAddKaon->SetTitle(
      "Kaon Sig. (combined) distribution;momentum p;Sig. $/Sigma$");
  fOutputList->Add(fHistNSigAddKaon);

  fHistPhotonPt = new TH1F("fHistPhotonPt",
                           "; #it{p}_{T} (GeV/#it{c}); Entries", 100, 0, 10);
  fOutputList->Add(fHistPhotonPt);

  fHistArmenterosPodolandski = new TH2F(
      "fHistArmenterosPodolandski", " ; #alpha; #it{q}_{T} p#pi [GeV/#it{c}]",
      500, -1, 1, 500, 0, 1);
  fOutputList->Add(fHistArmenterosPodolandski);

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
  AliMCEvent *fMC = nullptr;
  if (fismc) {
    AliAODInputHandler *eventHandler = dynamic_cast<AliAODInputHandler *>(
        AliAnalysisManager::GetAnalysisManager()->GetInputEventHandler());
    fMC = eventHandler->MCEvent();
    for (int iPart = 1; iPart < (fMC->GetNumberOfTracks()); iPart++) {
      AliMCParticle *mcParticle =
          static_cast<AliMCParticle *>(fMC->GetTrack(iPart));
      if (0.1 < mcParticle->Pt() && -0.8 < mcParticle->Eta() &&
          mcParticle->Eta() < 0.8) {
        fHistMCall->Fill(mcParticle->P());
        if (mcParticle->PdgCode() == 321 || mcParticle->PdgCode() == -321) {
          fHistAllPureKaon->Fill(mcParticle->P());
        }
      }
    }
  }
  if (!fAOD) return;

  // Event cuts - check whether the event is good for analysis
  if (!fEventCuts.AcceptEvent(fAOD)) {
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
  }

  for (auto v0obj : *(fAOD->GetV0s())) {
    auto* v0 = static_cast<AliAODv0 *>(v0obj);
    if (!v0) continue;
     //std::cout << v0->MassLambda() << "\n";
    AliAODTrack *posTrack =
        static_cast<AliAODTrack *>(fGlobalTrackReference[v0->GetPosID()]);
    AliAODTrack *negTrack =
        static_cast<AliAODTrack *>(fGlobalTrackReference[v0->GetNegID()]);
    if (!posTrack || !negTrack) continue;

    if (posTrack->Eta() < 0.8 ) {
      const float nCls = posTrack->GetTPCNcls();
      const short nFindable = posTrack->GetTPCNclsF();
      const float ratioFindable = nCls / static_cast<float>(nFindable);
      if (ratioFindable > 0.8) {
        const float armAlpha = v0->AlphaV0();
        const float armQt = v0->PtArmV0();
        fHistArmenterosPodolandski->Fill(armAlpha, armQt);
      }
    }
    if (negTrack->Eta() < 0.8) {
      const float nCls = negTrack->GetTPCNcls();
      const short nFindable = negTrack->GetTPCNclsF();
      const float ratioFindable = nCls / static_cast<float>(nFindable);
      if (ratioFindable > 0.8) {
        const float armAlpha = v0->AlphaV0();
        const float armQt = v0->PtArmV0();
        fHistArmenterosPodolandski->Fill(armAlpha, armQt);
      }
    }
    /*const float nCls = track->GetTPCNcls();
    const short nFindable = track->GetTPCNclsF();
    const float ratioFindable = nCls / static_cast<float>(nFindable);
    ratioFindable > 0.8

    const float armAlpha = v0->AlphaV0();
    const float armQt = v0->PtArmV0();
    fHistArmenterosPodolandski->Fill(armAlpha, armQt);*/
  }
  // End of bad code segment
  Int_t iTracks(
      fAOD->GetNumberOfTracks());  // see how many tracks there are in the event
  float vertexZ = fAOD->GetPrimaryVertex()->GetZ();
  fHistPtvertexZ->Fill(vertexZ);
  // float centrality = fAOD->GetCentrality()->GetCentralityPercentile("V0M");
  // fHistPtcentrality->Fill(centrality);

  for (Int_t i(0); i < iTracks; i++) {  // loop over all these tracks
    AliAODTrack *track = static_cast<AliAODTrack *>(
        fAOD->GetTrack(i));  // get a track (type AliAODTrack) from the event
    if (!track || !track->TestFilterBit(1))
      continue;  // if we failed, skip this track
    AliMCParticle *mcParticle = nullptr;
    if (fismc && fMC)
      mcParticle =
          static_cast<AliMCParticle *>(fMC->GetTrack(track->GetLabel()));
    if (fismc && !mcParticle) continue;

    AliAnalysisManager *man = AliAnalysisManager::GetAnalysisManager();
    if (man) {
      AliInputEventHandler *inputHandler =
          (AliInputEventHandler *)(man->GetInputEventHandler());
      if (inputHandler) fPIDResponse = inputHandler->GetPIDResponse();
    }

    fHistNSigTOFPion->Fill(
        track->P(), fPIDResponse->NumberOfSigmasTOF(track, AliPID::kPion));
    fHistNSigTOFKaon->Fill(
        track->P(), fPIDResponse->NumberOfSigmasTOF(track, AliPID::kKaon));
    fHistNSigTOFProton->Fill(
        track->P(), fPIDResponse->NumberOfSigmasTOF(track, AliPID::kProton));
    fHistNSigTOFElectron->Fill(
        track->P(), fPIDResponse->NumberOfSigmasTOF(track, AliPID::kElectron));

    fHistNSigTPCPion->Fill(
        track->P(), fPIDResponse->NumberOfSigmasTPC(track, AliPID::kPion));
    fHistNSigTPCKaon->Fill(
        track->P(), fPIDResponse->NumberOfSigmasTPC(track, AliPID::kKaon));
    fHistNSigTPCProton->Fill(
        track->P(), fPIDResponse->NumberOfSigmasTPC(track, AliPID::kProton));
    fHistNSigTPCElectron->Fill(
        track->P(), fPIDResponse->NumberOfSigmasTPC(track, AliPID::kElectron));

    // TEST->Fill(track->P(),track->P());

    // Selected events

    // Preselects protons and returns the quadratic sum of TOF and TPC nSigmas
    if (track->P() > 0.4 &&
        std::abs(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kProton)) < 3 &&
        std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kProton)) < 3) {
      fHistNSigAddProton->Fill(
          track->P(),
          std::sqrt(
              std::pow(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kProton),
                       2) +
              std::pow(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kProton),
                       2)));
      fHistPTPCProton->Fill(track->P(), track->GetTOFsignal());
      fHistPTOFProton->Fill(track->P(), track->GetTOFsignal());
      if ((0 < GetBeta(track)) && (1 > GetBeta(track))) {
        fHistPBetaProton->Fill(track->P(), GetBeta(track));
      }
      fHistSigSelectedProtonP->Fill(track->P());  // Neglects combined Sigmas
      if (std::sqrt(
              std::pow(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kProton),
                       2) +
              std::pow(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kProton),
                       2)) < 3) {
        fHist3SigSelectedProtonP->Fill(track->P());
      }
    }

    // Preselects electrons and returns the quadratic sum of TOF and TPC nSigmas
    if (track->P() > 0.2 &&
        std::abs(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kElectron)) <
            3 &&
        std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kElectron)) <
            3) {
      fHistNSigAddElectron->Fill(
          track->P(), std::sqrt(std::pow(fPIDResponse->NumberOfSigmasTOF(
                                             track, AliPID::kElectron),
                                         2) +
                                std::pow(fPIDResponse->NumberOfSigmasTPC(
                                             track, AliPID::kElectron),
                                         2)));
      fHistPTPCElectron->Fill(track->P(), track->GetTPCsignal());
      fHistPTOFElectron->Fill(track->P(), track->GetTOFsignal());
      if ((0 < GetBeta(track)) && (1 > GetBeta(track))) {
        fHistPBetaElectron->Fill(track->P(), GetBeta(track));
      }
      fHistSigSelectedElectronP->Fill(track->P());  // Neglects combined Sigmas
      if (std::sqrt(std::pow(fPIDResponse->NumberOfSigmasTOF(track,
                                                             AliPID::kElectron),
                             2) +
                    std::pow(fPIDResponse->NumberOfSigmasTPC(track,
                                                             AliPID::kElectron),
                             2)) < 3) {
        fHist3SigSelectedElectronP->Fill(track->P());
      }
    }

    // Preselects pions and returns the quadratic sum of TOF and TPC nSigmas
    if (track->P() > 0.1 &&
        std::abs(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kPion)) < 3 &&
        std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kPion)) < 3) {
      fHistNSigAddPion->Fill(
          track->P(),
          std::sqrt(
              std::pow(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kPion),
                       2) +
              std::pow(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kPion),
                       2)));
      fHistPTPCPion->Fill(track->P(), track->GetTPCsignal());
      fHistPTOFPion->Fill(track->P(), track->GetTOFsignal());
      if ((0 < GetBeta(track)) && (1 > GetBeta(track))) {
        fHistPBetaPion->Fill(track->P(), GetBeta(track));
      }
      fHistSigSelectedPionP->Fill(track->P());  // Neglects combined Sigmas
      if (std::sqrt(
              std::pow(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kPion),
                       2) +
              std::pow(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kPion),
                       2)) < 3) {
        fHist3SigSelectedPionP->Fill(track->P());
      }
    }

    // Preselects kaons and returns the quadratic sum of TOF and TPC nSigmas
    if (track->P() > 0.2 &&
        std::abs(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kKaon)) < 3 &&
        std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kKaon)) < 3) {
      fHistNSigAddKaon->Fill(
          track->P(),
          std::sqrt(
              std::pow(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kKaon),
                       2) +
              std::pow(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kKaon),
                       2)));
      fHistPTPCKaon->Fill(track->P(), track->GetTPCsignal());
      fHistPTOFKaon->Fill(track->P(), track->GetTOFsignal());
      if ((0 < GetBeta(track)) && (1 > GetBeta(track))) {
        fHistPBetaKaon->Fill(track->P(), GetBeta(track));
      }
      fHistSigSelectedKaonP->Fill(track->P());  // Neglects combined Sigmas
      if (std::sqrt(
              std::pow(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kKaon),
                       2) +
              std::pow(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kKaon),
                       2)) < 3) {
        fHist3SigSelectedKaonP->Fill(track->P());
        fHistPTPC3SigKaon->Fill(track->P(), track->GetTPCsignal());
        fHistPTOF3SigKaon->Fill(track->P(), track->GetTOFsignal());
      }
    }

    // Refined selection of plausible Kaon-Events through impuls selections
    // WITHOUT combined Sigma constraint!!!
    if (track->P() > 0.1 && track->P() < 0.4 &&
        std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kKaon)) < 3) {
      fHistPKaon->Fill(track->P());
      if (fismc) { /*st:cout << mcParticle->PdgCode() << "\n";*/
        fHistAllSpeciesKaon->Fill(mcParticle->PdgCode());
        if (mcParticle->PdgCode() == 321 || mcParticle->PdgCode() == -321) {
          fHistPureKaon->Fill(track->P());
        }
      }
    }
    if (track->P() > 0.4 && track->P() < 2 &&
        std::abs(fPIDResponse->NumberOfSigmasTOF(track, AliPID::kKaon)) < 3) {
      fHistPKaon->Fill(track->P());
      if (fismc) { /*st:cout << mcParticle->PdgCode() << "\n";*/
        fHistAllSpeciesKaon->Fill(mcParticle->PdgCode());
        if (mcParticle->PdgCode() == 321 || mcParticle->PdgCode() == -321) {
          fHistPureKaon->Fill(track->P());
        }
      }
    }
    // if(track->P()>2.1 && track->P()<4 &&
    // std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kPion)) < 3){
    // fHistPKaon->Fill(track->P());
    //}

    // pure electrons

    if (fPIDResponse->NumberOfSigmasTOF(track, AliPID::kPion) < 3) {
      // pion
      // plot histograms
      fHistPTOFPion2->Fill(track->P(), track->GetTOFsignal());
      if ((0 < GetBeta(track)) && (1 > GetBeta(track))) {
        fHistPBetaTOFPion->Fill(track->P(), GetBeta(track));
      }
    }

    if (std::abs(fPIDResponse->NumberOfSigmasTPC(track, AliPID::kPion)) < 3) {
      // jippy, i'm a pion
      // fHistPionPt->Fill(track->Pt());
      // fHistPionPsdRap->Fill(track->Eta());
      // fHistPionAzi->Fill(track->Phi());
      fHistPTPCPion2->Fill(track->P(), track->GetTPCsignal());
      if ((0 < GetBeta(track)) && (1 > GetBeta(track))) {
        fHistPBetaTPCPion->Fill(track->P(), GetBeta(track));
      }
    }

    fHistPt->Fill(
        track->Pt());  // plot the pt value of the track in a histogram
    fHistPt2D->Fill(track->Eta(), track->Phi());
    fHistTPC->Fill(track->P(), track->GetTPCsignal());
    fHistTOF->Fill(track->P(), track->GetTOFsignal());
    fHistBeta->Fill(track->P(), GetBeta(track));
    // cout << track->GetTOFsignal() << "\n";

    // cout << GetBeta(track)<< "\n";
    // for (Int_t j(0);j<v.size();j++) {
    // cout << v[j]<<"/n"
    //}
  }
  // Summe von P1 und P2
  // fHistSum_PKaon=new TH1F(*fHistP1Kaon);
  // fHistSum_PKaon->Add(fHistP2Kaon,1.);
  // fOutputList->Add(fHistSum_PKaon);

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
