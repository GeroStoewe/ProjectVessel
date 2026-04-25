#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NinjaGASPlayerCharacter.h"
#include "PVPlayerCharacter.generated.h"


class UPVSharedCharacterComponent;


UCLASS()
class PROJECTVESSEL_API APVPlayerCharacter : public ANinjaGASPlayerCharacter
{
	GENERATED_BODY()
	
public:
	APVPlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPVSharedCharacterComponent> SharedCharacterComponent;

	virtual void BeginPlay() override;
};
