// Copyright Seele


#include "Character/SeeleCharacterBase.h"

// Sets default values
ASeeleCharacterBase::ASeeleCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);



}

UAbilitySystemComponent* ASeeleCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ASeeleCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


