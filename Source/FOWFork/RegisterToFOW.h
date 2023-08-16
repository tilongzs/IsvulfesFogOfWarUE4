#pragma once

#include "Components/ActorComponent.h"
#include "FogOfWarManager.h"
#include "RegisterToFOW.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOWFORK_API URegisterToFOW : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URegisterToFOW();

	// Called when the game starts
	virtual void BeginPlay() override;

	/*Select the FOW Manager*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		AFogOfWarManager* Manager = nullptr;
	/*Is the actor able to influence unfogged texels*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		bool WriteUnFog = true;
	/*Is the actor able to influence terra incognita texels*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		bool WriteTerraIncog = true;
	/*是否检查actor在黑幕(isActorInTerraIncog)或可视范围(isActorInViewingArea)内 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		bool bCheckActorFOW = false;
	/*Should the actor reveal texels that are out of LOS*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		bool bUseLineOfSight = true;
	/**/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FogOfWar)
		bool isActorInTerraIncog = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = FogOfWar)
		bool isActorInViewingArea = false;
	/*How far will the actor be able to see*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		FVector2D SightRange = FVector2D(9.0f);	
};
