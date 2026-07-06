#include "Characters/Base/PVPlayerCharacter.h"
#include "Components/PVSharedCharacterComponent.h"
#include "GameplayAbilitySystem/AttributeSets/AS_Character.h"
#include "Core/PVPlayerState.h"
#include "Core/Debug/DebugHelper.h"

#include "AbilitySystemComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/PlayerState.h"


APVPlayerCharacter::APVPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SharedCharacterComponent = CreateDefaultSubobject<UPVSharedCharacterComponent>(TEXT("SharedCharacterComponent"));

	VitalCompassComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("VitalCompassComponent"));
	VitalCompassComponent->SetupAttachment(GetMesh(), FName(TEXT("VitalCompass_Socket")));
}


void APVPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SharedCharacterComponent)
	{
		SharedCharacterComponent->ApplySharedDefaultsToCharacter(this);
	}

	TryInitialVitalDisplay();
}

void APVPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	BindHealthDelegate();
	BindPlayerStateDelegates();
	TryInitialVitalDisplay();
}

void APVPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	BindHealthDelegate();
	BindPlayerStateDelegates();
	TryInitialVitalDisplay();
}

void APVPlayerCharacter::BindHealthDelegate()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	if (HealthDelegateHandle.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(UAS_Character::GetHealthAttribute()).Remove(HealthDelegateHandle);
		HealthDelegateHandle.Reset();
	}

	HealthDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(UAS_Character::GetHealthAttribute())
		.AddUObject(this, &APVPlayerCharacter::OnHealthChanged);
}

void APVPlayerCharacter::BindPlayerStateDelegates()
{
}

void APVPlayerCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	AActor* CompassActor = GetVitalCompassActor();
	if (!CompassActor)
	{
		return;
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	const float MaxHealth = ASC
		? ASC->GetNumericAttribute(UAS_Character::GetMaxHealthAttribute())
		: 3.f;

	IPVVitalDisplayInterface::Execute_OnVitalStateChanged(
		CompassActor,
		Data.NewValue,
		MaxHealth,
		Data.OldValue
	);
}

void APVPlayerCharacter::RefreshVitalDisplay() const
{
	AActor* CompassActor = GetVitalCompassActor();
	if (!CompassActor)
	{
		return;
	}

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();

	const float NewHealth = ASC
		? ASC->GetNumericAttribute(UAS_Character::GetHealthAttribute())
		: 0.f;

	const float MaxHealth = ASC
		? ASC->GetNumericAttribute(UAS_Character::GetMaxHealthAttribute())
		: 3.f;

	IPVVitalDisplayInterface::Execute_OnVitalStateChanged(
		CompassActor,
		NewHealth,
		MaxHealth,
		NewHealth
	);
}

void APVPlayerCharacter::TryInitialVitalDisplay()
{
	if (bInitialVitalDisplaySent)
	{
		return;
	}

	if (!GetAbilitySystemComponent())
	{
		return;
	}

	if (!GetVitalCompassActor())
	{
		return;
	}

	bInitialVitalDisplaySent = true;
	RefreshVitalDisplay();
}

APVPlayerState* APVPlayerCharacter::GetPVPlayerState() const
{
	return GetPlayerState<APVPlayerState>();
}

AActor* APVPlayerCharacter::GetVitalCompassActor() const
{
	return VitalCompassComponent ? VitalCompassComponent->GetChildActor() : nullptr;
}

void APVPlayerCharacter::DebugDamageOneLife()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	const float CurrentHealth = ASC->GetNumericAttribute(UAS_Character::GetHealthAttribute());
	ASC->SetNumericAttributeBase(UAS_Character::GetHealthAttribute(), FMath::Max(0.f, CurrentHealth - 1.f));
}

void APVPlayerCharacter::DebugHealOneLife()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	const float CurrentHealth = ASC->GetNumericAttribute(UAS_Character::GetHealthAttribute());
	const float MaxHealth = ASC->GetNumericAttribute(UAS_Character::GetMaxHealthAttribute());

	ASC->SetNumericAttributeBase(UAS_Character::GetHealthAttribute(), FMath::Min(MaxHealth, CurrentHealth + 1.f));
}
