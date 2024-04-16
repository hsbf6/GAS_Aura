// Copyright Seele

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SeelePlayerController.generated.h"

class UInputMappingContext;
class UInputAction; 
struct FInputActionValue;



/**
 * 
 */
UCLASS()
class AURA_API ASeelePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASeelePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> SeeleContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue);
};
