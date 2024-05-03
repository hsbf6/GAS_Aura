// Copyright Seele


#include "Actor/SeeleEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SeeleAttributeSet.h"
#include "Components/SphereComponent.h"


ASeeleEffectActor::ASeeleEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");

	Sphere->SetupAttachment(GetRootComponent());

}

void ASeeleEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const USeeleAttributeSet* SeeleAttributeSet = Cast<USeeleAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(USeeleAttributeSet::StaticClass()));

		USeeleAttributeSet* MutableSeeleAttributeSet = const_cast<USeeleAttributeSet*>(SeeleAttributeSet);
		MutableSeeleAttributeSet->SetHealth(SeeleAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ASeeleEffectActor::EndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void ASeeleEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASeeleEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASeeleEffectActor::EndOverlap);

}



