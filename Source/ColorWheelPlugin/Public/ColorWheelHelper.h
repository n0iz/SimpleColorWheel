// Copyright (c) n0iz 2024. All Rights Reserved.
// Copyright (c) W2.Wizard 2020-2021. All Rights Reserved.

#pragma once

// Core
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Framework/Application/SlateApplication.h"
#include "ColorWheelTypes.h"

// Generated.h
#include "ColorWheelHelper.generated.h"

/**
 * A Helper BP Library for various additional functions that someone might need, like hexadecimal conversion, random color, etc...
 */
UCLASS()
class COLORWHEELPLUGIN_API UColorWheelHelper : public UBlueprintFunctionLibrary
{
public:
	
	GENERATED_BODY()

	/**
	*	Converts a hexadecimal string value to a byte value.
	*	@param Hex				The Hexadecimal value
	*	@return					The value as a byte
	*/
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta=(DisplayName="Hex ➜ Byte", Keywords = "hex byte convert"))
    static uint8 HexToByte(FString Hex);
	
	/**
	*	Converts a byte value to a Hexadecimal value represented as a string.
	*	@param Byte				The byte value
	*	@return					The value as a hexadecimal represented in a string
	*/
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta=(DisplayName="Byte ➜ Hex", Keywords = "hex byte convert"))
    static FORCEINLINE FString ByteToHex(uint8 Byte) { return FString::Printf(TEXT("%02X"), Byte); }
	
	/**
	*	Converts a Hex from an FString value to a FColor value, needs to contain all channels so simply writing #FF won't
	*	work!
	*	@param Hex				The Hexadecimal string value
	*	@return					Returns the RGBA value of the Hexadecimal value
	*/
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta=(DisplayName="Hex ➜ Color", Keywords = "hex convert rgb"))
    static FORCEINLINE FColor HexToColor(FString Hex) { return FColor::FromHex(Hex); }

	/**
	*	Converts a Hex from an FString value to a FLinearColor value, needs to contain all channels so simply writing #FF won't
	*	work!
	*	@param Hex				The Hexadecimal string value
	*	@return					Returns the linear color values of the Hexadecimal value
	*/
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta=(DisplayName="Hex ➜ LinearColor", Keywords = "hex convert rgb linear"))
    static FORCEINLINE FLinearColor HexToLinearColor(FString Hex) { return FLinearColor(FColor::FromHex(Hex)); }

    /**
    * Converts a Hex from an FString value to a FColorHSV value, needs to contain all channels so simply writing #FF won't
    * work!
    * @param Hex The Hexadecimal string value
    * @return Returns the HSV value of the Hexadecimal value
	*/
    UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta = (DisplayName = "Hex ➜ HSV", Keywords = "hex convert hsv"))
    static FORCEINLINE FColorHSV HexToColorHSV(FString Hex) { return FColorHSV(FLinearColor(FColor::FromHex(Hex))); }

	/**
	*	Converts a FColor value to a FString value in Hexadecimal.
	*	@param Color			The RGBA Color
	*	@return					The Hex value as string
	*/
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta=(DisplayName="Color ➜ Hex", Keywords = "hex convert rgb"))
    static FORCEINLINE FString ColorToHex(const FColor Color) { return Color.ToHex(); }

	/**
	*	Converts a FLinearColor value to a FString value in Hexadecimal.
	*	@param Color			The linear color
	*	@param IsSRGB			Is the linear color in SRGB?
	*	@return					The Hex value as string
	*/
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta=(DisplayName="LinearColor ➜ Hex", Keywords = "hex convert rgb linear"))
    static FORCEINLINE FString LinearColorToHex(const FLinearColor Color, const bool IsSRGB) { return Color.ToFColor(IsSRGB).ToHex(); }

    /**
    * Converts a FColorHSV value to a FString value in Hexadecimal.
    * @param Color The HSV color to convert
    * @param IsSRGB Is the linear color in SRGB?
    * @return The Hex value as string
	*/
    UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta = (DisplayName = "HSV ➜ Hex", Keywords = "hex convert hsv"))
    static FORCEINLINE FString ColorHSVToHex(const FColorHSV& Color, const bool IsSRGB) { return Color.GetLinearColor().ToFColor(IsSRGB).ToHex(); }

	/**
	 * Returns a randomized linear color value
	 * @param RandomAlpha Randomize the Alpha value aswell ?
	 * @param TrueRandom Should each channel of the color be randomized ?
	 * @return A random linear color
	 */
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Misc", meta=(DisplayName="Random Linear Color", Keywords = "random linear color"))
    static FLinearColor RandomLinearColor(bool RandomAlpha, bool TrueRandom);

	/**
	* Returns a randomized color value
	* @param RandomAlpha Randomize the Alpha value aswell ?
	* @param TrueRandom Should each channel of the color be randomized ?
	* @return A random color
	*/
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Misc", meta=(DisplayName="Random Color", Keywords = "random color"))
    static FColor RandomColor(bool RandomAlpha, bool TrueRandom);
	
	/**
	* Returns the current color under which the cursor is currently residing.
	* @return The current color under the cursor
	*/
	UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Misc", meta=(DisplayName="Get Color under Cursor", Keywords = " get cursor color"))
	static FORCEINLINE FLinearColor GetColorUnderCursor()
	{
		// Not sure if FSlateApplication is a safe way of getting the cursor position, but it does work.
		return FPlatformApplicationMisc::GetScreenPixelColor(FSlateApplication::Get().GetCursorPos(), 2.2f);
	};

    /**
    * Converts a FColorHSV value to a FLinearColor.    
    * @param Color The HSV color to convert
    * @return The converted LinearColor
	*/
    UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta = (DisplayName = "HSV ➜ LinearColor", Keywords = "hsv convert linear"))
    static FLinearColor HSVToLinearColor(const FColorHSV& Color)
	{
		return Color.GetLinearColor();
	}
	
    /**
    * Converts a FLinearColor value to a FColorHSV value.
    * @param Color The LinearColor to convert
    * @return The converted HSV color    
	*/
    UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|Conversion", meta = (DisplayName = "LinearColor ➜ HSV", Keywords = "linear convert hsv"))
    static FColorHSV LinearColorToHSV(const FLinearColor& Color);

	
    UFUNCTION(BlueprintPure, Category = "Color Wheel Helper|HSV", meta = (DisplayName = "Equals=", Keywords = "hsv equals compare"))
    static bool EqualsColorHSV(const FColorHSV& A, const FColorHSV& B)
    {
        return A == B;
    }

};
