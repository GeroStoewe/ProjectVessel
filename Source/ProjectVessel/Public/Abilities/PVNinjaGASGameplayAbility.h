#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/NinjaGASGameplayAbility.h"
#include "PVNinjaGASGameplayAbility.generated.h"


UCLASS()
class PROJECTVESSEL_API UPVNinjaGASGameplayAbility : public UNinjaGASGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bShouldShowInAbilitiesBar = false;
};
