// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPropellerComponent.h"

UMyPropellerComponent::UMyPropellerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Set_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (Set_Propeller.Succeeded())
	{
		SetStaticMesh(Set_Propeller.Object);
	}
}

void UMyPropellerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AddRelativeRotation(FRotator(0, 0, 7200.0f * DeltaTime));
}