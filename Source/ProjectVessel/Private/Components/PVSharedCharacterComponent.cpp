#include "Components/PVSharedCharacterComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UPVSharedCharacterComponent::UPVSharedCharacterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UPVSharedCharacterComponent::ApplySharedDefaultsToCharacter(ACharacter* Character)
{
	if (!Character)
	{
		return;
	}

	if (UCapsuleComponent* Capsule = Character->GetCapsuleComponent())
	{
		Capsule->InitCapsuleSize(MovementSettings.CapsuleRadius, MovementSettings.CapsuleHalfHeight);
	}

	Character->bUseControllerRotationPitch = MovementSettings.bUseControllerRotationPitch;
	Character->bUseControllerRotationYaw = MovementSettings.bUseControllerRotationYaw;
	Character->bUseControllerRotationRoll = MovementSettings.bUseControllerRotationRoll;

	if (UCharacterMovementComponent* Movement = Character->GetCharacterMovement())
	{
		Movement->bOrientRotationToMovement = MovementSettings.bOrientRotationToMovement;
		Movement->RotationRate = MovementSettings.RotationRate;
		Movement->JumpZVelocity = MovementSettings.JumpZVelocity;
		Movement->AirControl = MovementSettings.AirControl;
		Movement->MaxWalkSpeed = MovementSettings.MaxWalkSpeed;
		Movement->MinAnalogWalkSpeed = MovementSettings.MinAnalogWalkSpeed;
		Movement->BrakingDecelerationWalking = MovementSettings.BrakingDecelerationWalking;
		Movement->BrakingDecelerationFalling = MovementSettings.BrakingDecelerationFalling;
	}
}
