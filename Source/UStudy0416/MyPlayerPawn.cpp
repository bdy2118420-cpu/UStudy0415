// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "MyPropellerComponent.h"
#include "MyRocket.h"
#include "EnhancedInputComponent.h"



// Sets default values
AMyPlayerPawn::AMyPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(55.0f, 53.0f, 8.0f));


	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Set_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));

	if (Set_Body.Succeeded())
	{
		Body->SetStaticMesh(Set_Body.Object);
	}

	Left = CreateDefaultSubobject<UMyPropellerComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UMyPropellerComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);

	
	Left->SetRelativeLocation(FVector(37.000000f, 21.000000f, 0.000000f));
	Right->SetRelativeLocation(FVector(37.000000f, -21.000000f, 0.000000f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->TargetArmLength = 300.f;
	SpringArm->SocketOffset = FVector(0, 0, 40.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraLagSpeed = 5.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(200.f, 0, 0));

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = MoveSpeed;
	Movement->Acceleration = 200.f;	
	Movement->Deceleration = 200.f;

	static ConstructorHelpers::FClassFinder<AMyRocket> BP_Rocket(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Rocket.BP_Rocket_C'"));
	if (BP_Rocket.Succeeded())
	{
		RocketTemplate = BP_Rocket.Class;
	}
}

// Called when the game starts or when spawned
void AMyPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddMovementInput(GetActorForwardVector());
}

// Called to bind functionality to input
void AMyPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPlayerPawn::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPlayerPawn::Roll);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPlayerPawn::Fire);
	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Pressed, this, &AMyPlayerPawn::Bost);
	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Released, this, &AMyPlayerPawn::UnBost);*/
	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &AMyPlayerPawn::Rotate);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPlayerPawn::Fire);
		UIC->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPlayerPawn::Boost);
		UIC->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPlayerPawn::Unboost);

	}
}

void AMyPlayerPawn::Rotate(const FInputActionValue& Value)
{
	FVector2D Rot = Value.Get<FVector2D>();
	Rot = Rot * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f;

	AddActorLocalRotation(FRotator(Rot.Y, 0, Rot.X));
}

void AMyPlayerPawn::Fire(const FInputActionValue& Value)
{
	GetWorld()->SpawnActor<AMyRocket>(RocketTemplate, Arrow->K2_GetComponentToWorld());
}

void AMyPlayerPawn::Boost(const FInputActionValue& Value)
{
	Movement->MaxSpeed = 500.0f;
}

void AMyPlayerPawn::Unboost(const FInputActionValue& Value)
{
	Movement->MaxSpeed = MoveSpeed;
}



