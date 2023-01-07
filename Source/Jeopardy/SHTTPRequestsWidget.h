// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class JEOPARDY_API SHTTPRequestsWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHTTPRequestsWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void Register(FString Username, FString Password, FString Email);

private:
	void POST(FHttpRequestRef Request, TSharedRef<FJsonObject> RequestObj);
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectedSuccessfully);
};
