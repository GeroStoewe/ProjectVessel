#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/NinjaGASAttributeSet.h"
#include "AS_Character.generated.h"


UCLASS()
class PROJECTVESSEL_API UAS_Character : public UNinjaGASAttributeSet
{
	GENERATED_BODY()


public:
	UAS_Character();

	// Health Attributes
    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UAS_Character, Health)

    UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAS_Character, MaxHealth)


public:
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldValue)
    {
        LAZY_GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, Health, OldValue);
    }

    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
    {
        LAZY_GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_Character, MaxHealth, OldValue);
    }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
};
