// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "HTTPRequestsActor.generated.h"

UCLASS()
class JEOPARDY_API AHTTPRequestsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHTTPRequestsActor();

	UPROPERTY(BlueprintReadWrite, Category = HTTP);
	FString ResponseContents;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "HTTP")
	void SuccessfulRegister();

	UPROPERTY(BlueprintReadWrite, Category = "HTTP");
	bool Read;

	enum Actions {
		NONE, REGISTER, LOGIN
	};

	int CurrentAction;

	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void Register(FString Username, FString Password, FString Email);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void POST(FHttpRequestRef Request, TSharedRef<FJsonObject> RequestObj);
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectedSuccessfully);
};
