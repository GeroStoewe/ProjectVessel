#include "Characters/Base/PVEnemyCharacter.h"
#include "Components/PVSharedCharacterComponent.h"


APVEnemyCharacter::APVEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SharedCharacterComponent = CreateDefaultSubobject<UPVSharedCharacterComponent>(TEXT("SharedCharacterComponent"));
}


void APVEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SharedCharacterComponent)
	{
		SharedCharacterComponent->ApplySharedDefaultsToCharacter(this);
	}
}
