// © 2021, Matthew Barham. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BoldStarship.generated.h"

UCLASS()
class BOLD_API ABoldStarship : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoldStarship();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* ShipMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* EngineL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* EngineR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* CockpitCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* ExternalCamera;

	UFUNCTION(BlueprintCallable)
	void SwitchCameraView();
};
