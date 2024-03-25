// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldGameMode.h"
#include "WorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWorldGameMode::AWorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
