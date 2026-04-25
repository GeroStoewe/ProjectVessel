#include "GameplayAbilitySystem/AttributeSets/AS_Character.h"
#include "Net/UnrealNetwork.h"


UAS_Character::UAS_Character()
    : Health(100.f)
    , MaxHealth(100.f)
{
}


void UAS_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UAS_Character, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UAS_Character::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
    }
}
