#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NinjaGASCharacter.h"
#include "PVEnemyCharacter.generated.h"


class UPVSharedCharacterComponent;


UCLASS()
class PROJECTVESSEL_API APVEnemyCharacter : public ANinjaGASCharacter
{
	GENERATED_BODY()

public:
	APVEnemyCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPVSharedCharacterComponent> SharedCharacterComponent;

	virtual void BeginPlay() override;
};
