#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FogOfWarWorker.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "FogOfWarManager.generated.h"

UCLASS()
class AFogOfWarManager : public AActor
{
	GENERATED_BODY()

public:
	//Triggers a update in the blueprint
	UFUNCTION(BlueprintNativeEvent)
		void OnFowTextureUpdated(UTexture2D* currentTexture, UTexture2D* lastTexture);

	UFUNCTION(BlueprintCallable, Category = FogOfWar)
		void debugTextureAccess();

	//Register an actor to influence the FOW-texture
	UFUNCTION(BlueprintCallable, Category = FogOfWar)
		void RegisterFOWActor(AActor* Actor);

	//Stolen from https://wiki.unrealengine.com/Dynamic_Textures
	void UpdateTextureRegions(
		UTexture2D* Texture,
		int32 MipIndex,
		uint32 NumRegions,
		FUpdateTextureRegion2D* Regions,
		uint32 SrcPitch,
		uint32 SrcBpp,
		const TArray<FColor>& Data,
		bool bFreeData);

	//The number of samples per 100 unreal units
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		float SamplesPerMeter = 4.0f;

	// 初始化时是否全部为未探索（全黑）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		bool bDefaultTerraIncog = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		//FColor	ColorOne = FColor((uint8)255, (uint8)255, (uint8)255, 255);
		uint8	UnfogColor = (uint8)255;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		uint8	FOWMaskColor = (uint8)100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		uint8	TerraIncogColor = (uint8)0;

	UPROPERTY(EditAnywhere, Category = FogOfWar)
		bool bUseTextureFile = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FogOfWar)
		UTexture2D* TextureInFile = nullptr;

	//If the last texture blending is done
	UPROPERTY(BlueprintReadWrite)
		bool bIsDoneBlending;

	//Should we blur? It takes up quite a lot of CPU time...
	UPROPERTY(EditAnywhere)
		bool bIsBlurEnabled = true;

	//The size of our textures
	uint32 TextureSize = 1024;

	// 从未探索过的区域数据（全黑）
	UPROPERTY()
		TArray<bool> TerraIncog;
	// 当前可视区域数据（全透明）
	UPROPERTY()
		TArray<bool> ViewingArea;

	//Temp array for horizontal blur pass
	UPROPERTY()
		TArray<uint8> HorizontalBlurData;

	//Our texture data (result of vertical blur pass)
	UPROPERTY()
		TArray<FColor> TextureData;

	//Our texture data from the last frame
	UPROPERTY()
		TArray<FColor> LastFrameTextureData;

	UPROPERTY()
		TArray<FColor> TextureInFileData;

	//Time Array
	UPROPERTY()
		TArray<float> FOWTimeArray;

	UPROPERTY()
		TArray<bool> FOWArray;

	UPROPERTY(EditAnywhere)
		bool bIsFOWTimerEnabled = false;

	UPROPERTY(EditAnywhere)
		float FOWTimeLimit = 5.0f;

	//Check to see if we have a new FOW-texture.
	bool bHasFOWTextureUpdate = false;

	//Blur size
	uint8 blurKernelSize = 15;

	//Blur kernel
	UPROPERTY()
		TArray<float> blurKernel;

	//Store the actors that will be unveiling the FOW-texture.
	UPROPERTY()
		TArray<AActor*> FOWActors;

	//DEBUG: Time it took to update the FOW texture
	float FOWUpdateTime = 0;

	//Getter for the working thread
	bool GetIsBlurEnabled();

	//Getter for the working thread
	bool GetIsTextureFileEnabled();

	//Temp method for logging an actor components names
	UFUNCTION(BlueprintCallable, Category = FogOfWar)
		void LogNames();
	// Sets default values for this actor's properties
	AFogOfWarManager();
	
	virtual ~AFogOfWarManager();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;

private:
	//Triggers the start of a new FOW-texture-update
	void StartFOWTextureUpdate();

	//Our dynamically updated texture
	UPROPERTY()
		UTexture2D* FOWTexture = nullptr;

	//Texture from last update. We blend between the two to do a smooth unveiling of newly discovered areas.
	UPROPERTY()
		UTexture2D* LastFOWTexture = nullptr;

	//Texture regions
	FUpdateTextureRegion2D* textureRegions = nullptr;

	//Our FOW updatethread
	AFogOfWarWorker* FOWThread = nullptr;

	//This is for accessing the actor component "RegisterToFow_BP"
	UActorComponent* ActorComp = nullptr;
};