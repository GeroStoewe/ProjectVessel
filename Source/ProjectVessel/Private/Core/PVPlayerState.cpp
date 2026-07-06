#include "Core/PVPlayerState.h"
#include "Net/UnrealNetwork.h"


APVPlayerState::APVPlayerState()
{
	bReplicates = true;
}


void APVPlayerState::SetUnlockedCrystals(int32 NewValue)
{
	const int32 ClampedValue = FMath::Clamp(NewValue, 0, 5);

	if (UnlockedCrystals == ClampedValue)
	{
		return;
	}

	const int32 OldValue = UnlockedCrystals;
	UnlockedCrystals = ClampedValue;

	OnUnlockedCrystalsChanged.Broadcast(UnlockedCrystals, OldValue);
}

void APVPlayerState::UnlockNextCrystal()
{
	SetUnlockedCrystals(UnlockedCrystals + 1);
}

void APVPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APVPlayerState, UnlockedCrystals);
}

void APVPlayerState::OnRep_UnlockedCrystals(int32 OldValue)
{
	OnUnlockedCrystalsChanged.Broadcast(UnlockedCrystals, OldValue);
}
