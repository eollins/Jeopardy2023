// Fill out your copyright notice in the Description page of Project Settings.


#include "SHTTPRequestsWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SHTTPRequestsWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SHTTPRequestsWidget::Register(FString username, FString password, FString email)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", username);
	RequestObj->SetStringField("password", password);
	RequestObj->SetStringField("email", email);

	SHTTPRequestsWidget::POST(Request, RequestObj);
}

void SHTTPRequestsWidget::POST(FHttpRequestRef Request, TSharedRef<FJsonObject> RequestObj)
{
	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindRaw(this, &SHTTPRequestsWidget::OnResponseReceived);
	Request->SetURL("http://ec2-54-67-85-210.us-west-1.compute.amazonaws.com/register.php");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void SHTTPRequestsWidget::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	UE_LOG(LogTemp, Display, TEXT("Reponse %s"), *Response->GetContentAsString());
}