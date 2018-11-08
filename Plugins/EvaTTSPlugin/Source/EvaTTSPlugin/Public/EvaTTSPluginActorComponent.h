// Copyright 2018 Augmented Enterprise, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EvaTTSPluginActorComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EVATTSPLUGIN_API UEvaTTSPluginActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEvaTTSPluginActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Make Object", Keywords = "Make Object from class"), Category = "TextToSpeech")
		void MakeObject(UClass *ObjectClass, UObject* &CreatedObject)
	{
		CreatedObject = NewObject<UObject>((UObject*)GetTransientPackage(), ObjectClass);
		return;
	}
	
};
