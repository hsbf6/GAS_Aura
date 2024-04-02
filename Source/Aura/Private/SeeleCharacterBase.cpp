// Copyright Seele


#include "SeeleCharacterBase.h"

// Sets default values
ASeeleCharacterBase::ASeeleCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASeeleCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASeeleCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASeeleCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

