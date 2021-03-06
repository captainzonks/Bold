// © 2021, Matthew Barham. All rights reserved.


#include "BoldStarship.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABoldStarship::ABoldStarship()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>("Ship Mesh");
	ShipMesh->SetupAttachment(RootComponent);
	ShipMesh->SetSimulatePhysics(true);
	ShipMesh->SetEnableGravity(false);

	EngineL = CreateDefaultSubobject<UStaticMeshComponent>("EngineL");
	EngineL->SetupAttachment(ShipMesh);
	EngineL->SetRelativeLocation(FVector(-100, -100, 0));
	EngineL->SetRelativeRotation(FRotator(90, 0, 0));
	EngineL->SetRelativeScale3D(FVector(0.5, 0.5, 1));

	EngineR = CreateDefaultSubobject<UStaticMeshComponent>("EngineR");
	EngineR->SetupAttachment(ShipMesh);
	EngineR->SetRelativeLocation(FVector(-100, 100, 0));
	EngineR->SetRelativeRotation(FRotator(90, 0, 0));
	EngineR->SetRelativeScale3D(FVector(0.5, 0.5, 1));

	CockpitCamera = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CockpitCamera->SetupAttachment(ShipMesh);
	CockpitCamera->SetRelativeLocation(FVector(-65, 0, 145));
	CockpitCamera->SetRelativeRotation(FRotator(-20, 0, 0));
	CockpitCamera->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
	CockpitCamera->SetAutoActivate(false);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(ShipMesh);
	SpringArm->SetRelativeLocation(FVector(-40, 0, 100));
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 5.f;
	SpringArm->SocketOffset = FVector(0, 0, 45);
	SpringArm->TargetArmLength = 600.f;

	ExternalCamera = CreateDefaultSubobject<UCameraComponent>("External Camera");
	ExternalCamera->SetupAttachment(SpringArm);
	ExternalCamera->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
}

// Called when the game starts or when spawned
void ABoldStarship::BeginPlay()
{
	Super::BeginPlay();
}

void ABoldStarship::SwitchCameraView()
{
	ExternalCamera->SetActive(!ExternalCamera->IsActive());
	CockpitCamera->SetActive(!CockpitCamera->IsActive());
}

// Called every frame
void ABoldStarship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABoldStarship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ToggleCameraView", IE_Pressed, this, &ABoldStarship::SwitchCameraView);
}
