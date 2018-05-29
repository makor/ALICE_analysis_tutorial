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
  Bool_t IsConvertedPhoton(AliAODMCParticle *posDaughter,
                           AliAODMCParticle *negDaughter, AliMCEvent *fMCEvent,
                           AliAODMCParticle *mcMother,
                           AliConvEventCuts *fEventCuts);
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
  TH1F* fHistAllPhotons2;                           //!
  TH1F* fHistV0mcPhotonPtandArmCut;                 //!
  TH1F* fHistmcDaug1Pt;                             //!
  TH1F* fHistDetAccmcDaug1Pt;                       //!
  TH1F* fHistmcDaug2Pt;                             //!
  TH1F* fHistDetAccmcDaug2Pt;                       //!
  TH1F* fHistV0LambdaInvMass;                       //!
  TH1F* fHistV0AntiLambdaInvMass;                   //!
  TH1F* fHistV0PhotonCandPt;                        //!
  TH1F* fHistV0mcPhotonPtCut;                       //!
  TH2F* fHistArmenterosPodolandskiV0mcPhotonsCut;   //!
  TH2F* fHistArmenterosPodolandskiArmCut;           //!
  TH1F* fHistV0Pt;                                  //!
  TH1F* fKind;                                      //!
  TH1F* FillMCHistograms;                           //!
  TH1F* fHistReconstrmcPhotonPtMoCh;                //!
  TH1F* fHistReconstrmcPhotonPtCutPt;               //!
  TH1F* fHistReconstrmcPhotonPtNoDetCut;            //!
  TH1F* fHistReconstrmcPhotonPt;                    //!
  TH1F* fHistV0K0ShortInvMass;                      //!
  TH2F* fHistClsDistrPosTr;                         //!
  TH2F* fHistClsDistrNegTr;                         //!
  AliConvEventCuts* fEventCuts;                     //!
  Bool_t fIsMC;
  const float fpTCut = 0.1;
  const float fECut = 0.001;
  const float fEtaCut = 0.8;
  const float farmQtCut = 0.02;
  const float fCluFindRatCut = 0.8;
  TH1F* fHistPhotonPt;                          //!
  TH2F* fHistArmenterosPodolandski;             //!
  TH2F* fHistArmenterosPodolandskiV0mcPhotons;  //!

  AliAnalysisTaskMyTask(const AliAnalysisTaskMyTask&);  // not implemented
  AliAnalysisTaskMyTask& operator=(
      const AliAnalysisTaskMyTask&);  // not implemented

  ClassDef(AliAnalysisTaskMyTask, 1);
};

#endif

/*   Merging collection <259788.xml> into masterjob input...
Exporting merged collection <259842_259788.xml> and copying to AliEn
180524 11:17:33 23731 Xrd: CheckErrorStatus: Server [clralicexrd.in2p3.fr:1094]
declared: Unable to create /00/50582/3bc68222-5f33-11e8-b907-001f29eb8d2a; too
many open files in system(error code: 3005)
180524 11:17:33 23731 Xrd: Open: Error opening the file
/00/50582/3bc68222-5f33-11e8-b907-001f29eb8d2a?&authz=-----BEGIN SEALED
CIPHER-----
X6xf+wnmjA5QlYVzvIuoZ9700USs325WSs0-8YgYqxYA8ShCf9-FUkNPjrnjelvGg7JZNSYD-BAj
RXik+dmhQ-05jOBhLJhl22MG2v50msECJWMwSfzt2Xn-dpwKCaNzA9JY14mDQleJy0HO51Q8OM7I
ep6lUcAuC4sg3ncv3pM=
-----END SEALED CIPHER-----
-----BEGIN SEALED ENVELOPE-----
AAAAgKrSrMRI1z2zzgAWfq2Z-kNmOomnsjIKItCJM30PVYJF1jczONvFlTLrsL--MOKz-M6TYwo+
bpjgeGPyE6ih3UpZCqOHm3FkZTC5pY-9+pZWuvekkkQeAqdAZrHjog7orBlTqQSNuBbKFRoU30Ow
mZDldeP0b7D12tg5ARJxjTN6Khwjo+HpiqAH8NYduJA5mNItgbbsBn+ABSl8nmJhSRJTQw2GRg1l
UaSB+cBVa7OqWxSBurPMPTCcHW+n3tsCwmrcHD38knq5+40RlN7bfnh5kd7rQvh1ndj+dtazO6N7
PGVZUHoLmGY0ajDn4idfXqoLvxIHb9K2-jsW6B+OHUSUJcQSPDec8mLjqlQS4MseRdGj1BQUPRDX
IHxy5VXa3jEXpj0XG4apaTgA61PVEHQiuF1ahZdUg724vP+czjeRzdKIfbN+3KNB4AmGxBJwleOS
Mo8LvbggtcAPSUsI1Yw-3wi50qPWHPe-pc5hdqafU+EDyvV647bd8kUGdRTKVzLS4StRWcA+6oLh
Qh-xOTQWY3VEl8mU6otwasuVv3ISBKQu3am1za1oiRARvas7CnGgT3yXt+dlQwsbWf5kSnSk9FI3
Xe2owu+NqtEce1yEneMToQkVUSUSqRqbLvMdvF8RHFz9PMAycJZla6nDePmSOvqhZ6SlbAS57xFO
o9bGD-Z-Hohf3XqqmBgG42+8wiWhrelCC1Xny8mSpNIuJxqVnvgMv4UV702YeWPeLPnLxSA4FcJK
zkpKmNAVF-ebQ-Q9xLMDSfJP0SOqbuDQCT5lzuqjITqgc4mzwEBkDGazJnPgi9-j7p1aDLnLN7WM
vuT+8RGFDAnhEE2BbHBiRgc5i109Kd+M1RlyNJiYcTUyYH6D6g8wTeREmVBlqO9QUJRG3jfGlu4g
Bn4tN54b7gxclYdZM4IZfP8yeKPD4LOURNpC+5SxvtHJq+6dYAOpGw80EemwzDM1oAzgoamBfTsf
7Ototltdm07iwNb3Y5+3DL6zCSFUp-6047DOe5-ubRFuS6skQ8u9BL5-E3uLgG5VSBrnObya9h7q
b7sB7xx6Qe083Y8N+Hbs6zvP-3xuMw==
-----END SEALED ENVELOPE-----
&filetype=raw&source=259842_259788.xml on host clralicexrd.in2p3.fr:1094
root [1] 180524 11:22:48 23805 Xrd: XrdClientMessage::ReadRaw: Failed to read
header (8 bytes).
*/
