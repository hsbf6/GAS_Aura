// Copyright Seele


#include "Character/SeeleEnemy.h"
#include "AbilitySystem/SeeleAbilitySystemComponent.h"
#include "AbilitySystem/SeeleAttributeSet.h"
#include "Aura/Aura.h"

//	forward declare
class UAbilitySystemComponent;

ASeeleEnemy::ASeeleEnemy() //constructor
{
	// This is so that post process red lines around enemy work
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	// Create the ASC on an enemy
	AbilitySystemComponent = CreateDefaultSubobject<USeeleAbilitySystemComponent>("AbilitySystemComponent");
	// Network
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	//Create AS on an enemy
	AttributeSet = CreateDefaultSubobject<USeeleAttributeSet>("AttributeSet");
	}

void ASeeleEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	
	 
}

void ASeeleEnemy::InitAbilityActorInfo()
{
/*
	// assert if ASC is valid, else crash
	check(AbilitySystemComponent);
*/

	// For AI Pawns InitAbilityActorInfo is called right here in Begin Play
	// Changed implementation to virtual function in base class
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<USeeleAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
		


}

void ASeeleEnemy::HighlightActor()
{
	
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

}

void ASeeleEnemy::UnHighlightActor()
{
	
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
	
}
