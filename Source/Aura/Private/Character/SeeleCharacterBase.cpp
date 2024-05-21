// Copyright Seele


#include "Character/SeeleCharacterBase.h"

// Sets default values
ASeeleCharacterBase::ASeeleCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Add a skeletal mesh component to the base class with name Weapon. 
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	//Attach it to WeaponHandSocket (created in editor)
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

//UASC pointer. GetAbilitySystemComponent in class ASeeleCharacterBase
UAbilitySystemComponent* ASeeleCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ASeeleCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


