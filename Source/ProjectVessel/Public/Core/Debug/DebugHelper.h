#pragma once

#include "CoreMinimal.h"

/**
 * Lightweight Debug Utility for On-Screen Messages
 * - Safe null checks for GEngine
 * - Supports formatted text
 * - Easy to use across the project
 */
class PROJECTVESSEL_API FPVDebugHelper
{
public:

    /** Simple text print */
    static void Print(const FString& Message, const FColor& Color = FColor::Green, float Duration = 5.f)
    {
#if !UE_BUILD_SHIPPING
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
        }
#endif
    }

    /** Warning style */
    static void Warning(const FString& Message, float Duration = 5.f)
    {
        Print(Message, FColor::Yellow, Duration);
    }

    /** Error style */
    static void Error(const FString& Message, float Duration = 5.f)
    {
        Print(Message, FColor::Red, Duration);
    }

    /** Formatted print (like printf) */
    template<typename... Args>
    static void Printf(const FString& Format, Args... args)
    {
#if !UE_BUILD_SHIPPING
        const FString Message = FString::Printf(*Format, args...);
        Print(Message);
#endif
    }

    /** Formatted warning */
    template<typename... Args>
    static void Warningf(const FString& Format, Args... args)
    {
#if !UE_BUILD_SHIPPING
        const FString Message = FString::Printf(*Format, args...);
        Warning(Message);
#endif
    }

    /** Formatted error */
    template<typename... Args>
    static void Errorf(const FString& Format, Args... args)
    {
#if !UE_BUILD_SHIPPING
        const FString Message = FString::Printf(*Format, args...);
        Error(Message);
#endif
    }
};