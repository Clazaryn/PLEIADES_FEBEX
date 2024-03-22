//------------------------------------------------------------------------
//************************ TPLEIADESDetEvent.h ***************************
//------------------------------------------------------------------------
//       The GSI Online Offline Object Oriented (Go4) Project
//         Experiment Data Processing at EE department, GSI
//------------------------------------------------------------------------
// Copyright (C) 2000- GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
//                     Planckstr. 1, 64291 Darmstadt, Germany
// Contact:            http://go4.gsi.de
//------------------------------------------------------------------------
// This software can be used under the license agreements as stated
// in Go4License.txt file which is part of the distribution.
//------------------------------------------------------------------------

#ifndef TPLEIADESDETEVENT_H
#define TPLEIADESDETEVENT_H

#include "TGo4CompositeEvent.h"
#include "TPLEIADESRawEvent.h"

//------------------------------------------------------------------------
// TPLEIADESDetChan is a dependent class on TPLEIADESDetector. It represents an output channel on the detector.
//------------------------------------------------------------------------

class TPLEIADESDetChan : public TGo4EventElement
{
    public:
        TPLEIADESDetChan();
        TPLEIADESDetChan(const char* name, Short_t id=0);
        virtual ~TPLEIADESDetChan();

        /** Method called by the framework to clear the event element. **/
        void Clear(Option_t *opt = "");

        /** actions on unique channel mapping **/
        void SetChanMap(UInt_t map) { fUniqChanMap = map; }
        UInt_t GetChanMap() { return fUniqChanMap; }

        /** actions on channel type **/
        void SetChanType(TString type) { fChanType = type; }
        TString GetChanType() { return fChanType; }

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

    private:
        UInt_t fUniqChanMap;    // channel map to DAQ position
        TString fChanType;      // type of channel

    ClassDef(TPLEIADESDetChan, 1)
};

//------------------------------------------------------------------------
// TPLEIADESNormPos is a dependent class on TPLEIADESDetector. It is a special class for the normalised position measurement of the DSSD.
//------------------------------------------------------------------------

class TPLEIADESNormPos : public TGo4EventElement
{
    public:
        TPLEIADESNormPos();
        TPLEIADESNormPos(const char* name, Short_t id=0);
        virtual ~TPLEIADESNormPos();

        /** Method called by the framework to clear the event element. **/
        void Clear(Option_t *opt = "");

        /** calculated position quantities **/
        Double_t fNormPosX;     // normalised position for X
        Double_t fNormPosY;     // normalised position for Y

    ClassDef(TPLEIADESNormPos, 1)
};

//------------------------------------------------------------------------
// TPLEIADESDector is a dependent class on TPLEIADESDetEvent. It represents a physical detector.
//------------------------------------------------------------------------

class TPLEIADESDetector : public TGo4CompositeEvent
{
    public:
        TPLEIADESDetector();
        TPLEIADESDetector(const char* name, Short_t id=0);
        virtual ~TPLEIADESDetector();

        /** actions on unique name of detector **/
        void SetDetName(TString dname) { fDetName = dname ; }
        TString GetDetName() { return fDetName; }

        /** actions on type of detector **/
        void SetDetType(TString dtype) { fDetType = dtype; }
        TString GetDetType() { return fDetType; }

        /** setup detector based on name and type **/
        void SetupDetector();      // setup channels based on name and type

        /** get channel objects created with board **/
        TPLEIADESDetChan* GetChannel(UInt_t id)
        {
            return (TPLEIADESDetChan*) getEventElement(id);
        }



        /** Method called by the framework to clear the event element. **/
        void Clear(Option_t *opt = "");

    private:
        TString fDetName;       // detector name setup in set_PLEIADESParam.C
        TString fDetType;       // detector type

    ClassDef(TPLEIADESDetector, 1)
};

//------------------------------------------------------------------------
// TPLEIADESDetEvent is the base class for detector grouping
//------------------------------------------------------------------------

class TPLEIADESDetEvent : public TGo4CompositeEvent
{
    public:
        TPLEIADESDetEvent();
        TPLEIADESDetEvent(const char* name, Short_t id=0);
        virtual ~TPLEIADESDetEvent();

        /** Method called by the framework to clear the event element. **/
        void Clear(Option_t *opt = "");

        /** access to board subcomponent by unique id **/
        void BuildDetectors();      // build detectors with name and type
        TPLEIADESDetector* GetDetector(TString dname);      //return detector by name

        /** this array keeps the unique names of configured detectors **/
        static std::vector<TString> fgConfigDetectors;

    ClassDef(TPLEIADESDetEvent, 1)
};

#endif // TPLEIADESDETEVENT_H

//----------------------------END OF GO4 SOURCE FILE ---------------------