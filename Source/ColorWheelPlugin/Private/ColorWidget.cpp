// Copyright (c) W2.Wizard 2020-2021. All Rights Reserved.

#include "ColorWidget.h"
#include "ColorWheelTypes.h"
#include "Misc/Attribute.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Framework/SlateDelegates.h"

/// Slate Overrides ///

TSharedRef<SWidget> UColorWidget::RebuildWidget()
{
    ColorWheel = SNew(SWColorWheel)
                .SelectedColor_UObject(this, &UColorWidget::GetColor)
                .SelectorPin(&SelectorPin)
                .HueCircle(&HueCircle)
                .OnMouseCaptureBegin_UObject(this, &UColorWidget::MouseDown)
                .OnMouseCaptureEnd_UObject(this, &UColorWidget::MouseUp)
                .OnValueChanged(FOnColorHSVChanged::CreateUObject(this, &UColorWidget::OnColorWheelValueChanged))
                .OnPositionChanged(FOnPositionChanged::CreateUObject(this, &UColorWidget::OnPositionUpdated));
	
    return ColorWheel.ToSharedRef();
}

void UColorWidget::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    ColorWheel.Reset();
}

void UColorWidget::OnColorWheelValueChanged(FColorHSV NewValue)
{
    Color.H = NewValue.H;
    Color.S = NewValue.S;
    OnColorChanged.Broadcast(Color);
}


void UColorWidget::OnPositionUpdated(FVector2D NewPosition)
{
    //UE_LOG(LogTemp, Warning, TEXT("D - X: %f - Y: %f"), NewPosition.X, NewPosition.Y)
    OnPositionChanged.Broadcast(NewPosition);
}

/// Main Functions ///

void UColorWidget::SetColor(const FColorHSV NewColor, bool BroadcastUpdate)
{
    Color = NewColor;

    if (BroadcastUpdate)
    {
        OnColorChanged.Broadcast(Color);
    }
}

void UColorWidget::SetHue(float NewHue, bool BroadcastUpdate)
{
    Color.H = NewHue;    
    if(BroadcastUpdate)
    {
        OnColorChanged.Broadcast(Color);
    }
}

void UColorWidget::SetSaturation(float NewSaturation, bool BroadcastUpdate)
{
    Color.S = NewSaturation;
    if (BroadcastUpdate)
    {
        OnColorChanged.Broadcast(Color);
    }
}

void UColorWidget::SetValue(float NewValue, bool BroadcastUpdate)
{
    Color.V = NewValue;
    if (BroadcastUpdate)
    {
        OnColorChanged.Broadcast(Color);
    }
}

void UColorWidget::SetAlpha(float NewAlpha, bool BroadcastUpdate)
{
    Color.A = NewAlpha;
    if (BroadcastUpdate)
    {
        OnColorChanged.Broadcast(Color);
    }
}

FColorHSV UColorWidget::GetCurrentColor()
{
    return Color;
}

/// Generics ///

void UColorWidget::SetColorAndOpacity(FLinearColor InColorAndOpacity, TEnumAsByte<EWheelBrushTarget> Target)
{
    // Update the values themselves, again this doesnt look good so change it later perhaps.
    auto ColorVal = FSlateColor(InColorAndOpacity);
    switch (Target)
    {
        case EWheelBrushTarget::All:
            SelectorPin.TintColor = ColorVal;
            HueCircle.TintColor = ColorVal;
            break;

        case EWheelBrushTarget::SelectorPin:
            SelectorPin.TintColor = ColorVal;
            break;

        case EWheelBrushTarget::HueCircle:
            HueCircle.TintColor = ColorVal;
            break;
    }

    // Update the visual widget itself
    if (ColorWheel.IsValid())
    {
        ColorWheel->SetColorAndOpacity(InColorAndOpacity, Target);
    }
}



