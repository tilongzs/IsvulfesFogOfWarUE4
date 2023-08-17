#include "RegisterToFOW.h"
#include "FogOfWarManager.h"
#include <Kismet/GameplayStatics.h>

URegisterToFOW::URegisterToFOW()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URegisterToFOW::BeginPlay()
{
	Super::BeginPlay();
	FString ObjectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Log, TEXT("I am alive %s"), *ObjectName);

	//registering the actor to the FOW Manager
	if (!Manager)
	{
		Manager = Cast<AFogOfWarManager>(UGameplayStatics::GetActorOfClass(this, AFogOfWarManager::StaticClass()));
	}

	if (Manager != nullptr) {
		Manager->RegisterFOWActor(GetOwner());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Please attach a FOW Manager"));
	}
}
