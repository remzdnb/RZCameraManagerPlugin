#include "RZCameraManager.h"

ARZCameraManager::ARZCameraManager()
{
	//TargetLocation = FVector(0, 0, Settings.DefaultHeight);
	//TargetRotation = FRotator(Settings.DefaultPitch, 0, 0);
	bIsFreeLook = false;
}

void ARZCameraManager::BeginPlay()
{
	Super::BeginPlay();
}

void ARZCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{

	if (Settings.CameraMode == ECameraMode::FreeTopDown)
	{
		if (bShouldTeleport)
		{
			OutVT.POV.Location = TargetLocation;
			OutVT.POV.Rotation = TargetRotation;
			bShouldTeleport = false;
		}
		else
		{
			OutVT.POV.Location = FMath::Lerp(GetCameraLocation(), TargetLocation, 10.0f * DeltaTime);;
			OutVT.POV.Rotation = TargetRotation;
		}
	}

}

void ARZCameraManager::LookUp(float AxisValue)
{
	if (bIsFreeLook)
		TargetRotation = TargetRotation + FRotator(AxisValue * Settings.LookSpeed, 0, 0);
}

void ARZCameraManager::LookRight(float AxisValue)
{
	if (bIsFreeLook)
		TargetRotation = TargetRotation + FRotator(0, AxisValue * Settings.LookSpeed, 0);
}

void ARZCameraManager::MoveForward(float AxisValue)
{
	const FRotator YawRotation(0, GetCameraRotation().Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);

	TargetLocation = TargetLocation + Direction * AxisValue * Settings.MoveSpeed;
}

void ARZCameraManager::MoveRight(float AxisValue)
{
	const FRotator YawRotation(0, GetCameraRotation().Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	TargetLocation = TargetLocation + Direction * AxisValue * Settings.MoveSpeed;
}

void ARZCameraManager::MoveUp(float AxisValue)
{
	TargetLocation = TargetLocation + FVector(0, 0, AxisValue * Settings.MoveSpeed * 4);
}

void ARZCameraManager::MoveTo(FVector Location, FRotator Rotation, bool bTeleport)
{
	TargetLocation = Location;
	TargetRotation = Rotation;
	bShouldTeleport = bTeleport;
}

void ARZCameraManager::ToggleFreeLook(bool bShouldEnable)
{
	if (bShouldEnable)
		bIsFreeLook = true;
	else
		bIsFreeLook = false;
}

void ARZCameraManager::EditSettings(float LookSpeed, float MoveSpeed)
{
	Settings.LookSpeed = LookSpeed;
	Settings.MoveSpeed = MoveSpeed;
}




////
////

void ARZCameraManager::AddRotation(FRotator RotationToAdd)
{
	TargetRotation += RotationToAdd;
}

void ARZCameraManager::PitchUp()
{
	if (TargetRotation.Pitch - Settings.PitchStep >= Settings.PitchMin)
		TargetRotation -= FRotator(Settings.PitchStep, 0.0f, 0.0f);
}

void ARZCameraManager::PitchDown()
{
	if (TargetRotation.Pitch + Settings.PitchStep <= Settings.PitchMax)
		TargetRotation += FRotator(Settings.PitchStep, 0.0f, 0.0f);
}

void ARZCameraManager::SetDefaultPitch()
{
	TargetRotation = FRotator(Settings.DefaultPitch, TargetRotation.Yaw, 0.0f);
}

//GEngine->AddOnScreenDebugMessage(12, 5.f, FColor::Red, FString::Printf(TEXT("Mouse: x: %f, y: %f"), MouseX, MouseY));
//GEngine->AddOnScreenDebugMessage(13, 5.f, FColor::Red, FString::Printf(TEXT("Viewport size: x: %i, y: %i"), SizeX, SizeY));
//GEngine->AddOnScreenDebugMessage(14, 5.f, FColor::Red, FString::Printf(TEXT("Mouse with VP: x: %f, y: %f"), MouseX, MouseY));