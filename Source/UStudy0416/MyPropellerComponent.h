// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MyPropellerComponent.generated.h"

/**
 * 
 */
UCLASS()
class USTUDY0416_API UMyPropellerComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UMyPropellerComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
