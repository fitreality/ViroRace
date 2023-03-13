// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOneLevelData.h"
#include "PerfectGymBlueprintLibrary.h"
#include "Engine/LevelScriptActor.h"
#include "GameOne/PGPortal.h"
#include "Engine/LevelStreamingKismet.h"

AGameOneLevelData::AGameOneLevelData(const FObjectInitializer& InOI) : Super(InOI)
{

}

void AGameOneLevelData::BeginPlay()
{
	Super::BeginPlay();
}

void AGameOneLevelData::GatherPortals(const TArray<ULevelStreamingKismet*>& Levels)
{
	for (int32 i = 0; i < Levels.Num(); ++i)
	{
		ULevel* Level = Levels[i]->GetLoadedLevel();
		if (Level)
		{
			TArray<AActor*> Portals;
			UPerfectGymBlueprintLibrary::GetActorsOfClassFromULevel(Level, APGPortal::StaticClass(), Portals);

			for (int32 i = 0; i < Portals.Num(); ++i)
			{
				APGPortal* Portal = Cast<APGPortal>(Portals[i]);
				if (Portal)
				{
					Portal->RerunConstructionScripts();
					if (Portal->PortalType == EPortalType::Start)
					{
						StartPortals.Add(Portal);
					}
					else if (Portal->PortalType == EPortalType::End)
					{
						EndPortals.Add(Portal);
					}
				}
			}
		}
	}
}

void AGameOneLevelData::RegisterPortals(const TArray<APGPortal*>& InStartPortals, const TArray<APGPortal*>& InEndPortals)
{
	StartPortals = InStartPortals;
	EndPortals = InEndPortals;
}

void AGameOneLevelData::GetPortals(TArray<APGPortal*>& OutStartPortals, TArray<APGPortal*>& OutEndPortals)
{
	OutStartPortals = StartPortals;
	OutEndPortals = EndPortals;
}