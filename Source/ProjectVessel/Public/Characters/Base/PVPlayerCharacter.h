#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NinjaGASPlayerCharacter.h"
#include "GameplayAbilitySystem/Interfaces/PVVitalDisplayInterface.h"
#include "PVPlayerCharacter.generated.h"


class UPVSharedCharacterComponent;
class UChildActorComponent;
class APVPlayerState;
struct FOnAttributeChangeData;


UCLASS()
class PROJECTVESSEL_API APVPlayerCharacter : public ANinjaGASPlayerCharacter
{
	GENERATED_BODY()
	
public:
	APVPlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPVSharedCharacterComponent> SharedCharacterComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UChildActorComponent> VitalCompassComponent;

private:
	FDelegateHandle HealthDelegateHandle;

	bool bInitialVitalDisplaySent = false;

	APVPlayerState* GetPVPlayerState() const;
	AActor* GetVitalCompassActor() const;


public:
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

private:
	void BindHealthDelegate();
	void BindPlayerStateDelegates();
	UFUNCTION(BlueprintCallable, Category = "Vital")
	void RefreshVitalDisplay() const;
	void TryInitialVitalDisplay();
	void OnHealthChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void DebugDamageOneLife();

	UFUNCTION(BlueprintCallable, Category = "Debug")
	void DebugHealOneLife();
};
