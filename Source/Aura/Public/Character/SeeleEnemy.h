// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "Character/SeeleCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "SeeleEnemy.generated.h"



/** Enemy class
 *	Also derived from SeeleCharacterBase
 */ 
UCLASS()
class AURA_API ASeeleEnemy : public ASeeleCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:

	ASeeleEnemy();
	
	/** Enemy Interface
	 *  Draw outline around enemy
	 */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End Enemy Interface */

protected:
	virtual void BeginPlay() override;
	
};
