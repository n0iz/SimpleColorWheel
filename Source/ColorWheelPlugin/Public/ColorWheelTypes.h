// Copyright (c) n0iz 2024. All Rights Reserved.
#pragma once

#include "ColorWheelTypes.generated.h"



USTRUCT(BlueprintType)
struct FColorHSV
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Wheel Helper|Conversion")
    float H;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Wheel Helper|Conversion")
    float S;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Wheel Helper|Conversion")
    float V;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color Wheel Helper|Conversion")
    float A;

    FColorHSV() : H(0), S(0), V(0), A(1) {}
    FColorHSV(float H, float S, float V, float A) : H(H), S(S), V(V), A(A) {}

    FColorHSV(const FLinearColor& Color)
    {
        FLinearColor HSVColor = Color.LinearRGBToHSV();
        H = HSVColor.R;
        S = HSVColor.G;
        V = HSVColor.B;
        A = HSVColor.A;
    }

    void operator= (const FLinearColor& Color)
    {
        FLinearColor HSVColor = Color.LinearRGBToHSV();
        H = HSVColor.R;
        S = HSVColor.G;
        V = HSVColor.B;
        A = HSVColor.A;
    }

    bool operator== (const FColorHSV& Other) const
    {
        return FMath::IsNearlyEqual(H,Other.H) && FMath::IsNearlyEqual(S,Other.S) && FMath::IsNearlyEqual(V,Other.V) && FMath::IsNearlyEqual(A,Other.A);
    }

    friend inline uint32 GetTypeHash(const FColorHSV& Color)
    {
        uint32 Hash = 20241209; //pre seed
        Hash = HashCombine(Hash, GetTypeHash(Color.H));
        Hash = HashCombine(Hash, GetTypeHash(Color.S));
        Hash = HashCombine(Hash, GetTypeHash(Color.V));
        Hash = HashCombine(Hash, GetTypeHash(Color.A));
        return Hash;
    }

    FLinearColor GetLinearColor() const
    {
        FLinearColor LinearColorHSV;
        LinearColorHSV.R = H;
        LinearColorHSV.G = S;
        LinearColorHSV.B = V;
        LinearColorHSV.A = A;

        return LinearColorHSV.HSVToLinearRGB();        
    }
};