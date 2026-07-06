#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NinjaGASPlayerState.h"
#include "PVPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUnlockedCrystalsChangedSignature, int32, NewValue, int32, OldValue);


UCLASS()
class PROJECTVESSEL_API APVPlayerState : public ANinjaGASPlayerState
{
	GENERATED_BODY()

public:
	APVPlayerState();

	UPROPERTY(BlueprintAssignable, Category = "Vitals")
	FOnUnlockedCrystalsChangedSignature OnUnlockedCrystalsChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing = OnRep_UnlockedCrystals, Category = "Vitals")
	int32 UnlockedCrystals = 3;


public:
	UFUNCTION(BlueprintCallable, Category = "Vitals")
	int32 GetUnlockedCrystals() const { return UnlockedCrystals; }

	UFUNCTION(BlueprintCallable, Category = "Vitals")
	void SetUnlockedCrystals(int32 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Vitals")
	void UnlockNextCrystal();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION()
	void OnRep_UnlockedCrystals(int32 OldValue);
};
