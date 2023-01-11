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
	TArray<FString> ResponseContents;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "HTTP")
	void SuccessfulRegister();

	UPROPERTY(BlueprintReadWrite, Category = "HTTP");
	bool Read;

	enum Actions {
		NONE, REGISTER, LOGIN, LOGOUT, PING, HOSTREQUEST, HOSTEND, JOINREQUEST, CANCELREQUEST, FETCHPLAYERREQUESTS, VERIFYCONNECTIONS
	};

	int CurrentAction;

	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void Register(FString Username, FString Password, FString Email);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void Login(FString Username, FString Password);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void LogOut(FString Token);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void Ping(FString Token);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void RequestHost(FString Token);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void EndHost(FString Token);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void RequestJoin(FString GameCode, FString Token, FString DisplayName);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void RequestCancel(FString GameCode, FString Token);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void FetchPlayerRequests(FString GameCode);
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void VerifyConnections(FString IdentifierType, TArray<FString> Players);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void POST(FHttpRequestRef Request, TSharedRef<FJsonObject> RequestObj, FString URL);
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectedSuccessfully);
};
