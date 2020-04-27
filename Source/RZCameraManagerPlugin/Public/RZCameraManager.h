#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/DataTable.h"
#include "RZCameraManager.generated.h"

UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	FreeFirstPerson,
	FreeTopDown,
	FirstPerson,
	ThirdPerson
};

USTRUCT(BlueprintType)
struct FCameraSettings : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	ECameraMode CameraMode;

	UPROPERTY(EditDefaultsOnly)
	float LookSpeed;

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly)
	float DefaultHeight;

	UPROPERTY(EditDefaultsOnly)
	float DefaultPitch;

	UPROPERTY(EditDefaultsOnly)
	float PitchMin;

	UPROPERTY(EditDefaultsOnly)
	float PitchMax;

	UPROPERTY(EditDefaultsOnly)
	float PitchStep;

	FCameraSettings()
	{
		CameraMode = ECameraMode::FreeTopDown;
		LookSpeed = 1.5f;
		MoveSpeed = 10.0f;
		DefaultHeight = 400.0f;
		DefaultPitch = -60.0f;
		PitchMin = -85.0f;
		PitchMax = -20.0f;
		PitchStep = 5.0f;
	}
};

UCLASS()
class RZCAMERAMANAGERPLUGIN_API ARZCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	ARZCameraManager();

	UFUNCTION(BlueprintCallable, Category = "Camera Controls")
	void LookUp(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Controls")
	void LookRight(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Controls")
	void MoveForward(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Controls")
	void MoveRight(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Controls")
	void MoveUp(float AxisValue);

	UFUNCTION(BlueprintCallable, Category = "Camera Controls")
	void MoveTo(FVector Location, FRotator Rotation, bool bTeleport);

	UFUNCTION(BlueprintCallable, Category = "Camera Controls")
	void ToggleFreeLook(bool bShouldEnable);

	UFUNCTION(BlueprintCallable, Category = "Camera Settings")
	void EditSettings(float LookSpeed, float MoveSpeed);

	//
	void AddRotation(FRotator RotationToAdd);
	void PitchUp();
	void PitchDown();
	void SetDefaultPitch();
	//

protected:

	virtual void BeginPlay() override;
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

private:

	FCameraSettings Settings;

	FVector TargetLocation;
	FRotator TargetRotation;

	bool bIsFreeLook;
	bool bShouldTeleport;

	////
	FVector CurrentOffsetX;
	FVector CurrentOffsetY;
	FRotator CurrentRotation;
	float TargetZoom;
	float CurrentZoom;
	////
};
