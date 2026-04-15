// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = CollisionBox;
	CollisionBox->SetBoxExtent(FVector(12.2f, 4.7f, 4.1f));

	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket"));
	RocketMesh->SetupAttachment(CollisionBox);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Rocket(TEXT("/Script/Engine.StaticMesh'/Game/Rocket/Meshes/SM_Rocket.SM_Rocket'"));
	RocketMesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	RocketMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));


	if (SM_Rocket.Succeeded())
	{
		RocketMesh->SetStaticMesh(SM_Rocket.Object);
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Move"));
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AMyRocket::ProcessActorBeginOverlap);

	SetLifeSpan(2.f);
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyRocket::ProcessActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Destroy();
}

