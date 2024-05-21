// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeeleEffectActor.generated.h"

class USphereComponent; 

/*	Effect actor; Couldn't quite remember what this was.
 *	Base class to add some kind of effect to the ASC and AS
 *	Currently implemented as a health pickup.
 *	If picked up, adds 25 health and is then destroyed
 *	
 */
UCLASS()
class AURA_API ASeeleEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// constructor
	ASeeleEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OnComponentEndOverlap, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh; 

};
