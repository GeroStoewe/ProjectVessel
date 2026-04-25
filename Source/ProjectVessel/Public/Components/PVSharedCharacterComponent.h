#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PVSharedCharacterComponent.generated.h"


class ACharacter;


USTRUCT(BlueprintType)
struct FPVSharedMovementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CapsuleRadius = 42.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CapsuleHalfHeight = 96.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bUseControllerRotationPitch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bUseControllerRotationYaw = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bUseControllerRotationRoll = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bOrientRotationToMovement = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FRotator RotationRate = FRotator(0.f, 500.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpZVelocity = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AirControl = 0.35f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxWalkSpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinAnalogWalkSpeed = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BrakingDecelerationWalking = 2000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BrakingDecelerationFalling = 1500.f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTVESSEL_API UPVSharedCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPVSharedCharacterComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shared")
	FPVSharedMovementSettings MovementSettings;

	UFUNCTION(BlueprintCallable, Category = "Shared")
	void ApplySharedDefaultsToCharacter(ACharacter* Character);
};
