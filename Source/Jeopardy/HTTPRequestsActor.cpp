// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTPRequestsActor.h"

// Sets default values
AHTTPRequestsActor::AHTTPRequestsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHTTPRequestsActor::BeginPlay()
{
	Super::BeginPlay();
	AHTTPRequestsActor::Read = true;
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::NONE;
}

// Called every frame
void AHTTPRequestsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Fill out your copyright notice in the Description page of Project Settings.


void AHTTPRequestsActor::Register(FString username, FString password, FString email)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", username);
	RequestObj->SetStringField("password", password);
	RequestObj->SetStringField("email", email);

	AHTTPRequestsActor::POST(Request, RequestObj, "register.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::REGISTER;
}

void AHTTPRequestsActor::Login(FString Username, FString Password)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("username", Username);
	RequestObj->SetStringField("password", Password);

	AHTTPRequestsActor::POST(Request, RequestObj, "login.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::LOGIN;
}

void AHTTPRequestsActor::LogOut(FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("token", Token);

	AHTTPRequestsActor::POST(Request, RequestObj, "logout.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::LOGOUT;
}

void AHTTPRequestsActor::Ping(FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("token", Token);

	AHTTPRequestsActor::POST(Request, RequestObj, "ping.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::PING;
}

void AHTTPRequestsActor::RequestHost(FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("HostToken", Token);

	AHTTPRequestsActor::POST(Request, RequestObj, "hostgame.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::HOSTREQUEST;
}

void AHTTPRequestsActor::EndHost(FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("HostToken", Token);

	AHTTPRequestsActor::POST(Request, RequestObj, "endgame.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::HOSTEND;
}

void AHTTPRequestsActor::RequestJoin(FString GameCode, FString Token)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("Token", Token);
	RequestObj->SetStringField("GameCode", GameCode);

	AHTTPRequestsActor::POST(Request, RequestObj, "joingame.php");
	AHTTPRequestsActor::CurrentAction = AHTTPRequestsActor::Actions::JOINREQUEST;
}

void AHTTPRequestsActor::POST(FHttpRequestRef Request, TSharedRef<FJsonObject> RequestObj, FString URL)
{
	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &AHTTPRequestsActor::OnResponseReceived);
	Request->SetURL("http://ec2-54-67-85-210.us-west-1.compute.amazonaws.com/" + URL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void AHTTPRequestsActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	FString Contents = *Response->GetContentAsString();

	if (ResponseObj != NULL) {
		if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::REGISTER) {
			AHTTPRequestsActor::ResponseContents = ResponseObj->GetStringField("REGISTER");
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::LOGIN) {
			AHTTPRequestsActor::ResponseContents = ResponseObj->GetStringField("Login");
			AHTTPRequestsActor::ResponseContents2 = ResponseObj->GetStringField("Token");
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::LOGOUT) {
			AHTTPRequestsActor::ResponseContents = ResponseObj->GetStringField("Logout");
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::PING) {
			AHTTPRequestsActor::ResponseContents = ResponseObj->GetStringField("Ping");
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::HOSTREQUEST) {
			AHTTPRequestsActor::ResponseContents = ResponseObj->GetStringField("Host");
			AHTTPRequestsActor::ResponseContents2 = ResponseObj->GetStringField("GameCode");
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::HOSTEND) {
			AHTTPRequestsActor::ResponseContents = ResponseObj->GetStringField("Host");
		}
		else if (AHTTPRequestsActor::CurrentAction == AHTTPRequestsActor::Actions::JOINREQUEST) {
			AHTTPRequestsActor::ResponseContents = ResponseObj->GetStringField("Join");
		}
	}
	else {
		AHTTPRequestsActor::ResponseContents = "Disconnected";
	}

	AHTTPRequestsActor::Read = false;
}