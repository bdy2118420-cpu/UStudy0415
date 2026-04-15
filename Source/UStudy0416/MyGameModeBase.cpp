// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyPlayerPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
