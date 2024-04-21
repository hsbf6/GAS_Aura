// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "Character/SeeleCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "SeeleEnemy.generated.h"


/**
 * 
 */
UCLASS()
class AURA_API ASeeleEnemy : public ASeeleCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:

	ASeeleEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	bool bBlockVisibility; 

	
};
