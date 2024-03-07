//-----------------------------------------------------------------------
//************************* TPLEIADESParam.cxx **************************
//-----------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//-----------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//-----------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//-----------------------------------------------------------------------

#ifndef TPLEIADESRawEvent_H
#define TPLEIADESRawEvent_H


// disable this define to speed up analysis, only histogram filling then
#define TPLEIADES_FILL_TRACES 1

#include "TGo4EventElement.h"
#include "TGo4CompositeEvent.h"


#define MAX_SFP          4
#define MAX_SLAVE        5
#define N_CHA            16


//-----------------------------------------------------------------------
// this is the lowest class for the individual FEBEX channel readouts
//-----------------------------------------------------------------------

class TPLEIADESFebChannel : public TGo4EventElement {
   public:
      TPLEIADESFebChannel();
      TPLEIADESFebChannel(const char *name, Short_t id);
      virtual ~TPLEIADESFebChannel();

      /** Method called by the framework to clear the event element. */
      void Clear(Option_t *opt = "") override;

      /** FEBEX special channel properties **/
      UInt_t fFPGAEnergy;
      Int_t fFGPAHitTime;
      std::vector<Int_t> fFPGATRAPEZ;

      /** FEBEX trace properties **/
#ifdef TPLEIADES_FILL_TRACES
      UInt_t fTrapezEnergy;
      std::vector<UInt_t>  fTrace;
      std::vector<Int_t>   fTraceBLR;
      std::vector<Int_t>   fTraceTRAPEZ;
#endif

      ClassDefOverride(TPLEIADESFebChannel,1)
};


//-----------------------------------------------------------------------
// this class represents one FEBEX-3 board with 16 Feb Channels
//-----------------------------------------------------------------------

class TPLEIADESFebBoard : public TGo4CompositeEvent {
   public:
      TPLEIADESFebBoard();
      TPLEIADESFebBoard(const char *name, Short_t id);
      virtual ~TPLEIADESFebBoard();

      /** get channel objects created with board **/
      TPLEIADESFebChannel* GetChannel(UInt_t id)
      {
         return (TPLEIADESFebChannel*) getEventElement(id);
      }

      /** Method called by the framework to clear the event element. */
      void Clear(Option_t *opt = "") override;

   private:

      /** check sequence number of events and report missing events **/
      Int_t fLastEventNumber;

   ClassDefOverride(TPLEIADESFebBoard,1)
};


//-----------------------------------------------------------------------
// this is the top event structure with all FEBEX boards in the chain
//-----------------------------------------------------------------------

class TPLEIADESRawEvent : public TGo4CompositeEvent {
   public:
      TPLEIADESRawEvent();
      TPLEIADESRawEvent(const char *name, Short_t id=0);
      virtual ~TPLEIADESRawEvent();

      /** get board objects created with output event **/
      TPLEIADESFebBoard* GetBoard(UInt_t id)
      {
         return (TPLEIADESFebBoard*) getEventElement(id);
      }

      /** Method called by the framework to clear the event element. */
      void Clear(Option_t *opt = "") override;

      /** Event sequence number incremented by MBS Trigger*/
      Int_t fSequenceNumber;

    ClassDefOverride(TPLEIADESRawEvent,1)
 };

#endif
