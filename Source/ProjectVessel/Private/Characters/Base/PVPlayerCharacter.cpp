#include "Characters/Base/PVPlayerCharacter.h"
#include "Components/PVSharedCharacterComponent.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

APVPlayerCharacter::APVPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SharedCharacterComponent = CreateDefaultSubobject<UPVSharedCharacterComponent>(TEXT("SharedCharacterComponent"));
}

void APVPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SharedCharacterComponent)
	{
		SharedCharacterComponent->ApplySharedDefaultsToCharacter(this);
	}
}
