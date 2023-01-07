// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "HTTPRequests.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class JEOPARDY_API AHTTPRequests : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="HTTP")
	void Register(FString Username, FString Password, FString Email);
private:
	void POST(FHttpRequestRef Request, TSharedRef<FJsonObject> RequestObj);
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectedSuccessfully);
};
