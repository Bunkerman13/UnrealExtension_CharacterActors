// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\Characters\CustomCharacterBase.h"
#include "GameFramework\SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
ACustomCharacterBase::ACustomCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	MeshComp->SetupAttachment(RootComponent);

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	StartScale = FVector(1.0f, 1.0f, 1.0f);
	TargetScale = FVector(1.3f, 1.3f, 0.8f);
}

// Called when the game starts or when spawned
void ACustomCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACustomCharacterBase::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ACustomCharacterBase::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ACustomCharacterBase::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ACustomCharacterBase::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ACustomCharacterBase::Fire()
{
	//GetWorld()->GetFirstPlayerController()->PlayerCameraManager()->PlayCameraShake(CamShake, 1.0f);
}

void ACustomCharacterBase::Tick(float DeltaTime)
{
	SquashTimeline.TickTimeline(DeltaTime);
}

// Called to bind functionality to input
void ACustomCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACustomCharacterBase::Fire);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACustomCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACustomCharacterBase::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ACustomCharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ACustomCharacterBase::LookUpAtRate);
}

void ACustomCharacterBase::Landed(const FHitResult & Hit)
{
	Super::Landed(Hit);

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("SquashProgress"));
		SquashTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		SquashTimeline.SetLooping(false);
		SquashTimeline.PlayFromStart();
	}
}

void ACustomCharacterBase::SquashProgress(float Value)
{
	FVector NewScale = FMath::Lerp(StartScale, TargetScale, Value);
	MeshComp->SetWorldScale3D(NewScale);
}

