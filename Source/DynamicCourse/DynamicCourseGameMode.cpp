// Copyright Epic Games, Inc. All Rights Reserved.

#include "DynamicCourseGameMode.h"
#include "DynamicCourseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADynamicCourseGameMode::ADynamicCourseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
