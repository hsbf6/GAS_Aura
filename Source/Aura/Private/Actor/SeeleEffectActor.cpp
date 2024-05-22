// Copyright Seele


#include "Actor/SeeleEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SeeleAttributeSet.h"
#include "Components/SphereComponent.h"


ASeeleEffectActor::ASeeleEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	// Health pickup art mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	// Sphere collision for overlap event
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

}

void ASeeleEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now using const_cast as a hack!
	//Does this actually work? 
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const USeeleAttributeSet* SeeleAttributeSet = Cast<USeeleAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(USeeleAttributeSet::StaticClass()));

		USeeleAttributeSet* MutableSeeleAttributeSet = const_cast<USeeleAttributeSet*>(SeeleAttributeSet);
		// add 25 to health hard coded 
		MutableSeeleAttributeSet->SetHealth(SeeleAttributeSet->GetHealth() + 25.f);
		// temp
		MutableSeeleAttributeSet->SetMana(SeeleAttributeSet->GetMana() - 25.f);
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

	// Bind UObject instance and member function to dynamic multicast delegate
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASeeleEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASeeleEffectActor::EndOverlap);

}



