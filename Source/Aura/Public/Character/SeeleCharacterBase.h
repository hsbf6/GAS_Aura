// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SeeleCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API ASeeleCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASeeleCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	
};
