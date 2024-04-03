// Copyright Seele


#include "Character/SeeleCharacterBase.h"

// Sets default values
ASeeleCharacterBase::ASeeleCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASeeleCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


