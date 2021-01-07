// © 2021, Matthew Barham. All rights reserved.


#include "BoldPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetInteractionComponent.h"

// Sets default values
ABoldPlayerCharacter::ABoldPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>("Widget Interaction Component");
	WidgetInteractionComponent->SetupAttachment(RootComponent);
	WidgetInteractionComponent->InteractionSource = EWidgetInteractionSource::Mouse;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	check(CameraComponent);
	CameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	CameraComponent->SetRelativeLocation(FVector(0, 0, 50.f + BaseEyeHeight));
	CameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ABoldPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using BoldPlayerCharacter."));
}

void ABoldPlayerCharacter::PressPointerKey()
{
	if (WidgetInteractionComponent->IsOverInteractableWidget())
	{
		WidgetInteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
	}
}

void ABoldPlayerCharacter::ReleasePointerKey()
{
	if (WidgetInteractionComponent->IsOverInteractableWidget())
	{
		WidgetInteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
	}
}

// Called every frame
void ABoldPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoldPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &ABoldPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABoldPlayerCharacter::MoveRight);

	// Set up "look" bindings
	PlayerInputComponent->BindAxis("Turn", this, &ABoldPlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABoldPlayerCharacter::AddControllerPitchInput);

	// Set up "action" bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABoldPlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABoldPlayerCharacter::StopJump);

	// Set up "widget interaction" bindings
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &ABoldPlayerCharacter::PressPointerKey);
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Released, this, &ABoldPlayerCharacter::ReleasePointerKey);
}

void ABoldPlayerCharacter::MoveForward(float const Value)
{
	// Find which way is "forward" and record that the player wants to move that way
	FVector const Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	AddMovementInput(Direction, Value);
}

void ABoldPlayerCharacter::MoveRight(float const Value)
{
	// Find which way is "right" and record that the player wants to move that way
	FVector const Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	AddMovementInput(Direction, Value);
}

void ABoldPlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void ABoldPlayerCharacter::StopJump()
{
	bPressedJump = false;
}

