#include "GoAT.h"


GoAT::GoAT() :
    useParticleReconstruction(0),
    nEventsWritten(0)
{ 
}

GoAT::~GoAT()
{
}

Bool_t	GoAT::Init()
{
    cout << endl << "Initialising GoAT analysis..." << endl << endl;

    std::string config = ReadConfig("Period-Macro");
    if( sscanf(config.c_str(),"%d\n", &period) == 1 ) usePeriodMacro = 1;

	cout << "==========================================================" << endl;	
	cout << "Setting up Data Checks:" << endl;	
	cout << "==========================================================" << endl;	
    if(!GDataChecks::Init())
	{
		cout << "GDataChecks Init failed!" << endl; 
		return kFALSE;
	}

	cout << "==========================================================" << endl;	
	cout << "Setting up sorting criteria:" << endl;	
	cout << "==========================================================" << endl;	
    if(!GSort::Init())
	{
		cout << "GSort Init failed!" << endl; 
		return kFALSE;
	}
	
	cout << "==========================================================" << endl;		
	cout << "Setting up analysis classes:" << endl;	
	cout << "==========================================================" << endl;	
    config = ReadConfig("DO-PARTICLE-RECONSTRUCTION");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        Int_t buffer=0;
        sscanf( config.c_str(), "%d\n", &buffer);
        useParticleReconstruction = (buffer==1);
    }

    if(useParticleReconstruction)
	{
        if(!GParticleReconstruction::Init())
		{
			cout << "GParticleReconstruction Init failed!" << endl; 
			return kFALSE;
		}
    }

    config = ReadConfig("DO-MESON-RECONSTRUCTION");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        Int_t buffer=0;
        sscanf( config.c_str(), "%d\n", &buffer);
        useMesonReconstruction = (buffer==1);
    }

    if(useMesonReconstruction)
    {
        if(!GMesonReconstruction::Init())
        {
            cout << "GParticleReconstruction Init failed!" << endl;
            return kFALSE;
        }
    }

    config = ReadConfig("TARGET-SHIFT");
    if (strcmp(config.c_str(), "nokey") != 0)
    {
        Double_t shift=0;
        Double_t tapsd=0;
        Int_t npars = sscanf( config.c_str(), "%lf %lf\n", &shift, &tapsd);
        if(npars == 1) GetTracks()->SetTargetShift(shift);
        else if(npars == 2)
        {
            GetTracks()->SetTargetShift(shift);
            GetTracks()->SetTAPSDistance(tapsd);
            cout << "Applying target shift of " << shift << " cm, with TAPS set at " << tapsd << " cm" << endl;
        }
        else
        {
            cout << "Target shift not set correctly" << endl;
            return kFALSE;
        }

    }

	cout << endl;	

	cout << "Initialisation complete." << endl;
	cout << "==========================================================" << endl << endl;
  
	return kTRUE;
}

void	GoAT::ProcessEvent()
{
    if(usePeriodMacro == 1)
    {
        if(GetEventNumber() % period == 0)
            cout << "Event: " << GetEventNumber() << "  Events Accepted: " << nEventsWritten << endl;
    }

    if(SortAnalyseEvent())
    {
        if(useParticleReconstruction)
        {
            if(!GParticleReconstruction::ProcessEventWithoutFilling())  return;
            if(useMesonReconstruction)
            {
                if(!GMesonReconstruction::ProcessEventWithoutFilling())  return;
                if(!SortFillEvent())    return;
                GetNeutralPions()->Fill();
                GetEtas()->Fill();
                GetEtaPrimes()->Fill();
            }
            else
            {
                if(!SortFillEvent())    return;
            }
            GetPhotons()->Fill();
            GetChargedPions()->Fill();
            GetElectrons()->Fill();
            GetProtons()->Fill();
            GetNeutrons()->Fill();
        }
        else if(useMesonReconstruction)
        {
            if(!GParticleReconstruction::SimpleEventWithoutFilling())  return;
            if(!GMesonReconstruction::ProcessEventWithoutFilling())  return;
            if(!SortFillEvent())    return;
            GetNeutralPions()->Fill();
            GetEtas()->Fill();
            GetEtaPrimes()->Fill();
        }
        else
        {
            if(!GParticleReconstruction::SimpleEventWithoutFilling())  return;
            if(!SortFillEvent())    return;
        }
        GetRootinos()->Fill();
        GetEventParameters()->SetNReconstructed(GetNReconstructed());
        GetEventParameters()->Fill();
        FillReadList();
        nEventsWritten++;
    }
}

Bool_t	GoAT::Start()
{
    if(!IsAcquFile())
    {
        cout << "ERROR: Input File is not a Acqu file." << endl;
        return kFALSE;
    }
    SetAsGoATFile();

    GetRootinos()->CloseForInput();
    if(useParticleReconstruction)
    {
        if(useMesonReconstruction)
        {
            GetPhotons()->CloseForInput();
            GetElectrons()->CloseForInput();
            GetChargedPions()->CloseForInput();
            GetProtons()->CloseForInput();
            GetNeutrons()->CloseForInput();
            GetNeutralPions()->CloseForInput();
            GetEtas()->CloseForInput();
            GetEtaPrimes()->CloseForInput();
        }
        else
        {
            GetPhotons()->CloseForInput();
            GetElectrons()->CloseForInput();
            GetChargedPions()->CloseForInput();
            GetProtons()->CloseForInput();
            GetNeutrons()->CloseForInput();
        }
    }
    else if(useMesonReconstruction)
    {
        GetNeutralPions()->CloseForInput();
        GetEtas()->CloseForInput();
        GetEtaPrimes()->CloseForInput();
    }

    if(!TraverseValidEvents())		return kFALSE;

    return kTRUE;
}
