// Fill out your copyright notice in the Description page of Project Settings.

#include "PGPortal.h"

APGPortal::APGPortal(const FObjectInitializer& InOI) : Super(InOI)
{

}

void APGPortal::EnterPortal(APGPortal* Portal, APawn* Pawn)
{
	OnPortalEntered.Broadcast(Portal, Pawn);
}