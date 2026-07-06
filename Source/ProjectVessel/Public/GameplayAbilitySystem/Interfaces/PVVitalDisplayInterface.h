#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PVVitalDisplayInterface.generated.h"


UINTERFACE(MinimalAPI, BlueprintType)
class UPVVitalDisplayInterface : public UInterface
{
    GENERATED_BODY()
};

class PROJECTVESSEL_API IPVVitalDisplayInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, Category = "Vitals")
    void OnVitalStateChanged(float NewHealth, float MaxHealth, float OldHealth);
};
