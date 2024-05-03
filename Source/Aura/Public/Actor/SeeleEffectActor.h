// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SeeleEffectActor.generated.h"

class USphereComponent; 

//Does this actually work?
UCLASS()
class AURA_API ASeeleEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
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
